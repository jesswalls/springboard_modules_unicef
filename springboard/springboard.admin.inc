<?php
/**
 * @file
 * Provides Springboard administrative forms.
 */

 /**
 * Dashboard settings form.
 */
 function springboard_dashboard_settings() {
  $form = array();
   // TODO: add support for pane weights.
  $panes = module_invoke_all('springboard_dashboard_panes');
  drupal_alter('springboard_dashboard_panes', $panes);
  foreach ($panes as $name => $info) {
    $panes[$name] = $info['label'];
  }
  $form['springboard_dashboard_config']['panes'] = array(
    '#type' => 'fieldset',
    '#title' => t('Dashboard Panes'),
  );
  $form['springboard_dashboard_config']['panes']['springboard_enabled_panes'] = array(
    '#description' => t('Enable/disable visible panes on the Springboard Dashboard'),
    '#type' => 'checkboxes',
    '#options' => $panes,
    '#default_value' => variable_get('springboard_enabled_panes', array()),
  );
  $form['#submit'] = array('springboard_dashboard_config_save');

  $form['actions']['cancel'] = array(
    '#type' => 'submit',
    '#value' => t('Return to Dashboard'),
    '#submit' => array('springboard_dashboard_config_cancel'),
    '#description' => t('Cancel changes and return to the dashboard'),
    '#weight' => 10,
  );
  return system_settings_form($form);
 }

/**
 * Admin settings form.
 */
function springboard_admin_settings() {
  $form = array();
  if (variable_get('springboard_needs_config', FALSE)) {
    $form['springboard_config'] = array(
      '#type' => 'fieldset',
      '#title' => t('Configure Springboard'),
      '#description' => t('New to Springboard? Configure the default Springboard installation to get started quickly. ' .
        'Give the system some time to work, it may take a bit of time to configure everything correctly.'),
      '#weight' => -1,
    );
    $form['springboard_config']['settings'] = array(
      '#type' => 'fieldset',
      '#title' => t('Springboard settings'),
    );
    $form['springboard_config']['settings']['order_handling'] = array(
      '#type' => 'select',
      '#options' => array(
//        'ubercart' => t('Ubercart'), // Ubercart default support deprc.
        'commerce' => t('Commerce'),
      ),
      '#title' => t('Select order processing system'),
    );
    $form['springboard_config']['settings']['sf_enable'] = array(
      '#title' => t('Enable Salesforce Integration?'),
      '#type' => 'checkbox',
      '#description' => t('If your organization has a Salesforce org and plans on synching information between Drupal ' .
        'and Salesforce you should enable integration.'),
    );
    $form['springboard_config']['settings']['sf'] = array(
      '#title' => t('Salesforce Integration Settings'),
      '#type' => 'fieldset',
      '#states' => array(
        'visible' => array(
          ':input[name="sf_enable"]' => array('checked' => TRUE),
        ),
      ),
    );
    $form['springboard_config']['settings']['sf']['sf_donation'] = array(
      '#title' => t('Enable Salesforce Donation Integration'),
      '#type' => 'checkbox',
    );
    $form['springboard_config']['settings']['sf']['sf_npsp'] = array(
      '#title' => t('Enable Salesforce Nonprofit Starter Pack Integration'),
      '#type' => 'checkbox',
    );
    $form['springboard_config']['settings']['sf']['sf_help'] = array(
      '#type' => 'item',
      '#markup' => t('You will need to authorize this website after setup to complete the connection to Salesforce.'),
    );
    $form['springboard_config']['settings']['sf']['sf_key'] = array(
      '#title' => t('Salesforce consumer key'),
      '#type' => 'textfield',
    );
    $form['springboard_config']['settings']['sf']['sf_secret'] = array(
      '#title' => t('Salesforce consumer secret'),
      '#type' => 'textfield',
    );
    $form['springboard_config']['configure'] = array(
      '#type' => 'submit',
      '#value' => t('Configure default Springboard'),
      '#description' => t('Click here to use the default settings for a Springboard install.'),
      '#submit' => array('springboard_admin_config'),
    );
    $form['springboard_config']['ignore'] = array(
      '#type' => 'submit',
      '#value' => t('Custom Springboard'),
      '#description' => t('Click here if you want to configure Springboard yourself.'),
      '#submit' => array('springboard_admin_ignore'),
    );
  }
  $form['dashboard'] = array(
    '#type' => 'fieldset',
    '#title' => t('Dashboard Threshold Settings'),
    '#description' => t('Configure display settings for your dashboard.'),
  );
  $form['dashboard']['springboard_conversion_threshold'] = array(
    '#type' => 'textfield',
    '#title' => t('Conversion Percentage Threshold'),
    '#description' => t('Set the minimum acceptable conversion rate percentage. Any forms with lower ' .
      'conversion rates will be flagged on the dashboard.'),
    '#default_value' => variable_get('springboard_conversion_threshold', 0),
  );
  $form['dashboard']['springboard_local_failure_threshold'] = array(
    '#type' => 'textfield',
    '#title' => t('Local Failure Threshold'),
    '#description' => t('Set the maximum acceptable local failure percentage. Any forms with higher ' .
      'local failure rates will be flagged.'),
    '#default_value' => variable_get('springboard_local_failure_threshold', 0),
  );
  $form['dashboard']['springboard_gateway_failure_threshold'] = array(
    '#type' => 'textfield',
    '#title' => t('Gateway Failure Percentage Threshold'),
    '#description' => t('Set the maximum acceptable gateway failure percentage. Any forms with higher ' .
      'gateway failure rates will be flagged.'),
    '#default_value' => variable_get('springboard_gateway_failure_threshold', 0),
  );
  $form['dashboard']['springboard_load_time_threshold'] = array(
    '#type' => 'textfield',
    '#title' => t('Load Time Threshold'),
    '#description' => t('Set the maximum acceptable time (in ms) to render a donation form. Any forms ' .
      'taking longer than this to load will be flagged.'),
    '#default_value' => variable_get('springboard_load_time_threshold', 500),
  );
  $form['#validate'][] = 'springboard_admin_settings_validate';
  return system_settings_form($form);
}

/**
 * Validation handler for the springboard admin settings form.
 */
function springboard_admin_settings_validate(&$form, $form_state) {
  if ($form_state['values']['springboard_conversion_threshold'] && !is_numeric($form_state['values']['springboard_conversion_threshold'])) {
    form_set_error('springboard_conversion_threshold', t('The conversion threshold must be numeric!'));
  }
  if ($form_state['values']['springboard_local_failure_threshold'] && !is_numeric($form_state['values']['springboard_local_failure_threshold'])) {
    form_set_error('springboard_local_failure_threshold', t('The local failure threshold must be numeric!'));
  }
  if ($form_state['values']['springboard_gateway_failure_threshold'] && !is_numeric($form_state['values']['springboard_gateway_failure_threshold'])) {
    form_set_error('springboard_gateway_failure_threshold', t('The gateway failure threshold must be numeric!'));
  }
  if ($form_state['values']['springboard_load_time_threshold'] && !is_numeric($form_state['values']['springboard_load_time_threshold'])) {
    form_set_error('springboard_load_time_threshold', t('The load time threshold must be numeric!'));
  }
}

/**
 * Submit handler for the springboard configuration button.
 */
function springboard_admin_config(&$form, $form_state) {
  if (variable_get('springboard_needs_config', FALSE)) {
    set_time_limit(300);
    variable_del('springboard_needs_config');
    drupal_set_message(t('Please see the !help page for additional help configuring Springboard.',
      array('!help' => l(t('Help'), 'admin/springboard/help'))));
    // This is where what used to be profile configuration in D6 went.
    // We dropped the profile support since it was, honestly, more hinderence than harm.
    // We would rather the Springboard suite be useful for all default profiles.
    springboard_admin_config_modules($form, $form_state);
    // Clear all caches.
    drupal_flush_all_caches();
    set_time_limit(300);
    // Set up module specific configurations.
    springboard_admin_config_springboard($form, $form_state);
    if ($form_state['values']['order_handling'] == 'ubercart') {
      springboard_admin_config_ubercart($form, $form_state);
    }
    else {
      springboard_admin_config_commerce($form, $form_state);
    }
    if ($form_state['values']['sf_enable']) {
      springboard_admin_config_salesforce($form, $form_state);
    }
    // Configure user profiles
    springboard_admin_config_profile($form, $form_state);
    // Configure secure prepopulate synonyms
    springboard_admin_configure_prepopulate_synonyms();
    // Configure a default fundraiser type
    springboard_admin_config_donation_form_type($form, $form_state);
    set_time_limit(300);
    // Create an example form.
    $email_nid = springboard_admin_config_email_wrapper_add($form, $form_state);
    springboard_admin_config_donation_form_add($form, $form_state, $email_nid);
    // Clear all caches one last time.
    drupal_flush_all_caches();
    menu_rebuild();
    drupal_set_message(t('Please be sure to set up the Encypt key path at !link',
      array('!link' => l(t('Encrypt settings'), 'admin/config/system/encrypt'))));
  }
  else {
    drupal_set_message(t('Springboard default configuration has already been set up.'));
  }
}

