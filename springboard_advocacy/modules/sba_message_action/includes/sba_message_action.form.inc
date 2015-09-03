<?php

/**
 * @file
 * Helper functions for building message action client forms.
 */

/**
 * Message action webform alterations.
 *
 * Add the message entities to the action webform node view.
 * Attach CSS and JS to Action nodes.
 * If it's a multiple message action, attach the ctools modal view of them.
 * Define custom submit and validate hooks.
 *
 * @param $form
 * @param $form_state
 */
function sba_message_action_additional_elements(&$form, &$form_state) {
  // Override core's theme_form in order to remove <form> tag
  // and use it in a template variable defined in
  // sba_message_action_build_preprocess and
  // theme_message_action_form_layout_form
  if (!empty($form['#theme_wrappers']) && !empty($form['#node']->form_layouts)) {
    foreach ($form['#theme_wrappers'] as $key => $wrapper) {
      if ($wrapper == 'form') {
        unset($form['#theme_wrappers'][$key]);
      }
    }
    $form['#theme_wrappers'][] = array('message_action_form_layout_form');
  }

  // Attach the JS and CSS.
  $form['#attached']['js'][] = drupal_get_path('module', 'sba_message_action')
    . '/js/sba_message_action.js';
  $form['#attached']['css'][] = drupal_get_path('module', 'sba_message_action')
    . '/css/message-modal.css';

  // Is form layouts enabled?
  if (!empty($form['#node']->form_layouts)) {
    $form['#attached']['css'][] = drupal_get_path('module', 'sba_message_action')
      . '/css/message-action-form-layouts.css';
  }
  else {
    $form['#attached']['css'][] = drupal_get_path('module', 'sba_message_action')
      . '/css/no-form-layouts.css';
  }

  $form['smarty_geo'] = array(
    '#type' => 'value',
    '#value' => '',
  );

  $form['webform_flat'] = array(
    '#type' => 'value',
    '#value' => array(),
  );

  // Create a container on the form for all messages.
  $form['sba_messages'] = array(
    '#type' => 'container',
    '#tree' => TRUE,
    '#attributes' => array(
      'id' => array('sba-messages-form'),
    ),
  );

  // Multiple messages for this form?
  $multiple = count($form['#node']->messages) > 1 ? TRUE : FALSE;

  if ($multiple) {
    ctools_include('ajax');
    ctools_include('modal');
    $href = 'messages/nojs/' . arg(1);
    $form['sba_messages']['multiple'] = array(
      '#type' => 'fieldset',
      '#title' => t('Your Message'),
      '#attributes' => array('class' => array('sba-message')),
    );
    $form['sba_messages']['multiple']['message'] = array(
      '#type' => 'item',
      '#markup' => '<p>' . t('We have crafted multiple messages for this action. We will select the right message or messages for your legislators, or others we are targeting, based on their position on this issue, and on the address you enter.')
        . '</p><p></p>' . ctools_modal_text_button('View all possible messages.', $href, t('View messages'), 'ctools-modal-message-window-style') . '</p>',
    );
  }

  // Create a set of fields for each message assigned to the form.
  foreach ($form['#node']->messages as $message) {
    sba_message_action_message_form($form['sba_messages'], $message, $multiple);
  }

  $form['#validate'][] = 'sba_message_action_form_validate';
  array_unshift($form['#submit'], 'sba_message_action_form_submit');
}

/**
 * Build a form to represent each message attached to the action webform node.
 *
 * @param array $form
 *   The webform client form.
 * @param object $message
 *   The message entity.
 * @param bool $multiple
 *    Whether this webform has multiple messages.
 */
