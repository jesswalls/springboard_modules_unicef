<?php

/**
 * @file
 * Contains a Views field handler to take care of displaying links to entities
 * as fields.
 */

class sba_message_handler_link_field extends views_handler_field {
  function construct() {
    parent::construct();

    $this->additional_fields['sba_message_id'] = 'sba_message_id';
    $this->additional_fields['type'] = 'type';
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['text'] = array('default' => '', 'translatable' => TRUE);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['text'] = array(
      '#type' => 'textfield',
      '#title' => t('Text to display'),
      '#default_value' => $this->options['text'],
    );
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
    $text = !empty($this->options['text']) ? $this->options['text'] : t('view');
    $sba_message_id = $values->{$this->aliases['sba_message_id']};
    $message = sba_message_load($sba_message_id);
    $wrapper = entity_metadata_wrapper('sba_message', $message);
    $nid = $wrapper->field_sba_action_id->value()->nid;
    return l($text, 'node/' . $nid . '/messages/sba_message/' . $sba_message_id);
  }
}