/**
 * Turn on a standard set of modules.
 */
function springboard_admin_config_modules($form, $form_state) {
  // Springboard custom.
  // Enable does recursion so we don't need to dig deeper.
  $modules = array(
    'field_ui',
    'fundraiser',
    'fundraiser_webform',
    'fundraiser_sustainers',
    'fundraiser_triggers',
    'market_source',
    'webform_user',
    'webform_confirmations',
    'email_wrappers',
    'springboard_views',
    'springboard_version',
    'clone', // Temp comment out, pending add to build script. Node clone support.
    'secure_prepopulate',
  );
  if ($form_state['values']['order_handling'] == 'ubercart') {
    $modules[] = 'fundraiser_ubercart';
    $modules[] = 'uc_credit';
    $modules[] = 'test_gateway';
  }
  else {
    $modules[] = 'fundraiser_commerce';
    $modules[] = 'commerce_product'; // To remove when dependancies in commerce_authnet, commerce_payment resolved.
    $modules[] = 'commerce_product_reference'; // To remove when dependancies in commerce_authnet, commerce_payment resolved.
    $modules[] = 'commerce_ui';
    $modules[] = 'commerce_payment_ui';
    $modules[] = 'commerce_payment_example';
    $modules[] = 'commerce_authnet';
    $modules[] = 'commerce_paypal';
    $modules[] = 'commerce_paypal_wps';
//    $modules[] = 'commerce_cardonfile'; // Temp comment out pending cardonfile install bug fix
  }
  // Optional Salesforce modules.
  if ($form_state['values']['sf_enable']) {
    $modules[] = 'salesforce';
    $modules[] = 'salesforce_log';
    $modules[] = 'salesforce_genmap';
    if ($form_state['values']['sf_donation']) {
      $modules[] = 'salesforce_donation';
    }
    if ($form_state['values']['sf_npsp']) {
      $modules[] = 'salesforce_npsp';
    }
  }
  foreach ($modules as $module) {
    $return = module_enable(array($module), TRUE);
    if ($return) {
      drupal_set_message(t('Module %modules has been enabled.', array('%modules' => $module)));
    }
    else {
      drupal_set_message(t('An error was encountered while installing %modules.', array('%modules' => $module)), 'error');
    }
  }
  $modules = array('comment', 'overlay');
  module_disable($modules, TRUE);
  drupal_set_message(t('Modules %modules have been disabled.', array('%modules' => implode(', ', $modules))));
}

/**
 * Configure Springboard iteself.
 */
function springboard_admin_config_springboard($form, $form_state) {
  $panes = module_invoke_all('springboard_dashboard_panes');
  $default_enabled_panes = array();
  drupal_alter('springboard_dashboard_panes', $panes);
  foreach ($panes as $name => $info) {
    $default_enabled_panes[$name] = $name;
  }
  variable_set('springboard_enabled_panes', $default_enabled_panes);
  drupal_set_message(t('Springboard panels have been configured'));
}

/**
 * Configure Fundraiser Ubercart gateways. On the assumption we are using Ubercart here.
 */
function springboard_admin_config_ubercart($form, $form_state) {
  // Enable the test payment gateway by default.
  variable_set('uc_pg_test_gateway_enabled', 1);
  drupal_set_message(t('Ubercart has been configured'));
}

/**
 * Configure Fundraiser Commerce.
 */
function springboard_admin_config_commerce($form, $form_state) {
  // Add things as we need to.
  drupal_set_message(t('Commerce has been configured'));
}

/**
 * Configure the default Salesforce settings.
 */
