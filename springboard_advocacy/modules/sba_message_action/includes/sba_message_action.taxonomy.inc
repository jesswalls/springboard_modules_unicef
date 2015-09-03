<?php

/**
 * @file
 * Helper functions for message action taxonomy form.
 */

/**
 * Shows the legislative issues form on the message action node/add/edit page.
 */
function sba_message_action_taxonomy_form(&$form, &$form_state, $form_id) {

  $form['springboard_taxonomy_options']['#title'] = t('Action options');
  form_load_include($form_state, 'inc', 'sba_message_action',
    'includes/sba_message_action.webform');
  $language = $form['language']['#value'];
  // Legislative Issues selection.
  if (isset($form['field_sba_legislative_issues']) && !empty($form['field_sba_legislative_issues'][$language])) {
    // Filter out all but the top-tier terms.
    $options =& $form['field_sba_legislative_issues'][$language]['#options'];
    $vocabulary = taxonomy_vocabulary_machine_name_load('sba_legislative_issues');
    // Add indentation class to non-top-tier org issue terms.
    $terms = array();

    foreach (taxonomy_get_tree($vocabulary->vid) as $term) {
      $terms[$term->tid] = $term;
    }
    foreach ($options as $tid => $label) {
      if ($terms[$tid]->depth > 0) {
        unset($options[$tid]);
      }
    }

    // Move the field to a special fieldset inside "Action options."
    $form['springboard_taxonomy_options']['legislative_issues'] = array(
      '#type' => 'fieldset',
      '#title' => t('Choose Legislative Issue(s)'),
      '#description' => t("Many members of Congress require an issue/topic to be selected for each message they receive. If your action is targeting members of Congress, please select the issue that best matches the topic of your message. Based on your choice, Springboard will choose the best available match on each legislator's web form."),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
      '#weight' => -1,
    );
    $form['field_sba_legislative_issues'][$language]['#title'] = '';
    $form['springboard_taxonomy_options']['legislative_issues']['field_sba_legislative_issues']
      = $form['field_sba_legislative_issues'];
    unset($form['field_sba_legislative_issues']);

  }
}

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * Alter the admin/structure/taxonomy page.
 *
 * Remove the operations links from the legislative issues row and display
 * a message explaining why they are not there.
 */
function sba_message_action_form_taxonomy_overview_vocabularies_alter(&$form, &$form_state) {
  foreach (element_children($form) as $key) {
    if (isset($form[$key]['#vocabulary']) && !empty($form[$key]['#vocabulary']->machine_name)) {
      if ($form[$key]['#vocabulary']->machine_name == 'sba_legislative_issues') {
        $form[$key]['edit']['#type'] = 'markup';
        $form[$key]['edit']['#markup'] = t('This vocabulary is pre-configured for Springboard Advocacy and is not editable.');
        $form[$key]['add']['#access'] = FALSE;
        $form[$key]['list']['#access'] = FALSE;
      }
    }
  }
}

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * Hide edit links on the terms page.
 */
function sba_message_action_form_taxonomy_overview_terms_alter(&$form, &$form_state) {
  if($form['#vocabulary']->machine_name == 'sba_legislative_issues') {
    $form['actions']['#access'] = FALSE;
    foreach (element_children($form) as $key) {
      $form[$key]['edit']['#access'] = FALSE;
    }
  }
}

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * Hide edit fields on the vocab edit page.
 */
function sba_message_action_form_taxonomy_form_vocabulary_alter(&$form, &$form_state) {
  if($form['#vocabulary']->machine_name == 'sba_legislative_issues') {
    foreach (element_children($form) as $key) {
      $form[$key]['#access'] = false;
    }
    $form['#prefix'] = t("This vocabulary cannot be edited");
  }
}

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * Remove form fields from the term edit page.
 */
function sba_message_action_form_taxonomy_form_term_alter(&$form, &$form_state) {
  if ($form['#bundle'] == 'sba_legislative_issues') {
    $prefix = t('Terms cannot be added or edited in this vocabulary.');
    foreach (element_children($form) as $key) {
      $form[$key]['#access'] = false;
    }
    $form['#prefix'] = $prefix;
  }
}
