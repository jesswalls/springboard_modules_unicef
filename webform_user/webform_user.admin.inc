<?php

/**
 * @file
 * Provides an admin interface for the Webform User module.
 */

/**
 * Callback function for the admin settings menu item.
 *
 * @return array
 *   Returns a system_settings_form() formatted Form API array.
 */
function webform_user_admin_settings_form($form, &$form_state) {
  $form = array();
  $form['webform_user_session_store'] = array(
    '#type' => 'checkbox',
    '#title' => t('Store user submitted values in session?'),
    '#description' => t('Enable this checkbox if webform user should store submitted values in the user\'s session for all webform user enabled content types.'),
    '#default_value' => variable_get('webform_user_session_store', 0),
  );
  return system_settings_form($form);
}