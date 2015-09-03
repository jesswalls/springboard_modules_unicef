<?php

/**
 * @file
 * Contains SalesforceSync.
 */

/**
 * Performs syncronization processes between Salesforce and Drupal records.
 */
class SalesforceSync {

  /**
   * Salesforce object to connect with
   *
   * @var Salesforce
   */
  public $sfapi;

  /**
   * SalesforceSoapPartner object to connect to Salesforce via SOAP.
   *
   * @var SalesforceSoapPartner
   */
  public $soap;

  /**
   * SalesforceSyncTokenScanner object used to do token replacements in batches.
   *
   * @var $tokenScanner
   */
  protected $tokenScanner;

  /**
   * The maximum number of items that can be sent to Salesforce in one call.
   *
   * @var int
   */
  protected $maxBatchSize = 200;

  /**
   * Maximum length a query can be to Salesforce before it is rejected.
   *
   * @var int
   */
  protected $maxQueryLength = 10000;

  /**
   * Maximum quantity of records that can ever be retrieved.
   *
   * @var int
   */
  protected $queryLimit = 4000;

  /**
   *  A running log of the new records created in Salesforce.
   *
   * @var array
   */
  public $newSfRecords = array();

  /**
   * Running log of all the Ids of Salesforce records that have been processed.
   *
   * @var array
   */
  public $processedItemIds = array();

  /**
   * Constructor for SalesforceSync.
   *
   * @param Salesforce $sfapi
   *   Optionally provide a Salesforce API object, otherwise the default version
   *   will be used.
   * @param SalesforceSoapPartner $soap
   *   Optionally provide a SOAP partner object, otherwise the default version
   *   will be used.
   */
  public function __construct(Salesforce $sfapi = NULL, SalesforceSoapPartner $soap = NULL) {
    $this->maxQueryLength = variable_get('salesforce_sync_max_query_length', SALESFORCE_SYNC_MAX_QUERY_LENGTH_DEFAULT);
    $this->maxBatchSize = variable_get('salesforce_sync_max_batch_size', SALESFORCE_SYNC_MAX_BATCH_SIZE_DEFAULT);
    $this->maxRetrieveSize = variable_get('salesforce_sync_max_retrieve_size', SALESFORCE_SYNC_MAX_RETRIEVE_SIZE_DEFAULT);
    $this->queryLimit = variable_get('salesforce_sync_query_limit', SALESFORCE_SYNC_QUERY_LIMIT_DEFAULT);
    $this->tokenScanner = new SalesforceSyncTokenScanner($this->getProcessedItemIds());
    $this->setSalesforceApi($sfapi);
    $this->setSalesforceSoap($soap);
  }

  /**
   * Apply sync rules to an item's fields based on its consumer's values.
   *
   * @param array $item_fields
   *   The array of fields of the item to be manipulated in order to have the
   *   sync rules  applied to it.
   * @param mixed $consumer_fields
   *   The fields of the record that will consume the item and is therefore used
   *   to compare with in order to apply the sync rules.  This can be provided
   *   as an array, or as an object, such as what is received from a Salesforce
   *   response.
   * @param array $sync_rules
   *   Associative array of Field-by-field sync rules for the fields that
   *   require rules.  The array is keyed by the Salesforce field name with the
   *   value being one of the 4 sync rules.
   */
  public function applySyncRules($item_fields, $consumer_fields, $sync_rules) {
    $consumer_fields = (array) $consumer_fields;
    foreach ($sync_rules as $field => $sync_rule) {
      switch ($sync_rule) {
        case SALESFORCE_SYNC_RULE_ALWAYS:
          // Leave the field as is.
          break;

        case SALESFORCE_SYNC_RULE_BLANK:
          // Check to see if source version is blank, otherwise set the target's
          // value to that of the source's value.  We are setting the value
          // instead of unsetting the target's field because 1) The dedupe field
          // must be provided when syncing to Salesforce, and the dedupe field
          // would most likely have this sync rule, and 2) When syncing with
          // Drupal unknown effects may occur when an expected field has no
          // value.
          if (isset($consumer_fields[$field]) && (
               (is_int($consumer_fields[$field]) && is_numeric($consumer_fields[$field])) ||
               (!is_int($consumer_fields[$field]) && !empty($consumer_fields[$field]))
             )) {
            $item_fields[$field] = $consumer_fields[$field];
          }
          break;

        case SALESFORCE_SYNC_RULE_APPEND:
          // When the source version is not blank, add value from source to the
          // begining of the target's value.
          if (isset($consumer_fields[$field]) && (
               (is_int($consumer_fields[$field]) && is_numeric($consumer_fields[$field])) ||
               (!is_int($consumer_fields[$field]) && !empty($consumer_fields[$field]))
             )) {
            $joined_value = $consumer_fields[$field] . ' ' . $item_fields[$field];
            $item_fields[$field] = $joined_value;
          }
          break;

        case SALESFORCE_SYNC_RULE_NEVER:
          // For the same reasoning as the 'blank' sync rule, we are setting the
          // value to the source value rather than unsetting the target field.
          if (isset($consumer_fields[$field])) {
            $item_fields[$field] = $consumer_fields[$field];
          }
          else {
            unset($item_fields[$field]);
          }
          break;
      }
    }
    return $item_fields;
  }


  /**
   * @name salesforce_sync_drupal_to_salesforce Drupal to Salesforce methods
   * @{
   */

