<?php

/**
 *
 * Save the target message data to the API server
 * @param $sba_message
 * @param $is_new
 * @param $form_state
 *
 * The api is expecting an array structured like so:
 *
array(
  'name' => 'group name', //required
  'chambers' => array(
    0 => array('chamber' => 'fs', 'party =>'r', state => 'MA'),
    1 => array('chamber' => 'fs', 'party =>'d', state => 'MA')
    2 => array('chamber' => 'PRES01', 'party =>'r'),
    3 => array('chamber' => 'PRES03', 'party =>'d')
  )
  'target_ids' => array('1', '2', '3', '4', '5', '6', '7'),
)
 */
function _sba_message_api_save($sba_message, $is_new, $form_state) {
  $values = $form_state['values'];
  $indvds = array();
  $multi_indvds = array();
  $has_gender_or_social = array();
  $gender_or_social_rows = array();
  $chamber_rows = array();
  $unstructured_chambers = array();

  if (!empty($values['data']['recipients'])) {

    $targets = json_decode($values['data']['recipients']);
    foreach ($targets as $target) {
      if (isset($target->id)) {
        $indvds[$target->id] = $target->id;
      }
      elseif (isset($target->ids)) {
        $multi_indvds =  array_merge($multi_indvds, explode('|', $target->ids));
      }
      elseif (isset($target->gender) || isset($target->social)) {
        $has_gender_or_social[] = $target;
      }
      else {
        $unstructured_chambers[] = $target;
      }
    }
  }

  if (!empty($has_gender_or_social)) {
    $gender_or_social_rows = _sba_message_api_get_gender_or_social_ids($has_gender_or_social);
  }

  if (!empty($unstructured_chambers)) {
    $chamber_rows = _sba_message_api_build_chambers($unstructured_chambers);
  }

  $combined = array_merge($multi_indvds, $indvds, $gender_or_social_rows);
  $indvds = !empty($combined) ? json_encode($combined) : '';

  $api_call = new AdvocacyApiCall();

  // Is this a new message? Then create a new target group for it.
  if ($is_new) {
    $response = _sba_message_api_create_group($api_call, $sba_message, $chamber_rows, $indvds, $values);
    if (!empty($response->data->id)) {
      _sba_message_api_valid_response($sba_message, $response);
    }
    else {
      _sba_message_api_invalid_response($sba_message);
    }
  }
  elseif (!$is_new) {
    // Perhaps during group creation the response was interrupted
    // or the group creaton failed
    if ($sba_message->data['group_id'] == 'no_response') {
      $response = _sba_message_api_get_group_by_message_id($api_call, $sba_message->data['message_id']);
      if (!empty($response) && !empty($response->data->id)) {
        $sba_message->data['group_id'] = $response->data->id;
        $sba_message->changed = time();
        $sba_message->save();
        $update = _sba_message_api_update_group($api_call, $sba_message, $chamber_rows, $indvds, $values);
      }
      else {
        $update = _sba_message_api_create_group($api_call, $sba_message, $chamber_rows, $indvds, $values);
      }
    }
    // everything was OK.
    else {
      $update = _sba_message_api_update_group($api_call, $sba_message, $chamber_rows, $indvds, $values);
    }
    if (!empty($update->data->id)) {
      _sba_message_api_valid_response($sba_message, $update);
    }
    else {
      _sba_message_api_invalid_response($sba_message);
    }
  }
}

/**
 * @param $target_fields
 * @return array
 */
function _sba_message_api_get_gender_or_social_ids($target_fields) {

  $api_call = new AdvocacyApiCall();

  $ids = array();
  foreach ($target_fields as $fields) {
    $fields->limit = 1;
    $response = $api_call->invokeClientMethod('searchTargets', (array) $fields);

    if (!empty($response->data->ids)) {
      $ids = array_unique(array_merge($ids, $response->data->ids));
    }
  }
  return $ids;
}

/**
 * Take the chambers form input and format it for the API callback.
 * @param $unstructured_chambers
 * @return array
 */
