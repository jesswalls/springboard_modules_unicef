<?php
/**
 * @file
 * Admin functions for Springboard advocacy.
 */

/**
 * Page callback for the admin form.
 */
function springboard_taxonomy_settings_page() {
  $build = array();
  $build['content'] = array(
    'page_description' => array(
      '#id' => 'springboard-taxonomy-settings-page',
      '#type' => 'markup',
      '#markup' => "The Organization's Issues taxonomy can be used to generate feeds and lists of related content throughout your website.",
      '#prefix' => '<div class="springboard-taxonomy-settings-page"><p>',
      '#suffix' => '</p></div>',
    ),
    'springboard_taxonomy_settings_form' => drupal_get_form('springboard_taxonomy_settings_form'),
  );
  return $build;
}

/**
 * Configuration settings form for Springboard taxonomy.
 */
function springboard_taxonomy_settings_form($form, &$form_state) {
  $form = array();

  if (!isset($form_state['storage']['step'])) {
    $form_state['storage']['step'] = 'step_1';
  }

  $form['#submit'][] = 'springboard_taxonomy_settings_submit';

  switch ($form_state['storage']['step']) {
    case 'step_1':

      $types = node_type_get_names();
      $webform_types = variable_get('webform_node_types', array());
      unset($webform_types['webform']);
      $webform_types = array_flip($webform_types);
      $options = array_intersect_key($types, $webform_types);

      $form['springboard_taxonomy_node_types'] = array(
        '#title' => t('Add or remove the Organization Issues taxonomy for the following form types:'),
        '#description' => t('Unchecking any checked items will permanently remove all Organization Issues data from that content type.'),
        '#type' => 'checkboxes',
        '#options' => $options,
        '#default_value' => variable_get('springboard_taxonomy_node_types', ''),
      );
      $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Submit'),
      );
      break;

    case 'step_2':

      $form['#submit'][] = 'system_settings_form_submit';

      $current_settings = variable_get('springboard_taxonomy_node_types', array());
      $new_settings = $form_state['values']['springboard_taxonomy_node_types'];
      $changes = array_diff_assoc($new_settings, $current_settings);

      foreach ($changes as $key => $value) {
        // This is a new content type so don't create a warning message about deleting data.
        if (!isset($current_settings[$key]) && $value === 0) {
          unset($changes[$key]);
        }
      }

     $messages = theme('springboard_taxonomy_confirm_message', array('changes' => $changes));

      $form['#submit'][] = 'system_settings_form_submit';
      $form = confirm_form(
        $form,
        t('Are you sure you want to do this?'),
        'admin/config/content/springboard-taxonomy',
        $messages,
        t('Confirm'),
        t('Cancel')
      );
      break;
  }
  return $form;
}

/**
 * Submit Function.
 *
 * Create or delete field instances.
 *
 * @param array $form
 * @param array $form_state
 */
function springboard_taxonomy_settings_submit($form, &$form_state) {

  switch ($form_state['storage']['step']) {
    case 'step_2':

      $form_state['values'] = $form_state['storage']['step_values']['step_1'];
      $types = $form_state['values']['springboard_taxonomy_node_types'];

      foreach ($types as $type => $status) {
        if ($status === 0) {
          _springboard_taxonomy_delete_instances($type);
        }
        else {
          _springboard_taxonomy_create_instances($type);
        }
      }
      break;

    case 'step_1':
      $form_state['storage']['step_values']['step_1'] = $form_state['values'];
      $form_state['storage']['step'] = 'step_2';
      $form_state['rebuild'] = TRUE;
      break;
  }

}

/**
 * Create taxonomy fields.
 */
function _springboard_taxonomy_create_instances($type) {
  module_load_include('inc', 'field', 'field.crud');
  module_load_include('inc', 'field', 'field.info');
  module_load_include('install', 'springboard_taxonomy');

  foreach (_springboard_taxonomy_field_instance($type) as $field_name => $field) {

    // If somehow the base field was deleted, recreate it.
    if (!field_info_field($field['field_instance']['field_name'])) {
      $base = _springboard_taxonomy_field_base();
      field_create_field($base[$field_name]['field_config']);
    }

    // Create the instance.
    if (!field_info_instance('node', $field['field_instance']['field_name'], $type)) {
      field_create_instance($field['field_instance']);
    }
  }
}

/**
 * Delete taxonomy fields.
 */
function _springboard_taxonomy_delete_instances($type) {
  module_load_include('inc', 'field', 'field.crud');
  module_load_include('inc', 'field', 'field.info');
  module_load_include('install', 'springboard_taxonomy');
  foreach (_springboard_taxonomy_field_instance($type) as $field_name => $field) {
    if (field_info_instance('node', $field['field_instance']['field_name'], $type)) {
      // Set false to avoid deleting base field if no more instances exist.
      field_delete_instance($field['field_instance'], FALSE);
    }
  }
}

function theme_springboard_taxonomy_confirm_message($vars) {
  $changes = $vars['changes'];
  $messages = array();
  if (empty($changes)) {
    $messages[] = t("Settings have not been changed. No updates will occur.");
  }
  else {
    foreach ($changes as $key => $change) {
      if (empty($change)) {
        $messages[] = '<span class = "warning">'
          . t(
            "You are permanently removing all Organization Issues data from the @type content type!",
            array('@type' => $key)
          )
          . '</span>';
      }
      else {
        $messages[] = t(
          "You are adding an Organization Issues taxonomy field to the @type content type.",
          array('@type' => $key)
        );
      }
    }
  }

  $list = theme('item_list', array('items' => $messages));
  return $list;
}