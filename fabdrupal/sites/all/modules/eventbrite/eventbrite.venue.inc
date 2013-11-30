<?php

/**
 * @file
 * Defines venue handling functions
 */

/**
 * Form constructor for the venue add/edit form.
 *
 * Depending whether the venue already exists, this form creates either an add
 * form or an edit form.
 *
 * @param $venue_id
 *   (optional) The venue ID.
 *
 * @see eventbrite_venue_validate()
 * @see eventbrite_venue_submit()
 */
function eventbrite_venue($form, $form_state, $venue_id = NULL) {
  $form = array();

  if (isset($venue_id) && $venue = eventbrite_venue_load($venue_id)) {
    $form = eventbrite_venue_form($venue);

    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Update venue information'),
      '#weight' => 10,
    );
  }
  else {
    $form = eventbrite_venue_form();

    // Organizer field required for new venues
    module_load_include('inc', 'eventbrite', 'eventbrite.organizer');
    $form['organizer'] = array(
      '#type' => 'select',
      '#title' => 'Organizer',
      '#options' => eventbrite_organizer_get_enabled(),
      '#default_value' => variable_get('eventbrite_organizer_default', ''),
      '#required' => 1,
      '#weight' => 9,
    );

    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Create this venue'),
      '#weight' => 10,
    );
  }
  return $form;
}

/**
 * Builds the bulk of the venue add/edit form.
 *
 * @param $default_values
 *   (optional) An array containing the fields of a locally-stored venue.
 */
function eventbrite_venue_form($default_values = array()) {
  $form = array();

  if (isset($default_values['venue_id'])) {
    $form['venue_id'] = array(
      '#type' => 'value',
      '#value' => $default_values['venue_id'],
    );
  }

  // Name is the only required field
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Venue Name'),
    '#default_value' => isset($default_values['name']) ? $default_values['name'] : '',
    '#required' => 1,
    '#weight' => 0,
  );

  // TODO: Add Organizer.  Select box if there are more than one, otherwise set the default as a value

  $form['address'] = array(
    '#type' => 'textfield',
    '#title' => t('Address Line 1'),
    '#default_value' => isset($default_values['address']) ? $default_values['address'] : '',
    '#weight' => 1,
  );

  $form['address2'] = array(
    '#type' => 'textfield',
    '#title' => t('Address Line 2'),
    '#default_value' => isset($default_values['address2']) ? $default_values['address2'] : '',
    '#weight' => 2,
  );

  $form['city'] = array(
    '#type' => 'textfield',
    '#title' => t('City'),
    '#default_value' => isset($default_values['city']) ? $default_values['city'] : '',
    '#weight' => 3,
  );

  $form['region'] = array(
    '#type' => 'textfield',
    '#title' => t('Region'),
    '#default_value' => isset($default_values['region']) ? $default_values['region'] : '',
    '#weight' => 4,
  );

  $form['postal_code'] = array(
    '#type' => 'textfield',
    '#title' => t('Postal Code'),
    '#default_value' => isset($default_values['postal_code']) ? $default_values['postal_code'] : '',
    '#weight' => 5,
  );

  $form['country'] = array(
    '#type' => 'select',
    '#title' => t('Country'),
    '#options' => country_get_list(),
    '#default_value' => isset($default_values['country']) ? $default_values['country'] : '',
    '#weight' => 6,
  );

  return $form;
}

/**
 * Form validation handler for eventbrite_venue().
 *
 * @see eventbrite_venue_submit()
 */
function eventbrite_venue_validate($form, &$form_state) {
  $form_values = $form_state['values'];

  $form_errors = eventbrite_venue_form_validate($form_values);

//  TODO: Check for form errors

  return;
}

// Temporary function
// TODO $form_errors wil have to turn into form_set_errors()
/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function eventbrite_venue_form_validate($values) {
  $form_errors = array();

  // TODO: Check that there isn't already a venue with this name for this user key
  /*
   if ($values['accept_paypal']) {
   // If using PayPay check that paypal email is entered
   if (!valid_email_address($values['paypal_email'])) {
   // TODO: Does this need to actually verified that there is a PayPal account registered to this user
   $form_errors['paypal_email'] = t('Please provide a valid Paypal email.');
   }
   }
   */

  return $form_errors;
}

