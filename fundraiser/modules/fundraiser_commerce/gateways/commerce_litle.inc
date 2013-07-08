<?php

/**
 * @file
 * Commerce based hook for commerce_litle
 */

/**
 * Implements hook_fundraiser_commerce_fundraiser_gateway_info().
 */
function commerce_litle_fundraiser_commerce_fundraiser_gateway_info() {
  return array(
    // Create the payment_method array with the commerce gateway method info name as the key
    'payment_method' => array('commerce_litle_cc' => 'credit', 'commerce_litle_echeck' => 'bank account'),
    'form callback' => 'commerce_litle_fundraiser_commerce_submit_form',
    'cleanup callback' => 'commerce_litle_fundraiser_commerce_cleanup',
    'scrub callback' => 'commerce_litle_fundraiser_commerce_scrub',
    'validate callback' => 'commerce_litle_fundraiser_commerce_validate',
    'charge callback' => 'commerce_litle_fundraiser_commerce_charge',
  );
}

/**
 * Returns the form fields for this method
 */
function commerce_litle_fundraiser_commerce_submit_form($payment_method, $config) {
  if ($payment_method == 'credit') {
    module_load_include('inc', 'fundraiser_commerce', 'includes/fundraiser_commerce.credit_card');
    return _fundraiser_commerce_credit_card_form();
  }
  elseif ($payment_method == 'bank account') {
    $form = commerce_litle_echeck_submit_form();
    return $form['echeck'];
  }
}

/**
 * Convert values to ones that Fundraiser Commerce is looking for
 */
function commerce_litle_fundraiser_commerce_cleanup($submission_fields, $payment_method) {
  if ($payment_method == 'credit') {
    module_load_include('inc', 'fundraiser_commerce', 'includes/fundraiser_commerce.credit_card');
    return _fundraiser_commerce_credit_card_cleanup($submission_fields);
  }

  return $submission_fields;
}

/**
 * Callback function, return the user entered expiration dates for this submission.
 */
function commerce_litle_fundraiser_commerce_expire($submission_fields) {
  module_load_include('inc', 'fundraiser_commerce', 'includes/fundraiser_commerce.credit_card');
  return _fundraiser_commerce_credit_card_expire($submission_fields);
}

/**
 * Callback function, scrub the data before saving.
 */
function commerce_litle_fundraiser_commerce_scrub($submission_fields, $payment_method) {
  if ($payment_method == 'credit') {
    module_load_include('inc', 'fundraiser_commerce', 'includes/fundraiser_commerce.credit_card');
    return _fundraiser_commerce_credit_card_scrub($submission_fields);
  }
  elseif ($payment_method == 'bank account') {
    // Scrub sensitive donation fields if they exists.
    if (isset($submission_fields['bank account']['accNum'])) {
      $submission_fields['back account']['accNum'] = substr($submission_fields['bank account']['accNum'], -3);
    }
    if (isset($submission_fields['bank account']['account_number'])) {
      $submission_fields['bank account']['accNum'] = substr($submission_fields['bank account']['accNum'], -3);
    }
    return $submission_fields;
  }
}

/**
 * Validate the submitted values with the commerce validate function
 */
function commerce_litle_fundraiser_commerce_validate($submission_fields, $payment_fields, $payment_method) {
  // Pass the values to the validation scripts
  if ($payment_method == 'credit') {
    $form_parents = array_merge($payment_fields['#parents'], array('credit'));
    module_load_include('inc', 'fundraiser_commerce', 'includes/fundraiser_commerce.credit_card');
    _fundraiser_commerce_credit_card_validate($submission_fields, $form_parents);
  }
  elseif ($payment_method == 'bank account') {
    $form_parents = array_merge($payment_fields['#parents'], array('bank account'));
    // Pass the values array with the key the litle module expects
    $values = array('echeck' => $submission_fields['payment_fields']['bank account']);
    commerce_litle_echeck_submit_form_validate(NULL, $payment_fields, $values, NULL, $form_parents); 
  }

  return $submission_fields;
}

/**
 * Submit the donation values to the Litle charge handler
 */
function commerce_litle_fundraiser_commerce_charge($method_instance, $donation) {
  module_load_include('inc', 'fundraiser_commerce', 'includes/fundraiser_commerce.credit_card');
  // Translate from donation settings to the correct values for the plugin.
  $order = commerce_order_load($donation->did);
  $wrapper = entity_metadata_wrapper('commerce_order', $order);
  $charge = $wrapper->commerce_order_total->value();

  $pane_form = array(); // Not actually used anywhere in this system, so ignore it.

  // Execute call to Litle depending on what payment method we have
  if ($donation->donation['payment_method'] == 'credit') {
    $pane_values = _fundraiser_commerce_credit_card_pane_values($donation);
    $result = commerce_litle_cc_submit_form_submit($method_instance, $pane_form, $pane_values, $order, $charge);
  }
  elseif ($donation->donation['payment_method'] == 'bank account') {
    $pane_values['echeck'] = $donation->donation['payment_fields']['bank account'];
    $result = commerce_litle_echeck_submit_form_submit($method_instance, $pane_form, $pane_values, $order, $charge);
  }

  // Returns FALSE if the payment failed, returns nothing if successful
  $success = FALSE;
  if ($result !== FALSE) {
    $success = TRUE;
  }
  return $success;
}