  /**
   * Send a bundled batch of instructions to Salesforce.
   *
   * @param array $batch
   *   An array of instructions to send to Salesforce.  The array is structured
   *   as follows:
   *   <code>
   *     $batch = array(
   *       'operation' => 'UPSERT',
   *       'dedupe_field' => 'Email',
   *       'items' => array(
   *         array of items...
   *       ),
   *       'sobjects' => array(
   *         array of sobjects...
   *       ),
   *     );
   *   </code>
   *   Only UPSERT requires the 'dedupe_field' key.  For the 'DELETE' operation,
   *   instead of an 'sobjects' key, it requires an 'ids' key that is an array
   *   of Salesforce Ids of the items to delete.  The 'items' key is not
   *   required but recommended so that full information can be provided to
   *   modules that hook into the send processes.
   *
   * @return mixed
   *   Upon success, the Salesforce results are provided.  If there is an
   *   exception then it will return FALSE.
   */
  public function sendBatch($batch) {
    $this->sendBatchPrepare($batch);

    // If all items failed tokenization it is possible that the batch as a whole
    // will fail.
    if (isset($batch['sobjects']) && empty($batch['sobjects'])) {
      $this->failBatch($batch, SALESFORCE_SYNC_ITEM_FAIL_TOKEN_BATCH);
      return FALSE;
    }
    // Soap connection to Salesforce could never be established.
    if (!is_object($this->soap)) {
      $this->failBatch($batch, SALESFORCE_SYNC_ITEM_FAIL_SOAP);
      return FALSE;
    }

    // Send away.
    try {
      switch ($batch['operation']) {
        case 'CREATE':
          // Whole sobject.
          $results = $this->soap->create($batch['sobjects']);
          $error_message = SALESFORCE_SYNC_ITEM_FAIL_CREATE;
          break;

        case 'UPSERT':
          // Whole sobject + dedupe field.
          $results = $this->soap->upsert($batch['dedupe_field'], $batch['sobjects']);
          $error_message = SALESFORCE_SYNC_ITEM_FAIL_UPSERT;
          break;

        case 'UPDATE':
          // Whole sobject that includes Id + fields +/or fields to null.
          $results = $this->soap->update($batch['sobjects']);
          $error_message = SALESFORCE_SYNC_ITEM_FAIL_UPDATE;
          break;

        case 'DELETE':
          // Require just Id of the object.
          $results = $this->soap->delete($batch['ids']);
          $error_message = SALESFORCE_SYNC_ITEM_FAIL_DELETE;
          break;

        case 'UNDELETE':
          // Require just Id of the object.
          $results = $this->soap->undelete($batch['ids']);
          $error_message = SALESFORCE_SYNC_ITEM_FAIL_UNDELETE;
          break;

        default:
          // Unsupported operation.
          throw new Exception('salesforce_sync does not support the operation "' . $batch['operation'] . '"');
      }

      // Process results.
      $items = isset($batch['items']) ? $batch['items'] : (isset($batch['sobjects']) ? $batch['sobjects'] : array());
      // If all items failed token checks, $results could be empty.
      if (is_array($results)) {
        foreach ($results as $key => $result) {
          // Since we pass an item to others to trigger actions based on its
          // success, we should make sure we send the same type and structure of
          // item.
          if (isset($items[$key]) && isset($items[$key]->sobject)) {
            $item = $items[$key];
          }
          elseif (isset($items[$key])) {
            $sobject = $items[$key];
            $dedupe_field = isset($batch['dedupe_field']) ? $batch['dedupe_field'] : NULL;
            $item = new SalesforceSyncItem($sobject->type, $batch['operation'], array(), $dedupe_field);
            $item->sobject = $sobject;
          }
          else {
            $item = new SalesforceSyncItem();
            $item->sobject->Id = $result->Id;
          }
          if ($result->success) {
            $this->passItem($item, $result);
          }
          else {
            $this->failItem($item, $error_message, $result);
          }
          // Invokes hook_salesforce_sync_complete_item().
          // Provided as a last, final say on the item life cycle after delete
          // from the queue and the like.
          module_invoke_all('salesforce_sync_complete_item', $item, $result);
        }
      }
    }
    catch (Exception $error) {
      $results = FALSE;
      $this->failBatch($batch, SALESFORCE_SYNC_ITEM_FAIL_BATCH, $error);
    }
    return $results;
  }

  /**
   * Wrapper for sendBatch in order to send a single item to Salesforce.
   *
   * @param object $item
   *   An individual representation of a record and instructions of how that
   *   record will be consumed by the recipient.
   *
   * @return mixed
   *   Results of sendBatch. Upon success, the Salesforce results are provided.
   *   If there is an exception then it will return FALSE.
   */
  public function sendItem($item) {
    $batch = array(
      'object_type' => $item->object_type,
      'operation' => $item->operation,
      'dedupe_field' => (isset($item->dedupe_field) ? $item->dedupe_field : NULL),
      'items' => array($item),
      'sobjects' => array($item->sobject),
    );
    if (isset($item->sobject->Id)) {
      $batch['ids'] = array($item->sobject->Id);
    }
    return $this->sendBatch($batch);
  }

  /**
   * Applies instructions on a batch in order to prepare it to be sent.
   *
   * @param array $batch
   *   An array of instructions to send to Salesforce.  The array is structured
   *   as follows:
   *   <code>
   *     $batch = array(
   *       'operation' => 'UPSERT',
   *       'dedupe_field' => 'Email',
   *       'items' => array(
   *         array of items...
   *       ),
   *       'sobjects' => array(
   *         array of sobjects...
   *       ),
   *     );
   *   </code>
   *   Only UPSERT requires the 'dedupe_field' key.  For the 'DELETE' operation,
   *   instead of an 'sobjects' key, it requires an 'ids' key that is an array
   *   of Salesforce Ids of the items to delete.  The 'items' key is not
   *   required but recommended so that full information can be provided to
   *   modules that hook into the send processes.
   */
  public function sendBatchPrepare(&$batch) {
    if (isset($batch['batch_prepared']) && $batch['batch_prepared']) {
      // No use continuing if this batch is already prepared.
      return;
    }
    // Last attempt to see if there is hope of getting a connection.
    if (!is_object($this->soap)) {
      $this->setSalesforceSoap();
    }
    $this->batchReplaceTokens($batch);
    $this->batchRemoveBadTokens($batch);
    $this->batchApplySalesforceSyncRules($batch);
    $this->batchConvertToSalesforceFormat($batch);
    $this->batchTruncateLongStrings($batch);
    $batch['batch_prepared'] = TRUE;
  }

  /**
   * Search and replace tokens in a batch of items.
   *
   * Uses a SalesforceSyncTokenScanner instance to search for and replace
   * relationship tokens in a batch of items.
   *
   * @param array $batch
   *   An array of instructions to send to Salesforce.  The array is structured
   *   as follows:
   *   <code>
   *     $batch = array(
   *       'operation' => 'UPSERT',
   *       'dedupe_field' => 'Email',
   *       'items' => array(
   *         array of items...
   *       ),
   *       'sobjects' => array(
   *         array of sobjects...
   *       ),
   *     );
   *   </code>
   */
  public function batchReplaceTokens(&$batch) {
    $this->tokenScanner->batchTokenReplace($batch);
  }

