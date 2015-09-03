<?php

/**
 * @file
 * Install helper functions for message action legislative vocabulary.
 */

/**
 * Install legislative issues vocabulary.
 *
 * Presently used by message actions but may be by other modules.
 */
function _sba_message_action_install_vocab_sba_legislative_issues() {
  $already_exists = FALSE;
  foreach (taxonomy_get_vocabularies() as $vocab) {
    if ($vocab->machine_name == 'sba_legislative_issues') {
      $already_exists = TRUE;
      break;
    }
  }
  if (!$already_exists) {
    $t = get_t();
    $status = taxonomy_vocabulary_save((object) array(
      'name' => t("Legislative Issues"),
      'machine_name' => 'sba_legislative_issues',
      'description' => $t("Search terms for selection of matching topics on legislative contact forms."),
    ));
    if ($status == SAVED_NEW) {
      $vocab = taxonomy_vocabulary_machine_name_load('sba_legislative_issues');
      // Populate with Springboard standard terms.
      $weight = 0;
      foreach (_sba_message_action_standard_legislative_issues() as $parent => $children) {
        taxonomy_term_save((object) array(
          'vid' => $vocab->vid,
          'name' => $t($parent),
          'weight' => $weight++,
          'vocabulary_machine_name' => $vocab->machine_name,
        ));
        $parent_terms = taxonomy_term_load_multiple(array(), array('name' => $t($parent), 'vid' => $vocab->vid));
        if (!empty($parent_terms)) {
          $parent_term = reset($parent_terms);
          foreach ($children as $child) {
            taxonomy_term_save((object) array(
              'vid' => $vocab->vid,
              'name' => $t($child),
              'weight' => $weight++,
              'parent' => array($parent_term->tid),
              'vocabulary_machine_name' => $vocab->machine_name,
            ));
          }
        }
      }
    }
  }
  _sba_message_action_install_taxonomy_fields();
}

/**
 * Define legislative issues terms.
 *
 * @return array
 */
function _sba_message_action_standard_legislative_issues() {
  $t = get_t();
  return array(
    "Agriculture and Food" => array("Agriculture", "FDA/USDA", "Food", "Nutrition"),
    "Animal Welfare" => array("Animals", "Animal Rights", "Animal Welfare"),
    "The Arts" => array("Arts", "Humanities", "Entertainment", "Culture"),
    "Banking and Finance" => array("Finance", "Banking", "Financial Sector", "Securities"),
    "Budget and Taxes" => array("Budget", "Appropriations", "Spending", "Ways and Means", "Budget Deficit", "Taxes", "Tax Policy", "Tax Reform"),
    "Civil Rights and Social Issues" => array("Social Issues", "Civil Rights", "Minority Rights", "Human Rights", "Civil Liberty"),
    "Consumer Affairs" => array("Consumer Affairs", "Consumer", "Consumer Protections"),
    "Crime" => array("Crime", "Law Enforcement", "Illegal", "Guns and Crime"),
    "Defense and National Security" => array("Homeland Security", "Military", "Defense", "Armed Forces", "National Security", "War"),
    "Education" => array("Education", "Schools", "K-12", "Social Sciences and History", "Colleges and Universities"),
    "Energy and Environment" => array("Energy", "Natural Resources", "Environment", "Interior/Public Lands", "Climate"),
    "Government Reform" => array("Government Reform", "Campaign Finance", "Ethics", "Elections", "Politics"),
    "Government Services & Affairs" => array("Government Issues", "Government Service", "Operations", "Government Affairs", "Federal Issues", "Process"),
    "Gun Control" => array("Guns", "Gun Control", "Second Amendment", "2nd Amendment", "Weapons"),
    "Health and Health Care" => array("Health", "Health Care", "Health Insurance"),
    "Immigration" => array("Immigration", "Border Security", "Borders"),
    "International Affairs" => array("International Relations", "Foreign Relations", "Foreign Affairs", "Foreign Policy", "International Affairs", "International"),
    "Jobs and the Economy" => array("Labor", "Jobs", "Employment", "Economy", "Workforce"),
    "Judiciary" => array("Judiciary", "Judicial", "Constitutional Issues", "Justice", "Law"),
    "Native Americans" => array("Native Americans", "Indian Affairs", "BIA"),
    "Other" => array("Other", "General", "Miscellaneous", "Not Listed"),
    "Science, Technology and Communications" => array("Technology", "Science", "NASA", "Telecommunications"),
    "Senior Citizens" => array("Senior Citizens", "Pensions", "Retirement", "Aging"),
    "Social Security, Medicare, and Medicaid" => array("Social Security", "Medicare", "Medicaid", "Disability"),
    "Social Services" => array("Welfare", "Social Services", "Welfare Issues", "Welfare Reform", "Housing and Urban Development"),
    "Trade and Commerce" => array("Trade", "Commerce", "Taxes and Trade", "Business", "Economic Development"),
    "Transportation and Infrastructure" => array("Transportation", "Public Works", "Infrastructure"),
    "Veterans" => array("Veterans", "Veteran Affairs", "Tricare", "Armed Services"),
    "Women, Children, and Family" => array("Women's", "Abortion", "Children", "Family", "Reproductive"),
  );
}

