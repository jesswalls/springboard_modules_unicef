<?php

/**
 * @file
 * Commerce based hook for commerce_sage_payments
 */

/**
 * Implements hook_fundraiser_commerce_fundraiser_gateway_info().
 */
function commerce_sage_payments_fundraiser_commerce_fundraiser_gateway_info() {
  return array(
    // Create the payment_method array with the commerce gateway method info name as the key
    'payment_method' => array('commerce_sage_payments_cc' => 'credit', 'commerce_sage_payments_eft' => 'bank account'),
    'allow_recurring'     => array('credit', 'bank account'),
    'allow_refund'        => array('credit', 'bank account'),
    'form callback'       => 'commerce_sage_payments_fundraiser_commerce_submit_form',
    'cleanup callback'    => 'commerce_sage_payments_fundraiser_commerce_cleanup',
    'scrub callback'      => 'commerce_sage_payments_fundraiser_commerce_scrub',
    'validate callback'   => 'commerce_sage_payments_fundraiser_commerce_validate',
    'expire callback'     => 'commerce_sage_payments_fundraiser_commerce_expire',
    'charge callback'     => 'commerce_sage_payments_fundraiser_commerce_charge',
    'refund callback'     => 'commerce_sage_payments_fundraiser_commerce_refund',
    'update callback'     => 'commerce_sage_payments_fundraiser_commerce_update',
    'cardonfile callback' => 'commerce_sage_payments_fundraiser_commerce_cardonfile',
  );
}

/**
 * Returns the form fields for this method
 */
function commerce_sage_payments_fundraiser_commerce_submit_form($payment_method, $config = NULL) {
  if ($payment_method == 'credit') {
    module_load_include('inc', 'fundraiser_commerce', 'includes/fundraiser_commerce.credit_card');
    $form = _fundraiser_commerce_credit_card_form();
  }
  elseif ($payment_method == 'bank account') {
    $method_instance = commerce_payment_method_instance_load($config['id']);
    $form = commerce_sage_payments_eft_submit_form($method_instance);
    // Set each field as not required
    foreach (element_children($form['bank_account']) as $field_name) {
      $form['bank_account'][$field_name]['#required'] = FALSE;
    }

    $form = $form['bank_account'];
  }

  return $form;
}

/**
 * Convert values to ones that Fundraiser Commerce is looking for
 */
function commerce_sage_payments_fundraiser_commerce_cleanup($submission_fields) {
  if ($submission_fields['payment_method'] == 'credit') {
    module_load_include('inc', 'fundraiser_commerce', 'includes/fundraiser_commerce.credit_card');
    return _fundraiser_commerce_credit_card_cleanup($submission_fields);
  }

  // Pass through for eft.
  return $submission_fields;
}

/**
 * Callback function, return the user entered expiration dates for this submission.
 */
function commerce_sage_payments_fundraiser_commerce_expire($submission_fields) {
  if ($submission_fields['payment_method'] == 'bank account') {
    if (isset($info['gateway_details']['settings']['commerce_sage_settings_sustainer_series_start_count'])) {
      $exp_month_count = $info['gateway_details']['settings']['commerce_sage_settings_sustainer_series_start_count'];
      $exp_timestamp = strtotime('+' . $exp_month_count . ' months');
    }
    else {
      // pretend expiration date for sustainers
      $exp_timestamp = strtotime('+24 months');
    }
    return array(
      'month' => date('m', $exp_timestamp),
      'year' => date('Y', $exp_timestamp),
    );
  }

  module_load_include('inc', 'fundraiser_commerce', 'includes/fundraiser_commerce.credit_card');
  return _fundraiser_commerce_credit_card_expire($submission_fields);
}

/**
 * Callback function, scrub the data before saving.
 */
