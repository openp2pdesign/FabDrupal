<?php


/**
 * @file
 * Implementation of Twitter REST API 1.1.
 * https://dev.twitter.com/docs/api/1.1
 */

/**
 * Exception handling class.
 */
class Scald_Twitter_Oauth_connector_Exception extends Exception {

  public function __construct($message) {  
    watchdog('scald_twitter', $message, array(), WATCHDOG_WARNING );
  }
  
}
/**
 * API implementation class
 */
class Scald_Twitter_oauth_request {
  private $oauth_access_token;
  private $oauth_access_token_secret;
  private $consumer_key;
  private $consumer_secret;
  private $postfields;
  private $getfield;
  protected $oauth;
  public $url;

  /**
   * Create the API access object. Requires an array of settings::
   * oauth access token, oauth access token secret, consumer key, consumer secret
   * These are all available by creating your own application on dev.twitter.com
   * Requires the cURL library
   *
   * @param array $settings
   */
  public function __construct(array $settings) {
    if (!in_array('curl', get_loaded_extensions())) {
      throw new Scald_Twitter_Oauth_connector_Exception('You need to install cURL, see: http://curl.haxx.se/docs/install.html');
    }

    if (!isset($settings['oauth_access_token'])
        || !isset($settings['oauth_access_token_secret'])
        || !isset($settings['consumer_key'])
        || !isset($settings['consumer_secret'])) {
      throw new Scald_Twitter_Oauth_connector_Exception('Make sure you are passing in the correct parameters');
    }

    $this->oauth_access_token = $settings['oauth_access_token'];
    $this->oauth_access_token_secret = $settings['oauth_access_token_secret'];
    $this->consumer_key = $settings['consumer_key'];
    $this->consumer_secret = $settings['consumer_secret'];
  }

  /**
   * Set postfields array, example: array('screen_name' => 'J7mbo')
   *
   * @param array $array Array of parameters to send to API
   *
   * @return TwitterAPIExchange Instance of self for method chaining
   */
  public function setPostfields(array $array) {
    if (!is_null($this->getGetfield())) {
      throw new Scald_Twitter_Oauth_connector_Exception('You can only choose get OR post fields.');
    }

    $this->postfields = $array;

    return $this;
  }

  /**
   * Set getfield string, example: '?screen_name=J7mbo'
   *
   * @param string $string Get key and value pairs as string
   *
   * @return \TwitterAPIExchange Instance of self for method chaining
   */
  public function setGetfield($string) {
    if (!is_null($this->getPostfields())) {
      throw new Scald_Twitter_Oauth_connector_Exception('You can only choose get OR post fields.');
    }

    $search = array('#', ',', '+', ':');
    $replace = array('%23', '%2C', '%2B', '%3A');
    $string = str_replace($search, $replace, $string);

    $this->getfield = $string;

    return $this;
  }

  /**
   * Get getfield string (simple getter)
   *
   * @return string $this->getfields
   */
  public function getGetfield() {
    return $this->getfield;
  }

  /**
   * Get postfields array (simple getter)
   *
   * @return array $this->postfields
   */
  public function getPostfields() {
    return $this->postfields;
  }

  /**
   * Build the Oauth object using params set in construct and additionals
   * passed to this method. For v1.1, see: https://dev.twitter.com/docs/api/1.1
   *
   * @param string $url The API url to use. Example: https://api.twitter.com/1.1/search/tweets.json
   * @param string $requestMethod Either POST or GET
   * @return \TwitterAPIExchange Instance of self for method chaining
   */
  public function buildOauth($url, $requestMethod) {
    if (!in_array(strtolower($requestMethod), array('post', 'get'))) {
      throw new Scald_Twitter_Oauth_connector_Exception('Request method must be either POST or GET');
    }

    $consumer_key = $this->consumer_key;
    $consumer_secret = $this->consumer_secret;
    $oauth_access_token = $this->oauth_access_token;
    $oauth_access_token_secret = $this->oauth_access_token_secret;

    $oauth = array(
        'oauth_consumer_key' => $consumer_key,
        'oauth_nonce' => md5(time()),
        'oauth_signature_method' => 'HMAC-SHA1',
        'oauth_token' => $oauth_access_token,
        'oauth_timestamp' => time(),
        'oauth_version' => '1.0'
        );

    $getfield = $this->getGetfield();

    if (!is_null($getfield)) {
      $getfields = str_replace('?', '', explode('&', $getfield));
      foreach ($getfields as $g) {
        $split = explode('=', $g);
        $oauth[$split[0]] = $split[1];
      }
    }

    $base_info = $this->buildBaseString($url, $requestMethod, $oauth);
    $composite_key = rawurlencode($consumer_secret) . '&' . rawurlencode($oauth_access_token_secret);
    $oauth_signature = base64_encode(hash_hmac('sha1', $base_info, $composite_key, TRUE));
    //$oauth['oauth_signature'] = rawurlencode($oauth_signature);
    $oauth['oauth_signature'] = $oauth_signature;
    ksort($oauth);

    $this->url = $url;
    $this->oauth = $oauth;

    return $this;
  }

  /**
   * Perform the acual data retrieval from the API
   *
   * @param boolean $return If true, returns data.
   *
   * @return json If $return param is true, returns json data.
   */
  public function performRequest($return = TRUE) {
    if (!is_bool($return)) {
      throw new Scald_Twitter_Oauth_connector_Exception('performRequest parameter must be true or false');
    }

    $header = array($this->buildAuthorizationHeader($this->oauth));

    $getfield = $this->getGetfield();
    $postfields = $this->getPostfields();

    $options = array(
        CURLOPT_HTTPHEADER => $header,
        CURLOPT_HEADER => FALSE,
        CURLOPT_HTTPGET => TRUE,
        CURLOPT_URL => $this->url,
        CURLOPT_RETURNTRANSFER => TRUE,
        );

    if (!is_null($postfields)) {
      $options[CURLOPT_POSTFIELDS] = $postfields;
    }
    else {
      if ($getfield !== '') {
        $options[CURLOPT_URL] .= $getfield;
      }
    }

    $feed = curl_init();
    curl_setopt_array($feed, $options);
    $json = curl_exec($feed);
    curl_close($feed);
    if ($json) { 
      return $json; 
    }
    else {
      throw new Scald_Twitter_Oauth_connector_Exception('Cannot read tweets from twitter');
    }
  }

  /**
   * Private method to generate the base string used by cURL
   *
   * @param string $baseURI
   * @param string $method
   * @param string $params
   *
   * @return string Built base string
   */
  private function buildBaseString($baseURI, $method, $params) {
    $return = array();
    ksort($params);
    $baseURI = preg_replace('/\?.*/', '', $baseURI);

    foreach ($params as $key => $value) {
      $return[] = "$key=" . $value;
    }

    return $method . "&" . rawurlencode($baseURI) . '&' . rawurlencode(implode('&', $return));
  }

  /**
   * Private method to generate authorization header used by cURL
   *
   * @param array $oauth Array of oauth data generated by buildOauth()
   *
   * @return string $return Header used by cURL for request
   */
  private function buildAuthorizationHeader($oauth) {
    $return = 'Authorization: OAuth ';
    $values = array();

    foreach ($oauth as $key => $value) {
      if (preg_match('/oauth/', $key)) {
        $values[] = "$key=\"" . rawurlencode($value) . "\"";
      }
    }

    $return .= implode(', ', $values);
    return $return;
  }
}

