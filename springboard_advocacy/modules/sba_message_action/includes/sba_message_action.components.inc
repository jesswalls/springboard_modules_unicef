<?php

/**
 * @file
 * Helper functions for message action webform components.
 */

/**
 * Insert new components on node/add.
 *
 * Also re-insert the state and zip fields that were unset
 * in webform_user_profile_fields_alter() and re-map them.
 *
 * Called from sba_message_action_node_insert();
 *
 * @param $node
 */
function sba_message_action_insert_components($node) {
  module_load_include('inc', 'webform', 'includes/webform.components');

  // Limit the state field to US states.
  $fields[] = array(
    'nid' => $node->nid,
    'form_key' => 'sbp_state',
    'pid' => 0,
    'name' => t('State'),
    'type' => 'select',
    'mandatory' => 1,
    'weight' => 12,
    'email' => 1,
    'extra' => array(
      'options_source' => 'united_states',
      // May have to remove some.
      'aslist' => 'Y',
      'multiple' => 0,
    ),
  );

  $fields[] = array(
    'nid' => $node->nid,
    'form_key' => 'sbp_zip',
    'pid' => 0,
    'name' => t('Zip Code'),
    'type' => 'textfield',
    'mandatory' => 1,
    'weight' => 13,
    'email' => 1,
    'extra' => array(
      'maxlength' => 5,
    ),
  );

  $fields[] = array(
    'nid' => $node->nid,
    'form_key' => 'sba_user_edit_flag',
    'pid' => 0,
    'name' => t('User Edit Flag'),
    'type' => 'hidden',
    'value' => 0,
    'weight' => 13,
    'email' => 1,
  );

  $fields[] = array(
    'nid' => $node->nid,
    'form_key' => 'sba_deliverable_count',
    'pid' => 0,
    'name' => t('Messages Generated'),
    'type' => 'hidden',
    'value' => 0,
    'weight' => 13,
    'email' => 1,
  );

  $fields[] = array(
    'nid' => $node->nid,
    'form_key' => 'sbp_sba_action_optin',
    'name' => t('Opt In '),
    'type' => 'select',
    'mandatory' => 0,
    'pid' => 0,
    'weight' => 40,
    'explanation' => '',
    'options' => array(0, 1),
    'category_key' => NULL,
    'category_name' => NULL,
    'extra' => array(
      'title_display' => 'none',
      'multiple' => 1,
      'items' => 'sbp_sba_action_optin|Show my name in a list of action takers.'
    ),
  );

  $exclude = array();
  $exclude[] = 'sba_user_edit_flag';
  $exclude[] = 'sba_deliverable_count';
  $exclude[] = 'sbp_sba_action_optin';

  // Add the component to the Webform.
  foreach ($fields as $field) {
    // Don't insert fields if cloning.
    if (!isset($node->map) || (isset($node->map) && !in_array($field['form_key'], $node->map) && !in_array($field['form_key'], $exclude))) {
      $cid = webform_component_insert($field);
      // User map the state field.
      if ($field['form_key'] == 'sbp_state' || $field['form_key'] == 'sbp_zip') {
        $map = array(
          'nid' => $node->nid,
          'cid' => $cid,
          'map_id' => $field['form_key'],
        );
        drupal_write_record('webform_user_component_map', $map);
      }
    }
  }
}

/**
 * Like it says, prevent deletion in the webform UI of these fields.
 *
 * Called from sba_message_action_form_webform_component_delete_form_alter().
 *
 * @param $form
 * @param $form_state
 */
function sba_message_action_prevent_component_delete(&$form, &$form_state) {

  $required_fields = sba_message_locked_fields();
  $cid = $form['component']['#value']['cid'];
  $component = $form['node']['#value']->webform['components'][$cid];

  if (in_array($component['form_key'], $required_fields)) {
    $message = t('<strong>!name</strong> is a required field and cannot be deleted from this form.',
      array('!name' => $component['name']));
    $form['description']['#markup'] = $message;
    unset($form['actions']['submit']);
  }
}

/**
 * Implements hook_form_webform_components_form_alter().
 *
 * Disable un-mandatory of certain profile fields.
 */
function sba_message_action_form_webform_components_form_alter(&$form, &$form_state, $form_id) {
  if ($form['#node']->type == 'sba_message_action') {
    sba_message_action_component_overview_lock($form);
  }
}

/**
 * Lock down edit forms.
 *
 * Called from sba_message_action_form_webform_component_edit_form_alter().
 * @param $form
 */
function sba_message_action_component_edit_lock(&$form) {
  $locked_fields = sba_message_locked_fields();

  if (in_array($form['form_key']['#default_value'], $locked_fields)) {
    // Check the node type.
    $form['form_key']['#disabled'] = TRUE;
    $form['validation']['mandatory']['#disabled'] = TRUE;
  }
}

/**
 * Lock down editing on the overview form.
 *
 * Called from sba_message_action_form_webform_components_form_alter().
 *
 * @param $form
 */
function sba_message_action_component_overview_lock(&$form) {
  $locked_fields = sba_message_locked_fields();
  foreach ($form['#node']->webform['components'] as $cid => $component) {
    if (in_array($component['form_key'], $locked_fields)) {
      $form['components'][$cid]['mandatory']['#disabled'] = TRUE;
    }
  }
}

/**
 * @return array
 */
function sba_message_locked_fields() {
  $locked_fields = array(
    'sbp_salutation',
    'sbp_first_name',
    'sbp_last_name',
    'mail',
    'sbp_address',
    'sbp_city',
    'sbp_state',
    'sbp_zip',
    'sbp_phone',
    'sba_deliverable_count',
    'sba_user_edit_flag',
    'sbp_zip_plus_four',
    'sbp_sba_action_optin',
  );
  return $locked_fields;
}

/**
 * Implements hook_form_FORMID_alter().
 *
 * Disable deletion of required advocacy webform fields.
 */
function sba_message_action_form_webform_component_delete_form_alter(&$form, &$form_state, $form_id) {
  if ($form['node']['#value']->type == 'sba_message_action') {
    sba_message_action_prevent_component_delete($form, $form_state);
  }
}

/**
 * Implements hook_form_webform_component_edit_form_alter().
 *
 * Disable form-key editing and un-mandatory of certain profile fields.
 */
function sba_message_action_form_webform_component_edit_form_alter(&$form, &$form_state, $form_id) {
  $node = node_load($form['nid']['#value']);
  if ($node->type == 'sba_message_action') {
    sba_message_action_component_edit_lock($form);
  }
}