  /**
   * Remove items from batches that have bad tokens.
   *
   * Uses a SalesforceSyncTokenScanner instance to search for and replace
   * relationship tokens in a batch of items.
   *
   * @param array $batch
   *   An array of instructions to send to Salesforce.  The array is structured
   *   as follows:
   *   <code>
   *     $batch = array(
   *       'operation' => 'UPSERT',
   *       'dedupe_field' => 'Email',
   *       'items' => array(
   *         array of items...
   *       ),
   *       'sobjects' => array(
   *         array of sobjects...
   *       ),
   *     );
   *   </code>
   */
  public function batchRemoveBadTokens(&$batch) {
    if (!isset($batch['sobjects'])) {
      // Some batches do not have sobjects, such as delete.
      return;
    }
    foreach ($batch['sobjects'] as $index => $sobject) {
      if (isset($sobject->tokens_replaced) && $sobject->tokens_replaced == FALSE) {
        // Fail the item.
        $this->failItem($batch['items'][$index], SALESFORCE_SYNC_ITEM_FAIL_TOKEN);
        // Unset the object, and the item. Reset array indicies in each array
        // to prevent Salesforce from throwing SOAP error.
        unset($batch['sobjects'][$index]);
        $batch['sobjects'] = array_values($batch['sobjects']);
        unset($batch['items'][$index]);
        $batch['items'] = array_values($batch['items']);
      }
    }
  }

  /**
   * Applys the sync rules to a batch of items with Salesforce as the consumer.
   *
   * @param array $batch
   *   An array of instructions to send to Salesforce.  The array is structured
   *   as follows:
   *   <code>
   *     $batch = array(
   *       'operation' => 'UPSERT',
   *       'dedupe_field' => 'Email',
   *       'items' => array(
   *         array of items...
   *       ),
   *       'sobjects' => array(
   *         array of sobjects...
   *       ),
   *     );
   *   </code>
   *   Only UPSERT requires the 'dedupe_field' key.  For the 'DELETE' operation,
   *   instead of an 'sobjects' key, it requires an 'ids' key that is an array
   *   of Salesforce Ids of the items to delete.  The 'items' key is not
   *   required but recommended so that full information can be provided to
   *   modules that hook into the send processes.
   */
  public function batchApplySalesforceSyncRules(&$batch) {
    if ((!isset($batch['sync_rules']) || !$batch['sync_rules']['apply']) || (isset($batch['sync_rules_applied']) && $batch['sync_rules_applied'])) {
      // Skip because the sync rules are disabled or have already been applied
      // to this item.
      return;
    }
    else {
      // Declare we've checked this batch.
      $batch['sync_rules_applied'] = TRUE;
    }

    // Only required on UPSERT and UPDATE operations.
    $operation = $batch['operation'];
    if (!($operation != 'UPSERT' || $operation != 'UPDATE')) {
      return;
    }

    // Check to see if there are items to prepare and sync_rules to apply.
    if (!isset($batch['sync_rules']) || !isset($batch['items']) || empty($batch['items'])) {
      // Could not find items to prepare.
      return;
    }
    else {
      $items = &$batch['items'];
    }

    // Retreive records from Salesforce about the items in this batch.
    $object_type = $batch['object_type'];
    $sync_rules = $batch['sync_rules'];
    $sf_records = array();
    $upsert_ids = array();
    $dedupe_field = isset($batch['dedupe_field']) ? $batch['dedupe_field'] : NULL;
    if ($operation == 'UPDATE') {
      $records = $this->fetchByIds($object_type, $sync_rules['fields'], $sync_rules['ids']);
      foreach ($records as $record) {
        $sf_records[$record->Id] = $record->fields;
      }
    }
    elseif ($operation == 'UPSERT') {
      $records = $this->fetchByField($object_type, $sync_rules['fields'], $dedupe_field, $sync_rules['dedupe_values']);
      foreach ($records as $record) {
        $sf_records[$record->Id] = $record->fields;
        $upsert_ids[$record->fields->$dedupe_field] = $record->Id;
      }
    }

    // No point continuing if we didn't find anything.
    if (empty($sf_records)) {
      return;
    }

    // Go through the items and apply the sync rules based upon the information
    // just retreived from Salesforce.
    foreach ($items as $key => $item) {
      if (isset($item->sync_rules_applied) && $item->sync_rules_applied) {
        // Skip if the sync rules have already been applied to this item.
      }
      else {
        // Make sure item was actually found in Salesforce before continuing.
        $item_fields = &$items[$key]->sobject->fields;
        if ($operation == 'UPDATE') {
          $id = $item->sobject->Id;
        }
        else {
          $id = isset($upsert_ids["$item_fields[$dedupe_field]"]) ? $upsert_ids["$item_fields[$dedupe_field]"] : NULL;
        }
        if (is_string($id) && isset($sf_records[$id])) {
          $items[$key]->sobject->fields = $this->applySyncRules($item_fields, $sf_records[$id], $item->sync_rules);
        }
        $items[$key]->sync_rules_applied = TRUE;
      }
    }
  }

  /**
   * Applies the Salesforce format conversion to all items in the batch.
   *
   * @param array $batch
   *   An array of instructions to send to Salesforce.  The array is structured
   *   as follows:
   *   <code>
   *     $batch = array(
   *       'operation' => 'UPSERT',
   *       'dedupe_field' => 'Email',
   *       'items' => array(
   *         array of items...
   *       ),
   *       'sobjects' => array(
   *         array of sobjects...
   *       ),
   *     );
   *   </code>
   *   Only UPSERT requires the 'dedupe_field' key.  For the 'DELETE' operation,
   *   instead of an 'sobjects' key, it requires an 'ids' key that is an array
   *   of Salesforce Ids of the items to delete.  The 'items' key is not
   *   required but recommended so that full information can be provided to
   *   modules that hook into the send processes.
   */
  public function batchConvertToSalesforceFormat(&$batch) {
    if (isset($batch['converted_to_salesforce_format']) && $batch['converted_to_salesforce_format']) {
      // Skip because this batch has already had its items formats converted.
      return;
    }

    // Convert each item.
    foreach ($batch['items'] as $item) {
      $this->convertToSalesforceFormat($item);
    }

    // Mark the batch as converted.
    $batch['converted_to_salesforce_format'] = TRUE;
  }

