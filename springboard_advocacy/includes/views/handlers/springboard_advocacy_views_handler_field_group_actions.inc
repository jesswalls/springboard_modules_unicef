<?php

/**
 * @file
 * Definition of views_handler_field_target_actions.
 */

/**
 * A handler to provide group action links.
 *
 * NOT currently implemented anywhere. Custom groups
 * are a planned feature.
 *
 * @ingroup views_field_handlers
 */
class springboard_advocacy_views_handler_field_group_actions extends views_handler_field {

  function query() {
   // override
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['which_links'] = array('default' => array('view', 'edit', 'delete'), 'translatable' => TRUE);
    return $options;
  }

  function options_form(&$form, &$form_state) {
    $form['which_links'] = array(
      '#type' => 'checkboxes',
      '#options' => drupal_map_assoc(array(t('view'), t('edit'), t('delete'))),
      '#title' => t('Which links should show'),
      '#default_value' => $this->options['which_links'],
      '#description' => t('Select whether view, edit and/or delete links are visible. Edit and Delete links will only be visible on custom groups, and to properly permissioned users.')
    );
    parent::options_form($form, $form_state);
  }

  function render($values) {
    return $this->render_links($values);
  }

  function render_links($values) {

    $links  = array();
    if (user_access('view targets') && !empty($this->options['which_links']['view'])) {
      $links[] = l('view', 'springboard/advocacy/groups/'. $values->id . '/view');
    }
    if ($values->class_name != "Legislator" && user_access('edit targets') && !empty($this->options['which_links']['edit'])) {
      $links[] = l('edit', 'springboard/advocacy/groups/'. $values->id . '/edit');
    }
    if ($values->class_name != "Legislator" && user_access('delete targets') && !empty($this->options['which_links']['delete'])) {
      $links[] = l('delete', 'springboard/advocacy/groups/'. $values->id . '/delete');
    }
    return implode(' | ', $links);
  }
}


