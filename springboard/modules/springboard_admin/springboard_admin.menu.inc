<?php

/**
 * @file
 * Definitions for the Springboard Administration menu.
 */

/**
 * Defines the custom menu "Springboard Administration".
 *
 * @return array
 *   A associative array describing a Drupal custom menu, as defined by
 *   menu_save().
 */
function springboard_admin_admin_menu() {
  return array(
    'menu_name' => 'springboard_admin_menu',
    'title' => 'Springboard Administration',
    'description' => 'Menu for the custom Springboard administration interface'
  );
}

/**
 * Defines menu items for the custom menu "Springboard Administration".
 *
 * @return array
 *   A heirarchical array of menu items for the Springboard Administratio menu.
 *
 *   Each item in the array is a associative array representing a menu link
 *   item, with elements as defined by menu_link_save().
 */
function springboard_admin_admin_menu_items() {
  $items = array();
  // Top Level: Sprinboard (dashboard).
  $items['admin/springboard'] = array(
    'link_path' => 'admin/springboard',
    'link_title' => t('Springboard'),
    'menu_name' => 'springboard_admin_menu',
    'expanded' => 1,
    'customized' => 1,
    'weight' => 0,
    '_children' => array(),
  );

  // Springboard > Your Website
  $items['admin/springboard']['_children']['website'] = array(
    'link_path' => variable_get('springboard_drupal_path', 'http://drupal.org'),
    'link_title' => 'Your Website',
    'menu_name' => 'springboard_admin_menu',
    'expanded' => 1,
    'external' => 1,
    'customized' => 1,
    'weight' => 0,
    'options' => array('attributes' => array('target' => '_blank')),
  );

  // Springboard > Salesforce.com
  $items['admin/springboard']['_children']['salesforce'] = array(
    'link_path' => 'http://login.salesforce.com',
    'link_title' => 'Salesforce.com',
    'menu_name' => 'springboard_admin_menu',
    'expanded' => 1,
    'external' => 1,
    'customized' => 1,
    'weight' => 1,
    'options' => array('attributes' => array('target' => '_blank')),
  );

  if(module_exists('fundraiser')) {
    // Top Level: Donation Form.
    $items['admin/springboard/donation-forms/all'] = array(
      'link_path' => 'admin/springboard/donation-forms/all',
      'link_title' => t('Donation Forms'),
      'menu_name' => 'springboard_admin_menu',
      'expanded' => 1,
      'customized' => 1,
      'weight' => 1,
      '_children' => array(),
    );

    // Donation Forms > View All Donation Forms.
    $items['admin/springboard/donation-forms/all']['_children']['admin/springboard/donation-forms/all'] = array(
      'link_path' => 'admin/springboard/donation-forms/all',
      'link_title' => t('View All Donation Forms'),
      'menu_name' => 'springboard_admin_menu',
      'expanded' => 1,
      'customized' => 1,
      'weight' => 0,
    );

    // Create a menu item for each type of webform.
    // In the future, we will use an intermediate page to choose the form type.
    $types = node_type_get_types();
    foreach ($types as $type) {
      if ($type && fundraiser_is_donation_type($type->type)) {
        // Donation Forms > $type->type
        $items['admin/springboard/donation-forms/all']['_children']['node/add/' . preg_replace('/_/', '-', $type->type)] = array(
          'link_path' => 'node/add/' . preg_replace('/_/', '-', $type->type),
          'link_title' => 'Create a ' . $type->name,
          'menu_name' => 'springboard_admin_menu',
          'expanded' => 1,
          'customized' => 1,
          'weight' => 1,
        );
      }
    }

    // Donation Forms > Donation Reports.
    $items['admin/springboard/donation-forms/all']['_children']['admin/reports/salesforce/donations'] = array(
      'link_path' => 'admin/reports/salesforce/donations',
      'link_title' => 'Donation Reports',
      'menu_name' => 'springboard_admin_menu',
      'expanded' => 1,
      'customized' => 1,
      'weight' => 3,
    );
  }

  if(module_exists('webform_user')) {
    // Top Level: Forms.
    $items['admin/springboard/forms/all'] = array(
      'link_path' => 'admin/springboard/forms/all',
      'link_title' => t('Forms'),
      'menu_name' => 'springboard_admin_menu',
      'expanded' => 1,
      'customized' => 1,
      'weight' => 2,
      '_children' => array(),
    );

    // Forms > View All Forms.
    $items['admin/springboard/forms/all']['_children']['admin/springboard/forms/all'] = array(
      'link_path' => 'admin/springboard/forms/all',
      'link_title' => t('View All Forms'),
      'menu_name' => 'springboard_admin_menu',
      'expanded' => 1,
      'customized' => 1,
      'weight' => 0,
    );

    // Create a menu item for each type of webform.
    // In the future, we will use an intermediate page to choose the form type.
    $types = node_type_get_types();
    foreach ($types as $type) {

      if (module_exists('springboard_advocacy')) {
        $action = springboard_advocacy_is_action_type($type->type);
      }
      if (module_exists('springboard_petition')) {
        $petition = springboard_petition_is_petition_type($type->type);
      }
      // Only create the item if the node type uses Webform User but not Fundraiser or Advocacy.
      if ($type && _webform_user_is_webform_user_node_type($type->type)
        && !fundraiser_is_donation_type($type->type)
        && empty($action)
        && empty($petition)
      ) {
        // Forms > $type->type.
        $items['admin/springboard/forms/all']['_children']['node/add/' . preg_replace('/_/', '-', $type->type)] = array(
          'link_path' => 'node/add/' . preg_replace('/_/', '-', $type->type),
          'link_title' => 'Create a ' . $type->name,
          'menu_name' => 'springboard_admin_menu',
          'expanded' => 1,
          'customized' => 1,
          'weight' => 1,
        );
      }
    }
  }

  // Top Level: Asset Library.
  $items['admin/springboard/asset-library'] = array(
    'link_path' => 'admin/springboard/asset-library',
    'link_title' => t('Asset Library'),
    'menu_name' => 'springboard_admin_menu',
    'expanded' => 1,
    'customized' => 1,
    'weight' => 3,
    '_children' => array(),
  );

  if(module_exists('email_wrappers')) {
    // Asset Library > Email Templates.
    $items['admin/springboard/asset-library']['_children']['admin/springboard/asset-library/email_wrapper'] = array(
      'link_path' => 'admin/springboard/asset-library/email_wrapper',
      'link_title' => 'Email Templates',
      'menu_name' => 'springboard_admin_menu',
      'expanded' => 1,
      'customized' => 1,
      'weight' => 0,
    );
  }

  if(module_exists('page_wrappers')) {
    // Asset Library > Page Wrappers.
    $items['admin/springboard/asset-library']['_children']['admin/springboard/asset-library/page_wrapper'] = array(
      'link_path' => 'admin/springboard/asset-library/page_wrapper',
      'link_title' => 'Page Wrappers',
      'menu_name' => 'springboard_admin_menu',
      'expanded' => 1,
      'customized' => 1,
      'weight' => 1,
    );
  }

  // Top Level: Marketing & Analytics.
  $items['admin/springboard/marketing-analytics'] = array(
    'link_path' => 'admin/springboard/marketing-analytics',
    'link_title' => t('Marketing & Analytics'),
    'menu_name' => 'springboard_admin_menu',
    'expanded' => 1,
    'customized' => 1,
    'weight' => 4,
    '_children' => array(),
  );

  if(module_exists('webform_ab')) {
    // Marketing & Analytics > Multivariate Testing.
    $items['admin/springboard/marketing-analytics']['_children']['admin/content/webform_ab'] = array(
      'link_path' => 'admin/content/webform_ab',
      'link_title' => 'Multivariate Testing',
      'menu_name' => 'springboard_admin_menu',
      'expanded' => 1,
      'customized' => 1,
      'weight' => 5,
    );
  }

  // Top Level: Settings.
  $items['admin/springboard/settings'] = array(
    'link_path' => 'admin/springboard/settings',
    'link_title' => t('Options'),
    'menu_name' => 'springboard_admin_menu',
    'expanded' => 1,
    'customized' => 1,
    'weight' => 6,
    '_children' => array(),
  );

  // Settings > My Profile.
  $items['admin/springboard/settings']['_children']['user'] = array(
    'link_path' => 'user',
    'link_title' => 'My Profile',
    'menu_name' => 'springboard_admin_menu',
    'expanded' => 1,
    'customized' => 1,
    'weight' => 0,
  );

  // Settings > Administrators
  $items['admin/springboard/settings']['_children']['admin/springboard/settings/administrators'] = array(
    'link_path' => 'admin/springboard/settings/administrators',
    'link_title' => 'Administrators',
    'menu_name' => 'springboard_admin_menu',
    'expanded' => 1,
    'customized' => 1,
    'weight' => 1,
  );

  // Settings > Configuration.
  $items['admin/springboard/settings']['_children']['admin/springboard/settings/config'] = array(
    'link_path' => 'admin/springboard/settings/config',
    'link_title' => 'Settings',
    'menu_name' => 'springboard_admin_menu',
    'expanded' => 0,
    'customized' => 1,
    'weight' => 2,
    '_children' => array(),
  );

  if(module_exists('salesforce_mapping')) {
    // Settings > Settings > Fieldmaps.
    $items['admin/springboard/settings']['_children']['admin/springboard/settings/config']['_children']['admin/structure/salesforce/mappings'] = array(
      'link_path' => 'admin/structure/salesforce/mappings',
      'link_title' => 'Fieldmaps',
      'menu_name' => 'springboard_admin_menu',
      'expanded' => 0,
      'customized' => 1,
      'weight' => 2,
    );

    // Settings > Settings > Add salesforce mapping.
    $items['admin/springboard/settings']['_children']['admin/springboard/settings/config']['_children']['admin/structure/salesforce/mappings/add'] = array(
      'link_path' => 'admin/structure/salesforce/mappings/add',
      'link_title' => 'Add Salesforce Mapping',
      'menu_name' => 'springboard_admin_menu',
      'expanded' => 0,
      'customized' => 1,
      'weight' => 2,
    );

    // Settings > Settings > Import salesforce mapping.
    $items['admin/springboard/settings']['_children']['admin/springboard/settings/config']['_children']['admin/structure/salesforce/mappings/import'] = array(
      'link_path' => 'admin/structure/salesforce/mappings/import',
      'link_title' => 'Import Salesforce Mapping',
      'menu_name' => 'springboard_admin_menu',
      'expanded' => 0,
      'customized' => 1,
      'weight' => 3,
    );
  }

  if(module_exists('webform_ab')) {
    // Settings > Settings > Multivariate Testing Settings.
    $items['admin/springboard/settings']['_children']['admin/springboard/settings/config']['_children']['admin/config/content/webform_ab'] = array(
      'link_path' => 'admin/config/content/webform_ab',
      'link_title' => 'Multivariate Testing Settings',
      'menu_name' => 'springboard_admin_menu',
      'expanded' => 0,
      'customized' => 1,
      'weight' => 1,
    );

    // Marketing & Analytics > Multivariate Testing.
    $items['admin/springboard/settings']['_children']['admin/springboard/settings/config']['_children']['admin/content/webform_ab'] = array(
      'link_path' => 'admin/content/webform_ab',
      'link_title' => 'Multivariate Testing',
      'menu_name' => 'springboard_admin_menu',
      'expanded' => 1,
      'customized' => 1,
      'weight' => 5,
    );
  }

  //Settings > Logout.
  $items['admin/springboard/settings']['_children']['logout'] = array(
    'link_path' => 'user/logout',
    'link_title' => 'Logout',
    'menu_name' => 'springboard_admin_menu',
    'expanded' => 1,
    'customized' => 1,
    'weight' => 3,
  );
  drupal_alter('springboard_admin_admin_menu_items', $items);
  return $items;
}

