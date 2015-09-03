<?php

/**
 * @file Goals UI forms.
 */

/**
 * Add a goal.
 */
function webform_goals_add($form, $form_state, $goal = array()) {

  ctools_include('plugins');

  if (!empty($goal['gid'])) {
    $form['gid'] = array(
      '#type' => 'value',
      '#value' => $goal['gid'],
    );
  }
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Goal name'),
    '#default_value' => isset($goal['name']) ? $goal['name'] : '',
    '#required' => TRUE,
  );
  $contexts = webform_goals_list_context();
  $selected_context = _webform_goals_get_selected_context($form_state, $goal);
  $metrics = webform_goals_list_metrics($selected_context, $form_state, $goal);
  $selected_metric = _webform_goals_get_selected_metric($selected_context, $form_state, $goal);
  $selected_bar = _webform_goals_get_selected_bar($form_state, $goal);
  //$selected_metric = !empty($form_state['values']['metrics']) ? $metrics[$form_state['values']['metrics']] : $metrics['submission_count'];
  foreach ($contexts as $key => $context) {
    $context_options[$key] = $context['name'];
  }
  $form['context_container'] = array(
    '#type' => 'fieldset',
    '#title' => t('Goal context'),
  );
  $form['context_container']['context'] = array(
    '#type' => 'radios',
    '#title' => t(''),
    '#options' => $context_options,
    '#default_value' => isset($selected_context['id']) ? $selected_context['id'] : '',
    '#ajax' => array(
      'callback' => 'webform_goals_context_callback',
      'wrapper' => 'context-options',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );
  $form['context_container']['context_description'] = array(
    '#type' => 'markup',
    '#markup' => !empty($selected_context['description']) ? $selected_context['description'] : '',
    '#prefix' => '<div id="context-description">',
    '#suffix' => '</div>',
  );

  $form['context_container']['options_wrapper'] = array(
    '#type' => 'item',
    '#value' => '',
    '#prefix' => '<div id="context-options">',
    '#suffix' => '</div>',
  );

  if (!empty($selected_context['settings_callback'])) {
    $form['context_container']['options_wrapper']['options'] = array(
      '#type' => 'fieldset',
      '#title' => 'Additional settings',
      '#description' => t('The selected context requires the following additional settings:'),
    );
    $func = $selected_context['settings_callback'];
    $func($form['context_container']['options_wrapper']['options'], $form_state, $goal);

  }

  // SF Webform should add the Salesforce context.
  // Metrics radios (standard + plugin architecture)
  foreach ($metrics as $key => $metric) {
    $metrics_options[$key] = $metric['name'];
  }

  // #AJAX enable so minimum display limit UI can be swapped.
  $form['metrics_wrapper'] = array(
    '#type' => 'fieldset',
    '#title' => t('What do you want to track?'),
    '#prefix' => '<div id="context-metrics">',
    '#suffix' => '</div>',
  );
  $form['metrics_wrapper']['metrics'] = array(
    '#type' => 'radios',
    '#title' => '',
    // Get valid options from plugin
    '#options' => $metrics_options,
    '#default_value' => $selected_metric['id'],
    '#ajax' => array(
      'callback' => 'webform_goals_metrics_callback',
      'wrapper' => 'context-metrics',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  // Unpack custom form elements associated with the current metric.
  if (!empty($selected_metric['child_elements'])) {
    foreach ($selected_metric['child_elements'] as $key => $element) {
      $form['metrics_wrapper']['metrics_children'][$key] = $element;
    }
  }

  // Goal
  $form['goal_wrapper'] = array(
    '#type' => 'fieldset',
    '#title' => t('Goal'),
    '#prefix' => '<div id="options-goal-settings">',
    '#suffix' => '</div>',
  );
  $form['goal_wrapper']['target_value'] = array(
    '#type' => 'textfield',
    '#size' => 8,
    '#title' => !empty($selected_metric['form_text']['target_value']['title']) ? $selected_metric['form_text']['target_value']['title'] : t('Set a target number for your goal'),
    '#description' => !empty($selected_metric['form_text']['target_value']['description']) ? $selected_metric['form_text']['target_value']['description'] : t('This tells us what your goal is shooting for.'),
    '#default_value' => !empty($goal['target_value']) ? $goal['target_value'] : '',
    '#required' => TRUE,
  );
  $form['goal_wrapper']['seed'] = array(
    '#type' => 'textfield',
    '#title' => !empty($selected_metric['form_text']['seed']['title']) ? $selected_metric['form_text']['seed']['title'] : t('Add this much to the initial goal progress'),
    '#description' => !empty($selected_metric['form_text']['seed']['description']) ? $selected_metric['form_text']['seed']['description'] : t(''),
    '#size' => 8,
    '#attributes' => array('name' => 'seed'),
    '#default_value' => !empty($goal['seed']) ? $goal['seed'] : '',
  );

  // selection-specific minimum display limit, start with value associated with the "Default" option above.
  // Attach js event to onchange or similar to conditionally show starter message ui
  $form['goal_wrapper']['display_threshold'] = array(
    '#type' => 'textfield',
    '#title' => !empty($selected_metric['form_text']['display_threshold']['title']) ? $selected_metric['form_text']['display_threshold']['title'] : t('Progress bar display threshold'),
    '#description' => !empty($selected_metric['form_text']['display_threshold']['description']) ? $selected_metric['form_text']['display_threshold']['description'] : t('The starter message will be displayed until goal progress meets this minimum.'),
    '#size' => 8,
    '#id' => 'edit-display_threshold',
    '#attributes' => array(
      'name' => 'display_threshold',
      'class' => array('container-inline'),
    ),
    '#default_value' => !empty($goal['display_threshold']) ? $goal['display_threshold'] : 0,
  );

  // starter message ui, initially hidden with CSS or JS unless threshold is set.
  // TODO: handling for input formats.
  $form['goal_wrapper']['starter_message'] = array(
    '#type' => 'text_format',
    '#title' => t('Starter message'),
  );
  if (!empty($goal['starter_message'])) {
    $form['goal_wrapper']['starter_message']['#default_value'] = $goal['starter_message'];
    $form['goal_wrapper']['starter_message']['#format'] = $goal['starter_message_format'];
  }
  else {
    $form['goal_wrapper']['starter_message']['#attributes'] = array('placeholder' => t('Enter your personal starter message here.'));
  }
  $form['goal_wrapper']['starter_message']['token_tree'] = array(
    '#type' => 'fieldset',
    '#title' => t('Replacement patterns'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => theme('token_tree', array('token_types' => array('webform_goal'))),
    '#weight' => 10,
  );

  // goal timeframe fieldset & date select fields
  $form['timeframe'] = array(
    '#type' => 'fieldset',
    '#title' => t('Goal timeframe'),
  );
  $format = 'm-d-Y';
  $form['timeframe']['start_date'] = array(
    '#type' => 'date_select',
    '#title' => t('Start date'),
    '#date_format' => $format,
    '#date_year_range' => '-3:+3',
    '#date_label_position' => 'within',
    '#default_value' => !empty($goal['start_date']) ? date('Y-m-d h:i:s', $goal['start_date']) : NULL,
  );
  $form['timeframe']['end_date'] = array(
    '#type' => 'date_select',
    '#title' => t('End date'),
    '#date_format' => $format,
    '#date_year_range' => '-3:+3',
    '#date_label_position' => 'within',
    '#default_value' => !empty($goal['end_date']) ? date('Y-m-d h:i:s', $goal['end_date']) : NULL,
  );
  $form['timeframe']['auto_expire'] = array(
    '#type' => 'checkbox',
    '#title' => t('Auto expire'),
    '#description' => t('Stop displaying goal progress after the end date has been reached.'),
    '#default_value' => !empty($goal['auto_expire']) ? $goal['auto_expire'] : 0,
  );
  // configurable goal template, start with "default" template.
  $form['template'] = array(
    '#type' => 'fieldset',
    '#title' => t('Display'),
  );
  $form['template']['progress_bar'] = array(
    '#type' => 'select',
    '#title' => t('Progress bar style'),
    '#options' => _webform_goals_progress_bar_options(),
    '#default_value' => $selected_bar,
    '#ajax' => array(
      'callback' => 'webform_goals_progress_bar_callback',
      'wrapper' => 'display-progress-demo',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  $form['template']['progress_bar_demo'] = array(
    '#type' => 'markup',
    '#markup' => isset($selected_bar) ? webform_goals_render_progress_bar($selected_bar, 75, 1) : '',
    '#prefix' => '<div id="display-progress-demo" style="width:450px">',
    '#suffix' => '</div>',
  );
  $form['template']['template'] = array(
    '#type' => 'text_format',
    '#title' => t('Goal template'),
    '#description' => t(''),
    // @todo theme function to output default template
    '#default_value' => !empty($goal['template']) ? $goal['template'] : theme('webform_goals_default_template'),
  );
  if (!empty($goal['template_format'])) {
    $form['template']['template']['#format'] = $goal['template_format'];
  }
  $form['template']['template']['token_tree'] = array(
    '#type' => 'fieldset',
    '#title' => t('Replacement patterns'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => theme('token_tree', array('token_types' => array('webform_goal'))),
    '#weight' => 10,
  );
  // Add token UI for goal tokens.
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  $form['#validate'][] = 'webform_goals_add_validate';
  $form['#submit'][] = 'webform_goals_add_submit';
  return $form;
}


function webform_goals_add_validate(&$form, &$form_state) {
  // validate display threshold
  $display = !(empty($form_state['values']['display_threshold'])) ? $form_state['values']['display_threshold'] : 0;
  $target = $form_state['values']['target_value'];
  if ($display && $display >= $target) {
    form_set_error('display_threshold', t('Display threshold settings should be less than the goal target.'));
  }

  // validate start/end dates
  $start_date = !empty($form_state['values']['start_date']) ? strtotime($form_state['values']['start_date']) : 0;
  $end_date =  !empty($form_state['values']['end_date']) ? strtotime($form_state['values']['end_date']) : 0;

  if ($end_date && $start_date > $end_date) {
    form_set_error('end_date', t('End date should not be before start date.'));
  }
}
/**
 * Submission handler for goal add/edit form.
 */
function webform_goals_add_submit($form, &$form_state) {
  $settings = array(
    'gid' => !empty($form_state['values']['gid']) ? $form_state['values']['gid'] : '',
    'name' => $form_state['values']['name'],
    'context' => $form_state['values']['context'],
    'metric' => $form_state['values']['metrics'],
    'extra' => array(),
    'display_threshold' => $form_state['values']['display_threshold'],
    'seed' => $form_state['values']['seed'],
    'target_value' => $form_state['values']['target_value'],
    'starter_message' => $form_state['values']['starter_message']['value'],
    'starter_message_format' => $form_state['values']['starter_message']['format'],
    'start_date' => !empty($form_state['values']['start_date']) ? strtotime($form_state['values']['start_date']) : 0,
    'end_date' => !empty($form_state['values']['end_date']) ? strtotime($form_state['values']['end_date']) : 0,
    'template' => $form_state['values']['template']['value'],
    'template_format' => $form_state['values']['template']['format'],
    'progress_bar' => $form_state['values']['progress_bar'],
  );
  $settings = module_invoke_all('webform_goals_save_goal', $settings, $form_state);
  webform_goals_save_goal($settings);

  $form_state['redirect'] = array('admin/config/content/webform_goals');
}

/**
 * AJAX callback for context radios.
 */
function webform_goals_context_callback($form, $form_state) {
  return array(
    '#type' => 'ajax',
    '#commands' => array(
      ajax_command_replace('#context-description', render($form['context_container']['context_description'])),
      ajax_command_replace("#context-options", render($form['context_container']['options_wrapper'])),
      ajax_command_replace("#context-metrics", render($form['metrics_wrapper'])),
    ),
  );
}

/**
 * AJAX callback for extra settings.
 */
function webform_goals_extra_callback($form, $form_state) {
  return array(
    '#type' => 'ajax',
    '#commands' => array(
      ajax_command_replace("#context-metrics", render($form['metrics_wrapper'])),
    ),
  );
}
/**
 * AJAX callback for metrics radios.
 */
function webform_goals_metrics_callback($form, $form_state) {
  return array(
    '#type' => 'ajax',
    '#commands' => array(
      ajax_command_replace('#context-metrics', render($form['metrics_wrapper'])),
      ajax_command_replace("#options-goal-settings", render($form['goal_wrapper'])),
      ajax_command_replace('#context-seed', render($form['seed_wrapper'])),
    ),
  );
}

function webform_goals_progress_bar_callback($form, $form_state) {
  return array(
    '#type' => 'ajax',
    '#commands' => array(
      ajax_command_replace('#display-progress-demo', render($form['template']['progress_bar_demo'])),
    ),
  );
}

function webform_goals_single_custom_metrics_fields() {

}

function _webform_goals_add_date_defaults($element) {
  $keys = array('month', 'day', 'year');

  foreach ($keys as $key) {
    $element[$key]['#empty_value'] = 0;
    $element[$key]['#empty_option'] = t(ucwords($key));
    unset($element[$key]['#value']);
    $element[$key] = form_process_select($element[$key]);
  }

  return $element;
}

/**
 * Goal deletion form.
 *
 */
function webform_goals_delete($form, $form_state, $goal = array()) {
  $form['confirmation_text'] = array(
    '#markup' => t('Are you sure you want to unrecoverably delete this goal?'),
  );
  $form['gid'] = array(
    '#type' => 'value',
    '#value' => !empty($goal['gid']) ? $goal['gid'] : NULL,
  );
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Delete'),
  );
  $form['actions']['cancel'] = array(
    '#type' => 'submit',
    '#value' => t('Cancel'),
    '#submit' => array('_webform_goals_form_cancel'),
    '#limit_validation_errors' => array(),
  );
  $form['#submit'][] = 'webform_goals_delete_submit';
  return $form;
}

function webform_goals_delete_submit($form, &$form_state) {
  if (is_numeric($form_state['values']['gid']) && $form_state['values']['gid']) {
    webform_goals_delete_goal($form_state['values']['gid']);
    drupal_set_message('Goal has been deleted');
  }
  $form_state['redirect'] = array('admin/config/content/webform_goals');
}

function _webform_goals_form_cancel($form, &$form_state) {
  drupal_goto('admin/config/content/webform_goals');
}

function _webform_goals_progress_bar_options() {
  $options = array(
    'flat_ui' => t('Flat UI'),
    'twitter_basic' => t('Twitter basic'),
    'twitter_striped' => t('Twitter striped'),
    // 'animated' => t('Animated'), // Drupal strips script sent via jsonp so this doesn't work locally.
  );
  drupal_alter('webform_goals_progress_bar_options', $options);
  return $options;
}

// figure out where this should live.
function webform_goals_render_progress_bar($bar_type, $goal_progress, $drupal = FALSE) {
  $output = '';
  switch ($bar_type) {
    case 'flat_ui':
      $output = theme('webform_goals_flat_ui_progress_bar', array('goal_progress' => $goal_progress));
      break;

    case 'twitter_basic':
      $output = theme('webform_goals_twitter_progress_bar', array('goal_progress' => $goal_progress));
      break;

    case 'twitter_striped':
      $output = theme('webform_goals_twitter_striped_progress_bar', array('goal_progress' => $goal_progress));
      break;

    case 'animated':
      $output = theme('webform_goals_animated_progress_bar', array('goal_progress' => $goal_progress, 'drupal' => $drupal));
      break;

  }

  return $output;
}