  /**
   * Loops over items in a batch and passes each individual
   * item to a string truncation routine.
   *
   * @param array $batch
   *   A batch of sobjects being sent to Salesforce.
   */
  public function batchTruncateLongStrings(&$batch) {
    if (isset($batch['long_strings_truncated']) && $batch['long_strings_truncated']) {
      return;
    }

    foreach ($batch['items'] as $item) {
      $this->truncateLongStrings($item);
    }

    $batch['long_strings_truncated'] = TRUE;
  }

  /**
   * Convert the mapped values into a format compatible to send to Salesforce.
   *
   * @param object $item
   *   An individual representation of a record and instructions of how that
   *   record will be consumed by the recipient.
   */
  public function convertToSalesforceFormat(&$item) {
    if (isset($item->converted_to_salesforce_format) && $item->converted_to_salesforce_format) {
      // Skip because this item has already had its formats converted.
      return;
    }

    // Find the data types of all the Salesforce fields and store it in a means
    // so that we can attempt to reduce the number of times we have to search
    // for this information.
    $sfapi = $this->sfapi;
    if (!is_object($sfapi)) {
      // Skip if we do not have a valid Salesforce connection.  Do not mark the
      // item has having been converted in case the connection gets repaired
      // leter in the process.
      return;
    }
    $sfobject = $sfapi->objectDescribe($item->object_type);
    $field_datatypes = &drupal_static(__FUNCTION__);
    $field_missing = FALSE;
    foreach ($item->sobject->fields as $field_name => $value) {
      if (!isset($field_datatypes) || !isset($field_datatypes[$field_name])) {
        $field_missing = TRUE;
      }
    }
    $count = count($item->sobject->fields);
    if (!isset($field_datatypes) || $field_missing) {
      foreach ($sfobject['fields'] as $field) {
        if (array_key_exists($field['name'], $item->sobject->fields)) {
          $field_datatypes[$field['name']] = $field['type'];
          $count--;
          if ($count == 0) {
            break;
          }
        }
      }
    }

    // Perform the actual conversion.
    foreach ($item->sobject->fields as $field_name => $value) {
      if (!empty($field_datatypes[$field_name])) {
        switch ($field_datatypes[$field_name]) {
          case 'boolean':
            if (is_string($value)) {
              // An array of string values that are considered TRUE
              $valid_booleans = array('true', 'yes', '1');
              // if the value is in the array set it to TRUE
              if (in_array(strtolower(trim($value)), $valid_booleans)) {
                $value = TRUE;
              }
              // Default to FALSE
              else {
                $value = FALSE;
              }
            }

            // Convert any value that evaluates to TRUE as 1
            if ($value) {
              $item->sobject->fields[$field_name] = 1;
            }
            else {
              $item->sobject->fields[$field_name] = 0;
            }
            break;

          case 'datetime':
            // Salesforce requires ISO 8601 format for dates.
            if ($this->isValidTimestamp($value)) {
              $item->sobject->fields[$field_name] = date('c', $value);
            }
            elseif ($value != '') {
              $item->sobject->fields[$field_name] = date('c', strtotime($value));
            }
            break;

          case 'date':
            // Drupal dates come in all flavors. Check to see if it's a unix
            // timestamp. If it is we can skip strtotime().
            if ($this->isValidTimestamp($value)) {
              $item->sobject->fields[$field_name] = date('Y-m-d', $value);
            }
            elseif ($value != '') {
              $item->sobject->fields[$field_name] = date('Y-m-d', strtotime($value));
            }
            else {
              unset($item->sobject->fields[$field_name]);
              $item->sobject->fieldsToNull[] = $field_name;
            }
            break;

          case 'string':
          case 'textarea':
          case 'phone':
          case 'picklist':
          case 'url':
            // Make sure all strings are escaped correctly for XML.
            // htmlspecialchars will be sufficient for most strings. If more
            // robust escaping is needed consider using DOMDocument or SimpleXML
            // to beef this up.
            $item->sobject->fields[$field_name] = htmlspecialchars($value, ENT_QUOTES, 'UTF-8');
            break;

          // Numeric types cannot be null or they will throw a SOAP fault. Let's
          // ensure these types are actually numeric before sending them.
          case 'double':
          case 'int':
          case 'currency':
            if (!is_numeric($value)) {
              unset($item->sobject->fields[$field_name]);
              $item->sobject->fieldsToNull[] = $field_name;
            }
            break;

          default:
            // Do nothing.
        }
      }
    }

    // Mark the item as converted.
    $item->converted_to_salesforce_format = TRUE;
  }

  /**
   * Examine the text fields in an sobject to see if the field's value exceeds
   * the max length property set in Salesforce. If the string is too long it
   * will get truncated.
   *
   * @param array $batch
   *   A batch of sobjects being sent to Salesforce.
   */
  public function truncateLongStrings(&$item) {
    if (isset($item->long_strings_truncated) && $item->long_strings_truncated) {
      return;
    }

    // Get field length limits for any string-type fields on this SF object type.
    $field_lengths = &drupal_static(__FUNCTION__, array());
    if (!isset($field_lengths[$item->object_type])) {
      // Find the data types of all the Salesforce fields and store it in a means
      // so that we can attempt to reduce the number of times we have to search
      // for this information.
      $sfapi = $this->sfapi;
      if (!is_object($sfapi)) {
        // Skip if we do not have a valid Salesforce connection.  Do not mark the
        // item has having been converted in case the connection gets repaired
        // leter in the process.
        return;
      }
      $sfobject = $sfapi->objectDescribe($item->object_type);
      $field_lengths[$item->object_type] = array();
      foreach ($sfobject['fields'] as $field) {
        // Always truncate sobject Name, FirstName, and LastName. Optionally also truncate other string fields.
        if (
          in_array($field['name'], array('Name', 'FirstName', 'LastName'))
          || variable_get('salesforce_sync_truncate_long_strings', SALESFORCE_SYNC_TRUNCATE_LONG_STRINGS_DEFAULT)
        ) {
          // If this field is a type stored as a string, then note its maximum length for possible truncation.
          if ($this->typeIsText($field['type'])) {
            $field_lengths[$item->object_type][$field['name']] = $field['length'];
          }
        }
      }
    }

    // Check the lengths of all truncatable fields on this sObject.
    foreach ($field_lengths[$item->object_type] as $field_name => $field_length) {
      if (!empty($item->sobject->fields[$field_name]) && strlen($item->sobject->fields[$field_name]) > $field_length) {
        // Truncate the value of the field to the maximum length allowed by SF.
        $item->sobject->fields[$field_name] = substr($item->sobject->fields[$field_name], 0, $field_length);
        // Make sure no XML entity was truncated.
        // This regex looks for ampersands followed by zero or more
        // non-space and non-semicolons at the end of the string.
        // This would indicate a broken entity due to truncation.
        // Note that at this point the string has already been escaped, so
        // there shouldn't be stray ampersands without matching semicolons.
        $item->sobject->fields[$field_name] = preg_replace("|\\&[^\\s;]*\$|", '', $item->sobject->fields[$field_name]);
      }
    }
  }

