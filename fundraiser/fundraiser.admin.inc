<?php

/**
 * @file
 * Administration page callbacks for the fundraiser module.
 */

/**
 * Form builder. Configure fundraiser module.
 */
function fundraiser_admin_settings($form, &$form_state) {
  $form['fundraiser'] = array(
    '#type' => 'fieldset',
    '#title' => t('Fundraiser general settings'),
    '#description' => t('Configure fundraiser settings.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['fundraiser']['fundraiser_development_mode'] = array(
    '#type' => 'checkbox',
    '#title' => t('Development mode'),
    '#default_value' => variable_get('fundraiser_development_mode', 0),
    '#description' => t('Development mode allows you to access donation forms over HTTP.'),
  );
  $form['fundraiser']['fundraiser_http_error_message'] = array(
    '#type' => 'textarea',
    '#title' => t('HTTPS error message'),
    '#default_value' => variable_get('fundraiser_http_error_message', t('We\'re sorry, but this ' .
        'donation form is experiencing a temporary problem. Please try again later.')),
    '#description' => t('The message to display to the user when a donation page is not secure and the site is ' .
      'NOT in development mode.'),
  );
  $form['fundraiser']['fundraiser_default_minimum'] = array(
    '#type' => 'textfield',
    '#title' => t('Default minimum donation amount'),
    '#default_value' => variable_get('fundraiser_default_minimum', 10.00),
    '#description' => t('Enter the default minimum donation amount that will be used on new donation forms.'),
  );
  $form['fundraiser']['fundraiser_default_amounts'] = array(
    '#type' => 'textarea',
    '#title' => t('Default ask amounts'),
    '#default_value' => variable_get('fundraiser_default_amounts', '10|$10' . "\n" . '20|$20' . "\n" . '50|$50' . "\n" . '100|$100'),
    '#description' => t('Enter the default donation ask amounts that will be used on new donation forms.'),
  );
  $form['fundraiser']['fundraiser_default_other'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use other amount by default'),
    '#default_value' => variable_get('fundraiser_default_other', TRUE),
    '#description' => t('Check this box to automatically configure donation forms to use the other amount.'),
  );
  $form['fundraiser']['fundraiser_default_quantity'] = array(
    '#type' => 'textarea',
    '#title' => t('Quantity cap'),
    '#default_value' => variable_get('fundraiser_default_quantity', '10'),
    '#description' => t('For donation forms that use the quantity field, how many should be allowed.'),
  );
  $form['fundraiser']['fundraiser_receipt_bcc'] = array(
    '#type' => 'textfield',
    '#title' => t('Donation receipt bcc email address'),
    '#default_value' => variable_get('fundraiser_receipt_bcc', ''),
    '#description' => t('The email address of the user that will receive a bcc copy of all donation receipt emails.'),
  );
  $form['fundraiser']['fundraiser_gateway_messages'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display gateway messages'),
    '#default_value' => variable_get('fundraiser_gateway_messages', 1),
    '#description' => t('When checked, the message that is returned from the payment gateway will be displayed in the Drupal status message area of the theme.'),
  );
  $form['fundraiser']['fundraiser_log_comments'] = array(
    '#type' => 'checkbox',
    '#title' => t('Log comments'),
    '#default_value' => variable_get('fundraiser_log_comments', 0),
    '#description' => t('Log comments made on donations to watchdog.'),
  );
  $form['fundraiser']['fundraiser_log_local_validation_errors'] = array(
    '#type' => 'checkbox',
    '#title' => t('Log local validation errors'),
    '#default_value' => variable_get('fundraiser_log_local_validation_errors', FALSE),
    '#description' => t('Log validation errors on donation forms to watchdog.'),
  );
  $gateways = _fundraiser_gateway_info();
  if (empty($gateways)) {
    $form['fundraiser']['fundraiser_gateway_config'] = array(
      '#markup' => '<div>' . t('There are no gateways configured to set a default configuration.') . '</div>',
    );
  }
  else {
    $fieldset = array(
      '#type' => 'fieldset',
      '#title' => t('Default Payment Method Configuration'),
      '#description' => t('Configure the default values for payment methods on the donation node forms.'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
      '#tree' => TRUE,
      '#theme' => 'fundraiser_form_payment_methods',
    );
    $configuration = variable_get('fundraiser_payment_method_config_defaults', array());
    $fieldset_name = 'fundraiser_payment_method_config_defaults';
    $form['fundraiser'][$fieldset_name] = _fundraiser_form_payment_method_config_fieldset($gateways, $configuration, $fieldset, $fieldset_name);
    $form['#validate'][] = '_fundraiser_form_payment_method_settings_validate';
  }
  return system_settings_form($form);
}

/**
 * Validate handler for our component, also sets the default value
 */
function _fundraiser_form_payment_method_settings_validate($form, &$form_state) {
  // Check the set payment methods.
  $values = $form_state['values']['fundraiser_payment_method_config_defaults'];
  $default_method = isset($values['_default']) ? $values['_default'] : '';
  $enabled_methods = array_filter($values, '_fundraiser_payment_method_array_filter_enabled');
  unset($form_state['values']['fundraiser_payment_method_config_defaults']['_default']);
  unset($enabled_methods['_default']);
  // Check that there is at least one method enabled
  if (empty($enabled_methods)) {
    form_set_error('payment_methods', t('At least one payment method must be enabled.'));
  }
  else {
    // Check that the marked payment type actually have selected gateways to match.
    foreach ($enabled_methods as $method => $enabled_method) {
      if (empty($enabled_method['id'])) {
        form_set_error('fundraiser_payment_method_config_defaults][' . $method . '][id', t('All enabled payment methods must select a gateway.'));
      }
      if (count($enabled_methods) > 1 && empty($enabled_method['label'])) {
        form_set_error('fundraiser_payment_method_config_defaults][' . $method . '][label', t('Please enter a label for the %method gateway.', array('%method' => $method)));
      }
    }
    // Check that a default has been set.
    if (!isset($enabled_methods[$default_method])) {
      if (count($enabled_methods) == 1) {
        $default_method = key($enabled_methods);
        $form_state['values']['fundraiser_payment_method_config_defaults'][$default_method]['default'] = 1;
      }
      else {
        form_set_error('fundraiser_payment_method_config_defaults][gateways][_default', t('Default method must be one of the enabled methods.'));
      }
    }
    else {
      $form_state['values']['fundraiser_payment_method_config_defaults'][$default_method]['default'] = 1;
    }
  }
}