function commerce_sage_payments_fundraiser_commerce_scrub($submission_fields, $payment_method) {
  if ($payment_method == 'credit') {
    module_load_include('inc', 'fundraiser_commerce', 'includes/fundraiser_commerce.credit_card');
    return _fundraiser_commerce_credit_card_scrub($submission_fields);
  }
  elseif ($payment_method == 'bank account') {
    // Scrub sensitive donation fields if they exist.
    if (isset($submission_fields['bank account']['account_number'])) {
      $submission_fields['bank account']['account_number'] = substr($submission_fields['bank account']['account_number'], -3);
      unset($submission_fields['bank account']['confirm_account_number']);
    }
    return $submission_fields;
  }
}

/**
 * Validate the submitted values with the commerce validate function
 */
function commerce_sage_payments_fundraiser_commerce_validate($submission_fields, $payment_fields, $payment_method) {
  // Pass the values to the validation scripts.
  if ($payment_method == 'credit') {
    $form_parents = array_merge($payment_fields['#parents'], array('credit'));
    module_load_include('inc', 'fundraiser_commerce', 'includes/fundraiser_commerce.credit_card');
    _fundraiser_commerce_credit_card_validate($submission_fields, $form_parents);
  }
  elseif ($payment_method == 'bank account') {
    $form_parents = array_merge($payment_fields['#parents'], array('bank account'));
    // Pass the values array with the key the litle module expects.
    $values = array('bank_account' => $submission_fields['payment_fields']['bank account']);
    // @todo We need $payment_method (with settings) as the first param here.
    // Passing NULL here means cardonfile will never be used in this case
    // which is not a big deal as long as we don't allow cardonfile selection
    // from the fundraiser forms.
    commerce_sage_payments_eft_submit_form_validate(NULL, $payment_fields, $values, NULL, $form_parents);
  }

  return $submission_fields;
}

/**
 * Submit the donation values to the Sage Payments charge handler
 */
function commerce_sage_payments_fundraiser_commerce_charge($method_instance, $donation) {
  module_load_include('inc', 'fundraiser_commerce', 'includes/fundraiser_commerce.credit_card');
  // Translate from donation settings to the correct values for the plugin.
  $order = commerce_order_load($donation->did);
  $wrapper = entity_metadata_wrapper('commerce_order', $order);
  $charge = $wrapper->commerce_order_total->value();
  if (!isset($charge['recurs_monthly']) && isset($donation->donation['recurs_monthly'])) {
    $charge['recurs_monthly'] = $donation->donation['recurs_monthly'];
  }

  $pane_form = array(); // Not actually used anywhere in this system, so ignore it.

  // Add fundraiser commerce data to the pane values array
  $pane_values =  _commerce_sage_fundraiser_pane_values($donation);
  _fundraiser_commerce_submit_handler_pane_values($pane_values, $donation, key($pane_values));

  // Execute call to Sage depending on what payment method we have.
  switch ($donation->donation['payment_method']) {
    case 'credit' :
      $result = commerce_sage_payments_cc_submit_form_submit($method_instance, $pane_form, $pane_values, $order, $charge);
      break;
    case 'bank account' :
      $result = commerce_sage_payments_eft_submit_form_submit($method_instance, $pane_form, $pane_values, $order, $charge);
      break;
  }

  $success = FALSE;
  if ($result !== FALSE) {
    $success = TRUE;
  }

  // Perform post processing functions
  _fundraiser_commerce_charge_submit_form_process($success, $method_instance, $pane_values, $donation);

  return $success;
}

/**
 * Get Litle pane values from a donation.
 *
 * Checks which payment type is used and returns the correct values.
 *
 * @param object $donation
 *   The donation to grab the pane values from.
 *
 * @return array
 *   The pane values, keyed by credit_card or echeck.
 */
function _commerce_sage_fundraiser_pane_values($donation) {
  switch ($donation->donation['payment_method']) {
    case 'credit' :
      $pane_values = _fundraiser_commerce_credit_card_pane_values($donation);
      break;
    case 'bank account' :
      $pane_values['bank_account'] = $donation->donation['payment_fields']['bank account'];
      break;
  }

  return $pane_values;
}

