<?php

class springboard_tag_export_ui extends ctools_export_ui {

  function edit_form(&$form, &$form_state) {
    parent::edit_form($form, $form_state);

    $form['tag'] = array(
      '#type' => 'textarea',
      '#title' => t('Tag'),
      '#default_value' => $form_state['item']->tag,
    );

    $form['placement'] = array(
      '#type' => 'select',
      '#title' => t('Placement'),
      '#default_value' => $form_state['item']->settings['placement'],
      '#options' => _springboard_tag_placement_options(),
    );

    $form['weight'] = array(
      '#type' => 'weight',
      '#title' => t('Weight'),
      '#default_value' => $form_state['item']->weight,
      '#delta' => 10,
      '#description' => t('Optional. Set a heavier value to have a tag rendered below others in the document.'),
    );

    // Visibility options.
    $form['visibility'] = array(
      '#type' => 'container',
      '#tree' => TRUE,
    );

    // Fundraiser visibility options.
    $form['visibility']['fundraiser'] = array(
      '#type' => 'fieldset',
      '#title' => t('Fundraiser Visibility'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#access' => module_exists('fundraiser'),
    );

    $form['visibility']['fundraiser']['confirmation'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show only on donation form confirmation pages'),
      '#default_value' => $form_state['item']->settings['visibility']['fundraiser']['confirmation'],
    );

    // Fundraiser visibility options.
    $form['visibility']['user'] = array(
      '#type' => 'fieldset',
      '#title' => t('User Visibility'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#access' => module_exists('fundraiser'),
    );

    $role_options = array_map('check_plain', user_roles());
    $form['visibility']['user']['roles'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Exclude tag for specific user roles'),
      '#default_value' => $form_state['item']->settings['visibility']['user']['roles'],
      '#options' => $role_options,
      '#description' => t('Exclude this tag for the selected role(s). If you select no roles, the tag will be visible to all users.'),
    );

    // Per-path visibility.
    $form['visibility']['path'] = array(
      '#type' => 'fieldset',
      '#title' => t('Path Visibility'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $form['visibility']['path']['page_specific'] = array(
      '#type' => 'radios',
      '#title' => t('Include tag on specific pages'),
      '#options' => array(
        BLOCK_VISIBILITY_NOTLISTED => t('All pages except those listed'),
        BLOCK_VISIBILITY_LISTED => t('Only the listed pages'),
      ),
      '#default_value' => $form_state['item']->settings['visibility']['path']['page_specific'],
    );

    $form['visibility']['path']['pages'] = array(
      '#type' => 'textarea',
      '#title' => 'Pages',
      '#default_value' => $form_state['item']->settings['visibility']['path']['pages'],
      '#description' => t("Specify pages by using their paths. Enter one path per line. The '*' character is a wildcard."),
    );

    // Per-node type visibility.
    $form['visibility']['node'] = array(
      '#type' => 'fieldset',
      '#title' => t('Content Visibility'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $form['visibility']['node']['type'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Show tag for specific content types'),
      '#default_value' => $form_state['item']->settings['visibility']['node']['type'],
      '#options' => node_type_get_names(),
      '#description' => t('Show this tag only on nodes of the given type(s). If you select no types, there will be no type-specific limitation.'),
    );
  }

  function edit_form_submit(&$form, &$form_state) {
    parent::edit_form_submit($form, $form_state);

    // Since items in our settings are not in the schema, we have to do these manually:
    $form_state['item']->settings['placement'] = $form_state['values']['placement'];
    $form_state['item']->settings['visibility'] = $form_state['values']['visibility'];
  }

  // ------------------------------------------------------------------------
  // These methods are the API for generating the list of exportable items.

  /**
   * Hide the top row of form items on the admin form.
   */
  function list_form(&$form, &$form_state) {
    parent::list_form($form, $form_state);
    $form['top row'] = $form['top row'] + array(
      '#access' => FALSE,
    );
  }

  /**
   * Determine if a row should be filtered out.
   *
   * @return
   *   TRUE if the item should be excluded.
   */
  function list_filter($form_state, $item) {
    // Disable the filtering.
    return FALSE;
  }

  /**
   * Provide a list of sort options.
   *
   * Override this if you wish to provide more or change how these work.
   * The actual handling of the sorting will happen in build_row().
   */
  function list_sort_options() {
    $options = array(
      'weight' => t('Weight'),
      'name' => t('Name'),
      'storage' => t('Storage'),
    );

    return $options;
  }

  /**
   * Build a row based on the item.
   *
   * By default all of the rows are placed into a table by the render
   * method, so this is building up a row suitable for theme('table').
   * This doesn't have to be true if you override both.
   */
  function list_build_row($item, &$form_state, $operations) {
    // Set up sorting
    $name = $item->{$this->plugin['export']['key']};
    $schema = ctools_export_get_schema($this->plugin['schema']);

    // Note: $item->{$schema['export']['export type string']} should have already been set up by export.inc so
    // we can use it safely.
    switch ($form_state['values']['order']) {
      case 'disabled':
        $this->sorts[$name] = empty($item->disabled) . $name;
        break;
      case 'title':
        $this->sorts[$name] = $item->{$this->plugin['export']['admin_title']};
        break;
      case 'name':
        $this->sorts[$name] = $name;
        break;
      case 'weight':
        $this->sorts[$name] = $item->weight;
        break;
      case 'storage':
        $this->sorts[$name] = $item->{$schema['export']['export type string']} . $name;
        break;
    }

    $this->rows[$name]['data'] = array();

    // Add the draggable class.
    $this->rows[$name]['class'] = array('draggable');
    $this->rows[$name]['class'][] = !empty($item->disabled) ? 'ctools-export-ui-disabled' : 'ctools-export-ui-enabled';

    // If we have an admin title, make it the first row.
    if (!empty($this->plugin['export']['admin_title'])) {
      $this->rows[$name]['data'][] = array('data' => check_plain($item->{$this->plugin['export']['admin_title']}), 'class' => array('ctools-export-ui-title'));
    }
    $this->rows[$name]['data'][] = array('data' => check_plain($name), 'class' => array('ctools-export-ui-name'));
    $this->rows[$name]['data'][] = array('data' => check_plain($item->{$schema['export']['export type string']}), 'class' => array('ctools-export-ui-storage'));

    $ops = theme('links__ctools_dropbutton', array('links' => $operations, 'attributes' => array('class' => array('links', 'inline'))));

    // Add the order column. This is only a placeholder replaced later in the form theme function.
    $this->rows[$name]['data'][] = array('data' => check_plain($item->weight));

    $this->rows[$name]['data'][] = array('data' => $ops, 'class' => array('ctools-export-ui-operations'));

    // Add an automatic mouseover of the description if one exists.
    if (!empty($this->plugin['export']['admin_description'])) {
      $this->rows[$name]['title'] = $item->{$this->plugin['export']['admin_description']};
    }
  }

  /**
   * Provide the table header.
   *
   * If you've added columns via list_build_row() but are still using a
   * table, override this method to set up the table header.
   */
  function list_table_header() {
    $header = parent::list_table_header();

    // Add the order columns as the next to last.
    $last = array_pop($header);
    $header[] = array('data' => t('Weight'));
    $header[] = $last;

    return $header;
  }

}
