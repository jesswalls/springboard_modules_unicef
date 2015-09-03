<?php

/**
 * @file
 * Definition of springboard_advocacy_views_handler_filter_search_types.
 */

class springboard_advocacy_views_handler_filter_search_types extends views_handler_filter_in_operator {

  /**
   * Allows exposed filter "groups" to function properly.
   *
   * @todo remove this if fixed in future views release.
   * bug workaround: https://www.drupal.org/node/2096447
   * can be removed after springboard upgrades to views 7.x-3.8
   * which should be before this module is released
   * not sure what unintended side effects this may have.
   *
   * @param $view
   * @param $options
   */
  function init(&$view, &$options) {
    if (!isset($options['group_info']['default_group_multiple'])) {
      if (is_array($this->options['group_info']['default_group_multiple'])) {
        $options['group_info']['default_group_multiple'] = $this->options['group_info']['default_group_multiple'];
      }
      else {
        $options['group_info']['default_group_multiple'] = array('default' => array());
      }
    }
    parent::init($view, $options);
  }

  /**
   * Format a search query for API. Add search terms to the views object.
   */
  function query() {

    // Process multiple selection fields.
    if (is_array($this->value)) {
      foreach ($this->value as $key => $value) {
        if (empty($value)) {
          unset($this->value[$key]);
        }
      }
      $values = array_values($this->value);
      // The API expects pipe-separated multitple values.
      $values = implode('|', $values);
    }
    else {
      // Not a multi-.
      $values = $this->value;
    }
    if (!empty($values)) {
      $field = str_replace('search_', '', $this->real_field);
      $this->query->search_terms[$field][] = $values;
    }
  }
}
