<?php

/**
 * @file
 * Fundraiser gateway functions for payflow cc
 */

// Commerce include
module_load_include('inc', 'fundraiser_commerce_payflow', 'includes/fundraiser_commerce_payflow.payflow_cc'); 

/**
 * Gateway info callback
 */
function fundraiser_commerce_payflow_cc_gateway_info($method_instance) {
  $info = array(
    'payment_method' => array('credit'),
    'allow_recurring' => array(),
    'offsite_processing' => array(),
    'offsite_recurring' => array(),
    'expire callback' => '_fundraiser_commerce_payflow_expire',
    'refund callback' => '_fundraiser_commerce_payflow_refund',
    'allow_refund' => array('credit'),
    'form callback' => 'fundraiser_commerce_payflow_cc_submit_form',
    'charge callback' => 'fundraiser_commerce_payflow_cc_charge',
    'validate callback' => 'fundraiser_commerce_payflow_cc_validate',
    'cleanup callback' => 'fundraiser_commerce_payflow_cc_cleanup',
    'scrub callback' => 'fundraiser_commerce_payflow_cc_scrub',
  );

  // Check the recurring billing settings on the method to determine the recurring options
  if ($method_instance['settings']['recurring-billing'] === 'recurring-billing-profile') {
    $info['allow_recurring'] = array('credit');
    $info['offsite_recurring'] = array('credit');
  }
  elseif ($method_instance['settings']['recurring-billing'] === 'pnref-token') {
    $info['allow_recurring'] = array('credit');
  }

  return $info;
}

/**
 * Return the fields for the donation form
 */
function fundraiser_commerce_payflow_cc_submit_form($payment_method, $config = NULL) {
  module_load_include('inc', 'fundraiser_commerce', 'includes/fundraiser_commerce.credit_card');
  return _fundraiser_commerce_credit_card_form();
}

/**
 * Charge the donation
 */
function fundraiser_commerce_payflow_cc_charge($method_instance, $donation) {
  // For reference charges use our custom function
  if ($donation->reference_charge == TRUE) {
    return _fundraiser_commerce_payflow_pnref_reference_charge($donation);
  }

  module_load_include('inc', 'fundraiser_commerce', 'includes/fundraiser_commerce.credit_card');

  $order = commerce_order_load($donation->did);
  $order_wrapper = entity_metadata_wrapper('commerce_order', $order);
  $charge = $order_wrapper->commerce_order_total->value();

  $pane_form = array(); // Not actually used anywhere in this system, so ignore it.

  $pane_values = _fundraiser_commerce_credit_card_pane_values($donation);

  // Set this for payflow's Recurring Billing add-on service
  $pane_values['recurring'] = !empty($donation->donation['recurs_monthly']) ? TRUE : FALSE; 

  // Add fundraiser commerce data to the pane values array
  _fundraiser_commerce_submit_handler_pane_values($pane_values, $donation);

  // Payflow cc doesn't currently integrate with card on file so unset this
  unset($pane_values['credit_card']['cardonfile_store']);

  // Execute the payflow cc submit handler
  $result = commerce_payflow_cc_submit_form_submit($method_instance, $pane_form, $pane_values, $order, $charge);
  $success = FALSE;
  if ($result !== FALSE) {
    $success = TRUE;
  }

  // Set the pnref value to support reference transactions
  $donation->data['payflow_pnref'] = _fundraiser_commerce_payflow_transaction_pnref($donation->did);

  // Perform post processing functions
  _fundraiser_commerce_charge_submit_form_process($success, $method_instance, $pane_values, $donation);

  return $success;
}

/**
 * Clean up the submission results after submission before they are returned to fundraiser.
 */
function fundraiser_commerce_payflow_cc_cleanup($submission_fields) {
  module_load_include('inc', 'fundraiser_commerce', 'includes/fundraiser_commerce.credit_card');
  return _fundraiser_commerce_credit_card_cleanup($submission_fields);
}

/**
 * Scrub the data before saving.
 */
function fundraiser_commerce_payflow_cc_scrub($submission_fields) {
  module_load_include('inc', 'fundraiser_commerce', 'includes/fundraiser_commerce.credit_card');
  return _fundraiser_commerce_credit_card_scrub($submission_fields);
}

/**
 * Validate the submitted values with the fundriaser commerce validate function
 */
function fundraiser_commerce_payflow_cc_validate($submission_fields, $payment_fields) {
  module_load_include('inc', 'fundraiser_commerce', 'includes/fundraiser_commerce.credit_card');
  $form_parents = array_merge($payment_fields['#parents'], array('credit'));
  _fundraiser_commerce_credit_card_validate($submission_fields, $form_parents);
  return $submission_fields;
}