/**
 * Helper function, deletes springboard admin menu if it already exists and
 * recreates it.
 *
 * @TODD add option to preserve custom links that may have been manually added
 * to the menu.
 */

function springboard_admin_recreate_menu() {
   $sb_menu = springboard_admin_admin_menu();
   if(menu_load($sb_menu['menu_name'])) {
     menu_delete($sb_menu);
   }
   springboard_admin_create_menu(TRUE);
   drupal_set_message('The Springboard Admin Menu has been rebuilt.');
}

/**
 * Helper function, creates the Springboard Admin Menu.
 */
function springboard_admin_create_menu($rebuild = FALSE) {
  // Define and save the Springboard Administration menu.
  $sb_menu = springboard_admin_admin_menu();
  menu_save($sb_menu);
  // Define and add default menu items to the Springboard Administration menu.
  $sb_menu_items = springboard_admin_admin_menu_items();
  /*
   * Iterate through each item. Save the parent and then the children using the
   * parent's newly assign mlid as the child's plid. If the menu ever advances
   * to more than two levels, we will need to rewrite this to be recursive.
   */
  $mlids = array();
  foreach ($sb_menu_items as $key => $item) {
    springboard_admin_create_menu_item($item, $mlids);
  }
  // Set menu links as customized so they don't get wiped out in the
  // router check.
  $result = db_update('menu_links')
  ->fields(array(
    'customized' => 1,
  ))
  ->condition('mlid', $mlids, 'IN')
  ->execute();
  if(!$rebuild) {
    drupal_set_message('The Springboard Admin menu has been created. If you need to rebuild the menu for any reason, visit the <a href="/admin/springboard/settings/springboard">Springboard Configuration</a> page.');
  }
}

function springboard_admin_create_menu_item($item, &$mlids, $plid = 0, $parent = array()) {
  $children = isset($item['_children']) ? $item['_children'] : array();
  // Set the item' parent ID if applicable
  if ($plid > 0) {
    $item['plid'] = $plid;
  }

  // Set a default module value.
  if (!isset($item['module'])) {
    $item['module'] = 'menu';
  }

  // Save a the item.
  $mlid = menu_link_save($item, array(), array($plid => $parent));
  $mlids[] = $mlid;
  // If save was successful, loop through child items.
  if ($mlid) {
    $mlids[] = $mlid;
    if (!empty($children)) {
      foreach ($children as $key => $child) {
        springboard_admin_create_menu_item($child, $mlids, $mlid, $item);
      }
    }
  }
  else {
    drupal_set_message(t('springboard admin menu item @item and its children were not created due to an error', array('@item' => check_plain($item['title']))), 'warning');
  }
}
