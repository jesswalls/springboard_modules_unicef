<?php

/**
 * @file
 * Admin functions for Springboard advocacy.
 */

/**
 * Page callback for the admin form.
 */

function springboard_advocacy_settings_page() {
  $build = array();
  $build['content'] = array(
    'page_description' => array(
      '#id' => 'springboard-advocacy-settings-page',
      '#type' => 'markup',
      '#markup' => '<p>' . t('Configure settings for Springboard advocacy.') .
      '</p><p>' .
      t('Saving this form will also force a rebuild of the advocacy subscription settings and renew the Oauth Access Token.') .
      '</p>',
      '#prefix' => '<div class="springboard-advocacy-settings-page">',
      '#suffix' => '</div>',
    ),
    'springboard_advocacy_settings_form' => drupal_get_form('springboard_advocacy_settings_form'),
  );
  return $build;
}

/**
 * Configuration settings form for Springboard advocacy.
 */
function springboard_advocacy_settings_form() {
  $form = array();

  $form['springboard_advocacy_debug'] = array(
    '#title' => t('Debug mode'),
    '#description' => t('Log extensive debug info to watchdog. Not recommended for production sites.'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('springboard_advocacy_debug', ''),
  );


  $form['transaction'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advocacy Server Configuration'),
  );

  $form['transaction']['springboard_advocacy_server_url'] = array(
    '#title' => t('Springboard advocacy server url'),
    '#description' => t('The url of the Springboard advocacy server.'),
    '#type' => 'textfield',
    '#default_value' => variable_get('springboard_advocacy_server_url', ''),
  );

  $form['transaction']['springboard_advocacy_client_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Transaction server Oauth Client ID.'),
    '#description' => t('Client ID for legislator lookup'),
    '#default_value' => variable_get('springboard_advocacy_client_id', ''),
  );

  $form['transaction']['springboard_advocacy_client_secret'] = array(
    '#type' => 'textfield',
    '#title' => t('Transaction server Oauth Client Secret.'),
    '#description' => t('Client Secret for legislator lookup'),
    '#default_value' => variable_get('springboard_advocacy_client_secret', ''),
  );

   $form['geo'] = array(
    '#type' => 'fieldset',
    '#title' => t('Geocoding configuration'),
  );

  //we may need this commented section if we offer a melissa option

  // $form['geo']['springboard_advocacy_geocoder'] = array(
  //   '#type' => 'radios',
  //   '#title' => t('Active Geocoding service'),
  //   '#options' => $options,
  //   '#description' => t('Choose the geocoding service to use. All but Google Javascript API require an API Key'),
  //   '#default_value' => variable_get('springboard_advocacy_geocoder', ''),
  // );

  $form['geo']['springboard_advocacy_geocoder'] = array(
  '#type' => 'hidden',
  '#value' => 'smartystreets_rest',
  );

  $form['geo']['smarty'] = array(
    '#type' => 'fieldset',
    '#title' => t('Smarty Streets configuration'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['geo']['smarty']['springboard_advocacy_smarty_authid'] = array(
    '#type' => 'textfield',
    '#title' => t('Smarty Streets Auth ID'),
    '#description' => t('Required for the REST API'),
    '#default_value' => variable_get('springboard_advocacy_smarty_authid', ''),
  );

  $form['geo']['smarty']['springboard_advocacy_smarty_authtoken'] = array(
    '#type' => 'textfield',
    '#title' => t('Smarty Streets Auth Token'),
    '#description' => t('Required for the REST AP'),
    '#default_value' => variable_get('springboard_advocacy_smarty_authtoken', ''),
  );

  return system_settings_form($form);

}

/**
 * Page callback for the advocacy dashboard.
 *
 * Embeds and themes various views landing pages.
 */
function springboard_advocacy_dashboard($path, $arg = NULL) {
  global $user;

  switch($path) {

    case 'add-custom-targets':
        module_load_include('inc', 'springboard_target', 'includes/springboard_target.custom_targets_create');
        drupal_add_css(drupal_get_path('module', 'springboard_target') . '/css/sba_target.css');
        $form = drupal_get_form('springboard_target_create_custom_targets_form');
        $views = array(
          'add-targets' => array(
            'header' => t('Create Target'),
            'content' => drupal_render($form),
            'manage_link' => array('title' => t('Return to targets list'), 'href' => 'admin/springboard/advocacy/targets/custom-targets'),
            'css' => drupal_get_path('module', 'springboard_advocacy') . '/css/sba.css',
          ),
        );
      break;

    case 'edit-custom-targets':
      module_load_include('inc', 'springboard_target', 'includes/springboard_target.custom_targets_edit');
      drupal_add_css(drupal_get_path('module', 'springboard_target') . '/css/sba_target.css');
      $form = drupal_get_form('springboard_target_edit_custom_targets_form', $arg);
      $views = array(
        'add-targets' => array(
          'header' => t('Edit Target'),
          'content' => drupal_render($form),
          'manage_link' => array('title' => t('Return to targets list'), 'href' => 'admin/springboard/advocacy/targets/custom-targets'),
          'css' => drupal_get_path('module', 'springboard_advocacy') . '/css/sba.css',
        ),
      );
      if (user_access('create targets')) {
        $views['add-targets']['create_link'] = array('title' => t('Create a new target'), 'href' => 'admin/springboard/advocacy/targets/custom-targets/add');
      };
      break;

    case 'actions':
      $view = views_get_view('sba_actions');
      $view -> set_display('block_1');
      $view -> set_arguments(array('sba_message_action'));
      $view -> pre_execute();
      $view -> execute();
      if ($view && $view -> access('block_1') && !empty($view -> result)) {
        $views = array(
          'sba_actions' => array(
            'header' => t('Message Actions'),
            'content' => $view->preview(), //views_embed_view('sba_actions', 'block_1', 'sba_message_action'),
            'create_link' => array('title' => t('Create a new message action'), 'href' => 'node/add/sba-message-action'),
            'viewmore_link' => array('title' => t('View All Message Actions'), 'href' => 'admin/springboard/advocacy/message-actions/all'),
            'css' => drupal_get_path('module', 'springboard_advocacy') . '/css/sba.css',
          ),
        );
        if (module_exists('springboard_target') && springboard_target_user_can_access_targets()) {
          $views['sba_actions']['manage_link'] = array('title' => t('Manage Custom Targets'), 'href' => 'admin/springboard/advocacy/targets/custom-targets');
        }
      }

      $view = views_get_view('sba_actions');
      $view -> set_display('block_1');
      $view -> set_arguments(array('springboard_petition'));
      $view -> pre_execute();
      $view -> execute();

      if ($view && $view -> access('block_1') && !empty($view -> result)) {
        $views['sba_petitions'] = array(
            'header' => t('Petitions'),
            'content' => $view->preview(), //views_embed_view('sbv_forms', 'block_1', 'springboard_petition'),
            'create_link' => array('title' => t('Create a new petition'), 'href' => 'node/add/springboard-petition'),
            'viewmore_link' => array('title' => t('View All Petitions'), 'href' => 'admin/springboard/advocacy/petitions/all'),
            'css' => drupal_get_path('module', 'springboard_advocacy') . '/css/sba.css',
        );
      }
      break;

    case 'message-actions/all':
      $view = views_get_view('sba_actions');
      if($view && isset($view->display['block_2'])) {
        $views = array(
          'sba_actions' => array(
            'header' => t('All Message Actions'),
            'content' => views_embed_view('sba_actions', 'block_2', 'sba_message_action'),
            'css' => drupal_get_path('module', 'springboard_advocacy') . '/css/sba.css',
          ),
        );
        if (user_access('create sba_message_action content')) {
          $views['sba_actions']['create_link'] = array('title' => t('Create a new message action'), 'href' => 'node/add/sba-message-action');
        }
        if (springboard_target_user_can_access_targets()) {
          $views['sba_actions']['manage_link'] = array('title' => t('Manage Custom Targets'), 'href' => 'admin/springboard/advocacy/targets/custom-targets');
        }
      }
      else {
        $views = springboard_advocacy_dashboard_error('sba_actions', 'Custom Targets', 'Message Actions view or view display "block_2" not found.');
      }
      break;

    case 'petitions/all':
      $view = views_get_view('sba_actions');
      if($view && isset($view->display['block_2'])) {
        $views = array(
          'sba_actions' => array(
            'header' => t('All Petitions'),
            'content' => views_embed_view('sba_actions', 'block_2', 'springboard_petition'),
            'css' => drupal_get_path('module', 'springboard_advocacy') . '/css/sba.css',
          ),
        );
        if (user_access('create springboard_petition content')) {
          $views['sba_actions']['create_link'] = array('title' => t('Create a new petition'), 'href' => 'node/add/springboard-petition');
        }
      }
      else {
        $views = springboard_advocacy_dashboard_error('sba_actions', 'Custom Targets', 'Petitions view or view display "block_2" not found.');
      }
      break;

    case 'custom-targets':
      $unconfigured = springboard_advocacy_api_unconfigured('springboard');
      if(!empty($unconfigured)) {
        $items = implode(', ', $unconfigured);
        $view = FALSE;
      }
      else {
        $view = views_get_view('sba_custom_targets');
      }
      if($view && isset($view->display['block_1'])) {
        $view -> set_display('block_1');
        $view -> pre_execute();
        $view -> execute();

        $views = array(
          'sba_targets' => array(
            'header' => t('Custom Targets'),
            'content' => $view->preview(),
            'css' => drupal_get_path('module', 'springboard_advocacy') . '/css/sba.css',
            //'js' => drupal_get_path('module', 'springboard_target') . '/js/sba_target.js',

          ),
        );
        if (user_access('create targets')) {
          $views['sba_targets']['create_link'] = array('title' => t('Create a new target'), 'href' => 'admin/springboard/advocacy/targets/custom-targets/add');
        };
      }
      else {
        if(!empty($unconfigured)) {
          $message = t('Please <a href="!url">configure</a> the Springboard API settings. There are empty values in :items. Configuration is required prior to target creation.', array('!url' => url('admin/config/services/advocacy'), ':items' => $items));
        }
        else {
          $message = t('Target view or view display "block_1" not found.');
        }
        $views = springboard_advocacy_dashboard_error('sba_targets', 'Custom Targets', $message);
      }

      break;

    case ($path == arg(1)):
      $message_types = variable_get('sba_message_node_types', array());
      $node = node_load($path);
      if(isset($message_types[$node->type])) {
        if(isset($node->message_ids)) {
          $messages = entity_load('sba_message', $node->message_ids);
          if(count($messages) == 1) {
            $message = array_pop($messages);
            $subject_editable = field_get_items('sba_message', $message, 'field_sba_subject_editable');
            $user_editable = field_get_items('sba_message', $message, 'field_sba_user_editable');
            if($subject_editable[0]['value'] != 'Not editable' || !empty($user_editable)) {
              $no_create = TRUE;
              drupal_set_message(t('This action\'s current message is user-editable, additional messages may not be created for this action until user editing is disabled.'), 'warning', FALSE);

            }
          }
        }

        $unconfigured = springboard_advocacy_api_unconfigured('springboard');
        if(!empty($unconfigured)) {
          $items = implode(', ', $unconfigured);
          drupal_set_message(t('Advocacy API is not properly <a href="!url">configured</a>. There are empty values in :items. Configuration is required prior to message creation.', array('!url' => url('admin/config/services/advocacy'), ':items' => $items)));
          $view = FALSE;
        }
        else {
          $view = views_get_view('sba_messages_node');
        }

        if ($view && isset($view->display['block_1'])) {
          $views = array(
            'sba_messages_node' => array(
              'header' => t('Messages'),
              'content' => views_embed_view('sba_messages_node', 'block_1', $path),
              'css' => drupal_get_path('module', 'springboard_advocacy') . '/css/sba.css',
            ),
          );
          if((user_access('edit own sba_message_action content') && $user->uid == $node->uid) || user_access('edit any sba_message_action content')) {
            $views['sba_messages_node']['create_link'] = array('title' => t('Create a new message'), 'href' => 'node/' . arg(1) . '/messages/add/' . $message_types[$node->type]);
          }
          if (!empty($no_create)) {
            unset($views['sba_messages_node']['create_link']);
          }
        } else {
          if(!empty($unconfigured)) {
            $message = t('Please <a href="!url">configure</a> the Springboard API settings. There are empty values in :items. Configuration is required prior to message creation.', array('!url' => url('admin/config/services/advocacy'), ':items' => $items));
          }
          else {
            $message = t('Message view or view display "block_1" not found');
          }
          $views = springboard_advocacy_dashboard_error('sba_messages_node', 'Messages', $message);
        }
      }
      else {
        $views = springboard_advocacy_dashboard_error('sba_messages_node', 'Messages', 'There was a problem locating the message type for this node type.');
      }
      break;

    default:
  }
  return theme('springboard_advocacy_dashboard', array('views' => $views));

}

function springboard_advocacy_dashboard_error($view, $title, $message) {
  $views = array(
    '{$view}' => array(
      'header' => t($title),
      'content' => '<div>' . t($message) . '</div>',
    ),
  );
  return $views;
}