function _sba_message_api_build_chambers($unstructured_chambers) {
  $chamber_rows_container = array();

  // An "Unstructured chambers" example:
  //    0 (Object)
  //        role => FR
  //        party => D
  //    1 (Object)
  //        role => PRES01|PRES03|GOVNR
  //    2 (Object)
  //        state => NY
  //        role => SR|SS


  //Unstructured chambers above will become:
  //0 =>
  //    chamber =>FR
  //    party  => D
  //1 =>
  //    chamber => PRES01
  //    party =>
  //2 =>
  //    chamber => PRES03
  //    party =>
  //3 =>
  //    chamber => GOVNR
  //    party =>
  //4 =>
  //    chamber => SR
  //    party =>
  //    state => NY
  //5 =>
  //    chamber => SS
  //    party =>
  //    state => NY

  foreach ($unstructured_chambers as $chamber_id => $chamber_fields) {

    //create a new container to rewrap our chambers
    $chamber_rows_container[$chamber_id] = array();

    foreach ($chamber_fields as $field_name => $chamber_field_values) {
      $chamber_field_values = explode('|', $chamber_field_values);
      if ($field_name == 'role') {
        $field_name = 'chamber';
      }

      $i = 0;
      $num = count($chamber_rows_container[$chamber_id]);

      if ($num) {
        foreach ($chamber_rows_container[$chamber_id] as $chamber_field) {
          foreach ($chamber_field_values as $value) {
            _sba_message_api_build_chambers_shmoosher($chamber_rows_container, $chamber_id, $i, $field_name, $value, $chamber_field);
            $i++;
          }
        }
      } else {
        foreach ($chamber_field_values as $value) {
          _sba_message_api_build_chambers_shmoosher($chamber_rows_container, $chamber_id, $i, $field_name, $value);
          $i++;
        }
      }
    }
  }

  $chamber_rows = array();
  foreach ($chamber_rows_container as $container)  {
    $chamber_rows = array_merge($chamber_rows, $container);
  }
  return $chamber_rows;
}

/**
 * Helper function to build chamber rows
 * @param $chamber_rows_container
 * @param $chamber_id
 * @param $i
 * @param $field_name
 * @param $value
 * @param array $chamber_field
 */
function _sba_message_api_build_chambers_shmoosher(&$chamber_rows_container, $chamber_id, $i, $field_name, $value, $chamber_field = array()) {

  // the container is passed by reference
  // make sure that values that are already set, get maintained.
  $chamber = isset($chamber_field['chamber']) ? $chamber_field['chamber'] : '';
  $party = isset($chamber_field['party']) ? $chamber_field['party'] : '';
  $state = isset($chamber_field['state']) ? $chamber_field['state'] : '';
  //$gender = isset($chamber_field['gender']) ? $chamber_field['gender'] : '';

  $chamber_rows_container[$chamber_id][$i]['chamber'] = $chamber;
  $chamber_rows_container[$chamber_id][$i]['party'] = $party;
  $chamber_rows_container[$chamber_id][$i]['state'] = $state;
  //$chamber_rows_container[$chamber_id][$i]['gender'] = $gender;

  $chamber_rows_container[$chamber_id][$i][$field_name] = $value;
}

/**
 * Create a target group and targets on the API server.
 * @param $api_call
 * @param $sba_message
 * @param $chamber_rows
 * @param $indvds
 * @param $values
 * @return mixed
 */
function _sba_message_api_create_group($api_call, $sba_message, $chamber_rows, $indvds, $values) {
  $response = $api_call->invokeClientMethod('createTargetGroup',
    array(
      'name' => $sba_message->name,
      'chambers' => $chamber_rows,
      'target_ids' => $indvds,
      'message' => array(
        'message_id' => $values['data']['message_id'],
        'form_id' => $values['advocacy_id'],
      ),
    )
  );

  return $response;
}

/**
 * Update existing message group on the API server
 * @param $api_call
 * @param $sba_message
 * @param $chamber_rows
 * @param $indvds
 * @param $values
 * @return mixed
 */
function _sba_message_api_update_group($api_call, $sba_message, $chamber_rows, $indvds, $values) {
  $response = $api_call->invokeClientMethod('updateTargetGroup',
    array(
      'name' => $sba_message->name,
      'chambers' => $chamber_rows,
      'target_ids' => $indvds,
      'message' => array(
        'message_id' => $values['data']['message_id'],
        'form_id' => $values['advocacy_id'],
      ),
    ), $sba_message->data['group_id']);

  return $response;
}

/**
 * If a group ID is missing in an existing message entity
 * try to retrieve it via the message id. This would happen if the
 * group creation fails or if the creation response was interrupted.
 *
 * @param $api_call
 * @param $message_id
 * @return mixed
 */
function _sba_message_api_get_group_by_message_id($api_call, $message_id) {
  $response = $api_call->invokeClientMethod('getTargetGroupByMessageID', $message_id);
  return $response;
}

/**
 *  Helper function to help negotiate remote
 *  or the interruption thereof.
 * @param $sba_message
 */
function _sba_message_api_invalid_response($sba_message) {
  drupal_set_message('There was a problem retrieving the group ID. Please save the message again, or try resaving at a later time.');
  $sba_message->data['group_id'] = 'no_response';
  $sba_message->save();
}

/**
 * Helper function to help negotiate remote
 * or the interruption thereof.
 * @param $sba_message
 * @param $response
 */
function _sba_message_api_valid_response($sba_message, $response) {
  $sba_message->data['group_id'] = $response->data->id;
  $sba_message->changed = time();
  $sba_message->save();
}


/**
 * @param $sba_message
 */
function _sba_message_api_delete_target_group ($sba_message) {
  //delete the remote API message group.

  $api_call = new AdvocacyApiCall();
  $response = $api_call->invokeClientMethod('deleteTargetGroup', $sba_message->data['group_id']);

  if (isset($response->data)) {
    drupal_set_message(t("The message's remote target group was deleted."));
  }
}
