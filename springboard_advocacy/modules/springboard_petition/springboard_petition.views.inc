<?php

/**
 * @file
 */

/**
 * Implements hook_views_data().
 */
function springboard_petition_views_data() {
  $data['springboard_petition_opt_in']['table'] = array(
    'group' => t('Springboard Petitions'),
    'base' => array(
      'title' => t('Springboard Petition Opt In'),
      'help' => t('Tracks petition signatures opted in for display.'),
    ),
    'join' => array(
      'node' => array(
        'left_field' => 'nid',
        'field' => 'nid',
      ),
      'users' => array(
        'left_field' => 'uid',
        'field' => 'uid',
      ),
      'webform_submissions' => array(
        'left_field' => 'sid',
        'field' => 'sid',
      ),
    ),
  );
  $data['springboard_petition_opt_in']['nid'] = array(
    'title' => t('Petition node'),
    'help' => t('Petition form node id.'),
    'relationship' => array(
      'base' => 'node',
      'base field' => 'nid',
      'handler' => 'views_handler_relationship',
      'label' => t('Petition node'),
    ),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );
  $data['springboard_petition_opt_in']['uid'] = array(
    'title' => t('Signature opt-in user'),
    'help' => t('User associated with opt-in record.'),
    'relationship' => array(
      'base' => 'users',
      'base field' => 'uid',
      'handler' => 'views_handler_relationship',
      'label' => t('Opt in user'),
    ),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );
  $data['springboard_petition_opt_in']['sid'] = array(
    'title' => t('Signature opt-in submission'),
    'help' => t('Webform submission associated with opt-in record.'),
    'relationship' => array(
      'base' => 'webform_submissions',
      'base field' => 'sid',
      'handler' => 'views_handler_relationship',
      'label' => t('Opt in submission'),
    ),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );
  $data['springboard_petition_opt_in']['opt_in'] = array(
    'title' => 'Petition signature opt-in',
    'help' => t('Tracks user opt-in to display petition signature.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
    $data['springboard_petition_opt_in']['created'] = array(
    'title' => t('Signature opt-in submission creation time'),
    'help' => t('Webform Submission timestamp.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
  );

  return $data;
}

/**
 * Implements hook_views_default_views().
 */
function springboard_petition_views_default_views() {

  $view = new view();
  $view->name = 'recent_petition_signatures';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'springboard_petition_opt_in';
  $view->human_name = 'Recent Petition Signatures';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Recent Petition Signatures';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '60';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '60';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'sbp_first_name' => 'sbp_first_name',
    'sbp_last_name' => 'sbp_last_name',
    'created' => 'created',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'sbp_first_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => 'views-align-left',
      'separator' => '',
      'empty_column' => 0,
    ),
    'sbp_last_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => 'views-align-left',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => 'views-align-left',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Relationship: Springboard Petitions: Signature opt-in user */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'springboard_petition_opt_in';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Field: User: First name */
  $handler->display->display_options['fields']['sbp_first_name']['id'] = 'sbp_first_name';
  $handler->display->display_options['fields']['sbp_first_name']['table'] = 'field_data_sbp_first_name';
  $handler->display->display_options['fields']['sbp_first_name']['field'] = 'sbp_first_name';
  $handler->display->display_options['fields']['sbp_first_name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['sbp_first_name']['exclude'] = TRUE;
  /* Field: User: Last name */
  $handler->display->display_options['fields']['sbp_last_name']['id'] = 'sbp_last_name';
  $handler->display->display_options['fields']['sbp_last_name']['table'] = 'field_data_sbp_last_name';
  $handler->display->display_options['fields']['sbp_last_name']['field'] = 'sbp_last_name';
  $handler->display->display_options['fields']['sbp_last_name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['sbp_last_name']['label'] = '';
  $handler->display->display_options['fields']['sbp_last_name']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['sbp_last_name']['alter']['text'] = '[sbp_first_name] [sbp_last_name]';
  $handler->display->display_options['fields']['sbp_last_name']['element_label_colon'] = FALSE;
  /* Field: Springboard Petitions: Signature opt-in submission creation time */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'springboard_petition_opt_in';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'time ago';
  /* Sort criterion: Springboard Petitions: Signature opt-in submission creation time */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'springboard_petition_opt_in';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Springboard Petitions: Petition node */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'springboard_petition_opt_in';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'raw';
  $handler->display->display_options['arguments']['nid']['default_argument_options']['index'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Springboard Petitions: Petition signature opt-in */
  $handler->display->display_options['filters']['opt_in']['id'] = 'opt_in';
  $handler->display->display_options['filters']['opt_in']['table'] = 'springboard_petition_opt_in';
  $handler->display->display_options['filters']['opt_in']['field'] = 'opt_in';
  $handler->display->display_options['filters']['opt_in']['value'] = '1';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');

  $views[$view->name] = $view;

  // return views
  return $views;
}
