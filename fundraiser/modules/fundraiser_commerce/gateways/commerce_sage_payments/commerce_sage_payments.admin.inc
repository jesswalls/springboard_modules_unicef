<?php

/**
 * @file
 * Administrative forms for the Sage Payment module.
 */

/**
 * Makes the Credit request and handles transactions and logging.
 *
 * Formats the request, makes it.
 * Logs response and request if needed.
 * On success creates a new transaction.
 * On failure updates the current transaction.
 *
 * @param array $payment_method
 *   Uses the payment method settings to determine what to log.
 *
 * @param stdClass $transaction
 *   The transaction object.
 *
 * @param stdClass $order
 *   The order object.
 *
 * @param float $amount
 *   Decimal format amount.  Gets converted to and from amount in this function.
 *
 * @return bool
 *   Whether the refund was successful.
 */
function commerce_sage_payments_credit_request($payment_method, $transaction, $order, $amount) {
  $credit_amount = commerce_currency_decimal_to_amount($amount, $transaction->currency_code);

  $request_parameters = array(
    'T_AMT'         => $credit_amount / 100,
    'T_REFERENCE'   => $transaction->remote_id,
  );

  // Log the request if specified.
  if ($payment_method['settings']['log']['request'] === 'request') {
    watchdog('commerce_sage_payments', 'Sage Payments Credit request: !param', array('!param' => '<pre>' . check_plain(print_r($request_parameters, TRUE)) . '</pre>'), WATCHDOG_DEBUG);
  }

  // Submit the request to Litle.
  $response = _commerce_sage_payments_request_credit($payment_method, $request_parameters);

  // Log the response if specified.
  if ($payment_method['settings']['log']['response'] === 'response') {
    watchdog('commerce_sage_payments', 'Sage Payments Credit response: !param', array('!param' => '<pre>' . check_plain(print_r($response, TRUE)) . '</pre>', WATCHDOG_DEBUG));
  }

  // Create a new transaction to record the credit.
  $credit_transaction = commerce_payment_transaction_new($payment_method['method_id'], $order->order_id);
  $credit_transaction->instance_id = $payment_method['instance_id'];
  $credit_transaction->remote_id = isset($response['REFERENCE']) ? $response['REFERENCE'] : '';
  $credit_transaction->amount = $credit_amount * -1;
  $credit_transaction->currency_code = $transaction->currency_code;
  $credit_transaction->payload[REQUEST_TIME] = check_plain(print_r($response, TRUE));

  if (trim($response['APPROVAL_INDICATOR']) == 'A') {
    drupal_set_message(t('Credit for @amount issued successfully', array('@amount' => commerce_currency_format($credit_amount, $transaction->currency_code))));

    // Set the statuses.
    $credit_transaction->status = COMMERCE_PAYMENT_STATUS_SUCCESS;
    $credit_transaction->remote_status = COMMERCE_CREDIT_AUTH_CAPTURE;

    _commerce_sage_payments_build_transaction_message($credit_transaction, $response);

    // Add the reference id of the transaction that was credited to the message
    $credit_transaction->message .= '<b>Credited to</b>: @credited_id';
    $credit_transaction->message_variables['@credited_id'] = $transaction->remote_id;

    // Save the credit transaction.
    commerce_payment_transaction_save($credit_transaction);
    return TRUE;
  }
  else {
    // Set the statuses.
    $credit_transaction->status = COMMERCE_PAYMENT_STATUS_FAILURE;
    $credit_transaction->remote_status = '';

    _commerce_sage_payments_build_transaction_message($credit_transaction, $response);

    // Display a failure message and response reason from Sage Payments.
    $message = $response['MESSAGE'];
    drupal_set_message(t('Credit failed: @reason', array('@reason' => check_plain($message))), 'error');

    // Add an additional helper message if the transaction hadn't settled yet.
    // if ($response[2] == 54) {
    //   drupal_set_message(t('The transaction must be setted before a credit can be issued. This usually takes 24 hours'), 'error');
    // }
    commerce_payment_transaction_save($credit_transaction);
  }

  return FALSE;
}
