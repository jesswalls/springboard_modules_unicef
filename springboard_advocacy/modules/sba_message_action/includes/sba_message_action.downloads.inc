<?php

/**
 * Page callback to handle the display for the form.
 * @param $nid
 * @return array|mixed
 */
function sba_message_action_download_page($nodeId) {

  // CSS assets
  drupal_add_css(drupal_get_path('module', 'sba_message_action') . '/css/message-downloads.css');

  $form = drupal_get_form('sba_message_action_download_form', $nodeId);

  $tabs = theme('messsage_deliverability_tabs', array(
    'nodeId' => $nodeId
  ));

  $renderForm = drupal_get_form('sba_message_action_download_form', $nodeId);
  $downloadReportForm = drupal_render($renderForm);

  $page = theme('messsage_action_downloads', array(
    'form' => $downloadReportForm,
    'tabs' => $tabs
  ));

  return $page;
}

/**
 * Generating the form rendering with form builder.
 * @param $form
 * @param $form_state
 * @param $nodeId
 * @return mixed
 */
function sba_message_action_download_form($form, &$form_state, $nodeId)
{

  global $user;

  $form['description'] = array(
    '#type'  => 'item',
    '#title' => t('Please provide the email that you want the CSV download link to be sent to.'),
  );

  $form['name'] = array(
    '#type'          => 'textfield',
    '#name'          => 'csv_messages_download_email',
    '#title'         => t('Email'),
    '#default_value' => $user->mail,
    '#required'      => true,
  );

  $form['node_id'] = array(
    '#type'          => 'value',
    '#name'          => 'node_id',
    '#title'         => t('Node Id'),
    '#default_value' => $nodeId,
    '#required'      => true,
  );

  $form['submit'] = array(
    '#type'  => 'submit',
    '#value' => t('Get Download'),
  );

  return $form;
}

/**
 * Form submission handler for the sba message action download page.
 * Implements hook_submit()
 * @param $form
 * @param $form_state
 */
function sba_message_action_download_form_submit($form, &$form_state)
{
  if (!form_get_errors()) {

    $messageNodeId = $form['node_id']['#value'];
    $emailAddress = $form_state['input']['csv_messages_download_email'];

    $form = node_load($messageNodeId);

    $messageAdvocacyId = $form->advocacy_id;

    // Make the API request to queue up the CSV download
    $apiClient = springboard_advocacy_api_call();
    $apiRequest = $apiClient->invokeClientMethod('getFailedMessagesDownload', $messageAdvocacyId, $emailAddress);

    if (isset($apiRequest->data) && $apiRequest->data == 'Download queued.') {
      drupal_set_message('Thanks! Your request has been submitted. You will receive an email shortly with a link to download the failed messages.');
    } else {
      drupal_set_message('Sorry, your request did not go through. Please try again later.', 'error');
    }
  }
}

/**
 * Method to validate the form submission of the sba message action download page.
 * Implements hook_validate()
 * @param $form
 * @param $form_state
 */
function sba_message_action_download_form_validate($form, &$form_state)
{

  if (!valid_email_address($form_state['input']['csv_messages_download_email'])) {
    form_set_error('csv_messages_download_email', t('Please enter a valid email address.'));
  }
}