function springboard_admin_config_salesforce($form, $form_state) {
  // Market source auto checks campaigns.
  variable_set('market_source_validate_sf_campaigns', TRUE);
  // Set keys and secrets
  if (!empty($form_state['values']['sf_key'])) {
    variable_set('salesforce_consumer_key', $form_state['values']['sf_key']);
  }
  if (!empty($form_state['values']['sf_secret'])) {
    variable_set('salesforce_consumer_secret', $form_state['values']['sf_secret']);
  }
  drupal_set_message(t('Salesforce has been configured'));
  // To do, set oauth up. THIS IS CRITICAL TO DO.
  drupal_set_message(t('You will need to authorize these settings under the Salesforce admin settings.'));
  // Add default contact -> user map.
  $default_map_user_to_contact = '{
  "name" : "user_to_contact",
  "label" : "User to contact",
  "type" : "salesforce_mapping",
  "salesforce_object_type" : "Contact",
  "salesforce_record_type" : "default",
  "drupal_entity_type" : "user",
  "drupal_bundle" : "user",
  "field_mappings" : [
    {
      "drupal_field" : { "fieldmap_type" : "property", "fieldmap_value" : "uid" },
      "salesforce_field" : {
        "length" : 50,
        "name" : "Drupal_User_ID__c",
        "type" : "string",
        "defaultValue" : null,
        "label" : "Drupal User ID",
        "byteLength" : 150,
        "unique" : true,
        "calculated" : false,
        "scale" : 0,
        "precision" : 0,
        "nameField" : false,
        "sortable" : true,
        "filterable" : true,
        "nillable" : true,
        "caseSensitive" : false,
        "inlineHelpText" : null,
        "controllerName" : null,
        "writeRequiresMasterRead" : false,
        "externalId" : true,
        "idLookup" : true,
        "autoNumber" : false,
        "soapType" : "xsd:string",
        "restrictedPicklist" : false,
        "namePointing" : false,
        "custom" : true,
        "defaultedOnCreate" : false,
        "deprecatedAndHidden" : false,
        "htmlFormatted" : false,
        "defaultValueFormula" : null,
        "calculatedFormula" : null,
        "picklistValues" : [],
        "dependentPicklist" : false,
        "referenceTo" : [],
        "relationshipName" : null,
        "relationshipOrder" : null,
        "cascadeDelete" : false,
        "restrictedDelete" : false,
        "digits" : 0,
        "createable" : true,
        "updateable" : true,
        "groupable" : true,
        "permissionable" : true,
        "displayLocationInDecimal" : false
      },
      "key" : false,
      "direction" : "drupal_sf",
      "drupal_sf" : "always",
      "sf_drupal" : "never"
    },
    {
      "drupal_field" : { "fieldmap_type" : "property", "fieldmap_value" : "mail" },
      "salesforce_field" : {
        "length" : 80,
        "name" : "Email",
        "type" : "email",
        "defaultValue" : null,
        "label" : "Email",
        "byteLength" : 240,
        "unique" : false,
        "calculated" : false,
        "scale" : 0,
        "precision" : 0,
        "nameField" : false,
        "sortable" : true,
        "filterable" : true,
        "nillable" : true,
        "caseSensitive" : false,
        "inlineHelpText" : "The Nonprofit Starter Pack fills this field from the other email fields on Contact. You shouldn\u0027t edit this field directly if you have the Preferred Email workflow rules enabled.",
        "controllerName" : null,
        "writeRequiresMasterRead" : false,
        "externalId" : false,
        "idLookup" : true,
        "autoNumber" : false,
        "soapType" : "xsd:string",
        "restrictedPicklist" : false,
        "namePointing" : false,
        "custom" : false,
        "defaultedOnCreate" : false,
        "deprecatedAndHidden" : false,
        "htmlFormatted" : false,
        "defaultValueFormula" : null,
        "calculatedFormula" : null,
        "picklistValues" : [],
        "dependentPicklist" : false,
        "referenceTo" : [],
        "relationshipName" : null,
        "relationshipOrder" : null,
        "cascadeDelete" : false,
        "restrictedDelete" : false,
        "digits" : 0,
        "createable" : true,
        "updateable" : true,
        "groupable" : true,
        "permissionable" : true,
        "displayLocationInDecimal" : false
      },
      "key" : true,
      "direction" : "drupal_sf",
      "drupal_sf" : "always",
      "sf_drupal" : "always"
    },
    {
      "drupal_field" : { "fieldmap_type" : "property", "fieldmap_value" : "mail" },
      "salesforce_field" : {
        "length" : 80,
        "name" : "Email",
        "type" : "email",
        "defaultValue" : null,
        "label" : "Email",
        "byteLength" : 240,
        "unique" : false,
        "calculated" : false,
        "scale" : 0,
        "precision" : 0,
        "nameField" : false,
        "sortable" : true,
        "filterable" : true,
        "nillable" : true,
        "caseSensitive" : false,
        "inlineHelpText" : "The Nonprofit Starter Pack fills this field from the other email fields on Contact. You shouldn\u0027t edit this field directly if you have the Preferred Email workflow rules enabled.",
        "controllerName" : null,
        "writeRequiresMasterRead" : false,
        "externalId" : false,
        "idLookup" : true,
        "autoNumber" : false,
        "soapType" : "xsd:string",
        "restrictedPicklist" : false,
        "namePointing" : false,
        "custom" : false,
        "defaultedOnCreate" : false,
        "deprecatedAndHidden" : false,
        "htmlFormatted" : false,
        "defaultValueFormula" : null,
        "calculatedFormula" : null,
        "picklistValues" : [],
        "dependentPicklist" : false,
        "referenceTo" : [],
        "relationshipName" : null,
        "relationshipOrder" : null,
        "cascadeDelete" : false,
        "restrictedDelete" : false,
        "digits" : 0,
        "createable" : true,
        "updateable" : true,
        "groupable" : true,
        "permissionable" : true,
        "displayLocationInDecimal" : false
      },
      "key" : true,
      "direction" : "sf_drupal",
      "drupal_sf" : "always",
      "sf_drupal" : "always"
    },
    {
      "drupal_field" : { "fieldmap_type" : "property", "fieldmap_value" : "sbp_first_name" },
      "salesforce_field" : {
        "length" : 40,
        "name" : "FirstName",
        "type" : "string",
        "defaultValue" : null,
        "label" : "First Name",
        "byteLength" : 120,
        "unique" : false,
        "calculated" : false,
        "scale" : 0,
        "precision" : 0,
        "nameField" : false,
        "sortable" : true,
        "filterable" : true,
        "nillable" : true,
        "caseSensitive" : false,
        "inlineHelpText" : null,
        "controllerName" : null,
        "writeRequiresMasterRead" : false,
        "externalId" : false,
        "idLookup" : false,
        "autoNumber" : false,
        "soapType" : "xsd:string",
        "restrictedPicklist" : false,
        "namePointing" : false,
        "custom" : false,
        "defaultedOnCreate" : false,
        "deprecatedAndHidden" : false,
        "htmlFormatted" : false,
        "defaultValueFormula" : null,
        "calculatedFormula" : null,
        "picklistValues" : [],
        "dependentPicklist" : false,
        "referenceTo" : [],
        "relationshipName" : null,
        "relationshipOrder" : null,
        "cascadeDelete" : false,
        "restrictedDelete" : false,
        "digits" : 0,
        "createable" : true,
        "updateable" : true,
        "groupable" : true,
        "permissionable" : false,
        "displayLocationInDecimal" : false
      },
      "key" : false,
      "direction" : "drupal_sf",
      "drupal_sf" : "always",
      "sf_drupal" : "blank"
    },
    {
      "drupal_field" : { "fieldmap_type" : "property", "fieldmap_value" : "sbp_first_name" },
      "salesforce_field" : {
        "length" : 40,
        "name" : "FirstName",
        "type" : "string",
        "defaultValue" : null,
        "label" : "First Name",
        "byteLength" : 120,
        "unique" : false,
        "calculated" : false,
        "scale" : 0,
        "precision" : 0,
        "nameField" : false,
        "sortable" : true,
        "filterable" : true,
        "nillable" : true,
        "caseSensitive" : false,
        "inlineHelpText" : null,
        "controllerName" : null,
        "writeRequiresMasterRead" : false,
        "externalId" : false,
        "idLookup" : false,
        "autoNumber" : false,
        "soapType" : "xsd:string",
        "restrictedPicklist" : false,
        "namePointing" : false,
        "custom" : false,
        "defaultedOnCreate" : false,
        "deprecatedAndHidden" : false,
        "htmlFormatted" : false,
        "defaultValueFormula" : null,
        "calculatedFormula" : null,
        "picklistValues" : [],
        "dependentPicklist" : false,
        "referenceTo" : [],
        "relationshipName" : null,
        "relationshipOrder" : null,
        "cascadeDelete" : false,
        "restrictedDelete" : false,
        "digits" : 0,
        "createable" : true,
        "updateable" : true,
        "groupable" : true,
        "permissionable" : false,
        "displayLocationInDecimal" : false
      },
      "key" : false,
      "direction" : "sf_drupal",
      "drupal_sf" : "always",
      "sf_drupal" : "blank"
    },
    {
      "drupal_field" : { "fieldmap_type" : "property", "fieldmap_value" : "sbp_last_name" },
      "salesforce_field" : {
        "length" : 80,
        "name" : "LastName",
        "type" : "string",
        "defaultValue" : null,
        "label" : "Last Name",
        "byteLength" : 240,
        "unique" : false,
        "calculated" : false,
        "scale" : 0,
        "precision" : 0,
        "nameField" : false,
        "sortable" : true,
        "filterable" : true,
        "nillable" : false,
        "caseSensitive" : false,
        "inlineHelpText" : null,
        "controllerName" : null,
        "writeRequiresMasterRead" : false,
        "externalId" : false,
        "idLookup" : false,
        "autoNumber" : false,
        "soapType" : "xsd:string",
        "restrictedPicklist" : false,
        "namePointing" : false,
        "custom" : false,
        "defaultedOnCreate" : false,
        "deprecatedAndHidden" : false,
        "htmlFormatted" : false,
        "defaultValueFormula" : null,
        "calculatedFormula" : null,
        "picklistValues" : [],
        "dependentPicklist" : false,
        "referenceTo" : [],
        "relationshipName" : null,
        "relationshipOrder" : null,
        "cascadeDelete" : false,
        "restrictedDelete" : false,
        "digits" : 0,
        "createable" : true,
        "updateable" : true,
        "groupable" : true,
        "permissionable" : false,
        "displayLocationInDecimal" : false
      },
      "key" : false,
      "direction" : "drupal_sf",
      "drupal_sf" : "always",
      "sf_drupal" : "blank"
    },
    {
      "drupal_field" : { "fieldmap_type" : "property", "fieldmap_value" : "sbp_last_name" },
      "salesforce_field" : {
        "length" : 80,
        "name" : "LastName",
        "type" : "string",
        "defaultValue" : null,
        "label" : "Last Name",
        "byteLength" : 240,
        "unique" : false,
        "calculated" : false,
        "scale" : 0,
        "precision" : 0,
        "nameField" : false,
        "sortable" : true,
        "filterable" : true,
        "nillable" : false,
        "caseSensitive" : false,
        "inlineHelpText" : null,
        "controllerName" : null,
        "writeRequiresMasterRead" : false,
        "externalId" : false,
        "idLookup" : false,
        "autoNumber" : false,
        "soapType" : "xsd:string",
        "restrictedPicklist" : false,
        "namePointing" : false,
        "custom" : false,
        "defaultedOnCreate" : false,
        "deprecatedAndHidden" : false,
        "htmlFormatted" : false,
        "defaultValueFormula" : null,
        "calculatedFormula" : null,
        "picklistValues" : [],
        "dependentPicklist" : false,
        "referenceTo" : [],
        "relationshipName" : null,
        "relationshipOrder" : null,
        "cascadeDelete" : false,
        "restrictedDelete" : false,
        "digits" : 0,
        "createable" : true,
        "updateable" : true,
        "groupable" : true,
        "permissionable" : false,
        "displayLocationInDecimal" : false
      },
      "key" : false,
      "direction" : "sf_drupal",
      "drupal_sf" : "always",
      "sf_drupal" : "blank"
    },
    {
      "drupal_field" : { "fieldmap_type" : "property", "fieldmap_value" : "sbp_address" },
      "salesforce_field" : {
        "length" : 255,
        "name" : "MailingStreet",
        "type" : "textarea",
        "defaultValue" : null,
        "label" : "Mailing Street",
        "byteLength" : 765,
        "unique" : false,
        "calculated" : false,
        "scale" : 0,
        "precision" : 0,
        "nameField" : false,
        "sortable" : true,
        "filterable" : true,
        "nillable" : true,
        "caseSensitive" : false,
        "inlineHelpText" : null,
        "controllerName" : null,
        "writeRequiresMasterRead" : false,
        "externalId" : false,
        "idLookup" : false,
        "autoNumber" : false,
        "soapType" : "xsd:string",
        "restrictedPicklist" : false,
        "namePointing" : false,
        "custom" : false,
        "defaultedOnCreate" : false,
        "deprecatedAndHidden" : false,
        "htmlFormatted" : false,
        "defaultValueFormula" : null,
        "calculatedFormula" : null,
        "picklistValues" : [],
        "dependentPicklist" : false,
        "referenceTo" : [],
        "relationshipName" : null,
        "relationshipOrder" : null,
        "cascadeDelete" : false,
        "restrictedDelete" : false,
        "digits" : 0,
        "createable" : true,
        "updateable" : true,
        "groupable" : true,
        "permissionable" : true,
        "displayLocationInDecimal" : false
      },
      "key" : false,
      "direction" : "drupal_sf",
      "drupal_sf" : "always",
      "sf_drupal" : "always"
    },
    {
      "drupal_field" : { "fieldmap_type" : "property", "fieldmap_value" : "sbp_address" },
      "salesforce_field" : {
        "length" : 255,
        "name" : "MailingStreet",
        "type" : "textarea",
        "defaultValue" : null,
        "label" : "Mailing Street",
        "byteLength" : 765,
        "unique" : false,
        "calculated" : false,
        "scale" : 0,
        "precision" : 0,
        "nameField" : false,
        "sortable" : true,
        "filterable" : true,
        "nillable" : true,
        "caseSensitive" : false,
        "inlineHelpText" : null,
        "controllerName" : null,
        "writeRequiresMasterRead" : false,
        "externalId" : false,
        "idLookup" : false,
        "autoNumber" : false,
        "soapType" : "xsd:string",
        "restrictedPicklist" : false,
        "namePointing" : false,
        "custom" : false,
        "defaultedOnCreate" : false,
        "deprecatedAndHidden" : false,
        "htmlFormatted" : false,
        "defaultValueFormula" : null,
        "calculatedFormula" : null,
        "picklistValues" : [],
        "dependentPicklist" : false,
        "referenceTo" : [],
        "relationshipName" : null,
        "relationshipOrder" : null,
        "cascadeDelete" : false,
        "restrictedDelete" : false,
        "digits" : 0,
        "createable" : true,
        "updateable" : true,
        "groupable" : true,
        "permissionable" : true,
        "displayLocationInDecimal" : false
      },
      "key" : false,
      "direction" : "sf_drupal",
      "drupal_sf" : "always",
      "sf_drupal" : "always"
    },
    {
      "drupal_field" : { "fieldmap_type" : "property", "fieldmap_value" : "sbp_city" },
      "salesforce_field" : {
        "length" : 40,
        "name" : "MailingCity",
        "type" : "string",
        "defaultValue" : null,
        "label" : "Mailing City",
        "byteLength" : 120,
        "unique" : false,
        "calculated" : false,
        "scale" : 0,
        "precision" : 0,
        "nameField" : false,
        "sortable" : true,
        "filterable" : true,
        "nillable" : true,
        "caseSensitive" : false,
        "inlineHelpText" : null,
        "controllerName" : null,
        "writeRequiresMasterRead" : false,
        "externalId" : false,
        "idLookup" : false,
        "autoNumber" : false,
        "soapType" : "xsd:string",
        "restrictedPicklist" : false,
        "namePointing" : false,
        "custom" : false,
        "defaultedOnCreate" : false,
        "deprecatedAndHidden" : false,
        "htmlFormatted" : false,
        "defaultValueFormula" : null,
        "calculatedFormula" : null,
        "picklistValues" : [],
        "dependentPicklist" : false,
        "referenceTo" : [],
        "relationshipName" : null,
        "relationshipOrder" : null,
        "cascadeDelete" : false,
        "restrictedDelete" : false,
        "digits" : 0,
        "createable" : true,
        "updateable" : true,
        "groupable" : true,
        "permissionable" : true,
        "displayLocationInDecimal" : false
      },
      "key" : false,
      "direction" : "drupal_sf",
      "drupal_sf" : "always",
      "sf_drupal" : "always"
    },
    {
      "drupal_field" : { "fieldmap_type" : "property", "fieldmap_value" : "sbp_city" },
      "salesforce_field" : {
        "length" : 40,
        "name" : "MailingCity",
        "type" : "string",
        "defaultValue" : null,
        "label" : "Mailing City",
        "byteLength" : 120,
        "unique" : false,
        "calculated" : false,
        "scale" : 0,
        "precision" : 0,
        "nameField" : false,
        "sortable" : true,
        "filterable" : true,
        "nillable" : true,
        "caseSensitive" : false,
        "inlineHelpText" : null,
        "controllerName" : null,
        "writeRequiresMasterRead" : false,
        "externalId" : false,
        "idLookup" : false,
        "autoNumber" : false,
        "soapType" : "xsd:string",
        "restrictedPicklist" : false,
        "namePointing" : false,
        "custom" : false,
        "defaultedOnCreate" : false,
        "deprecatedAndHidden" : false,
        "htmlFormatted" : false,
        "defaultValueFormula" : null,
        "calculatedFormula" : null,
        "picklistValues" : [],
        "dependentPicklist" : false,
        "referenceTo" : [],
        "relationshipName" : null,
        "relationshipOrder" : null,
        "cascadeDelete" : false,
        "restrictedDelete" : false,
        "digits" : 0,
        "createable" : true,
        "updateable" : true,
        "groupable" : true,
        "permissionable" : true,
        "displayLocationInDecimal" : false
      },
      "key" : false,
      "direction" : "sf_drupal",
      "drupal_sf" : "always",
      "sf_drupal" : "always"
    },
    {
      "drupal_field" : { "fieldmap_type" : "property", "fieldmap_value" : "sbp_state" },
      "salesforce_field" : {
        "length" : 80,
        "name" : "MailingState",
        "type" : "string",
        "defaultValue" : null,
        "label" : "Mailing State\/Province",
        "byteLength" : 240,
        "unique" : false,
        "calculated" : false,
        "scale" : 0,
        "precision" : 0,
        "nameField" : false,
        "sortable" : true,
        "filterable" : true,
        "nillable" : true,
        "caseSensitive" : false,
        "inlineHelpText" : null,
        "controllerName" : null,
        "writeRequiresMasterRead" : false,
        "externalId" : false,
        "idLookup" : false,
        "autoNumber" : false,
        "soapType" : "xsd:string",
        "restrictedPicklist" : false,
        "namePointing" : false,
        "custom" : false,
        "defaultedOnCreate" : false,
        "deprecatedAndHidden" : false,
        "htmlFormatted" : false,
        "defaultValueFormula" : null,
        "calculatedFormula" : null,
        "picklistValues" : [],
        "dependentPicklist" : false,
        "referenceTo" : [],
        "relationshipName" : null,
        "relationshipOrder" : null,
        "cascadeDelete" : false,
        "restrictedDelete" : false,
        "digits" : 0,
        "createable" : true,
        "updateable" : true,
        "groupable" : true,
        "permissionable" : true,
        "displayLocationInDecimal" : false
      },
      "key" : false,
      "direction" : "drupal_sf",
      "drupal_sf" : "always",
      "sf_drupal" : "always"
    },
    {
      "drupal_field" : { "fieldmap_type" : "property", "fieldmap_value" : "sbp_state" },
      "salesforce_field" : {
        "length" : 80,
        "name" : "MailingState",
        "type" : "string",
        "defaultValue" : null,
        "label" : "Mailing State\/Province",
        "byteLength" : 240,
        "unique" : false,
        "calculated" : false,
        "scale" : 0,
        "precision" : 0,
        "nameField" : false,
        "sortable" : true,
        "filterable" : true,
        "nillable" : true,
        "caseSensitive" : false,
        "inlineHelpText" : null,
        "controllerName" : null,
        "writeRequiresMasterRead" : false,
        "externalId" : false,
        "idLookup" : false,
        "autoNumber" : false,
        "soapType" : "xsd:string",
        "restrictedPicklist" : false,
        "namePointing" : false,
        "custom" : false,
        "defaultedOnCreate" : false,
        "deprecatedAndHidden" : false,
        "htmlFormatted" : false,
        "defaultValueFormula" : null,
        "calculatedFormula" : null,
        "picklistValues" : [],
        "dependentPicklist" : false,
        "referenceTo" : [],
        "relationshipName" : null,
        "relationshipOrder" : null,
        "cascadeDelete" : false,
        "restrictedDelete" : false,
        "digits" : 0,
        "createable" : true,
        "updateable" : true,
        "groupable" : true,
        "permissionable" : true,
        "displayLocationInDecimal" : false
      },
      "key" : false,
      "direction" : "sf_drupal",
      "drupal_sf" : "always",
      "sf_drupal" : "always"
    },
    {
      "drupal_field" : { "fieldmap_type" : "property", "fieldmap_value" : "sbp_zip" },
      "salesforce_field" : {
        "length" : 20,
        "name" : "MailingPostalCode",
        "type" : "string",
        "defaultValue" : null,
        "label" : "Mailing Zip\/Postal Code",
        "byteLength" : 60,
        "unique" : false,
        "calculated" : false,
        "scale" : 0,
        "precision" : 0,
        "nameField" : false,
        "sortable" : true,
        "filterable" : true,
        "nillable" : true,
        "caseSensitive" : false,
        "inlineHelpText" : null,
        "controllerName" : null,
        "writeRequiresMasterRead" : false,
        "externalId" : false,
        "idLookup" : false,
        "autoNumber" : false,
        "soapType" : "xsd:string",
        "restrictedPicklist" : false,
        "namePointing" : false,
        "custom" : false,
        "defaultedOnCreate" : false,
        "deprecatedAndHidden" : false,
        "htmlFormatted" : false,
        "defaultValueFormula" : null,
        "calculatedFormula" : null,
        "picklistValues" : [],
        "dependentPicklist" : false,
        "referenceTo" : [],
        "relationshipName" : null,
        "relationshipOrder" : null,
        "cascadeDelete" : false,
        "restrictedDelete" : false,
        "digits" : 0,
        "createable" : true,
        "updateable" : true,
        "groupable" : true,
        "permissionable" : true,
        "displayLocationInDecimal" : false
      },
      "key" : false,
      "direction" : "drupal_sf",
      "drupal_sf" : "always",
      "sf_drupal" : "always"
    },
    {
      "drupal_field" : { "fieldmap_type" : "property", "fieldmap_value" : "sbp_zip" },
      "salesforce_field" : {
        "length" : 20,
        "name" : "MailingPostalCode",
        "type" : "string",
        "defaultValue" : null,
        "label" : "Mailing Zip\/Postal Code",
        "byteLength" : 60,
        "unique" : false,
        "calculated" : false,
        "scale" : 0,
        "precision" : 0,
        "nameField" : false,
        "sortable" : true,
        "filterable" : true,
        "nillable" : true,
        "caseSensitive" : false,
        "inlineHelpText" : null,
        "controllerName" : null,
        "writeRequiresMasterRead" : false,
        "externalId" : false,
        "idLookup" : false,
        "autoNumber" : false,
        "soapType" : "xsd:string",
        "restrictedPicklist" : false,
        "namePointing" : false,
        "custom" : false,
        "defaultedOnCreate" : false,
        "deprecatedAndHidden" : false,
        "htmlFormatted" : false,
        "defaultValueFormula" : null,
        "calculatedFormula" : null,
        "picklistValues" : [],
        "dependentPicklist" : false,
        "referenceTo" : [],
        "relationshipName" : null,
        "relationshipOrder" : null,
        "cascadeDelete" : false,
        "restrictedDelete" : false,
        "digits" : 0,
        "createable" : true,
        "updateable" : true,
        "groupable" : true,
        "permissionable" : true,
        "displayLocationInDecimal" : false
      },
      "key" : false,
      "direction" : "sf_drupal",
      "drupal_sf" : "always",
      "sf_drupal" : "always"
    },
    {
      "drupal_field" : { "fieldmap_type" : "property", "fieldmap_value" : "sbp_country" },
      "salesforce_field" : {
        "length" : 80,
        "name" : "MailingCountry",
        "type" : "string",
        "defaultValue" : null,
        "label" : "Mailing Country",
        "byteLength" : 240,
        "unique" : false,
        "calculated" : false,
        "scale" : 0,
        "precision" : 0,
        "nameField" : false,
        "sortable" : true,
        "filterable" : true,
        "nillable" : true,
        "caseSensitive" : false,
        "inlineHelpText" : null,
        "controllerName" : null,
        "writeRequiresMasterRead" : false,
        "externalId" : false,
        "idLookup" : false,
        "autoNumber" : false,
        "soapType" : "xsd:string",
        "restrictedPicklist" : false,
        "namePointing" : false,
        "custom" : false,
        "defaultedOnCreate" : false,
        "deprecatedAndHidden" : false,
        "htmlFormatted" : false,
        "defaultValueFormula" : null,
        "calculatedFormula" : null,
        "picklistValues" : [],
        "dependentPicklist" : false,
        "referenceTo" : [],
        "relationshipName" : null,
        "relationshipOrder" : null,
        "cascadeDelete" : false,
        "restrictedDelete" : false,
        "digits" : 0,
        "createable" : true,
        "updateable" : true,
        "groupable" : true,
        "permissionable" : true,
        "displayLocationInDecimal" : false
      },
      "key" : false,
      "direction" : "drupal_sf",
      "drupal_sf" : "always",
      "sf_drupal" : "always"
    },
    {
      "drupal_field" : { "fieldmap_type" : "property", "fieldmap_value" : "sbp_country" },
      "salesforce_field" : {
        "length" : 80,
        "name" : "MailingCountry",
        "type" : "string",
        "defaultValue" : null,
        "label" : "Mailing Country",
        "byteLength" : 240,
        "unique" : false,
        "calculated" : false,
        "scale" : 0,
        "precision" : 0,
        "nameField" : false,
        "sortable" : true,
        "filterable" : true,
        "nillable" : true,
        "caseSensitive" : false,
        "inlineHelpText" : null,
        "controllerName" : null,
        "writeRequiresMasterRead" : false,
        "externalId" : false,
        "idLookup" : false,
        "autoNumber" : false,
        "soapType" : "xsd:string",
        "restrictedPicklist" : false,
        "namePointing" : false,
        "custom" : false,
        "defaultedOnCreate" : false,
        "deprecatedAndHidden" : false,
        "htmlFormatted" : false,
        "defaultValueFormula" : null,
        "calculatedFormula" : null,
        "picklistValues" : [],
        "dependentPicklist" : false,
        "referenceTo" : [],
        "relationshipName" : null,
        "relationshipOrder" : null,
        "cascadeDelete" : false,
        "restrictedDelete" : false,
        "digits" : 0,
        "createable" : true,
        "updateable" : true,
        "groupable" : true,
        "permissionable" : true,
        "displayLocationInDecimal" : false
      },
      "key" : false,
      "direction" : "sf_drupal",
      "drupal_sf" : "always",
      "sf_drupal" : "always"
    },
    {
      "drupal_field" : { "fieldmap_type" : "property", "fieldmap_value" : "sbp_ms" },
      "salesforce_field" : {
        "length" : 250,
        "name" : "Market_Source__c",
        "type" : "string",
        "defaultValue" : null,
        "label" : "Market Source",
        "byteLength" : 750,
        "unique" : false,
        "calculated" : false,
        "scale" : 0,
        "precision" : 0,
        "nameField" : false,
        "sortable" : true,
        "filterable" : true,
        "nillable" : true,
        "caseSensitive" : false,
        "inlineHelpText" : null,
        "controllerName" : null,
        "writeRequiresMasterRead" : false,
        "externalId" : false,
        "idLookup" : false,
        "autoNumber" : false,
        "soapType" : "xsd:string",
        "restrictedPicklist" : false,
        "namePointing" : false,
        "custom" : true,
        "defaultedOnCreate" : false,
        "deprecatedAndHidden" : false,
        "htmlFormatted" : false,
        "defaultValueFormula" : null,
        "calculatedFormula" : null,
        "picklistValues" : [],
        "dependentPicklist" : false,
        "referenceTo" : [],
        "relationshipName" : null,
        "relationshipOrder" : null,
        "cascadeDelete" : false,
        "restrictedDelete" : false,
        "digits" : 0,
        "createable" : true,
        "updateable" : true,
        "groupable" : true,
        "permissionable" : true,
        "displayLocationInDecimal" : false
      },
      "key" : false,
      "direction" : "drupal_sf",
      "drupal_sf" : "blank",
      "sf_drupal" : "never"
    },
    {
      "drupal_field" : { "fieldmap_type" : "property", "fieldmap_value" : "sbp_referrer" },
      "salesforce_field" : {
        "length" : 255,
        "name" : "Referrer__c",
        "type" : "string",
        "defaultValue" : null,
        "label" : "Referrer",
        "byteLength" : 765,
        "unique" : false,
        "calculated" : false,
        "scale" : 0,
        "precision" : 0,
        "nameField" : false,
        "sortable" : true,
        "filterable" : true,
        "nillable" : true,
        "caseSensitive" : false,
        "inlineHelpText" : null,
        "controllerName" : null,
        "writeRequiresMasterRead" : false,
        "externalId" : false,
        "idLookup" : false,
        "autoNumber" : false,
        "soapType" : "xsd:string",
        "restrictedPicklist" : false,
        "namePointing" : false,
        "custom" : true,
        "defaultedOnCreate" : false,
        "deprecatedAndHidden" : false,
        "htmlFormatted" : false,
        "defaultValueFormula" : null,
        "calculatedFormula" : null,
        "picklistValues" : [],
        "dependentPicklist" : false,
        "referenceTo" : [],
        "relationshipName" : null,
        "relationshipOrder" : null,
        "cascadeDelete" : false,
        "restrictedDelete" : false,
        "digits" : 0,
        "createable" : true,
        "updateable" : true,
        "groupable" : true,
        "permissionable" : true,
        "displayLocationInDecimal" : false
      },
      "key" : false,
      "direction" : "drupal_sf",
      "drupal_sf" : "blank",
      "sf_drupal" : "never"
    },
    {
      "drupal_field" : {
        "fieldmap_type" : "property",
        "fieldmap_value" : "sbp_initial_referrer"
      },
      "salesforce_field" : {
        "length" : 255,
        "name" : "Initial_Referrer__c",
        "type" : "string",
        "defaultValue" : null,
        "label" : "Initial Referrer",
        "byteLength" : 765,
        "unique" : false,
        "calculated" : false,
        "scale" : 0,
        "precision" : 0,
        "nameField" : false,
        "sortable" : true,
        "filterable" : true,
        "nillable" : true,
        "caseSensitive" : false,
        "inlineHelpText" : null,
        "controllerName" : null,
        "writeRequiresMasterRead" : false,
        "externalId" : false,
        "idLookup" : false,
        "autoNumber" : false,
        "soapType" : "xsd:string",
        "restrictedPicklist" : false,
        "namePointing" : false,
        "custom" : true,
        "defaultedOnCreate" : false,
        "deprecatedAndHidden" : false,
        "htmlFormatted" : false,
        "defaultValueFormula" : null,
        "calculatedFormula" : null,
        "picklistValues" : [],
        "dependentPicklist" : false,
        "referenceTo" : [],
        "relationshipName" : null,
        "relationshipOrder" : null,
        "cascadeDelete" : false,
        "restrictedDelete" : false,
        "digits" : 0,
        "createable" : true,
        "updateable" : true,
        "groupable" : true,
        "permissionable" : true,
        "displayLocationInDecimal" : false
      },
      "key" : false,
      "direction" : "drupal_sf",
      "drupal_sf" : "blank",
      "sf_drupal" : "never"
    },
    {
      "drupal_field" : {
        "fieldmap_type" : "property",
        "fieldmap_value" : "sbp_salesforce_account_id"
      },
      "salesforce_field" : {
        "length" : 18,
        "name" : "AccountId",
        "type" : "reference",
        "defaultValue" : null,
        "label" : "Account ID",
        "byteLength" : 18,
        "unique" : false,
        "calculated" : false,
        "scale" : 0,
        "precision" : 0,
        "nameField" : false,
        "sortable" : true,
        "filterable" : true,
        "nillable" : true,
        "caseSensitive" : false,
        "inlineHelpText" : null,
        "controllerName" : null,
        "writeRequiresMasterRead" : false,
        "externalId" : false,
        "idLookup" : false,
        "autoNumber" : false,
        "soapType" : "tns:ID",
        "restrictedPicklist" : false,
        "namePointing" : false,
        "custom" : false,
        "defaultedOnCreate" : false,
        "deprecatedAndHidden" : false,
        "htmlFormatted" : false,
        "defaultValueFormula" : null,
        "calculatedFormula" : null,
        "picklistValues" : [],
        "dependentPicklist" : false,
        "referenceTo" : [ "Account" ],
        "relationshipName" : "Account",
        "relationshipOrder" : null,
        "cascadeDelete" : false,
        "restrictedDelete" : false,
        "digits" : 0,
        "createable" : true,
        "updateable" : true,
        "groupable" : true,
        "permissionable" : true,
        "displayLocationInDecimal" : false
      },
      "key" : false,
      "direction" : "sf_drupal",
      "drupal_sf" : "never",
      "sf_drupal" : "always"
    }
  ],
  "sync_triggers" : "3",
  "created" : "1365215734",
  "updated" : "1365215808",
  "weight" : "0",
  "push_async" : "0",
  "push_batch" : "0",
  "locked" : "0",
  "rdf_mapping" : []
}';
  // Insert the default map, $default_map_user_to_contact into SF entity mappings.
  $mapping = entity_import('salesforce_mapping', $default_map_user_to_contact);
  entity_save('salesforce_mapping', $mapping);
  drupal_set_message(t('Drupal user entity has been mapped to Salesforce Contact object.'));
}

