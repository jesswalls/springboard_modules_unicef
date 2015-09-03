<?php
/**
 * Functions for the Commerce Payflow Credit Card payment method
 */

/**
 * Payment method callback: settings form
 */
function commerce_payflow_cc_settings_form($settings = array(), $payment_method = NULL) {
  $form = array();

  // Grab the default Payflow Link settings.
  $settings += commerce_payflow_cc_default_settings();

  // Load the form from the default settings

  $form['service_description'] = array(
    '#markup' => '<div>' . commerce_payflow_service_description($payment_method['method_id']) . ' '
      . t('Your PayPal Manager login information should be used to configure these first four textfields.') . '<br /><br />'
      . t('<strong>Important:</strong> Refer to the <a href="!url" target="_blank">module documentation</a> to ensure your PayPal Manager service settings are configured properly.', array('!url' => 'http://drupal.org/node/1902734')) . '</div>',
  );

  // Add the Payflow account form fields.
  $form['partner'] = array(
    '#type' => 'textfield',
    '#title' => t('Partner'),
    '#description' => t('Either PayPal or the name of the reseller who registered your @title account.', array('@title' => $payment_method['title'])),
    '#default_value' => $settings['partner'],
    '#required' => TRUE,
  );
  $form['vendor'] = array(
    '#type' => 'textfield',
    '#title' => t('Merchant login'),
    '#description' => t('The merchant login ID you chose when you created your @title account.', array('@title' => $payment_method['title'])),
    '#default_value' => $settings['vendor'],
    '#required' => TRUE,
  );
  $form['user'] = array(
    '#type' => 'textfield',
    '#title' => t('User'),
    '#description' => t('The name of the user on the account you want to use to process transactions or the merchant login if you have not created users.'),
    '#default_value' => $settings['user'],
    '#required' => TRUE,
  );
  $form['password'] = array(
    '#type' => 'password',
    '#title' => t('Password'),
    '#description' => t('The password created for the user specified in the previous textfield.'),
    '#default_value' => $settings['password'],
    '#required' => TRUE,
  );
  $form['mode'] = array(
    '#type' => 'radios',
    '#title' => t('Processing mode'),
    '#description' => t('Either mode requires a @title account with Hosted Checkout Pages. "Enable Secure Token" must be set to "Yes" in the PayPal Manager service settings.', array('@title' => $payment_method['title'])),
    '#options' => array(
      'test' => ('Test - process test transactions to an account in test mode'),
      'live' => ('Live - process real transactions to a live account'),
    ),
    '#default_value' => $settings['mode'],
  );

  // Add the checkout and transaction option form elements.
  $form['trxtype'] = array(
    '#type' => 'radios',
    '#title' => t('Default transaction type'),
    '#options' => array(
      'S' => t('Sale - authorize and capture the funds at the time the payment is processed'),
      'A' => t('Authorization - reserve funds on the card to be captured later through your PayPal account'),
    ),
    '#default_value' => $settings['trxtype'],
  );
  $form['currency_code'] = array(
    '#type' => 'select',
    '#title' => t('Default currency'),
    '#description' => t('Transactions in other currencies will be converted to this currency, so multi-currency sites must be configured to use appropriate conversion rates.') . '<br />' . t('Note: valid currencies will differ depending on your country and processor. Check before selecting a different currency.'),
    '#options' => commerce_paypal_currencies('payflow_link'),
    '#default_value' => $settings['currency_code'],
  );

  // Add the recurring billing options select.
  $form['recurring-billing'] = array(
    '#type' => 'radios',
    '#title' => 'Recurring Billing',
    '#description' => t('Select the options for recurring billing. See Payflow documentation for further details on each option.'),
    '#options' => array(
      '' => 'None',
      'pnref-token' => t('PNREF Token (Uses previous payment tokens to make reference charges)'),
      'recurring-billing-profile' => t('Recurring Billing Profile (requires add-on service in Payflow account)'),
    ),
    '#default_value' => $settings['recurring-billing'],
  );

  $form['verbose_errors'] = array(
    '#type' => 'checkbox',
    '#title' => t('Verbose gateway errors.'),
    '#description' => t('If checked, specific error messages from the gateway will be displayed to the user.'),
    '#default_value' => isset($settings['verbose_errors']) ? $settings['verbose_errors'] : FALSE,
  );

  // Add the logging configuration form elements.
  $form['log'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Log the following messages for debugging'),
    '#options' => array(
      'request' => t('API request messages'),
      'response' => t('API response messages'),
    ),
    '#default_value' => $settings['log'],
  );

  return $form;
}

