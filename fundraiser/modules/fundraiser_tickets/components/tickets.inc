<?php

function _webform_defaults_tickets() {
  return array(
    'name' => '',
    'form_key' => NULL,
    'pid' => 0,
    'weight' => 0,
    'value' => '',
    'mandatory' => 0,
    'extra' => array(
      'field_prefix' => '',
      'field_suffix' => '',
    ),
  );
}

/**
 * Implements _webform_edit_component().
 */
function _webform_edit_tickets($component) {
  $form = array();
  $form['edit_notice']['#markup'] = '<div>' . t('The settings for this field are controlled by Fundraiser.') . '</div>';
  $form['display']['#access'] = FALSE;
  return $form;
}

/**
 * Implements _webform_submit_component().
 *
 * Convert submitted keys and values into serialized, saveable data.
 */
function _webform_submit_tickets($component, $values) {
  foreach ($values as $key => $submitted_value){
    $return[] = serialize(array($key => $submitted_value));
  }
  return $return;
}

/**
 * Implements _webform_render_component().
 */
function _webform_render_tickets($component, $value = NULL, $filter = TRUE) {

  $element = array(
    '#type' => 'item',
    '#title' => $filter ? _webform_filter_xss($component['name']) : $component['name'],
    '#weight' => $component['weight'],
    '#attributes' => array('class' => array('webform-component-tickets')),
    '#title_display' => 'none',
    '#webform_component' => $component,
    '#theme' => 'fundraiser_tickets_webform_table',
    '#attached' => array('js' => array(drupal_get_path('module', 'fundraiser_tickets') . '/js/fundraiser_tickets.js')),
    '#element_validate' => array('_fundraiser_tickets_validate_webform_field'),
  );

  $node = isset($component['nid']) ? node_load($component['nid']) : NULL;
  $node_wrapper = entity_metadata_wrapper('node', $node);
  if (fundraiser_tickets_is_ticket_type($node->type)){

    if (!empty($node_wrapper->fr_tickets_ticket_types)) {
      // Create an array from the ticket products
      foreach ($node_wrapper->fr_tickets_ticket_types as $product_wrapper) {
        $ticket_types[] = $product_wrapper;
      }
    }

    if (!empty($ticket_types)){
      uasort($ticket_types, '_fundraiser_tickets_weight_sort');

      // Loop through the element and output the children fields as rows
      foreach ($ticket_types as $product_wrapper) {
        if ($product_wrapper->status->value() == FALSE){
          continue;
        }
        $tickets_available = $product_wrapper->fr_tickets_quantity->value() - $product_wrapper->fr_tickets_quantity_sold->value();
        $id = $product_wrapper->product_id->value();
        $item = array();
        $item['#type'] = 'select';
        $item['#id'] = 'product-' . $id . '-ticket-quant';
        $item['#extra']['product_id'] =  $id;
        $item['#options'] = range(0,($tickets_available < 50 ? $tickets_available : 50));
        if (! $tickets_available){
          $item['#disabled'] = TRUE;
        }
        $item['#title'] = '';
        $element[$item['#id']] = $item;
      }
    }

    if ($node_wrapper->fr_tickets_donation_donation->value() == TRUE){
      $element['#allow_extra_donation'] = TRUE;
    } else {
      $element['#allow_extra_donation'] = FALSE;
    }
    $target = !empty($node->fr_tickets_donation_addon_form[LANGUAGE_NONE][0]['target_id']) ? $node->fr_tickets_donation_addon_form[LANGUAGE_NONE][0]['target_id'] : FALSE;
    if ($target) {
      $addon_details = springboard_api_get_form_details($target);
    }
    if ($element['#allow_extra_donation'] == TRUE && isset($addon_details['fields']['other_amount'])){
      //$desc = strtolower($addon_details['fields']['other_amount']['description']);
      $item = array(
        '#type' => 'textfield',
        '#size' => 20,
        '#default_value' =>  NULL,
        '#id' => 'fundraiser-tickets-extra-donation',
        //'#description' => t('Optional. If giving, @min', array('@min' => $desc)),
      );
      $element['fundraiser-tickets-extra-donation'] = $item;
    }
    elseif($element['#allow_extra_donation'] == TRUE && !isset($addon_details['fields']['other_amount']) && user_access('create donation form')) {
      drupal_set_message('The add-on donation form for this item does not have an "other amount" field configured. Addon Donations will not be processed.', 'warning');
    }

    // Hide the event_table title if #title_display is 'none'.
    if (!empty($component['extra']['title_display']) && $component['extra']['title_display'] == 'none') {
      $element['#title'] = NULL;
    }
  }
  return $element;
}

