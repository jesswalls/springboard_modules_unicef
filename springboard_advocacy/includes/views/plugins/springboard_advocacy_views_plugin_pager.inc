<?php
/**
 * @file
 * springboard_advocacy_views_plugin_pager.inc
 */

/**
 * Class springboard_advocacy_views_plugin_pager.
 *
 * Create a custom pager to fix a long-term views pager bug.
 */
class springboard_advocacy_views_plugin_pager extends views_plugin_pager_full {

  /**
   * @param $input
   * @return string
   * @throws Exception
   */
  function render($input) {
    
    // bug fix for multiple select checkboxes
    // invalid values in query string
    // https://www.drupal.org/node/2303939
    foreach ($input as $field_name => $field_value) {
      if(is_array($field_value)) {
        foreach ($field_value as $index => $value) {
          if (empty($value)) { 
            unset($input[$field_name][$index]);
          }
        }
      }
    }

    $pager_theme = views_theme_functions('pager', $this->view, $this->display);
    // The 0, 1, 3, 4 index are correct. See theme_pager documentation.
    $tags = array(
      0 => $this->options['tags']['first'],
      1 => $this->options['tags']['previous'],
      3 => $this->options['tags']['next'],
      4 => $this->options['tags']['last'],
    );
    $output = theme($pager_theme, array(
      'tags' => $tags,
      'element' => $this->options['id'],
      'parameters' => $input,
      'quantity' => $this->options['quantity'],
    ));
    return $output;
  }
}
