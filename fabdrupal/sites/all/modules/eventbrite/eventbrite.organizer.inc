<?php

/**
 * @file
 * Defines organizer handling functions.
 */

/**
 * Form constructor for the organizer add/edit form.
 *
 * Depending whether the organizer already exists, this form creates either an
 * add form or an edit form.
 *
 * @param $organizer_id
 *   (optional) The organizer ID.
 *
 * @see eventbrite_organizer_submit()
 */
function eventbrite_organizer($form, $form_state, $organizer_id = NULL) {
  $form = array();

  if (isset($organizer_id) && $organizer = eventbrite_organizer_load($organizer_id)) {
    $form = eventbrite_organizer_form($organizer);

    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Update organizer information'),
    );
  }
  else {
    $form = eventbrite_organizer_form();

    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Create this organizer'),
    );
  }

  return $form;
}

/**
 * Builds the bulk of the organizer add/edit form.
 *
 * @param $default_values
 *   (optional) An array containing the fields of a locally-stored organizer.
 */
function eventbrite_organizer_form($default_values = array()) {
  $form = array();

  if (isset($default_values['organizer_id'])) {
    $form['organizer_id'] = array(
      '#type' => 'value',
      '#value' => $default_values['organizer_id'],
    );
  }

  // Name is the only required field
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#default_value' => isset($default_values['name']) ? $default_values['name'] : '',
    '#required' => 1,
    '#maxlength' => 32,
  );

  $form['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#default_value' => isset($default_values['description']) ? $default_values['description'] : '',
  );

  return $form;
}

/**
 * Form submission handler for eventbrite_organizer().
 */
function eventbrite_organizer_submit($form, &$form_state) {
  $organizer = _eventbrite_populate_organizer_from_form($form_state['values']);
  eventbrite_organizer_save($organizer);

  return;
}

/**
 * Returns an array representing a row from the eventbrite_organizer table.
 */
function eventbrite_organizer_load($organizer_id) {
  $result = db_query('SELECT * FROM {eventbrite_organizer} WHERE organizer_id = :organizer_id', array(':organizer_id' => $organizer_id));
  if ($result) {
    if ($row = $result->fetchAssoc()) {
      return $row;
    }
  }
}

/**
 * Builds an organizer object from the information submitted in the organizer form.
 *
 * @param $item
 *   The values submitted in the organizer add/edit form.
 *
 * @return
 *   An organizer object.
 */
function _eventbrite_populate_organizer_from_form($item) {
  $organizer = new stdClass();

  if (!empty($item['organizer_id'])) {
    $organizer->organizer_id = $item['organizer_id'];
  }
  $organizer->name = $item['name'];
  $organizer->description = $item['description'];

  return $organizer;
}

/**
 * Saves an organizer on the Eventbrite server and locally.
 *
 * @param $organizer
 *   An organizer object.
 *
 * @return
 *   If save is successful, returns the organizer ID from the Eventbrite server.
 */
function eventbrite_organizer_save($organizer) {
  if (isset($organizer->organizer_id) && !empty($organizer->organizer_id)) {
    // This venue already has an organizer_id, so organizer_update is the API call
    if ($saved_result = eventbrite_save('organizer_update', $organizer)) {
      drupal_set_message(t('This organizer has been updated on the Eventbrite server.'));
    }
    else {
      drupal_set_message(t('This organizer could not be updated on the Eventbrite server'), 'error');
      return;
    }
  }
  else {
    // This organizer does not exist, so organizer_new is the API call
    if ($saved_result = eventbrite_save('organizer_new', $organizer)) {
      drupal_set_message(t('This organizer has been created on the Eventbrite server.'));
    }
    else {
      drupal_set_message(t('This organizer could not be created on the Eventbrite server'), 'error');
      return;
    }
  }

  if ($saved_result) {
    $organizer->organizer_id = $saved_result;
    eventbrite_organizer_save_local($organizer);
    return $saved_result;
  }
}

/**
 * Saves the organizer locally.
 *
 * @param $organizer
 *   An organizer object.
 *
 * @return
 *   If the record insert or update failed, returns FALSE. If it succeeded,
 *   returns SAVED_NEW or SAVED_UPDATED, depending on the operation performed.
 */
function eventbrite_organizer_save_local($organizer) {
  // Only save locally if there is already an Eventbrite Organizer ID
  if (isset($organizer->organizer_id) && !empty($organizer->organizer_id)) {
    $result = db_query('SELECT * FROM {eventbrite_organizer} WHERE organizer_id = :organizer_id', array(':organizer_id' => $organizer->organizer_id));
    if ($result && $result->rowCount()) {
      while ($row = $result->fetchAssoc()) {
        // This event already exists in the local DB, so update it
        return drupal_write_record('eventbrite_organizer', $organizer, array('organizer_id'));
      }
    }
    else {
      // This organizer does not exist in the local DB, so insert it
      // Set status here
      if (empty($organizer->name)) {
        $organizer->status = 0;
      }
      else {
        $organizer->status = 1;
      }
      return drupal_write_record('eventbrite_organizer', $organizer);
    }
  }
}

/**
 * Form constructor for the organizer list form.
 *
 * @param $user_key
 *   (optional) The Eventbrite user key.
 *
 * @see eventbrite_organizer_list_form_validate()
 * @see eventbrite_organizer_list_form_submit()
 *
 * @ingroup forms
 */
