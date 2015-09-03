<?php

/**
 * @file
 * Install helper functions for message action configuration variables.
 */

/**
 * Variables needed for integrations with other modules.
 *
 * Webform user, salesforce, springboard taxonomy, advocacy.
 */
function _sba_message_action_set_vars() {

  $variables = array(
    'additional_settings__active_tab' => 'edit-webform-user',
    'field_bundle_settings_node_' => array(),
    'menu_parent' => 'main-menu:0',
    'menu_options' => array(
      0 => 'main-menu',
    ),
    'node_submitted' => 0,
    'node_preview' => 1,
    'node_options' => array(),
    'fundraiser' => 0,
    'webform_user' => 1,
    'webform_user_default_fields' => array(
      'sbp_salutation' => 'sbp_salutation',
      'sbp_first_name' => 'sbp_first_name',
      'sbp_last_name' => 'sbp_last_name',
      'mail' => 'mail',
      'sbp_address' => 'sbp_address',
      'sbp_address_line_2' => 'sbp_address_line_2',
      'sbp_city' => 'sbp_city',
      'sbp_state' => 'sbp_state',
      'sbp_zip' => 'sbp_zip',
      'sbp_zip_plus_four' => 'sbp_zip_plus_four',
      'sbp_phone' => 'sbp_phone',
      'sbp_cid' => 'sbp_cid',
      'sbp_market_source' => 'sbp_market_source',
      'sbp_referrer' => 'sbp_referrer',
      'sbp_initial_referrer' => 'sbp_initial_referrer',
      'sbp_search_engine' => 'sbp_search_engine',
      'sbp_search_string' => 'sbp_search_string',
      'sbp_user_agent' => 'sbp_user_agent',
      'sbp_salesforce_account_id' => 'sbp_salesforce_account_id',
      'sbp_salesforce_contact_id' => 'sbp_salesforce_contact_id',
    ),
  );
  foreach ($variables as $key => $value) {
    $variable_new = $key . '_sba_message_action';
    if (is_array($value)) {
      $value = array_keys(array_filter($value));
    }
    variable_set($variable_new, $value);
  }

  // Add as a webform.
  $webform_node_types = variable_get('webform_node_types', array('webform'));
  $webform_node_types_primary = variable_get('webform_node_types_primary', array('webform'));
  $webform_node_types = array_merge($webform_node_types, array('sba_message_action'));
  $webform_node_types_primary = array_merge($webform_node_types_primary, array('sba_message_action'));
  variable_set('webform_node_types', array_unique($webform_node_types));
  variable_set('webform_node_types_primary', array_unique($webform_node_types_primary));

  // Enable form_layouts.
  variable_set('form_layouts_sba_message_action', 1);
  // Default confirmation message.
  variable_set('sba_message_action_confirm', '');
  // Add as an advocacy message type.
  $sba_action_types = variable_get('sba_action_types', array(''));
  $sba_action_types = array_merge($sba_action_types, array('sba_message_action'));
  variable_set('sba_action_types', array_unique($sba_action_types));
  // Let springboard taxonomy know this type has organization issues field.
  $taxonomy_types = variable_get('springboard_taxonomy_node_types', array());
  $taxonomy_types = array_merge($taxonomy_types, array('sba_message_action' => 'sba_message_action'));
  variable_set('springboard_taxonomy_node_types', array_unique($taxonomy_types));
}
