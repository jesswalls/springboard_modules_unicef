<?php

/**
 * @file
 * Fundraiser gateway functions for payflow link

/**
 * Gateway info callback
 */
function fundraiser_commerce_payflow_link_gateway_info() {
  return array(
    'payment_method' => array('credit'),
    'allow_recurring' => array('credit'),
    // Important note: While payflow_link is an offsite processor, reference charges are handled onsite
    // We handle that switch in the charge callback
    'offsite_processing' => array(),
    'offsite_recurring' => array(),
    'expire callback' => '_fundraiser_commerce_payflow_expire',
    'refund callback' => '_fundraiser_commerce_payflow_refund',
    'allow_refund' => array('credit'),
    'form callback' => 'fundraiser_commerce_payflow_link_submit_form',
    'charge callback' => 'fundraiser_commerce_payflow_link_charge',
    'redirect callback' => 'fundraiser_commerce_payflow_link_redirect',
    'validate callback' => 'fundraiser_commerce_payflow_link_validate',
  );
}

/**
 * Submit form callback
 */
function _fundraiser_commerce_payflow_link_submit_form($payment_method, $config = NULL) {
  $form = array();
  if (!empty($config)) {
    $method_instance = commerce_payment_method_instance_load($config['id']);
  }

  // Show instructions if thats configured
  if (!empty($method_instance['settings']['show_payment_instructions'])) {
    $form['payflow_information'] = array(
      '#markup' => '<span class="commerce-paypal-wps-info">' . t('After submitting this form you will be taken to another form to enter your payment details.') . '</span>',
    );
  }

  // On the recurring update form let users know payflow doesn't support updating card data
  if (arg(2) == 'recurring_overview') {
    $form['payflow_no_update'] = array(
      '#markup' => '<span class="commerce-payflow-info">' . t('Please contact customer support to make changes to your card data.') . '</span>',
    );
  }

  // To avoid errors on form validation return a value
  $form['payflow_flag'] = array(
    '#type' => 'hidden',
    '#value' => 1,
  );

  return $form;
}

/**
 * Donation form validate callback
 *
 * Nothing to validate since payflow data isn't submitted on the form
 */
function _fundraiser_commerce_payflow_link_validate() {
  return;
}

/**
 * Callback charge function for the payflow link processer
 */
function fundraiser_commerce_payflow_link_charge($payment_method, $donation) {
  // If this is not a refernce charge use fundraiser's redirect functionality
  if (empty($donation->reference_charge)) {
    _fundraiser_commerce_fundraiser_donation_process_external($donation, $donation->gateway);
  }
  // For reference charges use our custom function
  elseif ($donation->reference_charge == TRUE) {
    return _fundraiser_commerce_payflow_pnref_reference_charge($donation);
  }
}

/**
 * Redirect form callback
 *
 * Returns a form for sending the user to payflow or an iframed cc form
 */
function fundraiser_commerce_payflow_link_redirect($method_instance, $donation, $order, $settings) {
  $form = array();
  $form_state = array();
  $pane_form = array();
  $pane_values = array();
  $charge = NULL;

  commerce_payflow_link_submit_form_submit($method_instance, $pane_form, $pane_values, $order, $charge);
  // Save the order to store the redirect key
  commerce_order_save($order);

  // Build the form
  return commerce_payflow_link_redirect_form($form, $form_state, $order, $method_instance);
}

/**
 * Redirect submit callback
 */
function fundraiser_commerce_payflow_link_redirect_submit($method_instance, $donation, $order) {
  // Let the module complete the transaction
  commerce_payflow_link_redirect_form_submit($order, $method_instance);

  // Sustainers will not know if this is a recurring donation at this point so we need to reset that
  $submission =  fundraiser_webform_get_submission($donation->sid);

  if (empty($donation->donation['recurs_monthly'])
   && !empty($submission['recurs_monthly']['value'][0])
   && $submission['recurs_monthly']['value'][0] == 'recurs') {
    $donation->donation['recurs_monthly'] = TRUE;
  }

  // Since the processing happens off site we set the payment fields here
  if (!empty($_POST['EXPDATE'])) {
    $dates = str_split($_POST['EXPDATE'], 2);
    $year = date_create_from_format('y', $dates[1]);

    $fields = array('credit' => array(
      'card_expiration_month' => $dates[0],
      'card_expiration_year' => $year->format('Y'),
      'card_number' => $_POST['ACCT'],
    ));

    $donation->data['payment_fields'] = $fields;
    $donation->donation['payment_fields'] = $fields;
  }

  // Set the pnref value to support reference transactions
  $donation->data['payflow_pnref'] = _fundraiser_commerce_payflow_transaction_pnref($donation->did);

  return TRUE;
}