function eventbrite_organizer_list_form($form, $form_state, $user_key = '') {
  // Set default user key to site wide Eventbrite user key
  if (empty($user_key)) {
    $user_key = variable_get('eventbrite_user_key', '');
    if (empty($user_key)) {
      return t('No Eventbrite user key has been configured for this account.');
    }
  }

  $form = array();
  $header = array(
    'name' => array('data' => t('Organizer Name'), 'field' => 'name'),
    'url' => array('data' => t('URL'), 'field' => 'url'),
    'description' => array('data' => t('Description'), 'field' => 'description'),
  );
  
  $options = array();
  $checked = array();

  // This refreshes organizers for the site-wide account
  if ($organizers = eventbrite_get('user_list_organizers')) {
    // Build form table based on locally stored data
    $result = db_select('eventbrite_organizer', 'eo')
                ->condition('user_key', $user_key, '=')
                ->fields('eo', array('organizer_id', 'status', 'name', 'url', 'description'))
                ->extend('TableSort')->orderByHeader($header)
                ->extend('PagerDefault')->limit(50)
                ->execute();
    if ($result) {
      $destination = drupal_get_destination();

      foreach ($result AS $organizer) {
        $options[$organizer->organizer_id] =array (
          'name' => l(
              $organizer->name,
              'admin/config/services/eventbrite/organizers/' . $organizer->organizer_id,
              array('query' => $destination)
            ),
          'url' => l($organizer->url, $organizer->url),
          'description' => $organizer->description,
        );
      }

      $enabled_organizers = eventbrite_organizer_get_enabled();
      if ($enabled_organizers) {
        foreach ($enabled_organizers as $id=>$name) {
          $checked[$id] = 1;
        }

        $form['default_organizer'] = array(
          '#type' => 'select',
          '#title' => t('Default Organizer'),
          '#default_value' => variable_get('eventbrite_organizer_default', ''),
          '#options' => $enabled_organizers,
          '#required' => TRUE,
        );
      }
    }

    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save enabled organizers'),
      '#weight' => 100,
    );
  }

  $form['enabled_organizers'] = array (
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#empty' => t('There are currently no organizers configured for this user account'),
    '#default_value' => $checked,
    '#prefix' => '<div class="form-item"><label>' . t('Enabled Organizers:') . '</label></div>',
    '#js_select' => FALSE,
  );

  $form['pager'] = array('#value' => theme('pager', array('tags' => NULL, 'element' => 0)));

  return $form;
}

/**
 * Form validation handler for eventbrite_organizer_list_form().
 *
 * @see eventbrite_organizer_list_form_submit()
 */
function eventbrite_organizer_list_form_validate($form, &$form_state) {
  // TODO: Check that default organizer is an enabled organizer
  $default_organizer = $form_state['values']['default_organizer'];
  $enabled_organizers = $form_state['values']['enabled_organizers'];

  if (array_sum($enabled_organizers) == 0) {
    form_set_error('enabled_organizers', t('You must enable at least one organizer.'));
  }

  if (isset($enabled_organizers[$default_organizer])) {
    if (empty($enabled_organizers[$default_organizer])) {
      form_set_error('enabled_organizers', t('Your default organizer must be enabled in the organizer list.'));
    }
  }
}

/**
 * Form submission handler for eventbrite_organizer_list_form().
 *
 * @see eventbrite_organizer_list_form_validate()
 */
function eventbrite_organizer_list_form_submit($form, &$form_state) {
  $enabled_organizers = $form_state['values']['enabled_organizers'];

  variable_set('eventbrite_organizer_default', $form_state['values']['default_organizer']);

  // Get current status for all organizers in DB
  $db_organizers = array();
  // Make sure DB matches enabled organizers list
  // TODO Please convert this statement to the D7 database API syntax.
  $result = db_query('SELECT organizer_id, status FROM {eventbrite_organizer} eo WHERE 1');
  foreach ($result AS $organizer) {
    $db_organizers[$organizer->organizer_id] = $organizer;
  }

  // Scroll through organizers returned by form. Since this was a pager query we
  // don't want to affect any organizers that weren't listed on this pager page.
  foreach ($enabled_organizers as $organizer_id => $form_organizer_status) {
    $form_organizer_status = ($form_organizer_status) ? 1 : 0;
    // For each organizer, if status has changed update the DB
    $db_organizer = $db_organizers[$organizer_id];
    if ($form_organizer_status != $db_organizer->status) {
      $db_organizer->status = $form_organizer_status;
      drupal_write_record('eventbrite_organizer', $db_organizer, array('organizer_id'));
      // TODO: Log to watchdog if this doesn't write
    }
  }
}


/**
 * Gets a list of organizers that are locally set as enabled.
 *
 * @return
 *   An array of organizer names keyed on organizer ID.
 */
function eventbrite_organizer_get_enabled() {
  // If Eventbrite OG is enabled and there is a group context
  // TODO: This filtering of organizers by sub modules should really happen via a hook
  if (module_exists('eventbrite_og') && $group_node = og_get_group_context()) {
    $filter_organizers = eventbrite_og_get_enabled_organizers($group_node);
  }
  else {
    // If Eventbrite OG is not overriding this field, use default user key for filtering
    $default_organizers = eventbrite_get('user_list_organizers');
    $filter_organizers = array_keys($default_organizers);
  }

  $enabled = array();
  $result = db_query('SELECT organizer_id, name FROM {eventbrite_organizer} WHERE status = :status', array(':status' => 1));
  foreach ($result AS $row) {
    if (!isset($filter_organizers) || in_array($row->organizer_id, $filter_organizers)) {
      $enabled[$row->organizer_id] = $row->name;
    }
  }
  return $enabled;
}
