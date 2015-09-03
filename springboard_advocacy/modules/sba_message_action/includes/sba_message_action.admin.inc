<?php

/**
 * Message action settings page, menu callback.
 *
 * @return array
 */
function sba_message_action_settings_page() {
  $build = array();
  $build['content'] = array(
    'page_description' => array(
      '#id' => 'message-action-settings-page',
      '#type' => 'markup',
      '#markup' => '<p>' . t('Configure confirmation settings for Message Actions.'),
      '#prefix' => '<div class="message-action-settings-page">',
      '#suffix' => '</div>',
    ),
    'springboard_advocacy_settings_form' => drupal_get_form('sba_message_action_settings_form'),
  );
  return $build;
}

/**
 * Message action settings form
 * Provides a textarea for a global confirmation message
 * and available tokens.
 * @return mixed
 */
function sba_message_action_settings_form() {

  //Create the confirmation form textarea
  $form['sba_message_action_confirm'] = array(
    '#type' => 'textarea',
    '#title' => t('Default Message Action Confirmation Failure Message'),
    '#default_value' => variable_get('sba_message_action_confirm', ''),
  );

  //Create the token fieldset
  $form['template']['tokens'] = array(
    '#type' => 'fieldset',
    '#title' => t('Available tokens'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#weight' => 9,
  );

  //Get the node tokens.
  $token_set = array('node');
  $form['template']['tokens']['tokens'] = array(
    '#type' => 'item',
    '#title' => t('Drupal tokens'),
    '#description' => theme('token_tree', array('token_types' => $token_set, 'recursion_limit' => 2, 'click_insert' => FALSE)),
  );
  // Get the webform tokens.
  $webform_token_help = theme('webform_token_help', array());
  $webform_token_help = str_replace('%post', '%value', $webform_token_help);
  $webform_token_help = str_replace('POST ', '', $webform_token_help);
  $form['template']['tokens']['webform_tokens'] = array(
    '#type' => 'item',
    '#title' => t('Webform tokens'),
    '#description' => $webform_token_help,
  );

  $form['#submit'][] = 'sba_message_action_settings_form_submit';
  return system_settings_form($form);
}


/**
 * Submit function for message action settings.
 *
 * Updates all message action nodes which do not use a custom confirmation
 * with the global confirmation.
 * @param $form
 * @param $form_state
 */
function sba_message_action_settings_form_submit($form, $form_state) {
  // Get all action node nids that do not have a custom confirmation record.
  $result = db_query('SELECT n.nid, s.custom_confirmation FROM {node} n
    LEFT JOIN {sba_message_action_confirm} s
    ON s.nid = n.nid WHERE n.type = :type && (s.custom_confirmation = 0
    OR s.nid IS NULL)', array(':type' => 'sba_message_action'));

  // Update the results with the global confirmation.
  foreach ($result as $node) {
    $record = array(
      'nid' => $node->nid,
      'fail_message' => variable_get('sba_message_action_confirm', ''),
    );
    drupal_write_record('sba_message_action_confirm', $record, 'nid');
  }
}
