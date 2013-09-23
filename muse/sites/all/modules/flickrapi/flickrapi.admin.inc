<?php

/**
 * @file
 * Admin settings form and OAuth authentication integration
 */

/**
 * Admin settings form
 */
function flickrapi_admin_settings() {
  $form = array();

  $api_key = variable_get('flickrapi_api_key', '');
  $form['flickrapi_api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('API Key'),
    '#required' => TRUE,
    '#default_value' => $api_key,
  );
  if (empty($api_key)) {
    $form['flickrapi_api_key']['#description'] = t('API Key from Flickr. !link', array(
      '!link' => l(t('Get one!'), 'http://www.flickr.com/services/apps/by/me'))
    );
  }
  else {
    $form['flickrapi_api_key']['#description'] = t('API Key from Flickr.');
  }

  $form['flickrapi_api_secret'] = array(
    '#type' => 'textfield',
    '#title' => t('API Shared Secret'),
    '#required' => TRUE,
    '#default_value' => variable_get('flickrapi_api_secret', ''),
    '#description' => t("API key's secret from Flickr."),
  );

  if (!_flickrapi_is_authenticated()) {
    $form['flickr_api_verified'] = array(
      'heading' => array('#markup' => t('<label>OAuth verification status</label>')),
      'image' => array(
        '#theme' => 'image',
        '#path' => drupal_get_path('module', 'flickrapi') . '/images/false.png',
        '#attributes' => array('style' => 'float: left; margin: 10px 10px 0 0; '),
      ),
      'text' => array('#markup' => '<p>' . t('Not verified yet') . '<br />' . t('Save this settings form to verify your credentials.') . '</p>'),
    );
  }
  else {
    $form['flickr_api_verified'] = array(
      'heading' => array('#markup' => t('<label>OAuth verification status</label>')),
      'image' => array(
        '#theme' => 'image',
        '#path' => drupal_get_path('module', 'flickrapi') . '/images/true.png',
        '#attributes' => array('style' => 'float: left; margin: 10px 10px 0 0; '),
      ),
      'text' => array('#markup' => '<p>' . t('Verified') . '<br />' . l(t('Delete access token'), 'admin/config/media/flickrapi/clear') . '</p>'),
    );
  }

  $times = array(
    900, 1800, 2700, 3600, 7200, 10800, 14400, 18000, 21600, 43200, 86400,
  );
  $ageoptions = drupal_map_assoc($times, 'format_interval');

  $form['advanced'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced settings'),
    '#collapsible' => TRUE,
    '#collapsed' => (
      variable_get('flickrapi_access_permissions', array('read')) == 'read' &&
      variable_get('flickrapi_cache', TRUE) == TRUE
    ) ? TRUE : FALSE,
  );

  $form['advanced']['flickrapi_access_permissions'] = array(
    '#type' => 'radios',
    '#title' => t('Flickr Access Permissions'),
    '#options' => array(
      'read' => t('Read only (default)'),
      'write' => t('Read & Write'),
      'delete' => t('Read, Write & Delete'),
    ),
    '#description' => t('If you change the access permissions after authentication, you need to re-authenticate your website.'),
    '#default_value' => variable_get('flickrapi_access_permissions', 'read'),
  );

  $form['advanced']['caching'] = array(
    '#type' => 'fieldset',
    '#title' => t('Cache settings'),
    '#description' => t('Caching can improve page loading speeds for your users if you are calling the same Flickr requests frequently. You may want to disable it for testing, to save on your own bandwidth costs, or if you have concerns about keeping images on your own server. Note that some Flickr methods enforce restrictions on the frequency with which they may be called, !documented.', array(
      '!documented' => l(t('as per the documentation'), 'http://www.flickr.com/services/api/'),
    )),
    '#collapsible' => TRUE,
  );
  $form['advanced']['caching']['flickrapi_cache'] = array(
    '#type' => 'checkbox',
    '#title' => t('Allow Flickr API to store results on your server'),
    '#default_value' => variable_get('flickrapi_cache', TRUE),
  );

  $form['advanced']['caching']['flickrapi_cache_path'] = array(
    '#title' => t('Flickr Cache Path'),
    '#description' => t('Location on the server file system where the results will be cached.'),
    '#type' => 'textfield',
    '#default_value' => variable_get('flickrapi_cache_path', variable_get('file_public_path', 'sites/default/files') . '/flickr'),
    '#states' => array(
      'visible' => array(
        ':input[name="flickrapi_cache"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['advanced']['caching']['flickrapi_cache_duration'] = array(
    '#type' => 'select',
    '#title' => t('Update Interval'),
    '#options' => $ageoptions,
    '#default_value' => variable_get('flickrapi_cache_duration', 3600),
    '#description' => t('How often you want to check cached Flickr API calls are up to date?'),
    '#states' => array(
      'visible' => array(
        ':input[name="flickrapi_cache"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['#validate'][] = 'flickrapi_admin_settings_validate';
  $form['#submit'][] = 'flickrapi_admin_settings_submit';
  return system_settings_form($form);
}

/**
 * Implements hook_form_alter().
 *
 * If the API key has not been validated yet,
 * change the button text on the admin form.
 */
function flickrapi_form_flickrapi_admin_settings_alter(&$form, &$form_state) {
  if (!_flickrapi_is_authenticated()) {
    $form['actions']['submit']['#value'] = t('Authorize using OAuth');
  }
}

/**
 * Validator for the admin settings form.
 */
function flickrapi_admin_settings_validate($form, &$form_state) {
  $key = trim($form_state['values']['flickrapi_api_key']);
  $secret = trim($form_state['values']['flickrapi_api_secret']);
  $cache = $form_state['values']['flickrapi_cache'];
  $cache_dir = $form_state['values']['flickrapi_cache_path'];

  if ($key && (preg_match('/^[A-Fa-f\d]{32}$/', $key) != 1)) {
    form_set_error('flickrapi_api_key', t('This does not appear to be a Flickr API key.'));
  }

  if ($secret && (preg_match('/^[A-Fa-f\d]{16}$/', $secret) != 1)) {
    form_set_error('flickrapi_api_secret', t('This does not appear to be a Flickr API secret.'));
  }

  if ($cache && !file_prepare_directory($cache_dir)) {
    form_set_error('flickrapi_cache_path', t('Cache folder does not exist or it is not writable.'));
  }
}

/**
 * Submit handler for the admin settings form.
 */
function flickrapi_admin_settings_submit($form, &$form_state) {
  // If the Access Permissions have changed, we need to re-authenticate.
  if ($perm_element = $form_state['complete form']['advanced']['flickrapi_access_permissions']) {
    if ($perm_element['#value'] != $perm_element['#default_value']) {
      //_flickrapi_oauth_clear();
    }
  }

  // Validate the credentials on Flickr.
  if (!_flickrapi_is_authenticated()) {
    $form_state['redirect'] = 'admin/config/media/flickrapi/authenticate';
  }
}

/**
 * Fetch a token from Flickr using the key & secret the user entered.
 *
 * This functions handles:
 *   - Signing Requests
 *   - Getting a Request Token
 *   - Getting the User Authorization
 * See: http://www.flickr.com/services/api/auth.oauth.html
 */
function flickrapi_oauth_authenticate() {
  module_load_include('module', 'oauth_common');
  $callback = url('admin/config/media/flickrapi/authenticate', array('absolute' => TRUE));

  // If the OAuth verifier token is already returned by Flickr, verify it.
  if (!empty($_GET['oauth_verifier'])) {
    flickrapi_oauth_token_verify();
  }
  else {
    // Set up a new OAuth Consumer and Client if it cannot be loaded.
    $consumer = DrupalOAuthConsumer::load(variable_get('flickrapi_api_key', ''), FALSE);
    if (!$consumer) {
      $consumer = new DrupalOAuthConsumer(variable_get('flickrapi_api_key', ''), variable_get('flickrapi_api_secret', ''));
      $consumer->write();
    }
    $sig_method = DrupalOAuthClient::signatureMethod();
    $client = new DrupalOAuthClient($consumer, NULL, $sig_method);
    try {
      if ($request_token = $client->getRequestToken('http://www.flickr.com/services/oauth/request_token', array('callback' => $callback))) {
        $request_token->write();
      }
    }
    catch (Exception $e) {
      drupal_set_message(t('You API key and secret do not seem to match.'), 'error');
      variable_del('flickrapi_api_key');
      variable_del('flickrapi_api_secret');
      drupal_goto('admin/config/media/flickrapi');
    }

    $auth_url = $client->getAuthorizationUrl(
      'http://www.flickr.com/services/oauth/authorize', array(
        'callback' => $callback,
        'params' => array(
          'perms' => variable_get('flickrapi_access_permissions', array('read')),
        ),
      )
    );

    // Send the user to the Flickr page which redirects
    // back to the Drupal site after accepting.
    drupal_goto($auth_url);
  }
}

/**
 * Verification callback to check the token we received from Flickr
 *
 * Handles the last step in the authentication proces:
 *   - Exchanging the Request Token for an Access Token
 * See http://www.flickr.com/services/api/auth.oauth.html
 */
function flickrapi_oauth_token_verify() {
  module_load_include('module', 'oauth_common');
  $consumer = DrupalOAuthConsumer::load(variable_get('flickrapi_api_key', ''), FALSE);
  $request_token = DrupalOAuthToken::loadByKey($_GET['oauth_token'], $consumer, OAUTH_COMMON_TOKEN_TYPE_REQUEST);

  $client = new DrupalOAuthClient($consumer, $request_token);
  $access_token = $client->getAccessToken('http://www.flickr.com/services/oauth/access_token', array(
    'verifier' => $_GET['oauth_verifier'])
  );

  $request_token->delete();

  drupal_set_message(t('Succesfully verified'));
  drupal_goto('admin/config/media/flickrapi');
}

/**
 * Form builder: confirm to delete OAuth authentication token.
 */
function flickrapi_oauth_clear_form($form, &$form_state) {
  return confirm_form(
    $form,
    t('Are you sure you want to delete the Flickr access token?'),
    'admin/config/media/flickrapi',
    t('This action can not be undone.'),
    t('Delete Flickr access token'),
    t('Cancel')
  );
}

/**
 * Form submit: deletes flickr credentials
 */
function flickrapi_oauth_clear_form_submit($form, &$form_state) {
  if (_flickrapi_oauth_clear()) {
    drupal_set_message(t('Flickr access token was deleted.'));
  } else {
    drupal_set_message(t('Flickr access token was not found.'), 'error');
  }
  $form_state['redirect'] = 'admin/config/media/flickrapi';
}