/**
 * Card on file callback
 *
 * We use a custom callback since we may need to update an existing vault profile
 */
function commerce_sage_payments_fundraiser_commerce_cardonfile($donation) {
  // Use standard function to setup the card on file fields.
  module_load_include('inc', 'fundraiser_commerce', 'includes/fundraiser_commerce.credit_card');
  $cardonfile_fields = _fundraiser_commerce_sage_payments_cardonfile_fields($donation);

  // So we need to search locally to see if we have an existing profile for
  // a card number.
  // Only perform this when we're in an active non-reference charge.
  if (isset($donation->reference_charge) && $donation->reference_charge === FALSE) {
    if ($donation->donation['payment_method'] == 'credit') {
      // Query the db for an existing record.
      $card_data = _fundraiser_commerce_cardonfile_exp_date_mismatch($cardonfile_fields);
    }
    else {
      // bank account records never get updated.
      $card_data = FALSE;
    }

    // If we have a profile for this user update it locally.
    if ($card_data) {
      // Make the update request to authorize.net
      commerce_sage_payments_fundraiser_commerce_update($donation, $card_data);
    }
  }

  return $cardonfile_fields;
}

/**
 * Returns the values need to load a card on file profile for Sage Payments.
 *
 * @param object $donation
 *   Fundraiser donation object.
 *
 * @return array
 *   Values ready to be passed into a card on file profile query.
 */
function _fundraiser_commerce_sage_payments_cardonfile_fields($donation) {
  $data = array();

  if ($donation->donation['payment_method'] == 'credit') {
    $pane_values = _fundraiser_commerce_credit_card_pane_values($donation);
    $data = array(
      // Strip the card number down to the last four
      // since thats all card on file will store.
      'card_number' => substr($pane_values['credit_card']['number'], -4),
      'card_exp_month' => $pane_values['credit_card']['exp_month'],
      'card_exp_year' => $pane_values['credit_card']['exp_year'],
    );
  }
  elseif ($donation->donation['payment_method'] == 'bank account') {
    $pane_values['bank_account'] = $donation->donation['payment_fields']['bank account'];
    $data = array(
      'card_number' => substr($pane_values['bank_account']['account_number'], -3),
    );
  }

  return $data + array('instance_id' => $donation->gateway['id'], 'uid' => $donation->uid);
}

/**
 * Callback function, update card data stored at the gateway and locally
 *
 * @param $donation Object
 *    Fundraiser commerce donation object which should include the new/updated card data
 * @param $card_data Object
 *    Card on file entity, this should be the current entity for the donation,
 *    new data should be passed in the donation object
 *
 * @return Object
 *    Card on file entity for the new/updated card data
 */
function commerce_sage_payments_fundraiser_commerce_update($donation, $card_data = NULL) {
  $payment_method = $donation->gateway['gateway_details'];

  // If no card data was passed load the profile from the donation if its set
  if (empty($card_data) && !empty($donation->data['cardonfile'])) {
    $card_data = commerce_cardonfile_load($donation->data['cardonfile']);
  }

  if (empty($card_data)) {
    // Log the missing card data
    watchdog(
      'fundraiser',
      'A card update was attempted on donation @id but no stored card data was found.',
      array('@id' => $donation->did),
      WATCHDOG_CRITICAL
    );
    return;
  }

  if ($donation->donation['payment_method'] == 'credit') {
    _commerce_sage_payments_fundraiser_commerce_update_cc($donation, $card_data);
  }
  elseif ($donation->donation['payment_method'] == 'bank account') {
    _commerce_sage_payments_fundraiser_commerce_update_eft($donation, $card_data);
  }
}

/**
 * Update card data stored at the gateway and locally
 *
 * @param $donation Object
 *    Fundraiser commerce donation object which should include the new/updated card data
 * @param $card_data Object
 *    Card on file entity, this should be the current entity for the donation,
 *    new data should be passed in the donation object
 *
 * @return Object
 *    Card on file entity for the new/updated card data
 */
