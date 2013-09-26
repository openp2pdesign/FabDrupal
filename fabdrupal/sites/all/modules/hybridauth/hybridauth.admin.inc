<?php
/**
 * @file
 * Administrative pages forms and functions for the HybridAuth module.
 */

function hybridauth_admin_settings() {
  if (!variable_get('hybridauth_register', 0) && variable_get('user_register', USER_REGISTER_VISITORS_ADMINISTRATIVE_APPROVAL) == USER_REGISTER_ADMINISTRATORS_ONLY) {
    drupal_set_message(t('Currently only administrators can create new user accounts. Either change the "Who can register accounts?" option under "Account settings" tab or at the core <a href="!link">Account settings</a>.',
      array('!link' => url('admin/config/people/accounts'))), 'warning');
  }

  $form = array();
  $form['vtabs'] = array(
    '#type' => 'vertical_tabs',
    '#attached' => array(
      'js' => array(drupal_get_path('module', 'hybridauth') . '/js/hybridauth.admin.js'),
    ),
  );

  $form['vtabs']['fset_providers'] = array(
    '#type' => 'fieldset',
    '#title' => t('Authentication providers'),
    '#theme' => 'hybridauth_admin_settings_providers_table',
  );
  foreach (hybridauth_providers_list() as $provider_id => $provider_name) {
    $form['vtabs']['fset_providers'][$provider_id]['icon'] = array(
      '#theme' => 'hybridauth_provider_icon',
      '#provider_id' => $provider_id,
      '#icon_pack' => 'hybridauth_16',
    );
    $form['vtabs']['fset_providers'][$provider_id]['hybridauth_provider_' . $provider_id . '_enabled'] = array(
      '#type' => 'checkbox',
      '#title' => drupal_placeholder($provider_name),
      '#default_value' => variable_get('hybridauth_provider_' . $provider_id . '_enabled', 0),
    );
    $form['vtabs']['fset_providers'][$provider_id]['file'] = array(
      '#markup' => array_key_exists($provider_id, hybridauth_providers_files()) ? t('Yes') : t('No'),
    );
    $form['vtabs']['fset_providers'][$provider_id]['hybridauth_provider_' . $provider_id . '_weight'] = array(
      '#type' => 'weight',
      // '#title' => t('Weight'),
      '#delta' => 20,
      '#default_value' => variable_get('hybridauth_provider_' . $provider_id . '_weight', 0),
      '#attributes' => array('class' => array('hybridauth-provider-weight')),
    );
    $form['vtabs']['fset_providers'][$provider_id]['settings'] = array(
      '#type' => 'link',
      '#title' => t('Settings'),
      '#href' => 'admin/config/people/hybridauth/provider/' . $provider_id,
      '#options' => array(
        'query' => drupal_get_destination(),
      ),
    );
  }

  $form['vtabs']['fset_fields'] = array(
    '#type' => 'fieldset',
    '#title' => t('Required information'),
  );
  $form['vtabs']['fset_fields']['hybridauth_required_fields'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Required information'),
    '#options' => array(
      'email' => t('Email address'),
      'firstName' => t('First name'),
      'lastName' => t('Last name'),
      'gender' => t('Gender'),
    ),
    '#description' => t("If authentication provider doesn't return it, visitor will need to fill additional form before registration."),
    '#default_value' => variable_get('hybridauth_required_fields', array('email' => 'email')),
  );

  $form['vtabs']['fset_widget'] = array(
    '#type' => 'fieldset',
    '#title' => t('Widget settings'),
  );
  $form['vtabs']['fset_widget']['hybridauth_widget_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Widget title'),
    '#default_value' => variable_get('hybridauth_widget_title', 'Or log in with...'),
  );
  $options = array(
    'list' => t('Enabled providers icons'),
    'button' => t('Single icon leading to a list of enabled providers'),
    'link' => t('Link leading to a list of enabled providers'),
  );
  $form['vtabs']['fset_widget']['hybridauth_widget_type'] = array(
    '#type' => 'radios',
    '#title' => t('Widget type'),
    '#options' => $options,
    '#default_value' => variable_get('hybridauth_widget_type', 'list'),
  );
  $form['vtabs']['fset_widget']['hybridauth_widget_use_overlay'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display list of enabled providers using overlay'),
    '#default_value' => variable_get('hybridauth_widget_use_overlay', 1),
    '#states' => array(
      'invisible' => array(
        ':input[name="hybridauth_widget_type"]' => array('value' => 'list'),
      ),
    ),
  );
  $form['vtabs']['fset_widget']['hybridauth_widget_link_text'] = array(
    '#type' => 'textfield',
    '#title' => t('Link text'),
    '#default_value' => variable_get('hybridauth_widget_link_text', 'Social network account'),
    '#states' => array(
      'visible' => array(
        ':input[name="hybridauth_widget_type"]' => array('value' => 'link'),
      ),
    ),
  );
  $form['vtabs']['fset_widget']['hybridauth_widget_link_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Link or icon title'),
    '#default_value' => variable_get('hybridauth_widget_link_title', 'Social network account'),
    '#states' => array(
      'invisible' => array(
        ':input[name="hybridauth_widget_type"]' => array('value' => 'list'),
      ),
    ),
  );
  $options = array();
  foreach (hybridauth_get_icon_packs() as $name => $icon_pack) {
    $options[$name] = $icon_pack['title'];
  }
  $form['vtabs']['fset_widget']['hybridauth_widget_icon_pack'] = array(
    '#type' => 'select',
    '#title' => t('Icon package'),
    '#options' => $options,
    '#default_value' => variable_get('hybridauth_widget_icon_pack', 'hybridauth_32'),
  );
  $form['vtabs']['fset_widget']['hybridauth_widget_weight'] = array(
    '#type' => 'weight',
    '#title' => t('Widget weight'),
    '#delta' => 100,
    '#description' => t('Determines the order of the elements on the form - heavier elements get positioned later.'),
    '#default_value' => variable_get('hybridauth_widget_weight', 100),
  );

  $form['vtabs']['fset_account'] = array(
    '#type' => 'fieldset',
    '#title' => t('Account settings'),
  );
  $core_settings = array(
    USER_REGISTER_ADMINISTRATORS_ONLY => t('Administrators only'),
    USER_REGISTER_VISITORS => t('Visitors'),
    USER_REGISTER_VISITORS_ADMINISTRATIVE_APPROVAL => t('Visitors, but administrator approval is required'),
  );
  $form['vtabs']['fset_account']['hybridauth_register'] = array(
    '#type' => 'radios',
    '#title' => t('Who can register accounts?'),
    '#options' => array(
      0 => t('Follow core') . ': ' . $core_settings[variable_get('user_register', USER_REGISTER_VISITORS_ADMINISTRATIVE_APPROVAL)],
      1 => t('Visitors'),
      2 => t('Visitors, but administrator approval is required'),
    ),
    '#description' => t('Select who can register accounts through HybridAuth.') . ' '
      . t('The core settings are available at <a href="!link">Account settings</a>.',
        array('!link' => url('admin/config/people/accounts'))),
    '#default_value' => variable_get('hybridauth_register', 0),
  );
  $core_settings = array(
    0 => t("Don't require e-mail verification"),
    1 => t('Require e-mail verification'),
  );
  $form['vtabs']['fset_account']['hybridauth_email_verification'] = array(
    '#type' => 'radios',
    '#title' => t('E-mail verification'),
    '#options' => array(
      0 => t('Follow core') . ': ' . $core_settings[variable_get('user_email_verification', TRUE)],
      1 => t('Require e-mail verification'),
      2 => t("Don't require e-mail verification"),
    ),
    '#description' => t('Select how to handle not verified e-mail addresses (authentication provider gives non-verified e-mail address).') . ' '
      . t('The core settings are available at <a href="!link">Account settings</a>.',
        array('!link' => url('admin/config/people/accounts'))),
    '#default_value' => variable_get('hybridauth_email_verification', 0),
  );
  $form['vtabs']['fset_account']['hybridauth_pictures'] = array(
    '#type' => 'checkbox',
    '#title' => t('Save HybridAuth provided picture as user picture'),
    '#description' => t('Save pictures provided by HybridAuth as user pictures. Check the "Enable user pictures" option at <a href="!link">Account settings</a> to make this option available.',
      array('!link' => url('admin/config/people/accounts'))),
    '#default_value' => variable_get('hybridauth_pictures', 1),
    '#disabled' => !variable_get('user_pictures', 0),
  );
  $form['vtabs']['fset_account']['hybridauth_username'] = array(
    '#type' => 'textfield',
    '#title' => t('Username pattern'),
    '#default_value' => variable_get('hybridauth_username', 'hybridauth_[user:hybridauth:provider]_[user:hybridauth:identifier]'),
    '#description' => t('Create username for new users using this pattern; counter will be added in case of username conflict.') . ' '
      . t('You should use only HybridAuth tokens here as the user is not created yet.') . ' '
      . t('Install !link module to get list of all available tokens.',
        array('!link' => l(t('Token'), 'http://drupal.org/project/token', array('attributes' => array('target' => '_blank'))))),
    '#required' => TRUE,
  );
  $form['vtabs']['fset_account']['hybridauth_registration_username_change'] = array(
    '#type' => 'checkbox',
    '#title' => t('Allow username change when registering'),
    '#description' => t('Allow users to change their username when registering through HybridAuth.'),
    '#default_value' => variable_get('hybridauth_registration_username_change', 0),
  );
  $form['vtabs']['fset_account']['hybridauth_display_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Display name pattern'),
    '#default_value' => variable_get('hybridauth_display_name', '[user:hybridauth:firstName] [user:hybridauth:lastName]'),
    '#description' => t('You can use any user tokens here.') . ' '
      . t('Install !link module to get list of all available tokens.',
        array('!link' => l(t('Token'), 'http://drupal.org/project/token', array('attributes' => array('target' => '_blank'))))),
    '#required' => TRUE,
  );
  if (module_exists('token')) {
    $form['vtabs']['fset_account']['fset_token'] = array(
      '#type' => 'fieldset',
      '#title' => t('Token'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['vtabs']['fset_account']['fset_token']['hybridauth_token_tree'] = array(
      '#theme' => 'token_tree',
      '#token_types' => array('user'),
      '#global_types' => FALSE,
    );
  }
  $form['vtabs']['fset_account']['hybridauth_override_realname'] = array(
    '#type' => 'checkbox',
    '#title' => t('Override Real name'),
    '#description' => t('Override <a href="!link1">Real name settings</a> using the above display name pattern for users created by HybridAuth. This option is available only if !link2 module is installed.',
      array('!link1' => url('admin/config/people/realname'),
        '!link2' => l(t('Real name'), 'http://drupal.org/project/realname', array('attributes' => array('target' => '_blank'))))),
    '#default_value' => variable_get('hybridauth_override_realname', 0),
    '#disabled' => !module_exists('realname'),
  );
  $form['vtabs']['fset_account']['hybridauth_disable_username_change'] = array(
    '#type' => 'checkbox',
    '#title' => t('Disable username change'),
    '#description' => t('Remove username field from user account edit form for users created by HybridAuth.'
      . ' If this is unchecked then users should also have "Change own username" permission to actually be able to change the username.'),
    '#default_value' => variable_get('hybridauth_disable_username_change', 1),
  );
  $form['vtabs']['fset_account']['hybridauth_remove_password_fields'] = array(
    '#type' => 'checkbox',
    '#title' => t('Remove password fields'),
    '#description' => t('Remove password fields from user account edit form for users created by HybridAuth.'),
    '#default_value' => variable_get('hybridauth_remove_password_fields', 1),
  );

  $form['vtabs']['fset_forms'] = array(
    '#type' => 'fieldset',
    '#title' => t('Drupal forms'),
  );
  $form['vtabs']['fset_forms']['hybridauth_forms'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Drupal forms'),
    '#options' => hybridauth_forms_list(),
    '#description' => t('Add HybridAuth widget to these forms.'),
    '#default_value' => variable_get('hybridauth_forms', array('user_login', 'user_login_block')),
  );

  $form['vtabs']['fset_other'] = array(
    '#type' => 'fieldset',
    '#title' => t('Other settings'),
  );
  $options = array(
    'current' => t('Use the current window'),
    'popup' => t('Use a new popup window'),
  );
  $form['vtabs']['fset_other']['hybridauth_window_type'] = array(
    '#type' => 'radios',
    '#title' => t('Authentication window type'),
    '#options' => $options,
    '#default_value' => variable_get('hybridauth_window_type', 'current'),
  );
  $form['vtabs']['fset_other']['hybridauth_destination'] = array(
    '#type' => 'textfield',
    '#title' => t('Redirect after login'),
    '#default_value' => variable_get('hybridauth_destination', ''),
    '#description' => t('Drupal path to redirect to, like "node/1". Leave empty to return to the same page.') . ' '
      . t('You can use any user or global tokens here.') . ' '
      . t('Install !link module to get list of all available tokens.',
        array('!link' => l(t('Token'), 'http://drupal.org/project/token', array('attributes' => array('target' => '_blank'))))),
  );
  if (module_exists('token')) {
    $form['vtabs']['fset_other']['fset_token'] = array(
      '#type' => 'fieldset',
      '#title' => t('Token'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['vtabs']['fset_other']['fset_token']['hybridauth_token_tree'] = array(
      '#theme' => 'token_tree',
      '#token_types' => array('user'),
      '#global_types' => TRUE,
    );
  }
  $options = array(
    0 => t('Allow duplicate email addresses, create new user account and login'),
    1 => t("Don't allow duplicate email addresses, block registration and advise to login using the existing account"),
    2 => t("Don't allow duplicate email addresses, add new identity to the existing account and login"),
  );
  $form['vtabs']['fset_other']['hybridauth_duplicate_emails'] = array(
    '#type' => 'radios',
    '#title' => t('Duplicate emails'),
    '#options' => $options,
    '#default_value' => variable_get('hybridauth_duplicate_emails', 1),
    '#description' => t('Select how to handle duplicate email addresses. '
      . 'This situation occurs when the same user is trying to authenticate using different authentication providers, but with the same email address.'),
  );
  $form['vtabs']['fset_other']['hybridauth_debug'] = array(
    '#type' => 'checkbox',
    '#title' => t('Debug mode'),
    '#description' => t('When in debug mode, extra error information will be logged/displayed. This should be disabled when not in development.'),
    '#default_value' => variable_get('hybridauth_debug', FALSE),
  );

  return system_settings_form($form);
}

/**
 * Theme function for hybridauth_admin_settings() to render providers table.
 */
function theme_hybridauth_admin_settings_providers_table($vars) {
  $form = $vars['form'];

  $header = array(
    array('data' => t('Name'), 'colspan' => 2),
    t('Available'),
    t('Weight'),
    t('Operations'),
  );
  $rows = array();

  foreach (element_children($form) as $provider_id) {
    if (isset($form[$provider_id]['icon'])) {
      $row = array(
        drupal_render($form[$provider_id]['hybridauth_provider_' . $provider_id . '_enabled']),
        drupal_render($form[$provider_id]['icon']),
        drupal_render($form[$provider_id]['file']),
        drupal_render($form[$provider_id]['hybridauth_provider_' . $provider_id . '_weight']),
        drupal_render($form[$provider_id]['settings']),
      );

      $rows[] = array(
        'data' => $row,
        'class' => array('draggable'),
      );
    }
  }

  // Finally, output the sortable table. Make sure the id variable is the same
  // as the table id in drupal_add_tabledrag().
  $output = theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'hybridauth-providers')));
  $output .= drupal_render_children($form);

  // This function is the instantiator of the sorter. Make sure the 0th
  // parameter is the id of your table, and the 3rd parameter is the class of
  // your weight variable.
  drupal_add_tabledrag('hybridauth-providers', 'order', 'sibling', 'hybridauth-provider-weight');

  return $output;
}