/**
 * Form submission handler for eventbrite_venue().
 *
 * @see eventbrite_venue_validate()
 */
function eventbrite_venue_submit($form, &$form_state) {
  $venue = _eventbrite_populate_venue_from_form($form_state['values']);
  if (eventbrite_venue_save($venue)) {
    // Venue successfully saved
    return;
  }
  // TODO: Build this error message out more & set a form error if still possible
  drupal_set_message('The venue could not be saved', 'error');
}

/**
 * Returns an array representing a row from the eventbrite_venue table.
 */
function eventbrite_venue_load($venue_id) {
  $result = db_query('SELECT * FROM {eventbrite_venue} WHERE venue_id = :venue_id', array(':venue_id' => $venue_id));
  if ($result) {
    if ($row = $result->fetchAssoc()) {
      return $row;
    }
  }
}

/**
 * Builds a venue object from the information submitted in the venue form.
 *
 * @param $item
 *   The values submitted in the venue add/edit form.
 *
 * @return
 *   A venue object.
 */
function _eventbrite_populate_venue_from_form($item) {
  // TODO: All this function does is convert array to object
  $venue = new stdClass();

  if (!empty($item['venue_id'])) {
    $venue->venue_id = $item['venue_id'];
  }
  $venue->name = $item['name'];
  if (!empty($item['organizer'])) {
    $venue->organizer = $item['organizer'];
  }
  $venue->address = $item['address'];
  $venue->address2 = $item['address2'];
  $venue->city = $item['city'];
  $venue->region = $item['region'];
  $venue->postal_code = $item['postal_code'];
  $venue->country = $item['country'];
  $venue->country_code = $item['country'];

  return $venue;
}

/**
 * Saves a venue on the Eventbrite server and locally.
 *
 * @param $venue
 *   A venue object.
 *
 * @return
 *   If save is successful, returns the venue ID from the Eventbrite server.
 */
function eventbrite_venue_save($venue) {
//  Check to see if this venue already exists on Eventbrite server by venue_id
  if (isset($venue->venue_id) && !empty($venue->venue_id)) {
    // This venue already has a venue_id, so venue_update is the API call
    if ($saved_result = eventbrite_save('venue_update', $venue)) {
      drupal_set_message(t('This venue has been updated on the Eventbrite server.'));
    }
    else {
      drupal_set_message(t('This venue could not be updated on the Eventbrite server'), 'error');
      return;
    }
  }
  else {
    // This venue does not exist, so venue_new is the API call
    if ($saved_result = eventbrite_save('venue_new', $venue)) {
      drupal_set_message(t('This venue has been created on the Eventbrite server.'));
      $venue->venue_id = $saved_result;

      // Call a hook so that submodules know that a new venue got saved
      module_invoke_all('eventbrite_venue_new', $venue);
    }
    else {
      drupal_set_message(t('This venue could not be created on the Eventbrite server'), 'error');
      return;
    }
  }
  if ($saved_result) {
    eventbrite_venue_save_local($venue);
    return $saved_result;
  }
}

/**
 * Saves a venue locally.
 *
 * @param $venue
 *   A venue object.
 *
 * @return
 *   If the record insert or update failed, returns FALSE. If it succeeded,
 *   returns SAVED_NEW or SAVED_UPDATED, depending on the operation performed.
 */
function eventbrite_venue_save_local($venue) {
  // Only save locally if there is already an Eventbrite Venue ID
  if (isset($venue->venue_id) && !empty($venue->venue_id)) {
    $result = db_query('SELECT * FROM {eventbrite_venue} WHERE venue_id = :venue_id', array(':venue_id' => $venue->venue_id));
    if ($result && $result->rowCount()) {
      while ($row = $result->fetchAssoc()) {
        // This venue already exists in the local DB, so update it
        return drupal_write_record('eventbrite_venue', $venue, array('venue_id'));
      }
    }
    else {
      // This venue does not exist in the local DB, so insert it
      // Set status here
      if (empty($venue->name) || $venue->name == 'TBD' || empty($venue->city)) {
        $venue->status = 0;
      }
      else {
        $venue->status = 1;
      }
      return drupal_write_record('eventbrite_venue', $venue);
    }
  }
}

