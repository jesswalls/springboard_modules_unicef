<?php
/**
 * @file
 * Plugin for AddThis email feature.
 */

$plugin = array(
  'name' => 'email',
  'title' => t('Email'),
  'settings' => 'sb_social_email_settings',
  'admin_settings' => 'sb_social_email_admin_settings',
  'admin_setings_submit' => 'sb_social_email_admin_settings_submit',
  'process' => 'sb_social_email_process_settings',
  'share_config' => 'sb_social_email_share_js_config',
  'js' => 'plugins/social_networks/email/email.share.js',
  'defaults' => 'sb_social_email_defaults',
  'button_extra' => 'sb_social_email_button_extra',
  'button_contents' => sb_social_email_custom_button_contents(),
  'uninstall' => 'sb_social_email_uninstall',
  'token_info' => sb_social_email_token_info(),
  'token_replace' => 'sb_social_email_token_replace',
);


function sb_social_email_token_info() {
  $email_tokens = array();
  $email_tokens['email_share_link'] = array(
    'name' => t('Email share link'),
    'description' => t('AddThis Email link'),
  );
  $email_tokens['email_subject'] = array(
    'name' => t('Email subject'),
    'description' => t('Share email subject'),
  );
  $email_tokens['email_message'] = array(
    'name' => t('Email message'),
    'description' => t('Share email message'),
  );


  return $email_tokens;
}

function sb_social_email_token_replace($tokens, &$replacements, $settings, $node = FALSE, $submission_id = FALSE, $extra = FALSE) {
  foreach ($tokens as $key => $token) {
    switch ($key) {
      case 'email_share_link':
        $vars['service'] = 'email';
        $vars['extra'] = sb_social_email_button_extra($settings['data']['email'], $node, $submission_id);
        $vars['contents'] = sb_social_email_custom_button_contents();
        $button = theme('sb_social_share_button', $vars);
        $replacements[$token] = theme('sb_social_share', array('buttons' => $button));
        break;
      case 'email_subject':
        $replacements[$token] = !empty($settings['data']['email']['subject']) ? _sb_social_replace_tokens($settings['data']['email']['subject'], $node, $submission_id) : '';
        break;
      case 'email_message':
        $replacements[$token] = !empty($settings['data']['email']['message']) ? _sb_social_replace_tokens($settings['data']['email']['message'], $node, $submission_id) : '';
        break;
    }
  }
}

function sb_social_email_defaults() {
  $settings = array(
    'subject' => variable_get('springboard_social_email_subject', '%title'),
    'message' => variable_get('springboard_social_email_message' . ''),
  );
  return $settings;
}

function sb_social_email_settings(&$form, $enabled_services = array(), $settings = array(), $token_set = array('all')) {
  $form['email_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Email Settings'),
    '#access' => in_array('email', $enabled_services),
    '#collapsible' => TRUE,
  );
  $form['email_settings']['email_subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Email subject'),
    '#default_value' => isset($settings['subject']) ? $settings['subject'] : '',
  );
  $form['email_settings']['email_message'] = array(
    '#type' => 'textarea',
    '#title' => t('Email message'),
    '#default_value' => isset($settings['message']) ? $settings['message'] : '',
  );
  $form['email_settings']['tokens'] = array(
    '#type' => 'fieldset',
    '#title' => t('Available Tokens'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['email_settings']['tokens']['token_help'] = array(
    '#type' => 'item',
    '#title' => t('Drupal tokens'),
    '#description' => theme('token_tree', array('token_types' => $token_set, 'recursion_limit' => 2, 'click_insert' => FALSE)),
  );
}

function sb_social_email_admin_settings(&$form) {
  $form['services']['email'] = array(
    '#type' => 'fieldset',
    '#title' => t('Email Settings'),
    '#states' => array(
      // Hide the settings when facebook checkbox is not selected.
      'invisible' => array(
        ':input[name="springboard_social_services[email]"]' => array('checked' => FALSE),
      ),
    ),
  );
  $form['services']['email']['icon'] = array(
    '#type' => 'fieldset',
    '#title' => t('Custom icon settings'),
  );
  $form['services']['email']['icon']['springboard_social_email_custom_text'] = array(
    '#type' => 'textfield',
    '#title' => t('Custom icon text'),
    '#default_value' => variable_get('springboard_social_email_custom_text', ''),
  );
  $form['services']['email']['icon']['springboard_social_email_custom_icon'] = array(
    '#type' => 'managed_file',
    '#title' => t('Upload custom icon'),
    '#description' => t('Custom share icon'),
    '#default_value' => variable_get('springboard_social_email_custom_icon', ''),
    '#upload_location' => 'public://social_images',
    '#upload_validators' => array(
      'file_validate_extensions' => array('gif png jpg jpeg'),
    ),
    '#theme' => 'sb_social_share_image_preview',
  );

  $form['services']['email']['springboard_social_email_subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Email subject'),
    '#default_value' => variable_get('springboard_social_email_subject', '%title'),
  );
  $form['services']['email']['springboard_social_email_message'] = array(
    '#type' => 'textarea',
    '#title' => t('Email message'),
    '#default_value' => variable_get('springboard_social_email_message', ''),
  );
}

function sb_social_email_admin_settings_submit($form, $form_state) {
  if ($form_state['values']['springboard_social_email_custom_icon']) {
    $value = $form_state['values']['springboard_social_email_custom_icon'];
    $file = file_load($value);
    if ($file && !$file->status) {
      $file->status = FILE_STATUS_PERMANENT;
      file_save($file);
      file_usage_add($file, 'sb_social', 'email_icon', 1);
    }
  }
}

function sb_social_email_process_settings(&$data, $form_state) {
  $data['email'] = array(
    'subject' => !empty($form_state['values']['email_subject']) ? $form_state['values']['email_subject'] : '',
    'message' => !empty($form_state['values']['email_message']) ? $form_state['values']['email_message'] : '',
  );
}

function sb_social_email_share_js_config($settings, $node = FALSE, $sid = FALSE) {
  $settings = array(
    'email_subject' => _sb_social_replace_tokens($settings['data']['email']['subject'], $node, $sid),
    'email_message' => _sb_social_replace_tokens($settings['data']['email']['message'], $node, $sid),
  );
  drupal_add_js(array('sb_social' => $settings), 'setting');
}

function sb_social_email_uninstall() {
  variable_del('springboard_social_email_subject');
  variable_del('springboard_social_email_message');
}

// undocumented little hack to set the email subject to a value we control.
// by setting the title attribute in the link we override AddThis' default behavior which
// is pulling in the <title></title> contents as the email subject.
function sb_social_email_button_extra($settings, $node = FALSE, $submission_id = FALSE) {
   return 'addthis:title="' . _sb_social_replace_tokens($settings['subject'], $node, $submission_id) . '"';
}

function sb_social_email_custom_button_contents() {
  $contents = '';
  $icon = variable_get('springboard_social_email_custom_icon', '');
  $text = variable_get('springboard_social_email_custom_text', '');
  if (!empty($icon)) {
    $icon_file = file_load($icon);
    if (isset($icon_file->uri)) {
      $url = file_create_url($icon_file->uri);
      $contents .= '<img src="' . $url . '">';
    }
  }
  if ($text) {
    $contents .= '<span>' . $text . '</span>';
  }
  return $contents;
}