function sba_message_action_message_form(&$form, $message, $multiple) {

  // Get some message values via an entity wrapper.
  $wrapper = entity_metadata_wrapper('sba_message', $message);
  $subject = $wrapper->field_sba_subject->value();
  $message_body = check_markup($wrapper->field_sba_message->value(), 'plain_text');
  $editable_message = $wrapper->field_sba_editable_area->value();
  $body_editable = $wrapper->field_sba_user_editable[0]->value() == 'editable' ? TRUE : FALSE;
  $required_body = $wrapper->field_sba_editable_area_optional[0]->value() == 'required' ? TRUE : FALSE;
  $placeholder_greeting = check_plain($wrapper->field_sba_placeholder_greeting->value());
  $greeting = check_plain($wrapper->field_sba_greeting->value());
  $conclusion = check_markup($wrapper->field_sba_bottom_conclusion->value(), 'plain_text');
  $subject_editable =  $wrapper->field_sba_subject_editable->value();

  // If it's a multiple message form, use a container instead of a fieldset.
  if (!$multiple) {
    $form['message'][$message->sba_message_id] = array(
      '#type' => 'fieldset',
      '#title' => t('Your Message'),
      '#attributes' => array('class' => array('sba-message')),
    );
  }
  else {
    $form['message'][$message->sba_message_id] = array(
      '#type' => 'container',
      '#attributes' => array('class' => array('sba-message')),
    );
  }

  $form['message'][$message->sba_message_id]['message_id'] = array(
    '#type' => 'value',
    '#value' => $message->data['message_id'],
  );

  $form['message'][$message->sba_message_id]['sba_message_id'] = array(
    '#type' => 'value',
    '#value' => $message->sba_message_id,
  );
  // The subject is editable.
  if ($subject_editable != 'Not editable') {

    // Is it required to edit the subject?
    if ($subject_editable == 'Editing is required') {
      $description = t('You must edit the subject line of this message before sending.');

      // Validator needs this value?
      $form['message'][$message->sba_message_id]['subject_required'] = array(
        '#type' => 'value',
        '#value' => 1,
      );
    }

    $form['message'][$message->sba_message_id]['subject'] = array(
      '#type' => 'textfield',
      '#title' => t('Subject'),
      '#default_value' => $subject,
      '#description' => !empty($description) ? $description : '',
    );
  }
  // The subject is not editable.
  else {
    // Show the non-editable subject if there aren't multiple messages.
    if (!$multiple) {
      $form['message'][$message->sba_message_id]['subject_show'] = array(
        '#type' => 'item',
        '#title' => t('Subject'),
        '#markup' => check_plain($subject),
      );
    }

    // The subject value field is present in either case.
    // The value here is eventually passed to the API server.
    $form['message'][$message->sba_message_id]['subject'] = array(
      '#type' => 'value',
      '#value' => $subject,
    );
  }

  // Show the greeting field is there aren't multiple messages.
  if (!$multiple) {
    $form['message'][$message->sba_message_id]['greeting_show'] = array(
      '#type' => 'item',
      '#title' => '',
      '#markup' => $placeholder_greeting,
    );
  }

  // The greeting value field is present in either case.
  // The value here is eventually passed to the API server.
  $form['message'][$message->sba_message_id]['greeting'] = array(
    '#type' => 'value',
    '#value' => $greeting,
  );

  // The body value field is present in either case.
  // The value here is eventually passed to the API server.
  $form['message'][$message->sba_message_id]['body'] = array(
    '#type' => 'value',
    '#value' => $message_body,
  );

  // If not multiple we show the message body.
  if (!empty($message_body) && !$multiple) {

    // If the message body is editable, suppress the field title.
    if ($body_editable) {
      $title = '';
    }
    else {
      $title = t('Message');
    }

    $form['message'][$message->sba_message_id]['body_show'] = array(
      '#type' => 'item',
      '#title' => $title,
      '#markup' => $message_body,
    );
  }

  if ($body_editable == 'editable' && !$multiple) {

    if ($required_body) {
      $description = t('You must edit the body of this message before sending.');
      $required = TRUE;
    }
    else {
      $description = '';
      $required = FALSE;
    }

    $form['message'][$message->sba_message_id]['edited_body'] = array(
      '#type' => 'textarea',
      '#default_value' => $editable_message,
      '#description' => $description,
      '#required' => $required,
    );

    $form['message'][$message->sba_message_id]['body_required'] = array(
      '#type' => 'value',
      '#value' => $required_body,
    );

    if (!empty($conclusion)) {
      $form['message'][$message->sba_message_id]['body_bottom'] = array(
        '#type' => 'item',
        '#markup' => $conclusion,
      );
    }
  }

  // Format the signature display.
  if (!$multiple) {
    $sig = strip_tags($wrapper->field_sba_signature->value());
    $sig = str_replace('[contact:first_name]', '[First Name]', $sig);
    $sig = str_replace('[contact:last_name]', '[Last Name]', $sig);
    $sig = str_replace('[contact:address]', '[Your Addess]', $sig);
    $form['message'][$message->sba_message_id]['signature'] = array(
      '#markup' => check_markup($sig, 'plain_text'),
    );
  }
}


/**
 * Validation handler for message action forms.
 *
 * Checks whether editing of subject or body is required.
 * Calls Smarty Streets API and injects response values into form state.
 * Flattens the webform submission tree and injects flattened values into
 * form state for use by the message sending functions
 * in sba_message_action.webform.inc
 *
 * @param $form
 * @param $form_state
 */