/**
 * Form constructor for the venue list form.
 *
 * @param $user_key
 *   (optional) The Eventbrite user key.
 *
 * @see eventbrite_venue_list_form_submit()
 *
 * @ingroup forms
 */
function eventbrite_venue_list_form($form, $form_state, $user_key = '') {
  // Set default user key to site wide Eventbrite user key
  if (empty($user_key)) {
    $user_key = variable_get('eventbrite_user_key', '');
    if (empty($user_key)) {
      return t('No Eventbrite user key has been configured for this account.');
    }
  }

  $form = array();
  $header = array(
    'name' => array(
      'data' => t('Venue Name'),
      'field' => 'name',
    ),
    'address' => array(
      'data' => t('Address'),
      'field' => 'address',
    ),
    'city' => array(
      'data' => t('City'),
      'field' => 'city',
    ),
    'region' => array(
      'data' => t('Region / Postal Code'),
      'field' => 'region',
    ),
    'country' => array(
      'data' => t('Country'),
      'field' => 'country',
    ),
  );

  $venue_array = array();
  $checked = array();

  // This refreshes organizers for the site-wide account
  if ($venues = eventbrite_get('user_list_venues')) {
    $countries = country_get_list();

    $result = db_select('eventbrite_venue', 'ev')
                ->condition('user_key', $user_key, '=')
                ->fields('ev', array('venue_id', 'name', 'address', 'address2', 'city', 'region', 'postal_code', 'country'))
                ->extend('TableSort')->orderByHeader($header)
                ->extend('PagerDefault')->limit(50)
                ->execute();

    if ($result) {
      $destination = drupal_get_destination();
      $status = array(t('blocked'), t('active'));
      $roles = user_roles(TRUE);
      foreach ($result AS $venue) {
        $venue_array[$venue->venue_id] = array(
          'name' => l(
            $venue->name,
            'admin/config/services/eventbrite/venues/' . $venue->venue_id,
            array('query' => $destination)
          ),
          'address' => empty($venue->address2) ? $venue->address : $venue->address . '<br/>' . $venue->address2,
          'city' => $venue->city,
          'region' => empty($venue->postal_code) ? $venue->region : $venue->region . '<br/>' . $venue->postal_code,
          'country' => $countries[$venue->country],
        );
      }

      $enabled_venues = eventbrite_venue_get_enabled();
      if ($enabled_venues) {
        foreach ($enabled_venues as $id=>$venue) {
          $checked[$id] = 1;
        }
      }
    }

    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save enabled venues'),
      '#weight' => 100,
    );
  }

  $form['enabled_venues'] = array (
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $venue_array,
    '#empty' => t('There are currently no venues configured for this user account'),
    '#default_value' => $checked,
    '#prefix' => '<div class="form-item"><label>' . t('Enabled Venues:') . '</label></div>',
    '#js_select' => FALSE,
  );

  $form['pager'] = array('#value' => theme('pager', array('tags' => NULL, 'element' => 0)));

  return $form;
}

/**
 * Form submission handler for eventbrite_venue_list_form().
 */
function eventbrite_venue_list_form_submit($form, &$form_state) {
  $enabled_venues = $form_state['values']['enabled_venues'];

  // Get current status for all venues in DB
  $db_venue_status = array();
  // Make sure DB matches enabled venues list
  // TODO Please convert this statement to the D7 database API syntax.
  $result = db_query('SELECT venue_id, status FROM {eventbrite_venue} ev WHERE 1');
  foreach ($result AS $venue) {
    $db_venues[$venue->venue_id] = $venue;
  }

  // Scroll through venues returned by form.  Since this was a pager query we
  // don't want to affect any venues that weren't listed on this pager page.
  foreach ($enabled_venues as $venue_id => $form_venue_status) {
    $form_venue_status = ($form_venue_status) ? 1 : 0;
    // For each venue, if status has changed update the DB
    $db_venue = $db_venues[$venue_id];
    if ($form_venue_status != $db_venue->status) {
      $db_venue->status = $form_venue_status;
      drupal_write_record('eventbrite_venue', $db_venue, array('venue_id'));
      // TODO: Log to watchdog if this doesn't write
    }
  }
}