function _sba_message_action_install_taxonomy_fields() {
  module_load_include('inc', 'field', 'field.crud');
  module_load_include('inc', 'field', 'field.info');

  // Install Organization Issues
  module_load_include('install', 'springboard_taxonomy');
  if(function_exists('_springboard_taxonomy_field_instance')) {
    foreach (_springboard_taxonomy_field_instance('sba_message_action') as $field_name => $field) {

      // If somehow the base organization field was deleted, recreate it.
      if (!field_info_field($field['field_instance']['field_name'])) {
        $base = _springboard_taxonomy_field_base();
        field_create_field($base[$field_name]['field_config']);
      }

      // Create the instance.
      if (!field_info_instance('node', $field['field_instance']['field_name'], 'sba_message_action')) {
        field_create_instance($field['field_instance']);
      }
    }
  }

  // Install Legislatve issues.
  if (function_exists('_sba_message_action_install_taxonomy_field_definitions')) {
    foreach (_sba_message_action_install_taxonomy_field_definitions() as $field_name => $field) {
      $exists = field_info_field('field_' . $field_name);
      if (empty($exists)) {
        field_create_field($field['field_config']);
      }
      // Before adding the field, check that it doesn't exist on the node type.
      if (!field_info_instance('node', 'field_' . $field_name, 'sba_message_action')) {
        field_create_instance($field['field_instance']);
      }
    }
  }
}

/**
 * @return mixed
 */
function _sba_message_action_install_taxonomy_field_definitions() {
  $t = get_t();

  // Legislative issues.
  $fields['sba_legislative_issues'] = array(
    'field_config' => array(
      'field_name' => 'field_sba_legislative_issues',
      'type' => 'taxonomy_term_reference',
      'translatable' => '0',
      'cardinality' => '-1',
      'foreign keys' => array(
        'tid' => array(
          'columns' => array(
            'tid' => 'tid',
          ),
          'table' => 'taxonomy_term_data',
        ),
      ),
      'indexes' => array(
        'tid' => array(
          0 => 'tid',
        ),
      ),
      'locked' => '1',
      'module' => 'taxonomy',
      'settings' => array(
        'allowed_values' => array(
          0 => array(
            'vocabulary' => 'sba_legislative_issues',
            'parent' => '0',
          ),
        ),
      ),
    ),
    'field_instance' => array(
      'field_name' => 'field_sba_legislative_issues',
      'entity_type' => 'node',
      'bundle' => 'sba_message_action',
      'label' => $t("Legislative Issues"),
      'default_value' => NULL,
      'required' => 0,
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '4',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'options',
        'settings' => array(),
        'type' => 'options_buttons',
        'weight' => 5,
      ),
    ),
  );

  return $fields;
}

/**
 * Delete taxonomy fields.
 */
function _sba_message_action_delete_legislative_vocab() {
  foreach (taxonomy_get_vocabularies() as $vocab) {
    if ($vocab->machine_name == 'sba_legislative_issues') {
      taxonomy_vocabulary_delete($vocab->vid);
    }
  }
}