/**
 * Configure a default set of secure prepopulate synonyms
 * to working with donation forms and webform user forms.
 */
function springboard_admin_configure_prepopulate_synonyms() {
  $synonyms = array(
    'first_name' => 'sbp_first_name',
    'last_name' => 'sbp_last_name',
    'address' => 'sbp_address',
    'address_line_2' => 'sbp_address_line_2',
    'city' => 'sbp_city',
    'state' => 'sbp_state',
    'zip' => 'sbp_zip',
    'country' => 'sbp_country',
  );

  if (module_exists('secure_prepopulate')) {
    foreach ($synonyms as $form_key => $synonym) {
      $settings = array(
        'token_key' => $form_key,
        'synonyms' => $synonym,
      );
      secure_prepopulate_save_synonym($settings);
    }
  }
}

/**
 * Configure a default set of User profile fields.
 */
function springboard_admin_config_profile($form, $form_state) {
  // See http://drupal.org/node/874026 for discussion re: Profile in D7.
  // By preference we use field API.
  // Add profile fields
  $profile_fields = _springboard_default_user_profile($form_state['values']['order_handling']);
  // Create the field on the user for each profile.
  foreach ($profile_fields as $profile_field) {
    $field = array(
      'field_name' => $profile_field['field_name'],
      'cardinality' => 1,
      'type' => $profile_field['type'],
      'settings' => isset($profile_field['settings']) ? $profile_field['settings'] : array(),
    );
    field_create_field($field);
    $instance = array(
      'entity_type' => 'user',
      'bundle' => 'user',
    );
    $instance = array_merge($profile_field, $instance);
    field_create_instance($instance);
  }

  springboard_add_admin_field_group_to_user_entity();

  drupal_set_message(t('Profiles have been configured'));

  // Set the default fundraiser to webform user profile handling settings.
  variable_set('fundraiser_webform_to_user_map', array(
    'mail' => 'mail',
    'sbp_first_name' => 'first_name',
    'sbp_last_name' => 'last_name',
    'sbp_address' => 'address',
    'sbp_address_line_2' => 'address_line_2',
    'sbp_city' => 'city',
    'sbp_state' => 'state',
    'sbp_zip' => 'zip',
    'sbp_country' => 'country',
    )
  );
  // And the same for market source
  variable_set('market_source_to_user_map', array(
    'sbp_cid' => 'cid',
    'sbp_ms' => 'ms',
    'sbp_referrer' => 'referrer',
    'sbp_initial_referrer' => 'initial_referrer',
    'sbp_search_engine' => 'search_engine',
    'sbp_search_string' => 'search_string',
    'sbp_user_agent' => 'user_agent',
    )
  );
  drupal_set_message(t('Profile mapping has been configured'));
}

