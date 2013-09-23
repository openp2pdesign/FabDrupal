<?php
/**
 * @file
 * Contains form handlers for the Flickr search form.
 */

/**
 * Generates the flickr search user and search results form.
 */
function scald_flickr_search_user_form($form, &$form_state, $search_type = '', $user_id = '') {

  // Check if search form contains a value.
  if (!empty($_REQUEST['search']['search_user'])) {
    $user_id = trim($_REQUEST['search']['search_user']);
    drupal_set_message(t("Your search user: @user", array('@user' => $user_id)));
  }

  // Define form elements.
  $form = array();

  $action = 'atoms/flickr/search/user';
  $form['#action'] = url($action);
  // Record the $action for later use in redirecting.
  $form_state['action'] = $action;

  $form['search'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
    '#attributes' => array('class' => array('container-inline')),
  );
  $form['search']['search_user'] = array(
    '#type' => 'textfield',
    '#title' => t('User id or Username:'),
    '#default_value' => $user_id,
    '#description' => 'User id like 123456789@N01 or username ({username}\'s photostream from user page).',
  );
  $form['search']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Search'),
    '#submit' => array('scald_flickr_search_user_form_search_submit'),
  );

  // If we have specified user, execute the search and display the results.
  if (!empty($user_id)) {

    $form['results'] = array(
      '#type' => 'fieldset',
      '#title' => t('Search results'),
      '#tree' => TRUE,
      '#theme' => 'scald_flickr_search_results_table',
    );

    // Return a flickr id or NULL.
    $user_id = scald_flickr_parse_id('user', $user_id);

    $items = scald_flickr_feed('search_user', $user_id);
    _scald_flickr_set_images_form($items, $form);

  }

  return $form;
}

/**
 * Generates the flickr search terms and search results form.
 */
function scald_flickr_search_form($form, &$form_state, $search_type = '', $terms = '') {

  // Check if serach form contains a value.
  if (!empty($_REQUEST['search']['search_term'])) {
    $terms = trim($_REQUEST['search']['search_term']);
    drupal_set_message(t("Your search terms: @terms", array('@terms' => $terms)));
  }

  // Define form elements.
  $form = array();

  $action = 'atoms/flickr/search';
  $form['#action'] = url($action);
  // Record the $action for later use in redirecting.
  $form_state['action'] = $action;

  $form['search'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
    '#attributes' => array('class' => array('container-inline')),
  );
  $form['search']['search_term'] = array(
    '#type' => 'textfield',
    '#title' => t('Terms'),
    '#default_value' => $terms,
  );
  $form['search']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Search'),
    '#submit' => array('scald_flickr_search_form_search_submit'),
  );

  // If we have specified terms, execute the search and display the results.
  if (!empty($terms)) {
    $form['results'] = array(
      '#type' => 'fieldset',
      '#title' => t('Search results'),
      '#tree' => TRUE,
      '#theme' => 'scald_flickr_search_results_table',
    );

    $items = scald_flickr_feed('search', $terms);
    _scald_flickr_set_images_form($items, $form);

  }

  return $form;
}

/**
 * Handles search terms form submission.
 */
function scald_flickr_search_form_search_submit($form, &$form_state) {
  if ($form_state['clicked_button']['#value'] == t('Search')) {
    $terms = $form_state['values']['search']['search_term'];
    // Redirect with search keywords.
    $form_state['redirect'] = $form_state['action'] . '/' . $terms;
  }
}

/**
 * Handles search user form submission.
 */
function scald_flickr_search_user_form_search_submit($form, &$form_state) {
  if ($form_state['clicked_button']['#value'] == t('Search')) {
    $user_id = $form_state['values']['search']['search_user'];
    // Redirect with search keywords.
    $form_state['redirect'] = $form_state['action'] . '/' . $user_id;
  }
}

/**
 * Handlers import form submission.
 */
function scald_flickr_search_form_submit($form, &$form_state) {
  $identifier = $form_state['values']['identifier'];
  if (!$identifier) {
    drupal_set_message(t('No image selected for import'));
    // Present again the list of results.
    $form_state['rebuild'] = TRUE;
    return;
  }

  // End the multistep search workflow.
  unset($form_state['storage']);
  $form_state['rebuild'] = FALSE;

  // Redirect user to the import form (special page).
  $form_state['redirect'] = array(
    'atoms/flickr/import',
    array(
      'query' => array(
        'flickr-id' => $identifier,
      ),
    ),
  );
}

/**
 * Themes the results table.
 */
function theme_scald_flickr_search_results_table($variables) {
  $flickr_import_pager = scald_flickr_import_page_count();

  // Generate pager.
  pager_default_initialize($flickr_import_pager['total'], $flickr_import_pager['per_page']);

  $form = $variables['form'];
  $header = array(t('Import'), t('Title'), t('Thumbnail'), t('ID'));
  $rows = array();
  foreach (element_children($form['images']) as $key) {
    $rows[] = array(
      'data' => array(
        drupal_render($form['images'][$key]['import']),
        drupal_render($form['images'][$key]['title']),
        drupal_render($form['images'][$key]['thumbnail']),
        drupal_render($form['images'][$key]['id']),
      ),
    );
  }
  $output = theme('table', array(
      'header' => $header,
      'rows' => $rows,
      'attributes' => array('id' => 'scald-flickr-images'),
    )
  );
  $output .= drupal_render_children($form);
  $output .= theme('pager');
  return $output;
}

/**
 * Fill the search result form with flickr images.
 */
function _scald_flickr_set_images_form($items, &$form) {

  if (count($items)) {
    // Iterate on all results.
    foreach ($items as $image) {
      // Prepare variables for theme_image()
      $image_variables = array(
        'path' => str_replace('large', 'small', $image->thumbnail['src']),
        'alt' => $image->title,
        'title' => $image->title,
      );
      // Prepare row data.
      $form['results']['images'][$image->id] = array(
        'import' => array(
          '#type' => 'radio',
          '#return_value' => $image->id,
          // This will ensure we get the selected
          // result in a variable called 'identifier'.
          '#parents' => array('identifier'),
        ),
        'title' => array(
          '#type' => 'item',
          '#markup' => $image->title,
        ),
        'thumbnail' => array(
          '#type' => 'item',
          '#markup' => theme('image', $image_variables),
        ),
        'id' => array(
          '#type' => 'item',
          '#markup' => $image->id,
        ),
      );
    }
    $form['results']['import'] = array(
      '#type' => 'submit',
      '#value' => t('Import'),
      '#submit' => array('scald_flickr_search_form_submit'),
    );
  }
  else {
    // No need to show a table.
    unset($form['results']['#theme']);

    // No results message.
    $form['results']['empty'] = array(
      '#type' => 'item',
      '#markup' => t('No results'),
    );
  }

}
