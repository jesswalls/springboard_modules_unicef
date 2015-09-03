<?php
/**
 * @file
 * Loads and instantiates an SpringboardAdvocacyApiClient object.
 */

/**
 * Class AdvocacyApiClientLoader.
 */
class AdvocacyApiClientLoader {

  /**
   * Get the SDK Client.
   *
   * @return \SpringboardAdvocacyAPIClient
   *   A client object.
   */
  public function getClient() {
    libraries_load('springboard_advocacy');
    $domain = variable_get('springboard_advocacy_server_url', '');
    $client = new SpringboardAdvocacyAPIClient($domain);
    $debug = variable_get('springboard_advocacy_debug', '');
    if (!empty($debug)) {
      $client->enableDebugMode();
    }
    $token = $this->getToken($client);
    if (!empty($token->access_token)) {
      $client->setToken($token->access_token);
    }
    else {
      if (!empty($token->error)) {
        drupal_set_message('Springboard Advocacy: ' . implode('. ', (array) $token));
        watchdog('advocacy', 'An error occurred when attempting to set an api token', array('@message' => implode('. ', (array) $token)), WATCHDOG_ERROR);
      }
    }

    return $client;
  }

  /**
   * Get or Refresh an Oauth access token.
   *
   * @param SpringboardAdvocacyAPIClient $client
   *    The ApiClient object.
   *
   * @return Object
   *   An access token object.
   */
  private function getToken(SpringboardAdvocacyAPIClient $client) {
    $token = variable_get('springboard_advocacy_access_token', array());
    if (!empty($token->access_token)) {
      $refresh = ($token->created < (time() - ($token->expires_in - 600)));
    }
    if (empty($token->access_token) || !empty($refresh)) {
      $client_id = variable_get('springboard_advocacy_client_id', '');
      $client_secret = variable_get('springboard_advocacy_client_secret', '');
      $token = $client->getToken($client_id, $client_secret);

      if (!empty($token->access_token)) {
        $token->created = time();
        variable_set('springboard_advocacy_access_token', $token);
        return $token;
      }
    }
    return $token;
  }
}