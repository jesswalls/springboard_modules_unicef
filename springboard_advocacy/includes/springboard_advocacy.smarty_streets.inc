<?php

/**
 * @file
 * Lookup function for smarty streets api.
 */

/**
 * Lookup 9 digit zip code from address in form submission.
 *
 * Grab the county, fips and lat/lon too.
 *
 * @param array $values
 *   Address values from the webform submission.
 *
 * @return array
 *   An array of smarty streets data derived from the address.
 */
function springboard_advocacy_smarty_lookup(array $values) {
  $query = array(
    'street' => $values['sbp_address'],
    'city' => $values['sbp_city'],
    'state' => $values['sbp_state'],
    'zipcode' => $values['sbp_zip'],
    'auth-id' => variable_get('springboard_advocacy_smarty_authid', ''),
    'auth-token' => variable_get('springboard_advocacy_smarty_authtoken', ''),
  );

  $url = url('https://api.smartystreets.com/street-address', array('query' => $query));
  $response = drupal_http_request($url);
  $geo = array();

  if (isset($response->error)) {
    $message = isset($response->status_message) ? $response->status_message : t('Smarty Streets API åServer not responding');
    if (user_access('administer springboard advocacy')) {
      drupal_set_message(t('An error occurred when attempting to retrieve zip code information: @message', array('@message' => $message)), 'error');
    }
    watchdog('advocacy', 'An error occurred when attempting to retrieve zip code information: @message', array('@message' => $message), WATCHDOG_ERROR);
    return $geo;
  }

  if (isset($response->data)) {

    $data = json_decode($response->data);

    if (empty($data)) {
      if (user_access('administer springboard advocacy')) {
        drupal_set_message(t('A zip code + four could not be found for the address entered.'), 'error');
      }
      watchdog('advocacy', 'A zip code + four could not be found for the address entered.', array(), WATCHDOG_ERROR);

      return $geo;
    }

    if (!empty($data) && empty($data[0]->components->plus4_code)) {
      if (user_access('administer springboard advocacy')) {
        drupal_set_message(t('A plus four extension could not be found'), 'error');
      }
      watchdog('advocacy', 'A + four extension could not be found for the address entered.', array(), WATCHDOG_ERROR);
      return $geo;
    }

    if (!empty($data) && !empty($data[0]->components->plus4_code)) {
      $geo['zip'] = isset($data[0]->components->zipcode) ? $data[0]->components->zipcode : '';
      $geo['plus4'] = isset($data[0]->components->plus4_code) ? $data[0]->components->plus4_code : '';
      $geo['county'] = isset($data[0]->metadata->county_name) ? $data[0]->metadata->county_name : '';
      $geo['fips'] = isset($data[0]->metadata->county_fips) ? $data[0]->metadata->county_fips : '';
      // $district = $data[0]->metadata->congressional_district;
      $geo['latitude'] = isset($data[0]->metadata->latitude) ? $data[0]->metadata->latitude : '';
      $geo['longitude'] = isset($data[0]->metadata->longitude) ? $data[0]->metadata->longitude : '';
    }
  }
  return $geo;
}