/**
 * Helper function, provide a list of available user profile fields,
 * including an optional hook to allow other modules to add.
 */
function _springboard_default_user_profile($mode = 'commerce') {
  $profile_fields = array();
  $profile_fields[] = array(
    'label' => t('First name'),
    'field_name' => 'sbp_first_name',
    'type' => 'text',
    'widget' => array(
      'type' => 'text_textfield',
    ),
  );
  $profile_fields[] = array(
    'label' => t('Last name'),
    'field_name' => 'sbp_last_name',
    'type' => 'text',
    'widget' => array(
      'type' => 'text_textfield',
    ),
  );
  $profile_fields[] = array(
    'label' => t('Address'),
    'field_name' => 'sbp_address',
    'type' => 'text',
    'widget' => array(
      'type' => 'text_textfield',
    ),
  );
  $profile_fields[] = array(
    'label' => t('Address Line 2'),
    'field_name' => 'sbp_address_line_2',
    'type' => 'text',
    'widget' => array(
      'type' => 'text_textfield',
    ),
  );
  $profile_fields[] = array(
    'label' => t('City'),
    'field_name' => 'sbp_city',
    'type' => 'text',
    'widget' => array(
      'type' => 'text_textfield',
    ),
  );
  if ($mode == 'ubercart' && module_exists('ubercart')) {
    // Default options loaded from {uc_zones} On the assumption we are using Ubercart here.
    // Load State/Province options from {uc_zones}, UC default is zone codes for US & Canada.
    $countries_set = fundraiser_ubercart_get_countries();
    $zones = '';
    foreach ($countries_set->zones as $zone) {
      $zones[$zone->zone_id] = $zone->zone_name;
    }
    $profile_fields[] = array(
      'label' => t('State/Province'),
      'field_name' => 'sbp_state',
      'type' => 'list_text',
      'widget' => array(
        'type' => 'options_select',
      ),
      'settings' => array('allowed_values' => $zones),
    );
  }
  elseif ($mode == 'commerce' && module_exists('fundraiser_commerce')) {
    // Commerce does not store countries in a database, it relies instead on locale.inc
    $countries_set = fundraiser_commerce_get_countries();
    $zones = '';
    foreach ($countries_set->zones as $zone) {
      $zones[$zone->zone_id] = $zone->zone_name;
    }
    // For Commerce or others for now.
    $profile_fields[] = array(
      'label' => t('State/Province'),
      'field_name' => 'sbp_state',
      'type' => 'list_text',
      'widget' => array(
        'type' => 'options_select',
      ),
      'settings' => array('allowed_values' => $zones),
    );
  }
  else {
    // For Commerce or others for now.
    $profile_fields[] = array(
      'label' => t('State/Province'),
      'field_name' => 'sbp_state',
      'type' => 'text',
      'widget' => array(
        'type' => 'text_textfield',
      ),
    );
  }
  $profile_fields[] = array(
    'label' => t('Postal Code'),
    'field_name' => 'sbp_zip',
    'type' => 'text',
    'widget' => array(
      'type' => 'text_textfield',
    ),
  );
  if ($mode == 'ubercart' && module_exists('ubercart')) {
    // Default options loaded from {uc_zones} On the assumption we are using Ubercart here.
    // Load State/Province options from {uc_zones}, UC default is zone codes for US & Canada.
    $countries_set = fundraiser_ubercart_get_countries();
    $countries = '';
    foreach ($countries_set->countries as $country) {
      $countries[$country->country_id] = $country->country_name;
    }
    $profile_fields[] = array(
      'label' => t('Country'),
      'field_name' => 'sbp_country',
      'type' => 'list_text',
      'widget' => array(
        'type' => 'options_select',
      ),
      'settings' => array('allowed_values' => $countries),
    );
  }
  elseif ($mode == 'commerce' && module_exists('fundraiser_commerce')) {
    // Commerce does not store countries in a database, it relies instead on locale.inc
    $countries_set = fundraiser_commerce_get_countries();
    $countries = '';
    foreach ($countries_set->countries as $country) {
      $countries[$country->country_id] = $country->country_name;
    }
    // For Commerce or others for now.
    $profile_fields[] = array(
      'label' => t('Country'),
      'field_name' => 'sbp_country',
      'type' => 'list_text',
      'widget' => array(
        'type' => 'options_select',
      ),
      'settings' => array('allowed_values' => $countries),
    );
  }
  else {
    $profile_fields[] = array(
      'label' => t('Country'),
      'field_name' => 'sbp_country',
      'type' => 'text',
      'widget' => array(
        'type' => 'text_textfield',
      ),
    );
  }
  $profile_fields[] = array(
    'label' => t('Campaign ID'),
    'field_name' => 'sbp_cid',
    'type' => 'text',
    'widget' => array(
      'type' => 'text_textfield',
    ),
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'type' => 'hidden',
      ),
    ),
  );
  $profile_fields[] = array(
    'label' => t('Market Source'),
    'field_name' => 'sbp_ms',
    'type' => 'text',
    'widget' => array(
      'type' => 'text_textfield',
    ),
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'type' => 'hidden',
      ),
    ),
  );
  $profile_fields[] = array(
    'label' => t('Referrer'),
    'field_name' => 'sbp_referrer',
    'type' => 'text',
    'widget' => array(
      'type' => 'text_textfield',
    ),
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'type' => 'hidden',
      ),
    ),
  );
  $profile_fields[] = array(
    'label' => t('Initial Referrer'),
    'field_name' => 'sbp_initial_referrer',
    'type' => 'text',
    'widget' => array(
      'type' => 'text_textfield',
    ),
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'type' => 'hidden',
      ),
    ),
  );
  $profile_fields[] = array(
    'label' => t('Search Engine'),
    'field_name' => 'sbp_search_engine',
    'type' => 'text',
    'widget' => array(
      'type' => 'text_textfield',
    ),
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'type' => 'hidden',
      ),
    ),
  );
  $profile_fields[] = array(
    'label' => t('Search String'),
    'field_name' => 'sbp_search_string',
    'type' => 'text',
    'widget' => array(
      'type' => 'text_textfield',
    ),
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'type' => 'hidden',
      ),
    ),
  );
  $profile_fields[] = array(
    'label' => t('User Agent'),
    'field_name' => 'sbp_user_agent',
    'type' => 'text',
    'widget' => array(
      'type' => 'text_textfield',
    ),
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'type' => 'hidden',
      ),
    ),
  );
  $profile_fields[] = array(
    'label' => t('Salesforce Account Id'),
    'field_name' => 'sbp_salesforce_account_id',
    'type' => 'text',
    'widget' => array(
      'type' => 'text_textfield',
    ),
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'type' => 'hidden',
      ),
    ),
  );
  $profile_fields[] = array(
    'label' => t('Salesforce Contact Id'),
    'field_name' => 'sbp_salesforce_contact_id',
    'type' => 'text',
    'widget' => array(
      'type' => 'text_textfield',
    ),
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'type' => 'hidden',
      ),
    ),
  );
  drupal_alter('springboard_default_user_profile', $profile_fields, $mode);
  return $profile_fields;
}

