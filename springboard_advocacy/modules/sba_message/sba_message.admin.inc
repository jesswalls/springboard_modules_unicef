<?php

/**
 * @file
 * SBA Message editing UI.
 */

/**
 * UI controller.
 */
class SbaMessageUIController extends EntityDefaultUIController {
  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {

    $items = array();
    $id_count = count(explode('/', $this->path));
    $wildcard = isset($this->entityInfo['admin ui']['menu wildcard']) ? $this->entityInfo['admin ui']['menu wildcard'] : '%' . $this->entityType;
    // @todo the menu type and context definitions here are definitely
    // not "correct" but they do allow the tabs to remain consistent
    // throughout editing workflow.
    foreach (sba_message_get_types() as $type) {
      $items[$this->path . '/add/' . $type->type] = array(
        'title' => 'Add ' . $type->label,
        'page callback' => 'sba_message_form_wrapper',
        'page arguments' => array($type->type),
        'access callback' => 'sba_message_access',
        'access arguments' => array('create', 'create ' . $type->type),
        'file' => 'sba_message.admin.inc',
        'file path' => drupal_get_path('module', $this->entityInfo['module']),
        'type' => MENU_DEFAULT_LOCAL_TASK,
        'context' => MENU_CONTEXT_INLINE,
      );
    }

    // Loading and editing sba_message entities.
    $items[$this->path . '/sba_message/' . $wildcard] = array(
      'page callback' => 'sba_message_form_wrapper',
      'page arguments' => array($id_count + 1),
      'access callback' => 'sba_message_access',
      'access arguments' => array('edit', $id_count + 1),
      'weight' => 0,
      'file' => 'sba_message.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module']),
      'type' => MENU_LOCAL_TASK,
    );
    $items[$this->path . '/sba_message/' . $wildcard . '/edit'] = array(
      'title' => 'Edit',
      'type' => MENU_DEFAULT_LOCAL_TASK,
      'weight' => -10,
    );
    $items[$this->path . '/sba_message/' . $wildcard . '/delete'] = array(
      'title' => 'Delete',
      'page callback' => 'sba_message_delete_form_wrapper',
      'page arguments' => array($id_count + 1),
      'access callback' => 'sba_message_access',
      'access arguments' => array('delete', $id_count + 1),
      'type' => MENU_LOCAL_TASK,
      'context' => MENU_CONTEXT_INLINE,
      'weight' => 10,
      'file' => 'sba_message.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module']),
    );
    return $items;
  }
}

/**
 * Form callback wrapper: create or edit a sba_message.
 *
 * @param $sba_message
 *   The sba_message object being edited by this form.
 *
 * @return array
 *   The message page render array.
 *
 * @see sba_message_edit_form()
 */
function sba_message_form_wrapper($sba_message) {
  if (is_string($sba_message)) {
    $sba_message = sba_message_create(array('type' => $sba_message));
  }
  $build = array();
  $build['#attached']['css'] = array(
    drupal_get_path('module', 'sba_message') . '/css/sba_message.css',
    'https://fonts.googleapis.com/css?family=Open+Sans:300italic,400italic,600italic,700italic,800italic,400,300,600,700,800',
  );

  $build['#attached']['js'] = array(
    drupal_get_path(
      'module',
      'sba_message'
    ) . '/js/sba_message.js' => array('group' => JS_THEME, 'weight' => 99999),
  );

  $build['content'] = array(
    'sba_message_edit_form' => drupal_get_form('sba_message_edit_form', $sba_message),
    'message_recipients' => array(
      '#id' => 'springboard-advocacy-message-recipients',
      '#type' => 'markup',
      '#markup' => '<div id="springboard-advocacy-message-recipients"><h3>Message Targets</h3><div class = "sba-message-status"></div><div id="springboard-advocacy-message-recipients-content"></div></div>',
      '#prefix' => '<div id="springboard-advocacy-message-recipients-container">',
      '#suffix' => '</div>',
      '#weight' => 2,
    ),
    'find_targets' => array(
      '#id' => 'springboard-advocacy-find-targets',
      '#type' => 'markup',
      '#markup' => views_embed_view('targets', 'block_3'),
      '#prefix' => '<div id="springboard-advocacy-find-targets-container"><div id="springboard-advocacy-find-targets"><h3>Find Targets</h3>',
      '#suffix' => '</div></div>',
      '#weight' => 3,
    ),
  );
  return $build;
}