/**
 * Pre-render function to add our id to the js settings
 */
function webform_tickets_prerender($element) {
  $id = 'webform-component-' . str_replace('_', '-', implode('--', array_slice($element['#parents'], 1)));
  $element['#attributes']['id'] = $id;
  drupal_add_js(array('fundraiserTickets' => array('table' => array('id' => $id))), 'setting');
  return $element;
}

/**
 * Validate the ticket fields to ensure at least one ticket type is selected
 */
function _fundraiser_tickets_validate_webform_field($element, &$form_state) {
  $ticket_values = drupal_array_get_nested_value($form_state['values'], $element['#parents']);

  // If the additional amount is set pull that from the ticket values and validate
  if (!empty($ticket_values['fundraiser-tickets-extra-donation'])) {
    $additional_amount = $ticket_values['fundraiser-tickets-extra-donation'];
    if (!preg_match('/^\d*(\.\d*)?$/', $additional_amount)) {
      form_set_error('fundraiser-tickets-extra-donation', t('Donation amount must be in a valid number format. No commas and only one decimal point.'));
    }
    if (!empty($form_state['complete form']['#node']->fr_tickets_donation_addon_form[LANGUAGE_NONE][0]['target_id'])) {
      $add_on = node_load($form_state['complete form']['#node']->fr_tickets_donation_addon_form[LANGUAGE_NONE][0]['target_id']);
      $min = intval($add_on->minimum_donation_amount);
      if(intval($ticket_values['fundraiser-tickets-extra-donation']) < $min) {
        form_set_error('fundraiser-tickets-extra-donation', t('Additional donation is a minimum of $@amount', array('@amount' => $min)));
      }
    }
    unset($ticket_values['fundraiser-tickets-extra-donation']);
  }

  // Grab the selected values and verify we have at least one
  $selected = array_filter($ticket_values);
  if (empty($selected)) {
    form_error($element, 'Please select at least one ticket type.');
  }

  // Verify we still have enough tickets to fulfill the order
  foreach ($selected as $key => $quantity) {
    $product_id = _fundraiser_tickets_get_product_id_from_form_element_name($key);

    if ($product_id && $quantity > 0) {
      $product_wrapper = entity_metadata_wrapper('commerce_product', commerce_product_load($product_id));

      // Compute the available tickets
      $available_tickets = $product_wrapper->fr_tickets_quantity->value() - $product_wrapper->fr_tickets_quantity_sold->value();
      if ($quantity > $available_tickets) {
        form_error($element, t('Your order could not be completed because only @quantity @type tickets remain.', array('@quantity' => $available_tickets, '@type' => $product_wrapper->title->value())));
      }
    }
  }
}

/**
 * Theme the form elements into a table
 */
