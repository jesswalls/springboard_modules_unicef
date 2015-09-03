<?php

/**
 * @file
 * Definition of springboard_advocacy_views_handler_filter_string.
 * 
 */

/**
 * Class springboard_advocacy_views_handler_filter_string
 *
 * Simplify and replace the query options provided by (the DB-oriented) parent class.
 */
class springboard_advocacy_views_handler_filter_string extends views_handler_filter_string {

  /**
   * Limit operators to equals.
   */
 function operators() {
    $operators = array(
      '=' => array(
        'title' => t('Contains'),
        'short' => t('contains'),
        'method' => 'op_contains',
        'values' => 1,
      ),
    );
    return $operators;
  }

  /**
   * Remove default options.
   */
  function operator_options($which = 'title') {
    $options = array();
    foreach ($this->operators() as $id => $info) {
      $options[$id] = $info[$which];
    }
    return $options;
  }

  /**
   * Pare down the default query definition.
   */
  function query() {
    $field = $this->real_field;
    $info = $this->operators();
    if (!empty($info[$this->operator]['method'])) {
      $this->{$info[$this->operator]['method']}($field);
    }
  }


  /**
   * Override parent method.
   * @param $field
   */
  function op_contains($field) {
    $this->query->search_terms[$field] = $this->value;
  }
}
