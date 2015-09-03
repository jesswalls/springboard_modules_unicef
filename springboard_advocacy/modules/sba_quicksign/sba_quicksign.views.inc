<?php

/**
 * @file
 */

/**
 * Implements hook_views_data().
 */
function sba_quicksign_views_data() {
  $data['sba_quicksign_submissions']['table'] = array(
    'group' => t('Springboard Advocacy Quicksign'),
    'join' => array(
      'node' => array(
        'left_field' => 'nid',
        'field' => 'nid',
      ),
      'webform_submissions' => array(
        'left_field' => 'sid',
        'field' => 'sid',
      ),
    ),
  );
  $data['sba_quicksign_submissions']['nid'] = array(
    'title' => t('Advocacy node'),
    'help' => t('Advocacy form node id.'),
    'relationship' => array(
      'base' => 'node',
      'base field' => 'nid',
      'handler' => 'views_handler_relationship',
      'label' => t('Advocacy node'),
    ),
  );
  $data['sba_quicksign_submissions']['sid'] = array(
    'title' => t('Webform submission'),
    'help' => t('Webform submission id.'),
    'relationship' => array(
      'base' => 'webform_submissions',
      'base field' => 'sid',
      'handler' => 'views_handler_relationship',
      'label' => t('Webform submission'),
    ),
  );
  return $data;
}
