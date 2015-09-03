<?php

/**
 * @file
 * Install helper functions for example nodes.
 */

/**
 * Create the example message action node.
 */
function _sba_message_action_create_example_message_action() {
  $node = new stdClass();
  $node->is_new = 1;
  $node->type = 'sba_message_action';
  $node->language = LANGUAGE_NONE;
  $node->uid = 1;
  $node->title = 'Example Message Action Form';
  $node->status = 1;
  $node->promote = 0;
  $node->body[LANGUAGE_NONE][0]['value'] = 'Donec placerat. Nullam nibh dolor, blandit sed, fermentum id, ' .
    'imperdiet sit amet, neque. Nam mollis ultrices justo. Sed tempor. Sed vitae tellus. Etiam sem arcu, eleifend ' .
    'sit amet, gravida eget, porta at, wisi. Nam non lacus vitae ipsum viverra pretium. Phasellus massa. Fusce ' .
    'magna sem, gravida in, feugiat ac, molestie eget, wisi. Fusce consectetuer luctus ipsum. Vestibulum nunc. ' .
    'Suspendisse dignissim adipiscing libero. Integer leo. Sed pharetra ligula a dui. Quisque ipsum nibh, ullamcorper ' .
    'eget, pulvinar sed, posuere vitae, nulla. Sed varius nibh ut lacus. Curabitur fringilla. Nunc est ipsum, ' .
    'pretium quis, dapibus sed, varius non, lectus. Proin a quam. Praesent lacinia, eros quis aliquam porttitor, ' .
    'urna lacus volutpat urna, ut fermentum neque mi egestas dolor.';
  $node->body[LANGUAGE_NONE][0]['summary'] = 'Donec placerat. Nullam nibh dolor, blandit sed, fermentum id, imperdiet ' .
    'sit amet, neque. Nam mollis ultrices justo. Sed tempor. Sed vitae tellus. Etiam sem arcu, eleifend sit amet, ' .
    'gravida eget, porta at, wisi. Nam non lacus vitae ipsum viverra pretium. Phasellus massa. Fusce magna sem, gravida ' .
    'in, feugiat ac, molestie eget, wisi.';
  $node->body[LANGUAGE_NONE][0]['format'] = 'filtered_html';
  $node->webform = array(
    'confirmation' => 'Thank you, %value[sbp_first_name] for participating in the messaging campaign. [action:all_messages]',
    'confirmation_format' => 'filtered_html',
    'redirect_url' => '<confirmation>',
    'teaser' => 0,
    'block' => 0,
    'allow_draft' => 0,
    'auto_save' => 0,
    'submit_notice' => 1,
    'submit_text' => t('Sign'),
    'submit_limit' => -1,
    'submit_interval' => -1,
    'total_submit_limit' => -1,
    'total_submit_interval' => -1,
    'status' => 1,
    'record_exists' => '',
    'roles' => array(
      '0' => 1,
      '1' => 2,
    ),
    'emails' => array(),
    'components' => array(),
  );
  $email_nid = sba_message_action_email_wrapper_add();
  if ($email_nid != NULL) {
    $node->webform['emails'][1] = array(
      'email' => '',
      'template' => 'default',
      'subject' => 'Thank you for your participation!',
      'from_name' => 'Springboard',
      'from_address' => 'example-from@example.com',
      'html' => 0,
      'attachments' => 0,
      'excluded_components' => array(),
    );
  }
  $node->is_webform_user = 1;
  $node->field_webform_user_internal_name[LANGUAGE_NONE][0]['value'] = "Example Message Action Form";
  if (module_exists('form_layouts')) {
    $node->form_layouts = 'two_column_message_left_vertical';
  }
  $node->send_new_user_email = 0;
  node_save($node);
  $node = node_load($node->nid);

  // Save confirmation details.
  $confirmation['nid'] = $node->nid;
  $confirmation['confirmation_page_title'] = 'Thank you for your participation!';
  _webform_confirmations_update($confirmation);
  // Save email wrapper details.
  foreach ($node->webform['components'] as $component) {
    if ($component['form_key'] == 'mail') {
      $cid = $component['cid'];
      $node->webform['emails'][1]['email'] = $cid;
    }
  }
  if ($email_nid != NULL) {
    $settings = array(
      'nid' => $node->nid,
      'eid' => 1,
      'tid' => $email_nid,
      'bcc_email' => '',
      'html_message' => 'Thank you for your participation!',
      'html_message_format' => 'filtered_html',
      'text_message' => 'Thank you for your participation!',
      'extra' => serialize(array()),
    );
  }
  // One last save.
  node_save($node);
  email_wrappers_save_settings($node->nid, 1, $settings);
  drupal_set_message(t('An example message to target form has been created.'));
}

/**
 * Create an email wrapper for the message action.
 */
function sba_message_action_email_wrapper_add() {
  $node = new stdClass();
  $node->is_new = 1;
  $node->type = 'email_wrapper';
  $node->language = LANGUAGE_NONE;
  $node->uid = 1;
  $node->title = 'Example Message Action Email Wrapper';
  $node->status = 0;
  $node->promote = 0;
  $node->email_wrapper_from_name[LANGUAGE_NONE][0] = array(
    'value' => 'Springboard',
    'format' => '',
    'safe_value' => 'Springboard',
  );
  $node->email_wrapper_from_email[LANGUAGE_NONE][0] = array(
    'value' => 'example-from@example.com',
    'format' => '',
    'safe_value' => 'example-from@example.com',
  );
  $node->email_wrapper_reply_email[LANGUAGE_NONE][0] = array(
    'value' => 'example-to@example.com',
    'format' => '',
    'safe_value' => 'example-to@example.com',
  );
  $node->email_wrapper_subject[LANGUAGE_NONE][0] = array(
    'value' => 'Thank you for your participation!',
    'format' => '',
    'safe_value' => 'Thank you for your participation!',
  );
  $node->email_wrapper_html_template[LANGUAGE_NONE][0] = array(
    'value' => 'Thank you for your participation!' . "\n" .
      "\n" .
      '%html_message' . "\n" .
      "\n" .
      '-----' . "\n" .
      'Springboard Example',
    'summary' => '',
    'format' => 'filtered_html',
    'safe_value' => '<p>Thank you for your participation!</p>' . "\n" .
      '<p>%html_message</p>' . "\n" .
      '<p>-----<br>' . "\n" .
      'Springboard Example</p>',
  );
  $node->email_wrapper_html_message[LANGUAGE_NONE][0] = array(
    'value' => 'Please visit us again soon.',
    'summary' => '',
    'format' => 'filtered_html',
    'safe_value' => '<p>Please visit us again soon.</p>',
  );
  $node->email_wrapper_text_template[LANGUAGE_NONE][0] = array(
    'value' => 'Thank you for your participation!' . "\n" .
      "\n" .
      '%text_message' . "\n" .
      "\n" .
      '-----' . "\n" .
      'Springboard Example',
    'format' => '',
    'safe_value' => 'Thank you for your participation!' . "\n" .
      "\n" .
      '%text_message' . "\n" .
      "\n" .
      '-----' . "\n" .
      'Springboard Example',
  );
  $node->email_wrapper_text_message[LANGUAGE_NONE][0] = array(
    'value' => 'Please visit us again soon.',
    'format' => 'filtered_html',
    'safe_value' => '<p>Please visit us again soon.</p>',
  );
  node_save($node);
  // Save extras.
  drupal_set_message(t('An example message to target email wrapper has been created.'));
  return $node->nid;
}