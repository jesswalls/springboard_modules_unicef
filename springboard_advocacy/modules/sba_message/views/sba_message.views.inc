<?php

/**
 * @file
 * Providing extra functionality for the SBA Message UI via views.
 */


/**
 * Implements hook_views_data()
 */
function sba_message_views_data_alter(&$data) { 
  $data['sba_message']['link_sba_message'] = array(
    'field' => array(
      'title' => t('Link'),
      'help' => t('Provide a link to the sba_message.'),
      'handler' => 'sba_message_handler_link_field',
    ),
  );
  $data['sba_message']['edit_sba_message'] = array(
    'field' => array(
      'title' => t('Edit Link'),
      'help' => t('Provide a link to the edit form for the sba_message.'),
      'handler' => 'sba_message_handler_edit_link_field',
    ),
  );
  $data['sba_message']['delete_sba_message'] = array(
    'field' => array(
      'title' => t('Delete Link'),
      'help' => t('Provide a link to delete the sba_message.'),
      'handler' => 'sba_message_handler_delete_link_field',
    ),
  );
  // This content of this field are decided based on the menu structure that
  // follows sba_messages/sba_message/%sba_message_id/op
  $data['sba_message']['operations'] = array(
    'field' => array(
      'title' => t('Operations links'),
      'help' => t('Display all operations available for this sba_message.'),
      'handler' => 'sba_message_handler_sba_message_operations_field',
    ),
  );
  $data['sba_message']['data'] = array(
    'field' => array(
      'title' => t('Recipients'),
      'help' => t('Display all operations available for this sba_message.'),
      'handler' => 'views_handler_field',
    ),
  );
}

