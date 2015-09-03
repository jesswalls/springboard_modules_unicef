<?php

/**
 * Gets Zip+4 from Smarty streets.
 *
 * Builds a user contact array with zip, county and lat/long.
 * Gets the messages associated with the webform and prepares them for sending
 * to the API.
 * Merges the contact, messages, and form_id and sends to the target resolver.
 *
 * @param array $user_message
 *    Message submitted by the user.
 * @param array $form_state
 *   The submitted form state.
 */
function sba_message_action_send_message(array $user_message, array $form_state) {
  $values = $form_state['values'];
  $webform_values = $values['webform_flat'];
  $zip = '';
  $response = '';
  // Unset the recipients from any prior submissions.
  if (isset($_SESSION['message_recipients'])) {
    unset($_SESSION['message_recipients']);
  }

  // Get the zip+4 from smarty streets.
  $geo = isset($form_state['values']['smarty_geo']) ? $form_state['values']['smarty_geo'] : array();
  if (!empty($geo) && !empty($geo['zip']) && !empty($geo['plus4'])) {
    $zip = $geo['zip'] . '-' . $geo['plus4'];
  }

  // We've got a full zip, so we can prepare the submission to send
  // to the resolver.
  if (!empty($zip)) {

    // Build the contact array.
    $contact = sba_message_action_build_contact($webform_values, $zip, $geo);

    // Build the message array.
    $message_build = sba_message_action_build_messages($user_message);
    // Build the submission array.
    $submission = array(
      'contact' => $contact,
      'form_id' => $values['advocacy_id'],
      'messages' => $message_build,
    );
    $node = $form_state['complete form']['#node'];
    $test_mode = field_get_items('node', $node, 'field_sba_test_mode');
    if (!empty($test_mode[0]['value']) && $test_mode[0]['value'] == 1) {
      $test_email = field_get_items('node', $node, 'field_sba_test_mode_email');
      $submission['test_mode'] = TRUE;
      $submission['test_email'] = !empty($test_email[0]['safe_value']) ? $test_email[0]['safe_value'] : '';
    }

    // Send submission to API Client.
    $api_call = new AdvocacyApiCall();
    $response = $api_call->invokeClientMethod('resolveTargets', $submission);
    if (isset($response->data)) {
      // We got a valid response, build the confirmation message array.
      sba_message_action_set_confirmation_session_vars($response->data, $contact);
    }
  }
  return !empty($response->data) ? $response->data : NULL;
}

/**
 * Loads the messages associated with this webform.
 *
 * Formats them into an array for the target resolver.
 *
 * @param array $user_message
 *   The submitted messages.
 *
 * @return array
 *   Messages formatted for the API call.
 */
function sba_message_action_build_messages(array $user_message) {
  $all_messages = entity_load('sba_message', array_keys($user_message));
  $messages = array();
  $x = 0;

  foreach ($all_messages as $message) {
    $message_wrapper = entity_metadata_wrapper('sba_message', $message);

    $message_unique_id = $message->data['message_id'];
    $weight = !empty($message->data['precedence']) ? $message->data['weight'] : $x++;

    // Attach legislative issue search terms.
    $legislative_terms = array("Other");
    // Provide a generic default.
    if ($message_wrapper->field_sba_action_id
      ->__isset('field_sba_legislative_issues')) {
      // Field_sba_action_id is a reference to the action webform.
      $legislative_parent_terms = $message_wrapper->field_sba_action_id
        ->field_sba_legislative_issues->value();
      $legislative_terms = sba_message_action_legislative_terms($legislative_parent_terms);
    }

    $messages[$weight] = array(
      'message_id' => $message_unique_id,
      'subject' => $user_message[$message->sba_message_id]['subject'],
      'body' => $user_message[$message->sba_message_id]['body'],
      'topic' => $legislative_terms,
      'precedence' => !empty($message->data['precedence']) ? 1 : 0,
    );
  }
  ksort($messages);
  return $messages;
}

/**
 * Parse the taxonomy tree.
 *
 * @param array $parent_terms
 *   The parent terms.
 *
 * @return array
 *   Terms merged with their children.
 */
