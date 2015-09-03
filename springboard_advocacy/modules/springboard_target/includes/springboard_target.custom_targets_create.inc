<?php

/**
 * @file
 * Functions for target creation.
 */

/**
 * Create custom target form.
 *
 * Add create target form items to the generic form defined
 * in springboard_target.custom_targets.inc.
 *
 * @return array
 *   The Target add form.
 */
function springboard_target_create_custom_targets_form() {

  module_load_include('inc', 'springboard_target', 'includes/springboard_target.custom_targets');

  $form = springboard_target_form();
  if (!isset($form['not_found'])) {
    $form['#validate'][] = 'springboard_target_form_validate';
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
      '#weight' => 10,
      '#attributes' => array('class' => 'target-add'),
    );
  }
  return $form;
}


/**
 * Submit function for target create form.
 *
 * @param $form
 * @param $form_state
 */
function springboard_target_create_custom_targets_form_submit($form, &$form_state) {
  $input = $form_state['values'];

  $api_call = new AdvocacyApiCall();
  $target = $api_call->invokeClientMethod('createCustomTarget', $input);

  if (!empty($target->data)) {
    $message = implode(' ', (array) $target->data->status);
    drupal_set_message($message);
    if (isset($target->data->id)) {
      $form_state['redirect'] = 'admin/springboard/advocacy/targets/custom-targets/';
    }
  }
}
