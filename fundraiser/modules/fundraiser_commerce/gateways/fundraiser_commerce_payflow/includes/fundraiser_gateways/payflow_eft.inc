<?php

/**
 * @file
 * Fundraiser gateway functions for payflow eft
 */

// Include commerce functions
module_load_include('inc', 'fundraiser_commerce_payflow', 'includes/fundraiser_commerce_payflow.payflow_eft');

/**
 * Gateway info callback
 */
function fundraiser_commerce_payflow_eft_gateway_info($method_instance) {
  $info = array(
    'payment_method' => array('bank account'),
    'allow_recurring' => array(),
    'offsite_processing' => array(),
    'offsite_recurring' => array(),
    'expire callback' => 'fundraiser_commerce_payflow_eft_expire',
    'refund callback' => '_fundraiser_commerce_payflow_refund',
    'allow_refund' => array('bank account'),
    'form callback' => 'fundraiser_commerce_payflow_eft_submit_form',
    'charge callback' => 'fundraiser_commerce_payflow_eft_charge',
    'validate callback' => 'fundraiser_commerce_payflow_eft_validate',
    'scrub callback' => 'fundraiser_commerce_payflow_eft_scrub',
  );

  // Check the recurring billing settings on the method to determine the recurring options
  if ($method_instance['settings']['recurring-billing'] === 'recurring-billing-profile') {
    $info['allow_recurring'] = array('bank account');
    $info['offsite_recurring'] = array('bank account');
  }

  return $info;
}

/**
 * Return the fields for the donation form
 */
function fundraiser_commerce_payflow_eft_submit_form($payment_method, $config = NULL) {
  $form = commerce_payflow_eft_submit_form();
  // Remove the required flag for the fields
  foreach (element_children($form['bank_account']) as $field_name) {
    $form['bank_account'][$field_name]['#required'] = FALSE;
  }

  return $form['bank_account'];
}

/**
 * Validate the submitted values with the fundriaser commerce validate function
 */
function fundraiser_commerce_payflow_eft_validate($submission_fields, $payment_fields) {
  $form_parents = array_merge($payment_fields['#parents'], array('bank account'));
  $values = array('bank_account' => $submission_fields['payment_fields']['bank account']);
  commerce_payflow_eft_submit_form_validate(NULL, $payment_fields, $values, NULL, $form_parents);
  return $submission_fields;
}

/**
 * Clean up the submission results after submission before they are returned to fundraiser.
 */
function fundraiser_commerce_payflow_eft_cleanup($submission_fields) {
  module_load_include('inc', 'fundraiser_commerce', 'includes/fundraiser_commerce.credit_card');
  return _fundraiser_commerce_credit_card_cleanup($submission_fields);
}

/**
 * Charge the donation
 */
function fundraiser_commerce_payflow_eft_charge($method_instance, $donation) {
  module_load_include('inc', 'fundraiser_commerce', 'includes/fundraiser_commerce.credit_card');

  $order = commerce_order_load($donation->did);
  $order_wrapper = entity_metadata_wrapper('commerce_order', $order);
  $charge = $order_wrapper->commerce_order_total->value();

  $pane_form = array(); // Not actually used anywhere in this system, so ignore it.

  $pane_values = array(
    'bank_account' => $donation->donation['payment_fields']['bank account'],
  );

  // Add fundraiser commerce data to the pane values array
  _fundraiser_commerce_submit_handler_pane_values($pane_values, $donation);

  // Payflow eft doesn't currently integrate with card on file so unset this
  unset($pane_values['credit_card']['cardonfile_store']);

  // Set this for payflow's Recurring Billing add-on service
  $pane_values['recurring'] = !empty($donation->donation['recurs_monthly']) ? TRUE : FALSE; 

  // Execute the payflow cc submit handler
  $result = commerce_payflow_eft_submit_form_submit($method_instance, $pane_form, $pane_values, $order, $charge);
  $success = FALSE;
  if ($result !== FALSE) {
    $success = TRUE;
  }

  // Perform post processing functions
  _fundraiser_commerce_charge_submit_form_process($success, $method_instance, $pane_values, $donation);

  return $success;
}

/**
 * Scrub the data before saving.
 */
function fundraiser_commerce_payflow_eft_scrub($fields) {
  // Scrub sensitive donation fields if they exists.
  if (isset($fields['bank account']['routing_number'])) {
    $fields['bank account']['routing_number'] = substr($fields['bank account']['routing_number'], -3);
  }
  if (isset($fields['bank account']['account_number'])) {
    $fields['bank account']['account_number'] = substr($fields['bank account']['account_number'], -3);
  }
  // Value added by commerce
  unset($fields['bank account']['confirm_account_number']);
  return $fields;
}
