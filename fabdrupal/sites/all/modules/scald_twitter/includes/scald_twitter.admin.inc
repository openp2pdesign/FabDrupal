<?php

/**
 * @file
 * Page callbacks for Scald Twitter provider.
 */

/**
 * Scald Twitter provider settings form.
 */
function scald_twitter_admin_form($form, &$form_state) {

    $form = array();

    $form['scald_twitter_oauth'] = array(
        '#type' => 'fieldset',
        '#title' => t('Scald Twitter OAuth Settings'),
        '#description' => t('Request <a href="@url">your api key here</a>.', array('@url' => 'https://dev.twitter.com/apps/new')),
    );
    $form['scald_twitter_oauth']['scald_twitter_consumer_key'] = array(
        '#type' => 'textfield',
        '#title' => t('Twitter OAuth Consumer key'),
        '#default_value' => variable_get('scald_twitter_consumer_key', NULL),
    );
    $form['scald_twitter_oauth']['scald_twitter_consumer_secret'] = array(
        '#type' => 'textfield',
        '#title' => t('Twitter OAuth Consumer secret'),
        '#default_value' => variable_get('scald_twitter_consumer_secret', NULL),
    );
    $form['scald_twitter_oauth']['scald_twitter_oauth_token'] = array(
        '#type' => 'textfield',
        '#title' => t('Twitter OAuth token'),
        '#default_value' => variable_get('scald_twitter_oauth_token', NULL),
    );
    $form['scald_twitter_oauth']['scald_twitter_oauth_token_secret'] = array(
        '#type' => 'textfield',
        '#title' => t('Twitter OAuth token secret'),
        '#default_value' => variable_get('scald_twitter_oauth_token_secret', NULL),
    );
    return system_settings_form($form);
}

function scald_twitter_admin_form_validate($form, &$form_state) {

    //checking the key
  $consumer_key = $form_state['values']['scald_twitter_consumer_key'];
  $consumer_secret = $form_state['values']['scald_twitter_consumer_secret'];
  $oauth_token = $form_state['values']['scald_twitter_oauth_token'];
  $oauth_token_secret = $form_state['values']['scald_twitter_oauth_token_secret'];
  module_load_include('inc', 'scald_twitter', 'includes/scald_twitter_connector');  
  $settings = array(
      'oauth_access_token' => $oauth_token,
      'oauth_access_token_secret' => $oauth_token_secret,
      'consumer_key' => $consumer_key,
      'consumer_secret' => $consumer_secret
      );
  $scald_twitter_oauth_request = new Scald_Twitter_oauth_request($settings)/* obj connection to Oauth */;
  $scald_twitter_oauth_request->setGetfield("?q=drupal");
  $json =  $scald_twitter_oauth_request->buildOauth(SCALD_TWITTER_SEARCH_URL, 'GET')
    ->performRequest() ;
  $tweet = json_decode($json);

  if ( isset($tweet->statuses)) {
    if (count($tweet->statuses) > 0 and is_array($tweet->statuses) ) {
      drupal_set_message(t('Authentification with twitter verified.'), 'status');
    }
    else {
      form_set_error('scald_twitter_oauth', 'Your API key are probably incorrect, we cannot authenticate with twitter.');
    }
  }
  else {
      form_set_error('scald_twitter_oauth', 'Your API key are probably incorrect, we cannot authenticate with twitter.');
  }

}