function sba_message_action_form_validate($form, &$form_state) {

  if (isset($form_state['values']['sba_messages'])) {
    $is_single = count($form_state['values']['sba_messages']['message']) == 1 ? TRUE : FALSE;
  }
  if (!empty($is_single)) {
    $child_messages = element_children($form['sba_messages']['message']);
    $message_id = reset($child_messages);
    $message = $form['sba_messages']['message'][$message_id];
    $body_default = isset($message['edited_body']['#default_value']) ? $message['edited_body']['#default_value'] : '';
    $body_edited = isset($form_state['values']['sba_messages']['message'][$message_id]['edited_body']) ? $form_state['values']['sba_messages']['message'][$message_id]['edited_body'] : '';
    $subject_default = isset($message['subject']['#default_value']) ? $message['subject']['#default_value'] : '';
    $subject_edited = isset($form_state['values']['sba_messages']['message'][$message_id]['subject']) ? $form_state['values']['sba_messages']['message'][$message_id]['subject'] : '';
    $changed = FALSE;
    // Enforce mandatory editing.
    if ($body_edited == $body_default && isset($message['body_required']) && $message['body_required']['#value'] == 1) {
        form_set_error('body_editable', t('Please personalize your message before sending.'));
    }
    elseif ($body_edited != $body_default) {
      $changed = TRUE;
    }
    if ($subject_edited == $subject_default && isset($message['subject_required']) && $message['subject_required']['#value'] == 1) {
        form_set_error('subject', t('Please personalize the subject line before sending your message.'));
    }
    elseif (!isset($message['subject_show']) && $subject_edited != $subject_default) {
      $changed = TRUE;
    }
    // Set user_edited_flag
    if ($changed && isset($form['submitted']['sba_user_edit_flag'])) {
      form_set_value($form['submitted']['sba_user_edit_flag'], 1, $form_state);
    }
  }
  form_load_include($form_state, 'inc', 'springboard_advocacy', 'includes/springboard_advocacy.smarty_streets');
  $webform_values_flat = _springboard_advocacy_webform_submission_flatten($form['#node']->nid, $form_state['values']['submitted']);
  form_set_value($form['webform_flat'], $webform_values_flat, $form_state);
  $smarty_geo = springboard_advocacy_smarty_lookup($webform_values_flat);
  if (!empty($smarty_geo) && is_array($smarty_geo)) {
    form_set_value($form['smarty_geo'], $smarty_geo, $form_state);
    if (isset($smarty_geo['zip']) && isset($smarty_geo['plus4'])) {
      form_set_value($form['submitted']['sbp_zip_plus_four'], $smarty_geo['zip'] . '-' . $smarty_geo['plus4'], $form_state);
    }
  }
  else {
    form_set_error('', t('We could not verify your address. Please check that the street, city, state and zip code information is correct.'));
  }
}

/**
 * Submit handler for message action forms.
 *
 * Capture all messages, combine with contact information and
 * submit to API.
 *
 * @param $form
 * @param $form_state
 */
function sba_message_action_form_submit($form, &$form_state) {
  $_SESSION['delivered_messages'] = array();
  $_SESSION['undelivered_messages'] = array();
  // Create array of messages to submit for target resolution.
  if (isset($form_state['values']['sba_messages'])) {
    $messages = array();
    foreach ($form_state['values']['sba_messages']['message'] as $id => $message) {
      $edited_body = isset($message['edited_body']) ? $message['edited_body'] : '';
      $messages[$id]['body'] = sba_message_action_build_message_bodies($message['sba_message_id'], $edited_body);
      $messages[$id]['subject'] = $message['subject'];
    }
    form_load_include($form_state, 'inc', 'sba_message_action', 'includes/sba_message_action.webform');
    $data = sba_message_action_send_message($messages, $form_state);
    // Calculate the deliverable count for sending to salesforce
    if (!empty($data->messages)) {
      $deliverable = 0;
      foreach ($data->messages as $key => $message) {
        $deliverable += count($message->deliverable);
      }
      if (isset($form_state['values']['submitted']['sba_deliverable_count'])) {
        $form_state['values']['submitted']['sba_deliverable_count'] = $deliverable;
      }
    }
  }
  else {
    drupal_set_message(t('No messages were configured for this action.'));
  }
}


/**
 * Helper function to build message bodies.
 *
 * Combines user edited message data with other static properties
 * to create the final message to deliver to the transaction server.
 *
 * @param int $sba_message_id
 *   The message ID.
 * @param string $body_editable
 *    The user-editable body.
 *
 * @return string
 *   The message in string format.
 */
function sba_message_action_build_message_bodies($sba_message_id, $body_editable) {
  // Load the message entity using the message entity id. We'll use the entity
  // to construct the full message.
  $message = entity_load('sba_message', array($sba_message_id));
  $message = array_shift($message);
  $wrapper = entity_metadata_wrapper('sba_message', $message);

  $user_message = array();
  $user_message[] = $wrapper->field_sba_greeting->value();
  $user_message[] = $wrapper->field_sba_message->value();
  $user_message[] = $body_editable;
  $user_message[] = $wrapper->field_sba_bottom_conclusion->value();
  $user_message[] = $wrapper->field_sba_signature->value();
  $user_message = implode("\n\n", array_filter($user_message));

  return $user_message;
}