/**
 * Returns the default settings for the PayPal WPS payment method.
 */
function commerce_payflow_cc_default_settings() {
  $default_currency = commerce_default_currency();

  return array(
    'partner' => 'PayPal',
    'vendor' => '',
    'user' => '',
    'password' => '',
    'mode' => 'test',
    'trxtype' => 'S',
    'currency_code' => in_array($default_currency, array_keys(commerce_paypal_currencies('payflow_link'))) ? $default_currency : 'USD',
    'allow_supported_currencies' => FALSE,
    'recurring-billing' => '',
    'verbose_errors' => FALSE,
    'log' => array('request' => 0, 'response' => 0),
  );
}

/**
 * Payment method callback: checkout form.
 */
function commerce_payflow_cc_submit_form($payment_method, $pane_values, $checkout_pane, $order) {
  module_load_include('inc', 'commerce_payment', 'includes/commerce_payment.credit_card');
  return commerce_payment_credit_card_form(array('code' => ''));
}

/**
 * Payment method callback: checkout form validation.
 */
function commerce_payflow_cc_submit_form_validate($payment_method, $pane_form, $pane_values, $order, $form_parents = array()) {
  module_load_include('inc', 'commerce_payment', 'includes/commerce_payment.credit_card');

  // Validate the credit card fields.
  $settings = array(
    'form_parents' => array_merge($form_parents, array('credit_card')),
  );

  if (!commerce_payment_credit_card_validate($pane_values['credit_card'], $settings)) {
    return FALSE;
  }
}

/**
 * Payment method callback: checkout form submission.
 */