function _commerce_sage_payments_fundraiser_commerce_update_cc($donation, $card_data = NULL) {
  $payment_method = $donation->gateway['gateway_details'];

  // Pull the new credit card values from the donation
  $pane_values = _fundraiser_commerce_credit_card_pane_values($donation);
  $cardonfile_fields = _fundraiser_commerce_credit_card_cardonfile_fields($donation);

  // Check the card number to see if it matches the current card data number
  // If it does then we use the update function
  // if its a new card check if we should create a new vault profile
  $action = 'update';
  if ($cardonfile_fields['card_number'] != $card_data->card_number) {
    // This is a new card for this donation, make sure we don't have an existing profile
    // First check with the card number and date
    if ($existing = _fundraiser_commerce_cardonfile_match($cardonfile_fields)) {
      // Set the existing card on the donation and return it
      $donation->data['cardonfile'] = $existing->card_id;
      $card_data = $existing;
    }
    // Check if we have a mismatched exp date record
    elseif ($mismatch =  _fundraiser_commerce_cardonfile_exp_date_mismatch($cardonfile_fields)) {
      $donation->data['cardonfile'] = $mismatch->card_id;
      $card_data = $mismatch;
    }
    // Nothing stored locally so create a new profile
    else {
      $action = 'new';
    }
  }

  if ($action == 'update') {
    $card_data->card_number = $cardonfile_fields['card_number'];
    $card_data->card_exp_month = $cardonfile_fields['card_exp_month'];
    $card_data->card_exp_year = $cardonfile_fields['card_exp_year'];

    // We're mirroring the commerce_authnet_cim_cardonfile_update function so setup values that function uses, see that function for details
    $form['credit_card']['number']['#default_value'] = '';

    $response = commerce_sage_payments_cc_vault_cardonfile_update($form, $form_state, $payment_method, $card_data);

    if ($response) {
      commerce_cardonfile_save($card_data);
      return $card_data;
    }
  }
  // Create a new card on file record
  elseif ($action == 'new') {
    // We're using the built in function that requires a payment details array and the order
    $payment_details = array(
      'CARDNUMBER'      => $pane_values['credit_card']['number'],
      'EXPIRATION_DATE' => str_pad($pane_values['credit_card']['exp_month'], 2, 0, STR_PAD_LEFT) . substr($pane_values['credit_card']['exp_year'], 2, 2),
    );

    // Load the order
    $order = commerce_order_load($donation->did);
    $order_wrapper = entity_metadata_wrapper('commerce_order', $order);

    // Card name is used to save the card name with the other card data..
    if ($order_wrapper->commerce_customer_billing->value()) {
      $billing_address = $order_wrapper->commerce_customer_billing->commerce_customer_address->value();
      $card_name = $billing_address['name_line'];
    }

    $vault_response = commerce_sage_payments_vault_request_insert($payment_method, $payment_details);

    // If the Vault Profile creation was a success, store the new card on file data locally.
    if (trim($vault_response['SUCCESS']) == 'true') {
      $guid = trim($vault_response['GUID']);

      // Get the card type
      $card_type = commerce_payment_validate_credit_card_type($pane_values['credit_card']['number'], array_keys(commerce_payment_credit_card_types()));
      $all_types = commerce_payment_credit_card_types();
      $card_type = !empty($all_types[$card_type]) ? $all_types[$card_type] : 'card';

      // Store the token with cardonfile.
      $card_data = commerce_cardonfile_new();
      $card_data->uid = $order->uid;
      $card_data->payment_method = $payment_method['method_id'];
      $card_data->instance_id = $payment_method['instance_id'];
      $card_data->remote_id = $guid;
      $card_data->card_type = !empty($card_type) ? $card_type : 'card';
      $card_data->card_name = !empty($billing_address['name_line']) ? $billing_address['name_line'] : '';
      $card_data->card_number = substr($pane_values['credit_card']['number'], -4);
      $card_data->card_exp_month = $pane_values['credit_card']['exp_month'];
      $card_data->card_exp_year = $pane_values['credit_card']['exp_year'];
      $card_data->status = 1;

      // Save and log the creation of the new card on file.
      commerce_cardonfile_save($card_data);
      watchdog('commerce_sage_payments', 'GUID @guid registered and saved to user @uid.', array('@guid' => $guid, '@uid' => $order->uid));

      // Set the value on the donation
      $donation->data['cardonfile'] = $card_data->card_id;
      return $card_data;
    }
  }
}