function sba_message_action_legislative_terms($parent_terms) {
  $terms = array();
  if (!empty($parent_terms)) {
    $tree = taxonomy_get_tree($parent_terms[0]->vid);
    foreach ($parent_terms as $parent_term) {
      $children = _sba_message_action_legislative_terms_descendents($parent_term->tid, $tree);
      $terms = array_merge($terms, $children);
    }
  }
  return $terms;
}

/**
 * Helper function.
 *
 * @param int $ancestor_tid
 * @param array $tree
 *
 * @return array
 */
function _sba_message_action_legislative_terms_descendents($ancestor_tid, $tree) {
  $children = array();
  foreach ($tree as $term) {
    foreach ($term->parents as $parent_tid) {
      if ($parent_tid == $ancestor_tid || !empty($children[$parent_tid])) {
        $children[$term->tid] = $term->name;
      }
    }
  }
  return $children;
}

/**
 * Merges the webform users contact data with data returned from smarty streets.
 *
 * Preparation for sending to target resolver.
 *
 * @param array $values
 *    Springboard Profile Values.
 * @param string $zip
 *   A zip + 4 code.
 * @param array $geo
 *   Array of address data returned from Smarty Streets lookup.
 *
 * @return array
 *   Contact's profile data plus smarty data.
 */
function sba_message_action_build_contact(array $values, $zip, array $geo) {

  $line_2 = !empty($values['sbp_address_line_2']) ? $values['sbp_address_line_2'] . "\n " : '';
  $contact = array(
    'first_name' => $values['sbp_first_name'],
    'last_name' => $values['sbp_last_name'],
    'address' => $values['sbp_address'],
    'address_line_2' => $values['sbp_address_line_2'],
    'city' => $values['sbp_city'],
    'state' => $values['sbp_state'],
    'phone' => $values['sbp_phone'],
    'zip' => $zip,
    'full_address' => $values['sbp_address'] . "\n"  . $line_2   . $values['sbp_city'] . ", "  . $values['sbp_state'] . " " . $zip,
    'email' => $values['mail'],
    'county' => isset($geo['county']) ? $geo['county'] : '',
    'fips' => isset($geo['fips']) ? $geo['fips'] : '',
    'latitude' => isset($geo['latitude']) ? $geo['latitude'] : '',
    'longitude' => isset($geo['longitude']) ? $geo['longitude'] : '',
  );

  return $contact;
}

/**
 * Create session vars to hold data for use by confirmation theming functions.
 *
 * The session variables are passed through their theming functions
 * from hook_tokens().
 *
 * @param object $response
 *   The API response.
 */
function sba_message_action_set_confirmation_session_vars($response, $contact) {
  if (!empty($response->messages)) {
    $_SESSION['delivered_messages'] = array();
    $_SESSION['undelivered_messages'] = array();
    $status = sba_message_action_get_message_statuses($response);
    unset($status['success']['target_count']);
    if (!empty($status['success'])) {
      $messages = array();
      $count_messages = count($status['success']);
      $count_targets = 0;
      $x = 0;
      foreach ($status['success'] as $id => $message) {
        foreach ($message['people'] as $key => $person) {
          $count_targets++;
          $messages[$x]['person'] = $person;
          $messages[$x]['subject'] = $status['success'][$id]['subject'];
          $messages[$x]['body'] = $status['success'][$id]['body'];
          $messages[$x]['targets'] = $message['targets'][$key];
          $x++;
        }
      }
      $_SESSION['delivered_messages'] =
        array(
          'messages' => $messages,
          'contact' => $contact,
          'target_count' => $count_targets,
          'message_count' => $count_messages,

      );
    }

    unset($status['hold']['target_count']);
    $messages = array();
    if (!empty($status['hold'])) {
      foreach ($status['hold'] as $id => $message) {
        foreach ($message['people'] as $key => $person) {
          $messages[$id]['people'][] = $person;
          $messages[$id]['message'] = $status['hold'][$id]['body'];
          $messages[$id]['subject'] = $status['hold'][$id]['subject'];
          $messages[$id]['targets'] = $message['targets'];
        };
      }
      $_SESSION['undelivered_messages'] =
        array(
          'messages' => $messages,
          'contact' => $contact,
          'targets' => '',
        );
      }
    }
}

