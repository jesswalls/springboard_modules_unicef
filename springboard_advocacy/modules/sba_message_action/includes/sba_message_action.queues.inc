<?php

/**
 * Callback handler for 'node/%/message-queue' menu item.
 *
 * Displays message queue delivery metrics and form actions for changing queue message items status.
 */
function sba_message_action_queue_page($nid) {

  // CSS assets
  drupal_add_css(drupal_get_path('module', 'sba_message_action') . '/css/message-queues.css');

  // Get the node ID/name for API calls
  $advocacyId = node_load($nid)->advocacy_id;

  // Get an instance of the advocacy API client.
  $client = springboard_advocacy_api_call();

  if (isset($advocacyId)) {
    $queueReady = $client->invokeClientMethod(
      'getQueueMessagesCountByStatus',
      $advocacyId,
      'ready'
    );
    $queuePaused = $client->invokeClientMethod(
      'getQueueMessagesCountByStatus',
      $advocacyId,
      'paused'
    );
    $queueCanceled = $client->invokeClientMethod(
      'getQueueMessagesCountByStatus',
      $advocacyId,
      'canceled'
    );
  }
  $queueReadyItems = !empty($queueReady->data->count) ? $queueReady->data->count : 0;
  $queuePausedItems = !empty($queuePaused->data->count) ? $queuePaused->data->count : 0;
  $queueCanceledItems = !empty($queueCanceled->data->count) ? $queueCanceled->data->count : 0;

  // Create the tabs
  $tabs = theme('messsage_deliverability_tabs', array(
    'nodeId' => $nid
  ));

  // Render the action form for changing queue items status
  if (isset($advocacyId)) {
    $renderForm = drupal_get_form('sba_message_action_queues_form', $advocacyId);
    $queueActionsForm = drupal_render($renderForm);
  }
  else {
    $queueActionsForm = t('No actions are currently available. Advocacy Form ID not found.');
  }

  // Setup the page theme
  $page = theme('messsage_action_queues', array(
    'tabs'               => $tabs,
    'queueReadyItems'    => $queueReadyItems,
    'queuePausedItems'   => $queuePausedItems,
    'queueCanceledItems' => $queueCanceledItems,
    'queueActionsForm'   => $queueActionsForm
  ));

  // Return the page to the browser
  return $page;
}

/**
 * Form handler for rendering the action form that allows changing message status.
 * @param $form
 * @param $form_state
 * @param $advocacyId
 * @return mixed
 */
function sba_message_action_queues_form($form, &$form_state, $advocacyId) {

  // Setup the bounds of the allowed and rendered queue actions
  $active = array('Pause' => t('Pause'), 'Restart' => t('Restart'), 'Cancel' => t('Cancel') );

  // Create the form radios for queue update status
  $form['queue_update_type'] = array(
    '#type' => 'radios',
    '#default_value' => 'Pause',
    '#options' => $active,
    '#description' => t('In the event that you need to immediately modify messages pending in the queue, you can do so here.'),
  );

  // Hidden node id for usage in API calls
  $form['node_id'] = array(
    '#type'          => 'value',
    '#name'          => 'node_id',
    '#title'         => t('Node Id'),
    '#default_value' => $advocacyId,
    '#required'      => true,
  );

  // Submit button
  $form['submit'] = array(
    '#type'  => 'submit',
    '#value' => t('Update Queue Items'),
  );

  // Return the form
  return $form;
}

/**
 * Form submission handler for the sba message action queues page.
 * Implements hook_submit()
 * @param $form
 * @param $form_state
 */
function sba_message_action_queues_form_submit($form, &$form_state) {
  // Make the API request to queue up the CSV download
  $apiClient = springboard_advocacy_api_call();

  if (!form_get_errors()) {

    $updateStatusMessage = '';
    $updateStatusMessageType = 'status';

    // Check the submitted radio state to provide feedback and run appropriate API calls
    switch($form_state['input']['queue_update_type']) {
      case 'Pause':
        $apiRequest = $apiClient->invokeClientMethod('modifyQueueMessagesStatus', $form_state['values']['node_id'], 'pause');
        if(isset($apiRequest->data)) {
          $updateStatusMessage = $apiRequest->data->items_updated == 0 ?
            t('Their are no "Ready" messages to pause delivery for.') :
            t('@count Queue message/s have been "Paused" and will not be delivered.', array('@count' => $apiRequest->data->items_updated));
          if ($apiRequest->data->items_updated == 0) {
            $updateStatusMessageType = 'warning';
          }
        }
        break;

      case 'Restart':
          $apiRequest = $apiClient->invokeClientMethod('modifyQueueMessagesStatus', $form_state['values']['node_id'], 'restart');
          if(isset($apiRequest->data)) {
            $updateStatusMessage = $apiRequest->data->items_updated == 0 ?
              t('Their are no "Paused" messages to restart delivery for.') :
              t('@count Queue message/s are now "Ready" and are scheduled for delivery.',
                array('@count' => $apiRequest->data->items_updated)
              );
            if ($apiRequest->data->items_updated == 0) {
              $updateStatusMessageType = 'warning';
            }
          }
        break;

      case 'Cancel':
        $apiRequest = $apiClient->invokeClientMethod('modifyQueueMessagesStatus', $form_state['values']['node_id'], 'cancel');
        if(isset($apiRequest->data)) {
          $updateStatusMessage = $apiRequest->data->items_updated == 0 ?
              t('Their are no "Ready" messages to cancel delivery for.') :
              t('@count Queue message/s have been "Canceled" indefinitely.', array('@count' => $apiRequest->data->items_updated));
          if ($apiRequest->data->items_updated == 0) {
              $updateStatusMessageType = 'warning';
            }
        }
        break;
    }

    // Send the message back the to user for the update attempt and result.
    if(!empty($apiRequest) && isset($apiRequest->data)) {
      $advocacy_id = $form_state['values']['node_id'];
      cache_clear_all($advocacy_id, 'cache_deliverability_report');
      drupal_set_message($updateStatusMessage, $updateStatusMessageType);
    }
  }
}

/**
 * Method to validate the form submission of the sba message action queues page.
 * Implements hook_validate()
 * @param $form
 * @param $form_state
 */
function sba_message_action_queues_form_validate($form, &$form_state) {

}