function hybridauth_admin_provider_settings($form, &$form_state, $provider_id = NULL) {
  $form = array();

  switch ($provider_id) {
    case 'Facebook':
      $help = t('
          <p>Enter your application ID and private key. You can get these by creating a new application at <a href="!apps_uri">!apps_uri</a>.</p>
          <p>You must set <strong>App Domain</strong> to something like <strong>example.com</strong> to cover <strong>*.example.com</strong>.</p>
          <p>You must set <strong>Site URL</strong> to <strong>%site_uri</strong>.</p>
        ',
        array(
          '!apps_uri' => 'https://developers.facebook.com/apps',
          '%site_uri' => url('<front>', array('absolute' => TRUE)),
        )
      );
      break;

    case 'Twitter':
      $help = t('
          <p>Enter your consumer key and private key. You can get these by creating a new application at <a href="!apps_uri">!apps_uri</a>.</p>
        ',
        array(
          '!apps_uri' => 'https://dev.twitter.com/apps',
        )
      );
      break;

    case 'Google':
      $origin_uri_parts = parse_url(url('<front>', array('absolute' => TRUE)));
      $help = t('
          <p>Enter your application ID and private key. You can get these by creating a new application at <a href="!apps_uri">!apps_uri</a>.</p>
          <p>You must set <strong>Authorized Redirect URIs</strong> to <strong>%redirect_uri</strong>.</p>
          <p>You must set <strong>Authorized JavaScript Origins</strong> to <strong>%origin_uri</strong>.</p>
        ',
        array(
          '!apps_uri' => 'https://code.google.com/apis/console#access',
          '%redirect_uri' => url('hybridauth/endpoint', array('absolute' => TRUE, 'query' => array('hauth.done' => 'Google'))),
          '%origin_uri' => $origin_uri_parts['scheme'] . '://' . $origin_uri_parts['host'],
        )
      );
      break;

    default:
      $help = t('Enter the application ID, consumer key, and/or secret key as required.');
  }

  $form['keys'] = array(
    '#type' => 'fieldset',
    '#description' => $help,
  );
  $form['keys']['hybridauth_provider_' . $provider_id . '_keys_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Application ID'),
    '#description' => t('The application ID'),
    '#default_value' => variable_get('hybridauth_provider_' . $provider_id . '_keys_id', ''),
  );
  $form['keys']['hybridauth_provider_' . $provider_id . '_keys_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Application consumer key'),
    '#description' => t('The Application consumer key'),
    '#default_value' => variable_get('hybridauth_provider_' . $provider_id . '_keys_key', ''),
  );
  $form['keys']['hybridauth_provider_' . $provider_id . '_keys_secret'] = array(
    '#type' => 'textfield',
    '#title' => t('Application consumer secret'),
    '#description' => t('The application consumer secret key'),
    '#default_value' => variable_get('hybridauth_provider_' . $provider_id . '_keys_secret', ''),
  );

  if (in_array($provider_id, array('LinkedIn', 'MySpace', 'Twitter', 'Yahoo'))) {
    unset($form['keys']['hybridauth_provider_' . $provider_id . '_keys_id']);
  }
  if (in_array($provider_id, array('Facebook', 'Google', 'Live', 'Vkontakte'))) {
    unset($form['keys']['hybridauth_provider_' . $provider_id . '_keys_key']);
  }

  if ($provider_id == 'Facebook') {
    $form['advanced'] = array(
      '#type' => 'fieldset',
      '#title' => 'Advanced settings',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['advanced']['hybridauth_provider_' . $provider_id . '_scope'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Scope - Permissions to request by default'),
      '#default_value' => variable_get('hybridauth_provider_' . $provider_id . '_scope', array(
        'email', 'user_about_me', 'user_birthday', 'user_hometown', 'user_website', 'offline_access',
      )),
      '#options' => array(
        // See http://developers.facebook.com/docs/reference/api/permissions/
        // Regular permissions.
        'user_about_me'             => '<strong>user_about_me</strong> -- ' . t('Provides access to the "About Me" section of the profile in the about property'),
        'user_activities'           => '<strong>user_activities</strong> -- ' . t("Provides access to the user's list of activities as the activities connection"),
        'user_birthday'             => '<strong>user_birthday</strong> -- ' . t('Provides access to the birthday with year as the birthday_date property'),
        'user_checkins'             => '<strong>user_checkins</strong> -- ' . t("Provides read access to the authorized user's check-ins that the user can see."),
        'user_education_history'    => '<strong>user_education_history</strong> -- ' . t('Provides access to education history as the education property'),
        'user_events'               => '<strong>user_events</strong> -- ' . t('Provides access to the list of events the user is attending as the events connection'),
        'user_groups'               => '<strong>user_groups</strong> -- ' . t('Provides access to the list of groups the user is a member of as the groups connection'),
        'user_hometown'             => '<strong>user_hometown</strong> -- ' . t("Provides access to the user's hometown in the hometown property"),
        'user_interests'            => '<strong>user_interests</strong> -- ' . t("Provides access to the user's list of interests as the interests connection"),
        'user_likes'                => '<strong>user_likes</strong> -- ' . t('Provides access to the list of all of the pages the user has liked as the likes connection'),
        'user_location'             => '<strong>user_location</strong> -- ' . t("Provides access to the user's current location as the location property"),
        'user_notes'                => '<strong>user_notes</strong> -- ' . t("Provides access to the user's notes as the notes connection"),
        'user_online_presence'      => '<strong>user_online_presence</strong> -- ' . t("Provides access to the user's online/offline presence"),
        'user_photos'               => '<strong>user_photos</strong> -- ' . t('Provides access to the photos the user has uploaded, and photos the user has been tagged in'),
        'user_questions'            => '<strong>user_questions</strong> -- ' . t('Provides access to the questions the user or friend has asked'),
        'user_relationships'        => '<strong>user_relationships</strong> -- ' . t("Provides access to the user's family and personal relationships and relationship status"),
        'user_relationship_details' => '<strong>user_relationship_details</strong> -- ' . t("Provides access to the user's relationship preferences"),
        'user_religion_politics'    => '<strong>user_religion_politics</strong> -- ' . t("Provides access to the user's religious and political affiliations"),
        'user_status'               => '<strong>user_status</strong> -- ' . t("Provides access to the user's most recent status message"),
        'user_videos'               => '<strong>user_videos</strong> -- ' . t('Provides access to the videos the user has uploaded, and videos the user has been tagged in'),
        'user_website'              => '<strong>user_website</strong> -- ' . t("Provides access to the user's web site URL"),
        'user_work_history'         => '<strong>user_work_history</strong> -- ' . t('Provides access to work history as the work property'),
        'email'                     => '<strong>email</strong> -- ' . t("Provides access to the user's primary email address in the email property. Do not spam users. Your use of email must comply both with Facebook policies and with the CAN-SPAM Act."),

        // Extended permissions.
        'read_friendlists'     => '<strong>read_friendlists</strong> -- ' . t("Provides access to any friend lists the user created. All user's friends are provided as part of basic data, this extended permission grants access to the lists of friends a user has created, and should only be requested if your application utilizes lists of friends."),
        'read_insights'        => '<strong>read_insights</strong> -- ' . t('Provides read access to the Insights data for pages, applications, and domains the user owns.'),
        'read_mailbox'         => '<strong>read_mailbox</strong> -- ' . t("Provides the ability to read from a user's Facebook Inbox."),
        'read_requests'        => '<strong>read_requests</strong> -- ' . t("Provides read access to the user's friend requests"),
        'read_stream'          => '<strong>read_stream</strong> -- ' . t("Provides access to all the posts in the user's News Feed and enables your application to perform searches against the user's News Feed"),
        'xmpp_login'           => '<strong>xmpp_login</strong> -- ' . t('Provides applications that integrate with Facebook Chat the ability to log in users.'),
        'ads_management'       => '<strong>ads_management</strong> -- ' . t('Provides the ability to manage ads and call the Facebook Ads API on behalf of a user.'),
        'create_event'         => '<strong>create_event</strong> -- ' . t("Enables your application to create and modify events on the user's behalf"),
        'manage_friendlists'   => '<strong>manage_friendlists</strong> -- ' . t("Enables your app to create and edit the user's friend lists."),
        'manage_notifications' => '<strong>manage_notifications</strong> -- ' . t('Enables your app to read notifications and mark them as read. This permission will be required to all access to notifications after October 22, 2011.'),
        'offline_access'       => '<strong>offline_access</strong> -- ' . t('Enables your app to perform authorized requests on behalf of the user at any time. By default, most access tokens expire after a short time period to ensure applications only make requests on behalf of the user when the are actively using the application. This permission makes the access token returned by our OAuth endpoint long-lived.'),
        'publish_checkins'     => '<strong>publish_checkins</strong> -- ' . t('Enables your app to perform checkins on behalf of the user.'),
        'publish_stream'       => '<strong>publish_stream</strong> -- ' . t("Enables your app to post content, comments, and likes to a user's stream and to the streams of the user's friends. With this permission, you can publish content to a user's feed at any time, without requiring offline_access. However, please note that Facebook recommends a user-initiated sharing model."),
        'rsvp_event'           => '<strong>rsvp_event</strong> -- ' . t("Enables your application to RSVP to events on the user's behalf"),
        'sms'                  => '<strong>sms</strong> -- ' . t('Enables your application to send messages to the user and respond to messages from the user via text message'),
        'publish_actions'      => '<strong>publish_actions</strong> -- ' . t('Enables your application to publish user scores and achievements.'),
      ),
    );
  }

  return system_settings_form($form);
}

/**
 * Renders report on HybridAuth identities.
 */
function hybridauth_report() {
  $providers = hybridauth_providers_list();

  $header = array(t('Authentication provider'), t('Users count'));
  $rows = array();
  $query = db_select('hybridauth_identity', 'ha_id');
  $query->addField('ha_id', 'provider', 'provider');
  $query->addExpression('COUNT(provider_identifier)', 'count');
  $query->groupBy('provider');
  $results = $query
    ->execute()
    ->fetchAllAssoc('provider', PDO::FETCH_ASSOC);
  foreach ($results as $result) {
    $rows[] = array(
      $providers[$result['provider']],
      $result['count'],
    );
  }

  $form = array();
  $form['report'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
  );
  return $form;
}