/**
 * Create the donation_form type.
 */
function springboard_admin_config_donation_form_type($form, $form_state) {
  $type = node_type_set_defaults();
  $type->name = t('Donation Form');
  $type->type = 'donation_form';
  $type->description = t('Springboard provided donation form type.');
  $type->title_label = t('Title');
  $type->has_title = ($type->title_label != '');
  $type->base = 'node_content';
  $type->custom = TRUE;
  $type->modified = TRUE;
  $type->module = 'springboard';
  // Save or reset persistent variable values.
  $variables = array(
    'node_submitted' => 0,
    'fundraiser' => 1,
    'webform_user' => 1,
    'webform_user_default_fields' => array(
      'webform_user_all_profile_fields' => 'webform_user_all_profile_fields',
    ),
  );
  foreach ($variables as $key => $value) {
    $variable_new = $key . '_' . $type->type;
    if (is_array($value)) {
      $value = array_keys(array_filter($value));
    }
    variable_set($variable_new, $value);
  }
  $status = node_type_save($type);
  node_types_rebuild();
  node_add_body_field($type);
  // Add as a webform.
  $webform_node_types = variable_get('webform_node_types', array('webform'));
  $webform_node_types_primary = variable_get('webform_node_types_primary', array('webform'));
  $webform_node_types = array_merge($webform_node_types, array('donation_form'));
  $webform_node_types_primary = array_merge($webform_node_types_primary, array('donation_form'));
  variable_set('webform_node_types', array_unique($webform_node_types));
  variable_set('webform_node_types_primary', array_unique($webform_node_types_primary));
  // Done.
  drupal_set_message(t('The content type <em>donation_form</em> has been added.'));
  watchdog('springboard_config', 'Added content type donation_form.');
}

