<?php

/**
 * Callback handler for 'node/%/performance' menu item.
 *
 * Generates and outputs deliverability reports for a particular message action.
 */
function sba_message_action_performance_page($nid) {
  // CSS and JS assets
  drupal_add_css(drupal_get_path('module', 'sba_message_action') . '/css/message-performance.css');

  // Load up the message action node.
  $node = node_load($nid);

  // API Client instance
  $client = springboard_advocacy_api_call();
  // Try to make the API call and if it fails return a response.
  $responses =  sba_message_action_report_cache($client, $node->advocacy_id);
  // Check the status of the API call return and if it's an error return that to the browser.
  if (isset($responses['report']->error)):
    return 'Sorry, no performance metrics are available for this message.';
  endif;

  $deliverablity_targets = sba_message_action_performance_targets_table($responses, $node);

  return $deliverablity_targets;
}

/**
 * Helper function to convert target deliverability report data into
 * a data structure that can be rendered in an HTML table.
 */
function sba_message_action_performance_targets_table($responses, $node) {

  $targets = !empty($responses['report']->data->targets) ? $responses['report']->data->targets : array();
  $targets = sba_message_action_pager_default_initialize($targets, 10);

  $rows = array();
  $advocacyId = $node->advocacy_id;
  foreach ($targets as $target) {
      // Get the target deliverability metrics for this target
    $rows[] = array(
      $target->salutation . ' ' . $target->first_name . ' ' . $target->last_name,
      $target->party,
      $target->state,
      $target->district_code,
      $target->deliverability->totalMessages,
      $target->deliverability->delivered,
      $target->deliverability->failed,
      $target->deliverability->deliverabilityIndexPercent
    );
  }

  // Define the table header
  $header = array('Name', 'Party', 'State', 'District', 'Total Messages Sent', 'Delivered Messages', 'Failed Messages', 'Deliverability Index');
  $tabs = theme('messsage_deliverability_tabs', array(
    'nodeId' => $node->nid
  ));

  $queueReadyItems = $responses['queue']['ready'];
  $queuePausedItems = $responses['queue']['paused'];
  $queueCanceledItems = $responses['queue']['cancelled'];

  $output = theme('messsage_deliverability_dashboard', array(
    'targets_table_header' => $header,
    'targets'              => $rows,
    'report'               => $responses['report'],
    'queueReadyItems'      => $queueReadyItems,
    'queuePausedItems'     => $queuePausedItems,
    'queueCanceledItems'   => $queueCanceledItems,
    'nodeId'               => $node->nid,
    'tabs'                 => $tabs
  ));

  return $output;
}

/**
 * Modified version of pager.inc function pager_default_initialize().
 *
 * Slices the array of targets into pageable segments.
 *
 * @param $rows
 * @param int $limit
 * @param int $element
 * @return array
 */
function sba_message_action_pager_default_initialize($rows, $limit = 9, $element = 0) {
   global $pager_page_array, $pager_total, $pager_total_items, $pager_limits;
  $page = pager_find_page($element);
  // We calculate the total of pages as ceil(items / limit).
  $pager_total_items[$element] = count($rows);
  $pager_total[$element] = ceil($pager_total_items[$element] / $limit);
  $pager_page_array[$element] = max(0, min($page, ((int) $pager_total[$element]) - 1));
  $pager_limits[$element] = $limit;

  return array_slice($rows, $pager_page_array[$element] * $limit, $limit, TRUE);
}

/**
 * Implements hook_preprocess()
 * @param $variables
 * @throws \Exception
 */
function sba_message_action_preprocess_messsage_deliverability_dashboard(&$vars)
{
  // Sanitize the targets data
  foreach ($vars['targets'] as $key => $data) {
    foreach ($data as $itemKey => $value) {
      $vars['targets'][$key][$itemKey] = check_plain($value);
    }
  }

  // Sanitize report data
  $vars['totalMessages'] = isset($vars['report']->data->totalMessages) ? check_plain($vars['report']->data->totalMessages) : 0;
  $vars['delivered'] = isset($vars['report']->data->delivered) ? check_plain($vars['report']->data->delivered) : 0;
  $vars['failed'] = isset($vars['report']->data->failed) ? check_plain($vars['report']->data->failed) : 0;
  $vars['percentage'] = isset($vars['report']->data->deliverabilityIndexPercentage) ? check_plain($vars['report']->data->deliverabilityIndexPercentage) : 0;

  // Render targets table
  $targetsTable = theme('table', array('header' => $vars['targets_table_header'], 'rows' => $vars['targets']));
  $targetsTable  .= theme('pager', array('quantity' => 1));

  $vars['targets_table'] = $targetsTable;
}


function sba_message_action_report_cache($client, $advocacy_id) {
  $responses = &drupal_static(__FUNCTION__);
  $report = $client->invokeClientMethod('getTargetDeliverability', $advocacy_id);
  if (empty($responses)) {
    if ($cache = cache_get($advocacy_id, 'cache_deliverability_report')) {
      $responses = $cache->data;
      if(REQUEST_TIME > $cache->expire) {
        cache_clear_all($advocacy_id, 'cache_deliverability_report');
      }
    }
    else {
      $report = $client->invokeClientMethod('getTargetDeliverability', $advocacy_id);
      $responses['report'] = $report;
      $queueReady = $client->invokeClientMethod('getQueueMessagesCountByStatus', $advocacy_id, 'ready');
      $queuePaused = $client->invokeClientMethod('getQueueMessagesCountByStatus', $advocacy_id, 'paused');
      $queueCanceled = $client->invokeClientMethod('getQueueMessagesCountByStatus', $advocacy_id, 'canceled');
      $queueReadyItems = !empty($queueReady->data->count) ? $queueReady->data->count : 0;
      $queuePausedItems = !empty($queuePaused->data->count) ? $queuePaused->data->count : 0;
      $queueCanceledItems = !empty($queueCanceled->data->count) ? $queueCanceled->data->count : 0;
      $responses['queue'] = array('ready' => $queueReadyItems, 'paused' => $queuePausedItems, 'cancelled' => $queueCanceledItems);
      cache_set($advocacy_id, $responses, 'cache_deliverability_report', REQUEST_TIME + 600);
    }
  }
  return $responses;
}

function sba_message_action_target_cache($client, $target_id, $advocacy_id) {
  $responses = &drupal_static(__FUNCTION__);

  if (empty($responses)) {
    if ($cache = cache_get($advocacy_id .':' . $target_id, 'cache_deliverability_target')) {
      $responses = $cache->data;
      if(REQUEST_TIME > $cache->expire) {
        cache_clear_all($advocacy_id.':' . $target_id, 'cache_deliverability_target');
      }
    }
    else {
      $responses = $client->invokeClientMethod('getSingleTargetDeliverability', $advocacy_id, $target_id);
      cache_set($advocacy_id.':' . $target_id, $responses, 'cache_deliverability_target', REQUEST_TIME + 600);
    }
  }
  return $responses;
}