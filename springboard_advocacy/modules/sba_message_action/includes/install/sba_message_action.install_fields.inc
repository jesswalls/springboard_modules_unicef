<?php

/**
 * @file
 * Install helper functions for field API fields.
 */

/**
 * Create FieldAPi fields for message actions.
 */
function _sba_message_action_create_node_fields($update = false) {

  $fields = array(
    'field_message_action_img' => array(
      'active' => 1,
      'cardinality' => 1,
      'deleted' => 0,
      'entity_types' => array('node'),
      'field_name' => 'field_message_action_img',
      'foreign keys' => array(
        'fid' => array(
          'columns' => array(
            'fid' => 'fid',
          ),
          'table' => 'file_managed',
        ),
      ),
      'indexes' => array(
        'fid' => array(
          0 => 'fid',
        ),
      ),
      'locked' => 0,
      'module' => 'image',
      'settings' => array(
        'default_image' => 0,
        'uri_scheme' => 'public',
      ),
      'translatable' => 0,
      'type' => 'image',

      '_instance' => array(
        'bundle' => 'sba_message_action',
        'deleted' => 0,
        'description' => '',
        'display' => array(
          'default' => array(
            'label' => 'hidden',
            'module' => 'image',
            'settings' => array(
              'image_link' => '',
              'image_style' => '',
            ),
            'type' => 'image',
            'weight' => -1,
          ),
          'teaser' => array(
            'label' => 'above',
            'settings' => array(),
            'type' => 'hidden',
            'weight' => 0,
          ),
        ),
        'entity_type' => 'node',
        'field_name' => 'field_message_action_img',
        'label' => 'Image',
        'required' => 0,
        'settings' => array(
          'alt_field' => 1,
          'default_image' => 0,
          'file_directory' => '',
          'file_extensions' => 'png gif jpg jpeg',
          'max_filesize' => '',
          'max_resolution' => '',
          'min_resolution' => '',
          'title_field' => 0,
          'user_register_form' => FALSE,
        ),
        'widget' => array(
          'active' => 1,
          'module' => 'image',
          'settings' => array(
            'preview_image_style' => 'thumbnail',
            'progress_indicator' => 'throbber',
          ),
          'type' => 'image_image',
          'weight' => 0,
        ),
      ),
    ),
  );

  $fields['body'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'node',
    ),
    'field_name' => 'body',
    'foreign keys' => array(
      'format' => array(
        'columns' => array(
          'format' => 'format',
        ),
        'table' => 'filter_format',
      ),
    ),
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(),
    'translatable' => 0,
    'type' => 'text_with_summary',
    '_instance' => array(
      'bundle' => 'sba_message_action',
      'default_value' => NULL,
      'deleted' => 0,
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'text',
          'settings' => array(),
          'type' => 'text_default',
          'weight' => 5,
        ),
        'teaser' => array(
          'label' => 'hidden',
          'module' => 'text',
          'settings' => array(
            'trim_length' => 600,
          ),
          'type' => 'text_summary_or_trimmed',
          'weight' => 5,
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'body',
      'label' => 'Body',
      'required' => 1,
      'settings' => array(
        'display_summary' => 1,
        'text_processing' => 1,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'rows' => 20,
          'summary_rows' => 5,
        ),
        'type' => 'text_textarea_with_summary',
        'weight' => 5,
      ),
    ),
  );

  // Exported field_base: 'field_message_call_to_action'
  $fields['field_message_call_to_action'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_message_call_to_action',
    'foreign keys' => array(
      'format' => array(
        'columns' => array(
          'format' => 'format',
        ),
        'table' => 'filter_format',
      ),
    ),
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
    '_instance' => array(
      'bundle' => 'sba_message_action',
      'default_value' => NULL,
      'deleted' => 0,
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'text',
          'settings' => array(),
          'type' => 'text_default',
          'weight' => 4,
        ),
        'teaser' => array(
          'label' => 'hidden',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 4,
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_message_call_to_action',
      'label' => 'Call to Action',
      'required' => 0,
      'settings' => array(
        'text_processing' => 0,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => 60,
        ),
        'type' => 'text_textfield',
        'weight' => 4,
      ),
    ),
  );

  $fields['field_sba_test_mode'] = array(
    'active' => 1,
    'cardinality' => 2,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_sba_test_mode',
    'foreign keys' => array(),
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        1 => 'Enabled',
      ),
      'allowed_values_function' => '',
    ),
    'translatable' => 0,
    'type' => 'list_text',
    '_instance' => array(
      'bundle' => 'sba_message_action',
      'deleted' => 0,
      'description' => 'Check this box to enable test mode. Messages will not be sent to any configured targets when test mode is enabled.',
      'display' => array(
        'default' => array(
          'label' => 'Above',
          'module' => 'list',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 3,
        ),
        'teaser' => array(
          'label' => 'hidden',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_sba_test_mode',
      'label' => 'Enable Test Mode',
      'required' => 0,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'options',
        'settings' => array(),
        'type' => 'options_buttons',
        'weight' => 31,
      ),
    ),
  );

  // Exported field_base: 'field_sba_test_mode_email'
  $fields['field_sba_test_mode_email'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_sba_test_mode_email',
    'foreign keys' => array(
      'format' => array(
        'columns' => array(
          'format' => 'format',
        ),
        'table' => 'filter_format',
      ),
    ),
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
    '_instance' => array(
      'bundle' => 'sba_message_action',
      'default_value' => NULL,
      'deleted' => 0,
      'description' => 'Enter an email address for test mode. Test messages will be sent to this address instead of to the configured targets.',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'text',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 4,
        ),
        'teaser' => array(
          'label' => 'none',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_sba_test_mode_email',
      'label' => 'Test Mode Email Address',
      'required' => 0,
      'settings' => array(
        'text_processing' => 0,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => 60,
        ),
        'type' => 'text_textfield',
        'weight' => 32,
      ),
    ),
  );

  foreach ($fields as $key => $values) {
    $instance = $values['_instance'];
    unset($values['_instance']);
    $base = field_info_field($key);
    $node = field_info_instance('node', $key, 'sba_message_action');
    if (empty($base)) {
      field_create_field($values);
    }
    if (empty($node)) {
      field_create_instance($instance);
    }

  }
  if ($update == FALSE) {

    $export = array();

    $field_group = new stdClass();
    $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
    $field_group->api_version = 1;
    $field_group->identifier = 'group_sba_test_mode|node|sba_message_action|form';
    $field_group->group_name = 'group_sba_test_mode';
    $field_group->entity_type = 'node';
    $field_group->bundle = 'sba_message_action';
    $field_group->mode = 'form';
    $field_group->parent_name = '';
    $field_group->label = 'Test Mode';
    $field_group->weight = '33';
    $field_group->children = array(
      0 => 'field_sba_test_mode',
      1 => 'field_sba_test_mode_email',
    );
    $field_group->format_type = 'fieldset';
    $field_group->format_settings = array(
      'label' => 'Test Mode',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-test-mode field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsible',
    );

    $export['group_sba_test_mode|node|sba_message_action|form'] = $field_group;

    foreach ($export as $field_group) {
      field_group_group_save($field_group);
    }
  }
}

/**
 * Delete springboard message action fields.
 */
function _sba_message_action_delete_fields() {
  $fields = array(
    'sba_message_action_call_to_action',
    'field_message_action_img',
    'field_sba_legislative_issues',
    'field_sba_test_mode',
    'field_sba_test_mode_email',
  );
  foreach ($fields as $field_name) {
    $field = field_info_instance('node', $field_name, 'sba_message_action');
    field_delete_instance($field);
    $field = field_info_field($field_name);
    field_delete_field($field);
  }
  drupal_set_message('Springboard message action fields deleted.');
}
