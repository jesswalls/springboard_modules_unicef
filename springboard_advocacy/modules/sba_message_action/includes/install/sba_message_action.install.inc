<?php

/**
 * @file
 * Install helper functions for message action content type CRUD.
 */

/**
 * Creates the sba_message_action content type.
 */
function _sba_message_action_create_content_type() {

  module_load_include('inc', 'sba_message_action', 'includes/install/sba_message_action.install_fields');
  module_load_include('inc', 'sba_message_action', 'includes/install/sba_message_action.install_variables');
  module_load_include('inc', 'sba_message_action', 'includes/install/sba_message_action.install_profile');
  require_once(drupal_get_path('module', 'webform_user') . '/includes/webform_user.fields.inc');


  $type = node_type_set_defaults();
  $type->name = t('Message Action');
  $type->type = 'sba_message_action';
  $type->description = '';
  $type->title_label = t('Title');
  $type->has_title = TRUE;
  $type->base = 'node_content';
  $type->custom = TRUE;
  $type->modified = TRUE;
  $type->module = 'sba_message_action';

  // Save or reset persistent variable values.
  _sba_message_action_set_vars();
  node_type_save($type);
  node_types_rebuild();
  _sba_message_action_create_node_fields();
  _sbp_message_action_create_user_profile_fields();
  _webform_user_add_default_fields('sba_message_action');
  _sba_message_action_reorder_internal_name();

  drupal_set_message(t('The content type Springboard Message Action has been added.'));
  watchdog('sba_message_action', 'Added content type Springboard Message Action.');

  // Weighting the module to ensure submission handlers run after Webform User.
  // This ensures that the user id in webform_submissions has been updated by
  // Webform User before we get to it.
  db_query('UPDATE {system} SET weight = :weight WHERE name = :name', array(':weight' => 1000, ':name' => 'sba_message_action'));
}

function _sba_message_action_reorder_internal_name() {
  $instance_info = field_read_instance('node', 'field_webform_user_internal_name', 'sba_message_action');
  $instance_info['widget']['weight'] = 1;
  field_update_instance($instance_info);

  $instance_info = field_read_instance('node', 'field_message_action_img', 'sba_message_action');
  $instance_info['widget']['weight'] = 2;
  field_update_instance($instance_info);

  $instance_info = field_read_instance('node', 'field_message_call_to_action', 'sba_message_action');
  $instance_info['widget']['weight'] = 4;
  field_update_instance($instance_info);

  $instance_info = field_read_instance('node', 'body', 'sba_message_action');
  $instance_info['widget']['weight'] = 5;
  field_update_instance($instance_info);
}

/**
 * Delete springboard message action nodes and their messages.
 */
function _sba_message_action_delete_nodes() {

  $result = db_select('node', 'n')
    ->fields('n', array('nid'))
    ->condition('type', 'sba_message_action')
    ->execute();

  $nids = $result->fetchCol();

  if (!empty($nids)) {
    if (module_exists('sba_message')) {

      $message_ids = db_query(
        'SELECT entity_id FROM {field_data_field_sba_action_id} WHERE field_sba_action_id_target_id IN (:nids)',
        array(':nids' => $nids))->fetchAssoc();

      drupal_load('module', 'sba_message');
      if (is_array($message_ids)) {
        sba_message_delete_multiple($message_ids);
      }
    }
    node_delete_multiple($nids);
    drupal_set_message('Springboard message actions have been deleted.');
  }
}
