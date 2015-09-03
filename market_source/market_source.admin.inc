<?php

/**
 * @file
 * Provides an admin interface for the Market Source module.
 */

/**
 * Callback function for the admin settings menu item.
 *
 * @return array
 *   Returns a system_settings_form() formatted Form API array.
 */
function market_source_admin_settings_form($form, &$form_state) {
  $form = array();
  $form['market_source_default_campaign'] = array(
    '#type' => 'textfield',
    '#title' => t('Default Market Source'),
    '#description' => t('Select a default campaign for your donation forms.'),
    '#default_value' => variable_get('market_source_default_campaign', 'default_ms'),
  );
  if (module_exists('salesforce_sync')) {
    $form['market_source_validate_sf_campaigns'] = array(
      '#title' => t('Validate Salesforce Campaigns'),
      '#type' => 'checkbox',
      '#description' => t('When enabled, campaigns will be validated against a list of Salesforce campaigns before being saved.'),
      '#default_value' => variable_get('market_source_validate_sf_campaigns', 0),
    );
  }
  $form['advanced'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced settings'),
    '#tree' => FALSE,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $additional_forms = variable_get('market_source_additional_forms', array());
  if (!is_array($additional_forms)) {
    $additional_forms = array();
  }
  $form['advanced']['market_source_additional_forms'] = array(
    '#title' => t('Additional forms to process'),
    '#type' => 'textarea',
    '#description' => t('Specify any additional forms to process. By default, Market Source will process all webforms and the user ' .
      'registration form. Enter the internal Drupal form ID, one per line.'),
    '#default_value' => implode("\n", $additional_forms),
  );

  // Default global field settings.
  $form['market_source_default_fields'] = array(
    '#type' => 'fieldset',
    '#title' => t('Default Global Fields'),
    '#description' => t('Customize certain aspects of the default webform fields.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#tree' => TRUE,
  );
  $form['market_source_default_fields']['default_fields_wrapper'] = array(
    '#prefix' => '<div id="marketsource-default-fields">',
    '#suffix' => '</div>',
    '#theme' => 'market_source_admin_global_fields_table',
  );

  // Get current settings for these fields.
  if (!isset($form_state['values']['market_source_default_fields']['default_fields_wrapper'])) {
    $form_state['values']['market_source_default_fields']['default_fields_wrapper'] = variable_get('market_source_default_fields', NULL);
  }
  //set up fields to loop through
  $default_fields_list = market_source_list_default_fields();
  // Shortcut.
  $default_fields_values = &$form_state['values']['market_source_default_fields']['default_fields_wrapper'];

  foreach ($default_fields_list as $key => $field_name) {
    if ($key == 'referrer' || $key == 'initial_referrer') {
      // Hidden field to force persistence for referrer fields.
      $persistence_field = array(
        '#type' => 'hidden',
        '#value' => 'direct',
        // theme_market_source_admin_global_fields_table() needs this.
        '#title' => t('Persistent'),
      );
    }
    else {
      // Checkbox for all others.
      $persistence_field = array(
        '#type' => 'radios',
        '#title' => t('Persistence'),
        '#description' => t("Keep the first-seen page's query-string value?"),
        '#default_value' => isset($default_fields_values[$key]['persistence']) ? $default_fields_values[$key]['persistence'] : 'on',
        '#options' => array(
          'on' => t('On (first-seen value)'),
          'off' => t('Off (last-seen value)'),
          'direct' => t('Direct (value from the form page only)'),
        ),
      );
    }

    $form['market_source_default_fields']['default_fields_wrapper'][$key] = array(
      'persistence' => $persistence_field,
      'name' => array(
        '#type' => 'item',
        '#title' => t('Human-readable field name'),
        '#markup' => $field_name,
      ),
      'key' => array(
        '#type' => 'item',
        '#title' => t('Unique field key'),
        '#markup' => $key,
      ),
    );
  }

  // Custom global fields.
  $form['market_source_global_fields'] = array(
    '#type' => 'fieldset',
    '#title' => t('Custom Global Fields'),
    '#description' => t('Any global custom fields created will be added as webform components to your webforms when they are created. ' .
      'Custom fields are not retroactively applied to existing webforms. Leave blank to remove a field.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#tree' => TRUE,
  );
  $form['market_source_global_fields']['custom_fields_wrapper'] = array(
    '#prefix' => '<div id="marketsource-custom-fields">',
    '#suffix' => '</div>',
    '#theme' => 'market_source_admin_global_fields_table',
  );
  $custom_fields = &$form['market_source_global_fields']['custom_fields_wrapper'];
  // If this is the first time visiting the form, this will be empty.
  if (!isset($form_state['values']['market_source_global_fields']['custom_fields_wrapper'])) {
    $form_state['values']['market_source_global_fields']['custom_fields_wrapper'] = variable_get('market_source_custom_fields', array());
  }
  $custom_field_values = &$form_state['values']['market_source_global_fields']['custom_fields_wrapper'];
  // Add a blank row at the end.
  $custom_field_values[] = array();
  foreach ($custom_field_values as $i => $field_value) {
    $custom_fields[$i] = array();
    $custom_fields[$i]['persistence'] = array(
      '#type' => 'radios',
      '#title' => t('Persistence'),
      '#description' => t("Keep the first-seen page's query-string value?"),
      '#default_value' => isset($field_value['persistence']) ? $field_value['persistence'] : 'on',
      '#options' => array(
        'on' => t('On (first-seen value)'),
        'off' => t('Off (last-seen value)'),
        'direct' => t('Direct (value from the form page only)'),
      ),
    );
    $custom_fields[$i]['name'] = array(
      '#type' => 'textfield',
      '#title' => t('Human-readable field name'),
      '#description' => t('This value is displayed in the webform component list.'),
      '#default_value' => isset($field_value['name']) ? $field_value['name'] : '',
      '#size' => 20,
    );
    $custom_fields[$i]['key'] = array(
      '#type' => 'textfield',
      '#title' => t('Unique field key'),
      '#description' => t('This value cannot match any pre-existing field keys.'),
      '#default_value' => isset($field_value['key']) ? $field_value['key'] : '',
      '#size' => 20,
    );
    $custom_fields[$i]['default'] = array(
      '#type' => 'textfield',
      '#title' => t('Default value'),
      '#description' => t('Default value sent to webform.'),
      '#default_value' => isset($field_value['default']) ? $field_value['default'] : '',
      '#size' => 20,
    );
  }
  $form['market_source_global_fields']['add_more'] = array(
    '#type' => 'submit',
    '#value' => t('Add another'),
    '#jax' => array(
      'callback' => 'market_source_admin_add_more_ahah',
      'wrapper' => 'marketsource-custom-fields',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );
  global $cookie_domain;
  $form['market_source_cookie_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Market Source cookie settings'),
    '#description' => t('The cookie domain name for Market Source cookies.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['market_source_cookie_settings']['market_source_cookie_domain'] = array(
    '#title' => t('Cookie domain'),
    '#type' => 'textfield',
    '#description' => t('This is the domain name Market Source cookies will exist under.'),
    '#default_value' => variable_get('market_source_cookie_domain', $cookie_domain),
  );
  if (module_exists('webform_user')) {
    $form['webform_users'] = array(
      '#type' => 'fieldset',
      '#title' => t('Webform User integration'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    $form['webform_users']['help'] = array(
      '#markup' => '<div>' . t('Webform User creates webform components based on User profile fields. Because Market Source also creates ' .
      'components for user fields we need to avoid doubling up on component creation. Therefore a map of Market Source components to user ' .
      'profile fields needs to be created. This will prevent Webform User from creating the same components that Market Source already ' .
      'handles. For each profile field listed here set which (if any) Market Source field will handle creating a component for it instead. ' .
      'Fields left unmapped will be created by Webform User.') . '</div>',
    );
    // If the module exists, we can use it's functions.
    $profile_fields = _webform_user_get_profile_fields();
    $ms_fields = _market_source_get_nonfieldset_keys();
    $current_map = variable_get('market_source_to_user_map', array());
    $form['webform_users']['mapping'] = array(
      '#prefix' => '<div id="webform-user-field-mapping">',
      '#suffix' => '</div>',
      '#tree' => TRUE,
      '#theme' => 'table',
      '#header' => array(t('Profile field'), t('Matching component will be created by this Market Source field')),
      '#rows' => array(),
    );
    $options = array('0' => t('--Not handled by Market Source--'));
    foreach ($ms_fields as $field_key => $ms_field) {
      $options[$field_key] = $ms_field['#title'];
    }
    // Now we just need to note which of these fields map to which fundraiser fields.
    foreach ($profile_fields as $profile_field) {
      $name = $profile_field['name'];
      // Mail is a special case, and should be doubled up on always.
      // It is required by both modules, and field name has been coordinated to match.
      $form['webform_users']['mapping'][$name] = array(
        '#id' => 'field-' . $name,
        '#type' => 'select',
        '#options' => $options,
        '#default_value' => isset($current_map[$name]) ? $current_map[$name] : '',
      );
      $form['webform_users']['mapping']['#rows'][] = array(
        array('data' => $profile_field['title']),
        array('data' => &$form['webform_users']['mapping'][$name]), // Pointer is important.
      );
    }
    $form['#submit'][] = 'market_source_to_webform_user_map_submit';
  }
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save settings'),
  );
  $form['#submit'][] = 'market_source_admin_settings_form_submit';
  return $form;
}

/**
 * AHAH callback for the Add More button for custom fields.
 */
function market_source_admin_add_more_ahah($form, $form_state) {
  $form['market_source_global_fields']['custom_fields_wrapper']['#collapsed'] = FALSE;
  return $form['market_source_global_fields']['custom_fields_wrapper'];
}

/**
 * Validates marketsource admin form.
 */
function market_source_admin_settings_form_validate($form, &$form_state) {
  $values = &$form_state['values'];
  // we don't want any bogus field keys or names.
  foreach ($values['market_source_global_fields']['custom_fields_wrapper'] as $i => $field) {
    if (empty($field['name']) XOR empty($field['key'])) {
      $error_key = empty($field['name']) ? 'name' : 'key';
      form_set_error('market_source_global_fields][custom_fields_wrapper][' . $i . '][' . $error_key,
        t('Both the field name and the field key must be provided.'));
    }
    if (!empty($field['name']) && !preg_match('/^[a-zA-Z0-9_ ]+$/', $field['name'])) {
      form_set_error('market_source_global_fields][custom_fields_wrapper][' . $i . '][name',
        t('The field name may only contain alphanumeric characters, whitespace and underscores.'));
    }
    if (!empty($field['key']) && !preg_match('/^[a-zA-Z0-9_]+$/', $field['key'])) {
      form_set_error('market_source_global_fields][custom_fields_wrapper][' . $i . '][key',
        t('The field key may only contain alphanumeric characters and underscores.'));
    }
    if (!empty($field['default']) && !preg_match('|^[a-zA-Z0-9_+\-:\\\/\s%\[\]]+$|', $field['default'])) {
      form_set_error('market_source_global_fields][custom_fields_wrapper][' . $i . '][default',
        t('The default value may only contain alphanumeric characters, whitespace, underscores, slashes, square brackets, colon and the percent sign.'));
    }
  }
  if (!(count(explode('.', $values['market_source_cookie_domain'])) > 1 && !is_numeric(str_replace('.', '', $values['market_source_cookie_domain'])))) {
    form_set_error('market_source_cookie_domain', t('Your cookie settings will not work. Either you do not have enough of a domain path to be used ' .
      'or you have used an IP address as the domain.'));
  }
}

/**
 * Handle admin form submission.
 */
function market_source_admin_settings_form_submit($form, &$form_state) {
  $values = &$form_state['values'];
  // Set the default campaign value.
  variable_set('market_source_default_campaign', $values['market_source_default_campaign']);
  // Set whether to validate campaigns.
  if (isset($values['market_source_validate_sf_campaigns'])) {
    variable_set('market_source_validate_sf_campaigns', $values['market_source_validate_sf_campaigns']);
  }
  // Save the additional forms.
  $additional_forms = explode("\n", $values['market_source_additional_forms']);
  foreach ($additional_forms as $i => &$val) {
    $val = trim($val);
  }
  variable_set('market_source_additional_forms', array_filter($additional_forms));
  // Save default field settings.
  $default_fields = array();
  if (!empty($values['market_source_default_fields']['default_fields_wrapper'])) {
    foreach ($values['market_source_default_fields']['default_fields_wrapper'] as $key => $default_values) {
      $default_fields[$key] = array(
        'persistence' => $default_values['persistence'],
      );
    }
  }
  variable_set('market_source_default_fields', $default_fields);
  // Save all the custom fields.
  $custom_fields = array();
  if (!empty($values['market_source_global_fields']['custom_fields_wrapper'])) {
    foreach ($values['market_source_global_fields']['custom_fields_wrapper'] as $i => $field) {
      if (!empty($field['key']) && !empty($field['name'])) {
        $custom_fields[] = array(
          'persistence' => $field['persistence'],
          'key' => $field['key'],
          'name' => $field['name'],
          'default' => $field['default'],
        );
      }
    }
  }
  variable_set('market_source_custom_fields', $custom_fields);
  variable_set('market_source_cookie_domain', '');
  $market_source_cookie_domain = $form_state['values']['market_source_cookie_domain'];
  // Per RFC 2109, cookie domains must contain at least one dot other than the
  // first. For hosts such as 'localhost' or IP Addresses we don't set a cookie domain.
  if (count(explode('.', $market_source_cookie_domain)) > 1 && !is_numeric(str_replace('.', '', $market_source_cookie_domain))) {
    variable_set('market_source_cookie_domain', $market_source_cookie_domain);
  }
  elseif (!empty($market_source_cookie_domain)) {
    drupal_set_message(t('Your cookie settings will not work. Either you do not have enough of a domain path to be used ' .
      'or you have used an IP address as the domain. The full site domain will be used.'), 'error');
  }
  // Empty can be left alone, empty is ok. The cookie will fall back to the full domain.
  drupal_set_message(t('Market Source settings saved.'));

  // Empty the cache of campaigns
  cache_clear_all('market_source_campaigns', 'cache');
}

/**
 * Submit handler for mapping fundraiser fields to webform object objects.
 */
function market_source_to_webform_user_map_submit($form, &$form_state) {
  variable_set('market_source_to_user_map', $form_state['values']['mapping']);
}

/**
 * Theme custom fields as a table.
 */
function theme_market_source_admin_global_fields_table($vars) {
  $element = $vars['element'];
  $header = array();
  $rows = array();
  foreach (element_children($element) as $i) {
    $row = array();
    foreach (element_children($element[$i]) as $f) {
      $this_element = &$element[$i][$f];
      if (isset($this_element['#title'])) {
        if (!isset($header[$f])) {
          $header[$f] = $this_element['#title'];
        }
        unset($this_element['#title']);
        $row[] = drupal_render($this_element);
      }
    }
    $rows[] = array(
      'data' => $row,
    );
  }
  return theme('table', array('header' => $header, 'rows' => $rows));
}

/**
 * Helper function, given the array from field_info - get the listed fields for NON fieldset fields, flattened.
 * WARNING: Recursion is here to walk the field info array to gather form keys.
 */
function _market_source_get_nonfieldset_keys($field_info = NULL, $fields = array()) {
  if ($field_info == NULL) {
    $field_info = market_source_field_info();
  }
  $children = element_children($field_info);
  foreach ($children as $child) {
    // If this child is a defined field, but not a fieldset, add it.
    if (isset($field_info[$child]['#title']) && $field_info[$child]['#type'] != 'fieldset') {
      $fields[$child] = $field_info[$child];
    }
    if (is_array($field_info[$child]) && !empty($field_info[$child])) {
      $fields = _market_source_get_nonfieldset_keys($field_info[$child], $fields);
    }
  }
  return $fields;
}

function market_source_list_default_fields() {
  $default_fields_list = array(
    'market_source' => t('Market Source'),
    'campaign' => t('Campaign ID'),
    'referrer' => t('Referrer'),
    'initial_referrer' => t('Initial Referrer'),
    'search_engine' => t('Search Engine'),
    'search_string' => t('Search String'),
    'user_agent' => t('User Agent'),
  );
  return $default_fields_list;
}