/**
 * Create an example Email Wrapper.
 */
function springboard_admin_config_email_wrapper_add($form, $form_state) {
  $node = new stdClass();
  $node->is_new = 1;
  $node->type = 'email_wrapper';
  $node->language = LANGUAGE_NONE;
  $node->uid = 1;
  $node->title = 'Example Email Wrapper';
  $node->status = 0;
  $node->promote = 0;
  $node->email_wrapper_from_name[LANGUAGE_NONE][0] = array(
    'value' => 'Springboard',
    'format' => '',
    'safe_value' => 'Springboard',
  );
  $node->email_wrapper_from_email[LANGUAGE_NONE][0] = array(
    'value' => 'example-from@example.com',
    'format' => '',
    'safe_value' => 'example-from@example.com',
  );
  $node->email_wrapper_reply_email[LANGUAGE_NONE][0] = array(
    'value' => 'example-to@example.com',
    'format' => '',
    'safe_value' => 'example-to@example.com',
  );
  $node->email_wrapper_subject[LANGUAGE_NONE][0] = array(
    'value' => 'Thank you for your generous donation!',
    'format' => '',
    'safe_value' => 'Thank you for your generous donation!',
  );
  $node->email_wrapper_html_template[LANGUAGE_NONE][0] = array(
    'value' => 'Thank you for your generous donation!' . "\n" .
      "\n" .
      '%html_message' . "\n" .
      "\n" .
      '-----' . "\n" .
      'Springboard Example',
    'summary' => '',
    'format' => 'filtered_html',
    'safe_value' => '<p>Thank you for your generous donation!</p>' . "\n" .
      '<p>%html_message</p>' . "\n" .
      '<p>-----<br>' . "\n" .
      'Springboard Example</p>',
  );
  $node->email_wrapper_html_message[LANGUAGE_NONE][0] = array(
    'value' => 'Please visit us again soon.',
    'summary' => '',
    'format' => 'filtered_html',
    'safe_value' => '<p>Please visit us again soon.</p>',
  );
  $node->email_wrapper_text_template[LANGUAGE_NONE][0] = array(
    'value' => 'Thank you for your generous donation!' . "\n" .
      "\n" .
      '%text_message' . "\n" .
      "\n" .
      '-----' . "\n" .
      'Springboard Example',
    'format' => '',
    'safe_value' => 'Thank you for your generous donation!' . "\n" .
      "\n" .
      '%text_message' . "\n" .
      "\n" .
      '-----' . "\n" .
      'Springboard Example',
  );
  $node->email_wrapper_text_message[LANGUAGE_NONE][0] = array(
    'value' => 'Please visit us again soon.',
    'format' => 'filtered_html',
    'safe_value' => '<p>Please visit us again soon.</p>',
  );
  node_save($node);
  // Save extras.
  drupal_set_message(t('An example donation form has been created.'));
  return $node->nid;
}

/**
 * Create an example Fundraiser form.
 */
