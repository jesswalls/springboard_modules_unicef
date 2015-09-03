<?php
/**
 * @file
 * Functions for target updates.
 */

/**
 * Target edit form.
 *
 * Add edit form items to the generic form defined
 * in springboard_target.custom_targets.
 *
 * @param $form
 * @param $form_state
 * @param $target_id
 *
 * @return array
 *   The edit form.
 */
function springboard_target_edit_custom_targets_form($form, &$form_state, $target_id) {

  module_load_include('inc', 'springboard_target', 'includes/springboard_target.custom_targets');

  $form = springboard_target_form($target_id);
  if (!isset($form['not_found'])) {

    $name = array(
      $form['row_one']['salutation']['#default_value'],
      $form['row_one']['first_name']['#default_value'],
      $form['row_one']['last_name']['#default_value'],
    );
    $form['header'] = array(
      '#prefix' => '<h2>',
      '#suffix' => '</h2>',
      '#markup' => check_plain(implode(' ', $name)),
      '#weight' => '-100' ,
    );

    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Update'),
      '#weight' => 10,
      '#attributes' => array('class' => 'target-add'),
    );
  }
  $form['#validate'][] = 'springboard_target_form_validate';

  return $form;

}

/**
 * Submit function for target edit form.
 *
 * @param $form
 * @param $form_state
 */
function springboard_target_edit_custom_targets_form_submit($form, &$form_state) {
  $id = $form_state['build_info']['args'][0];
  $input = $form_state['values'];
  $api_call = new AdvocacyApiCall();
  $target = $api_call->invokeClientMethod('updateCustomTarget', $input, $id);

  if (!empty($target->data)) {
    $message = implode(' ', (array) $target->data->status);
    drupal_set_message($message);
    $form_state['redirect'] = 'admin/springboard/advocacy/targets/custom-targets/';
  }
}