/**
 * Theme the delivered messages.
 *
 * @param array $vars
 *   Array of message recipients.
 *
 * @return string
 *   Rendered HTML.
 */
function sba_message_action_preprocess_webform_confirmations_delivered(&$vars) {

  // Put the recipients in an array for the item list.
  $targets = array();
  foreach ($vars['messages'] as $key => $message) {

    // Put the party in parens.
    if(isset($message['person']['party'])) {
      $message['person']['party'] = '(' . $message['person']['party'] . ')';
    }

    // Format the contact for token replacement.
    $contact = (object) $vars['contact'];
    // Replace the tokens
    $message['body'] = token_replace($message['body'], array('sba_contact' => $contact, 'sba_target' => $message['targets'],));
    //In case it comes back encoded,
    // we don't want theme_link to double encode it.
    $subject = decode_entities($message['subject']);
    // Prepare the body text for display in a javascript
    // pop-up window. Make sure we're not double encoding.
    $body =  nl2br(check_plain(decode_entities($message['body'])));
    $body = addslashes(trim(preg_replace('/\s+/', ' ', $body)));
    $on_click = "if(typeof messageWrapper !=='undefined'){messageWrapper.close()};messageWrapper=window.open('','messageWrapper','toolbar=no,scrollbars=yes,status=no,menubar=no,resizable=yes,top=0,left=0,width=640,height=480');messageWrapper.document.write(\"" . $body  . "\");messageWrapper.focus();return false;";
    $link = l($subject, '#', array('attributes' => array('onclick' => $on_click)));
    // Prepare the recipients for display in a bulleted list.
    unset($message['person']['url']);

    $targets[$key]['person'] = implode(' ', $message['person']);
    $targets[$key]['link'] =  $link;
  }

  if(empty($targets)) {
    $targets[]['person'] = t('You have no deliverable messages.');
  }

  $message_plural = format_plural($vars['message_count'], 'message was', 'messages were');
  $target_plural = format_plural($vars['target_count'], 'target', 'targets');

  $vars['message_count_text'] = t('@message_count @messages delivered to @target_count @targets.',
    array(
      '@message_count' => $vars['message_count'],
      '@messages' => $message_plural,
      '@target_count' => $vars['target_count'],
      '@targets' => $target_plural,
    )
  );

  $vars['delivered_title'] = t('Delivered Messages');
  $vars['targets'] = $targets;
}

/**
 * Theme the undelivered messages.
 *
 * @param array $vars
 * @return string
 */
function sba_message_action_preprocess_webform_confirmations_undelivered(&$vars) {
  $messages = $vars['messages'];
  $message_count = count($messages);
  $target_count = 0;
  $messages_out = array();
  $count_output = '';

  foreach ($messages as $id => $message) {
    foreach ($message['people'] as $key => $person) {
      // Stores the segments of the target
      $target_info = array();
      $target_count++;
      if (!empty($person['url'])) {
        $on_click = "var extWrapper=window.open(this.href,'targetWindow','toolbar=no,scrollbars=yes,status=no,menubar=no,resizable=yes,top=0,left=0,width=1024,height=800');extWrapper.focus();return false;";
        $link = l($person['name'], check_plain($person['url']), array('attributes' => array('onclick' => $on_click)));
        $target_info[] = t('!name', array('!name' => $link)) . ' (' . $person['party'] . ') ' . $person['district'];
      } else {
        $target_info[] = $person['name'].' ('.$person['party'].') '.$person['district'];
      }
      // Prepare the contact object so we can replace tokens in the message.
      $contact = (object) $vars['contact'];
      $message['message'] = token_replace($message['message'], array('sba_contact' => $contact, 'sba_target' => $message['targets'][$key],));
      // The recipient.
      $messages_out[$id][$key]['target'] = implode(' ', $target_info);
      // Make sure we're not double encoding in case
      // it comes back from API server encoded.
      $messages_out[$id][$key]['subject'] =   check_plain(decode_entities($message['subject']));
      $messages_out[$id][$key]['message'] = check_markup($message['message'], 'filtered_html');
    }
  }

  $message_plural = format_plural($message_count, 'message', 'messages');
  $target_plural = format_plural($target_count, 'target', 'targets');

  if ($message_count) {
    $count_output .= t(
        "We were unable to deliver @message_count @messages to @target_count @targets. Please visit the decision-maker's website to submit your message directly.",
        array(
          '@message_count' => $message_count,
          '@messages' => $message_plural,
          '@target_count' => $target_count,
          '@targets' => $target_plural,
        )
      );
  }
  else {
    $count_output .= t('You have no undeliverable messages.');
  }

  $vars['undeliverable_title'] =  t('Undeliverable Messages');
  $vars['message_count'] = $message_count;
  $vars['target_count'] = $target_count;
  $vars['message_count_text'] = $count_output;
  $vars['show_message_text'] = t('Show message');
  $vars['messages_out'] = array();
  foreach ($messages_out as $key => $message) {
    foreach($message as $recipient) {
      $vars['messages_out'][] = $recipient;
    }
  }
}



