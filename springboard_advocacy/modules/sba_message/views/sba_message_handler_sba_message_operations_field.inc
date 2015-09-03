<?php

/**
 * This field handler aggregates operations that can be done on a sba_message
 * under a single field providing a more flexible way to present them in a view
 */
class sba_message_handler_sba_message_operations_field extends views_handler_field {
  function construct() {
    parent::construct();

    $this->additional_fields['sba_message_id'] = 'sba_message_id';
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {

    $links = menu_contextual_links('sba_message', 'node/%node/messages/message', array($this->get_value($values, 'sba_message_id')));
    
    if (!empty($links)) {
      return theme('links', array('links' => $links, 'attributes' => array('class' => array('links', 'inline', 'operations'))));
    }
  }
}