/**
 * Form callback wrapper: delete a sba_message.
 *
 * @param $sba_message
 *   The sba_message object being edited by this form.
 *
 * @return mixed
 *   A rendered delete from.
 *
 * @see sba_message_edit_form()
 */
function sba_message_delete_form_wrapper($sba_message) {
  // Add the breadcrumb for the form's location.
  return drupal_get_form('sba_message_delete_form', $sba_message);
}

/**
 * Message create/edit form.
 *
 * This is where all the targeting elements are added.
 *
 * @param $form
 *   The form array.
 * @param $form_state
 *    The form meta-data and values.
 * @param $sba_message
 *
 * @return mixed
 */
function sba_message_edit_form($form, &$form_state, $sba_message) {
  $apiCall = springboard_advocacy_api_Call();
  $apiCall->invokeClientMethod('getMaintenanceMode');

  // This form should only appear at node/%/messages.
  // Grab the node so we can get the action form UUID and node ID.
  $node = menu_get_object();

  $form = array(
    '#prefix' => '<div id="springboard-advocacy-message-form-container">',
    '#suffix' => '</div>',
  );

  $form['parent_node']['nid'] = array(
    '#type' => 'hidden',
    '#value' => $node->nid,
  );
  $form['advocacy_id'] = array(
    '#type' => 'hidden',
    '#value' => $node->advocacy_id,
  );

  // Add the default field elements.
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Internal Title'),
    '#default_value' => isset($sba_message->name) ? $sba_message->name : '',
    '#maxlength' => 255,
    '#required' => TRUE,
    '#weight' => -5,
  );
  
  $form['data']['#tree'] = TRUE;
  // Get/Set the message UUID.
  $form['data']['message_id'] = array(
    '#type' => 'hidden',
    '#value' => isset($sba_message->data['message_id']) ? $sba_message->data['message_id'] : str_replace(' ', '-', uniqid(substr(variable_get('site_name', ''), 0, 10) . '-' . substr($node->title, 0, 10) . '-')),
  );

  $form['data']['recipients'] = array(
    '#type' => 'hidden',
    '#default_value' => isset($sba_message->data['recipients']) ? str_replace('"', '&quot;', $sba_message->data['recipients']) : '',
  );

  $form['data']['group_id'] = array(
    '#type' => 'hidden',
    '#default_value' => isset($sba_message->data['group_id']) ? $sba_message->data['group_id'] : '',
  );

  $form['data']['precedence'] = array(
    '#type' => 'hidden',
    '#default_value' => isset($node->precedence) ? $node->precedence : 0,
  );

  if (empty($sba_message->is_new)) {
    $form['data']['weight'] = array(
      '#type' => 'hidden',
      '#default_value' => isset($sba_message->data['weight']) ? $sba_message->data['weight'] : NULL,
    );
  }

  if (isset($sba_message->data['group_id']) && $sba_message->data['group_id'] == 'no_response') {
    drupal_set_message('A remote group ID could not be found.');
    watchdog('advocacy', 'A remote group ID could not be found. Local ID: @message', array('@message' => $sba_message->data['group_id']), WATCHDOG_ERROR);
  }

  // Add the field related form elements.
  $form_state['sba_message'] = $sba_message;
  field_attach_form('sba_message', $sba_message, $form, $form_state);

  if ((isset($node->message_ids) && empty($sba_message->sba_message_id)) || (isset($node->message_ids) && count($node->message_ids) > 1)) {
    $form['field_sba_subject_editable']['#disabled'] = TRUE;
    $form['field_sba_subject_editable']['#attributes']['class'][] = 'disabled';
    $form['field_sba_user_editable']['#disabled'] = TRUE;
    $form['field_sba_user_editable']['#attributes']['class'][] = 'disabled';
  }

  $form['actions'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('form-actions')),
    '#weight' => 400,
  );

  $submit = array();

  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $form['message_error'] = array(
    '#markup' => '',
    '#prefix' => '<div id = "advo-error-wrapper">',
    '#suffix' => '</div>',
    '#weight' => 10,

  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save message'),
    '#submit' => $submit + array('sba_message_edit_form_submit'),
  );

  // We append the validate handler to #validate in case a form callback_wrapper
  // is used to add validate handlers earlier.
  $form['#validate'][] = 'sba_message_edit_form_validate';
  return $form;
}


/**
 * Form API validate callback for the sba_message form.
 *
 * @param $form
 *   The form array.
 * @param $form_state
 *    The form meta-data and values.
 */
