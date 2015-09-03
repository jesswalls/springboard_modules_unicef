<?php

/**
 * @file
 * Definition of views_handler_field_target_actions.
 */

/**
 * A handler to provide target_action links.
 *
 * @ingroup views_field_handlers
 */
class springboard_advocacy_views_handler_field_target_actions extends views_handler_field {

  /**
   * Prevent the default database query.
   */
  function query() {
  }

  /**
   * Define link options.
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['which_links'] = array(
      //'default' => array('view', 'edit', 'delete'), 
      'translatable' => TRUE);
    return $options;
  }


  /**
   * Form definition for link visibility options.
   * allows the admin to select which links to display.
   * @param $form
   * @param $form_state
   */
  function options_form(&$form, &$form_state) {
    $form['which_links'] = array(
      '#type' => 'checkboxes',
      '#options' => drupal_map_assoc(array(t('edit'), t('delete'), t('add'))),
      '#title' => t('Which links should show'),
      '#default_value' => $this->options['which_links'],
      '#description' => t('Select whether view, edit and/or delete links are visible. Edit and Delete links will only be visible on custom targets, and to properly permissioned users.')
    );
    parent::options_form($form, $form_state);
  }


  /**
   *  Render links.
   * @param $values
   * @return string
   */
  function render($values) {
    return $this->render_links($values);
  }


  /**
   * Render Helper.
   *
   * Display links based on option choices, result class type and user permission.
   *
   * @param $values
   * @return string
   */
  function render_links($values) {

    $legislator = TRUE;

    if (isset($values->class_name) && $values->class_name == "Legislator") {
      $path = 'springboard/advocacy/targets/legislator';
    }
    else {
      $path = 'springboard/advocacy/targets/custom-targets';
      $legislator = FALSE;
    }

    $links  = array();

    // Add Target to Action Link used in message entity's target search form results.
    if (user_access('add target to action') && !empty($this->options['which_links']['add'])) {
      $links[] = l(t('add'), 'add-target', array(
        'external' => TRUE,
        'attributes' => array('class' => array('advocacy-add-target')),
        'query' => array(
          'id' => $values->id,
          'first' => $values->first_name,
          'last' => $values->last_name,
          'sal' => $values->salutation
        )
      ));
    }

    // Custom targets can be edited and deleted. Legislators can't.
    if (!$legislator) {
      if (user_access('edit targets') && !empty($this->options['which_links']['edit'])) {
        $links[] = l(t('edit'), $path . '/' . $values->id . '/edit');
      }
      if (user_access('delete targets') && !empty($this->options['which_links']['delete'])) {
        $links[] = l(t('delete'), $path . '/' . $values->id . '/delete');
      }
    }

    return implode(' | ', $links);
  }
}