  /**
   * Determines if a given Salesforce field type is stored as a string.
   *
   * @param string $field_type
   *   The field type as identified in an sobject describe call.
   *   See http://www.salesforce.com/developer/docs/api/Content/
   *   sforce_api_calls_describesobjects_describesobjectresult.htm#i1427375
   */
  public function typeIsText($field_type) {
    switch ($field_type) {
      case 'string':
      case 'textarea':
      case 'phone':
      case 'picklist':
      case 'url':
      return TRUE;
    }

    return FALSE;
  }

  /**
   * Helper to remove newly created items from Salesforce. Used for simpletests.
   */
  public function deleteNewSfRecords() {
    if (empty($this->newSfRecords)) {
      return;
    }
    $chunks = array_chunk($this->newSfRecords, $this->maxBatchSize);
    $this->newSfRecords = array();
    foreach ($chunks as $items) {
      $ids = array();
      foreach ($items as $key => $item) {
        $items[$key]->operation = 'DELETE';
        $ids[] = $item->sobject->Id;
      }
      $batch = array(
        'operation' => 'DELETE',
        'items' => $items,
        'ids' => $ids,
      );
      $this->sendBatch($batch);
    }
  }

  /**
   * @} salesforce_sync_drupal_to_salesforce
   */


  /**
   * @name salesforce_sync_salesforce_to_drupal Salesforce to Drupal methods
   * @{
   */

  /**
   * Import a bundled batch of instructions from Salesforce.
   *
   * @param array $batch
   *   It is unknown at this time if Drupal batches will be formatted
   *   differently from the Salesforce batches.
   */
  public function importBatch($batch) {
    $this->importBatchPrepare($batch);
    // @TODO
  }

  /**
   * Wrapper for importBatch in order to import a single item from Salesforce.
   *
   * @param object $item
   *   It is unknown at this time if Drupal items will be formatted differently
   *   from the Salesforce items.
   */
  public function importItem($item) {
    $batch = array(
      'items' => array($item),
    );
    // @TODO
    $this->importBatch($batch);
  }

  /**
   * Applies instructions on a batch in order to prepare it to be imported.
   *
   * @param array $batch
   *   It is unknown at this time if Drupal batches will be formatted
   *   differently from the Salesforce batches.
   */
  public function importBatchPrepare($batch) {
    if (isset($batch['batch_prepared']) && $batch['batch_prepared']) {
      // No use continuing if this batch is already prepared.
      return;
    }
    $this->batchConvertToDrupalFormat($batch);
    $this->batchApplyDrupalSyncRules($batch);
    $batch['batch_prepared'] = TRUE;
  }

  /**
   * Applys the sync rules to a batch of items with Drupal as the consumer.
   *
   * @param array $batch
   *   It is unknown at this time if Drupal batches will be formatted
   *   differently from the Salesforce batches.
   */
  public function batchApplyDrupalSyncRules($batch) {
    if (isset($batch['sync_rules_applied']) && $batch['sync_rules_applied']) {
      // Skip because the sync rules have already been applied to this item.
      return;
    }
    else {
      // Declare we're checking this batch.
      $batch['sync_rules_applied'] = TRUE;
    }
    // @TODO
  }

  /**
   * Applies the Drupal format conversion to all items in the batch.
   *
   * @param array $batch
   *   It is unknown at this time if Drupal batches will be formatted
   *   differently from the Salesforce batches.
   */
  public function batchConvertToDrupalFormat($batch) {
    if (isset($batch['converted_to_drupal_format']) && $batch['converted_to_drupal_format']) {
      // Skip because this batch has already had its items formats converted.
      return;
    }

    // @TODO: Convert each item.
    // Mark the batch as converted.
    $batch['converted_to_salesforce_format'] = TRUE;
  }

  /**
   * Convert the mapped values into a format compatible to import into Drupal.
   *
   * @param object $item
   *   It is unknown at this time if Drupal items will be formatted differently
   *   from the Salesforce items.
   */
  public function convertToDrupalFormat($item) {
    if (isset($item->converted_to_drupal_format) && $item->converted_to_drupal_format) {
      // Skip because this item has already had its formats converted.
      return;
    }

    // @TODO: Convert each field.
    // Mark the item as converted.
    $item->converted_to_drupal_format = TRUE;
  }

  /**
   * @} salesforce_sync_salesforce_to_drupal
   */


  /**
   * @name salesforce_sync_results Result processing
   * @{
   */

  /**
   * Marks an item has having succeeded processing.
   *
   * @param object $item
   *   Item to be processed.
   * @param object $result
   *   Result of the item's processing from Salesforce.
   */
  public function passItem($item, $result) {
    $item->sobject->Id = $result->id;

    // Keep a log of newly created items.
    if ($item->operation == 'CREATE' || $item->operation == 'UPSERT') {
      $this->newSfRecords[$result->id] = $item;
    }

    // Keep a log of all items processed.
    if (isset($item->module) && isset($item->delta) && isset($item->drupal_id)) {
      $id_key = $item->module . '-' . $item->delta . '-' . $item->drupal_id;
      $this->processedItemIds[$item->object_type][$id_key] = $result->id;
      // Pass the item to the token scanner's internal cache so it doesn't
      // have to go to the db as often.
      $this->tokenScanner->addItemToTokenCache($item, $result->id);
    }

    // Remove deleted items from the new records since it is not in Salesforce.
    if ($item->operation == 'DELETE' && isset($this->newSfRecords[$result->id])) {
      unset($this->newSfRecords[$result->id]);
    }

    // Invokes hook_salesforce_sync_pass_item().
    module_invoke_all('salesforce_sync_pass_item', $item, $result);
  }