function commerce_payflow_cc_submit_form_submit($payment_method, $pane_form, $pane_values, $order, $charge) {
  $order_wrapper = entity_metadata_wrapper('commerce_order', $order);
  $billing_address = $order_wrapper->commerce_customer_billing->commerce_customer_address->value();

  // First check if this method has been set to use Payflow's recurring bill service
  if (!empty($pane_values['recurring']) && $payment_method['settings']['recurring-billing'] === 'recurring-billing-profile') {
    // Build a name-value pair array for this transaction.
    $nvp = array(
      'ACTION' => 'A',
      'PROFILENAME' => substr($billing_address['first_name'], 0, 20) . ' ' . substr($billing_address['last_name'], 0, 30) . ' - Order: #' . $order->order_id,
      'TERM' => 0,
      'PAYPERIOD' => 'MONT',
      'RETRYNUMDAYS' => 4,
      // Start in one month
      'START' => date('mdY', strtotime('+1 month')),
      // Must be R to initiate recurring profile
      'TRXTYPE' => 'R',
      // C - Credit card
      'TENDER' => 'C',
      // The total price
      'AMT' => commerce_currency_amount_to_decimal($charge['amount'], $charge['currency_code']),
      // Optional amount to charge initially
      'OPTIONALTRX' => $payment_method['settings']['trxtype'],
      'OPTIONALTRXAMT' => commerce_currency_amount_to_decimal($charge['amount'], $charge['currency_code']),
      // The currency code
      'CURRENCY' => $charge['currency_code'],
      // The credit card number
      'ACCT' => $pane_values['credit_card']['number'],
      // The expiration date, in format 'mmyy'
      'EXPDATE' => sprintf("%02d", $pane_values['credit_card']['exp_month']) . substr($pane_values['credit_card']['exp_year'], 2),
    );
  }
  else {
    // Build a name-value pair array for this transaction.
    $nvp = array(
      // A - Authorize, S - Auth and Capture
      'TRXTYPE' => $payment_method['settings']['trxtype'],
      // C - Credit card
      'TENDER' => 'C',
      // The total price
      'AMT' => commerce_currency_amount_to_decimal($charge['amount'], $charge['currency_code']),
      // The currency code
      'CURRENCY' => $charge['currency_code'],
      // The credit card number
      'ACCT' => $pane_values['credit_card']['number'],
      // The expiration date, in format 'mmyy'
      'EXPDATE' => sprintf("%02d", $pane_values['credit_card']['exp_month']) . substr($pane_values['credit_card']['exp_year'], 2),
      // The order number
      'INVNUM' => $order->order_number,
    );
  }

  if (isset($pane_values['credit_card']['code'])) {
    $nvp['CVV2'] = $pane_values['credit_card']['code'];
  }

  // Build a description for the order.
  $description = array();
  foreach ($order_wrapper->commerce_line_items as $delta => $line_item_wrapper) {
    if (in_array($line_item_wrapper->type->value(), commerce_product_line_item_types())) {
      $description[] = round($line_item_wrapper->quantity->value()) . 'x ' . $line_item_wrapper->line_item_label->value();
    }
  }

  $descr = variable_get('site_name');
  if (!empty($description)) {
    $descr .= ': ' . implode(', ', $description);
  }

  $nvp['COMMENT1'] = substr($descr, 0, 127);
  if (strlen($descr) > 127) {
    $nvp['COMMENT2'] = substr($descr, 128, 255);
  }

  // Prepare the billing address for use in the request.
  if (empty($billing_address['first_name'])) {
    $name_parts = explode(' ', $billing_address['name_line']);
    $billing_address['first_name'] = array_shift($name_parts);
    $billing_address['last_name'] = implode(' ', $name_parts);
  }

  // Add customer information
  $nvp += array(
    'FIRSTNAME'     => substr($billing_address['first_name'], 0, 30),
    'LASTNAME'      => substr($billing_address['last_name'], 0, 30),
    'COMPANYNAME'   => substr($billing_address['organisation_name'], 0, 30),
    'STREET'        => substr($billing_address['thoroughfare'], 0, 30),
    'CITY'          => substr($billing_address['locality'], 0, 30),
    'STATE'         => substr($billing_address['administrative_area'], 0, 30),
    'ZIP'           => substr($billing_address['postal_code'], 0, 12),
    'COUNTRY'       => substr($billing_address['country'], 0, 2),
    'EMAIL'         => substr($order->mail, 0, 255),
    'CUSTCODE'      => $order->uid,
    'CUSTIP'        => ip_address(),
  );

  // Submit the request
  $response = commerce_payflow_api_request($payment_method, 'pro', $nvp, $order);
  
  // Something went wrong with the request. Abort.
  if (!$response) {
    drupal_set_message(t('We are unable to process your request at this time. Please try again.'), 'error');
    return FALSE;  
  }

  // Get the PNREF value
  $pnref = NULL;
  if (!empty($response['TRXPNREF'])) {
    $pnref = $response['TRXPNREF'];
  }
  elseif (!empty($response['PNREF'])) {
    $pnref = $response['PNREF'];
  }

  // Prepare a transaction object to log the API response.
  $transaction = commerce_payment_transaction_new($payment_method['method_id'], $order->order_id);
  $transaction->instance_id = $payment_method['instance_id'];
  $transaction->remote_id = $pnref;
  $transaction->amount = $charge['amount'];
  $transaction->currency_code = $charge['currency_code'];
  $transaction->payload[REQUEST_TIME] = $response;

  $trxtype = $payment_method['settings']['trxtype'];
  // Store the type of transaction in the remote status.
  $transaction->remote_status = $trxtype;

  $trxtype_name = commerce_payflow_trxtype_name($trxtype);

  // Build the response message.
  $message = array(
    '<b>Response: @response</b>',
  );

  $transaction->message_variables = array(
    '@response' => $response['RESPMSG'],
    '@action' => $trxtype_name,
  );

  if (intval($response['RESULT']) == 0) {
    // Set the transaction status based on the type of transaction this was.
    switch ($trxtype) {
      case 'S':
        $transaction->status = COMMERCE_PAYMENT_STATUS_SUCCESS;
        break;

      case 'A':
      default:
        $transaction->status = COMMERCE_PAYMENT_STATUS_PENDING;
        break;
    }

    $message[] = '@action - Success';
  }
  elseif (intval($response['RESULT']) == 126) {
    $transaction->status = COMMERCE_PAYMENT_STATUS_PENDING;
    $message[] = '@action - Pending fraud review';
  }
  else {
    $message[] = '@action - REJECTED';
  }

  // Add the rest of the response values to the message
  foreach ($response as $key => $value) {
    $message[] = ucwords(strtolower($key)) . ': @' . $key;
    $transaction->message_variables['@' . $key] = $value;
  }

  $transaction->message = implode('<br />', $message);

  // Store the PNREF in the data array
  $transaction->data['commerce_payflow']['pnref'] = $pnref;

  // Save the transaction information.
  commerce_payment_transaction_save($transaction);

  // If the payment failed, display an error and rebuild the form.
  if ($response['RESULT'] != '0') {
    $error_message = !empty($payment_method['settings']['verbose_errors']) ? check_plain($response['RESPMSG']) : 'Please enter you information again or try a different card.';
    drupal_set_message(t('We received an error processing your card. @error', array('@error' => $error_message)), 'error');
    return FALSE;
  }

  return $transaction->transaction_id;
}