/**
 * Update bank account data stored at the gateway and locally
 *
 * @param $donation Object
 *    Fundraiser commerce donation object which should include the new/updated card data
 * @param $card_data Object
 *    Card on file entity, this should be the current entity for the donation,
 *    new data should be passed in the donation object
 *
 * @return Object
 *    Card on file entity for the new/updated card data
 */
function _commerce_sage_payments_fundraiser_commerce_update_eft($donation, $card_data = NULL) {
  $payment_method = $donation->gateway['gateway_details'];

  // Pull the new credit card values from the donation
  $cardonfile_fields = _fundraiser_commerce_sage_payments_cardonfile_fields($donation);

  // Bank account info isn't updated, so check if we have new account #
  if ($cardonfile_fields != $card_data->card_number) {
    $pane_values['bank_account'] = $donation->donation['payment_fields']['bank account'];

    // Build a payment details array for the bank account.
    $payment_details = array(
      'ROUTING_NUMBER' => $pane_values['bank_account']['routing_number'],
      'ACCOUNT_NUMBER' => $pane_values['bank_account']['account_number'],
      'C_ACCT_TYPE' => $pane_values['bank_account']['account_type'],
    );

    // Load the order
    $order = commerce_order_load($donation->did);
    $order_wrapper = entity_metadata_wrapper('commerce_order', $order);

    // Card name is used to save the card name with the other card data..
    if ($order_wrapper->commerce_customer_billing->value()) {
      $billing_address = $order_wrapper->commerce_customer_billing->commerce_customer_address->value();
      $card_name = $billing_address['name_line'];
    }
 
    // Save the credit card in the Vault.
    $vault_response = commerce_sage_payments_vault_request_insert($payment_method, $payment_details);

    if (trim($vault_response['SUCCESS']) == 'true') {
      $guid = trim($vault_response['GUID']);

      // Store the token with cardonfile.
      $card_data = commerce_cardonfile_new();
      $card_data->uid = $order->uid;
      $card_data->payment_method = $payment_method['method_id'];
      $card_data->instance_id = $payment_method['instance_id'];
      $card_data->remote_id = $guid;
      $card_data->card_type = $pane_values['bank_account']['account_type'];
      $card_data->card_name = !empty($billing_address['name_line']) ? $billing_address['name_line'] : '';
      $card_data->card_number = substr($pane_values['bank_account']['account_number'], -3);
      $card_data->status = 1;

      // Save and log the creation of the new card on file.
      commerce_cardonfile_save($card_data);
      watchdog('commerce_sage_payments', 'GUID @guid registered and saved to user @uid.', array('@guid' => $guid, '@uid' => $order->uid));

      // Set the value on the donation
      $donation->data['cardonfile'] = $card_data->card_id;
      return $card_data;
    }
  }
}

/**
 * Refund callback for Sage Payments, wraps the admin form used for refund with our own system.
 */
function commerce_sage_payments_fundraiser_commerce_refund($payment_method, $refund) {
  // Retrieve data.
  $refunding_order = commerce_order_load($refund->did);

  $transaction = commerce_payment_transaction_load(arg(5));

  // Set up the values needed for the transaction to go through.
  $payment_method = commerce_payment_method_instance_load($transaction->instance_id);
  // Submit the donation form.
  module_load_include('inc', 'commerce_sage_payments', 'commerce_sage_payments.admin');
  return commerce_sage_payments_credit_request($payment_method, $transaction, $refunding_order, $refund->amount);
}
