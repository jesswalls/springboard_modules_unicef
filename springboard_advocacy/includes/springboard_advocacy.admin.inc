<?php

/**
 * @file
 * Admin functions for Springboard advocacy.
 */

/**
 * Page callback for the admin form.
 */

function springboard_advocacy_settings_page() {
  $build = array();
  $build['content'] = array(
    'page_description' => array(
      '#id' => 'springboard-advocacy-settings-page',
      '#type' => 'markup',
      '#markup' => '<p>' . t('Configure settings for Springboard advocacy.') .
        '</p><p>' .
        t('Saving this form will also force a rebuild of the advocacy subscription settings and renew the Oauth Access Token.') .
        '</p>',
      '#prefix' => '<div class="springboard-advocacy-settings-page">',
      '#suffix' => '</div>',
    ),
    'springboard_advocacy_settings_form' => drupal_get_form('springboard_advocacy_settings_form'),
  );
  return $build;
}

/**
 * Configuration settings form for Springboard advocacy.
 */
function springboard_advocacy_settings_form() {
  $form = array();

  $form['springboard_advocacy_debug'] = array(
    '#title' => t('Debug mode'),
    '#description' => t('Log extensive debug info to watchdog. Not recommended for production sites.'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('springboard_advocacy_debug', ''),
  );

  $form['transaction'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advocacy Server Configuration'),
  );

  $form['transaction']['springboard_advocacy_server_url'] = array(
    '#title' => t('Springboard advocacy server url'),
    '#description' => t('The url of the Springboard advocacy server. Use "https" for the gospringboard.io servers.'),
    '#type' => 'textfield',
    '#default_value' => variable_get('springboard_advocacy_server_url', ''),
    '#required' => TRUE,
    '#element_validate' => array('springboard_advocacy_url_validate'),

  );

  $form['transaction']['springboard_advocacy_client_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Transaction server Oauth Client ID.'),
    '#description' => t('Client ID for legislator lookup'),
    '#default_value' => variable_get('springboard_advocacy_client_id', ''),
    '#required' => TRUE,
  );

  $form['transaction']['springboard_advocacy_client_secret'] = array(
    '#type' => 'textfield',
    '#title' => t('Transaction server Oauth Client Secret.'),
    '#description' => t('Client Secret for legislator lookup'),
    '#default_value' => variable_get('springboard_advocacy_client_secret', ''),
    '#required' => TRUE,
  );

  $form['geo'] = array(
    '#type' => 'fieldset',
    '#title' => t('Geocoding configuration'),
  );

  $form['geo']['springboard_advocacy_geocoder'] = array(
    '#type' => 'hidden',
    '#value' => 'smartystreets_rest',
  );

  $form['geo']['smarty'] = array(
    '#type' => 'fieldset',
    '#title' => t('Smarty Streets configuration'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['geo']['smarty']['springboard_advocacy_smarty_authid'] = array(
    '#type' => 'textfield',
    '#title' => t('Smarty Streets Auth ID'),
    '#description' => t('Required for the REST API'),
    '#default_value' => variable_get('springboard_advocacy_smarty_authid', ''),
    '#required' => TRUE,
  );

  $form['geo']['smarty']['springboard_advocacy_smarty_authtoken'] = array(
    '#type' => 'textfield',
    '#title' => t('Smarty Streets Auth Token'),
    '#description' => t('Required for the REST API'),
    '#default_value' => variable_get('springboard_advocacy_smarty_authtoken', ''),
    '#required' => TRUE,
  );

  return system_settings_form($form);
}

function springboard_advocacy_url_validate($element, &$form_state) {

  if (!valid_url($form_state['values']['springboard_advocacy_server_url'], TRUE)) {
    form_error($element, t('You must enter a valid, fully-prefixed absolute url.'));
  }

  $non_local = strpos($form_state['values']['springboard_advocacy_server_url'], 'gospringboard.io');
  $https = strpos($form_state['values']['springboard_advocacy_server_url'], 'https');

  if ($non_local !== FALSE && $https === FALSE) {
    form_error($element, t('You must use an "https" prefix when connecting to the gospringboard.io server.'));
  }
}