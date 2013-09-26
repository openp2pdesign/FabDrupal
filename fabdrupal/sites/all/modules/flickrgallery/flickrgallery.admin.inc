<?php
/**
 * @file
 * Administration page callbacks
 */

/**
 * Administration settings form
 */
function flickrgallery_settings_form() {
  $form = array();

  drupal_set_title(t('Flickr Gallery Settings'));

  $options = array(
    's'  => t('small square 75x75'),
    'q'  => t('large square 150x150'),
    't'  => t('thumbnail, 100 on longest side'),
    'm'  => t('small, 240 on longest side'),
    'n'  => t('small, 320 on longest side'),
    '-'  => t('medium, 500 on longest side'),
    'z'  => t('medium 640, 640 on longest side'),
    'c'  => t('medium 800, 800 on longest side†'),
    'b'  => t('large, 1024 on longest side'),
  );

  $sizes = array(
    "square" => t('small square 75x75'),
    "large_square" => t('small square 150x150'),
    "thumbnail" => t('thumbnail, 100 on longest side'),
    "small_240" => t('small, 240 on longest side'),
    "small_320" => t('small, 320 on longest side'),
    "medium_-" => t('small, 500 on longest side'),
    "medium_640" => t('medium 640, 640 on longest side'),
    "medium_800" => t('medium 800, 800 on longest side'),
    "large" =>  t('large, 1024 on longest side'),
  );

  $form['flickrgallery_userID'] = array(
    '#type' => 'textfield',
    '#title' => t('User ID'),
    '#description' => t('Fill in the user ID or e-mail of the Flickr account.') . ' ' . l(t('Find your User ID'), 'http://idgettr.com/'),
    '#default_value' => variable_get('flickrgallery_userID', NULL),
  );
  
  $form['flickrgallery_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title sets page'),
    '#description' => t('Provide a title for the sets page.'),
    '#default_value' => t(variable_get('flickrgallery_title', NULL)),
  );

  $form['flickrgallery_description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#description' => t('Provide a description for the sets page.'),
    '#default_value' => variable_get('flickrgallery_description', NULL),
  );

  $form['flickrgallery_lightbox_type'] = array(
    '#type' => 'textfield',
    '#title' => t('Lightbox type'),
    '#description' => t('Fill in what type of Lightbox you would like to use. Examples: lightbox, shadowbox, colorbox, ...<br />This field will be used as the link rel tag and class name. (You need to download these modules separately)'),
    '#default_value' => variable_get('flickrgallery_lightbox_type', 'lightbox2'),
  );

  $form['flickrgallery_private_pictures'] = array(
    '#type' => 'select',
    '#title' => t('Show private pictures'),
    '#description' => t('Show your private pictures, by default this is turned off.'),
    '#default_value' => variable_get('flickrgallery_private_pictures', 0),
    '#options' => array(0 => t('No'), 1 => t('Yes')),
  ); 
  
  $form['flickrgallery_token'] = array(
    '#type' => 'textfield',
    '#title' => t('Token for private pictures'),
    '#description' => t('Go to') . ' ' . l(t('http://www.flickr.com/services/api/keys/'), 'http://www.flickr.com/services/api/keys/', array('attributes' => array('target' => '_blank')))
                        . ' ' . t('and edit your API key details, set \'authentication type\' to web application and as \'callback url\': <em>http://phpflickr.com/tools/auth/auth.php</em>') . '<br />' . 
                      t('Visit') . ' ' . l(t('http://phpflickr.com/tools/auth/'), 'http://phpflickr.com/tools/auth/', array('attributes' => array('target' => '_blank')))
                        . '' . t('and fill in your API and Secret keys to generate a token, copy the token in this field.'),
    '#default_value' => variable_get('flickrgallery_token', NULL),
    '#states' => array(
      'visible' => array(
        ':input[name="flickrgallery_private_pictures"]' => array('value' => 1),
      ),
    ),
  );
  
  $form['flickrgallery_displaysets_bool'] = array(
    '#type' => 'select',
    '#title' => t('Show specific sets?'),
    '#description' => t('Show only some specific sets instead of all? By default this is turned off.'),
    '#default_value' => variable_get('flickrgallery_displaysets_bool', 0),
    '#options' => array(0 => t('No'), 1 => t('Yes')),
  ); 

  $form['flickrgallery_displaysets_values'] = array(
    '#type' => 'textarea',
    '#title' => t('Specific Sets'),
    '#description' => t('Provide the set IDs you wish to display.'),
    '#default_value' => variable_get('flickrgallery_displaysets_values', NULL),
    '#states' => array(
      'visible' => array(
        ':input[name="flickrgallery_displaysets_bool"]' => array('value' => 1),
      ),
    ),
  );
  
  $form['flickrgallery_display'] = array(
    '#type' => 'fieldset',
    '#title' => t('Image display'),
    '#collapsible' => TRUE,
  );
  
  $form['flickrgallery_display']['flickrgallery_display_type'] = array(
    '#type' => 'select',
    '#title' => t('Choose who\'s responsible to build the images'),
    '#options' => array(0 => t('Use the images build by Flickr'), 1 => t('Use Drupal\'s imagestyles for building the images')),
    '#default_value' => variable_get('flickrgallery_display_type', 0),
  );

  $form['flickrgallery_display']['flickrgallery_albums'] = array(
    '#type' => 'select',
    '#title' => t('Display sets images size.'),
    '#description' => t('Select the size for the sets images'),
    '#default_value' => variable_get('flickrgallery_albums', 'square'),
    '#options' => $options,
    '#states' => array(
      'visible' => array(
        ':input[name="flickrgallery_display_type"]' => array('value' => 0),
      ),
    ),
  );

  $form['flickrgallery_display']['flickrgallery_thumb'] = array(
    '#type' => 'select',
    '#title' => t('Display thumbnails on a set page'),
    '#description' => t('Select the size for the thumbnails on a set page.'),
    '#default_value' => variable_get('flickrgallery_thumb', 'square'),
    '#options' => $sizes,
    '#states' => array(
      'visible' => array(
        ':input[name="flickrgallery_display_type"]' => array('value' => 0),
      ),
    ),
  );

  $form['flickrgallery_display']['flickrgallery_large'] = array(
    '#type' => 'select',
    '#title' => t('Display large images from a set'),
    '#description' => t('Select the size for the larger images'),
    '#default_value' => variable_get('flickrgallery_large', 'large'),
    '#options' => $sizes,
    '#states' => array(
      'visible' => array(
        ':input[name="flickrgallery_display_type"]' => array('value' => 0),
      ),
    ),
  );
  
  // Check if image module is enabled
  if (module_exists('image') && module_exists('imagecache_external')) {
    $options_imagestyle = image_style_options(TRUE);

    $form['flickrgallery_display']['flickrgallery_albums_imagestyle'] = array(
      '#type' => 'select',
      '#title' => t('Display sets images size.'),
      '#description' => t('Select the size for the sets images'),
      '#default_value' => variable_get('flickrgallery_albums_imagestyle', 'thumbnail'),
      '#options' => $options_imagestyle,
      '#states' => array(
        'visible' => array(
          ':input[name="flickrgallery_display_type"]' => array('value' => 1),
        ),
      ),
    );
  
    $form['flickrgallery_display']['flickrgallery_thumb_imagestyle'] = array(
      '#type' => 'select',
      '#title' => t('Display thumbnails on a set page'),
      '#description' => t('Select the size for the thumbnails on a set page.'),
      '#default_value' => variable_get('flickrgallery_thumb_imagestyle', 'thumbnail'),
      '#options' => $options_imagestyle,
      '#states' => array(
        'visible' => array(
          ':input[name="flickrgallery_display_type"]' => array('value' => 1),
        ),
      ),
    );
  
    $form['flickrgallery_display']['flickrgallery_large_imagestyle'] = array(
      '#type' => 'select',
      '#title' => t('Display large images from a set'),
      '#description' => t('Select the size for the larger images'),
      '#default_value' => variable_get('flickrgallery_large_imagestyle', 'large'),
      '#options' => $options_imagestyle,
      '#states' => array(
        'visible' => array(
          ':input[name="flickrgallery_display_type"]' => array('value' => 1),
        ),
      ),
    );
  }
  else {
    $form['flickrgallery_display']['flickrgallery_image_msg'] = array(
      '#markup' => t('You need to have image and imagecache_external modules enabled to use this feature.'),
      '#states' => array(
        'visible' => array(
          ':input[name="flickrgallery_display_type"]' => array('value' => 1),
        ),
      ),
    );    
  }

  $form['flickrgallery_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Path for the Gallery'),
    '#description' => t('You can set a custom path for your gallery, by default this is /flickr'),
    '#default_value' => variable_get('flickrgallery_path', 'flickr'),
  );

  $form['flickrgallery_performance'] = array(
    '#type' => 'fieldset',
    '#title' => t('Extra options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['flickrgallery_performance']['flickrgallery_override'] = array(
    '#type' => 'checkbox',
    '#title' => t('Add more information to the images (You need to override the template files)'),
    '#description' => t('Select this option is you want to override the template files and have more information about the images available. Not recommended because this will lead to slower performance.'),
    '#default_value' => variable_get('flickrgallery_override', FALSE),
  );

  $form['flickrgallery_help'] = array(
    '#markup' => '<div>' . t('When all settings are filled in correctly, you can visit your') . ' ' . l(t('Flickr Gallery'), variable_get('flickrgallery_path', 'flickr')) . '</div>',
  );

  $form['#validate'][] = 'flickrgallery_settings_form_validate';
  $form['#submit'][] = 'flickrgallery_settings_form_submit';

  return system_settings_form($form);
}

/**
 * Administration settings form validator
 */
function flickrgallery_settings_form_validate($form, &$form_state) {
  module_load_include('module', 'flickrapi');
  if ($nsid = flickrapi_get_user_nsid($form_state['values']['flickrgallery_userID'])) {
    $form_state['values']['flickrgallery_userID'] = $nsid;
  }
  else {
    form_set_error('flickrgallery_userID', t('Not a valid Flickr UserID.'));
  }  
}

/**
 * Custom submit function for the settings form
 */
function flickrgallery_settings_form_submit($form, &$form_state) {
  
  // Check if path is provided, if so rebuild the menu
  if ($form_state['values']['flickrgallery_path'] != $form['flickrgallery_path']['#default_value']) {
    variable_set('flickrgallery_path', $form_state['values']['flickrgallery_path']);
    if (menu_rebuild()) {
      drupal_set_message(t('Menu has been rebuild'));
    }
  }
}
