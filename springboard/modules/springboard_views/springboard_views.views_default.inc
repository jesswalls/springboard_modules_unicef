<?php
/**
 * @file
 * Provides default view configurations.
 */

/**
 * Implements hook_views_default_views().
 */
function springboard_views_views_default_views() {
  /**
   * View sbv_forms
   */
  $view = new view();
  $view->name = 'sbv_forms';
  $view->description = 'Springboard form summaries';
  $view->tag = 'springboard_views';
  $view->base_table = 'node';
  $view->human_name = 'sbv_forms';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Recent Forms';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['link_display'] = 'page_2';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access springboard dashboard';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['pager']['type'] = 'mini';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'field_webform_user_internal_name' => 'field_webform_user_internal_name',
    'field_fundraiser_internal_name' => 'field_webform_user_internal_name',
    'title' => 'title',
    'nid' => 'nid',
    'status' => 'status',
    'created' => 'created',
    'path' => 'path',
    'webform_submission_count_node' => 'webform_submission_count_node',
    'clone_node' => 'view_node',
    'edit_node' => 'view_node',
    'view_node' => 'view_node',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'field_webform_user_internal_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_fundraiser_internal_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nid' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'path' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'webform_submission_count_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'clone_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'view_node' => array(
      'align' => '',
      'separator' => ' ',
      'empty_column' => 0,
    ),
  );
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Form Name';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Published */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'node';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'Status';
  $handler->display->display_options['fields']['status']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['status']['type'] = 'published-notpublished';
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = 'Form ID';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Internal Name */
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['id'] = 'field_fundraiser_internal_name';
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['table'] = 'field_data_field_fundraiser_internal_name';
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['field'] = 'field_fundraiser_internal_name';
  /* Field: Content: Path */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'node';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['exclude'] = TRUE;
  /* Field: Webform: Webform submission count */
  $handler->display->display_options['fields']['webform_submission_count_node']['id'] = 'webform_submission_count_node';
  $handler->display->display_options['fields']['webform_submission_count_node']['table'] = 'node';
  $handler->display->display_options['fields']['webform_submission_count_node']['field'] = 'webform_submission_count_node';
  $handler->display->display_options['fields']['webform_submission_count_node']['label'] = 'Submissions';
  $handler->display->display_options['fields']['webform_submission_count_node']['element_label_colon'] = FALSE;
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['label'] = 'Action';
  $handler->display->display_options['fields']['view_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_node']['text'] = 'view';
  /* Field: Webform: Webform edit link */
  $handler->display->display_options['fields']['webform_edit']['id'] = 'webform_edit';
  $handler->display->display_options['fields']['webform_edit']['table'] = 'node';
  $handler->display->display_options['fields']['webform_edit']['field'] = 'webform_edit';
  $handler->display->display_options['fields']['webform_edit']['label'] = '';
  $handler->display->display_options['fields']['webform_edit']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['webform_edit']['text'] = 'edit';
  /* Field: Content: Updated date */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'node';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['label'] = 'Last updated date';
  $handler->display->display_options['fields']['changed']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['changed']['date_format'] = 'short';
  /* Field: Content: Clone link */
  $handler->display->display_options['fields']['clone_node']['id'] = 'clone_node';
  $handler->display->display_options['fields']['clone_node']['table'] = 'node';
  $handler->display->display_options['fields']['clone_node']['field'] = 'clone_node';
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type_1']['id'] = 'type_1';
  $handler->display->display_options['filters']['type_1']['table'] = 'node';
  $handler->display->display_options['filters']['type_1']['field'] = 'type';
  $handler->display->display_options['filters']['type_1']['value'] = array(
    'donation_form' => 'donation_form',
  );
  $handler->display->display_options['filters']['type_1']['group'] = 1;
  $handler->display->display_options['filters']['type_1']['expose']['operator_id'] = 'type_1_op';
  $handler->display->display_options['filters']['type_1']['expose']['label'] = 'Type';
  $handler->display->display_options['filters']['type_1']['expose']['use_operator'] = TRUE;
  $handler->display->display_options['filters']['type_1']['expose']['operator'] = 'type_1_op';
  $handler->display->display_options['filters']['type_1']['expose']['identifier'] = 'type_1';
  $handler->display->display_options['filters']['type_1']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['type_1']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['type_1']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    8 => 0,
  );
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['exposed'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['status']['expose']['label'] = 'Published';
  $handler->display->display_options['filters']['status']['expose']['operator'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['identifier'] = 'status';
  $handler->display->display_options['filters']['status']['expose']['required'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['group'] = 1;
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Title';
  $handler->display->display_options['filters']['title']['expose']['use_operator'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    8 => 0,
  );

  /* Display: Springboard Recent Forms by Type */
  $handler = $view->new_display('block', 'Springboard Recent Forms by Type', 'block_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Recent Forms by Type';
  $handler->display->display_options['defaults']['use_ajax'] = FALSE;
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '35';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'field_webform_user_internal_name' => 'field_webform_user_internal_name',
    'title' => 'title',
    'nid' => 'nid',
    'status' => 'status',
    'created' => 'created',
    'path' => 'path',
    'webform_submission_count_node' => 'webform_submission_count_node',
    'clone_node' => 'clone_node',
    'edit_node' => 'clone_node',
    'view_node' => 'clone_node',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'field_webform_user_internal_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nid' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'path' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'webform_submission_count_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'clone_node' => array(
      'align' => '',
      'separator' => ' | ',
      'empty_column' => 0,
    ),
    'edit_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'view_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Internal Name */
  $handler->display->display_options['fields']['field_webform_user_internal_name']['id'] = 'field_webform_user_internal_name';
  $handler->display->display_options['fields']['field_webform_user_internal_name']['table'] = 'field_data_field_webform_user_internal_name';
  $handler->display->display_options['fields']['field_webform_user_internal_name']['field'] = 'field_webform_user_internal_name';
  $handler->display->display_options['fields']['field_webform_user_internal_name']['alter']['max_length'] = '30';
  $handler->display->display_options['fields']['field_webform_user_internal_name']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['field_webform_user_internal_name']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Form Name';
  $handler->display->display_options['fields']['title']['alter']['max_length'] = '30';
  $handler->display->display_options['fields']['title']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = 'Form ID';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Published */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'node';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'Status';
  $handler->display->display_options['fields']['status']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['status']['type'] = 'published-notpublished';
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Date Created';
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'n/j/o';
  /* Field: Content: Path */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'node';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['exclude'] = TRUE;
  /* Field: Webform: Webform submission count */
  $handler->display->display_options['fields']['webform_submission_count_node']['id'] = 'webform_submission_count_node';
  $handler->display->display_options['fields']['webform_submission_count_node']['table'] = 'node';
  $handler->display->display_options['fields']['webform_submission_count_node']['field'] = 'webform_submission_count_node';
  $handler->display->display_options['fields']['webform_submission_count_node']['label'] = 'Submissions';
  $handler->display->display_options['fields']['webform_submission_count_node']['element_label_colon'] = FALSE;
  /* Field: Content: Clone link */
  $handler->display->display_options['fields']['clone_node']['id'] = 'clone_node';
  $handler->display->display_options['fields']['clone_node']['table'] = 'node';
  $handler->display->display_options['fields']['clone_node']['field'] = 'clone_node';
  $handler->display->display_options['fields']['clone_node']['label'] = 'Action';
  $handler->display->display_options['fields']['clone_node']['element_class'] = 'table-actions';
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Edit';
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['element_class'] = 'table-actions';
  $handler->display->display_options['fields']['view_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_node']['text'] = 'view';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Type */
  $handler->display->display_options['arguments']['type']['id'] = 'type';
  $handler->display->display_options['arguments']['type']['table'] = 'node';
  $handler->display->display_options['arguments']['type']['field'] = 'type';
  $handler->display->display_options['arguments']['type']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['type']['title'] = 'Recent %1s';
  $handler->display->display_options['arguments']['type']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['type']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['type']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['type']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['type']['limit'] = '0';
  $handler->display->display_options['arguments']['type']['break_phrase'] = TRUE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  $handler->display->display_options['block_description'] = 'Springboard Recent Forms by Type';

  /* Display: Fundraiser Gateway Switcher */
  $handler = $view->new_display('page', 'Fundraiser Gateway Switcher', 'page_3');
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'use gateway switcher';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Bulk operations: Content */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'node';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::_fundraiser_gateway_switch_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Form Name';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Internal Name */
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['id'] = 'field_fundraiser_internal_name';
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['table'] = 'field_data_field_fundraiser_internal_name';
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['field'] = 'field_fundraiser_internal_name';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = 'Form ID';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Path */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'node';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['exclude'] = TRUE;
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['label'] = 'Action';
  $handler->display->display_options['fields']['view_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_node']['text'] = 'view';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  $handler->display->display_options['path'] = 'admin/content/donation-forms/gateway-switcher';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Gateway Switcher';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Short Springboard Recent Forms by Type */
  $handler = $view->new_display('block', 'Short Springboard Recent Forms by Type', 'block_3');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Recent Forms by Type';
  $handler->display->display_options['defaults']['use_ajax'] = FALSE;
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'path' => 'path',
    'nid' => 'nid',
    'field_webform_user_internal_name' => 'field_webform_user_internal_name',
    'title' => 'title',
    'type' => 'type',
    'webform_submission_count_node' => 'webform_submission_count_node',
    'status' => 'status',
    'clone_node' => 'clone_node',
    'edit_node' => 'clone_node',
    'webform_results' => 'clone_node',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'path' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nid' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_webform_user_internal_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'type' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'webform_submission_count_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'clone_node' => array(
      'align' => '',
      'separator' => '|',
      'empty_column' => 0,
    ),
    'edit_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'webform_results' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Path */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'node';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['exclude'] = TRUE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = 'Form ID';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Internal Name */
  $handler->display->display_options['fields']['field_webform_user_internal_name']['id'] = 'field_webform_user_internal_name';
  $handler->display->display_options['fields']['field_webform_user_internal_name']['table'] = 'field_data_field_webform_user_internal_name';
  $handler->display->display_options['fields']['field_webform_user_internal_name']['field'] = 'field_webform_user_internal_name';
  $handler->display->display_options['fields']['field_webform_user_internal_name']['alter']['max_length'] = '30';
  $handler->display->display_options['fields']['field_webform_user_internal_name']['alter']['trim'] = TRUE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Form Name';
  $handler->display->display_options['fields']['title']['alter']['max_length'] = '30';
  $handler->display->display_options['fields']['title']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'node';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  /* Field: Webform: Webform submission count */
  $handler->display->display_options['fields']['webform_submission_count_node']['id'] = 'webform_submission_count_node';
  $handler->display->display_options['fields']['webform_submission_count_node']['table'] = 'node';
  $handler->display->display_options['fields']['webform_submission_count_node']['field'] = 'webform_submission_count_node';
  $handler->display->display_options['fields']['webform_submission_count_node']['label'] = 'Submissions';
  $handler->display->display_options['fields']['webform_submission_count_node']['element_label_colon'] = FALSE;
  /* Field: Content: Published */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'node';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'Status';
  $handler->display->display_options['fields']['status']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['status']['type'] = 'published-notpublished';
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Field: Content: Clone link */
  $handler->display->display_options['fields']['clone_node']['id'] = 'clone_node';
  $handler->display->display_options['fields']['clone_node']['table'] = 'node';
  $handler->display->display_options['fields']['clone_node']['field'] = 'clone_node';
  $handler->display->display_options['fields']['clone_node']['label'] = 'Action';
  $handler->display->display_options['fields']['clone_node']['element_class'] = 'table-actions';
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Edit';
  /* Field: Webform: Webform results link */
  $handler->display->display_options['fields']['webform_results']['id'] = 'webform_results';
  $handler->display->display_options['fields']['webform_results']['table'] = 'node';
  $handler->display->display_options['fields']['webform_results']['field'] = 'webform_results';
  $handler->display->display_options['fields']['webform_results']['label'] = '';
  $handler->display->display_options['fields']['webform_results']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Type */
  $handler->display->display_options['arguments']['type']['id'] = 'type';
  $handler->display->display_options['arguments']['type']['table'] = 'node';
  $handler->display->display_options['arguments']['type']['field'] = 'type';
  $handler->display->display_options['arguments']['type']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['type']['title'] = 'Recent %1s';
  $handler->display->display_options['arguments']['type']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['type']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['type']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['type']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['type']['limit'] = '0';
  $handler->display->display_options['arguments']['type']['break_phrase'] = TRUE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Global: Combine fields filter */
  $handler->display->display_options['filters']['combine']['id'] = 'combine';
  $handler->display->display_options['filters']['combine']['table'] = 'views';
  $handler->display->display_options['filters']['combine']['field'] = 'combine';
  $handler->display->display_options['filters']['combine']['operator'] = 'contains';
  $handler->display->display_options['filters']['combine']['group'] = 1;
  $handler->display->display_options['filters']['combine']['exposed'] = TRUE;
  $handler->display->display_options['filters']['combine']['expose']['operator_id'] = 'combine_op';
  $handler->display->display_options['filters']['combine']['expose']['operator'] = 'combine_op';
  $handler->display->display_options['filters']['combine']['expose']['identifier'] = 'combine';
  $handler->display->display_options['filters']['combine']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  $handler->display->display_options['filters']['combine']['fields'] = array(
    'field_webform_user_internal_name' => 'field_webform_user_internal_name',
    'title' => 'title',
    'type' => 'type',
  );
  $handler->display->display_options['block_description'] = 'Short Springboard Recent Forms by Type';

  /* Display: Springboard Recent Donation Forms by Type */
  $handler = $view->new_display('block', 'Springboard Recent Donation Forms by Type', 'block_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Recent Forms by Type';
  $handler->display->display_options['defaults']['use_ajax'] = FALSE;
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['defaults']['link_display'] = FALSE;
  $handler->display->display_options['link_display'] = 'page_1';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '35';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'field_fundraiser_internal_name' => 'field_fundraiser_internal_name',
    'title' => 'title',
    'nid' => 'nid',
    'status' => 'status',
    'changed' => 'changed',
    'path' => 'path',
    'clone_node' => 'clone_node',
    'edit_node' => 'clone_node',
    'view_node' => 'clone_node',
  );
  $handler->display->display_options['style_options']['default'] = 'changed';
  $handler->display->display_options['style_options']['info'] = array(
    'field_fundraiser_internal_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nid' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'changed' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'path' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'clone_node' => array(
      'align' => '',
      'separator' => ' | ',
      'empty_column' => 0,
    ),
    'edit_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'view_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Internal Name */
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['id'] = 'field_fundraiser_internal_name';
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['table'] = 'field_data_field_fundraiser_internal_name';
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['field'] = 'field_fundraiser_internal_name';
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['alter']['max_length'] = '30';
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Form Name';
  $handler->display->display_options['fields']['title']['alter']['max_length'] = '30';
  $handler->display->display_options['fields']['title']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = 'Form ID';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Published */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'node';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'Status';
  $handler->display->display_options['fields']['status']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['status']['type'] = 'published-notpublished';
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Field: Content: Updated date */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'node';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['label'] = 'Last Updated';
  $handler->display->display_options['fields']['changed']['date_format'] = 'custom';
  $handler->display->display_options['fields']['changed']['custom_date_format'] = 'n/j/Y';
  $handler->display->display_options['fields']['changed']['second_date_format'] = 'long';
  /* Field: Content: Path */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'node';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['exclude'] = TRUE;
  /* Field: Content: Clone link */
  $handler->display->display_options['fields']['clone_node']['id'] = 'clone_node';
  $handler->display->display_options['fields']['clone_node']['table'] = 'node';
  $handler->display->display_options['fields']['clone_node']['field'] = 'clone_node';
  $handler->display->display_options['fields']['clone_node']['label'] = 'Action';
  $handler->display->display_options['fields']['clone_node']['element_class'] = 'table-actions';
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Edit';
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['element_class'] = 'table-actions';
  $handler->display->display_options['fields']['view_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_node']['text'] = 'view';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Type */
  $handler->display->display_options['arguments']['type']['id'] = 'type';
  $handler->display->display_options['arguments']['type']['table'] = 'node';
  $handler->display->display_options['arguments']['type']['field'] = 'type';
  $handler->display->display_options['arguments']['type']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['type']['title'] = 'Recent %1s';
  $handler->display->display_options['arguments']['type']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['type']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['type']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['type']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['type']['limit'] = '0';
  $handler->display->display_options['arguments']['type']['break_phrase'] = TRUE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  $handler->display->display_options['block_description'] = 'Springboard Recent Donation Forms by Type';

  /* Display: Springboard Recent Donation Forms by Type Page */
  $handler = $view->new_display('page', 'Springboard Recent Donation Forms by Type Page', 'page_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Recent forms by type';
  $handler->display->display_options['defaults']['use_ajax'] = FALSE;
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '35';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'field_fundraiser_internal_name' => 'field_fundraiser_internal_name',
    'title' => 'title',
    'nid' => 'nid',
    'status' => 'status',
    'changed' => 'changed',
    'path' => 'path',
    'clone_node' => 'clone_node',
    'edit_node' => 'clone_node',
    'view_node' => 'clone_node',
  );
  $handler->display->display_options['style_options']['default'] = 'changed';
  $handler->display->display_options['style_options']['info'] = array(
    'field_fundraiser_internal_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nid' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'changed' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'path' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'clone_node' => array(
      'align' => '',
      'separator' => ' | ',
      'empty_column' => 0,
    ),
    'edit_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'view_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['empty'] = FALSE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'Your search returned 0 results, please try again.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Internal Name */
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['id'] = 'field_fundraiser_internal_name';
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['table'] = 'field_data_field_fundraiser_internal_name';
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['field'] = 'field_fundraiser_internal_name';
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Form Name';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = 'Form ID';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Published */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'node';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'Status';
  $handler->display->display_options['fields']['status']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['status']['type'] = 'published-notpublished';
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Field: Content: Updated date */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'node';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['label'] = 'Last Updated';
  $handler->display->display_options['fields']['changed']['date_format'] = 'custom';
  $handler->display->display_options['fields']['changed']['custom_date_format'] = 'n/j/Y';
  $handler->display->display_options['fields']['changed']['second_date_format'] = 'long';
  /* Field: Content: Path */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'node';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['exclude'] = TRUE;
  /* Field: Content: Clone link */
  $handler->display->display_options['fields']['clone_node']['id'] = 'clone_node';
  $handler->display->display_options['fields']['clone_node']['table'] = 'node';
  $handler->display->display_options['fields']['clone_node']['field'] = 'clone_node';
  $handler->display->display_options['fields']['clone_node']['label'] = 'Action';
  $handler->display->display_options['fields']['clone_node']['element_class'] = 'table-actions';
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Edit';
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['element_class'] = 'table-actions';
  $handler->display->display_options['fields']['view_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_node']['text'] = 'view';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Type */
  $handler->display->display_options['arguments']['type']['id'] = 'type';
  $handler->display->display_options['arguments']['type']['table'] = 'node';
  $handler->display->display_options['arguments']['type']['field'] = 'type';
  $handler->display->display_options['arguments']['type']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['type']['title'] = '%1s';
  $handler->display->display_options['arguments']['type']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['type']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['type']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['type']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['type']['limit'] = '0';
  $handler->display->display_options['arguments']['type']['break_phrase'] = TRUE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Global: Combine fields filter */
  $handler->display->display_options['filters']['combine']['id'] = 'combine';
  $handler->display->display_options['filters']['combine']['table'] = 'views';
  $handler->display->display_options['filters']['combine']['field'] = 'combine';
  $handler->display->display_options['filters']['combine']['operator'] = 'contains';
  $handler->display->display_options['filters']['combine']['exposed'] = TRUE;
  $handler->display->display_options['filters']['combine']['expose']['operator_id'] = 'combine_op';
  $handler->display->display_options['filters']['combine']['expose']['label'] = 'Search';
  $handler->display->display_options['filters']['combine']['expose']['operator'] = 'combine_op';
  $handler->display->display_options['filters']['combine']['expose']['identifier'] = 'combine';
  $handler->display->display_options['filters']['combine']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  $handler->display->display_options['filters']['combine']['fields'] = array(
    'field_fundraiser_internal_name' => 'field_fundraiser_internal_name',
    'title' => 'title',
  );
  /* Filter criterion: Date: Date (node_revision) */
  $handler->display->display_options['filters']['date_filter']['id'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['table'] = 'node_revision';
  $handler->display->display_options['filters']['date_filter']['field'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['operator'] = 'between';
  $handler->display->display_options['filters']['date_filter']['exposed'] = TRUE;
  $handler->display->display_options['filters']['date_filter']['expose']['operator_id'] = 'date_filter_op';
  $handler->display->display_options['filters']['date_filter']['expose']['operator'] = 'date_filter_op';
  $handler->display->display_options['filters']['date_filter']['expose']['identifier'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  $handler->display->display_options['filters']['date_filter']['form_type'] = 'date_popup';
  $handler->display->display_options['filters']['date_filter']['date_fields'] = array(
    'node_revision.timestamp' => 'node_revision.timestamp',
  );
  $handler->display->display_options['path'] = 'admin/springboard/donation-forms/%';

  /* Display: Springboard Recent Forms by Type */
  $handler = $view->new_display('page', 'Springboard Recent Forms by Type', 'page_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Recent Forms by Type Page';
  $handler->display->display_options['defaults']['use_ajax'] = FALSE;
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '35';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'field_fundraiser_internal_name' => 'field_fundraiser_internal_name',
    'title' => 'title',
    'nid' => 'nid',
    'status' => 'status',
    'created' => 'created',
    'path' => 'path',
    'webform_submission_count_node' => 'webform_submission_count_node',
    'clone_node' => 'clone_node',
    'edit_node' => 'clone_node',
    'view_node' => 'clone_node',
    'field_webform_user_internal_name' => 'field_fundraiser_internal_name',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'field_fundraiser_internal_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nid' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'path' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'webform_submission_count_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'clone_node' => array(
      'align' => '',
      'separator' => ' | ',
      'empty_column' => 0,
    ),
    'edit_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'view_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_webform_user_internal_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'Your search returned 0 results, please try again.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Internal Name */
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['id'] = 'field_fundraiser_internal_name';
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['table'] = 'field_data_field_fundraiser_internal_name';
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['field'] = 'field_fundraiser_internal_name';
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Form Name';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = 'Form ID';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Published */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'node';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'Status';
  $handler->display->display_options['fields']['status']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['status']['type'] = 'published-notpublished';
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Date Created';
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'n/j/o';
  /* Field: Content: Path */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'node';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['exclude'] = TRUE;
  /* Field: Webform: Webform submission count */
  $handler->display->display_options['fields']['webform_submission_count_node']['id'] = 'webform_submission_count_node';
  $handler->display->display_options['fields']['webform_submission_count_node']['table'] = 'node';
  $handler->display->display_options['fields']['webform_submission_count_node']['field'] = 'webform_submission_count_node';
  $handler->display->display_options['fields']['webform_submission_count_node']['label'] = 'Submissions';
  $handler->display->display_options['fields']['webform_submission_count_node']['element_label_colon'] = FALSE;
  /* Field: Content: Clone link */
  $handler->display->display_options['fields']['clone_node']['id'] = 'clone_node';
  $handler->display->display_options['fields']['clone_node']['table'] = 'node';
  $handler->display->display_options['fields']['clone_node']['field'] = 'clone_node';
  $handler->display->display_options['fields']['clone_node']['label'] = 'Action';
  $handler->display->display_options['fields']['clone_node']['element_class'] = 'table-actions';
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Edit';
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['element_class'] = 'table-actions';
  $handler->display->display_options['fields']['view_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_node']['text'] = 'view';
  /* Field: Content: Internal Name */
  $handler->display->display_options['fields']['field_webform_user_internal_name']['id'] = 'field_webform_user_internal_name';
  $handler->display->display_options['fields']['field_webform_user_internal_name']['table'] = 'field_data_field_webform_user_internal_name';
  $handler->display->display_options['fields']['field_webform_user_internal_name']['field'] = 'field_webform_user_internal_name';
  $handler->display->display_options['fields']['field_webform_user_internal_name']['label'] = '';
  $handler->display->display_options['fields']['field_webform_user_internal_name']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Type */
  $handler->display->display_options['arguments']['type']['id'] = 'type';
  $handler->display->display_options['arguments']['type']['table'] = 'node';
  $handler->display->display_options['arguments']['type']['field'] = 'type';
  $handler->display->display_options['arguments']['type']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['type']['title'] = '%1s';
  $handler->display->display_options['arguments']['type']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['type']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['type']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['type']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['type']['limit'] = '0';
  $handler->display->display_options['arguments']['type']['break_phrase'] = TRUE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Global: Combine fields filter */
  $handler->display->display_options['filters']['combine']['id'] = 'combine';
  $handler->display->display_options['filters']['combine']['table'] = 'views';
  $handler->display->display_options['filters']['combine']['field'] = 'combine';
  $handler->display->display_options['filters']['combine']['operator'] = 'contains';
  $handler->display->display_options['filters']['combine']['exposed'] = TRUE;
  $handler->display->display_options['filters']['combine']['expose']['operator_id'] = 'combine_op';
  $handler->display->display_options['filters']['combine']['expose']['label'] = 'Search';
  $handler->display->display_options['filters']['combine']['expose']['operator'] = 'combine_op';
  $handler->display->display_options['filters']['combine']['expose']['identifier'] = 'combine';
  $handler->display->display_options['filters']['combine']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  $handler->display->display_options['filters']['combine']['fields'] = array(
    'field_fundraiser_internal_name' => 'field_fundraiser_internal_name',
    'title' => 'title',
  );
  /* Filter criterion: Date: Date (node_revision) */
  $handler->display->display_options['filters']['date_filter']['id'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['table'] = 'node_revision';
  $handler->display->display_options['filters']['date_filter']['field'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['operator'] = 'between';
  $handler->display->display_options['filters']['date_filter']['exposed'] = TRUE;
  $handler->display->display_options['filters']['date_filter']['expose']['operator_id'] = 'date_filter_op';
  $handler->display->display_options['filters']['date_filter']['expose']['operator'] = 'date_filter_op';
  $handler->display->display_options['filters']['date_filter']['expose']['identifier'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  $handler->display->display_options['filters']['date_filter']['form_type'] = 'date_popup';
  $handler->display->display_options['filters']['date_filter']['date_fields'] = array(
    'node_revision.timestamp' => 'node_revision.timestamp',
  );
  $handler->display->display_options['path'] = 'admin/springboard/forms/%';

  /* Display: Short Springboard Recent Donation Forms by Type */
  $handler = $view->new_display('block', 'Short Springboard Recent Donation Forms by Type', 'block_4');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Recent Forms by Type';
  $handler->display->display_options['defaults']['use_ajax'] = FALSE;
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'path' => 'path',
    'nid' => 'nid',
    'field_fundraiser_internal_name' => 'field_fundraiser_internal_name',
    'field_webform_user_internal_name' => 'field_fundraiser_internal_name',
    'title' => 'title',
    'sbstats_total_transactions' => 'sbstats_total_transactions',
    'status' => 'status',
    'clone_node' => 'clone_node',
    'edit_node' => 'clone_node',
    'webform_results' => 'clone_node',
    'type' => 'type',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'path' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nid' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_fundraiser_internal_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_webform_user_internal_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'sbstats_total_transactions' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'clone_node' => array(
      'align' => '',
      'separator' => '|',
      'empty_column' => 0,
    ),
    'edit_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'webform_results' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'type' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Path */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'node';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['exclude'] = TRUE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = 'Form ID';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Internal Name */
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['id'] = 'field_fundraiser_internal_name';
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['table'] = 'field_data_field_fundraiser_internal_name';
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['field'] = 'field_fundraiser_internal_name';
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Form Name';
  $handler->display->display_options['fields']['title']['alter']['max_length'] = '30';
  $handler->display->display_options['fields']['title']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'node';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  /* Field: Content: Published */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'node';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'Status';
  $handler->display->display_options['fields']['status']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['status']['type'] = 'published-notpublished';
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Field: Content: Clone link */
  $handler->display->display_options['fields']['clone_node']['id'] = 'clone_node';
  $handler->display->display_options['fields']['clone_node']['table'] = 'node';
  $handler->display->display_options['fields']['clone_node']['field'] = 'clone_node';
  $handler->display->display_options['fields']['clone_node']['label'] = 'Action';
  $handler->display->display_options['fields']['clone_node']['element_class'] = 'table-actions';
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Edit';
  /* Field: Webform: Webform results link */
  $handler->display->display_options['fields']['webform_results']['id'] = 'webform_results';
  $handler->display->display_options['fields']['webform_results']['table'] = 'node';
  $handler->display->display_options['fields']['webform_results']['field'] = 'webform_results';
  $handler->display->display_options['fields']['webform_results']['label'] = '';
  $handler->display->display_options['fields']['webform_results']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Type */
  $handler->display->display_options['arguments']['type']['id'] = 'type';
  $handler->display->display_options['arguments']['type']['table'] = 'node';
  $handler->display->display_options['arguments']['type']['field'] = 'type';
  $handler->display->display_options['arguments']['type']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['type']['title'] = 'Recent %1s';
  $handler->display->display_options['arguments']['type']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['type']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['type']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['type']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['type']['limit'] = '0';
  $handler->display->display_options['arguments']['type']['break_phrase'] = TRUE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Global: Combine fields filter */
  $handler->display->display_options['filters']['combine']['id'] = 'combine';
  $handler->display->display_options['filters']['combine']['table'] = 'views';
  $handler->display->display_options['filters']['combine']['field'] = 'combine';
  $handler->display->display_options['filters']['combine']['operator'] = 'contains';
  $handler->display->display_options['filters']['combine']['group'] = 1;
  $handler->display->display_options['filters']['combine']['exposed'] = TRUE;
  $handler->display->display_options['filters']['combine']['expose']['operator_id'] = 'combine_op';
  $handler->display->display_options['filters']['combine']['expose']['operator'] = 'combine_op';
  $handler->display->display_options['filters']['combine']['expose']['identifier'] = 'combine';
  $handler->display->display_options['filters']['combine']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  $handler->display->display_options['filters']['combine']['fields'] = array(
    'field_fundraiser_internal_name' => 'field_fundraiser_internal_name',
    'title' => 'title',
    'type' => 'type',
  );
  $handler->display->display_options['block_description'] = 'Short Springboard Recent Donation Forms by Type';
  $views[$view->name] = $view;

  /**
   * View 'sbv_donations'
   */
  $view = new view();
  $view->name = 'sbv_donations';
  $view->description = 'Donations currently in the system';
  $view->tag = 'springboard_views';
  $view->base_table = 'fundraiser_donation';
  $view->human_name = 'sbv_donations';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Donations';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer fundraiser';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '35';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'order_id' => 'order_id',
    'created' => 'created',
    'commerce_order_total' => 'commerce_order_total',
    'sbp_first_name' => 'sbp_first_name',
    'sbp_last_name' => 'sbp_first_name',
    'mail' => 'mail',
    'title' => 'title',
    'field_fundraiser_internal_name' => 'field_fundraiser_internal_name',
    'status' => 'status',
    'view_order' => 'view_order',
    'transaction_id' => 'transaction_id',
    'nothing' => 'view_order',
    'nid' => 'nid',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'order_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'commerce_order_total' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'sbp_first_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '  ',
      'empty_column' => 0,
    ),
    'sbp_last_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'mail' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_fundraiser_internal_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'view_order' => array(
      'align' => '',
      'separator' => ' | ',
      'empty_column' => 0,
    ),
    'transaction_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nothing' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Relationship: Fundraiser donations: Donating user */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'fundraiser_donation';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Relationship: Fundraiser donations: Fundraiser node */
  $handler->display->display_options['relationships']['nid']['id'] = 'nid';
  $handler->display->display_options['relationships']['nid']['table'] = 'fundraiser_donation';
  $handler->display->display_options['relationships']['nid']['field'] = 'nid';
  /* Relationship: Fundraiser donations: Commerce order */
  $handler->display->display_options['relationships']['did']['id'] = 'did';
  $handler->display->display_options['relationships']['did']['table'] = 'fundraiser_donation';
  $handler->display->display_options['relationships']['did']['field'] = 'did';
  /* Relationship: Commerce Order: Owner */
  $handler->display->display_options['relationships']['uid_1']['id'] = 'uid_1';
  $handler->display->display_options['relationships']['uid_1']['table'] = 'commerce_order';
  $handler->display->display_options['relationships']['uid_1']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid_1']['relationship'] = 'did';
  /* Relationship: Fundraiser donations: Webform Submission */
  $handler->display->display_options['relationships']['sid_2']['id'] = 'sid_2';
  $handler->display->display_options['relationships']['sid_2']['table'] = 'fundraiser_donation';
  $handler->display->display_options['relationships']['sid_2']['field'] = 'sid';
  /* Field: Commerce Order: Order ID */
  $handler->display->display_options['fields']['order_id']['id'] = 'order_id';
  $handler->display->display_options['fields']['order_id']['table'] = 'commerce_order';
  $handler->display->display_options['fields']['order_id']['field'] = 'order_id';
  $handler->display->display_options['fields']['order_id']['relationship'] = 'did';
  /* Field: Commerce Order: Created date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'commerce_order';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['relationship'] = 'did';
  $handler->display->display_options['fields']['created']['label'] = 'Date';
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'n/j/Y';
  /* Field: Commerce Payment Transaction: Amount */
  $handler->display->display_options['fields']['amount']['id'] = 'amount';
  $handler->display->display_options['fields']['amount']['table'] = 'commerce_payment_transaction';
  $handler->display->display_options['fields']['amount']['field'] = 'amount';
  $handler->display->display_options['fields']['amount']['relationship'] = 'payment_transaction';
  /* Field: User: First name */
  $handler->display->display_options['fields']['sbp_first_name']['id'] = 'sbp_first_name';
  $handler->display->display_options['fields']['sbp_first_name']['table'] = 'field_data_sbp_first_name';
  $handler->display->display_options['fields']['sbp_first_name']['field'] = 'sbp_first_name';
  $handler->display->display_options['fields']['sbp_first_name']['relationship'] = 'uid';
  /* Field: User: Last name */
  $handler->display->display_options['fields']['sbp_last_name']['id'] = 'sbp_last_name';
  $handler->display->display_options['fields']['sbp_last_name']['table'] = 'field_data_sbp_last_name';
  $handler->display->display_options['fields']['sbp_last_name']['field'] = 'sbp_last_name';
  $handler->display->display_options['fields']['sbp_last_name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['sbp_last_name']['label'] = 'Last Name';
  $handler->display->display_options['fields']['sbp_last_name']['element_label_colon'] = FALSE;
  /* Field: User: E-mail */
  $handler->display->display_options['fields']['mail']['id'] = 'mail';
  $handler->display->display_options['fields']['mail']['table'] = 'users';
  $handler->display->display_options['fields']['mail']['field'] = 'mail';
  $handler->display->display_options['fields']['mail']['relationship'] = 'uid';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'nid';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  /* Field: Content: Internal Name */
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['id'] = 'field_fundraiser_internal_name';
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['table'] = 'field_data_field_fundraiser_internal_name';
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['field'] = 'field_fundraiser_internal_name';
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['relationship'] = 'nid';
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['label'] = 'Form';
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['alter']['text'] = '[title] ([field_fundraiser_internal_name-value])';
  /* Field: Commerce Order: Order status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'commerce_order';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['relationship'] = 'did';
  /* Field: Commerce Order: Link */
  $handler->display->display_options['fields']['view_order']['id'] = 'view_order';
  $handler->display->display_options['fields']['view_order']['table'] = 'commerce_order';
  $handler->display->display_options['fields']['view_order']['field'] = 'view_order';
  $handler->display->display_options['fields']['view_order']['relationship'] = 'did';
  $handler->display->display_options['fields']['view_order']['label'] = 'Actions';
  $handler->display->display_options['fields']['view_order']['text'] = 'View order';
  /* Field: Webform submissions: View link */
  $handler->display->display_options['fields']['view_submission']['id'] = 'view_submission';
  $handler->display->display_options['fields']['view_submission']['table'] = 'webform_submissions';
  $handler->display->display_options['fields']['view_submission']['field'] = 'view_submission';
  $handler->display->display_options['fields']['view_submission']['relationship'] = 'sid_2';
  $handler->display->display_options['fields']['view_submission']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_submission']['text'] = 'View submission';
  /* Field: Commerce Payment Transaction: Transaction ID */
  $handler->display->display_options['fields']['transaction_id']['id'] = 'transaction_id';
  $handler->display->display_options['fields']['transaction_id']['table'] = 'commerce_payment_transaction';
  $handler->display->display_options['fields']['transaction_id']['field'] = 'transaction_id';
  $handler->display->display_options['fields']['transaction_id']['relationship'] = 'payment_transaction';
  $handler->display->display_options['fields']['transaction_id']['label'] = '';
  $handler->display->display_options['fields']['transaction_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['transaction_id']['element_label_colon'] = FALSE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<a href="/admin/commerce/orders/[order_id]/payment/[transaction_id]/refund">Refund</a>';
  /* Filter criterion: Global: Combine fields filter */
  $handler->display->display_options['filters']['combine']['id'] = 'combine';
  $handler->display->display_options['filters']['combine']['table'] = 'views';
  $handler->display->display_options['filters']['combine']['field'] = 'combine';
  $handler->display->display_options['filters']['combine']['operator'] = 'contains';
  $handler->display->display_options['filters']['combine']['group'] = 1;
  $handler->display->display_options['filters']['combine']['exposed'] = TRUE;
  $handler->display->display_options['filters']['combine']['expose']['operator_id'] = 'combine_op';
  $handler->display->display_options['filters']['combine']['expose']['label'] = 'Search';
  $handler->display->display_options['filters']['combine']['expose']['operator'] = 'combine_op';
  $handler->display->display_options['filters']['combine']['expose']['identifier'] = 'combine';
  $handler->display->display_options['filters']['combine']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  $handler->display->display_options['filters']['combine']['group_info']['label'] = 'Combine fields filter';
  $handler->display->display_options['filters']['combine']['group_info']['identifier'] = 'combine';
  $handler->display->display_options['filters']['combine']['group_info']['group_items'] = array(
    1 => array(
      'title' => '',
      'operator' => 'contains',
      'value' => '',
    ),
    2 => array(
      'title' => '',
      'operator' => 'contains',
      'value' => '',
    ),
    3 => array(
      'title' => '',
      'operator' => 'contains',
      'value' => '',
    ),
  );
  $handler->display->display_options['filters']['combine']['fields'] = array(
    'order_id' => 'order_id',
    'sbp_first_name' => 'sbp_first_name',
    'sbp_last_name' => 'sbp_last_name',
    'mail' => 'mail',
    'title' => 'title',
  );
  /* Filter criterion: Commerce Order: Order status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'commerce_order';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['relationship'] = 'did';
  $handler->display->display_options['filters']['status']['value'] = array(
    'failed_refund' => 'failed_refund',
    'failed' => 'failed',
    'canceled' => 'canceled',
    'pending_future_payment' => 'pending_future_payment',
    'refunded' => 'refunded',
    'partially_refunded' => 'partially_refunded',
    'payment_received' => 'payment_received',
  );
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['exposed'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['operator_id'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['label'] = 'Order status';
  $handler->display->display_options['filters']['status']['expose']['operator'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['identifier'] = 'status';
  $handler->display->display_options['filters']['status']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  $handler->display->display_options['filters']['status']['expose']['reduce'] = TRUE;
  /* Filter criterion: Date: Date (node) */
  $handler->display->display_options['filters']['date_filter']['id'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['table'] = 'node';
  $handler->display->display_options['filters']['date_filter']['field'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['relationship'] = 'nid';
  $handler->display->display_options['filters']['date_filter']['operator'] = 'between';
  $handler->display->display_options['filters']['date_filter']['group'] = 1;
  $handler->display->display_options['filters']['date_filter']['exposed'] = TRUE;
  $handler->display->display_options['filters']['date_filter']['expose']['operator_id'] = 'date_filter_op';
  $handler->display->display_options['filters']['date_filter']['expose']['operator'] = 'date_filter_op';
  $handler->display->display_options['filters']['date_filter']['expose']['identifier'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  $handler->display->display_options['filters']['date_filter']['form_type'] = 'date_popup';
  $handler->display->display_options['filters']['date_filter']['date_fields'] = array(
    'fundraiser_donation.created' => 'fundraiser_donation.created',
  );

  /* Display: Unfiltered Page */
  $handler = $view->new_display('page', 'Unfiltered Page', 'page');
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'views-data-table';
  $handler->display->display_options['defaults']['use_ajax'] = FALSE;
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Commerce Order: Order ID */
  $handler->display->display_options['fields']['order_id']['id'] = 'order_id';
  $handler->display->display_options['fields']['order_id']['table'] = 'commerce_order';
  $handler->display->display_options['fields']['order_id']['field'] = 'order_id';
  $handler->display->display_options['fields']['order_id']['relationship'] = 'did';
  /* Field: Commerce Order: Created date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'commerce_order';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['relationship'] = 'did';
  $handler->display->display_options['fields']['created']['label'] = 'Date';
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'n/j/Y';
  /* Field: Commerce Order: Order total */
  $handler->display->display_options['fields']['commerce_order_total']['id'] = 'commerce_order_total';
  $handler->display->display_options['fields']['commerce_order_total']['table'] = 'field_data_commerce_order_total';
  $handler->display->display_options['fields']['commerce_order_total']['field'] = 'commerce_order_total';
  $handler->display->display_options['fields']['commerce_order_total']['relationship'] = 'did';
  $handler->display->display_options['fields']['commerce_order_total']['label'] = 'Amount';
  $handler->display->display_options['fields']['commerce_order_total']['click_sort_column'] = 'amount';
  $handler->display->display_options['fields']['commerce_order_total']['settings'] = array(
    'calculation' => FALSE,
  );
  /* Field: User: First name */
  $handler->display->display_options['fields']['sbp_first_name']['id'] = 'sbp_first_name';
  $handler->display->display_options['fields']['sbp_first_name']['table'] = 'field_data_sbp_first_name';
  $handler->display->display_options['fields']['sbp_first_name']['field'] = 'sbp_first_name';
  $handler->display->display_options['fields']['sbp_first_name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['sbp_first_name']['label'] = 'Name';
  /* Field: User: Last name */
  $handler->display->display_options['fields']['sbp_last_name']['id'] = 'sbp_last_name';
  $handler->display->display_options['fields']['sbp_last_name']['table'] = 'field_data_sbp_last_name';
  $handler->display->display_options['fields']['sbp_last_name']['field'] = 'sbp_last_name';
  $handler->display->display_options['fields']['sbp_last_name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['sbp_last_name']['label'] = 'Last Name';
  $handler->display->display_options['fields']['sbp_last_name']['element_label_colon'] = FALSE;
  /* Field: User: E-mail */
  $handler->display->display_options['fields']['mail']['id'] = 'mail';
  $handler->display->display_options['fields']['mail']['table'] = 'users';
  $handler->display->display_options['fields']['mail']['field'] = 'mail';
  $handler->display->display_options['fields']['mail']['relationship'] = 'uid';
  $handler->display->display_options['fields']['mail']['link_to_user'] = 'user';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'nid';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  /* Field: Content: Internal Name */
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['id'] = 'field_fundraiser_internal_name';
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['table'] = 'field_data_field_fundraiser_internal_name';
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['field'] = 'field_fundraiser_internal_name';
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['relationship'] = 'nid';
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['label'] = 'Form';
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['alter']['text'] = '<span class="form-name-title truncate">[title]</span> <span class="form-internal-name">([field_fundraiser_internal_name-value])</span>';
  /* Field: Commerce Order: Order status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'commerce_order';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['relationship'] = 'did';
  /* Field: Commerce Order: Link */
  $handler->display->display_options['fields']['view_order']['id'] = 'view_order';
  $handler->display->display_options['fields']['view_order']['table'] = 'commerce_order';
  $handler->display->display_options['fields']['view_order']['field'] = 'view_order';
  $handler->display->display_options['fields']['view_order']['relationship'] = 'did';
  $handler->display->display_options['fields']['view_order']['label'] = 'Actions';
  $handler->display->display_options['fields']['view_order']['text'] = 'View order';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'Payments';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = 'admin/commerce/orders/[order_id]/payment';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['relationship'] = 'sid_2';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['path'] = 'admin/reports/salesforce/donations';

  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'views-data-table';
  $handler->display->display_options['defaults']['use_ajax'] = FALSE;
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '0';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'views_data_export_csv';
  $handler->display->display_options['style_options']['attach_text'] = 'Download as .CSV';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['filename'] = 'donation-export-%timestamp-full.csv';
  $handler->display->display_options['style_options']['parent_sort'] = 1;
  $handler->display->display_options['style_options']['quote'] = 1;
  $handler->display->display_options['style_options']['trim'] = 0;
  $handler->display->display_options['style_options']['replace_newlines'] = 0;
  $handler->display->display_options['style_options']['header'] = 1;
  $handler->display->display_options['style_options']['keep_html'] = 0;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Commerce Order: Order ID */
  $handler->display->display_options['fields']['order_id']['id'] = 'order_id';
  $handler->display->display_options['fields']['order_id']['table'] = 'commerce_order';
  $handler->display->display_options['fields']['order_id']['field'] = 'order_id';
  $handler->display->display_options['fields']['order_id']['relationship'] = 'did';
  /* Field: Commerce Order: Created date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'commerce_order';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['relationship'] = 'did';
  $handler->display->display_options['fields']['created']['label'] = 'Date';
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'n/j/Y';
  /* Field: Commerce Order: Order total */
  $handler->display->display_options['fields']['commerce_order_total']['id'] = 'commerce_order_total';
  $handler->display->display_options['fields']['commerce_order_total']['table'] = 'field_data_commerce_order_total';
  $handler->display->display_options['fields']['commerce_order_total']['field'] = 'commerce_order_total';
  $handler->display->display_options['fields']['commerce_order_total']['relationship'] = 'did';
  $handler->display->display_options['fields']['commerce_order_total']['label'] = 'Amount';
  $handler->display->display_options['fields']['commerce_order_total']['click_sort_column'] = 'amount';
  $handler->display->display_options['fields']['commerce_order_total']['settings'] = array(
    'calculation' => FALSE,
  );
  /* Field: User: First name */
  $handler->display->display_options['fields']['sbp_first_name']['id'] = 'sbp_first_name';
  $handler->display->display_options['fields']['sbp_first_name']['table'] = 'field_data_sbp_first_name';
  $handler->display->display_options['fields']['sbp_first_name']['field'] = 'sbp_first_name';
  $handler->display->display_options['fields']['sbp_first_name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['sbp_first_name']['label'] = 'Name';
  /* Field: User: Last name */
  $handler->display->display_options['fields']['sbp_last_name']['id'] = 'sbp_last_name';
  $handler->display->display_options['fields']['sbp_last_name']['table'] = 'field_data_sbp_last_name';
  $handler->display->display_options['fields']['sbp_last_name']['field'] = 'sbp_last_name';
  $handler->display->display_options['fields']['sbp_last_name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['sbp_last_name']['label'] = 'Last Name';
  $handler->display->display_options['fields']['sbp_last_name']['element_label_colon'] = FALSE;
  /* Field: User: E-mail */
  $handler->display->display_options['fields']['mail']['id'] = 'mail';
  $handler->display->display_options['fields']['mail']['table'] = 'users';
  $handler->display->display_options['fields']['mail']['field'] = 'mail';
  $handler->display->display_options['fields']['mail']['relationship'] = 'uid';
  $handler->display->display_options['fields']['mail']['link_to_user'] = 'user';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'nid';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  /* Field: Content: Internal Name */
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['id'] = 'field_fundraiser_internal_name';
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['table'] = 'field_data_field_fundraiser_internal_name';
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['field'] = 'field_fundraiser_internal_name';
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['relationship'] = 'nid';
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['label'] = 'Form';
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['alter']['text'] = '<span class="form-name-title truncate">[title]</span> <span class="form-internal-name">([field_fundraiser_internal_name-value])</span>';
  /* Field: Commerce Order: Order status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'commerce_order';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['relationship'] = 'did';
  /* Field: Commerce Order: Link */
  $handler->display->display_options['fields']['view_order']['id'] = 'view_order';
  $handler->display->display_options['fields']['view_order']['table'] = 'commerce_order';
  $handler->display->display_options['fields']['view_order']['field'] = 'view_order';
  $handler->display->display_options['fields']['view_order']['relationship'] = 'did';
  $handler->display->display_options['fields']['view_order']['label'] = 'Actions';
  $handler->display->display_options['fields']['view_order']['text'] = 'View order';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'Payments';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = 'admin/commerce/orders/[order_id]/payment';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['relationship'] = 'sid_2';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['path'] = 'admin/reports/salesforce/donations/export';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'page_1' => 'page_1',
    'default' => 0,
  );
  $handler->display->display_options['use_batch'] = 'batch';
  $handler->display->display_options['return_path'] = 'admin/reports/salesforce/donations';
  $handler->display->display_options['segment_size'] = '100';

  /* Display: Filtered Page */
  $handler = $view->new_display('page', 'Filtered Page', 'page_1');
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'views-data-table';
  $handler->display->display_options['defaults']['use_ajax'] = FALSE;
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['empty'] = FALSE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = '<h2>Your search yielded no results</h2>';
  $handler->display->display_options['empty']['area']['format'] = 'full_html';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Commerce Order: Order ID */
  $handler->display->display_options['fields']['order_id']['id'] = 'order_id';
  $handler->display->display_options['fields']['order_id']['table'] = 'commerce_order';
  $handler->display->display_options['fields']['order_id']['field'] = 'order_id';
  $handler->display->display_options['fields']['order_id']['relationship'] = 'did';
  /* Field: Commerce Order: Created date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'commerce_order';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['relationship'] = 'did';
  $handler->display->display_options['fields']['created']['label'] = 'Date';
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'n/j/Y';
  /* Field: Commerce Order: Order total */
  $handler->display->display_options['fields']['commerce_order_total']['id'] = 'commerce_order_total';
  $handler->display->display_options['fields']['commerce_order_total']['table'] = 'field_data_commerce_order_total';
  $handler->display->display_options['fields']['commerce_order_total']['field'] = 'commerce_order_total';
  $handler->display->display_options['fields']['commerce_order_total']['relationship'] = 'did';
  $handler->display->display_options['fields']['commerce_order_total']['label'] = 'Amount';
  $handler->display->display_options['fields']['commerce_order_total']['click_sort_column'] = 'amount';
  $handler->display->display_options['fields']['commerce_order_total']['settings'] = array(
    'calculation' => FALSE,
  );
  /* Field: User: First name */
  $handler->display->display_options['fields']['sbp_first_name']['id'] = 'sbp_first_name';
  $handler->display->display_options['fields']['sbp_first_name']['table'] = 'field_data_sbp_first_name';
  $handler->display->display_options['fields']['sbp_first_name']['field'] = 'sbp_first_name';
  $handler->display->display_options['fields']['sbp_first_name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['sbp_first_name']['label'] = 'Name';
  /* Field: User: Last name */
  $handler->display->display_options['fields']['sbp_last_name']['id'] = 'sbp_last_name';
  $handler->display->display_options['fields']['sbp_last_name']['table'] = 'field_data_sbp_last_name';
  $handler->display->display_options['fields']['sbp_last_name']['field'] = 'sbp_last_name';
  $handler->display->display_options['fields']['sbp_last_name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['sbp_last_name']['label'] = 'Last Name';
  $handler->display->display_options['fields']['sbp_last_name']['element_label_colon'] = FALSE;
  /* Field: User: E-mail */
  $handler->display->display_options['fields']['mail']['id'] = 'mail';
  $handler->display->display_options['fields']['mail']['table'] = 'users';
  $handler->display->display_options['fields']['mail']['field'] = 'mail';
  $handler->display->display_options['fields']['mail']['relationship'] = 'uid';
  $handler->display->display_options['fields']['mail']['link_to_user'] = 'user';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'nid';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  /* Field: Content: Internal Name */
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['id'] = 'field_fundraiser_internal_name';
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['table'] = 'field_data_field_fundraiser_internal_name';
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['field'] = 'field_fundraiser_internal_name';
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['relationship'] = 'nid';
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['label'] = 'Form';
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_fundraiser_internal_name']['alter']['text'] = '<span class="form-name-title truncate">[title]</span> <span class="form-internal-name">([field_fundraiser_internal_name-value])</span>';
  /* Field: Commerce Order: Order status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'commerce_order';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['relationship'] = 'did';
  /* Field: Commerce Order: Link */
  $handler->display->display_options['fields']['view_order']['id'] = 'view_order';
  $handler->display->display_options['fields']['view_order']['table'] = 'commerce_order';
  $handler->display->display_options['fields']['view_order']['field'] = 'view_order';
  $handler->display->display_options['fields']['view_order']['relationship'] = 'did';
  $handler->display->display_options['fields']['view_order']['label'] = 'Actions';
  $handler->display->display_options['fields']['view_order']['text'] = 'View order';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'Payments';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = 'admin/commerce/orders/[order_id]/payment';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['relationship'] = 'sid_2';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'raw';
  $handler->display->display_options['arguments']['nid']['default_argument_options']['index'] = '4';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['path'] = 'admin/reports/salesforce/donations/%';
  $views[$view->name] = $view;

  // End sbv_donations.

  /**
   * View sbv_page_wrappers
   */
  $view = new view();
  $view->name = 'sbv_page_wrappers';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Springboard Page Wrappers';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE;
  /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Page Wrappers';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'edit any page_wrapper content';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'status' => 'status',
    'created' => 'created',
    'clone_node' => 'edit_node',
    'delete_node' => 'edit_node',
    'edit_node' => 'edit_node',
    'view_node' => 'edit_node',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'clone_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'delete_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_node' => array(
      'align' => '',
      'separator' => ' | ',
      'empty_column' => 0,
    ),
    'view_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<a href="/node/add/page-wrapper" class="button">Create Page Wrapper</a>';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Wrapper Name';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Published */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'node';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'Status';
  $handler->display->display_options['fields']['status']['type'] = 'published-notpublished';
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Date Created';
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'm/d/Y';
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['label'] = '';
  $handler->display->display_options['fields']['view_node']['element_label_colon'] = FALSE;
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Action';
  /* Field: Content: Clone link */
  $handler->display->display_options['fields']['clone_node']['id'] = 'clone_node';
  $handler->display->display_options['fields']['clone_node']['table'] = 'node';
  $handler->display->display_options['fields']['clone_node']['field'] = 'clone_node';
  $handler->display->display_options['fields']['clone_node']['label'] = '';
  $handler->display->display_options['fields']['clone_node']['element_label_colon'] = FALSE;
  /* Field: Content: Delete link */
  $handler->display->display_options['fields']['delete_node']['id'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['delete_node']['field'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['label'] = '';
  $handler->display->display_options['fields']['delete_node']['element_label_colon'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'page_wrapper' => 'page_wrapper',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['header'] = FALSE;
  $handler->display->display_options['path'] = 'admin/springboard/asset-library/page-wrappers';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '6';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '5';
  $handler->display->display_options['defaults']['footer'] = FALSE;
  /* Footer: Global: Text area */
  $handler->display->display_options['footer']['area']['id'] = 'area';
  $handler->display->display_options['footer']['area']['table'] = 'views';
  $handler->display->display_options['footer']['area']['field'] = 'area';
  $handler->display->display_options['footer']['area']['content'] = '<a href="admin/springboard/asset-library/page-wrappers" class="button">View All Page Wrappers</a>';
  $handler->display->display_options['footer']['area']['format'] = 'filtered_html';
  $views[$view -> name] = $view;

  /**
   * sbv_email_templates
   */
  $view = new view();
  $view->name = 'sbv_email_templates';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Springboard Email Templates';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Email Templates';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'edit any email_wrapper content';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'status' => 'status',
    'created' => 'created',
    'clone_node' => 'edit_node',
    'delete_node' => 'edit_node',
    'edit_node' => 'edit_node',
    'view_node' => 'edit_node',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'clone_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'delete_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_node' => array(
      'align' => '',
      'separator' => ' | ',
      'empty_column' => 0,
    ),
    'view_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<a href="/node/add/email-wrapper" class="button">Create Email Template</a>';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Template Name';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Published */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'node';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'Status';
  $handler->display->display_options['fields']['status']['type'] = 'published-notpublished';
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Date Created';
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'm/d/Y';
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['label'] = '';
  $handler->display->display_options['fields']['view_node']['element_label_colon'] = FALSE;
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Action';
  /* Field: Content: Clone link */
  $handler->display->display_options['fields']['clone_node']['id'] = 'clone_node';
  $handler->display->display_options['fields']['clone_node']['table'] = 'node';
  $handler->display->display_options['fields']['clone_node']['field'] = 'clone_node';
  $handler->display->display_options['fields']['clone_node']['label'] = '';
  $handler->display->display_options['fields']['clone_node']['element_label_colon'] = FALSE;
  /* Field: Content: Delete link */
  $handler->display->display_options['fields']['delete_node']['id'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['delete_node']['field'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['label'] = '';
  $handler->display->display_options['fields']['delete_node']['element_label_colon'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'email_wrapper' => 'email_wrapper',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['header'] = FALSE;
  $handler->display->display_options['path'] = 'admin/springboard/asset-library/email-templates';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '6';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '5';
  $handler->display->display_options['defaults']['footer'] = FALSE;
  /* Footer: Global: Text area */
  $handler->display->display_options['footer']['area']['id'] = 'area';
  $handler->display->display_options['footer']['area']['table'] = 'views';
  $handler->display->display_options['footer']['area']['field'] = 'area';
  $handler->display->display_options['footer']['area']['content'] = '<a href="admin/springboard/asset-library/email-templates" class="button">View All Email Templates</a>';
  $handler->display->display_options['footer']['area']['format'] = 'filtered_html';
  $views[$view -> name] = $view;
  
  /**
   * View sbv_dblog
   */

  $view = new view();
  $view -> name = 'sbv_dblog';
  $view -> description = '';
  $view -> tag = 'default';
  $view -> base_table = 'watchdog';
  $view -> human_name = 'Recent log messages extended';
  $view -> core = 7;
  $view -> api_version = '3.0';
  $view -> disabled = FALSE;
  /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view -> new_display('default', 'Master', 'default');
  $handler -> display -> display_options['title'] = 'Springboard log messages';
  $handler -> display -> display_options['use_more'] = TRUE;
  $handler -> display -> display_options['use_more_always'] = FALSE;
  $handler -> display -> display_options['access']['type'] = 'perm';
  $handler -> display -> display_options['access']['perm'] = 'access site reports';
  $handler -> display -> display_options['cache']['type'] = 'none';
  $handler -> display -> display_options['query']['type'] = 'views_query';
  $handler -> display -> display_options['exposed_form']['type'] = 'basic';
  $handler -> display -> display_options['pager']['type'] = 'full';
  $handler -> display -> display_options['pager']['options']['items_per_page'] = '20';
  $handler -> display -> display_options['pager']['options']['offset'] = '0';
  $handler -> display -> display_options['pager']['options']['id'] = '0';
  $handler -> display -> display_options['pager']['options']['quantity'] = '9';
  $handler -> display -> display_options['style_plugin'] = 'watchdog_table';
  $handler -> display -> display_options['style_options']['columns'] = array(
    'severity' => 'severity',
    'timestamp' => 'timestamp',
    'type' => 'type',
    'message' => 'message',
  );
  $handler -> display -> display_options['style_options']['default'] = '-1';
  $handler -> display -> display_options['style_options']['info'] = array(
    'severity' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'timestamp' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'type' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'message' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler -> display -> display_options['style_options']['watchdog_table_type'] = 1;
  $handler -> display -> display_options['style_options']['watchdog_table_severity'] = 1;
  /* Relationship: Watchdog: User */
  $handler -> display -> display_options['relationships']['uid']['id'] = 'uid';
  $handler -> display -> display_options['relationships']['uid']['table'] = 'watchdog';
  $handler -> display -> display_options['relationships']['uid']['field'] = 'uid';
  /* Field: Watchdog: Severity */
  $handler -> display -> display_options['fields']['severity']['id'] = 'severity';
  $handler -> display -> display_options['fields']['severity']['table'] = 'watchdog';
  $handler -> display -> display_options['fields']['severity']['field'] = 'severity';
  $handler -> display -> display_options['fields']['severity']['watchdog_severity_icon'] = 0;
  /* Field: Watchdog: Type */
  $handler -> display -> display_options['fields']['type']['id'] = 'type';
  $handler -> display -> display_options['fields']['type']['table'] = 'watchdog';
  $handler -> display -> display_options['fields']['type']['field'] = 'type';
  /* Field: Watchdog: Message */
  $handler -> display -> display_options['fields']['message']['id'] = 'message';
  $handler -> display -> display_options['fields']['message']['table'] = 'watchdog';
  $handler -> display -> display_options['fields']['message']['field'] = 'message';
  $handler -> display -> display_options['fields']['message']['watchdog_message_format'] = 1;
  $handler -> display -> display_options['fields']['message']['watchdog_message_link'] = 0;
  /* Field: Watchdog: Timestamp */
  $handler -> display -> display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler -> display -> display_options['fields']['timestamp']['table'] = 'watchdog';
  $handler -> display -> display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler -> display -> display_options['fields']['timestamp']['date_format'] = 'long';
  /* Sort criterion: Watchdog: Timestamp */
  $handler -> display -> display_options['sorts']['timestamp']['id'] = 'timestamp';
  $handler -> display -> display_options['sorts']['timestamp']['table'] = 'watchdog';
  $handler -> display -> display_options['sorts']['timestamp']['field'] = 'timestamp';
  $handler -> display -> display_options['sorts']['timestamp']['order'] = 'DESC';
  /* Filter criterion: Watchdog: Type */
  $handler -> display -> display_options['filters']['type']['id'] = 'type';
  $handler -> display -> display_options['filters']['type']['table'] = 'watchdog';
  $handler -> display -> display_options['filters']['type']['field'] = 'type';
  $handler -> display -> display_options['filters']['type']['value'] = array(
    'fundraiser_cron' => 'fundraiser_cron',
    'fundraiser_sustainers' => 'fundraiser_sustainers',
    'springboard_config' => 'springboard_config',
  );
  $handler -> display -> display_options['filters']['type']['group'] = 1;
  $handler -> display -> display_options['filters']['type']['expose']['operator_id'] = 'type_op';
  $handler -> display -> display_options['filters']['type']['expose']['label'] = 'Type';
  $handler -> display -> display_options['filters']['type']['expose']['operator'] = 'type_op';
  $handler -> display -> display_options['filters']['type']['expose']['identifier'] = 'type';
  $handler -> display -> display_options['filters']['type']['expose']['multiple'] = TRUE;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/springboard/reports/dblog';

  /* Display: Springboard Dashboard Log */
  $handler = $view -> new_display('block', 'Springboard Dashboard Log', 'block_1');
  $handler -> display -> display_options['defaults']['use_more'] = FALSE;
  $handler -> display -> display_options['use_more'] = TRUE;
  $handler -> display -> display_options['defaults']['use_more_always'] = FALSE;
  $handler -> display -> display_options['defaults']['use_more_always'] = FALSE;
  $handler -> display -> display_options['use_more_always'] = FALSE;
  $handler -> display -> display_options['defaults']['use_more_text'] = FALSE;
  $handler -> display -> display_options['use_more_text'] = 'More Log Entries';
  $handler -> display -> display_options['defaults']['pager'] = FALSE;
  $handler -> display -> display_options['pager']['type'] = 'some';
  $handler -> display -> display_options['pager']['options']['items_per_page'] = '5';
  $handler -> display -> display_options['pager']['options']['offset'] = '0';
  $handler -> display -> display_options['defaults']['style_plugin'] = FALSE;
  $handler -> display -> display_options['style_plugin'] = 'default';
  $handler -> display -> display_options['style_options']['grouping'] = array(0 => array(
      'field' => 'severity',
      'rendered' => 1,
      'rendered_strip' => 0,
    ), );
  $handler -> display -> display_options['defaults']['style_options'] = FALSE;
  $handler -> display -> display_options['defaults']['row_plugin'] = FALSE;
  $handler -> display -> display_options['row_plugin'] = 'fields';
  $handler -> display -> display_options['defaults']['row_options'] = FALSE;
  $handler -> display -> display_options['defaults']['fields'] = FALSE;
  /* Field: Watchdog: Severity */
  $handler -> display -> display_options['fields']['severity']['id'] = 'severity';
  $handler -> display -> display_options['fields']['severity']['table'] = 'watchdog';
  $handler -> display -> display_options['fields']['severity']['field'] = 'severity';
  $handler -> display -> display_options['fields']['severity']['label'] = '';
  $handler -> display -> display_options['fields']['severity']['exclude'] = TRUE;
  $handler -> display -> display_options['fields']['severity']['element_type'] = '0';
  $handler -> display -> display_options['fields']['severity']['element_label_type'] = '0';
  $handler -> display -> display_options['fields']['severity']['element_label_colon'] = FALSE;
  $handler -> display -> display_options['fields']['severity']['element_wrapper_type'] = '0';
  $handler -> display -> display_options['fields']['severity']['watchdog_severity_icon'] = 0;
  /* Field: Watchdog: Timestamp */
  $handler -> display -> display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler -> display -> display_options['fields']['timestamp']['table'] = 'watchdog';
  $handler -> display -> display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler -> display -> display_options['fields']['timestamp']['label'] = '';
  $handler -> display -> display_options['fields']['timestamp']['exclude'] = TRUE;
  $handler -> display -> display_options['fields']['timestamp']['element_type'] = '0';
  $handler -> display -> display_options['fields']['timestamp']['element_label_type'] = '0';
  $handler -> display -> display_options['fields']['timestamp']['element_label_colon'] = FALSE;
  $handler -> display -> display_options['fields']['timestamp']['element_wrapper_type'] = '0';
  $handler -> display -> display_options['fields']['timestamp']['date_format'] = 'time ago';
  /* Field: Watchdog: Type */
  $handler -> display -> display_options['fields']['type']['id'] = 'type';
  $handler -> display -> display_options['fields']['type']['table'] = 'watchdog';
  $handler -> display -> display_options['fields']['type']['field'] = 'type';
  $handler -> display -> display_options['fields']['type']['label'] = '';
  $handler -> display -> display_options['fields']['type']['exclude'] = TRUE;
  $handler -> display -> display_options['fields']['type']['element_type'] = '0';
  $handler -> display -> display_options['fields']['type']['element_label_type'] = '0';
  $handler -> display -> display_options['fields']['type']['element_label_colon'] = FALSE;
  $handler -> display -> display_options['fields']['type']['element_wrapper_type'] = '0';
  /* Field: Watchdog: Message */
  $handler -> display -> display_options['fields']['message']['id'] = 'message';
  $handler -> display -> display_options['fields']['message']['table'] = 'watchdog';
  $handler -> display -> display_options['fields']['message']['field'] = 'message';
  $handler -> display -> display_options['fields']['message']['label'] = '';
  $handler -> display -> display_options['fields']['message']['alter']['alter_text'] = TRUE;
  $handler -> display -> display_options['fields']['message']['alter']['text'] = '[type]: [message] <em>[timestamp]</em>';
  $handler -> display -> display_options['fields']['message']['alter']['max_length'] = '240';
  $handler -> display -> display_options['fields']['message']['element_type'] = '0';
  $handler -> display -> display_options['fields']['message']['element_label_type'] = '0';
  $handler -> display -> display_options['fields']['message']['element_label_colon'] = FALSE;
  $handler -> display -> display_options['fields']['message']['element_wrapper_type'] = '0';
  $handler -> display -> display_options['fields']['message']['watchdog_message_format'] = 0;
  $handler -> display -> display_options['fields']['message']['watchdog_message_link'] = 1;
  $handler -> display -> display_options['defaults']['filter_groups'] = FALSE;
  $handler -> display -> display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Watchdog: Type */
  $handler -> display -> display_options['filters']['type']['id'] = 'type';
  $handler -> display -> display_options['filters']['type']['table'] = 'watchdog';
  $handler -> display -> display_options['filters']['type']['field'] = 'type';
  $handler -> display -> display_options['filters']['type']['value'] = array(
    'fundraiser_cron' => 'fundraiser_cron',
    'fundraiser_sustainers' => 'fundraiser_sustainers',
    'springboard_config' => 'springboard_config',
    'capwiz_connect' => 'capwiz_connect',
    'commerce_psi' => 'commerce_psi',
    'commerce_litle' => 'commerce_litle',
    'dynamic gift strings' => 'dynamic gift strings',
    'fundraiser' => 'fundraiser',
    'fundraiser_commerce' => 'fundraiser_commerce',
    'fundraiser_webform' => 'fundraiser_webform',
    'fundraiser_comment' => 'fundraiser_comment',
    'Market Source' => 'Market Source',
    'salesforce' => 'salesforce',
    'Salesforce Pull' => 'Salesforce Pull',
    'salesforce_push' => 'salesforce_push',
    'salesforce_soap' => 'salesforce_soap',
    'salesforce_sync' => 'salesforce_sync',
    'sb_social' => 'sb_social',
    'Secure Prepopulate' => 'Secure Prepopulate',
    'webform_dupe_cop' => 'webform_dupe_cop',
    'webform_goals' => 'webform_goals',
    'webform_user' => 'webform_user',
  );
  $handler -> display -> display_options['filters']['type']['group'] = 1;
  $handler -> display -> display_options['filters']['type']['expose']['operator_id'] = 'type_op';
  $handler -> display -> display_options['filters']['type']['expose']['label'] = 'Type';
  $handler -> display -> display_options['filters']['type']['expose']['operator'] = 'type_op';
  $handler -> display -> display_options['filters']['type']['expose']['identifier'] = 'type';
  $handler -> display -> display_options['filters']['type']['expose']['multiple'] = TRUE;

  $views[$view -> name] = $view;

  $view = new view();
  $view -> name = 'sbv_soap_errors';
  $view -> description = 'Salesforce SOAP Errors';
  $view -> tag = 'default';
  $view -> base_table = 'salesforce_log_item';
  $view -> human_name = 'salesforce_soap_errors';
  $view -> core = 7;
  $view -> api_version = '3.0';
  $view -> disabled = FALSE;
  /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view -> new_display('default', 'Master', 'default');
  $handler -> display -> display_options['title'] = 'Errors for Unsynched Content';
  $handler -> display -> display_options['use_more_always'] = FALSE;
  $handler -> display -> display_options['access']['type'] = 'perm';
  $handler -> display -> display_options['access']['perm'] = 'view salesforce batch logs';
  $handler -> display -> display_options['cache']['type'] = 'none';
  $handler -> display -> display_options['query']['type'] = 'views_query';
  $handler -> display -> display_options['exposed_form']['type'] = 'basic';
  $handler -> display -> display_options['pager']['type'] = 'full';
  $handler -> display -> display_options['pager']['options']['items_per_page'] = '10';
  $handler -> display -> display_options['style_plugin'] = 'table';
  $handler -> display -> display_options['style_options']['columns'] = array(
    'drupal_id' => 'drupal_id',
    'error_code' => 'error_code',
    'object_type' => 'object_type',
    'message' => 'message',
  );
  $handler -> display -> display_options['style_options']['default'] = '-1';
  $handler -> display -> display_options['style_options']['info'] = array(
    'drupal_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'error_code' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'object_type' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'message' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: Salesforce item log: Drupal ID */
  $handler -> display -> display_options['fields']['drupal_id']['id'] = 'drupal_id';
  $handler -> display -> display_options['fields']['drupal_id']['table'] = 'salesforce_log_item';
  $handler -> display -> display_options['fields']['drupal_id']['field'] = 'drupal_id';
  /* Field: Salesforce item log: Object type */
  $handler -> display -> display_options['fields']['object_type']['id'] = 'object_type';
  $handler -> display -> display_options['fields']['object_type']['table'] = 'salesforce_log_item';
  $handler -> display -> display_options['fields']['object_type']['field'] = 'object_type';
  /* Field: Salesforce item log: Message */
  $handler -> display -> display_options['fields']['message']['id'] = 'message';
  $handler -> display -> display_options['fields']['message']['table'] = 'salesforce_log_item';
  $handler -> display -> display_options['fields']['message']['field'] = 'message';
  $handler -> display -> display_options['fields']['message']['label'] = 'Explanation';
  /* Sort criterion: Salesforce item log: Log Item ID */
  $handler -> display -> display_options['sorts']['lid']['id'] = 'lid';
  $handler -> display -> display_options['sorts']['lid']['table'] = 'salesforce_log_item';
  $handler -> display -> display_options['sorts']['lid']['field'] = 'lid';
  $handler -> display -> display_options['sorts']['lid']['order'] = 'DESC';
  /* Filter criterion: Salesforce item log: Error code */
  $handler -> display -> display_options['filters']['error_code']['id'] = 'error_code';
  $handler -> display -> display_options['filters']['error_code']['table'] = 'salesforce_log_item';
  $handler -> display -> display_options['filters']['error_code']['field'] = 'error_code';
  $handler -> display -> display_options['filters']['error_code']['value'] = 'Client';
  /* Filter criterion: Salesforce item log: Message */
  $handler -> display -> display_options['filters']['message']['id'] = 'message';
  $handler -> display -> display_options['filters']['message']['table'] = 'salesforce_log_item';
  $handler -> display -> display_options['filters']['message']['field'] = 'message';
  $handler -> display -> display_options['filters']['message']['operator'] = 'contains';
  $handler -> display -> display_options['filters']['message']['value'] = 'SOAP-ERROR';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/springboard/reports/salesforce-soap-errors';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Unsynched Errors';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Unsynched Errors Block */
  $handler = $view -> new_display('block', 'Unsynched Errors Block', 'block');
  $handler -> display -> display_options['defaults']['title'] = FALSE;
  $handler -> display -> display_options['title'] = 'Errors for Unsynched Content';
  $handler -> display -> display_options['defaults']['use_more'] = FALSE;
  $handler -> display -> display_options['use_more'] = TRUE;
  $handler -> display -> display_options['defaults']['use_more_always'] = FALSE;
  $handler -> display -> display_options['use_more_always'] = FALSE;
  $handler -> display -> display_options['defaults']['use_more_text'] = FALSE;
  $handler -> display -> display_options['use_more_text'] = 'See the full Error Message Guide';
  $handler -> display -> display_options['defaults']['pager'] = FALSE;
  $handler -> display -> display_options['pager']['type'] = 'some';
  $handler -> display -> display_options['pager']['options']['items_per_page'] = '3';
  $handler -> display -> display_options['pager']['options']['offset'] = '0';
  $handler -> display -> display_options['block_description'] = 'Unsynched Errors';
  $views[$view -> name] = $view;

  /**
   * View sbv_contacts
   */
  $view = new view();
  $view->name = 'sbv_contacts';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'users';
  $view->human_name = 'sbv_contacts';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Springboard Contacts';
  $handler->display->display_options['css_class'] = 'donor-table-view sbadmin-table-min sbadmin-table-min-x views-data-table';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access springboard dashboard';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['query']['options']['pure_distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'uid' => 'uid',
    'sbp_first_name' => 'sbp_first_name',
    'sbp_last_name' => 'sbp_last_name',
    'mail' => 'mail',
    'sbp_address' => 'sbp_address',
    'sbp_address_line_2' => 'sbp_address',
    'sbp_city' => 'sbp_city',
    'sbp_state' => 'sbp_state',
    'sbp_zip' => 'sbp_zip',
    'sbp_country' => 'sbp_country',
    'created' => 'created',
    'edit_node' => 'edit_node',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'uid' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'sbp_first_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'sbp_last_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'mail' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'sbp_address' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'sbp_address_line_2' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'sbp_city' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'sbp_state' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'sbp_zip' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'sbp_country' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: User: Uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'users';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  /* Field: User: First name */
  $handler->display->display_options['fields']['sbp_first_name']['id'] = 'sbp_first_name';
  $handler->display->display_options['fields']['sbp_first_name']['table'] = 'field_data_sbp_first_name';
  $handler->display->display_options['fields']['sbp_first_name']['field'] = 'sbp_first_name';
  /* Field: User: Last name */
  $handler->display->display_options['fields']['sbp_last_name']['id'] = 'sbp_last_name';
  $handler->display->display_options['fields']['sbp_last_name']['table'] = 'field_data_sbp_last_name';
  $handler->display->display_options['fields']['sbp_last_name']['field'] = 'sbp_last_name';
  /* Field: User: E-mail */
  $handler->display->display_options['fields']['mail']['id'] = 'mail';
  $handler->display->display_options['fields']['mail']['table'] = 'users';
  $handler->display->display_options['fields']['mail']['field'] = 'mail';
  $handler->display->display_options['fields']['mail']['link_to_user'] = 'user';
  /* Field: User: Address */
  $handler->display->display_options['fields']['sbp_address']['id'] = 'sbp_address';
  $handler->display->display_options['fields']['sbp_address']['table'] = 'field_data_sbp_address';
  $handler->display->display_options['fields']['sbp_address']['field'] = 'sbp_address';
  /* Field: User: Address Line 2 */
  $handler->display->display_options['fields']['sbp_address_line_2']['id'] = 'sbp_address_line_2';
  $handler->display->display_options['fields']['sbp_address_line_2']['table'] = 'field_data_sbp_address_line_2';
  $handler->display->display_options['fields']['sbp_address_line_2']['field'] = 'sbp_address_line_2';
  /* Field: User: City */
  $handler->display->display_options['fields']['sbp_city']['id'] = 'sbp_city';
  $handler->display->display_options['fields']['sbp_city']['table'] = 'field_data_sbp_city';
  $handler->display->display_options['fields']['sbp_city']['field'] = 'sbp_city';
  /* Field: User: State/Province */
  $handler->display->display_options['fields']['sbp_state']['id'] = 'sbp_state';
  $handler->display->display_options['fields']['sbp_state']['table'] = 'field_data_sbp_state';
  $handler->display->display_options['fields']['sbp_state']['field'] = 'sbp_state';
  $handler->display->display_options['fields']['sbp_state']['label'] = 'State';
  /* Field: User: Postal Code */
  $handler->display->display_options['fields']['sbp_zip']['id'] = 'sbp_zip';
  $handler->display->display_options['fields']['sbp_zip']['table'] = 'field_data_sbp_zip';
  $handler->display->display_options['fields']['sbp_zip']['field'] = 'sbp_zip';
  $handler->display->display_options['fields']['sbp_zip']['label'] = 'Zip';
  /* Field: User: Country */
  $handler->display->display_options['fields']['sbp_country']['id'] = 'sbp_country';
  $handler->display->display_options['fields']['sbp_country']['table'] = 'field_data_sbp_country';
  $handler->display->display_options['fields']['sbp_country']['field'] = 'sbp_country';
  /* Field: User: Created date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'users';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Created';
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'm/j/y';
  /* Field: User: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'users';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Action';
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Global: Combine fields filter */
  $handler->display->display_options['filters']['combine']['id'] = 'combine';
  $handler->display->display_options['filters']['combine']['table'] = 'views';
  $handler->display->display_options['filters']['combine']['field'] = 'combine';
  $handler->display->display_options['filters']['combine']['operator'] = 'contains';
  $handler->display->display_options['filters']['combine']['exposed'] = TRUE;
  $handler->display->display_options['filters']['combine']['expose']['operator_id'] = 'combine_op';
  $handler->display->display_options['filters']['combine']['expose']['label'] = 'Search';
  $handler->display->display_options['filters']['combine']['expose']['operator'] = 'combine_op';
  $handler->display->display_options['filters']['combine']['expose']['identifier'] = 'combine';
  $handler->display->display_options['filters']['combine']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  $handler->display->display_options['filters']['combine']['fields'] = array(
    'sbp_first_name' => 'sbp_first_name',
    'sbp_last_name' => 'sbp_last_name',
    'mail' => 'mail',
  );
  /* Filter criterion: Date: Date (users) */
  $handler->display->display_options['filters']['date_filter']['id'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['table'] = 'users';
  $handler->display->display_options['filters']['date_filter']['field'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['operator'] = 'between';
  $handler->display->display_options['filters']['date_filter']['exposed'] = TRUE;
  $handler->display->display_options['filters']['date_filter']['expose']['operator_id'] = 'date_filter_op';
  $handler->display->display_options['filters']['date_filter']['expose']['operator'] = 'date_filter_op';
  $handler->display->display_options['filters']['date_filter']['expose']['identifier'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  $handler->display->display_options['filters']['date_filter']['form_type'] = 'date_popup';
  $handler->display->display_options['filters']['date_filter']['date_fields'] = array(
    'users.created' => 'users.created',
  );
  /* Filter criterion: User: Roles */
  $handler->display->display_options['filters']['rid']['id'] = 'rid';
  $handler->display->display_options['filters']['rid']['table'] = 'users_roles';
  $handler->display->display_options['filters']['rid']['field'] = 'rid';
  $handler->display->display_options['filters']['rid']['operator'] = 'not';
  $handler->display->display_options['filters']['rid']['value'] = array(
    3 => '3',
    4 => '4',
    5 => '5',
  );
  $handler->display->display_options['filters']['rid']['reduce_duplicates'] = TRUE;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/springboard/reports/contacts';

  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'views_data_export_csv';
  $handler->display->display_options['style_options']['attach_text'] = 'Download as .CSV';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['filename'] = 'donation-export-%timestamp-full.csv';
  $handler->display->display_options['style_options']['parent_sort'] = 1;
  $handler->display->display_options['style_options']['quote'] = 1;
  $handler->display->display_options['style_options']['trim'] = 0;
  $handler->display->display_options['style_options']['replace_newlines'] = 0;
  $handler->display->display_options['style_options']['header'] = 1;
  $handler->display->display_options['style_options']['keep_html'] = 0;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: User: Uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'users';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  /* Field: User: First name */
  $handler->display->display_options['fields']['sbp_first_name']['id'] = 'sbp_first_name';
  $handler->display->display_options['fields']['sbp_first_name']['table'] = 'field_data_sbp_first_name';
  $handler->display->display_options['fields']['sbp_first_name']['field'] = 'sbp_first_name';
  /* Field: User: Last name */
  $handler->display->display_options['fields']['sbp_last_name']['id'] = 'sbp_last_name';
  $handler->display->display_options['fields']['sbp_last_name']['table'] = 'field_data_sbp_last_name';
  $handler->display->display_options['fields']['sbp_last_name']['field'] = 'sbp_last_name';
  /* Field: User: E-mail */
  $handler->display->display_options['fields']['mail']['id'] = 'mail';
  $handler->display->display_options['fields']['mail']['table'] = 'users';
  $handler->display->display_options['fields']['mail']['field'] = 'mail';
  /* Field: User: Address */
  $handler->display->display_options['fields']['sbp_address']['id'] = 'sbp_address';
  $handler->display->display_options['fields']['sbp_address']['table'] = 'field_data_sbp_address';
  $handler->display->display_options['fields']['sbp_address']['field'] = 'sbp_address';
  /* Field: User: Address Line 2 */
  $handler->display->display_options['fields']['sbp_address_line_2']['id'] = 'sbp_address_line_2';
  $handler->display->display_options['fields']['sbp_address_line_2']['table'] = 'field_data_sbp_address_line_2';
  $handler->display->display_options['fields']['sbp_address_line_2']['field'] = 'sbp_address_line_2';
  /* Field: User: City */
  $handler->display->display_options['fields']['sbp_city']['id'] = 'sbp_city';
  $handler->display->display_options['fields']['sbp_city']['table'] = 'field_data_sbp_city';
  $handler->display->display_options['fields']['sbp_city']['field'] = 'sbp_city';
  /* Field: User: State/Province */
  $handler->display->display_options['fields']['sbp_state']['id'] = 'sbp_state';
  $handler->display->display_options['fields']['sbp_state']['table'] = 'field_data_sbp_state';
  $handler->display->display_options['fields']['sbp_state']['field'] = 'sbp_state';
  $handler->display->display_options['fields']['sbp_state']['label'] = 'State';
  /* Field: User: Postal Code */
  $handler->display->display_options['fields']['sbp_zip']['id'] = 'sbp_zip';
  $handler->display->display_options['fields']['sbp_zip']['table'] = 'field_data_sbp_zip';
  $handler->display->display_options['fields']['sbp_zip']['field'] = 'sbp_zip';
  $handler->display->display_options['fields']['sbp_zip']['label'] = 'Zip';
  /* Field: User: Country */
  $handler->display->display_options['fields']['sbp_country']['id'] = 'sbp_country';
  $handler->display->display_options['fields']['sbp_country']['table'] = 'field_data_sbp_country';
  $handler->display->display_options['fields']['sbp_country']['field'] = 'sbp_country';
  /* Field: User: Referrer */
  $handler->display->display_options['fields']['sbp_referrer']['id'] = 'sbp_referrer';
  $handler->display->display_options['fields']['sbp_referrer']['table'] = 'field_data_sbp_referrer';
  $handler->display->display_options['fields']['sbp_referrer']['field'] = 'sbp_referrer';
  /* Field: User: Initial Referrer */
  $handler->display->display_options['fields']['sbp_initial_referrer']['id'] = 'sbp_initial_referrer';
  $handler->display->display_options['fields']['sbp_initial_referrer']['table'] = 'field_data_sbp_initial_referrer';
  $handler->display->display_options['fields']['sbp_initial_referrer']['field'] = 'sbp_initial_referrer';
  /* Field: User: Market Source */
  $handler->display->display_options['fields']['sbp_ms']['id'] = 'sbp_ms';
  $handler->display->display_options['fields']['sbp_ms']['table'] = 'field_data_sbp_ms';
  $handler->display->display_options['fields']['sbp_ms']['field'] = 'sbp_ms';
  /* Field: User: Search Engine */
  $handler->display->display_options['fields']['sbp_search_engine']['id'] = 'sbp_search_engine';
  $handler->display->display_options['fields']['sbp_search_engine']['table'] = 'field_data_sbp_search_engine';
  $handler->display->display_options['fields']['sbp_search_engine']['field'] = 'sbp_search_engine';
  /* Field: User: Search String */
  $handler->display->display_options['fields']['sbp_search_string']['id'] = 'sbp_search_string';
  $handler->display->display_options['fields']['sbp_search_string']['table'] = 'field_data_sbp_search_string';
  $handler->display->display_options['fields']['sbp_search_string']['field'] = 'sbp_search_string';
  /* Field: User: Created date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'users';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Created';
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'm/j/y';
  $handler->display->display_options['path'] = 'admin/springboard/reports/contacts/export';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $handler->display->display_options['use_batch'] = 'batch';
  $handler->display->display_options['return_path'] = 'admin/springboard/reports/contacts';
  $handler->display->display_options['segment_size'] = '100';
  $views[$view -> name] = $view;

  /**
   * sbv_assets view.
   */
  $view = new view();
  $view->name = 'sbv_assets';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'sbv_assets';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access springboard dashboard';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'status' => 'status',
    'created' => 'created',
    'clone_node' => 'edit_node',
    'delete_node' => 'edit_node',
    'edit_node' => 'edit_node',
    'view_node' => 'edit_node',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'clone_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'delete_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_node' => array(
      'align' => '',
      'separator' => ' | ',
      'empty_column' => 0,
    ),
    'view_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'No %1s have been created yet. ';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  $handler->display->display_options['empty']['area']['tokenize'] = TRUE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Published */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'node';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'Status';
  $handler->display->display_options['fields']['status']['type'] = 'published-notpublished';
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Date Created';
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'm/d/Y';
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['label'] = '';
  $handler->display->display_options['fields']['view_node']['element_label_colon'] = FALSE;
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Action';
  /* Field: Content: Clone link */
  $handler->display->display_options['fields']['clone_node']['id'] = 'clone_node';
  $handler->display->display_options['fields']['clone_node']['table'] = 'node';
  $handler->display->display_options['fields']['clone_node']['field'] = 'clone_node';
  $handler->display->display_options['fields']['clone_node']['label'] = '';
  $handler->display->display_options['fields']['clone_node']['element_label_colon'] = FALSE;
  /* Field: Content: Delete link */
  $handler->display->display_options['fields']['delete_node']['id'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['delete_node']['field'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['label'] = '';
  $handler->display->display_options['fields']['delete_node']['element_label_colon'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Content: Type */
  $handler->display->display_options['arguments']['type']['id'] = 'type';
  $handler->display->display_options['arguments']['type']['table'] = 'node';
  $handler->display->display_options['arguments']['type']['field'] = 'type';
  $handler->display->display_options['arguments']['type']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['type']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['type']['title'] = '%1s';
  $handler->display->display_options['arguments']['type']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['type']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['type']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['type']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['type']['limit'] = '0';
  /* Filter criterion: Global: Combine fields filter */
  $handler->display->display_options['filters']['combine']['id'] = 'combine';
  $handler->display->display_options['filters']['combine']['table'] = 'views';
  $handler->display->display_options['filters']['combine']['field'] = 'combine';
  $handler->display->display_options['filters']['combine']['operator'] = 'contains';
  $handler->display->display_options['filters']['combine']['exposed'] = TRUE;
  $handler->display->display_options['filters']['combine']['expose']['operator_id'] = 'combine_op';
  $handler->display->display_options['filters']['combine']['expose']['label'] = 'Search';
  $handler->display->display_options['filters']['combine']['expose']['operator'] = 'combine_op';
  $handler->display->display_options['filters']['combine']['expose']['identifier'] = 'combine';
  $handler->display->display_options['filters']['combine']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  $handler->display->display_options['filters']['combine']['fields'] = array(
    'title' => 'title',
    'created' => 'created',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '6';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '5';
  $handler->display->display_options['defaults']['footer'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['path'] = 'admin/springboard/asset-library/%';
  $views[$view->name] = $view;

  /**
   * sbv_sf_batch_items
   */
  $view = new view();
  $view->name = 'sbv_sf_batch_items';
  $view->description = '';
  $view->tag = 'salesforce log';
  $view->base_table = 'salesforce_log_item';
  $view->human_name = 'sbv_sf_batch_items';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Item log';
  $handler->display->display_options['css_class'] = 'views-data-table';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view salesforce batch logs';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['query']['options']['pure_distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'lid' => 'item_id',
    'item_id' => 'item_id',
    'bid' => 'bid',
    'start' => 'start',
    'status' => 'status',
    'error_code' => 'error_code',
    'message' => 'message',
    'sobject' => 'sobject',
    'sfid' => 'sfid',
    'drupal_id' => 'drupal_id',
    'queue' => 'queue',
    'retries' => 'retries',
  );
  $handler->display->display_options['style_options']['default'] = 'bid';
  $handler->display->display_options['style_options']['info'] = array(
    'lid' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'item_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'bid' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'start' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'error_code' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'message' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'sobject' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'sfid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'drupal_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'queue' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'retries' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  /* Relationship: Salesforce item log: Batch */
  $handler->display->display_options['relationships']['bid']['id'] = 'bid';
  $handler->display->display_options['relationships']['bid']['table'] = 'salesforce_log_item';
  $handler->display->display_options['relationships']['bid']['field'] = 'bid';
  /* Relationship: Salesforce item log: Queue item */
  $handler->display->display_options['relationships']['item_id']['id'] = 'item_id';
  $handler->display->display_options['relationships']['item_id']['table'] = 'salesforce_log_item';
  $handler->display->display_options['relationships']['item_id']['field'] = 'item_id';
  /* Field: Salesforce item log: Item Queue ID */
  $handler->display->display_options['fields']['item_id']['id'] = 'item_id';
  $handler->display->display_options['fields']['item_id']['table'] = 'salesforce_log_item';
  $handler->display->display_options['fields']['item_id']['field'] = 'item_id';
  $handler->display->display_options['fields']['item_id']['label'] = 'Item #';
  $handler->display->display_options['fields']['item_id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['item_id']['separator'] = '';
  /* Field: Salesforce item log: Item Batch ID */
  $handler->display->display_options['fields']['bid']['id'] = 'bid';
  $handler->display->display_options['fields']['bid']['table'] = 'salesforce_log_item';
  $handler->display->display_options['fields']['bid']['field'] = 'bid';
  $handler->display->display_options['fields']['bid']['label'] = 'Batch #';
  $handler->display->display_options['fields']['bid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['bid']['separator'] = '';
  /* Field: Salesforce batch log: Start Timestamp */
  $handler->display->display_options['fields']['start']['id'] = 'start';
  $handler->display->display_options['fields']['start']['table'] = 'salesforce_log_batch';
  $handler->display->display_options['fields']['start']['field'] = 'start';
  $handler->display->display_options['fields']['start']['relationship'] = 'bid';
  $handler->display->display_options['fields']['start']['label'] = 'Date';
  $handler->display->display_options['fields']['start']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['start']['date_format'] = 'short';
  /* Field: Salesforce item log: Status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'salesforce_log_item';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['element_label_colon'] = FALSE;
  /* Field: Salesforce item log: Error code */
  $handler->display->display_options['fields']['error_code']['id'] = 'error_code';
  $handler->display->display_options['fields']['error_code']['table'] = 'salesforce_log_item';
  $handler->display->display_options['fields']['error_code']['field'] = 'error_code';
  $handler->display->display_options['fields']['error_code']['element_label_colon'] = FALSE;
  /* Field: Salesforce item log: Message */
  $handler->display->display_options['fields']['message']['id'] = 'message';
  $handler->display->display_options['fields']['message']['table'] = 'salesforce_log_item';
  $handler->display->display_options['fields']['message']['field'] = 'message';
  $handler->display->display_options['fields']['message']['label'] = 'Error Message';
  $handler->display->display_options['fields']['message']['element_class'] = 'expander';
  $handler->display->display_options['fields']['message']['element_label_colon'] = FALSE;
  /* Field: Salesforce item log: Salesforce sObject */
  $handler->display->display_options['fields']['sobject']['id'] = 'sobject';
  $handler->display->display_options['fields']['sobject']['table'] = 'salesforce_log_item';
  $handler->display->display_options['fields']['sobject']['field'] = 'sobject';
  $handler->display->display_options['fields']['sobject']['label'] = 'Data';
  $handler->display->display_options['fields']['sobject']['element_class'] = 'expander';
  $handler->display->display_options['fields']['sobject']['element_label_colon'] = FALSE;
  /* Field: Salesforce item log: Salesforce id */
  $handler->display->display_options['fields']['sfid']['id'] = 'sfid';
  $handler->display->display_options['fields']['sfid']['table'] = 'salesforce_log_item';
  $handler->display->display_options['fields']['sfid']['field'] = 'sfid';
  $handler->display->display_options['fields']['sfid']['label'] = 'SF Id';
  $handler->display->display_options['fields']['sfid']['element_label_colon'] = FALSE;
  /* Field: Salesforce item log: Drupal ID */
  $handler->display->display_options['fields']['drupal_id']['id'] = 'drupal_id';
  $handler->display->display_options['fields']['drupal_id']['table'] = 'salesforce_log_item';
  $handler->display->display_options['fields']['drupal_id']['field'] = 'drupal_id';
  $handler->display->display_options['fields']['drupal_id']['label'] = 'SB Id';
  $handler->display->display_options['fields']['drupal_id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['drupal_id']['separator'] = '';
  /* Field: Salesforce queue: Queue */
  $handler->display->display_options['fields']['queue']['id'] = 'queue';
  $handler->display->display_options['fields']['queue']['table'] = 'salesforce_queue';
  $handler->display->display_options['fields']['queue']['field'] = 'queue';
  $handler->display->display_options['fields']['queue']['relationship'] = 'item_id';
  $handler->display->display_options['fields']['queue']['empty'] = 'Removed from queue';
  $handler->display->display_options['fields']['queue']['empty_zero'] = TRUE;
  /* Field: Salesforce queue: Retries */
  $handler->display->display_options['fields']['retries']['id'] = 'retries';
  $handler->display->display_options['fields']['retries']['table'] = 'salesforce_queue';
  $handler->display->display_options['fields']['retries']['field'] = 'retries';
  $handler->display->display_options['fields']['retries']['relationship'] = 'item_id';
  $handler->display->display_options['fields']['retries']['label'] = 'Attempts';
  $handler->display->display_options['fields']['retries']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['retries']['empty'] = 'N/A';
  $handler->display->display_options['fields']['retries']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['retries']['separator'] = '';
  /* Sort criterion: Salesforce batch log: Batch Item ID */
  $handler->display->display_options['sorts']['bid']['id'] = 'bid';
  $handler->display->display_options['sorts']['bid']['table'] = 'salesforce_log_batch';
  $handler->display->display_options['sorts']['bid']['field'] = 'bid';
  $handler->display->display_options['sorts']['bid']['relationship'] = 'bid';
  $handler->display->display_options['sorts']['bid']['order'] = 'DESC';
  /* Filter criterion: Salesforce item log: Item Batch ID */
  $handler->display->display_options['filters']['bid']['id'] = 'bid';
  $handler->display->display_options['filters']['bid']['table'] = 'salesforce_log_item';
  $handler->display->display_options['filters']['bid']['field'] = 'bid';
  $handler->display->display_options['filters']['bid']['relationship'] = 'bid';
  $handler->display->display_options['filters']['bid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['bid']['expose']['operator_id'] = 'bid_op';
  $handler->display->display_options['filters']['bid']['expose']['label'] = 'Batch #';
  $handler->display->display_options['filters']['bid']['expose']['operator'] = 'bid_op';
  $handler->display->display_options['filters']['bid']['expose']['identifier'] = 'bid';
  $handler->display->display_options['filters']['bid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  $handler->display->display_options['filters']['bid']['group_info']['label'] = 'Batch ID';
  $handler->display->display_options['filters']['bid']['group_info']['identifier'] = 'bid';
  $handler->display->display_options['filters']['bid']['group_info']['remember'] = FALSE;
  $handler->display->display_options['filters']['bid']['group_info']['group_items'] = array(
    1 => array(),
    2 => array(),
    3 => array(),
  );
  /* Filter criterion: Salesforce item log: Item Queue ID */
  $handler->display->display_options['filters']['item_id']['id'] = 'item_id';
  $handler->display->display_options['filters']['item_id']['table'] = 'salesforce_log_item';
  $handler->display->display_options['filters']['item_id']['field'] = 'item_id';
  $handler->display->display_options['filters']['item_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['item_id']['expose']['operator_id'] = 'item_id_op';
  $handler->display->display_options['filters']['item_id']['expose']['label'] = 'Item #';
  $handler->display->display_options['filters']['item_id']['expose']['operator'] = 'item_id_op';
  $handler->display->display_options['filters']['item_id']['expose']['identifier'] = 'item_id';
  $handler->display->display_options['filters']['item_id']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  /* Filter criterion: Salesforce item log: Drupal ID */
  $handler->display->display_options['filters']['drupal_id']['id'] = 'drupal_id';
  $handler->display->display_options['filters']['drupal_id']['table'] = 'salesforce_log_item';
  $handler->display->display_options['filters']['drupal_id']['field'] = 'drupal_id';
  $handler->display->display_options['filters']['drupal_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['drupal_id']['expose']['operator_id'] = 'drupal_id_op';
  $handler->display->display_options['filters']['drupal_id']['expose']['label'] = 'Springboard ID';
  $handler->display->display_options['filters']['drupal_id']['expose']['operator'] = 'drupal_id_op';
  $handler->display->display_options['filters']['drupal_id']['expose']['identifier'] = 'drupal_id';
  $handler->display->display_options['filters']['drupal_id']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  /* Filter criterion: Salesforce item log: Salesforce id */
  $handler->display->display_options['filters']['sfid']['id'] = 'sfid';
  $handler->display->display_options['filters']['sfid']['table'] = 'salesforce_log_item';
  $handler->display->display_options['filters']['sfid']['field'] = 'sfid';
  $handler->display->display_options['filters']['sfid']['operator'] = 'contains';
  $handler->display->display_options['filters']['sfid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['sfid']['expose']['operator_id'] = 'sfid_op';
  $handler->display->display_options['filters']['sfid']['expose']['label'] = 'Salesforce ID';
  $handler->display->display_options['filters']['sfid']['expose']['operator'] = 'sfid_op';
  $handler->display->display_options['filters']['sfid']['expose']['identifier'] = 'sfid';
  $handler->display->display_options['filters']['sfid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  $handler->display->display_options['filters']['sfid']['group_info']['label'] = 'Salesforce id';
  $handler->display->display_options['filters']['sfid']['group_info']['identifier'] = 'sfid';
  $handler->display->display_options['filters']['sfid']['group_info']['remember'] = FALSE;
  $handler->display->display_options['filters']['sfid']['group_info']['group_items'] = array(
    1 => array(),
    2 => array(),
    3 => array(),
  );
  /* Filter criterion: Salesforce item log: Error code */
  $handler->display->display_options['filters']['error_code']['id'] = 'error_code';
  $handler->display->display_options['filters']['error_code']['table'] = 'salesforce_log_item';
  $handler->display->display_options['filters']['error_code']['field'] = 'error_code';
  $handler->display->display_options['filters']['error_code']['operator'] = 'contains';
  $handler->display->display_options['filters']['error_code']['exposed'] = TRUE;
  $handler->display->display_options['filters']['error_code']['expose']['operator_id'] = 'error_code_op';
  $handler->display->display_options['filters']['error_code']['expose']['label'] = 'Error code';
  $handler->display->display_options['filters']['error_code']['expose']['operator'] = 'error_code_op';
  $handler->display->display_options['filters']['error_code']['expose']['identifier'] = 'error_code';
  $handler->display->display_options['filters']['error_code']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'admin/springboard/reports/integration-reports/item';
  $handler->display->display_options['menu']['title'] = 'Item log';
  $handler->display->display_options['menu']['description'] = 'Log of individual objects synced to Salesforce';
  $handler->display->display_options['menu']['weight'] = '1';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $views[$view->name] = $view;

  /**
   * sbv_sf_batches
   */
   $view = new view();
  $view->name = 'sbv_sf_batches';
  $view->description = '';
  $view->tag = 'salesforce log';
  $view->base_table = 'salesforce_log_batch';
  $view->human_name = 'sbv_sf_batches';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Batch log';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['css_class'] = 'views-data-table';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view salesforce batch logs';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'bid' => 'bid',
    'module' => 'module',
    'object_type' => 'object_type',
    'operation' => 'operation',
    'start' => 'start',
    'end' => 'end',
    'count' => 'count',
    'successes' => 'successes',
    'failures' => 'failures',
  );
  $handler->display->display_options['style_options']['default'] = 'bid';
  $handler->display->display_options['style_options']['info'] = array(
    'bid' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'module' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'object_type' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'operation' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'start' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'end' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'count' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'successes' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'failures' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  /* Field: Salesforce batch log: Batch Item ID */
  $handler->display->display_options['fields']['bid']['id'] = 'bid';
  $handler->display->display_options['fields']['bid']['table'] = 'salesforce_log_batch';
  $handler->display->display_options['fields']['bid']['field'] = 'bid';
  $handler->display->display_options['fields']['bid']['label'] = 'Batch #';
  $handler->display->display_options['fields']['bid']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['bid']['alter']['path'] = 'admin/springboard/reports/integration-reports/item?bid=[bid]';
  $handler->display->display_options['fields']['bid']['alter']['alt'] = 'View the items synced in this batch.';
  $handler->display->display_options['fields']['bid']['separator'] = '';
  /* Field: Salesforce batch log: Module */
  $handler->display->display_options['fields']['module']['id'] = 'module';
  $handler->display->display_options['fields']['module']['table'] = 'salesforce_log_batch';
  $handler->display->display_options['fields']['module']['field'] = 'module';
  $handler->display->display_options['fields']['module']['label'] = 'SB Module';
  $handler->display->display_options['fields']['module']['element_label_colon'] = FALSE;
  /* Field: Salesforce batch log: Object type */
  $handler->display->display_options['fields']['object_type']['id'] = 'object_type';
  $handler->display->display_options['fields']['object_type']['table'] = 'salesforce_log_batch';
  $handler->display->display_options['fields']['object_type']['field'] = 'object_type';
  $handler->display->display_options['fields']['object_type']['label'] = 'SB Object';
  $handler->display->display_options['fields']['object_type']['element_label_colon'] = FALSE;
  /* Field: Salesforce batch log: Operation */
  $handler->display->display_options['fields']['operation']['id'] = 'operation';
  $handler->display->display_options['fields']['operation']['table'] = 'salesforce_log_batch';
  $handler->display->display_options['fields']['operation']['field'] = 'operation';
  $handler->display->display_options['fields']['operation']['element_label_colon'] = FALSE;
  /* Field: Salesforce batch log: Start Timestamp */
  $handler->display->display_options['fields']['start']['id'] = 'start';
  $handler->display->display_options['fields']['start']['table'] = 'salesforce_log_batch';
  $handler->display->display_options['fields']['start']['field'] = 'start';
  $handler->display->display_options['fields']['start']['label'] = 'Start';
  $handler->display->display_options['fields']['start']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['start']['date_format'] = 'short';
  /* Field: Salesforce batch log: End Timestamp */
  $handler->display->display_options['fields']['end']['id'] = 'end';
  $handler->display->display_options['fields']['end']['table'] = 'salesforce_log_batch';
  $handler->display->display_options['fields']['end']['field'] = 'end';
  $handler->display->display_options['fields']['end']['label'] = 'End';
  $handler->display->display_options['fields']['end']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['end']['date_format'] = 'short';
  /* Field: Salesforce batch log: Count */
  $handler->display->display_options['fields']['count']['id'] = 'count';
  $handler->display->display_options['fields']['count']['table'] = 'salesforce_log_batch';
  $handler->display->display_options['fields']['count']['field'] = 'count';
  $handler->display->display_options['fields']['count']['label'] = 'Items';
  $handler->display->display_options['fields']['count']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['count']['separator'] = '';
  /* Field: Salesforce batch log: Successes */
  $handler->display->display_options['fields']['successes']['id'] = 'successes';
  $handler->display->display_options['fields']['successes']['table'] = 'salesforce_log_batch';
  $handler->display->display_options['fields']['successes']['field'] = 'successes';
  $handler->display->display_options['fields']['successes']['label'] = 'Synced';
  $handler->display->display_options['fields']['successes']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['successes']['separator'] = '';
  /* Field: Salesforce batch log: Failures */
  $handler->display->display_options['fields']['failures']['id'] = 'failures';
  $handler->display->display_options['fields']['failures']['table'] = 'salesforce_log_batch';
  $handler->display->display_options['fields']['failures']['field'] = 'failures';
  $handler->display->display_options['fields']['failures']['label'] = 'Failed';
  $handler->display->display_options['fields']['failures']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['failures']['separator'] = '';
  /* Sort criterion: Salesforce batch log: Batch Item ID */
  $handler->display->display_options['sorts']['bid']['id'] = 'bid';
  $handler->display->display_options['sorts']['bid']['table'] = 'salesforce_log_batch';
  $handler->display->display_options['sorts']['bid']['field'] = 'bid';
  $handler->display->display_options['sorts']['bid']['order'] = 'DESC';
  /* Filter criterion: Salesforce item log: Item Batch ID */
  $handler->display->display_options['filters']['bid']['id'] = 'bid';
  $handler->display->display_options['filters']['bid']['table'] = 'salesforce_log_item';
  $handler->display->display_options['filters']['bid']['field'] = 'bid';
  $handler->display->display_options['filters']['bid']['group'] = 1;
  $handler->display->display_options['filters']['bid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['bid']['expose']['operator_id'] = 'bid_op';
  $handler->display->display_options['filters']['bid']['expose']['label'] = 'Batch #';
  $handler->display->display_options['filters']['bid']['expose']['operator'] = 'bid_op';
  $handler->display->display_options['filters']['bid']['expose']['identifier'] = 'bid';
  $handler->display->display_options['filters']['bid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  /* Filter criterion: Salesforce batch log: Module */
  $handler->display->display_options['filters']['module']['id'] = 'module';
  $handler->display->display_options['filters']['module']['table'] = 'salesforce_log_batch';
  $handler->display->display_options['filters']['module']['field'] = 'module';
  $handler->display->display_options['filters']['module']['group'] = 1;
  $handler->display->display_options['filters']['module']['exposed'] = TRUE;
  $handler->display->display_options['filters']['module']['expose']['operator_id'] = 'module_op';
  $handler->display->display_options['filters']['module']['expose']['label'] = 'SB Module';
  $handler->display->display_options['filters']['module']['expose']['operator'] = 'module_op';
  $handler->display->display_options['filters']['module']['expose']['identifier'] = 'module';
  $handler->display->display_options['filters']['module']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  /* Filter criterion: Salesforce batch log: Object type */
  $handler->display->display_options['filters']['object_type']['id'] = 'object_type';
  $handler->display->display_options['filters']['object_type']['table'] = 'salesforce_log_batch';
  $handler->display->display_options['filters']['object_type']['field'] = 'object_type';
  $handler->display->display_options['filters']['object_type']['group'] = 1;
  $handler->display->display_options['filters']['object_type']['exposed'] = TRUE;
  $handler->display->display_options['filters']['object_type']['expose']['operator_id'] = 'object_type_op';
  $handler->display->display_options['filters']['object_type']['expose']['label'] = 'SB Object';
  $handler->display->display_options['filters']['object_type']['expose']['operator'] = 'object_type_op';
  $handler->display->display_options['filters']['object_type']['expose']['identifier'] = 'object_type';
  $handler->display->display_options['filters']['object_type']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  /* Filter criterion: Salesforce batch log: Operation */
  $handler->display->display_options['filters']['operation']['id'] = 'operation';
  $handler->display->display_options['filters']['operation']['table'] = 'salesforce_log_batch';
  $handler->display->display_options['filters']['operation']['field'] = 'operation';
  $handler->display->display_options['filters']['operation']['group'] = 1;
  $handler->display->display_options['filters']['operation']['exposed'] = TRUE;
  $handler->display->display_options['filters']['operation']['expose']['operator_id'] = 'operation_op';
  $handler->display->display_options['filters']['operation']['expose']['label'] = 'Operation';
  $handler->display->display_options['filters']['operation']['expose']['operator'] = 'operation_op';
  $handler->display->display_options['filters']['operation']['expose']['identifier'] = 'operation';
  $handler->display->display_options['filters']['operation']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  /* Filter criterion: Salesforce batch log: Failures */
  $handler->display->display_options['filters']['failures']['id'] = 'failures';
  $handler->display->display_options['filters']['failures']['table'] = 'salesforce_log_batch';
  $handler->display->display_options['filters']['failures']['field'] = 'failures';
  $handler->display->display_options['filters']['failures']['operator'] = '>=';
  $handler->display->display_options['filters']['failures']['group'] = 1;
  $handler->display->display_options['filters']['failures']['exposed'] = TRUE;
  $handler->display->display_options['filters']['failures']['expose']['operator_id'] = 'failures_op';
  $handler->display->display_options['filters']['failures']['expose']['label'] = 'Failed';
  $handler->display->display_options['filters']['failures']['expose']['operator'] = 'failures_op';
  $handler->display->display_options['filters']['failures']['expose']['identifier'] = 'failures';
  $handler->display->display_options['filters']['failures']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'admin/springboard/reports/integration-reports/batch';
  $handler->display->display_options['menu']['title'] = 'Batch log';
  $handler->display->display_options['menu']['description'] = 'Current and previous salesforce batches.';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $views[$view->name] = $view;

  /**
   * sbv_sf_queue
   */
  $view = new view();
  $view->name = 'sbv_sf_queue';
  $view->description = '';
  $view->tag = 'salesforce log';
  $view->base_table = 'salesforce_queue';
  $view->human_name = 'sbv_sf_queue';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Queue';
  $handler->display->display_options['css_class'] = 'views-data-table';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view salesforce batch logs';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'item_id' => 'item_id',
    'module' => 'module',
    'drupal_id' => 'drupal_id',
    'object_type' => 'object_type',
    'operation' => 'operation',
    'queue' => 'queue',
    'retries' => 'retries',
    'created' => 'created',
  );
  $handler->display->display_options['style_options']['default'] = 'item_id';
  $handler->display->display_options['style_options']['info'] = array(
    'item_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'module' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'drupal_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'object_type' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'operation' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'queue' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'retries' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  /* Field: Bulk operations: Salesforce queue */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'salesforce_queue';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_script_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_modify_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'show_all_tokens' => 1,
        'display_values' => array(
          '_all_' => '_all_',
        ),
      ),
    ),
    'action::views_bulk_operations_argument_selector_action' => array(
      'selected' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'url' => '',
      ),
    ),
    'action::salesforce_queue_salesforce_queue_item_requeue_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::salesforce_queue_salesforce_queue_item_refresh_item_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::system_send_email_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
  );
  /* Field: Salesforce queue: Queue ID */
  $handler->display->display_options['fields']['item_id']['id'] = 'item_id';
  $handler->display->display_options['fields']['item_id']['table'] = 'salesforce_queue';
  $handler->display->display_options['fields']['item_id']['field'] = 'item_id';
  $handler->display->display_options['fields']['item_id']['label'] = 'Item #';
  $handler->display->display_options['fields']['item_id']['separator'] = '';
  /* Field: Salesforce queue: Module */
  $handler->display->display_options['fields']['module']['id'] = 'module';
  $handler->display->display_options['fields']['module']['table'] = 'salesforce_queue';
  $handler->display->display_options['fields']['module']['field'] = 'module';
  $handler->display->display_options['fields']['module']['element_label_colon'] = FALSE;
  /* Field: Salesforce queue: Drupal ID */
  $handler->display->display_options['fields']['drupal_id']['id'] = 'drupal_id';
  $handler->display->display_options['fields']['drupal_id']['table'] = 'salesforce_queue';
  $handler->display->display_options['fields']['drupal_id']['field'] = 'drupal_id';
  $handler->display->display_options['fields']['drupal_id']['label'] = 'SB ID';
  $handler->display->display_options['fields']['drupal_id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['drupal_id']['separator'] = '';
  /* Field: Salesforce queue: Object type */
  $handler->display->display_options['fields']['object_type']['id'] = 'object_type';
  $handler->display->display_options['fields']['object_type']['table'] = 'salesforce_queue';
  $handler->display->display_options['fields']['object_type']['field'] = 'object_type';
  $handler->display->display_options['fields']['object_type']['element_label_colon'] = FALSE;
  /* Field: Salesforce queue: Operation */
  $handler->display->display_options['fields']['operation']['id'] = 'operation';
  $handler->display->display_options['fields']['operation']['table'] = 'salesforce_queue';
  $handler->display->display_options['fields']['operation']['field'] = 'operation';
  $handler->display->display_options['fields']['operation']['element_label_colon'] = FALSE;
  /* Field: Salesforce queue: Queue */
  $handler->display->display_options['fields']['queue']['id'] = 'queue';
  $handler->display->display_options['fields']['queue']['table'] = 'salesforce_queue';
  $handler->display->display_options['fields']['queue']['field'] = 'queue';
  $handler->display->display_options['fields']['queue']['element_label_colon'] = FALSE;
  /* Field: Salesforce queue: Retries */
  $handler->display->display_options['fields']['retries']['id'] = 'retries';
  $handler->display->display_options['fields']['retries']['table'] = 'salesforce_queue';
  $handler->display->display_options['fields']['retries']['field'] = 'retries';
  $handler->display->display_options['fields']['retries']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['retries']['separator'] = '';
  /* Field: Salesforce queue: Created Timestamp */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'salesforce_queue';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Created';
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'short';
  /* Sort criterion: Salesforce queue: Queue ID */
  $handler->display->display_options['sorts']['item_id']['id'] = 'item_id';
  $handler->display->display_options['sorts']['item_id']['table'] = 'salesforce_queue';
  $handler->display->display_options['sorts']['item_id']['field'] = 'item_id';
  $handler->display->display_options['sorts']['item_id']['order'] = 'DESC';
  /* Filter criterion: Salesforce queue: Queue ID */
  $handler->display->display_options['filters']['item_id']['id'] = 'item_id';
  $handler->display->display_options['filters']['item_id']['table'] = 'salesforce_queue';
  $handler->display->display_options['filters']['item_id']['field'] = 'item_id';
  $handler->display->display_options['filters']['item_id']['group'] = 1;
  $handler->display->display_options['filters']['item_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['item_id']['expose']['operator_id'] = 'item_id_op';
  $handler->display->display_options['filters']['item_id']['expose']['label'] = 'Item #';
  $handler->display->display_options['filters']['item_id']['expose']['operator'] = 'item_id_op';
  $handler->display->display_options['filters']['item_id']['expose']['identifier'] = 'item_id';
  $handler->display->display_options['filters']['item_id']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  /* Filter criterion: Salesforce queue: Module */
  $handler->display->display_options['filters']['module']['id'] = 'module';
  $handler->display->display_options['filters']['module']['table'] = 'salesforce_queue';
  $handler->display->display_options['filters']['module']['field'] = 'module';
  $handler->display->display_options['filters']['module']['group'] = 1;
  $handler->display->display_options['filters']['module']['exposed'] = TRUE;
  $handler->display->display_options['filters']['module']['expose']['operator_id'] = 'module_op';
  $handler->display->display_options['filters']['module']['expose']['label'] = 'Module';
  $handler->display->display_options['filters']['module']['expose']['operator'] = 'module_op';
  $handler->display->display_options['filters']['module']['expose']['identifier'] = 'module';
  $handler->display->display_options['filters']['module']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  /* Filter criterion: Salesforce queue: Drupal ID */
  $handler->display->display_options['filters']['drupal_id']['id'] = 'drupal_id';
  $handler->display->display_options['filters']['drupal_id']['table'] = 'salesforce_queue';
  $handler->display->display_options['filters']['drupal_id']['field'] = 'drupal_id';
  $handler->display->display_options['filters']['drupal_id']['group'] = 1;
  $handler->display->display_options['filters']['drupal_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['drupal_id']['expose']['operator_id'] = 'drupal_id_op';
  $handler->display->display_options['filters']['drupal_id']['expose']['label'] = 'Springboard ID';
  $handler->display->display_options['filters']['drupal_id']['expose']['operator'] = 'drupal_id_op';
  $handler->display->display_options['filters']['drupal_id']['expose']['identifier'] = 'drupal_id';
  $handler->display->display_options['filters']['drupal_id']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  /* Filter criterion: Salesforce queue: Object type */
  $handler->display->display_options['filters']['object_type_1']['id'] = 'object_type_1';
  $handler->display->display_options['filters']['object_type_1']['table'] = 'salesforce_queue';
  $handler->display->display_options['filters']['object_type_1']['field'] = 'object_type';
  $handler->display->display_options['filters']['object_type_1']['group'] = 1;
  $handler->display->display_options['filters']['object_type_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['object_type_1']['expose']['operator_id'] = 'object_type_1_op';
  $handler->display->display_options['filters']['object_type_1']['expose']['label'] = 'Object type';
  $handler->display->display_options['filters']['object_type_1']['expose']['operator'] = 'object_type_1_op';
  $handler->display->display_options['filters']['object_type_1']['expose']['identifier'] = 'object_type_1';
  $handler->display->display_options['filters']['object_type_1']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  /* Filter criterion: Salesforce queue: Operation */
  $handler->display->display_options['filters']['operation']['id'] = 'operation';
  $handler->display->display_options['filters']['operation']['table'] = 'salesforce_queue';
  $handler->display->display_options['filters']['operation']['field'] = 'operation';
  $handler->display->display_options['filters']['operation']['group'] = 1;
  $handler->display->display_options['filters']['operation']['exposed'] = TRUE;
  $handler->display->display_options['filters']['operation']['expose']['operator_id'] = 'operation_op';
  $handler->display->display_options['filters']['operation']['expose']['label'] = 'Operation';
  $handler->display->display_options['filters']['operation']['expose']['operator'] = 'operation_op';
  $handler->display->display_options['filters']['operation']['expose']['identifier'] = 'operation';
  $handler->display->display_options['filters']['operation']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  /* Filter criterion: Salesforce queue: Queue */
  $handler->display->display_options['filters']['queue']['id'] = 'queue';
  $handler->display->display_options['filters']['queue']['table'] = 'salesforce_queue';
  $handler->display->display_options['filters']['queue']['field'] = 'queue';
  $handler->display->display_options['filters']['queue']['group'] = 1;
  $handler->display->display_options['filters']['queue']['exposed'] = TRUE;
  $handler->display->display_options['filters']['queue']['expose']['operator_id'] = 'queue_op';
  $handler->display->display_options['filters']['queue']['expose']['label'] = 'Queue';
  $handler->display->display_options['filters']['queue']['expose']['operator'] = 'queue_op';
  $handler->display->display_options['filters']['queue']['expose']['identifier'] = 'queue';
  $handler->display->display_options['filters']['queue']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  /* Filter criterion: Salesforce queue: Created Timestamp */
  $handler->display->display_options['filters']['created']['id'] = 'created';
  $handler->display->display_options['filters']['created']['table'] = 'salesforce_queue';
  $handler->display->display_options['filters']['created']['field'] = 'created';
  $handler->display->display_options['filters']['created']['operator'] = 'between';
  $handler->display->display_options['filters']['created']['exposed'] = TRUE;
  $handler->display->display_options['filters']['created']['expose']['operator_id'] = 'created_op';
  $handler->display->display_options['filters']['created']['expose']['label'] = 'Created';
  $handler->display->display_options['filters']['created']['expose']['description'] = 'A date in any machine readable format. CCYY-MM-DD HH:MM:SS is preferred.';
  $handler->display->display_options['filters']['created']['expose']['operator'] = 'created_op';
  $handler->display->display_options['filters']['created']['expose']['identifier'] = 'created';
  $handler->display->display_options['filters']['created']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'admin/springboard/reports/integration-reports/queue';
  $handler->display->display_options['menu']['title'] = 'Queue';
  $handler->display->display_options['menu']['description'] = 'The active Salesforce queue';
  $handler->display->display_options['menu']['weight'] = '2';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $views[$view->name] = $view;

  /**
   * View sbv_administrator_users
   */
  $view = new view();
  $view->name = 'sbv_administrator_users';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'users';
  $view->human_name = 'sbv_administrator_users';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Administrators';
  $handler->display->display_options['css_class'] = 'donor-table-view sbadmin-table-min sbadmin-table-min-x sb-admin-page';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer springboard';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'uid' => 'uid',
    'sbp_first_name' => 'sbp_first_name',
    'sbp_last_name' => 'sbp_last_name',
    'mail' => 'mail',
    'created' => 'created',
    'rid' => 'rid',
    'edit_node' => 'edit_node',
    'view_user' => 'edit_node',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'uid' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'sbp_first_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'sbp_last_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'mail' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'rid' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_node' => array(
      'align' => '',
      'separator' => ' | ',
      'empty_column' => 0,
    ),
    'view_user' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: User: Uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'users';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['label'] = 'ID';
  $handler->display->display_options['fields']['uid']['link_to_user'] = FALSE;
  /* Field: User: First name */
  $handler->display->display_options['fields']['sbp_first_name']['id'] = 'sbp_first_name';
  $handler->display->display_options['fields']['sbp_first_name']['table'] = 'field_data_sbp_first_name';
  $handler->display->display_options['fields']['sbp_first_name']['field'] = 'sbp_first_name';
  $handler->display->display_options['fields']['sbp_first_name']['label'] = 'First Name';
  /* Field: User: Last name */
  $handler->display->display_options['fields']['sbp_last_name']['id'] = 'sbp_last_name';
  $handler->display->display_options['fields']['sbp_last_name']['table'] = 'field_data_sbp_last_name';
  $handler->display->display_options['fields']['sbp_last_name']['field'] = 'sbp_last_name';
  /* Field: User: E-mail */
  $handler->display->display_options['fields']['mail']['id'] = 'mail';
  $handler->display->display_options['fields']['mail']['table'] = 'users';
  $handler->display->display_options['fields']['mail']['field'] = 'mail';
  $handler->display->display_options['fields']['mail']['link_to_user'] = '0';
  /* Field: User: Created date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'users';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Created';
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'm/j/y';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'long';
  /* Field: User: Roles */
  $handler->display->display_options['fields']['rid']['id'] = 'rid';
  $handler->display->display_options['fields']['rid']['table'] = 'users_roles';
  $handler->display->display_options['fields']['rid']['field'] = 'rid';
  $handler->display->display_options['fields']['rid']['label'] = 'Role(s)';
  /* Field: User: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'users';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Action';
  /* Field: User: Link */
  $handler->display->display_options['fields']['view_user']['id'] = 'view_user';
  $handler->display->display_options['fields']['view_user']['table'] = 'users';
  $handler->display->display_options['fields']['view_user']['field'] = 'view_user';
  $handler->display->display_options['fields']['view_user']['label'] = 'View';
  /* Sort criterion: User: Last name (sbp_last_name) */
  $handler->display->display_options['sorts']['sbp_last_name_value']['id'] = 'sbp_last_name_value';
  $handler->display->display_options['sorts']['sbp_last_name_value']['table'] = 'field_data_sbp_last_name';
  $handler->display->display_options['sorts']['sbp_last_name_value']['field'] = 'sbp_last_name_value';
  /* Filter criterion: Global: Combine fields filter */
  $handler->display->display_options['filters']['combine']['id'] = 'combine';
  $handler->display->display_options['filters']['combine']['table'] = 'views';
  $handler->display->display_options['filters']['combine']['field'] = 'combine';
  $handler->display->display_options['filters']['combine']['operator'] = 'contains';
  $handler->display->display_options['filters']['combine']['group'] = 1;
  $handler->display->display_options['filters']['combine']['exposed'] = TRUE;
  $handler->display->display_options['filters']['combine']['expose']['operator_id'] = 'combine_op';
  $handler->display->display_options['filters']['combine']['expose']['label'] = 'Search';
  $handler->display->display_options['filters']['combine']['expose']['operator'] = 'combine_op';
  $handler->display->display_options['filters']['combine']['expose']['identifier'] = 'combine';
  $handler->display->display_options['filters']['combine']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  $handler->display->display_options['filters']['combine']['fields'] = array(
    'sbp_first_name' => 'sbp_first_name',
    'sbp_last_name' => 'sbp_last_name',
    'mail' => 'mail',
  );
  /* Filter criterion: Date: Date (users) */
  $handler->display->display_options['filters']['date_filter']['id'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['table'] = 'users';
  $handler->display->display_options['filters']['date_filter']['field'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['operator'] = 'between';
  $handler->display->display_options['filters']['date_filter']['group'] = 1;
  $handler->display->display_options['filters']['date_filter']['exposed'] = TRUE;
  $handler->display->display_options['filters']['date_filter']['expose']['operator_id'] = 'date_filter_op';
  $handler->display->display_options['filters']['date_filter']['expose']['operator'] = 'date_filter_op';
  $handler->display->display_options['filters']['date_filter']['expose']['identifier'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  $handler->display->display_options['filters']['date_filter']['form_type'] = 'date_popup';
  $handler->display->display_options['filters']['date_filter']['date_fields'] = array(
    'users.created' => 'users.created',
  );
  /* Filter criterion: User: Roles */
  $handler->display->display_options['filters']['rid']['id'] = 'rid';
  $handler->display->display_options['filters']['rid']['table'] = 'users_roles';
  $handler->display->display_options['filters']['rid']['field'] = 'rid';
  $handler->display->display_options['filters']['rid']['value'] = array(
    3 => '3',
    4 => '4',
    5 => '5',
  );
  $handler->display->display_options['filters']['rid']['group'] = 1;
  $handler->display->display_options['filters']['rid']['reduce_duplicates'] = TRUE;

  /* Display: Administrators */
  $handler = $view->new_display('page', 'Administrators', 'page');
  $handler->display->display_options['path'] = 'admin/springboard/settings/administrators';
  $views[$view->name] = $view;

  /**
   * View sbv_notes
   */
  $view = new view();
  $view->name = 'sbv_notes';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'aggregator_item';
  $view->human_name = 'sbv_notes';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'sbv_notes';
  $handler->display->display_options['css_class'] = 'sbv-notes-view';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access springboard dashboard';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'mini';
  $handler->display->display_options['pager']['options']['items_per_page'] = '3';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['class'] = 'notes-feed-list';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<h2>Springboard Notes</h2>';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  /* Footer: Global: Text area */
  $handler->display->display_options['footer']['area']['id'] = 'area';
  $handler->display->display_options['footer']['area']['table'] = 'views';
  $handler->display->display_options['footer']['area']['field'] = 'area';
  $handler->display->display_options['footer']['area']['content'] = '<a class="button all-notes"  href="http://www.jacksonriver.com/taxonomy/term/69" target="_blank">Read more Springboard notes</a>';
  $handler->display->display_options['footer']['area']['format'] = 'filtered_html';
  /* Field: Aggregator: Timestamp */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'aggregator_item';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['label'] = '';
  $handler->display->display_options['fields']['timestamp']['element_type'] = 'span';
  $handler->display->display_options['fields']['timestamp']['element_class'] = 'notes-timestamp';
  $handler->display->display_options['fields']['timestamp']['element_label_type'] = '0';
  $handler->display->display_options['fields']['timestamp']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['timestamp']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['timestamp']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['timestamp']['date_format'] = 'custom';
  $handler->display->display_options['fields']['timestamp']['custom_date_format'] = 'n/j/Y';
  /* Field: Aggregator: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'aggregator_item';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_type'] = 'h3';
  $handler->display->display_options['fields']['title']['element_label_type'] = '0';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['title']['display_as_link'] = FALSE;
  /* Field: Aggregator: Body */
  $handler->display->display_options['fields']['description']['id'] = 'description';
  $handler->display->display_options['fields']['description']['table'] = 'aggregator_item';
  $handler->display->display_options['fields']['description']['field'] = 'description';
  $handler->display->display_options['fields']['description']['label'] = '';
  $handler->display->display_options['fields']['description']['element_type'] = '0';
  $handler->display->display_options['fields']['description']['element_label_type'] = '0';
  $handler->display->display_options['fields']['description']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['description']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['description']['element_default_classes'] = FALSE;
  /* Field: Aggregator: Link */
  $handler->display->display_options['fields']['link']['id'] = 'link';
  $handler->display->display_options['fields']['link']['table'] = 'aggregator_item';
  $handler->display->display_options['fields']['link']['field'] = 'link';
  $handler->display->display_options['fields']['link']['label'] = '';
  $handler->display->display_options['fields']['link']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['link']['alter']['text'] = '<a class="button more-notes" href="[link]" target="_blank">Read more</a>';
  $handler->display->display_options['fields']['link']['element_type'] = '0';
  $handler->display->display_options['fields']['link']['element_label_type'] = '0';
  $handler->display->display_options['fields']['link']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['link']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['link']['display_as_link'] = FALSE;
  /* Sort criterion: Aggregator: Timestamp */
  $handler->display->display_options['sorts']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['table'] = 'aggregator_item';
  $handler->display->display_options['sorts']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['order'] = 'DESC';
  /* Filter criterion: Aggregator feed: Feed ID */
  $handler->display->display_options['filters']['fid']['id'] = 'fid';
  $handler->display->display_options['filters']['fid']['table'] = 'aggregator_feed';
  $handler->display->display_options['filters']['fid']['field'] = 'fid';
  $handler->display->display_options['filters']['fid']['value']['value'] = '1';

  /* Display: Dashboard Notes View */
  $handler = $view->new_display('block', 'Dashboard Notes View', 'block');
  $views[$view->name] = $view;

  // Return all the views.
  return $views;
}
