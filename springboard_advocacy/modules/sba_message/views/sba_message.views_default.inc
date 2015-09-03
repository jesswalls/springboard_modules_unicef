<?php

/**
 * @file
 * Provides default view configurations.
 */


/**
 * Implements hook_views_default_views().
 */
function sba_message_views_default_views() {
  $views = array();

  /************** message targets search block *********/
  $view = new view();
  $view->name = 'targets';
  $view->description = 'Search block for message add page';
  $view->tag = 'Advocacy';
  $view->base_table = 'advocacy';
  $view->human_name = 'SBA Message Targets';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Targets';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view targets';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Search';
  $handler->display->display_options['pager']['type'] = 'springboard_advocacy_views_plugin_pager';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'id' => 'id',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'id' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* No results behavior: Global: Unfiltered text */
  $handler->display->display_options['empty']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['empty']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['empty'] = TRUE;
  $handler->display->display_options['empty']['area_text_custom']['content'] = 'No targets matched your search. Please try again.';
  /* Field: Advocacy: Salutation */
  $handler->display->display_options['fields']['salutation']['id'] = 'salutation';
  $handler->display->display_options['fields']['salutation']['table'] = 'advocacy';
  $handler->display->display_options['fields']['salutation']['field'] = 'salutation';
  /* Field: Advocacy: First Name */
  $handler->display->display_options['fields']['first_name']['id'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['table'] = 'advocacy';
  $handler->display->display_options['fields']['first_name']['field'] = 'first_name';
  /* Field: Advocacy: Last Name */
  $handler->display->display_options['fields']['last_name']['id'] = 'last_name';
  $handler->display->display_options['fields']['last_name']['table'] = 'advocacy';
  $handler->display->display_options['fields']['last_name']['field'] = 'last_name';
  /* Field: Advocacy: Email */
  $handler->display->display_options['fields']['email']['id'] = 'email';
  $handler->display->display_options['fields']['email']['table'] = 'advocacy';
  $handler->display->display_options['fields']['email']['field'] = 'email';
  /* Field: Advocacy: Politcal Party */
  $handler->display->display_options['fields']['party']['id'] = 'party';
  $handler->display->display_options['fields']['party']['table'] = 'advocacy';
  $handler->display->display_options['fields']['party']['field'] = 'party';
  /* Field: Advocacy: Role */
  $handler->display->display_options['fields']['role']['id'] = 'role';
  $handler->display->display_options['fields']['role']['table'] = 'advocacy';
  $handler->display->display_options['fields']['role']['field'] = 'role';
  /* Field: Advocacy: State */
  $handler->display->display_options['fields']['state']['id'] = 'state';
  $handler->display->display_options['fields']['state']['table'] = 'advocacy';
  $handler->display->display_options['fields']['state']['field'] = 'state';
  /* Filter criterion: Advocacy: Search By Type */
  $handler->display->display_options['filters']['search_class_name']['id'] = 'search_class_name';
  $handler->display->display_options['filters']['search_class_name']['table'] = 'advocacy';
  $handler->display->display_options['filters']['search_class_name']['field'] = 'search_class_name';
  $handler->display->display_options['filters']['search_class_name']['value'] = array(
    'Target' => 'Target',
  );
  $handler->display->display_options['filters']['search_class_name']['expose']['operator_id'] = 'search_class_name_op';
  $handler->display->display_options['filters']['search_class_name']['expose']['label'] = 'Search By Type';
  $handler->display->display_options['filters']['search_class_name']['expose']['operator'] = 'search_class_name_op';
  $handler->display->display_options['filters']['search_class_name']['expose']['identifier'] = 'search_class_name';
  $handler->display->display_options['filters']['search_class_name']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['search_class_name']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  /* Filter criterion: Advocacy: Last Name */
  $handler->display->display_options['filters']['last_name']['id'] = 'last_name';
  $handler->display->display_options['filters']['last_name']['table'] = 'advocacy';
  $handler->display->display_options['filters']['last_name']['field'] = 'last_name';
  $handler->display->display_options['filters']['last_name']['exposed'] = TRUE;
  $handler->display->display_options['filters']['last_name']['expose']['operator_id'] = 'last_name_op';
  $handler->display->display_options['filters']['last_name']['expose']['label'] = 'Last Name';
  $handler->display->display_options['filters']['last_name']['expose']['operator'] = 'last_name_op';
  $handler->display->display_options['filters']['last_name']['expose']['identifier'] = 'last_name';
  $handler->display->display_options['filters']['last_name']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  /* Filter criterion: Advocacy: Search By Gender */
  $handler->display->display_options['filters']['search_gender']['id'] = 'search_gender';
  $handler->display->display_options['filters']['search_gender']['table'] = 'advocacy';
  $handler->display->display_options['filters']['search_gender']['field'] = 'search_gender';
  $handler->display->display_options['filters']['search_gender']['value'] = array(
    'M' => 'M',
    'F' => 'F',
  );
  $handler->display->display_options['filters']['search_gender']['exposed'] = TRUE;
  $handler->display->display_options['filters']['search_gender']['expose']['operator_id'] = 'search_gender_op';
  $handler->display->display_options['filters']['search_gender']['expose']['label'] = 'Search By Gender';
  $handler->display->display_options['filters']['search_gender']['expose']['operator'] = 'search_gender_op';
  $handler->display->display_options['filters']['search_gender']['expose']['identifier'] = 'search_gender';
  $handler->display->display_options['filters']['search_gender']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['search_gender']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  $handler->display->display_options['filters']['search_gender']['expose']['reduce'] = TRUE;
  $handler->display->display_options['filters']['search_gender']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['search_gender']['group_info']['label'] = 'Search By Gender';
  $handler->display->display_options['filters']['search_gender']['group_info']['identifier'] = 'search_gender';
  $handler->display->display_options['filters']['search_gender']['group_info']['multiple'] = TRUE;
  $handler->display->display_options['filters']['search_gender']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'Male',
      'operator' => 'in',
      'value' => array(
        'F' => 'F',
        'all' => 0,
        'M' => 0,
      ),
    ),
    2 => array(
      'title' => 'Female',
      'operator' => 'in',
      'value' => array(
        'F' => 'F',
        'all' => 0,
        'M' => 0,
      ),
    ),
  );
  /* Filter criterion: Advocacy: Search By State */
  $handler->display->display_options['filters']['search_state']['id'] = 'search_state';
  $handler->display->display_options['filters']['search_state']['table'] = 'advocacy';
  $handler->display->display_options['filters']['search_state']['field'] = 'search_state';
  $handler->display->display_options['filters']['search_state']['value'] = array(
    'AL' => 'AL',
    'AK' => 'AK',
    'AZ' => 'AZ',
    'AR' => 'AR',
    'CA' => 'CA',
    'CO' => 'CO',
    'CT' => 'CT',
    'DE' => 'DE',
    'DC' => 'DC',
    'FL' => 'FL',
    'GA' => 'GA',
    'HI' => 'HI',
    'ID' => 'ID',
    'IL' => 'IL',
    'IN' => 'IN',
    'IA' => 'IA',
    'KS' => 'KS',
    'KY' => 'KY',
    'LA' => 'LA',
    'ME' => 'ME',
    'MD' => 'MD',
    'MA' => 'MA',
    'MI' => 'MI',
    'MN' => 'MN',
    'MS' => 'MS',
    'MO' => 'MO',
    'MT' => 'MT',
    'NE' => 'NE',
    'NV' => 'NV',
    'NH' => 'NH',
    'NJ' => 'NJ',
    'NM' => 'NM',
    'NY' => 'NY',
    'NC' => 'NC',
    'ND' => 'ND',
    'OH' => 'OH',
    'OK' => 'OK',
    'OR' => 'OR',
    'PA' => 'PA',
    'RI' => 'RI',
    'SC' => 'SC',
    'SD' => 'SD',
    'TN' => 'TN',
    'TX' => 'TX',
    'UT' => 'UT',
    'VT' => 'VT',
    'VA' => 'VA',
    'WA' => 'WA',
    'WV' => 'WV',
    'WI' => 'WI',
    'WY' => 'WY',
  );
  $handler->display->display_options['filters']['search_state']['exposed'] = TRUE;
  $handler->display->display_options['filters']['search_state']['expose']['operator_id'] = 'search_state_op';
  $handler->display->display_options['filters']['search_state']['expose']['label'] = 'Search By State';
  $handler->display->display_options['filters']['search_state']['expose']['operator'] = 'search_state_op';
  $handler->display->display_options['filters']['search_state']['expose']['identifier'] = 'search_state';
  $handler->display->display_options['filters']['search_state']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  $handler->display->display_options['filters']['search_state']['expose']['reduce'] = TRUE;
  /* Filter criterion: Advocacy: Search By Branch */
  $handler->display->display_options['filters']['search_role']['id'] = 'search_role';
  $handler->display->display_options['filters']['search_role']['table'] = 'advocacy';
  $handler->display->display_options['filters']['search_role']['field'] = 'search_role';
  $handler->display->display_options['filters']['search_role']['value'] = array(
    'SR|SS' => 'SR|SS',
    'FR|FS' => 'FR|FS',
  );
  $handler->display->display_options['filters']['search_role']['exposed'] = TRUE;
  $handler->display->display_options['filters']['search_role']['expose']['operator_id'] = 'search_role_op';
  $handler->display->display_options['filters']['search_role']['expose']['label'] = 'Search By Level';
  $handler->display->display_options['filters']['search_role']['expose']['operator'] = 'search_role_op';
  $handler->display->display_options['filters']['search_role']['expose']['identifier'] = 'search_role';
  $handler->display->display_options['filters']['search_role']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['search_role']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  $handler->display->display_options['filters']['search_role']['expose']['reduce'] = TRUE;
  $handler->display->display_options['filters']['search_role']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['search_role']['group_info']['label'] = 'Search By Level';
  $handler->display->display_options['filters']['search_role']['group_info']['identifier'] = 'search_role';
  $handler->display->display_options['filters']['search_role']['group_info']['widget'] = 'radios';
  $handler->display->display_options['filters']['search_role']['group_info']['multiple'] = TRUE;
  $handler->display->display_options['filters']['search_role']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'State',
      'operator' => 'in',
      'value' => array(
        'SR|SS' => 'SR|SS',
        'all' => 0,
        'FR|FS' => 0,
      ),
    ),
    2 => array(
      'title' => 'Federal',
      'operator' => 'in',
      'value' => array(
        'FR|FS' => 'FR|FS',
        'all' => 0,
        'SR|SS' => 0,
      ),
    ),
  );

  /* Display: Message Search Tagets Block */
  $handler = $view->new_display('block', 'Message Search Tagets Block', 'block_3');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Find Targets';
  $handler->display->display_options['display_description'] = 'For use in message add form';
  $handler->display->display_options['defaults']['use_ajax'] = FALSE;
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['defaults']['exposed_form'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Search';
  $handler->display->display_options['exposed_form']['options']['expose_sort_order'] = FALSE;
  $handler->display->display_options['exposed_form']['options']['autosubmit_hide'] = FALSE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'salutation' => 'salutation',
    'first_name' => 'last_name',
    'last_name' => 'last_name',
    'email' => 'email',
    'party' => 'party',
    'role' => 'role',
    'state' => 'state',
    'committee_memberships' => 'committee_memberships',
    'target_actions' => 'target_actions',
  );
  $handler->display->display_options['style_options']['default'] = 'last_name';
  $handler->display->display_options['style_options']['info'] = array(
    'salutation' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'first_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'last_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => ' ',
      'empty_column' => 0,
    ),
    'email' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'party' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'role' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'state' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'committee_memberships' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'target_actions' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Advocacy: Salutation */
  $handler->display->display_options['fields']['salutation']['id'] = 'salutation';
  $handler->display->display_options['fields']['salutation']['table'] = 'advocacy';
  $handler->display->display_options['fields']['salutation']['field'] = 'salutation';
  /* Field: Advocacy: First Name */
  $handler->display->display_options['fields']['first_name']['id'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['table'] = 'advocacy';
  $handler->display->display_options['fields']['first_name']['field'] = 'first_name';
  /* Field: Advocacy: Last Name */
  $handler->display->display_options['fields']['last_name']['id'] = 'last_name';
  $handler->display->display_options['fields']['last_name']['table'] = 'advocacy';
  $handler->display->display_options['fields']['last_name']['field'] = 'last_name';
  $handler->display->display_options['fields']['last_name']['label'] = 'Name';
  /* Field: Advocacy: Email */
  $handler->display->display_options['fields']['email']['id'] = 'email';
  $handler->display->display_options['fields']['email']['table'] = 'advocacy';
  $handler->display->display_options['fields']['email']['field'] = 'email';
  $handler->display->display_options['fields']['email']['exclude'] = TRUE;
  /* Field: Advocacy: Politcal Party */
  $handler->display->display_options['fields']['party']['id'] = 'party';
  $handler->display->display_options['fields']['party']['table'] = 'advocacy';
  $handler->display->display_options['fields']['party']['field'] = 'party';
  $handler->display->display_options['fields']['party']['label'] = 'Party';
  /* Field: Advocacy: Role */
  $handler->display->display_options['fields']['role']['id'] = 'role';
  $handler->display->display_options['fields']['role']['table'] = 'advocacy';
  $handler->display->display_options['fields']['role']['field'] = 'role';
  /* Field: Advocacy: State */
  $handler->display->display_options['fields']['state']['id'] = 'state';
  $handler->display->display_options['fields']['state']['table'] = 'advocacy';
  $handler->display->display_options['fields']['state']['field'] = 'state';
  /* Field: Advocacy: District Code */
  $handler->display->display_options['fields']['district_code']['id'] = 'district_code';
  $handler->display->display_options['fields']['district_code']['table'] = 'advocacy';
  $handler->display->display_options['fields']['district_code']['field'] = 'district_code';
  $handler->display->display_options['fields']['district_code']['label'] = 'District';
  $handler->display->display_options['fields']['district_code']['hide_empty'] = TRUE;
  /* Field: Advocacy: Committee Memberships */
  $handler->display->display_options['fields']['committee_memberships']['id'] = 'committee_memberships';
  $handler->display->display_options['fields']['committee_memberships']['table'] = 'advocacy';
  $handler->display->display_options['fields']['committee_memberships']['field'] = 'committee_memberships';
  $handler->display->display_options['fields']['committee_memberships']['label'] = '';
  $handler->display->display_options['fields']['committee_memberships']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['committee_memberships']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['committee_memberships']['empty_zero'] = TRUE;
  /* Field: Advocacy: Target Actions */
  $handler->display->display_options['fields']['target_actions']['id'] = 'target_actions';
  $handler->display->display_options['fields']['target_actions']['table'] = 'advocacy';
  $handler->display->display_options['fields']['target_actions']['field'] = 'target_actions';
  $handler->display->display_options['fields']['target_actions']['label'] = '';
  $handler->display->display_options['fields']['target_actions']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['target_actions']['which_links'] = array(
    'add' => 'add',
    'view' => 0,
    'edit' => 0,
    'delete' => 0,
  );
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Advocacy: Search Multiple Target Fields by Keywords */
  $handler->display->display_options['filters']['combine']['id'] = 'combine';
  $handler->display->display_options['filters']['combine']['table'] = 'advocacy';
  $handler->display->display_options['filters']['combine']['field'] = 'combine';
  $handler->display->display_options['filters']['combine']['group'] = 1;
  $handler->display->display_options['filters']['combine']['exposed'] = TRUE;
  $handler->display->display_options['filters']['combine']['expose']['operator_id'] = 'combine_op';
  $handler->display->display_options['filters']['combine']['expose']['description'] = 'First name or last name';
  $handler->display->display_options['filters']['combine']['expose']['operator'] = 'combine_op';
  $handler->display->display_options['filters']['combine']['expose']['identifier'] = 'combine';
  $handler->display->display_options['filters']['combine']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  $handler->display->display_options['filters']['combine']['fields'] = array(
    'first_name' => 'first_name',
    'last_name' => 'last_name',
  );
  /* Filter criterion: Advocacy: Search by Committee Name */
  $handler->display->display_options['filters']['search_committee']['id'] = 'search_committee';
  $handler->display->display_options['filters']['search_committee']['table'] = 'advocacy';
  $handler->display->display_options['filters']['search_committee']['field'] = 'search_committee';
  $handler->display->display_options['filters']['search_committee']['group'] = 1;
  $handler->display->display_options['filters']['search_committee']['exposed'] = TRUE;
  $handler->display->display_options['filters']['search_committee']['expose']['operator_id'] = 'search_committee_op';
  $handler->display->display_options['filters']['search_committee']['expose']['description'] = 'Search by Committee Name';
  $handler->display->display_options['filters']['search_committee']['expose']['operator'] = 'search_committee_op';
  $handler->display->display_options['filters']['search_committee']['expose']['identifier'] = 'search_committee';
  $handler->display->display_options['filters']['search_committee']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  /* Filter criterion: Advocacy: Search By State */
  $handler->display->display_options['filters']['search_state']['id'] = 'search_state';
  $handler->display->display_options['filters']['search_state']['table'] = 'advocacy';
  $handler->display->display_options['filters']['search_state']['field'] = 'search_state';
  $handler->display->display_options['filters']['search_state']['value'] = array(
    'AL' => 'AL',
    'AK' => 'AK',
    'AZ' => 'AZ',
    'AR' => 'AR',
    'CA' => 'CA',
    'CO' => 'CO',
    'CT' => 'CT',
    'DE' => 'DE',
    'DC' => 'DC',
    'FL' => 'FL',
    'GA' => 'GA',
    'HI' => 'HI',
    'ID' => 'ID',
    'IL' => 'IL',
    'IN' => 'IN',
    'IA' => 'IA',
    'KS' => 'KS',
    'KY' => 'KY',
    'LA' => 'LA',
    'ME' => 'ME',
    'MD' => 'MD',
    'MA' => 'MA',
    'MI' => 'MI',
    'MN' => 'MN',
    'MS' => 'MS',
    'MO' => 'MO',
    'MT' => 'MT',
    'NE' => 'NE',
    'NV' => 'NV',
    'NH' => 'NH',
    'NJ' => 'NJ',
    'NM' => 'NM',
    'NY' => 'NY',
    'NC' => 'NC',
    'ND' => 'ND',
    'OH' => 'OH',
    'OK' => 'OK',
    'OR' => 'OR',
    'PA' => 'PA',
    'RI' => 'RI',
    'SC' => 'SC',
    'SD' => 'SD',
    'TN' => 'TN',
    'TX' => 'TX',
    'UT' => 'UT',
    'VT' => 'VT',
    'VA' => 'VA',
    'WA' => 'WA',
    'WV' => 'WV',
    'WI' => 'WI',
    'WY' => 'WY',
  );
  $handler->display->display_options['filters']['search_state']['group'] = 1;
  $handler->display->display_options['filters']['search_state']['exposed'] = TRUE;
  $handler->display->display_options['filters']['search_state']['expose']['operator_id'] = 'search_state_op';
  $handler->display->display_options['filters']['search_state']['expose']['label'] = 'State';
  $handler->display->display_options['filters']['search_state']['expose']['operator'] = 'search_state_op';
  $handler->display->display_options['filters']['search_state']['expose']['identifier'] = 'search_state';
  $handler->display->display_options['filters']['search_state']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  $handler->display->display_options['filters']['search_state']['expose']['reduce'] = TRUE;
  /* Filter criterion: Advocacy: Search By District */
  $handler->display->display_options['filters']['search_district_name']['id'] = 'search_district_name';
  $handler->display->display_options['filters']['search_district_name']['table'] = 'advocacy';
  $handler->display->display_options['filters']['search_district_name']['field'] = 'search_district_name';
  $handler->display->display_options['filters']['search_district_name']['group'] = 1;
  $handler->display->display_options['filters']['search_district_name']['exposed'] = TRUE;
  $handler->display->display_options['filters']['search_district_name']['expose']['operator_id'] = 'search_district_name_op';
  $handler->display->display_options['filters']['search_district_name']['expose']['label'] = 'District';
  $handler->display->display_options['filters']['search_district_name']['expose']['operator'] = 'search_district_name_op';
  $handler->display->display_options['filters']['search_district_name']['expose']['identifier'] = 'search_district_name';
  $handler->display->display_options['filters']['search_district_name']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Advocacy: Search By Branch */
  $handler->display->display_options['filters']['search_role_1']['id'] = 'search_role_1';
  $handler->display->display_options['filters']['search_role_1']['table'] = 'advocacy';
  $handler->display->display_options['filters']['search_role_1']['field'] = 'search_role';
  $handler->display->display_options['filters']['search_role_1']['value'] = array(
    'FS' => 'FS',
    'FR' => 'FR',
    'SR' => 'SR',
    'SS' => 'SS',
    'PRES01|PRES03' => 'PRES01|PRES03',
    'GOVNR' => 'GOVNR',
  );
  $handler->display->display_options['filters']['search_role_1']['group'] = 1;
  $handler->display->display_options['filters']['search_role_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['search_role_1']['expose']['operator_id'] = 'search_role_1_op';
  $handler->display->display_options['filters']['search_role_1']['expose']['label'] = 'Branch';
  $handler->display->display_options['filters']['search_role_1']['expose']['operator'] = 'search_role_1_op';
  $handler->display->display_options['filters']['search_role_1']['expose']['identifier'] = 'search_role_1';
  $handler->display->display_options['filters']['search_role_1']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['search_role_1']['expose']['remember_roles'] = array(
    2 => 0,
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  $handler->display->display_options['filters']['search_role_1']['expose']['reduce'] = TRUE;
  $handler->display->display_options['filters']['search_role_1']['group_info']['label'] = 'Branch';
  $handler->display->display_options['filters']['search_role_1']['group_info']['identifier'] = 'search_role_1';
  $handler->display->display_options['filters']['search_role_1']['group_info']['widget'] = 'radios';
  $handler->display->display_options['filters']['search_role_1']['group_info']['multiple'] = TRUE;
  $handler->display->display_options['filters']['search_role_1']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'Federal Executive',
      'operator' => 'in',
      'value' => array(
        'FX|SX' => 'FX|SX',
        'FX' => 'FX',
        'all' => 0,
        'SR|SS' => 0,
        'FR|FS' => 0,
        'FS' => 0,
        'FR' => 0,
        'SR' => 0,
        'SS' => 0,
        'SX' => 0,
      ),
    ),
    2 => array(
      'title' => 'Federal Senate',
      'operator' => 'in',
      'value' => array(
        'FS' => 'FS',
        'all' => 0,
        'SR|SS' => 0,
        'FR|FS' => 0,
        'FR' => 0,
        'SR' => 0,
        'SS' => 0,
        'FX|SX' => 0,
        'FX' => 0,
        'SX' => 0,
      ),
    ),
    3 => array(
      'title' => 'Federal House',
      'operator' => 'in',
      'value' => array(
        'FR' => 'FR',
        'all' => 0,
        'SR|SS' => 0,
        'FR|FS' => 0,
        'FS' => 0,
        'SR' => 0,
        'SS' => 0,
        'FX|SX' => 0,
        'FX' => 0,
        'SX' => 0,
      ),
    ),
    4 => array(
      'title' => 'State Executive',
      'operator' => 'in',
      'value' => array(
        'SX' => 'SX',
        'all' => 0,
        'SR|SS' => 0,
        'FR|FS' => 0,
        'FS' => 0,
        'FR' => 0,
        'SR' => 0,
        'SS' => 0,
        'FX|SX' => 0,
        'FX' => 0,
      ),
    ),
    5 => array(
      'title' => 'State Senate',
      'operator' => 'in',
      'value' => array(
        'SS' => 'SS',
        'all' => 0,
        'SR|SS' => 0,
        'FR|FS' => 0,
        'FS' => 0,
        'FR' => 0,
        'SR' => 0,
        'FX|SX' => 0,
        'FX' => 0,
        'SX' => 0,
      ),
    ),
    6 => array(
      'title' => 'State House',
      'operator' => 'in',
      'value' => array(
        'SR' => 'SR',
        'all' => 0,
        'SR|SS' => 0,
        'FR|FS' => 0,
        'FS' => 0,
        'FR' => 0,
        'SS' => 0,
        'FX|SX' => 0,
        'FX' => 0,
        'SX' => 0,
      ),
    ),
  );
  /* Filter criterion: Advocacy: Search By Party */
  $handler->display->display_options['filters']['search_party']['id'] = 'search_party';
  $handler->display->display_options['filters']['search_party']['table'] = 'advocacy';
  $handler->display->display_options['filters']['search_party']['field'] = 'search_party';
  $handler->display->display_options['filters']['search_party']['value'] = array(
    'D' => 'D',
    'R' => 'R',
    'O' => 'O',
  );
  $handler->display->display_options['filters']['search_party']['group'] = 1;
  $handler->display->display_options['filters']['search_party']['exposed'] = TRUE;
  $handler->display->display_options['filters']['search_party']['expose']['operator_id'] = 'search_party_op';
  $handler->display->display_options['filters']['search_party']['expose']['label'] = 'Party';
  $handler->display->display_options['filters']['search_party']['expose']['operator'] = 'search_party_op';
  $handler->display->display_options['filters']['search_party']['expose']['identifier'] = 'search_party';
  $handler->display->display_options['filters']['search_party']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['search_party']['expose']['remember_roles'] = array(
    2 => 0,
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  $handler->display->display_options['filters']['search_party']['expose']['reduce'] = TRUE;
  $handler->display->display_options['filters']['search_party']['group_info']['label'] = 'Party';
  $handler->display->display_options['filters']['search_party']['group_info']['identifier'] = 'search_party';
  $handler->display->display_options['filters']['search_party']['group_info']['widget'] = 'radios';
  $handler->display->display_options['filters']['search_party']['group_info']['multiple'] = TRUE;
  $handler->display->display_options['filters']['search_party']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'Democrat',
      'operator' => 'in',
      'value' => array(
        'D' => 'D',
        'all' => 0,
        'R' => 0,
        'I' => 0,
        'O' => 0,
      ),
    ),
    2 => array(
      'title' => 'Republican',
      'operator' => 'in',
      'value' => array(
        'R' => 'R',
        'all' => 0,
        'D' => 0,
        'I' => 0,
        'O' => 0,
      ),
    ),
    3 => array(
      'title' => 'Other',
      'operator' => 'in',
      'value' => array(
        'O' => 'O',
        'all' => 0,
        'D' => 0,
        'R' => 0,
        'I' => 0,
      ),
    ),
  );
  /* Filter criterion: Advocacy: Search By Gender */
  $handler->display->display_options['filters']['search_gender']['id'] = 'search_gender';
  $handler->display->display_options['filters']['search_gender']['table'] = 'advocacy';
  $handler->display->display_options['filters']['search_gender']['field'] = 'search_gender';
  $handler->display->display_options['filters']['search_gender']['value'] = array(
    'all' => 'all',
    'M' => 'M',
    'F' => 'F',
    'O' => 'O',
  );
  $handler->display->display_options['filters']['search_gender']['group'] = 1;
  $handler->display->display_options['filters']['search_gender']['exposed'] = TRUE;
  $handler->display->display_options['filters']['search_gender']['expose']['operator_id'] = 'search_gender_op';
  $handler->display->display_options['filters']['search_gender']['expose']['label'] = 'Gender';
  $handler->display->display_options['filters']['search_gender']['expose']['operator'] = 'search_gender_op';
  $handler->display->display_options['filters']['search_gender']['expose']['identifier'] = 'search_gender';
  $handler->display->display_options['filters']['search_gender']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['search_gender']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  $handler->display->display_options['filters']['search_gender']['expose']['reduce'] = TRUE;
  $handler->display->display_options['filters']['search_gender']['group_info']['label'] = 'Gender';
  $handler->display->display_options['filters']['search_gender']['group_info']['identifier'] = 'search_gender';
  $handler->display->display_options['filters']['search_gender']['group_info']['multiple'] = TRUE;
  $handler->display->display_options['filters']['search_gender']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'Male',
      'operator' => 'in',
      'value' => array(
        'M' => 'M',
        'all' => 0,
        'F' => 0,
        'O' => 0,
      ),
    ),
    2 => array(
      'title' => 'Female',
      'operator' => 'in',
      'value' => array(
        'F' => 'F',
        'all' => 0,
        'M' => 0,
        'O' => 0,
      ),
    ),
    3 => array(
      'title' => 'Other',
      'operator' => 'in',
      'value' => array(
        'O' => 'O',
        'all' => 0,
        'M' => 0,
        'F' => 0,
      ),
    ),
  );
  /* Filter criterion: Advocacy: Search By Social Media Presence */
  $handler->display->display_options['filters']['search_social']['id'] = 'search_social';
  $handler->display->display_options['filters']['search_social']['table'] = 'advocacy';
  $handler->display->display_options['filters']['search_social']['field'] = 'search_social';
  $handler->display->display_options['filters']['search_social']['value'] = array(
    'facebook' => 'facebook',
    'twitter' => 'twitter',
  );
  $handler->display->display_options['filters']['search_social']['group'] = 1;
  $handler->display->display_options['filters']['search_social']['exposed'] = TRUE;
  $handler->display->display_options['filters']['search_social']['expose']['operator_id'] = 'search_social_op';
  $handler->display->display_options['filters']['search_social']['expose']['label'] = 'Social Media';
  $handler->display->display_options['filters']['search_social']['expose']['operator'] = 'search_social_op';
  $handler->display->display_options['filters']['search_social']['expose']['identifier'] = 'search_social';
  $handler->display->display_options['filters']['search_social']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['search_social']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  $handler->display->display_options['filters']['search_social']['expose']['reduce'] = TRUE;
  $handler->display->display_options['filters']['search_social']['group_info']['label'] = 'Social Media';
  $handler->display->display_options['filters']['search_social']['group_info']['identifier'] = 'search_social';
  $handler->display->display_options['filters']['search_social']['group_info']['widget'] = 'radios';
  $handler->display->display_options['filters']['search_social']['group_info']['multiple'] = TRUE;
  $handler->display->display_options['filters']['search_social']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'Facebook',
      'operator' => 'in',
      'value' => array(
        'facebook' => 'facebook',
        'all' => 0,
        'twitter' => 0,
      ),
    ),
    2 => array(
      'title' => 'Twitter',
      'operator' => 'in',
      'value' => array(
        'twitter' => 'twitter',
        'all' => 0,
        'facebook' => 0,
      ),
    ),
  );
  /* Filter criterion: Advocacy: Search By Committee Chamber */
  $handler->display->display_options['filters']['search_committee_chamber']['id'] = 'search_committee_chamber';
  $handler->display->display_options['filters']['search_committee_chamber']['table'] = 'advocacy';
  $handler->display->display_options['filters']['search_committee_chamber']['field'] = 'search_committee_chamber';
  $handler->display->display_options['filters']['search_committee_chamber']['group'] = 1;
  $handler->display->display_options['filters']['search_committee_chamber']['exposed'] = TRUE;
  $handler->display->display_options['filters']['search_committee_chamber']['expose']['operator_id'] = 'search_committee_chamber_op';
  $handler->display->display_options['filters']['search_committee_chamber']['expose']['label'] = 'Committee Chamber';
  $handler->display->display_options['filters']['search_committee_chamber']['expose']['operator'] = 'search_committee_chamber_op';
  $handler->display->display_options['filters']['search_committee_chamber']['expose']['identifier'] = 'search_committee_chamber';
  $handler->display->display_options['filters']['search_committee_chamber']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );


  $views[$view->name] = $view;




  /******* Message Landing page *************/

  $view = new view();
  $view->name = 'sba_messages_node';
  $view->description = '';
  $view->tag = 'Advocacy';
  $view->base_table = 'sba_message';
  $view->human_name = 'SBA  Messages';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'SBA  Messages';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'name' => 'name',
    'field_sba_subject' => 'field_sba_subject',
    'edit_sba_message' => 'edit_sba_message',
    'nid' => 'nid',
    'delete_sba_message' => 'edit_sba_message',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_sba_subject' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_sba_message' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '|',
      'empty_column' => 0,
    ),
    'delete_sba_message' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_sba_action_id_target_id']['id'] = 'field_sba_action_id_target_id';
  $handler->display->display_options['relationships']['field_sba_action_id_target_id']['table'] = 'field_data_field_sba_action_id';
  $handler->display->display_options['relationships']['field_sba_action_id_target_id']['field'] = 'field_sba_action_id_target_id';
  /* Field: SBA Message: Subject text */
  $handler->display->display_options['fields']['field_sba_subject']['id'] = 'field_sba_subject';
  $handler->display->display_options['fields']['field_sba_subject']['table'] = 'field_data_field_sba_subject';
  $handler->display->display_options['fields']['field_sba_subject']['field'] = 'field_sba_subject';
  $handler->display->display_options['fields']['field_sba_subject']['delta_offset'] = '0';
  /* Field: SBA Message: Action ID */
  $handler->display->display_options['fields']['field_sba_action_id']['id'] = 'field_sba_action_id';
  $handler->display->display_options['fields']['field_sba_action_id']['table'] = 'field_data_field_sba_action_id';
  $handler->display->display_options['fields']['field_sba_action_id']['field'] = 'field_sba_action_id';
  $handler->display->display_options['fields']['field_sba_action_id']['settings'] = array(
    'link' => 0,
  );
  /* Field: SBA Message: Edit Link */
  $handler->display->display_options['fields']['edit_sba_message']['id'] = 'edit_sba_message';
  $handler->display->display_options['fields']['edit_sba_message']['table'] = 'sba_message';
  $handler->display->display_options['fields']['edit_sba_message']['field'] = 'edit_sba_message';
  /* Contextual filter: SBA Message: Action ID (field_sba_action_id) */
  $handler->display->display_options['arguments']['field_sba_action_id_target_id']['id'] = 'field_sba_action_id_target_id';
  $handler->display->display_options['arguments']['field_sba_action_id_target_id']['table'] = 'field_data_field_sba_action_id';
  $handler->display->display_options['arguments']['field_sba_action_id_target_id']['field'] = 'field_sba_action_id_target_id';
  $handler->display->display_options['arguments']['field_sba_action_id_target_id']['default_action'] = 'access denied';
  $handler->display->display_options['arguments']['field_sba_action_id_target_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_sba_action_id_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_sba_action_id_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_sba_action_id_target_id']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: SBA Message: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'sba_message';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'sba_message_action_message' => 'sba_message_action_message',
  );

  /* Display: Embedded node/%/messages Block */
  $handler = $view->new_display('block', 'Embedded node/%/messages Block', 'block_1');
  $handler->display->display_options['display_description'] = 'Embedded block for edit page';
  $handler->display->display_options['defaults']['use_ajax'] = FALSE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'name' => 'name',
    'field_sba_subject' => 'field_sba_subject',
    'edit_sba_message' => 'edit_sba_message',
    'delete_sba_message' => 'edit_sba_message',
    'draggableviews' => 'draggableviews',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_sba_subject' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_sba_message' => array(
      'align' => '',
      'separator' => ' | ',
      'empty_column' => 0,
    ),
    'delete_sba_message' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'draggableviews' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['empty'] = FALSE;
  /* No results behavior: Global: Unfiltered text */
  $handler->display->display_options['empty']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['empty']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['empty'] = TRUE;
  $handler->display->display_options['empty']['area_text_custom']['content'] = 'No messages have been added yet.';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: SBA Message: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'sba_message';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  /* Field: SBA Message: Subject text */
  $handler->display->display_options['fields']['field_sba_subject']['id'] = 'field_sba_subject';
  $handler->display->display_options['fields']['field_sba_subject']['table'] = 'field_data_field_sba_subject';
  $handler->display->display_options['fields']['field_sba_subject']['field'] = 'field_sba_subject';
  $handler->display->display_options['fields']['field_sba_subject']['delta_offset'] = '0';
  /* Field: SBA Message: Edit Link */
  $handler->display->display_options['fields']['edit_sba_message']['id'] = 'edit_sba_message';
  $handler->display->display_options['fields']['edit_sba_message']['table'] = 'sba_message';
  $handler->display->display_options['fields']['edit_sba_message']['field'] = 'edit_sba_message';
  $handler->display->display_options['fields']['edit_sba_message']['label'] = 'Actions';
  /* Field: SBA Message: Delete Link */
  $handler->display->display_options['fields']['delete_sba_message']['id'] = 'delete_sba_message';
  $handler->display->display_options['fields']['delete_sba_message']['table'] = 'sba_message';
  $handler->display->display_options['fields']['delete_sba_message']['field'] = 'delete_sba_message';
  /* Field: Draggableviews: SBA Message */
  $handler->display->display_options['fields']['draggableviews']['id'] = 'draggableviews';
  $handler->display->display_options['fields']['draggableviews']['table'] = 'sba_message';
  $handler->display->display_options['fields']['draggableviews']['field'] = 'draggableviews';
  $handler->display->display_options['fields']['draggableviews']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['draggableviews']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['draggableviews']['draggableviews']['save_button_label'] = 'Save message order';
  $handler->display->display_options['fields']['draggableviews']['draggableviews']['ajax'] = 0;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Draggableviews: Weight */
  $handler->display->display_options['sorts']['weight']['id'] = 'weight';
  $handler->display->display_options['sorts']['weight']['table'] = 'draggableviews_structure';
  $handler->display->display_options['sorts']['weight']['field'] = 'weight';
  $handler->display->display_options['sorts']['weight']['order'] = 'DESC';
  $handler->display->display_options['sorts']['weight']['draggableviews_setting_view'] = 'self';
  $handler->display->display_options['sorts']['weight']['draggableviews_setting_new_items_bottom_list'] = 0;

  /* Display: Block 2 */
  $handler = $view->new_display('block', 'Block 2', 'block_2');
  $handler->display->display_options['defaults']['use_ajax'] = FALSE;
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'mini';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: SBA Message: Subject text */
  $handler->display->display_options['fields']['field_sba_subject']['id'] = 'field_sba_subject';
  $handler->display->display_options['fields']['field_sba_subject']['table'] = 'field_data_field_sba_subject';
  $handler->display->display_options['fields']['field_sba_subject']['field'] = 'field_sba_subject';
  $handler->display->display_options['fields']['field_sba_subject']['label'] = 'Subject';
  $handler->display->display_options['fields']['field_sba_subject']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_sba_subject']['delta_offset'] = '0';
  /* Field: SBA Message: Placeholder Greeting (for display on the action) */
  $handler->display->display_options['fields']['field_sba_placeholder_greeting']['id'] = 'field_sba_placeholder_greeting';
  $handler->display->display_options['fields']['field_sba_placeholder_greeting']['table'] = 'field_data_field_sba_placeholder_greeting';
  $handler->display->display_options['fields']['field_sba_placeholder_greeting']['field'] = 'field_sba_placeholder_greeting';
  $handler->display->display_options['fields']['field_sba_placeholder_greeting']['label'] = 'Greeting';
  $handler->display->display_options['fields']['field_sba_placeholder_greeting']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_sba_placeholder_greeting']['hide_empty'] = TRUE;
  /* Field: SBA Message: Message/Intro */
  $handler->display->display_options['fields']['field_sba_message']['id'] = 'field_sba_message';
  $handler->display->display_options['fields']['field_sba_message']['table'] = 'field_data_field_sba_message';
  $handler->display->display_options['fields']['field_sba_message']['field'] = 'field_sba_message';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Draggableviews: Weight */
  $handler->display->display_options['sorts']['weight']['id'] = 'weight';
  $handler->display->display_options['sorts']['weight']['table'] = 'draggableviews_structure';
  $handler->display->display_options['sorts']['weight']['field'] = 'weight';
  $handler->display->display_options['sorts']['weight']['draggableviews_setting_view'] = 'sba_messages_node:block_1';
  $handler->display->display_options['sorts']['weight']['draggableviews_setting_new_items_bottom_list'] = 1;


  $views[$view->name] = $view;

  return $views;

}