/**
 * Split up the "deliverable" response into "success" and "hold".
 *
 * Some deliverable target webforms may be temporarily out of action and
 * the target object in the response will have a "webform_status" property
 * set to "hold". If so, we split those off into a separate array for display
 * on the confirmation page.
 *
 * @param object $response
 *   The API server response.
 *
 * @return array
 *   An array of messages.
 */
function sba_message_action_get_message_statuses($response) {

  $messages = array();
  $message_success = array();
  $message_hold = array();
  $success_count = 0;
  $hold_count = 0;

  foreach ($response->messages as $id => $message) {
    if (!empty($message->deliverable)) {
      $messages[$id]['deliverable'] = $message->deliverable;
      $messages[$id]['subject'] = $message->message->subject;
      $messages[$id]['body'] = $message->message->body;
    }
  }

  foreach ($messages as $id => $message) {
    foreach ($messages[$id]['deliverable'] as $target) {
      // Filter the largish target object in the response down to
      // a few select properties, in an array
      $target_details = sba_message_action_get_target_details($target);
      // Split into success and hold arrays.
      if (empty($target->webform_status)
        || (!empty($target->webform_status) && $target->webform_status != 'Hold')) {
        $success_count++;
        $message_success['target_count'] = $success_count;
        $message_success[$id]['people'][] = $target_details;
        $message_success[$id]['subject'] = $messages[$id]['subject'];
        $message_success[$id]['body'] = $messages[$id]['body'];
        $message_success[$id]['targets'][] = $target;
      }
      else {
        $hold_count++;
        $message_hold['target_count'] = $hold_count;
        $message_hold[$id]['people'][] = $target_details;
        $message_hold[$id]['subject'] = $messages[$id]['subject'];
        $message_hold[$id]['body'] = $messages[$id]['body'];
        $message_hold[$id]['targets'][] = $target;
      }
    }
  }

  return array('success' => $message_success, 'hold' => $message_hold);
}

/**
 * Creates an array of recipients for each message.
 *
 * An array with name and organization details
 * that eventually gets converted to a readable string in the
 * confirmation theme function.
 *
 * @param object $target
 *   A target object extracted from the API response.
 *
 * @return array
 *   An array containing a subset of target properties.
 */
function sba_message_action_get_target_details($target) {

  $name = array();
  $target_details = array();

  if (!empty($target->salutation)) {
    $name[] = $target->salutation;
  }
  if (!empty($target->first_name)) {
    $name[] = $target->first_name;
  }
  if (!empty($target->last_name)) {
    $name[] = $target->last_name;
  }

  $target_details['name'] = implode(' ', $name);

  if (!empty($target->party)) {
    $target_details['party'] = check_plain($target->party);
  }
  if (!empty($target->state) && empty($target->district_name)) {
    $target_details['state'] = check_plain($target->state);
  }
  if (!empty($target->district_name)) {
    $target_details['district'] = check_plain($target->district_name);
  }

  if (!empty($target->webform_url)) {
    $target_details['url'] = check_plain($target->webform_url);
  }

  return $target_details;
}
