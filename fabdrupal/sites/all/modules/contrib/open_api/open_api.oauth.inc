<?php
/**
 * @file
 * open_api.oauth.inc
 */

/**
 * Implements hook_default_oauth_common_context().
 */
function open_api_default_oauth_common_context() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 1;
  $context->name = 'authentication';
  $context->title = 'Authentication';
  $context->authorization_options = array(
    'access_token_lifetime' => NULL,
    'page_title' => NULL,
    'message' => 'Hi @user!
Click on the Login button to log in to @appname. This will give @appname access to your account (without disclosing your password).',
    'warning' => NULL,
    'deny_access_title' => 'Cancel',
    'grant_access_title' => 'Log in',
    'disable_auth_level_selection' => NULL,
    'signature_methods' => array(
      0 => 'HMAC-SHA1',
      1 => 'HMAC-SHA256',
      2 => 'HMAC-SHA384',
      3 => 'HMAC-SHA512',
    ),
    'default_authorization_levels' => array(),
  );
  $context->authorization_levels = array();
  $export['authentication'] = $context;

  return $export;
}