  /**
   * Marks an item has having failed.
   *
   * @param object $item
   *   Item to be processed.
   * @param string $message
   *   Error message.
   * @param object $result
   *   Salesforce result if the item had received a result from salesforce, or
   *   exception caught when call failed.
   */
  public function failItem($item, $message, $result = NULL) {
    // Send an error to admin that the item failed.
    // With many cases of Salesforce being helpful and deleting things for you,
    // there is no need to get too alarmed if an item failed to be deleted.
    $msg_id = $item->operation == 'DELETE' ? 'sync-02' : 'sync-01';
    $severity = $item->operation == 'DELETE' ? WATCHDOG_INFO : WATCHDOG_WARNING;
    watchdog('salesforce', '[@id] Sync failed: @item_id (@message) @result',
      array(
        '@id' => $msg_id,
        '@item_id' => (isset($item->item_id) ? '#' . $item->item_id : 'N/A'),
        '@message' => $message,
        '@result' => is_object($result) && method_exists($result, 'getMessage') ? $result->getMessage() : '',
      ), $severity);

    // Invokes hook_salesforce_sync_fail_item().
    module_invoke_all('salesforce_sync_fail_item', $item, $message, $result);
  }

  /**
   * Wrapper for failItem() so that every item in a batch is failed.
   *
   * @param array $batch
   *   Batch array as set up for processBatch() for execute
   * @param Exception $result
   *   Error caught when the call to Salesforce failed.
   */
  public function failBatch($batch, $message, $result = NULL) {
    // Send an error to admin that the batch failed.
    watchdog('salesforce', '[@id] Batch failed: (@message) @result',
      array(
        '@id' => 'sync-03',
        '@message' => $message,
        '@result' => is_object($result) && method_exists($result, 'getMessage') ? $result->getMessage() : '',
      ), WATCHDOG_ERROR);

    // Fail each item.
    foreach ($batch['items'] as $item) {
      $this->failItem($item, $message, $result);
    }

    // Invokes hook_salesforce_sync_fail_batch().
    module_invoke_all('salesforce_sync_fail_batch', $batch, $message, $result);
  }

  /**
   * @} salesforce_sync_results
   */


  /**
   * @name salesforce_sync_fetch Helpers to fetch records from Salesforce
   * @{
   */

  /**
   * Helper method to fetch records from Salesforce based upon provided Ids.
   *
   * @param string $object_type
   *   The type of object of the desired records, such as 'Account' or 'User'.
   * @param array $fields
   *   Array of field names of the records to return.
   * @param array $ids
   *   Array of Salesforce Ids of the desired records.
   *
   * @return mixed
   *   If records are found, an array of Salesforce objects for reach found
   *   record is returned.  Otherwise, receive FALSE.
   */
  public function fetchByIds($object_type, $fields, $ids) {
    if (empty($ids) || empty($ids)) {
      // If there are no Ids to fetch, there is no point wasting an API call.
      return array();
    }

    // Salesforce expects a comma deliminated string of fields.
    $fields = implode(', ', $fields);

    // Ids need to be an unassociated array or Salesforce will reject it.
    $ids = array_values($ids);

    // Salesforce's maximum is 2000 records, or else it will give you nothing.
    // Chunk up the provided ids to make sure no single call exceeds 2000.
    $responses = array();
    $id_chunks = array_chunk($ids, $this->maxRetrieveSize);
    foreach ($id_chunks as $id_chunk) {
      try {
        $response = $this->soap->retrieve($fields, $object_type, $id_chunk);
        if (is_array($response)) {
          $responses = array_merge($responses, $response);
        }
        else {
          // Log message for later investigation.
          watchdog('salesforce', "[@id] Fetch records by Id returned bad results for @object.\nResponse:\n@response \nFields:\n@fields \nIds:\n@ids",
            array(
              '@id' => 'sync-05',
              '@object' => $object_type,
              '@response' => print_r($response, TRUE),
              '@fields' => print_r($fields, TRUE),
              '@ids' => print_r($ids, TRUE),
            ), WATCHDOG_NOTICE);
        }
      }
      catch (Exception $error) {
        // Log message for later investigation.
        watchdog('salesforce', "[@id] Fetch records by Id failed for @object: @message\nFields:\n@fields \nIds:\n@ids",
          array(
            '@id' => 'sync-04',
            '@object' => $object_type,
            '@message' => $error->getMessage(),
            '@fields' => print_r($fields, TRUE),
            '@ids' => print_r($ids, TRUE),
          ), WATCHDOG_DEBUG);
      }
    }

    return $responses;
  }

  /**
   * Helper method to fetch records from Salesforce based on values of a field.
   *
   * @param string $object_type
   *   The type of object of the desired records, such as 'Account' or 'User'.
   * @param array $fields
   *   Array of field names of the records to return.
   * @param string $key_field
   *   Field name of the field to query on.
   * @param array $key_field_values
   *   Array of values of the $key_field the searched for records can have.
   *
   * @return array
   *   Array of Salesforce objects for reach found record.
   */
  public function fetchByField($object_type, $fields, $key_field, $key_field_values) {
    $conditions = array(
      array(
        'field' => $key_field,
        'op' => 'IN',
        'value' => $key_field_values,
      ),
    );
    return $this->fetchRecords($object_type, $fields, $conditions);
  }

