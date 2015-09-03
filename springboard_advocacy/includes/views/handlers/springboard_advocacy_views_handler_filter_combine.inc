<?php

/**
 * @file
 * Definition of springboard_advocacy_views_handler_filter_combine.
 */


/**
 * Class springboard_advocacy_views_handler_filter_combine
 *
 *  Filter handler which allows to search on multiple fields.
 */
class springboard_advocacy_views_handler_filter_combine extends springboard_advocacy_views_handler_filter_string {
  /**
   * @var views_plugin_query_default
   */
  public $query;

  /**
   * Create a combination field "fields".
   *
   * @return array
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['fields'] = array('default' => array());
    return $options;
  }

  /**
   * @param $form
   * @param $form_state
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $this->view->init_style();

    // Allow to choose all fields as possible.
    if ($this->view->style_plugin->uses_fields()) {
      $options = array();
      foreach ($this->view->display_handler->get_handlers('field') as $name => $field) {
        $options[$name] = $field->ui_name(TRUE);
      }
      if ($options) {
        $form['fields'] = array(
          '#type' => 'select',
          '#title' => t('Choose fields to combine for filtering'),
          '#description' => t(""),
          '#multiple' => TRUE,
          '#options' => $options,
          '#default_value' => $this->options['fields'],
        );
      }
      else {
        form_set_error('', t('You have to add some fields to be able to use this filter.'));
      }
    }
  }

  /**
   * Format the combined fields into a query-string compatible format of:
   * 'fields' => field names
   * 'values' => field values
   */
  function query() {
    $this->view->_build('field');
    $fields = array();
    $query_string = array();
    foreach ($this->options['fields'] as $id) {
      $field = $this->view->field[$id];
      $fields[] = $field->real_field;
    }
    if (!empty($fields)) {
      $query_string['fields'] = implode(' ', $fields);
      $query_string['values'] = $this->value;
     // $query_string['search_type'] = 'custom';
      $info = $this->operators();
      if (!empty($info[$this->operator]['method'])) {
        $this->{$info[$this->operator]['method']}($query_string);
      }
    }
  }

  /**
   * Add the query to the view object.
   * @param Array $query_string
   */
  function op_contains($query_string) {
    $this->query->search_terms = $query_string;
  }
}
