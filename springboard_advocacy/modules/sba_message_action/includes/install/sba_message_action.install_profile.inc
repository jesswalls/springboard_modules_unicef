<?php

/**
 * @file
 * Install helper functions for profile fields.
 */

/**
 * Create the message action user profile fields.
 */
function _sbp_message_action_create_user_profile_fields() {
  $phone_exists = field_info_field('sbp_phone');

  $profile_phone = array(
    'label' => t('Phone'),
    'field_name' => 'sbp_phone',
    'type' => 'text',
    'widget' => array(
      'type' => 'text_textfield',
    ),
  );

  if (empty($phone_exists)) {
    field_create_field($profile_phone);
  }

  $instance_exists = field_info_instance('user', 'sbp_phone', 'user');
  if (empty($instance_exists)) {
    $instance = array(
      'entity_type' => 'user',
      'bundle' => 'user',
    );
    $instance = array_merge($profile_phone, $instance);
    field_create_instance($instance);
  }

  $salutation_exists = field_info_field('sbp_salutation');

  $profile_salutation = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'sbp_salutation',
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
        'Mr' => 'Mr',
        'Mrs' => 'Mrs',
        'Ms' => 'Ms',
      ),
      'allowed_values_function' => '',
    ),
    'translatable' => 0,
    'type' => 'list_text',
  );

  if (empty($salutation_exists)) {
    field_create_field($profile_salutation);
  }

  $sbp_salutation = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => -1,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'sbp_salutation',
    'label' => 'Salutation',
    'required' => 0,
    'settings' => array(
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 4,
    ),
  );

  $sal_instance_exists = field_info_instance('user', 'sbp_salutation', 'user');
  if (empty($sal_instance_exists)) {
    field_create_instance($sbp_salutation);
  }

  _sba_message_action_create_zip_plus_four();
}

/**
 * Create the zip plus four user profile field.
 *
 * Done separately so can be used in update hook.
 */
function _sba_message_action_create_zip_plus_four() {

  $profile_zip_plus_four = array(
    'label' => t('Zip+4'),
    'field_name' => 'sbp_zip_plus_four',
    'type' => 'text',
    'widget' => array(
      'type' => 'text_textfield',
    ),
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'type' => 'hidden',
      ),
      'teaser' => array(
        'label' => 'hidden',
        'type' => 'hidden',
      ),
    ),
  );

  $zip_exists = field_info_field('sbp_zip_plus_four');

  if (empty($zip_exists)) {
    field_create_field($profile_zip_plus_four);
  }

  $instance_exists = field_info_instance('user', 'sbp_zip_plus_four', 'user');
  if (empty($instance_exists)) {
    $instance = array(
      'entity_type' => 'user',
      'bundle' => 'user',
    );
    $instance = array_merge($profile_zip_plus_four, $instance);
    field_create_instance($instance);
  }

  $field_group = field_group_load_field_group('group_profile_admin', 'user', 'user', 'form');
  $table = 'field_group';

  // If the group exists make sure its not disabled.
  if ($field_group) {
    $field_group->children[] = 'sbp_zip_plus_four';
    ctools_export_crud_save($table, $field_group);
  }
}