function springboard_admin_config_donation_form_add($form, $form_state, $email_nid = NULL) {
  // Refresh field information defs. So that what was picked up if anything
  // earlier during module activation, is now configured right. Avoid static cache issues.
  $fields = _fundraiser_field_info(TRUE);
  // Create the node.
  $node = new stdClass();
  $node->is_new = 1;
  $node->type = 'donation_form';
  $node->language = LANGUAGE_NONE;
  $node->uid = 1;
  $node->title = 'Test Donation Form';
  $node->field_fundraiser_internal_name = array($node->language => array(0 => array('value' => 'Test Donation Form')));
  $node->status = 1;
  $node->promote = 1;
  $node->body[LANGUAGE_NONE][0]['value'] = 'Donec placerat. Nullam nibh dolor, blandit sed, fermentum id, ' .
    'imperdiet sit amet, neque. Nam mollis ultrices justo. Sed tempor. Sed vitae tellus. Etiam sem arcu, eleifend ' .
    'sit amet, gravida eget, porta at, wisi. Nam non lacus vitae ipsum viverra pretium. Phasellus massa. Fusce ' .
    'magna sem, gravida in, feugiat ac, molestie eget, wisi. Fusce consectetuer luctus ipsum. Vestibulum nunc. ' .
    'Suspendisse dignissim adipiscing libero. Integer leo. Sed pharetra ligula a dui. Quisque ipsum nibh, ullamcorper ' .
    'eget, pulvinar sed, posuere vitae, nulla. Sed varius nibh ut lacus. Curabitur fringilla. Nunc est ipsum, ' .
    'pretium quis, dapibus sed, varius non, lectus. Proin a quam. Praesent lacinia, eros quis aliquam porttitor, ' .
    'urna lacus volutpat urna, ut fermentum neque mi egestas dolor.';
  $node->body[LANGUAGE_NONE][0]['summary'] = 'Donec placerat. Nullam nibh dolor, blandit sed, fermentum id, imperdiet ' .
    'sit amet, neque. Nam mollis ultrices justo. Sed tempor. Sed vitae tellus. Etiam sem arcu, eleifend sit amet, ' .
    'gravida eget, porta at, wisi. Nam non lacus vitae ipsum viverra pretium. Phasellus massa. Fusce magna sem, gravida ' .
    'in, feugiat ac, molestie eget, wisi.';
  $node->body[LANGUAGE_NONE][0]['format'] = 'filtered_html';
  $node->webform = array(
      'confirmation' => 'Thank you [donation:first_name] [donation:last_name] for your donation of [donation:currency:symbol][donation:amount].' . "\n" .
      "\n" .
      'The email address we have for you is: [donation:mail]' . "\n" .
      "\n" .
      'The address we have on record for you is:' . "\n" .
      '[donation:address] [donation:address_line_2]' . "\n" .
      '[donation:city], [donation:state] [donation:zip]' . "\n" .
      '[donation:country]' . "\n" .
      "\n" .
      'Your card ending in [donation:card_number], expires [donation:card_expiration_month] / [donation:card_expiration_year]',
    'confirmation_format' => 'filtered_html',
    'redirect_url' => '<confirmation>',
    'teaser' => 0,
    'block' => 0,
    'allow_draft' => 0,
    'auto_save' => 0,
    'submit_notice' => 1,
    'submit_text' => t('Donate'),
    'submit_limit' => -1,
    'submit_interval' => -1,
    'total_submit_limit' => -1,
    'total_submit_interval' => -1,
    'status' => 1,
    'record_exists' => '',
    'roles' => array(
      '0' => 1,
      '1' => 2,
    ),
    'emails' => array(),
    'components' => array(),
  );
  if ($email_nid != NULL) {
    $node->webform['emails'][1] = array(
      'email' => 6,
      'template' => 'default',
      'subject' => 'Thank you for your generous donation!',
      'from_name' => 'Springboard',
      'from_address' => 'example-from@example.com',
      'html' => 0,
      'attachments' => 0,
      'excluded_components' => array(),
    );
  }
  $node->gateways = array(
    'credit' => array(
      'status' => 1,
      'method' => 'credit',
      'id' => 'commerce_payment_example|commerce_payment_commerce_payment_example',
    ),
  );
  $node->amount_wrapper = array(
    'donation_amounts' => array(
      '0' => array(
        'amount' => 10,
        'label' => '$10',
        'weight' => 0,
      ),
      '1' => array(
        'amount' => 20,
        'label' => '$20',
        'weight' => 1,
      ),
      '2' => array(
        'amount' => 50,
        'label' => '$50',
        'weight' => 2,
      ),
      '3' => array(
        'amount' => 100,
        'label' => '$100',
        'weight' => 3,
      ),
    ),
    'show_other_amount' => 1,
    'ask_for_quantity' => 1,
    'minimum_donation_amount' => 10,
  );
  $node->recurring_setting = 'user_choice';
  $node->is_webform_user = 1;
  $node->send_new_user_email = 0;
  node_save($node);
  $node = node_load($node->nid);
  // Save confirmation details.
  $confirmation['nid'] = $node->nid;
  $confirmation['confirmation_page_title'] = 'Thank you for your donation!';
  _webform_confirmations_update($confirmation);
  // Save email wrapper details.
  $eid = -1;
  foreach ($node->webform['components'] as $component) {
    if ($component['form_key'] == 'mail') {
      $cid = $component['cid'];
      $node->webform['emails'][1]['email'] = $cid;
    }
  }
  if ($email_nid != NULL) {
    $settings = array(
      'nid' => $node->nid,
      'eid' => 1,
      'tid' => $email_nid,
      'bcc_email' => '',
      'html_message' => 'Thank you [donation:first_name] [donation:last_name] for your donation of [donation:currency:symbol][donation:amount].' . "\n" .
      "\n" .
      'The email address we have for you is: [donation:mail]' . "\n" .
      "\n" .
      'Your card ending in [donation:card_number], expires [donation:card_expiration_month] / [donation:card_expiration_year]',
      'html_message_format' => 'filtered_html',
      'text_message' => 'Thank you [donation:first_name] [donation:last_name] for your donation of [donation:currency:symbol][donation:amount].' . "\n" .
      "\n" .
      'The email address we have for you is: [donation:mail]' . "\n" .
      "\n" .
      'Your card ending in [donation:card_number], expires [donation:card_expiration_month] / [donation:card_expiration_year]',
      'extra' => serialize(array('send_on_donation_success' => 1, 'send_on_donation_decline' => 0, 'send_on_submission' => 0)),
    );
  }
  // One last save.
  node_save($node);
  email_wrappers_save_settings($node->nid, 1, $settings);
  // Make sure the donation maps are moved over to be ready when/if SF is authenticated.
  if ($form_state['values']['sf_donation']) {
    // Add default map for donation.
    $map = salesforce_genmap_load_map(-1, 'salesforce_donation');
    if (!empty($map)) {
      // Copy the map to the node.
      unset($map->mid);
      $map->nid = $node->nid;
      salesforce_genmap_save_map($map, 'salesforce_donation');
    }
    // Add default map for sustainers.
    $map = salesforce_genmap_load_map(-1, 'fundraiser_sustainers');
    if (!empty($map)) {
      // Copy the map to the node.
      unset($map->mid);
      $map->nid = $node->nid;
      salesforce_genmap_save_map($map, 'fundraiser_sustainers');
    }
  }
  drupal_set_message(t('An example donation form has been created.'));
}

/**
 * Submit handler for the springboard configuration button.
 */
function springboard_admin_ignore($form, $form_state) {
  variable_del('springboard_needs_config');
  drupal_set_message(t('Please see the !help page for additional help configuring Springboard.',
    array('!help' => l(t('Help'), 'admin/springboard/help'))));
}

/**
 * Submit handler for the Springboard Dashboard config
 */

 function springboard_dashboard_config_save($form, &$form_state) {
   $form_state['redirect'] = 'admin/springboard';
 }

/**
 * Submit handler for the Springboard Dashbord config cancel button
 */
function springboard_dashboard_config_cancel($form, &$form_state) {
  $form_state['redirect'] = 'admin/springboard';
}

/**
 * Creates an admin field_group for the user entity.
 *
 * Adds some standard springboard fields under the group so they won't be shown
 * to users who don't have the 'administer users' permission.
 *
 * @return bool|int
 *   FALSE, SAVED_NEW, or SAVED_UPDATED.
 */
function springboard_add_admin_field_group_to_user_entity() {
  module_load_include('module', 'ctools');
  ctools_include('export');

  // Search for an existing group.
  $existing = field_group_load_field_group('group_profile_admin', 'user', 'user', 'form');
  $table = 'field_group';

  // If the group exists make sure its not disabled
  if ($existing) {
    $field_group = $existing;
    if ($field_group->disabled == TRUE) {
      ctools_export_crud_enable($table, $field_group->identifier);
      unset($field_group->disabled);
    }
  }
  // Create a new group
  else {
    $field_group = new stdClass();
    $field_group->identifier = 'group_profile_admin|user|user|form';
    $field_group->group_name = 'group_profile_admin';
    $field_group->entity_type = 'user';
    $field_group->bundle = 'user';
    $field_group->mode = 'form';
    $field_group->parent_name = '';

    $field_group->disabled = FALSE;
    $field_group->label = 'Admin';
    $field_group->weight = '40';
    $field_group->children = array(
      'sbp_cid',
      'sbp_ms',
      'sbp_referrer',
      'sbp_initial_referrer',
      'sbp_search_engine',
      'sbp_search_string',
      'sbp_user_agent',
      'sbp_salesforce_account_id',
      'sbp_salesforce_contact_id',
    );
    $field_group->formate_type = 'fieldset';
    $field_group->format_settings = array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-profile-admin field-group-fieldset',
        'required_fields' => 1,
      ),
    );

    $field_group = ctools_export_crud_save($table, $field_group);
  }

  return $field_group;
}