function sba_message_edit_form_validate(&$form, &$form_state) {
  $sba_message = $form_state['sba_message'];
  // Notify field widgets to validate their data.
  field_attach_form_validate('sba_message', $sba_message, $form, $form_state);
}


/**
 * Form API submit callback for the sba_message form.
 *
 * @param $form
 *   The form array.
 * @param $form_state
 *    The form meta-data and values.
 */
function sba_message_edit_form_submit(&$form, &$form_state) {

  $form_state['values']['data']['recipients'] = str_replace('&quot;', '"', $form_state['values']['data']['recipients']);

  $sba_message = entity_ui_controller('sba_message')->entityFormSubmitBuildEntity($form, $form_state);
  // Add in created and changed times.
  $is_new = FALSE;
  if ($sba_message->is_new = isset($sba_message->is_new) ? $sba_message->is_new : 0) {
    $sba_message->created = time();
    $is_new = TRUE;
  }

  $sba_message->changed = time();

  $status = $sba_message->save();
  if ($status) {
    drupal_set_message(t('Message saved.'));
  }

  $wrapper = entity_metadata_wrapper('sba_message', $sba_message);
  $nid = $wrapper->field_sba_action_id->value()->nid;
  // Set a weight and an entry in the draggableviews table
  // if there is no weight.
  if (!isset($sba_message->data['weight']) && isset($sba_message->sba_message_id)) {
    $arg = json_encode(array($nid));
    // Create new order record.
    $weight = db_query("SELECT MAX(weight) FROM {draggableviews_structure} WHERE view_name = :name and args = :arg",
      array(':name' => 'sba_messages_node', ':arg' => $arg))->fetchField();

    $sba_message->data['weight']  = $weight + 1;
    $sba_message->save();

    $record = array(
      'view_name' => 'sba_messages_node',
      'view_display' => 'block_1',
      'args' => $arg,
      'entity_id' => $sba_message->sba_message_id,
      'weight' => $weight + 1,
    );
    drupal_write_record('draggableviews_structure', $record);
  }

  form_load_include($form_state, 'inc', 'sba_message', 'sba_message.api_calls');
  _sba_message_api_save($sba_message, $is_new, $form_state);

  $form_state['redirect'] = 'node/' . $nid . '/messages';
}


/**
 * Form API submit callback for the delete button.
 *
 * @param $form
 *   The form array.
 * @param $form_state
 *    The form meta-data and values.
 */
function sba_message_form_submit_delete(&$form, &$form_state) {
  $nid =  $form_state['values']['nid'];
  $form_state['redirect'] = 'node/' . $nid . '/messages/sba_message/' . $form_state['sba_message']->sba_message_id . '/delete';
}


/**
 * Form callback: confirmation form for deleting a sba_message.
 *
 * @see confirm_form()
 *
 * @param $form
 *   The form array.
 * @param $form_state
 *    The form meta-data and values.
 * @param $sba_message  The sba_message to delete
 *
 * @return mixed
 */
function sba_message_delete_form($form, &$form_state, $sba_message) {
  $form_state['sba_message'] = $sba_message;
  $wrapper = entity_metadata_wrapper('sba_message', $sba_message);
  $nid = $wrapper->field_sba_action_id->value()->nid;

  $form['#submit'][] = 'sba_message_delete_form_submit';

  $form = confirm_form($form,
    t('Are you sure you want to delete sba_message %name?', array('%name' => $sba_message->name)),
    'node/' . $nid . '/messages/sba_message',
    '<p>' . t('This action cannot be undone.') . '</p>',
    t('Delete'),
    t('Cancel'),
    'confirm'
  );
  
  return $form;
}

/**
 * Submit callback for sba_message_delete_form
 * @param $form
 *   The form array.
 * @param $form_state
 *    The form meta-data and values.
 */
function sba_message_delete_form_submit($form, &$form_state) {
  // Delete the message.
  $sba_message = $form_state['sba_message'];
  $wrapper = entity_metadata_wrapper('sba_message', $sba_message);
  $nid = $wrapper->field_sba_action_id->value()->nid;
  sba_message_delete($sba_message);
  drupal_set_message(t('%name has been deleted.', array('%name' => $sba_message->name)));
  watchdog('sba_message', 'Deleted sba_message: %name.', array('%name' => $sba_message->name));
  form_load_include($form_state, 'inc', 'sba_message', 'sba_message.api_calls');

  _sba_message_api_delete_target_group($sba_message);

  $form_state['redirect'] = 'node/' . $nid . '/messages';
}