/**
 * Gets a list of venues that are locally set as enabled.
 *
 * @return
 *   An array of venues keyed on venue ID.
 */
function eventbrite_venue_get_enabled() {
  // If Eventbrite OG is enabled and there is a group context
  // TODO: This filtering of venues by sub modules should really happen via a hook
  if (module_exists('eventbrite_og') && $group_node = og_get_group_context()) {
    $filter_venues = eventbrite_og_get_enabled_venues($group_node);
  }
  else {
    // If Eventbrite OG does not override this field, use default user key for
    // filtering
    $default_venues = eventbrite_get('user_list_venues');
    $filter_venues = array_keys($default_venues);
  }

  $enabled = array();
  $result = db_query('SELECT venue_id, name, address, address2, city, region FROM {eventbrite_venue} WHERE status = :status ORDER BY name', array(':status' => 1));
  foreach ($result AS $row) {
    if (in_array($row->venue_id, $filter_venues)) {
      $enabled[$row->venue_id] = $row->name;
      if (!empty($row->address)) {
        $enabled[$row->venue_id] .= ', ' . $row->address;
      }
      if (!empty($row->address2)) {
        $enabled[$row->venue_id] .= ', ' . $row->address2;
      }
      if (!empty($row->city)) {
        $enabled[$row->venue_id] .= ', ' . $row->city;
      }
      if (!empty($row->region)) {
        $enabled[$row->venue_id] .= ', ' . $row->region;
      }
    }
  }
  return $enabled;
}

/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function eventbrite_venue_options($required = FALSE) {
  $result = db_query('SELECT * FROM {eventbrite_venue}');
  $venue_options = array();
  if (!$required) {
    $venue_options[''] = '--';
  }
  foreach ($result AS $row) {
    $venue_options[$row->venue_id] = $row->name;
  }
  return $venue_options;
}

/*
 function eventbrite_venue_list() {
 // TODO: Get venues from Eventbrite server
 $venues = eventbrite_get('user_list_venues');

 if ($venues) {
 $header = array('Venue ID', 'Edit link', 'Venue Name', 'Address' / * TODO: Add venue editing, 'Edit Link' * /);
 $rows = array();
 foreach ($venues as $venue) {
 $address = $venue->address;
 if (!empty($venue->address2)) {
 $address .= ', '. $venue->address2;
 }
 if (!empty($venue->city)) {
 $address .= ', '. $venue->city;
 }
 if (!empty($venue->region)) {
 $address .= ', '. $venue->region;
 }
 if (!empty($venue->country)) {
 $address .= ', '. $venue->country;
 }
 if (!empty($venue->postal_code)) {
 $address .= ', '. $venue->postal_code;
 }
 $rows[] = array(
 $venue->venue_id,
 l('edit', 'admin/config/eventbrite/venues/'.$venue->venue_id),
 //        l($venue->name, '/admin/settings/eventbrite/view-venue/'. $venue->venue_id),
 $venue->name,
 $address,
 // TODO: Add venue editing back in
 //        l('edit', 'admin/config/eventbrite/list-venues/'. $venue->venue_id),
 );
 }
 return theme('table', $header, $rows);
 }

 return t('There are currently no venues conifigured for this user account.');
 }
 */


/* Enabling venues by city not currently supported
 function eventbrite_venue_get_enabled_bycity($list) {
 $enabled = array();
 $result = db_query('SELECT venue_id, city, region FROM {eventbrite_venue} WHERE status = 1 ORDER by city, region');
 while ($row = db_fetch_object($result)) {
 $enabled[$row->city .', '. $row->region][] = $row->venue_id;
 }
 $enabled_bycity = array();
 foreach ($enabled as $city => $venue_ids) {
 $enabled_bycity[serialize($venue_ids)] = $city;
 }
 return $enabled_bycity;
 }
 */
