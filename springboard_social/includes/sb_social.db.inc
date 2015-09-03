<?php

/**
 * @file
 * db helper functions
 */

/**
 * Load share event.
 *
 * @param int $share_id
 *   Social share event ID.
 *
 * @return array
 *   Returns an associative array of event data.
 */
function sb_social_share_event_load($share_id) {
  $result = db_query('
    SELECT
      share_id,
      uid,
      sid,
      did,
      nid,
      page_name,
      internal_name,
      market_source,
      s.type,
      service,
      created,
      status,
      url,
      sf_share_id,
      opportunity_id,
      client_id

    FROM {sb_social_shares} s
    WHERE
      share_id = :share_id
  ', array(':share_id' => $share_id));

  return $result->fetchAssoc();
}

/**
 * Save a social share record to the database. Generate and return the share's url.
 *
 * @param array $record
 *   Social share record to be saved.
 *
 * @param array $settings
 *   Social share settings for this record. (Optional, for url generation.)
 *
 * @param array $url_path
 *   Path to use for url generation. (Optional.)
 *
 * @return string
 *   Counterintuitively, this function returns a shortened share url for the
 *   share event.
 */
function sb_social_share_save($record, $settings = FALSE, $url_path = FALSE) {
  // Update is not included as these records should only be created when a share
  // event has taken place and should not be editable after the fact.
  $query = db_insert('sb_social_shares');
  $share_id = $query->fields($record)->execute();
  
  // Generate url and update share record.
  if (empty($record['url']) && $settings && $url_path) {
    $url = sb_social_share_tracker_url($share_id, $settings, $url_path);
    // URL context is set in $_SESSION so any data set during a form submission
    // is still available after Webform redirects to a confirmation page.
    // This lets 3rd party modules set url context info during the form submission
    // and then check for their data when the URL alter hook is executed.
    $url_context = isset($_SESSION['sb_social_url_context']) ? $_SESSION['sb_social_url_context'] : FALSE;
    $node = node_load($record['nid']);
    drupal_alter('sb_social_share_url', $url, $node, $url_context);
    $record['url'] = $url;
    db_query('UPDATE {sb_social_shares} set url = :url WHERE share_id = :share_id', array(':url' => $url, ':share_id' => $share_id));
  }
  
  watchdog('sb_social', 'share id:' . $share_id);  //@TODO: Is this test code that should be removed?

  // Behold, a new entity!
  if ($share_id) {
    $record['share_id'] = $share_id;
    module_invoke_all('entity_insert', (object)$record, 'sb_social_share');
  }
  
  // Let modules react to the share event. This is a legacy hook for the benefit of old implementations.
  module_invoke_all('sb_social_share_event_save', $record);

  return $record['url'];
}

/**
 * Getter for social share event entity properties.
 */
function sb_social_share_entity_get_properties($data, array $options, $name, $type, $info) {
  switch ($name) {
    case 'share_name':
      // Give a unique share name with the page name and date/time.
      return t(
        'Social Share - !page_name (!date)',
        array('!page_name' => $data->page_name, '!date' => date('Y-m-d H:i:s', $data->created))
      );
    case 'user':
      // Load and return the sharing user's account object.
      return $data->uid ? user_load($data->uid) : NULL;
    case 'submission':
      // Load and return the originating Webform submission, if any.
      module_load_include('inc', 'webform', 'includes/webform.submissions');
      return $data->sid ? webform_get_submission($data->nid, $data->sid) : NULL;
    case 'donation':
      // Load and return the originating Fundraiser donation object, if any.
      return $data->did ? fundraiser_donation_get_donation($data->did) : NULL;
    case 'share_date':
      // The "date" type is represented by a UNIX timestamp (per https://www.drupal.org/node/905580).
      return $data->created;
  }
  return NULL;
}

/**
 * Setter for social share event entity properties.
 */
function sb_social_share_entity_set_properties($data, $name, $value) {
  // @TODO: Logic along the lines of sb_social_share_entity_get_properties() would need to be written here
  // if social shares were ever to be imported via Salesforce Pull.
  return entity_property_verbatim_set($data, $name, $value);
}

/**
 * Load social settings by id.
 *
 * If no id is provided, attempt to identify applicable settings from
 * the url.
 *
 * @param mixed $id
 *   Optional share settings id.
 *
 * @return mixed
 *   Returns an associative array containing the social share settings
 *   applicable to the ID passed or the current URL.
 */
function sb_social_get_current_settings($id = FALSE) {
  if (!$id) {
    if (arg(0) == 'node' && is_numeric(arg(1))) {
      $node = node_load(arg(1));
      $id = is_object($node) ? $node->nid : FALSE;
    }
    else {
      // Social supports both internal paths and path aliases so  we need to
      // check both.
      $path = current_path();
      $alias = drupal_get_path_alias($path);
      $id = !empty($alias) ? array($path, $alias) : $path;
    }
  }

  if ($id) {
    $sid = _sb_social_sid_by_id($id);
    $settings = sb_social_settings_load($sid);
  }
  return $settings;
}

/**
 * Delete share event.
 */
function sb_social_share_event_delete($sid) {
  db_query('DELETE FROM {sb_social_shares} WHERE sid = :sid', array(':sid' => $sid));
}

/**
 * Load shared content settings.
 */
function sb_social_settings_load($sid, $cache = TRUE) {

  // This can get called by hook_block_view() in addition to hook_init() so we
  // should cache.
  $settings = &drupal_static(__FUNCTION__);

  if (!isset($settings[$sid]) || !$cache) {
    $results = db_query('SELECT * FROM {sb_social_settings} WHERE sid = :sid', array(':sid' => $sid));

    $settings[$sid] = $results->fetchAssoc();
    if ($settings[$sid] && !empty($settings[$sid]['data'])) {
      $settings[$sid]['data'] = unserialize($settings[$sid]['data']);
    }
    if ($settings[$sid]['type'] == 'path') {
      $settings[$sid]['path'] = sb_social_get_path($settings[$sid]['id']);
    }

    // Supply global defaults if no settings are available.
    if (empty($settings[$sid])) {
      // Check for node view page.
      $node = menu_get_object();
      // Confirmation page.
      if (!$node && arg(2) == 'done') {
        $node = menu_get_object('webform_menu');
      }
      if (isset($node->nid)) {
        $enabled_content_types = variable_get('springboard_social_enabled_content_types', array());
        // If this node is not a supported node type return FALSE
        if (empty($enabled_content_types[$node->type])) {
          return $settings[$sid] = FALSE;
        }

        $settings[$sid]['id'] = $node->nid;
        $settings[$sid]['type'] = 'node';
      }
      else {
        // If we still don't have settings, use the current path.
        $settings[$sid]['id'] = current_path();
        $settings[$sid]['type'] = 'path';
      }

      $enabled_services = sb_social_get_enabled_services();
      foreach ($enabled_services as $service) {
        $settings[$sid]['data'][$service] = _sb_social_settings_defaults($service);
      }
      if (module_exists('market_source')) {
        $settings[$sid]['data']['market_source'] = _sb_social_market_source_defaults();
      }
    }
  }

  return $settings[$sid];
}


/**
 * Delete settings.
 */
function sb_social_webform_settings_delete($nid, $type = 'node') {
  db_query('DELETE FROM {sb_social_settings} WHERE id = :id AND type = :type', array(':id' => $nid, ':type' => $type));
}

/**
 * Lookup ID associated with the share settings ID provided.
 *
 * @param int $sid
 *   Share settings ID
 *
 * @return mixed
 *   Returns the node id or path associated with the share settings ID.
 */
function sb_social_get_id_by_sid($sid) {
  $result = db_query('SELECT id FROM {sb_social_settings} WHERE sid = :sid', array(':sid' => $sid));
  return $result->fetchField();
}

/**
 * Get share settings id by drupal id.
 *
 * @param int $id
 *   Node id for node settings, path for path settings.
 *
 * @param bool|string $type
 *   Optional record type.
 *
 * @return mixed
 *   Returns the sid associated with the given id, or FALSE if no records were
 *   found.
 */
function sb_social_get_sid_by_id($id, $type = FALSE) {

  $query = db_select('sb_social_settings', 's');
  $query->fields('s', array('sid'));
  $query->condition('id', $id, '=');
  if ($type) {
    $query->condition('type', $type, '=');
  }
  $result = $query->execute();
  $data = $result->fetchField();
  return $data ? $data : FALSE;
}

/**
 * Load all path settings, used by path admin list page.
 */
function sb_social_path_settings_load_all() {
  $settings = array();
  $results = db_query('SELECT s.sid, p.path FROM {sb_social_settings} s INNER JOIN {sb_social_path} p ON s.id = p.pid;');
  while ($item = $results->fetchAssoc()) {
    $settings[] = $item;
  }
  return $settings;
}


/**
 * Provide service default settings.
 */
function _sb_social_settings_defaults($service) {
  $settings = array();
  ctools_include('plugins');
  $plugins = ctools_get_plugins('sb_social', 'social_networks');
  $services = array_keys($plugins);

  if (in_array($service, $services)) {
    $func = $plugins[$service]['defaults'];
    $settings = $func();
  }

  return $settings;
}

/**
 * Provide default MS settings when no node settings are available.
 */
function _sb_social_market_source_defaults() {
  $market_source = array();
  $fields = market_source_field_info();
  $share_enabled_fields = _sb_social_list_share_enabled_market_source_fields();
  foreach ($fields as $key => $field) {
    if (!in_array($key, $share_enabled_fields)) {
      continue;
    }
    $market_source[$key] = variable_get('springboard_social_ms_' . $key, '');
  }
  return $market_source;
}

/**
 * List services enabled on the Social admin settings form.
 *
 * @return array
 *   An array of enabled services.
 */
function sb_social_get_enabled_services() {
  static $enabled_services = array();
  if (empty($enabled_services) && $enabled_services !== FALSE) {
    $services = variable_get('springboard_social_services', array());
    if (!empty($services)) {
      foreach ($services as $service => $status) {
        if ($status) {
          $enabled_services[] = $service;
        }
      }
    }
  }
  return $enabled_services;
}


/**
 * Save share settings.
 *
 * @param array $settings
 *   Associative array of settings to save.
 */
function sb_social_settings_save($settings) {

  if (is_array($settings['data'])) {
    $settings['data'] = serialize($settings['data']);
  }
  $update = array();
  $sid = _sb_social_sid_by_id($settings['id']);

  // If there is a share settings id associated with the settings id,
  // update the existing record.
  if ($sid) {
    $settings['sid'] = $sid;
    $update = array('sid');
  }
  drupal_write_record('sb_social_settings', $settings, $update);
}

/**
 * Delete share settings.
 *
 * @param int $sid
 *   Share settings id of record to delete.
 */
function sb_social_settings_delete($sid) {
  $query = db_delete('sb_social_settings');
  $query->condition('sid', $sid);
  $query->execute();
}

/**
 * Lookup social share settings by webform submission id.
 *
 * @param int $submission_id
 *   Webform submission id.
 *
 * @return array
 *   Returns Social settings associated with webform that was submitted.
 */
function _sb_social_get_settings_by_sid($submission_id) {
  $nid = _sb_social_get_nid_by_sid($submission_id);
  $sid = sb_social_get_sid_by_id($nid, 'node');
  return sb_social_settings_load($sid);
}

/**
 * Lookup Webform node id from Webform submission ID.
 *
 * @param int $sid
 *   Webform submission id.
 *
 * @return int
 *   Node id of the Webform associated with this submission.
 */
function _sb_social_get_nid_by_sid($sid) {
  static $data = array();
  if (empty($data[$sid])) {
    $result = db_query('SELECT nid FROM {webform_submissions} WHERE sid = :sid', array(':sid' => $sid));
    $nid = $result->fetchField();
    $data[$sid] = $nid ? $nid : 0;
  }
  return $data[$sid];
}

/**
 * Load a partial submission record from {webform_submissions}.
 *
 * @param int $sid
 *   Webform submission id.
 *
 * @return mixed
 *   Returns an associative array of nid, sid, and uid for a given webform
 *   submission.
 */
function _sb_social_load_submission($sid) {
  $result = db_query('
    SELECT
      nid,
      sid,
      uid
    FROM {webform_submissions}
    WHERE
      sid = :sid
  ', array(':sid' => $sid));
  return $result->fetchAssoc();
}

/**
 * Lookup donation details by Webform submission id.
 *
 * @param int $sid
 *   Webform submission id.
 *
 * @return mixed
 *   Returns donation information associated with a given Webform submission.
 */
function sb_social_get_donation_by_sid($sid) {
  $query = db_select('fundraiser_donation', 'f');
  $query->fields('f');
  $query->condition('sid', $sid);
  $result = $query->execute();

  return $result->fetchObject();
}

/**
 * Retrieve share settings unique id (sid) by current context id.
 */
function _sb_social_sid_by_id($id) {
  $query = db_select('sb_social_settings', 's');
  $query->fields('s', array('sid'));

  if (is_array($id)) {
    $or = db_or();
    foreach ($id as $data) {
      $or->condition('id', $data, '=');
    }
    $query->condition($or);
  }
  else {
    $query->condition('id', $id, '=');
  }
  $results = $query->execute();

  return $results->fetchField();
}

/**
 * Lookup numeric id of path.
 *
 * @param string|array $path
 *   Drupal path, may be a string or an array of original path and alias.
 */
function sb_social_get_path_id($path) {
  $query = db_select('sb_social_path', 'p');
  $query->fields('p', array('pid'));

  if (is_array($path)) {
    $or = db_or();
    foreach ($path as $item) {
      $or->condition('path', $item, '=');
    }
    $query->condition($or);
  }
  else {
    $query->condition('path', $path, '=');
  }
  $results = $query->execute();

  return $results->fetchField();
}

/**
 * Save path record and return path id.
 *
 * This permits us to reference an arbitrary Drupal path
 * with a unique numeric identifier, which can then be used as
 * the numeric portion of edit form paths or passed as an ID to
 * the share tracking callback.
 *
 * @param string $path
 *   Drupal menu path.
 *
 * @return int
 *   Numeric id of path.
 */
function sb_social_save_path($path) {
  $query = db_insert('sb_social_path');
  $record = array('path' => $path);
  $path_id = $query->fields($record)->execute();
  return $path_id;
}

/**
 * Lookup Drupal menu path by numeric path id.
 *
 * @param int $id
 *   Numeric id of the drupal path we're looking for.
 *
 * @return string
 *   Returns the requested path.
 */
function sb_social_get_path($id) {
  $results = db_query('SELECT path FROM {sb_social_path} WHERE pid = :id', array(':id' => $id));
  return $results->fetchField();
}

/**
 * Lookup webform submission ID for a given fundraiser donation id.
 */
function _sb_social_get_webform_sid_by_donation_id($did) {
  $result = db_query('SELECT sid FROM {fundraiser_donation} WHERE did = :did', array(':did' => $did));
  return $result->fetchField();
}

/**
 * Add opportunity sfid to {sb_social_shares}.
 *
 * @param mixed $item
 *   Salesforce queue item.
 *
 * @param mixed $record
 *   Salesforce queue response record.
 *
 * @return bool
 *   Returns TRUE if SFID is available and the social share record was updated.
 *   Otherwise returns FALSE.
 */
function sb_social_update_opportunity_id($item, $record) {
  if (empty($record->id) || $record->success != TRUE) {
    return FALSE;
  }
  $sid = _sb_social_get_webform_sid_by_donation_id($item->drupal_id);
  db_query('UPDATE {sb_social_shares} SET opportunity_id = :oppid WHERE sid = :sid', array(':oppid' => $record->id, ':sid' => $sid));
  return TRUE;
}

/**
 * Add share sfid to {sb_social_shares}.
 *
 * @param object $item
 *   Salesforce queue item.
 *
 * @param object $record
 *   Salesforce queue response record.
 */
function sb_social_update_sf_share_id($item, $record) {
  db_query('UPDATE {sb_social_shares} SET sf_share_id = :sf_share_id WHERE share_id = :share_id', array(':sf_share_id' => $record->id, 'share_id' => $item->drupal_id));
}

/**
 * Look up the Opportunity Salesforce ID associated with a given Webform sid.
 *
 * @param int $sid
 *   Webform submission ID.
 *
 * @return mixed
 *   Returns the current sfid or 0 if none found.
 */
function _sb_social_get_opportunity_id_from_submission_id($sid) {
  if (module_exists('salesforce_sync')) {
    $result = db_query('
      SELECT
        s.sfid
      FROM {salesforce_sync_map} s
      INNER JOIN {fundraiser_donation} f
        ON f.did = s.drupal_id
      WHERE f.sid = :sid', array(':sid' => $sid));
    $sfid = $result->fetchField();
  }
  return !empty($sfid) ? $sfid : 0;
}

/**
 * Look up the Opportunity Salesforce ID for share events linked to a donation.
 *
 * @param int $share_id
 *   Share id.
 *
 * @return bool|string
 *   Returns the sfid if one is available or FALSE.
 */
function _sb_social_get_opportunity_id_from_share_id($share_id) {
  $result = db_query('SELECT sid FROM {sb_social_shares} WHERE share_id = :share_id', array(':share_id' => $share_id));
  $sid = $result->fetchField();
  if ($sid) {
    return _sb_social_get_opportunity_id_from_submission_id($sid);
  }
  return FALSE;
}

/**
 * Add did value to shares table.
 */
function sb_social_update_did($sid, $did) {
  db_query('UPDATE {sb_social_shares} SET did = :did WHERE sid = :sid', array(':did' => $did, ':sid' => $sid));
}

/**
 * Stripped down version of fundraiser_get_donation_by_sid.
 *
 * In this instance we don't need the entire donation record.
 *
 * @param int $sid
 *   Webform submission id.
 *
 * @return int
 *   Returns the Fundraiser donation id (did) associated with a given
 *   Webform submission.
 */
function _sb_social_get_did_by_sid($sid) {
  $results = db_query('SELECT did FROM {fundraiser_donation} WHERE sid = :sid', array(':sid' => $sid));
  return $results->fetchField();
}