  /**
   * Helper to fetch records from Salesforce based on custom conditions.
   *
   * This of course will have its limitations and can handle only simple
   * queries, but the hope is it will save time in more routine instances.  All
   * conditions are joined by AND.
   *
   * @param string $object_type
   *   The type of object of the desired records, such as 'Account' or 'User'.
   * @param array $fields
   *   Array of field names of the records to return.
   * @param array $conditions
   *   Array of SQL conditions.  Each value can be a string of a complete
   *   statement, or can be an array with 'field', 'op' and 'value' keys.  The
   *   'value' key may also be an array which will be automatically converted
   *   into a string.  Example:
   *   <code>
   *     $conditions = array(
   *       array(
   *         'field' => 'email',
   *         'op' => 'IN',
   *         'value' => array(
   *           'john.doe@example.com',
   *           'jane.doe@example.com',
   *         ),
   *       ),
   *       'CreatedDate > 2012-01-01 00:00:00',
   *     );
   *   </code>
   */
  public function fetchRecords($object_type, array $fields, array $conditions = array()) {
    if (!is_object($this->soap)) {
      watchdog('salesforce_sync', 'Unable to connect to Salesforce', array(), WATCHDOG_ERROR);
      return FALSE;
    }
    $queries = $this->buildQueries($object_type, $conditions);

    // List of error messages that should cease all querying from continuing.
    $restricted_errors = array(
      'REQUEST_LIMIT_EXCEEDED',
      'bytes exhausted',
    );

    // Partner API requests are formatted incorrectly, so we are reciving the Id
    // as an array, and the fields are not retreived in a structured format.
    // Because of this, we are grabbing only the Ids from this query, then
    // passing them on to fetchByIds to complete the request.  Once the bug is
    // fixed, remove this work around and retreive the records directly from
    // this query.
    // @see http://goo.gl/Xv8k7
    $ids = array();
    $continue_queries = TRUE;
    foreach ($queries as $query) {
      // Only query when we are allowed to query.
      if (!$continue_queries) {
        continue;
      }

      // Log the query being run.
      watchdog('salesforce', 'Running SOQL query [@query].',
        array(
          '@query' => $query,
        ), WATCHDOG_DEBUG);

      try {
        $response = $this->soap->query($query);
        if ($response->size > 0) {
          $more = TRUE;
          while ($more) {
            foreach ($response->records as $record) {
              $ids[] = $record->Id[0];
            }

            // Salesforce will only return a maximum number of records at a
            // time, which we are automatically restricting to be
            // SALESFORCE_SYNC_MAX_BATCH_SIZE.  We'll use queryMore() to
            // continue to pull down more records until we retreive all of them.
            if (empty($response->done)) {
              try {
                $response = $this->soap->queryMore($response->queryLocator);
              }
              catch (Exception $error) {
                // Stop this query from continuing when an error has been
                // reached.
                $more = FALSE;

                // Log message for later investigation.
                watchdog('salesforce', "[@id] Salesforce queryMore failed: @message\nQuery: @query",
                  array(
                    '@id' => 'sync-07',
                    '@message' => $error->getMessage(),
                    '@query' => $query,
                  ), WATCHDOG_DEBUG);

                // Do not continue querying whatsoever if any of one of the
                // restricted errors has been encountered.
                foreach ($restricted_errors as $restricted_error) {
                  if (strpos($error->getMessage(), $restricted_error) !== FALSE) {
                    $continue_queries = FALSE;
                  }
                }
              }
            }
            else {
              $more = FALSE;
            }
          }
        }
      }
      catch (Exception $error) {
        // Log message for later investigation.
        watchdog('salesforce', "[@id] Salesforce query failed: @message\nQuery: @query",
          array(
            '@id' => 'sync-06',
            '@message' => $error->getMessage(),
            '@query' => $query,
          ), WATCHDOG_DEBUG);

        // Do not continue querying whatsoever if any of one of the restricted
        // errors has been encountered.
        foreach ($restricted_errors as $restricted_error) {
          if (strpos($error->getMessage(), $restricted_error) !== FALSE) {
            $continue_queries = FALSE;
          }
        }
      }
    }

    return $this->fetchByIds($object_type, $fields, $ids);
  }

