<?php

/**
 * @file
 * Contains a Views field handler to take care of displaying deletes links
 * as fields
 */


class sba_message_handler_delete_link_field extends sba_message_handler_link_field {
  function construct() {
    parent::construct();
    $this->additional_fields['type'] = 'type';
  }

  function render($values) {
    $type = $values->{$this->aliases['type']};
    
    //Creating a dummy model to check access against
    $dummy_model = (object) array('type' => $type);
    if (!sba_message_access('edit', $dummy_model)) {
      return;
    }
    
    $text = !empty($this->options['text']) ? $this->options['text'] : t('delete');
    $sba_message_id = $values->{$this->aliases['sba_message_id']};
    $message = sba_message_load($sba_message_id);
    $wrapper = entity_metadata_wrapper('sba_message', $message);
    $nid = $wrapper->field_sba_action_id->value()->nid;
    return l($text, 'node/' . $nid  .'/messages/sba_message/' . $sba_message_id . '/delete');
  }
}
