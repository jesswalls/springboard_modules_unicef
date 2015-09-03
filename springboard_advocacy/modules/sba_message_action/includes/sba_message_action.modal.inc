<?php

/**
 * Multi-message popup modal callback for actions with multiple messages.
 *
 * @param bool $js
 *   Is js enabled.
 * @param int $nid
 *   The message action node ID.
 */
function sba_message_action_modal_page($js = NULL, $nid = NULL) {
  if ($nid == NULL) {
    return;
  }
  if ($js) {
    ctools_include('modal');
    ctools_include('ajax');
  }
  $contents = views_embed_view('sba_messages_node', 'block_2', $nid);
  ctools_modal_render(t('Possible Messages'), $contents);
}

function sba_message_action_build_modal() {

  // Multi-message modal popup.
  ctools_include('ajax');
  ctools_include('modal');
  ctools_modal_add_js();
  $message_window = array(
    'message-window-style' => array(
      'modalSize' => array(
        'type' => 'fixed',
        'width' => 600,
        'height' => 440,
        'addWidth' => 10,
        'addHeight' => 100,
        'contentRight' => 0,
        'contentBottom' => 0,
      ),
      'modalOptions' => array(
        'opacity' => .4,
        'background-color' => '#000',
      ),
      'animation' => 'fadeIn',
    ),
  );
  drupal_add_js($message_window, 'setting');
  ctools_add_css('springboard_message_action', 'modal');
}