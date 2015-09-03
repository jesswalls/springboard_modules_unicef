<?php

/**
 * @file
 * Extends salesforce_mapping functionality.
 */

/**
 * Implements hook_salesforce_genmap_permission().
 */
function salesforce_mapping_salesforce_genmap_permission() {
  $permissions = array();
  if (variable_get('salesforce_genmap_allow_delete_sync', FALSE)) {
    $permissions['configure salesforce_mapping delete sync'] = array(
      'title' => t('Configure a !module map to sync deleted records',
        array('!module' => 'salesforce_mapping')),
      'description' => t('Allow the configuration for a map to automatically delete its associated record from Salesforce when it is deleted from Drupal.'),
    );
  }
  return $permissions;
}

/**
 * @name salesforce_mapping_alter_form Modifications to the mapping form
 * @{
 */

/**
 * Implements hook_form_FORM_ID_alter().
 */
function salesforce_mapping_form_salesforce_mapping_form_alter(&$form, &$form_state) {
  // Change the mapping table.  The whole table needs to be rebuilt from scratch
  // or else reminents from the prior form will stick around.
  if (isset($form['salesforce_field_mappings_wrapper']['salesforce_field_mappings'])) {
    $form['salesforce_field_mappings_wrapper']['salesforce_field_mappings'] = array(
      '#theme' => 'salesforce_fieldmap_form_table',
      '#tree' => TRUE,
      '#header' => array(
        'drupal_field' => t('Drupal field'),
        'salesforce_field' => t('Salesforce field'),
        // Column 'key' renamed to 'Dedupe'.
        'key' => t('Dedupe'),
        // Add columns for field-by-field sync rules.
        'drupal_sf' => t('Overwrite rule when exporting to Salesforce'),
        'sf_drupal' => t('Overwrite rule when importing into Drupal'),
        // Column 'direction' removed.
        // Column 'delete_field_maping' removed.
      ),
      '#attributes' => array(
        'id' => array('edit-salesforce-field-mappings'),
      ),
    );

    $salesforce_object_type = _salesforce_mapping_alter_get_default_value('salesforce_object_type', $form_state);
    $entity_type = _salesforce_mapping_alter_get_default_value('drupal_entity_type', $form_state);
    $entity_bundle_type = _salesforce_mapping_alter_get_default_value('drupal_bundle', $form_state);
    $entity_fields = _salesforce_mapping_get_entity_fields($entity_type, $entity_bundle_type);
    $sf_fields = _salesforce_mapping_get_salesforce_field_options($salesforce_object_type, $form_state);
    asort($sf_fields);
    $dedupe_isset = FALSE;
    foreach ($entity_fields as $drupal_field_name => $drupal_field_label) {
      $delta = $drupal_field_name;
      $sanitized_delta = str_replace(':', '-', $delta);

      // Same as original.
      $row_id = 'edit-salesforce-field-mappings-' . $sanitized_delta;
      $form['salesforce_field_mappings_wrapper']['salesforce_field_mappings'][$delta] = array(
        '#type' => 'container',
        '#attributes' => array(
          'id' => array($row_id),
        ),
      );
      $row = &$form['salesforce_field_mappings_wrapper']['salesforce_field_mappings'][$delta];

      // Same as original.
      $row['drupal_field'] = array(
        '#type' => 'container',
        '#attributes' => array(
          'id' => array('edit-drupal-field-' . $sanitized_delta),
        ),
      );

      // We don't need the Drupal field type choices, so set it to properties
      // and hide the select field.
      $row['drupal_field']['fieldmap_type'] = array(
        '#type' => 'hidden',
        '#value' => 'property',
      );

      // We want all of the drupal fields to be listed on the form automatically
      // instead of adding each one manually.  Print Drupal field's user
      // friendly name as a label and set the fieldmap_value to it's machine
      // name.  If a field has multiple attributes, then $drupal_field_label
      // will be an array and $drupal_field_name will be a user-friendly name of
      // the entire field set.
      $drupal_field_label = is_array($drupal_field_label) ? $drupal_field_name : $drupal_field_label;
      $row['drupal_field']['fieldmap_label'] = array(
        '#markup' => '<label>' . $drupal_field_label . '</label>',
      );
      $row['drupal_field']['fieldmap_value'] = array(
        '#type' => 'hidden',
        '#value' => $drupal_field_name,
      );

      // This is the same as the original but simplified since it is referencing
      // solely the property Drupal fieldmap type.
      $salesforce_field = _salesforce_mapping_alter_get_default_value('salesforce_field', $form_state, $delta);
      $row['salesforce_field'] = array(
        '#id' => 'edit-salesforce-field-' . $sanitized_delta,
        '#type' => 'select',
        '#description' => t('Select a Salesforce field to map.'),
        '#options' => $sf_fields,
        '#default_value' => $salesforce_field,
        '#ajax' => array(
          'wrapper' => $row_id,
          'callback' => 'salesforce_mapping_form_field_callback',
        ),
      );

      // Same as original.
      if (_salesforce_mapping_salesforce_field_can_idlookup($salesforce_field, $salesforce_object_type, $form_state)) {
        $key_default_value = _salesforce_mapping_alter_get_default_value('key', $form_state, $delta);
        if ($key_default_value) {
          $dedupe_isset = TRUE;
        }
        $row['key'] = array(
          '#id' => 'edit-key-' . $sanitized_delta,
          '#type' => 'radio',
          '#name' => 'key',
          '#return_value' => $delta,
          '#tree' => FALSE,
          '#default_value' => $key_default_value,
        );
      }
      else {
        $row['key'] = array(
          '#type' => 'hidden',
          '#value' => FALSE,
        );
      }

      // Add field-by-field sync rule columns.
      $row['drupal_sf'] = array('#id' => 'edit-drupal-sf-' . $sanitized_delta);
      $row['sf_drupal'] = array('#id' => 'edit-sf-drupal-' . $sanitized_delta);
      if (empty($salesforce_field)) {
        $row['drupal_sf'] += array(
          '#markup' => '<label class="description">' . t('Select Salesforce field.') . '</label>',
          '#attributes' => array(
            'class' => array('form-item form-disabled'),
          ),
        );
      }
      else {
        $row['drupal_sf'] += $row['sf_drupal'] += array(
          '#type' => 'radios',
        );
        $drupal_sf_value = _salesforce_mapping_alter_get_default_value('drupal_sf', $form_state, $delta);
        $sf_drupal_value = _salesforce_mapping_alter_get_default_value('sf_drupal', $form_state, $delta);
        $row['drupal_sf']['#options'] = _salesforce_mapping_get_sync_rule_options($entity_type, $drupal_field_name, $salesforce_object_type, $salesforce_field, 'drupal_sf', $form_state);
        $row['sf_drupal']['#options'] = _salesforce_mapping_get_sync_rule_options($entity_type, $drupal_field_name, $salesforce_object_type, $salesforce_field, 'sf_drupal', $form_state);
        // Must verify the default value is in the options before setting it or
        // receive a illegal action error.
        if (array_key_exists($drupal_sf_value, $row['drupal_sf']['#options'])) {
          $row['drupal_sf']['#default_value'] = $drupal_sf_value;
        }
        if (array_key_exists($sf_drupal_value, $row['sf_drupal']['#options'])) {
          $row['sf_drupal']['#default_value'] = $sf_drupal_value;
        }
      }
    }

    // Add a "none" option for the dedupe field and some help text.
    $dedupe_help = array(
      '#type' => 'container',
      '#attributes' => array(
        'id' => array('salesforce-mapping-dedupe-helptext'),
      ),
      // Using the first column to produce a buffer.
      'drupal_field' => array(
        '#type' => 'container',
        '#attributes' => array(
          'class' => array('empty-cell'),
          'colspan' => 2,
        ),
      ),
      'key' => array(
        '#id' => 'edit-key-none',
        '#title' => t('None'),
        '#type' => 'radio',
        '#name' => 'key',
        '#return_value' => 'none',
        '#tree' => FALSE,
        '#default_value' => $dedupe_isset ? FALSE : TRUE,
        '#attributes' => array(
          'valign' => 'top',
        ),
      ),
      // Using subsequent columns to contain the help text.
      'sf_drupal' => array(
        '#markup' => '<p>' . t('<strong>Dedupe:</strong> Selecting a Salesforce
          field as a "dedupe field" minimizes duplicate records and allows
          updating existing records <em>when new records are being created</em>.
          Selecting a dedupe field chooses which field will be used as the
          unique identifier for matching potential existing records.  A dedupe
          option only appears next to a Salesforce field that can be used as a
          unique identifier. Select "None" to not use this feature.') . '</p>',
        '#attributes' => array(
          'colspan' => 3,
        ),
      ),
    );
    $form['salesforce_field_mappings_wrapper']['salesforce_field_mappings']['none'] = $dedupe_help;

    // Since we are listing all Drupal fields, we do not need add field button.
    unset($form['salesforce_field_mappings_wrapper']['salesforce_add_field']);
  }

  // Add the option to configure a map to delete on sync only if this site is
  // configured to allow this configuration setting and the user has access.
  if (!variable_get('salesforce_genmap_allow_delete_sync', FALSE) || !user_access('configure salesforce_mapping delete sync')) {
    unset($form['sync_triggers']['#options'][SALESFORCE_MAPPING_SYNC_DRUPAL_DELETE]);
    unset($form['sync_triggers']['#options'][SALESFORCE_MAPPING_SYNC_SF_DELETE]);
    foreach ($form['sync_triggers']['#default_value'] as $key => $value) {
      if (in_array($value, array(SALESFORCE_MAPPING_SYNC_DRUPAL_DELETE, SALESFORCE_MAPPING_SYNC_SF_DELETE))) {
        unset($form['sync_triggers']['#default_value'][$key]);
      }
    }
  }

  // We do not use these options, so hide them.
  $form['push_async']['#access'] = FALSE;
  $form['push_batch']['#access'] = FALSE;

  // The need to manipulate the form causes a need to manipulate the storage
  // of data. Appending a "prevalidate" callback to shift around all of the data
  // so the original validation callback will function properly.
  array_unshift($form['#validate'], 'salesforce_mapping_form_prevalidate');

  // And add our own normal validate hook.
  // Making it separate from prevalidate so the difference in tasks is clear.
  $form['#validate'][] = 'salesforce_mapping_form_alter_validate';

  // Same as with the need for a "prevalidate" callback, calling another submit
  // callback to add back in the additional data we need that the original
  // submit callback is filtering out.
  $form['#submit'][] = 'salesforce_mapping_form_alter_submit';
}

/**
 * Prevalidation callback for the altered mapping form.
 */
function salesforce_mapping_form_prevalidate($form, &$form_state) {
  // Add the DELETE sync option values back in.
  if (!variable_get('salesforce_genmap_allow_delete_sync', FALSE)) {
    // Automatically set it FALSE.
    $form_state['values']['sync_triggers'][SALESFORCE_MAPPING_SYNC_DRUPAL_DELETE] = FALSE;
    $form_state['values']['sync_triggers'][SALESFORCE_MAPPING_SYNC_SF_DELETE] = FALSE;
  }
  elseif (!user_access('configure salesforce_mapping delete sync')) {
    // Set the value to the original configuration's value.
    $form_state['values']['sync_triggers'][SALESFORCE_MAPPING_SYNC_DRUPAL_DELETE] = ($form['salesforce_mapping']->sync_trigger[SALESFORCE_MAPPING_SYNC_DRUPAL_DELETE] & SALESFORCE_MAPPING_SYNC_DRUPAL_DELETE);
    $form_state['values']['sync_triggers'][SALESFORCE_MAPPING_SYNC_SF_DELETE] = ($form['salesforce_mapping']->sync_trigger[SALESFORCE_MAPPING_SYNC_SF_DELETE] & SALESFORCE_MAPPING_SYNC_SF_DELETE);
  }

  // Update the field maps.
  $field_maps = &$form_state['values']['salesforce_field_mappings'];
  if (!is_array($field_maps)) {
    return;
  }
  $key = _salesforce_mapping_alter_get_default_value('key', $form_state);
  foreach ($field_maps as $delta => $field_map) {
    // Two rows need to be created for every one row submitted.  The one that is
    // shown to the user is the "Drupal to Salesforce" configuration, and the
    // "ghost" configuration we're simultating here is the "Salesforce to
    // Drupal" configuration.
    if (is_string($delta)) {
      // If the direction is set to never sync, do not set the row so it doesn't
      // go through and subsequently fail validation.
      $set_key = ($key == $delta);
      foreach (array('drupal_sf', 'sf_drupal') as $direction) {
        if (isset($field_map[$direction]) && $field_map[$direction] != SALESFORCE_SYNC_RULE_NEVER) {
          $field_map['key'] = FALSE;
          $field_map['direction'] = $direction;
          $field_maps[] = $field_map;

          // The salesforce_mapping module expects 'key' to be the row number of
          // the given item.  Since we 1) have rows labeled as Drupal field and
          // 2) are adding ghost rows, the 'key' value will need to be manually
          // calculated. Only one direction should set this value.  If the first
          // direction doesn't set it, then the next direction will.
          if ($set_key) {
            end($field_maps);
            $position = key($field_maps);
            $field_maps[$position]['key'] = TRUE;
            $form_state['values']['key'] = $position;
            $set_key = FALSE;
          }
        }
      }
      unset($field_maps[$delta]);
    }
  }
  if (!is_int($form_state['values']['key'])) {
    $form_state['values']['key'] = FALSE;
  }
}

/**
 * Validate callback for salesforce_mapping_form().
 */
function salesforce_mapping_form_alter_validate($form, &$form_state) {
  // Prevent the user from mistakenly bypassing the restriction for configuring
  // delete on sync.
  $sync_options = $form_state['values']['sync_triggers'];
  $error_text = t('You do not have permission to configure a !module map to sync on delete.', array('!module' => 'salesforce_mapping'));
  if ((in_array(SALESFORCE_MAPPING_SYNC_DRUPAL_DELETE, $sync_options) || in_array(SALESFORCE_MAPPING_SYNC_SF_DELETE, $sync_options)) && !user_access('configure salesforce_mapping delete sync')) {
    // Remove the values from form state to minimize possible user frustration.
    foreach ($sync_options as $key => $value) {
      if (in_array($value, array(SALESFORCE_MAPPING_SYNC_DRUPAL_DELETE, SALESFORCE_MAPPING_SYNC_SF_DELETE))) {
        unset($form_state['values']['sync_triggers'][$key]);
        form_set_error('sync_triggers][' . $value, $error_text);
      }
    }
  }

  // No Salesforce field can be used twice.
  $error_text = t('Multiple Drupal fields cannot be mapped to the same Salesforce fields.');
  $sf_fields = array();
  if (isset($form_state['values']['salesforce_field_mappings']) && is_array($form_state['values']['salesforce_field_mappings'])) {
    foreach ($form_state['values']['salesforce_field_mappings'] as $key => $values) {
      $sf_field = $values['salesforce_field'];
      if (!empty($sf_field)) {
        $drupal_field = $values['drupal_field']['fieldmap_value'];
        $sf_fields[$sf_field][$drupal_field] = $drupal_field;
      }
    }
  }
  foreach ($sf_fields as $sf_field => $drupal_fields) {
    $count = count($drupal_fields);
    $drupal_fields_text = '"' . implode('", "', $drupal_fields) . '"';
    if ($count > 1) {
      if ($count > 2) {
        $error_text = t('The Drupal fields, !drupal_fields, cannot all be mapped to the "!sf_field" Salesforce field.',
          array('!drupal_fields' => $drupal_fields_text, '!sf_field' => $sf_field));
      }
      else {
        $error_text = t('The Drupal fields, !drupal_fields, cannot both be mapped to the "!sf_field" Salesforce field.',
          array('!drupal_fields' => $drupal_fields_text, '!sf_field' => $sf_field));
      }
      $i = 1;
      foreach ($drupal_fields as $drupal_field) {
        $message = $i === 1 ? $error_text : '';
        form_set_error('salesforce_field_mappings][' . $drupal_field . '][salesforce_field', $message);
        $i++;
      }
    }
  }
}

/**
 * Submit callback to handle extra data from the altered mapping form.
 */
function salesforce_mapping_form_alter_submit($form, &$form_state) {
  // The original callback, salesforce_mapping_form_submit(), saved the entity
  // and removed our additional data in the process so we'll have to reload it
  // and save it again adding in our new values.
  $machine_name = _salesforce_mapping_alter_get_default_value('name', $form_state);
  $mapping = salesforce_mapping_load($machine_name);
  $key = _salesforce_mapping_alter_get_default_value('key', $form_state);
  foreach ($mapping->field_mappings as $delta => $field_map) {
    $mapping->field_mappings[$delta]['key'] = ($key == $field_map['drupal_field']['fieldmap_value']);
    $mapping->field_mappings[$delta]['drupal_sf'] = _salesforce_mapping_alter_get_default_value('drupal_sf', $form_state, $field_map['drupal_field']['fieldmap_value']);
    $mapping->field_mappings[$delta]['sf_drupal'] = _salesforce_mapping_alter_get_default_value('sf_drupal', $form_state, $field_map['drupal_field']['fieldmap_value']);
  }
  $mapping->save();

  // Clear the cache so all newly created and modified entities will
  // automatically get the new settings.
  entity_get_controller('salesforce_mapping')->resetCache();
}

/**
 * @} salesforce_mapping_alter_form
 */

/**
 * @name salesforce_queue_hooks
 * @{
 */

/**
 * Implements hook_salesforce_queue_refresh_queue_item().
 */
function salesforce_genmap_salesforce_queue_refresh_queue_item($item) {
  // Grab the map for this particular module/delta combination.
  $mappings = salesforce_mapping_load_multiple(array(
    'drupal_entity_type' => $item->module,
    'drupal_bundle' => $item->delta,
  ));

  // If we have any mappings then this item is handled by entity interation.
  if (!empty($mappings)) {
    $item_entity = entity_load($item->module, array($item->drupal_id));
    // salesforce_mapping_send_entity_to_queue doesn't always return a value
    // so we'll assume it actually worked.
    salesforce_mapping_send_entity_to_queue($item_entity[$item->drupal_id], $item->module, $item->operation);
    return TRUE;
  }
}

/**
 * @} salesforce_queue_hooks
 */

/**
 * @name salesforce_mapping_alter_queue Sending entity mapping to Queue
 * @{
 */

/**
 * Implements hook_entity_insert().
 */
function salesforce_genmap_entity_insert($entity, $entity_type) {
  salesforce_mapping_send_entity_to_queue($entity, $entity_type, 'CREATE');
}

/**
 * Implements hook_entity_update().
 */
function salesforce_genmap_entity_update($entity, $entity_type) {
  // Updating the mapping entity will require having all of the queue items
  // regenerated so the new mapping configuration can be applied to them.
  if ($entity_type == 'salesforce_mapping') {
    $result = db_select('salesforce_queue', 'q')
      ->fields('q')
      ->condition('module', $entity->drupal_entity_type)
      ->condition('delta', $entity->drupal_bundle)
      ->condition('object_type', $entity->salesforce_object_type)
      ->execute();
    foreach ($result as $item) {
      // Get the original entity and requeue it.
      $item_entity = entity_load($item->module, array($item->drupal_id));
      $op = ($item->operation == 'UPSERT') ? 'UPDATE' : $item->operation;
      salesforce_mapping_send_entity_to_queue($item_entity[$item->drupal_id], $item->module, $op);
    }
  }
  else {
    salesforce_mapping_send_entity_to_queue($entity, $entity_type, 'UPDATE');
  }
}

/**
 * Implements hook_entity_delete().
 */
function salesforce_genmap_entity_delete($entity, $entity_type) {
  // Dequeue anything previous this entity may have sent to the queue.
  salesforce_mapping_dequeue_entity($entity, $entity_type);

  // If the entity needs to queue up its delete state, then queue its delete.
  salesforce_mapping_send_entity_to_queue($entity, $entity_type, 'DELETE');
}

/**
 * Send a given entity to a queue for a given operation.
 *
 * @param object $entity
 *   Entity to queue.
 * @param string $entity_type
 *   Type of entity being queued.
 * @param string $op
 *   Salesforce operation to be performed.
 *
 * @return bool
 *   TRUE if the item was successfully queued.  FALSE if the item could not be
 *   queued, or if the item was not supposed to be queued.
 */
function salesforce_mapping_send_entity_to_queue($entity, $entity_type, $op) {
  $sfapi = salesforce_get_api();
  if (!$sfapi->isAuthorized()) {
    // If there isn't a valid connection to Salesforce, lets not start queueing
    // items.
    return FALSE;
  }

  if (!variable_get('salesforce_genmap_allow_delete_sync', FALSE) && $op == 'DELETE') {
    // Do not queue DELETE if site has disallowed delete trigger.  This is a
    // failsafe in case someone had bypassed the configuration form's validation
    // (such as manually constructing the configuration).  The goal is not to
    // prevent any sort of deletion of records but rather to prevent the
    // deletion of records on a triggered event.
    return FALSE;
  }

  // Allow modules to control whether this entity is queued
  foreach (module_implements('salesforce_mapping_confirm_entity_for_queue') as $module) {
    $function = $module . '_salesforce_mapping_confirm_entity_for_queue';
    if ($function($entity, $entity_type, $op) === FALSE) {
      return FALSE;
    }
  }

  // Information specific to this entity.
  list($entity_id, , $bundle) = entity_extract_ids($entity_type, $entity);

  // Associate Salesforce operations with sync triggers.
  $op_sync = array(
    'CREATE' => SALESFORCE_MAPPING_SYNC_DRUPAL_CREATE,
    'UPDATE' => SALESFORCE_MAPPING_SYNC_DRUPAL_UPDATE,
    'DELETE' => SALESFORCE_MAPPING_SYNC_DRUPAL_DELETE,
  );

  // Grab the map for this particular entity.
  $mappings = salesforce_mapping_load_multiple(array(
    'drupal_entity_type' => $entity_type,
    'drupal_bundle' => $bundle,
  ));

  $map = NULL;
  $queue_item = FALSE;
  if (is_array($mappings)) {
    foreach ($mappings as $mapping) {
      // Check if this operation is configured to trigger a sync to Salesforce.
      if ($mapping->sync_triggers & $op_sync[$op]) {
        $queue_item = TRUE;
        $map = $mapping;
      }
    }
  }

  // Not all entities need to be queued, and this happens to be one of them.
  if (is_null($map) || !$queue_item) {
    return FALSE;
  }

  // Find the dedupe field.
  $dedupe_field = NULL;
  foreach ($map->field_mappings as $field_map) {
    if ($field_map['key']) {
      $dedupe_field = $field_map['salesforce_field']['name'];
    }
  }

  // Create the queue item.
  $mapped_entity = salesforce_mapping_map_entity($entity, $entity_type, $map);
  $item = array(
    'drupal_id' => $entity_id,
    'module' => $entity_type,
    'delta' => $bundle,
    'object_type' => $map->salesforce_object_type,
    'operation' => $op,
    'dedupe_field' => $dedupe_field,
    'sobject' => $mapped_entity['sobject'],
    'sync_rules' => $mapped_entity['sync_rules'],
  );
  _salesforce_genmap_alter_operation($item);

  // Send to queue.
  $queue = salesforce_queue_load();
  $result = $queue->createItem($item);
  if (!$result) {
    // salesforce_set_message() is a wrapper for drupal_set_message() that will
    // restrict this message to appear only to those with the
    // 'administer salesforce' permission.
    salesforce_set_message(t('The submission was not sent to Salesforce.'), 'error');
  }
}

/**
 * Map an entity to a sobject and sync rules.
 *
 * @param object $entity
 *   Entity to queue.
 * @param string $entity_type
 *   Type of entity being queued.
 * @param object $map
 *   SalesforceMapping object of the entity that provides instructions of how
 *   to map to the Salesforce object.
 *
 * @return array
 *   An array keyed with 'sobject' containing an sobject and 'sync_rules' with
 *   an array of sync rules.
 */
function salesforce_mapping_map_entity($entity, $entity_type, $map) {
  $entity_wrapper = entity_metadata_wrapper($entity_type, $entity);
  $fields = array();
  $sync_rules = array();
  $field_info = field_info_field_map();
  foreach ($map->field_mappings as $field_map) {
    // Skip fields that aren't being pushed to Salesforce.
    if (!in_array($field_map['direction'], array(SALESFORCE_MAPPING_DIRECTION_DRUPAL_SF, SALESFORCE_MAPPING_DIRECTION_SYNC))) {
      continue;
    }
    $drupal_field_type = $field_map['drupal_field']['fieldmap_type'];
    $sf_field = $field_map['salesforce_field']['name'];

    $fieldmap_type = salesforce_mapping_get_fieldmap_types($drupal_field_type);

    // Check if it's a taxonomy field and use alternate push value function if so.
    $drupal_field = $field_map['drupal_field']['fieldmap_value'];
    if (!empty($field_info[$drupal_field]['type']) && $field_info[$drupal_field]['type'] == 'taxonomy_term_reference') {
      $value =  _salesforce_mapping_taxonomy_field_push_value($field_map, $entity_wrapper);
    }
    else {
      $value = call_user_func($fieldmap_type['push_value_callback'], $field_map, $entity_wrapper);
    }

    $fields[$sf_field] = $value;
    $sync_rules[$sf_field] = isset($field_map['drupal_sf']) ? $field_map['drupal_sf'] : SALESFORCE_SYNC_RULE_ALWAYS;
  }

  // Give other modules a crack at the mapped values.
  $context = array(
    'object' => $entity,
    'entity_type' => $entity_type,
    'entity_wrapper' => $entity_wrapper,
    'map' => $map,
  );
  drupal_alter('salesforce_mapping_map_fields', $fields, $context);

  // Create sObject.
  $object_type = $map->salesforce_object_type;
  $sobject = new SalesforceObject($object_type, $fields);

  // The salesforce_mapping module stores the RecordTypeId rather than the
  // RecordType itself.
  $record_type_id = ($map->salesforce_record_type == 'default') ? NULL : $map->salesforce_record_type;
  $sobject->setRecordTypeId($record_type_id);

  return array(
    'sobject' => $sobject,
    'sync_rules' => $sync_rules,
  );
}

/**
 * Override salesforce_mapping_property_fieldmap_push_value
 *
 * If taxonomy field has been loaded as a property instead of as related entity
 * determine the push value.
 *
 * @param $fieldmap
 * @param $entity_wrapper
 * @return string
 * @throws \EntityMetadataWrapperException
 */
function _salesforce_mapping_taxonomy_field_push_value($fieldmap, $entity_wrapper) {
  $drupal_fields_array = explode(':', $fieldmap['drupal_field']['fieldmap_value']);
  $parent = $entity_wrapper;

  foreach ($drupal_fields_array as $drupal_field) {
    if ($parent instanceof EntityListWrapper) {
      $child_wrapper = $parent->get(0)->{$drupal_field};
    }
    else {
      $child_wrapper = $parent->{$drupal_field};
    }
    $parent = $child_wrapper;
  }

  $terms = array();
  $values = array();

  try {
    $terms = $child_wrapper->value();
  }
  catch (EntityMetadataWrapperException $e) {
  }

  foreach ($terms as $value) {
    $values[] = $value->name;
  }
  $value = implode(SALESFORCE_MAPPING_ARRAY_DELIMITER, $values);

  return $value;
}

/**
 * Remove an entity's items from the queue.
 *
 * @param object $entity
 *   Entity to queue.
 * @param string $entity_type
 *   Type of entity being queued.
 *
 * @return boolean
 *   TRUE if there are no items for the entity in the queue, FALSE if the delete
 *   process failed.
 */
function salesforce_mapping_dequeue_entity($entity, $entity_type) {
  // Information specific to this entity.
  list($entity_id, , $bundle) = entity_extract_ids($entity_type, $entity);

  // Grab the map for this particular entity.
  $mappings = salesforce_mapping_load_multiple(array(
    'drupal_entity_type' => $entity_type,
    'drupal_bundle' => $bundle,
  ));

  $map = NULL;
  if (is_array($mappings)) {
    foreach ($mappings as $mapping) {
      $map = $mapping;
    }
  }
  if (is_null($map)) {
    return TRUE;
  }

  $item = new stdClass();
  $item->drupal_id = $entity_id;
  $item->module = $entity_type;
  $item->delta = $bundle;
  $item->object_type = $map->salesforce_object_type;
  $queue = salesforce_queue_load();
  return $queue->deleteItem($item);
}

/**
 * @} salesforce_mapping_alter_queue
 */


/**
 * @name salesforce_mapping_alter_api Helper API the extension
 * @{
 */

/**
 * Wrapper for *_get_default_value() to compensate for delta differences.
 *
 * @param string $field
 *   Name of the field who's value to retreive.
 * @param array $form_state
 *   Current state of the form to compare with.
 * @param mixed $delta
 *   Optionally provide the delta of the specific field map to check.
 *
 * @return mixed
 *   Value of the field that is appropriate for #default_value.
 */
function _salesforce_mapping_alter_get_default_value($field, &$form_state, $delta = NULL) {
  $value = _salesforce_mapping_get_default_value($field, $form_state, $delta);

  // The delta between stored mapping and the form input mapping are
  // incompatible so we'll figure out what the mapping's delta is and check the
  // default value again.  The original mapping delta is numeric, while our
  // delta is the Drupal field name.
  if (is_null($value) && !is_null($delta) || ($field == 'key' && !is_string($value))) {
    $mapping = NULL;
    if (isset($form_state['salesforce_mapping'])) {
      $mapping = &$form_state['salesforce_mapping'];
    }
    if (!empty($mapping)) {
      $map_delta = NULL;
      foreach ($mapping->field_mappings as $row_key => $row) {
        if (isset($row['drupal_field']['fieldmap_value']) && $row['drupal_field']['fieldmap_value'] == $delta) {
          $map_delta = $row_key;
        }
      }
      if (!is_null($map_delta)) {
        $value = _salesforce_mapping_get_default_value($field, $form_state, $map_delta);
      }
    }
  }

  // Special case for sync direction. Automatically set sync rule if no other
  // value provided.
  if (in_array($field, array('sf_drupal', 'drupal_sf'))) {
    $value = empty($value) ? SALESFORCE_SYNC_RULE_ALWAYS : $value;
  }

  // Special case for 'key'.  When 'delta' is provided, return TRUE or FALSE.
  if ($field == 'key' && !is_null($delta)) {
    $value = $value !== FALSE;
  }

  return $value;
}

/**
 * Get all fields for a given entity type and bundle.
 *
 * This is a modification of salesforce_mapping_property_fieldmap_options()
 * because that function assumes it will be used as an option list for a select
 * field, rather it nests fields with multiple values, which is not what we
 * want when looping through the values.
 *
 * @param string $entity_type
 *   Type of entity to check against.
 * @param string $entity_bundle_type
 *   The specific bundle to check that is part of the given entity type.
 *
 * @return array
 *   List of fields for the given entity type and bundle, keyed by the fields'
 *   machine names and values as the fields' user-friendly name.
 */
function _salesforce_mapping_get_entity_fields($entity_type, $entity_bundle_type = FALSE) {
  $entity_fields = salesforce_mapping_property_fieldmap_options($entity_type, $entity_bundle_type);

  // Grab organization issues and legislative issues vocabs and treat
  // them as node properties instead of as related entities.
  $related_entity_fields = salesforce_mapping_property_fieldmap_options($entity_type, $entity_bundle_type, TRUE);
  $field_info = field_info_field_map();
  foreach ($related_entity_fields as $field_name => $field_title) {
    if (!empty($field_info[$field_name]['type']) && $field_info[$field_name]['type'] == 'taxonomy_term_reference') {
      $entity_fields[$field_name] = $related_entity_fields[$field_name];
    }
  }

  // Remove - Select - option.
  unset($entity_fields['']);

  // Flatten the field list.
  $field_names = array();
  foreach ($entity_fields as $key => $value) {
    if (is_array($value)) {
      // When an array, $key is the user-friendly name rather than machine name.
      // The $sub_key value contains both the machine name of the field and the
      // field's attribute as "field:attribute", for example, "body:text". The
      // $value is the attribute's user friendly name, for example, "Text".
      foreach ($value as $sub_key => $sub_value) {
        $field_names[$sub_key] = $key . ': ' . $sub_value;
      }
    }
    else {
      // Otherwise, $key is the machine name and $value is the user friendly
      // name.
      $field_names[$key] = $value;
    }
  }

  return $field_names;
}

/**
 * Helper to see if the given Salesforce field can be used as an idLookup.
 *
 * @param string $field
 *   The name of the Salesforce field to check.
 * @param string $salesforce_object_type
 *   The object type the field belongs to.
 * @param array $form_state
 *   Current state of the form to store and retreive results from to minimize
 *   the need for recalculation.
 *
 * @return bool
 *   TRUE if the field can be used as an idLookup, otherwise FALSE.
 */
function _salesforce_mapping_salesforce_field_can_idlookup($field, $salesforce_object_type, $form_state) {
  if (empty($field) || empty($salesforce_object_type)) {
    return FALSE;
  }
  if (isset($form_state['sfm_storage']) && isset($form_state['sfm_storage']['idlookup']) && isset($form_state['sfm_storage']['idlookup'][$salesforce_object_type]) && isset($form_state['sfm_storage']['idlookup'][$salesforce_object_type][$field])) {
    return $form_state['sfm_storage']['idlookup'][$salesforce_object_type][$field];
  }
  $sfobject = _salesforce_mapping_get_salesforce_object($salesforce_object_type, $form_state);
  foreach ($sfobject['fields'] as $field_info) {
    $form_state['sfm_storage']['idlookup'][$salesforce_object_type][$field] = $field_info['idLookup'];
    if ($field_info['name'] == $field) {
      return $field_info['idLookup'];
    }
  }
}

/**
 * Get sync rule options compatible with the given Drupal and Salesforce fields.
 *
 * @param string $entity_type
 *   Type of entity being checked.
 * @param string $drupal_field
 *   Field of the entity whose datatype is to be compared.
 * @param string $salesforce_object_type
 *   Type of Salesforce object being checked.
 * @param string $salesforce_field
 *   Field of the Salesforce object whose datatype is to be compared.
 * @param string $direction
 *   The direction the data will be flowing to, either from Drupal to
 *   Salesforce, "drupal_sf", or Salesforce to Drupal, "sf_drupal".
 * @param array $form_state
 *   The current state of the form, used for storage and retreival of data.
 *
 * @return array
 *   Array of sync rule options that can be used for #options in a form.
 */
function _salesforce_mapping_get_sync_rule_options($entity_type, $drupal_field, $salesforce_object_type, $salesforce_field, $direction, $form_state) {
  $options = array(
    SALESFORCE_SYNC_RULE_NEVER => t('Never'),
    SALESFORCE_SYNC_RULE_BLANK => t('When blank'),
    SALESFORCE_SYNC_RULE_APPEND => t('Merge values'),
    SALESFORCE_SYNC_RULE_ALWAYS => t('Always'),
  );

  $allowed_options = array();
  foreach ($options as $sync_rule => $label) {
    $allowed = _salesforce_mapping_datatype_can_sync($entity_type, $drupal_field, $salesforce_object_type, $salesforce_field, $direction, $sync_rule, $form_state);
    if ($allowed) {
      $allowed_options[$sync_rule] = $label;
    }
  }
  return $allowed_options;
}

/**
 * Checks to see if the given Drupal field and Salesforce field can sync.
 *
 * @param string $entity_type
 *   Type of entity being checked.
 * @param string $drupal_field
 *   Field of the entity whose datatype is to be compared.
 * @param string $salesforce_object_type
 *   Type of Salesforce object being checked.
 * @param string $salesforce_field
 *   Field of the Salesforce object whose datatype is to be compared.
 * @param string $direction
 *   The direction the data will be flowing to, either from Drupal to
 *   Salesforce, "drupal_sf", or Salesforce to Drupal, "sf_drupal".
 * @param string $sync_rule
 *   The sync rule being applied, SALESFORCE_SYNC_RULE_ALWAYS,
 *   SALESFORCE_SYNC_RULE_BLANK, SALESFORCE_SYNC_RULE_APPEND, or
 *   SALESFORCE_SYNC_RULE_NEVER.
 * @param array $form_state
 *   The current state of the form, used for storage and retreival of data.
 *
 * @return boolean
 *   TRUE if they can sync and FALSE if they cannot.
 */
function _salesforce_mapping_datatype_can_sync($entity_type, $drupal_field, $salesforce_object_type, $salesforce_field, $direction, $sync_rule, &$form_state) {
  // We're being lenient here because we can very likely be passing no values in
  // the form because the user hasn't yet selected a value for some of these
  // vars.
  if (empty($entity_type) || empty($drupal_field) || empty($salesforce_object_type) || empty($salesforce_field) || empty($direction) || empty($sync_rule)) {
    return FALSE;
  }

  // The 'never' sync rule always passes because there is never any actual data
  // being passed around in this case.
  if ($sync_rule == SALESFORCE_SYNC_RULE_NEVER) {
    return TRUE;
  }

  // The 'append' sync rule always fails because Springboard is choosing to
  // disable this feature.  The variable is added so that the append
  // functionality can still be tested, and in an edge case scenario, reenabled
  // on a case-by-case basis if required.
  if ($sync_rule == SALESFORCE_SYNC_RULE_APPEND && variable_get('salesforce_genmap_disable_sync_rule_append', TRUE)) {
    return FALSE;
  }

  // Find the datatype for the Drupal field.
  if (isset($form_state['sfm_storage']) && isset($form_state['sfm_storage']['drupal_datatype']) && isset($form_state['sfm_storage']['drupal_datatype'][$entity_type]) && isset($form_state['sfm_storage']['drupal_datatype'][$entity_type][$drupal_field])) {
    $drupal_datatype = $form_state['sfm_storage']['drupal_datatype'][$entity_type][$drupal_field];
  }
  else {
    $entity_properties = entity_get_all_property_info($entity_type);
    $drupal_field_parts = explode(':', $drupal_field);
    $drupal_datatype = 'text';
    if (isset($entity_properties[$drupal_field_parts[0]])) {
      $drupal_field_info = $entity_properties[$drupal_field_parts[0]];
      if ((!isset($drupal_field_parts[1]) || empty($drupal_field_parts[1])) && isset($drupal_field_info['type'])) {
        $drupal_datatype = $drupal_field_info['type'];
      }
      elseif (isset($drupal_field_parts[1]) && !empty($drupal_field_parts[1]) && isset($drupal_field_info['property_info'][$drupal_field_parts[1]]['type'])) {
        $drupal_datatype = $drupal_field_info['property_info'][$drupal_field_parts[1]]['type'];
      }
    }
    $form_state['sfm_storage']['drupal_datatype'][$entity_type][$drupal_field] = $drupal_datatype;
  }

  // Find the datatype for the Salesforce field.
  if (isset($form_state['sfm_storage']) && isset($form_state['sfm_storage']['salesforce_datatype']) && isset($form_state['sfm_storage']['salesforce_datatype'][$salesforce_object_type]) && isset($form_state['sfm_storage']['salesforce_datatype'][$salesforce_object_type][$salesforce_field])) {
    $salesforce_datatype = $form_state['sfm_storage']['salesforce_datatype'][$salesforce_object_type][$salesforce_field];
  }
  else {
    $sfobject = _salesforce_mapping_get_salesforce_object($salesforce_object_type, $form_state);
    foreach ($sfobject['fields'] as $field_info) {
      $form_state['sfm_storage']['salesforce_datatype'][$salesforce_object_type][$field_info['name']] = $field_info['type'];
      if ($field_info['name'] == $salesforce_field) {
        $salesforce_datatype = $field_info['type'];
        break;
      }
    }
  }

  // This is taken straight from salesforce_mapping_property_validation().
  $verify_array = array(
    'sync' => array(
      'string' => array('text', 'list<text>', 'uri'),
      'int' => array('integer'),
      'id' => array('integer'),
      'datetime' => array('date'),
      'email' => array('text'),
    ),
    'drupal_sf' => array(
      'string' => array(),
      'int' => array('integer'),
      'id' => array('integer'),
      'datetime' => array('date'),
      'email' => array('text'),
    ),
    'sf_drupal' => array(
      'string' => array('text', 'int', 'list<text>'),
      'int' => array('integer'),
      'id' => array('integer'),
      'datetime' => array('date'),
      'email' => array('text'),
    ),
  );

  // The datatypes are compatible if the Drupal datatype is in the array for the
  // given direction and Salesforce datatype, or is assumed to be compatible if
  // there is not a rule or when the ruleset is empty.
  if (
    !isset($verify_array[$direction][$salesforce_datatype])
    || empty($verify_array[$direction][$salesforce_datatype])
    || in_array($drupal_datatype, $verify_array[$direction][$salesforce_datatype])
  ) {
    // These two datatypes can sync.  Now see if the the sync rule is compatible
    // with this set.
    $sync_restrictions = array(
      SALESFORCE_SYNC_RULE_ALWAYS => array(),
      // Although 'append' returned FALSE in the begining, leaving the logic
      // here so it can be reenabled rather easily.  It also serves as an
      // example of syncing with only text data types.
      SALESFORCE_SYNC_RULE_APPEND => array(
        'drupal' => array(
          'text',
          'list<text>',
        ),
        'salesforce' => array(
          'string',
        ),
      ),
      SALESFORCE_SYNC_RULE_BLANK => array(),
      // The 'never' sync rule returned TRUE in the very begining.
    );
    if (empty($sync_restrictions[$sync_rule])) {
      // No rules mean no restrictions.
      return TRUE;
    }
    else {
      return (
        in_array($drupal_datatype, $sync_restrictions[$sync_rule]['drupal'])
        && in_array($salesforce_datatype, $sync_restrictions[$sync_rule]['salesforce'])
      );
    }
  }
  else {
    // These two datatypes cannot sync.
    return FALSE;
  }
}

/**
 * @} salesforce_mapping_alter_api
 */