  /**
   * Helper to build a Salesforce query that will not exceed 10,000 characters.
   *
   * This of course will have its limitations and can handle only simple
   * queries, but the hope is it will save time in more routine instances.  All
   * conditions are joined by AND.
   *
   * @param string $object_type
   *   The type of object of the desired records, such as 'Account' or 'User'.
   * @param array $conditions
   *   Array of SQL conditions.  Each value can be a string of a complete
   *   statement, or can be an array with 'field', 'op' and 'value' keys.  The
   *   'value' key may also be an array which will be automatically converted
   *   into a string.  Example:
   *   <code>
   *     $conditions = array(
   *       array(
   *         'field' => 'email',
   *         'op' => 'IN',
   *         'value' => array(
   *           'john.doe@example.com',
   *           'jane.doe@example.com',
   *         ),
   *       ),
   *       'CreatedDate > 2012-01-01 00:00:00',
   *     );
   *   </code>
   * @param int $query_splits
   *   The number of times the query should be split up.  This is done in an
   *   attempt to lower its character count so it does not exceed 10,000
   *   characters.  You would not need to set this value yourself, let the
   *   function set it automatically.
   */
  protected function buildQueries($object_type, array $conditions, $query_splits = 0) {
    $queries = array();
    $query_count = $query_splits;

    // Build the first part of the query.  We will be stubbing out the same
    // number of queries as $query_splits there are (counting base 0).
    $select_sql = 'SELECT Id FROM ' . $object_type;
    $i = $query_count;
    while ($i >= 0) {
      $queries[$i] = $select_sql;
      $i--;
    }

    // Build the WHERE part of the query.
    // Automatically fail if conditions is empty.  We disallow selects without a
    // WHERE condition so every row is not selected.
    $fail = empty($conditions);
    foreach ($conditions as $key => $condition) {
      if (empty($condition)) {
        // Fail out if an empty condition is provided.
        $fail = TRUE;
        watchdog('salesforce', "[@id] Empty query condition provided for key @key\nProvided conditions:\n@conditions ",
          array(
            '@id' => 'sync-12',
            '@key' => $key,
            '@conditions' => print_r($conditions, TRUE),
          ), WATCHDOG_ALERT);
      }

      // Handle cases where the condition is provided to us as a 'field', 'op',
      // 'value' array.
      elseif (is_array($condition) && isset($condition['op']) && isset($condition['field']) && isset($condition['value'])) {
        if (empty($condition['op']) || empty($condition['field']) || empty($condition['value'])) {
          // Fail out if any of options are empty.
          $fail = TRUE;
          watchdog('salesforce', "[@id] Empty query condition provided\nProvided condition:\n@condition",
            array(
              '@id' => 'sync-12',
              '@condition' => print_r($condition, TRUE),
            ), WATCHDOG_ALERT);
        }
        else {
          $op = $condition['op'];
          $field = $condition['field'];
          // The value can be provided as an array and we'll convert it to a
          // string automatically.
          if ($query_splits == 0 || is_string($condition['value'])) {
            if (is_array($condition['value'])) {
              $value = " ('" . implode("', '", $condition['value']) . "')";
            }
            else {
              $value = $condition['value'];
            }

            // Append the condition to each query.
            $i = $query_count;
            while ($i >= 0) {
              $queries[$i] .= ($key == 0 ? ' WHERE' : ' AND');
              $queries[$i] .= ' ' . $field . ' ' . $op . ' ' . $value;
              $i--;
            }
          }
          // If the query needs to be split up, this is where it is done.  We
          // will divide the values of the array into the number of splits
          // requested.
          elseif ($query_splits > 0 && is_array($condition['value'])) {
            $chunk_size = count($condition['value']) / ($query_splits + 1);
            $value_chunks = array_chunk($condition['value'], $chunk_size);
            $new_queries = array();
            foreach ($value_chunks as $value_chunk) {
              $value = " ('" . implode("', '", $value_chunk) . "')";
              $operation = $field . ' ' . $op . ' ' . $value;
              foreach ($queries as $i => $query) {
                $new_queries[] = $query . ($key == 0 ? ' WHERE' : ' AND') . ' ' . $operation;
              }
            }
            $query_count = count($new_queries);
            $queries = $new_queries;
          }
        }
      }

      // Plain old strings can be passed straight on through to the query.
      elseif (is_string($condition)) {
        $i = $query_count;
        while ($i >= 0) {
          $queries[$i] .= ($key == 0 ? ' WHERE' : ' AND');
          $queries[$i] .= ' ' . $condition;
          $i--;
        }
      }

      // WTF why did you pass something else? No, I can't handle it.
      else {
        $fail = TRUE;
      }
    }

    if (strlen($queries[0]) > $this->maxQueryLength) {
      // 3 tries is enough.  After that, give up.
      if ($query_splits < 2) {
        $query_splits++;
        return $this->buildQueries($object_type, $conditions, $query_splits);
      }

      // This query is hopeless, forget about it.
      $fail = TRUE;
      watchdog('salesforce', "[@id] Query to Salesforce exceeded limit of @char_limit characters.\nConditions provided:\n@conditions",
        array(
          '@id' => 'sync-08',
          '@char_limit' => $this->maxQueryLength,
          '@conditions' => print_r($conditions, TRUE),
        ), WATCHDOG_ALERT);
    }

    // If there was a failure at any point, blank out the query so no query is
    // performed. Not providing any queries will prevent any from being
    // executed because the intended behavior is to loop through the queries
    // returned from this method.
    if ($fail) {
      $queries = array();
    }

    // Add the limit to the end of each query.
    foreach ($queries as $key => $query) {
      $queries[$key] .= ' LIMIT ' . $this->queryLimit;
    }

    return $queries;
  }

  /**
   * @}
   */


  /**
   * Helper to get all records created by this SalesforceSync.
   *
   * Implemented to mimic version in SalesforceQueueProcessor.
   *
   * @return array
   *   Records that have been created.
   */
  public function getNewSfRecords() {
    return $this->newSfRecords;
  }

  /**
   * Helper to get all item Ids processed by this SalesforceSync.
   *
   * Implemented to mimic version in SalesforceQueueProcessor.
   *
   * @return array
   *   Ids of items that have been processed keyed by their unique identifier.
   */
  public function getProcessedItemIds() {
    return $this->processedItemIds;
  }

  /**
   * Helper to externally set the Salesforce API. Used for simpletests.
   */
  public function setSalesforceApi(Salesforce $sfapi = NULL) {
    // Reload the api if the current one isn't authorized. This extra check is
    // for simpletests and drush.
    $sfapi = (!is_object($sfapi) || !$sfapi->isAuthorized()) ? salesforce_get_api() : $sfapi;
    if (!$sfapi->isAuthorized()) {
      watchdog('salesforce', '[@id] SalesforceAPI is not authorized',
        array(
          '@id' => 'sync-10',
        ), WATCHDOG_NOTICE);
      $sfapi = NULL;
    }
    $this->sfapi = $sfapi;
    return $sfapi;
  }

  /**
   * Helper to externally set the Salesforce SOAP Partner. Used for simpletests.
   */
  public function setSalesforceSoap(SalesforceSoapPartner $soap = NULL) {
    // Create a SalesforceSoapPartner if we weren't provided one.
    if (!is_object($soap)) {
      // Create SalesforceApi if it hasn't be created yet.
      if (!is_object($this->sfapi)) {
        $this->setSalesforceApi();
      }
      // Do not create soap if we cannot get sfapi functioning.
      if (is_object($this->sfapi)) {
        $soap = new SalesforceSoapPartner($this->sfapi);
      }
      else {
        $soap = NULL;
        $message = 'SalesforceAPI is not authorized.';
      }
    }

    // If a SalesforceSoapPartner has been created, test the connection.
    if (is_object($soap)) {
      try {
        $soap->getUserInfo();
      }
      catch (Exception $e) {
        $soap = NULL;
        $message = '(' . $e->faultcode . ') ' . $e->getMessage();
      }
    }

    // Set soap options.
    if (is_object($soap)) {
      // Queries return same number as batch sizes.
      $sync_options = new QueryOptions($this->maxBatchSize);
      $soap->setQueryOptions($sync_options);
    }

    // Send a fail message.
    else {
      watchdog('salesforce', '[@id] SalesforceSoapPartner cannot be used: @message',
        array(
          '@id' => 'sync-11',
          '@message' => $message,
        ), WATCHDOG_NOTICE);
    }

    $this->soap = $soap;
    return $soap;
  }

  /**
   * Helper to determine if a date is unix timestamp.
   *
   * @param int $date
   *   The date to examine.
   */
  protected function isValidTimestamp($date) {
    for ($i = 0; $i < 5; $i++) {
      if (!is_numeric(substr($date, $i, 1))) {
        return FALSE;
      }
    }

    return TRUE;
  }
}
