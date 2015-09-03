<?php

/**
 * Add a "failure message" textarea to confirmation form admin page.
 *
 * If there are no deliverable messages, this message will be used.
 * Called from sba_message_action_form_webform_configure_form_alter().
 *
 * @param $form
 * @param $form_state
 */
function sba_message_action_confirmation(&$form, &$form_state) {
  $form['submission']['confirmation']['#weight'] = -2;
  // Does this node have a custom confirmation record?
  $custom_status = isset($form['#node']->custom_confirmation) ? $form['#node']->custom_confirmation : 0;

  $form['submission']['confirmation_fail'] = array(
    '#type' => 'fieldset',
    '#weight' => -1,
    '#tree' => FALSE,
    '#prefix' => '<div id="confirmation-div">',
    '#suffix' => '</div>',
  );

  // Add the ajax-enabled custom confirmation checkbox with a default value.
  $form['submission']['confirmation_fail']['custom_confirmation'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use custom failure message'),
    '#weight' => 6,
    '#default_value' => $custom_status,
    '#ajax' => array(
      'callback' => 'sba_message_action_form_webform_configure_callback',
      'wrapper' => 'confirmation-div',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  if ($custom_status == 1) {
    $default = $form['#node']->custom_fail_message;
  }
  else {
    $default = variable_get('sba_message_action_confirm', '');
  }
  // Alter the confirmation textarea to have an ajax wrapper
  // and drupal_process_states array.
  $form['submission']['confirmation_fail']['fail_message'] = array(
    '#type' => 'textarea',
    '#title' => 'Confirmation failure message',
    '#prefix' => '<p>Message to be shown to the user if the action has no valid recipients.</p>',
    '#default_value' => $default,
    '#rows' => 10,
    '#cols' => 60,
    '#states' => array(
      'disabled' => array(
        ':input[name="confirmation_fail[custom_confirmation]"]' => array('checked' => FALSE),
      ),
    ),
  );

  // Intercept the Ajax reload and change the confirmation
  // message value according to confirmation status.
  $new_custom_status = isset($form_state['values']['custom_confirmation']) ? $form_state['values']['custom_confirmation'] : NULL;
  if ($new_custom_status === 1) {
    // Value does not get reset without this.
    unset($form_state['input']['fail_message']);
    // Use custom message is enabled so use the local node's
    // confirmation message.

    $form['submission']['confirmation_fail']['fail_message']['#default_value'] = $form['#node']->custom_fail_message;
  }
  elseif ($new_custom_status === 0) {
    unset($form_state['input']['fail_message']);
    // Use custom message is disabled so use the global confirmation message.
    $form['submission']['confirmation_fail']['fail_message']['#default_value'] = variable_get('sba_message_action_confirm', '');
  }

  // Add a custom submit function to save the confirmation status value.
  $form['#submit'][] = 'sba_message_action_confirmation_submit';

  // Need this to alter the filter format box.
  $form['#after_build'][] = 'sba_message_action_configure_form_after_build';
}


/**
 * Some onerous form manipulations.
 *
 * In order to get the webform confirmation failure
 * message form to display nicely in the admin form.
 *
 * @param $element
 *   The form.
 *
 * @return mixed
 */
function sba_message_action_configure_form_after_build($element) {
  $element['submission']['confirmation']['format']['#collapsible'] = TRUE;
  $element['submission']['confirmation']['format']['#collapsed'] = TRUE;
  $element['submission']['confirmation']['format']['#attached']['library'][]
    = array('system', 'drupal.collapse');
  $element['submission']['confirmation']['format']['#title'] = 'Text Format';
  $element['submission']['confirmation']['format']['#weight'] = 20;
  $element['submission']['confirmation']['format']['#attributes']['class'][] = 'collapsible';
  $element['submission']['confirmation']['format']['#attributes']['class'][] = 'collapsed';
  $element['submission']['confirmation']['value']['#title'] = 'Confirmation success message';
  $element['submission']['confirmation']['value']['#description']
    = $element['submission']['confirmation']['#description'];
  unset($element['submission']['confirmation']['#description']);
  return $element;
}


/**
 * Ajax callback.
 *
 * For webform confirmation field which has been altered above
 * to be an ajax field.
 *
 * @param $form
 * @param $form_state
 *
 * @return mixed
 */
function sba_message_action_form_webform_configure_callback($form, $form_state) {
 // form_load_include($form_state, 'inc', 'sba_message_action', 'includes/sba_message_action.confirmations');
  return $form['submission']['confirmation_fail'];
}

/**
 * Submit callback for webform settings page.
 *
 * If this form has a custom confirmation overriding the
 * global confirmation, save a record registering that status.
 *
 * @param $form
 * @param $form_state
 */
function sba_message_action_confirmation_submit($form, $form_state) {
  if (isset($form_state['values']['custom_confirmation'])) {
    $record = array(
      'nid' => $form['#node']->nid,
      'custom_confirmation' => $form_state['values']['custom_confirmation'],
      'fail_message' => $form_state['values']['fail_message'],

    );
    if (isset($form['#node']->custom_confirmation)) {
      drupal_write_record('sba_message_action_confirm', $record, 'nid');
    }
    else {
      drupal_write_record('sba_message_action_confirm', $record);
    }
  }
}