function theme_fundraiser_tickets_webform_table($variables) {

  $element = $variables['element'];

  $node = node_load($element['#webform_component']['nid']);
  $node_currency = fundraiser_get_currency_from_node($node);

  // Ideally here we would use the currency code and commerce_currency_format(),
  // but we don't have the equivalent in the JS so instead we use dumbed down
  // currency formatting here to stay consistent with what the JS does.
  $node_currency_symbol = $node_currency['symbol'];

  $rows = array();
  $last_row = array();
  $ticket_prices = array();

  // Loop through the element and output the children fields as rows
  foreach (element_children($element) as $id) {
    if ($id == 'fundraiser-tickets-extra-donation'){

      try {
        $node_wrapper = entity_metadata_wrapper('node', $node);
        $addon_node = $node_wrapper->fr_tickets_donation_addon_form->value();
        $addon_currency = fundraiser_get_currency_from_node($addon_node);
        $addon_currency_symbol = $addon_currency['symbol'];
      }
      catch (Exception $e) {
        $addon_currency_symbol = $node_currency_symbol;
      }

      $last_row = array(
        'data' => array(
          t('Additional Donation'),
          '',
          drupal_render($element[$id]),
          '',
          array(
            'data' => $addon_currency_symbol . ' ' . '0.00',
            'id' => 'fundraiser-tickets-extra-donation-display',
            'align' => 'right',
            ),
          ),
        );
    } elseif (isset($element[$id]['#extra']['product_id'])){
      $product_wrapper = entity_metadata_wrapper('commerce_product', commerce_product_load($element[$id]['#extra']['product_id']));
      $tickets_available = $product_wrapper->fr_tickets_quantity->value() - $product_wrapper->fr_tickets_quantity_sold->value();

      $ticket_amount = $product_wrapper->commerce_price->amount->value();
      $ticket_currency_code = $product_wrapper->commerce_price->currency_code->value();
      $ticket_currency = commerce_currency_load($ticket_currency_code);
      $ticket_currency_symbol = $ticket_currency['symbol'];

      $formatted_amount = commerce_currency_format($ticket_amount, $ticket_currency_code);
      $row = array();
      $title = array(
        'data' => check_plain($product_wrapper->title->value()) . ' (' . $formatted_amount . ')',
        'class' => 'ticket_type',
      );

      $ticket_prices[$product_wrapper->product_id->value()] = array(
        'amount' => number_format(commerce_currency_amount_to_decimal($ticket_amount, $ticket_currency_code), 2),
        'currency' => $ticket_currency,
      );
      $description = array(
        'data' => $tickets_available ? check_plain($product_wrapper->fr_tickets_description->value()) : check_plain($product_wrapper->fr_tickets_sold_out_message->value()),
        'class' => 'ticket_description',
      );
      $warning_message = array(
        'data' => $tickets_available > 0 && $tickets_available <= $product_wrapper->fr_tickets_threshold->value() ? theme('fundraiser_tickets_warning_indicator', array('warning_message' =>t("Only @tickets remaining!", array('@tickets' => format_plural($tickets_available, '1 ticket', '@count tickets'))))) : NULL,
        'class' => 'ticket_warning',
      );
      // Add a div to contain the ticket total
      $ticket_total = array(
        'data' => $ticket_currency_symbol . ' ' . '0.00',
        'class' => 'fundraiser-ticket-type-total',
        'id' => 'product-' . $element[$id]['#extra']['product_id'] . '-tickets-total',
        'align' => 'right',
      );
      $row['data'] = array($title, $description, array('data'=> drupal_render($element[$id]), 'align' => 'right'), $warning_message, $ticket_total);
      $rows[] = $row;
    }
  }

  $rows[] = $last_row;

  // Add a row to contain our totals
  $rows[] = array(
    'data' => array(
      array('data' => t('Totals'), 'class' => 'ticket_type'),
      array('data' => '', 'class' => 'ticket_description'),
      array('data' => 0, 'id' => 'fundraiser-tickets-total-quant', 'class' => 'quantity', 'align' => 'right'),
      array('data' => '', 'class' => 'ticket_warning'),
      array('data' => $node_currency_symbol . ' ' . '0.00', 'id' => 'fundraiser-tickets-total-cost', 'class' => 'fundraiser-ticket-type-total', 'align' => 'right')
    )
  );
  $header = array(
    array('data' => t('Type'), 'class' => 'ticket_type'),
    array('data' => '', 'class' => 'ticket_description', 'id' => 'description'),
    array('data' => t('Quantity'), 'class' => 'quantity', 'align' => 'right'),
    array('data' => '', 'class' => 'ticket_warning'),
    array('data' => t('Amount'), 'class' => 'fundraiser-ticket-type-total', 'align' => 'right')
  );
  // $attributes = array('class' => $element['#attributes']['class'], 'id' => $id, 'width' => '100%');

  // Add the JS for the settings too
  drupal_add_js(array('fundraiserTickets' => array('ticketPrices' => $ticket_prices)), 'setting');

  $table = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
    '#attributes' => array(
      'class' => array('ticket_box'),
    )
  );

  $output = drupal_render($table);
  return $output;
}

/**
 * Theme function for the low ticket quantity warning message.
 */
function theme_fundraiser_tickets_warning_indicator($vars){
  return '*' . $vars['warning_message'] . '*';
}

/**
 * Theme function for the message that replaces the webform when the form is
 * closed.
 */
function theme_fundraiser_tickets_closed_message($vars){
  return $vars['message']['safe_value'];
}

/**
 * Theme function for the message that replaces the webform when tickets are
 * sold out.
 */
function theme_fundraiser_tickets_soldout_message($vars){
  return $vars['message']['safe_value'];
}




