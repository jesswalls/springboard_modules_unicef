<?php
/**
 * @file
 * Configuration for fields that are added to fundraiser enabled content types.
 */

/**
 * Add fields needed by fundraiser to a node type.
 *
 * @param string $type
 *   The content type to check if the fundraiser fields exist,
 *   and if not the fields are added to the type.
 */
function _fundraiser_add_default_fields($type) {
  $fields = _fundraiser_default_fields_settings($type);
  foreach ($fields as $field_name => $field) {
    // These should be added on each page request, but to be sure do it again.
    module_load_include('inc', 'field', 'field.crud');
    module_load_include('inc', 'field', 'field.info');

    // If the field doesn't exist create it.
    if (!field_info_field($field_name)) {
      field_create_field($field['field_config']);
    }
    // Before adding the field check that it does not exist on the node type.
    if (!field_info_instance('node', $field_name, $type)) {
      field_create_instance($field['field_instance']);
    }
  }
}

/**
 * Returns an array of field configurations.
 *
 * This is copied from a features export.
 *
 * @param string $type
 *    The type of node these fields will be added to,
 *    used to populate the bundle property.
 */
function _fundraiser_default_fields_settings($type) {
  $fields = array();

  $fields['field_fundraiser_internal_name'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_fundraiser_internal_name',
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
      'locked' => '0',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
      ),
      'translatable' => '0',
      'type' => 'text',
    ),
    'field_instance' => array(
      'bundle' => $type,
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '2',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_fundraiser_internal_name',
      'label' => 'Internal Name',
      'required' => 1,
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
        'weight' => '0',
      ),
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Internal Name');

  $fields['field_fundraiser_currency'] = array(
    'field_config' => fundraiser_currency_field_definition(),
    'field_instance' => fundraiser_currency_field_instance($type),
  );

  t('Default currency');

  return $fields;
}

/**
 * The currency field definition.
 *
 * @return array
 *   The field definition for the currency fundraiser field.
 */
function fundraiser_currency_field_definition() {
  return array(
    'translatable' => '0',
    'entity_types' => array(),
    'settings' => array(
      'allowed_values_function' => 'fundraiser_currency_field_get_currency_options',
    ),
    'storage' => array(
      'type' => 'field_sql_storage',
      'settings' => array(),
      'module' => 'field_sql_storage',
      'active' => '1',
      'details' => array(
        'sql' => array(
          'FIELD_LOAD_CURRENT' => array(
            'field_data_field_default_currency' => array(
              'value' => 'field_fundraiser_currency_value',
            ),
          ),
          'FIELD_LOAD_REVISION' => array(
            'field_revision_field_default_currency' => array(
              'value' => 'field_fundraiser_currency_value',
            ),
          ),
        ),
      ),
    ),
    'foreign keys' => array(),
    'indexes' => array(
      'value' => array('value'),
    ),
    'field_name' => 'field_fundraiser_currency',
    'type' => 'list_text',
    'module' => 'list',
    'active' => '1',
    'locked' => '0',
    'cardinality' => '1',
    'deleted' => '0',
    'columns' => array(
      'value' => array(
        'type' => 'varchar',
        'length' => 32,
        'not null' => TRUE,
      ),
    ),
  );
}

/**
 * Provides the currency field instance configuration.
 *
 * @param string $bundle_name
 *   The name of the bundle to add the instance to.
 *
 * @return array
 *   The currency field instance array with included bundle name.
 */
function fundraiser_currency_field_instance($bundle_name) {
  return array(
    'label' => 'Default currency',
    'widget' => array(
      'weight' => '2',
      'type' => 'options_select',
      'module' => 'options',
      'active' => 1,
      'settings' => array(),
    ),
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'display' => array(
      'default' => array(
        'type' => 'hidden',
        'label' => 'above',
        'settings' => array(),
        'weight' => 4,
      ),
      'teaser' => array(
        'type' => 'hidden',
        'label' => 'above',
        'settings' => array(),
        'weight' => 0,
      ),
    ),
    'required' => 1,
    'description' => 'The default currency for this donation form.',
    'default_value' => array(
      array('value' => commerce_default_currency()),
    ),
    'field_name' => 'field_fundraiser_currency',
    'entity_type' => 'node',
    'bundle' => $bundle_name,
    'deleted' => '0',
  );
}
