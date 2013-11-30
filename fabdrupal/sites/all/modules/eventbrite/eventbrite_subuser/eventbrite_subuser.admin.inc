<?php

module_load_include('inc', 'eventbrite', 'eventbrite.organizer');
module_load_include('inc', 'eventbrite', 'eventbrite.venue');

/*
 * Organizer Edit Form
 */
function eventbrite_subuser($user_id = NULL) {
  if (isset($user_id) && $subuser = eventbrite_subuser_load($user_id)) {
    return theme('eventbrite_subuser', array('subuser' => $subuser));
  }
}

/*
 * Default Payment Settings Form Validate
 */
/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function eventbrite_subuser_submit($form, &$form_state) {
  if (!empty($form_state['values']['user_id'])) {
    $subuser = new stdClass();

    $subuser->user_id = $form_state['values']['user_id'];
    $subuser->status = $form_state['values']['status'];
    $subuser->enabled_organizers = serialize($form_state['values']['enabled_organizers']);

    $venue_access_method = variable_get('eventbrite_subuser_venue_access', 'venue');
    switch ($venue_access_method) {
      case 'venue':
        $subuser->enabled_venues = serialize($form_state['values']['enabled_venues']);
        break;
      case 'city':
        $subuser->enabled_venues = serialize($form_state['values']['enabled_venues']);
        break;
    }

    // Subuser already exists in DB, update with changes
    if (drupal_write_record('eventbrite_subuser', $subuser, array('user_id'))) {
      drupal_set_message('The configuration for this subuser has been updated locally.');
    }
    else {
      drupal_set_message('The configuration for this subuser could not be updated locally.', 'error');
      // TODO: Set watchdog entry
    }
  }
}

/*
 * Organizer Edit Form
 */
/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function eventbrite_subuser_objects($form, $form_state, $user_id, $subuser_op) {
  $form = array();

  if (isset($user_id) && $subuser = eventbrite_subuser_load($user_id)) {
    // Add user id to form
    $form['user_id'] = array(
      '#type' => 'value',
      '#value' => $user_id,
    );

    $form['subuser_op'] = array(
      '#type' => 'value',
      '#value' => $subuser_op,
    );

    switch ($subuser_op) {
      case 'organizers':
        // Show select list of enabled organizers to activate
        $form['enabled_organizers'] = array(
          '#type' => 'checkboxes',
          '#title' => t('Enabled Organizers'),
          '#description' => t('Organizers accessible to this subuser'),
          '#options' => eventbrite_organizer_get_enabled(),
          '#default_value' => $subuser->enabled_organizers,
          '#weight' => 2,
        );
        break;
      case 'venues':
        // Show select list of enabled venues to activate
        $form['enabled_venues'] = array(
          '#type' => 'checkboxes',
          '#title' => t('Enabled venues'),
          '#description' => t('Venues accessible to this subuser'),
          '#options' => eventbrite_venue_get_enabled(),
          '#default_value' => $subuser->enabled_venues,
          '#weight' => 3,
        );
        break;
      case 'venues-city':
        // Show select list of cities to use for toggle venues
        $form['enabled_venues_by_city'] = array(
          '#type' => 'checkboxes',
          '#title' => t('Enable all venues in these cities'),
          '#description' => t('Venues accessible to this subuser'),
          '#options' => eventbrite_venue_get_enabled_bycity(),
          //          '#default_value' => $subuser->enabled_venues,
          '#weight' => 3,
        );
        break;
    }

    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Update subuser access'),
      '#weight' => 10,
    );
  }

  return $form;
}

/*
 * Default Payment Settings Form Validate
 */
/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function eventbrite_subuser_objects_submit($form, &$form_state) {
  if (!empty($form_state['values']['user_id']) && !empty($form_state['values']['subuser_op'])) {
    $subuser = new stdClass();

    $subuser->user_id = $form_state['values']['user_id'];

    switch ($form_state['values']['subuser_op']) {
      case 'organizers':
        $enabled_organizers = $form_state['values']['enabled_organizers'];
        foreach ($enabled_organizers as $key => $value) {
          if (!$value) {
            unset($enabled_organizers[$key]);
          }
        }
        $subuser->enabled_organizers = serialize($enabled_organizers);
        break;
      case 'venues':
        $enabled_venues = $form_state['values']['enabled_venues'];
        foreach ($enabled_venues as $key => $value) {
          if (!$value) {
            unset($enabled_venues[$key]);
          }
        }
        $subuser->enabled_venues = serialize($enabled_venues);
        break;
      case 'venues-city':
//        $subuser->enabled_venues = serialize($form_state['values']['enabled_venues']);
        break;
    }

    // Subuser already exists in DB, update with changes
    if (drupal_write_record('eventbrite_subuser', $subuser, array('user_id'))) {
      drupal_set_message('The configuration for this subuser has been updated locally.');
    }
    else {
      drupal_set_message('The configuration for this subuser could not be updated locally.', 'error');
      // TODO: Set watchdog entry
    }
  }
}

/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function eventbrite_subuser_list_form($form, $form_state) {
  if ($subusers = eventbrite_subuser_refresh()) {
    $form = array();

    $header = array(
      array(),
      array(
        'data' => t('Email'),
        'field' => 'es.email',
      ),
      array(
        'data' => t('User ID'),
        'field' => 'es.user_id',
      ),
      array(
        'data' => t('Enabled Organizers'),
        'field' => 'es.user_id',
      ),
      array(
        'data' => t('Enabled Venues'),
        'field' => 'es.user_id',
      ),
      array(
        'data' => t('User Key'),
        'field' => 'es.user_key',
      ),
    );

    $sql = 'SELECT es.user_id, es.status, es.email, es.user_key, es.enabled_organizers, es.enabled_venues '
      . 'FROM {eventbrite_subuser} es WHERE 1';
    $query_count = 'SELECT COUNT(es.user_id) FROM {eventbrite_subuser} es WHERE 1';

    $sql .= tablesort_sql($header);

    // TODO: This should display all results, no need for a pager query
    $result = pager_query($sql, 50, 0, $query_count);

    $destination = drupal_get_destination();

    $subuser_array = array();
    while ($subuser = db_fetch_object($result)) {
      $subuser_id = $subuser->user_id;
      $subuser_array[$subuser_id] = '';

      $form['email'][$subuser_id] = array(
        '#value' => l(
          $subuser->email,
          'admin/config/eventbrite/subuser/' . $subuser_id . '/view',
          array('query' => $destination)
        ),
      );
      $form['user_id'][$subuser_id]['#value'] = $subuser->user_id;

      $organizers_link = l(
	'configure',
	'admin/config/eventbrite/subuser/' . $subuser->user_id . '/organizers',
        array('query' => $destination)
      );
      $form['enabled_organizers'][$subuser_id]['#value'] = '0, ' . $organizers_link;
      if (isset($subuser->enabled_organizers)) {
        if ($enabled_organizers = unserialize($subuser->enabled_organizers)) {
          $form['enabled_organizers'][$subuser_id]['#value'] = sizeof($enabled_organizers) . ', ' . $organizers_link;
        }
      }

      $venues_link = l(
	'configure',
	'admin/config/eventbrite/subuser/' . $subuser->user_id . '/venues',
        array('query' => $destination)
      );
      $venues_bycity_link = l(
	'configure by city',
	'admin/config/eventbrite/subuser/' . $subuser->user_id . '/venues-city',
        array('query' => $destination)
      );
      $form['enabled_venues'][$subuser_id]['#value'] = '0, ' . $venues_link; // .', '. $venues_bycity_link;
      if (isset($subuser->enabled_venues)) {
        if ($enabled_venues = unserialize($subuser->enabled_venues)) {
          $form['enabled_venues'][$subuser_id]['#value'] = sizeof($enabled_venues) . ', ' . $venues_link; // .', '. $venues_bycity_link;
        }
      }

      $form['user_key'][$subuser_id] = array('#value' => $subuser->user_key);
    }

    $enabled_subusers = eventbrite_subuser_get_enabled();
    $form['enabled_subusers'] = array(
      '#type' => 'checkboxes',
      '#options' => $subuser_array,
      '#default_value' => array_keys($enabled_subusers),
    );

    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save enabled subusers'),
      '#weight' => 100,
    );
    $form['pager'] = array('#value' => theme('pager', array('tags' => NULL, 'element' => 0)));

    return $form;
  }

  return t('There are currently no subusers configured for this user account.');
}

/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function eventbrite_subuser_list_form_submit($form, &$form_state) {
  $enabled_subusers = $form_state['values']['enabled_subusers'];

  // Get current status for all subusers in DB
  $db_subusers = array();
  // Make sure DB matches enabled organizers list
  // TODO Please convert this statement to the D7 database API syntax.
  $result = db_query('SELECT user_id, status FROM {eventbrite_subuser} eo WHERE 1');
  while ($subuser = db_fetch_object($result)) {
    $db_subusers[$subuser->user_id] = $subuser;
  }

  // Scroll through subusers returned by form.  Since this was a pager query we don't
//   want to affect any subusers that weren't listed on this pager page
  foreach ($enabled_subusers as $user_id => $form_subuser_status) {
    $form_subuser_status = ($form_subuser_status) ? 1 : 0;
    // For each organizer, if status has changed update the DB
    $db_subuser = $db_subusers[$user_id];
    if ($form_subuser_status != $db_subuser->status) {
      $db_subuser->status = $form_subuser_status;
      drupal_write_record('eventbrite_subuser', $db_subuser, array('user_id'));
      // TODO: Log to watchdog if this doesn't write
    }
  }

}


/* Theme organizer list form.
 *
 * @ingroup themeable
 */
/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function theme_eventbrite_subuser_list_form($variables) {
  $form = $variables['form'];
  // TODO Please change this theme call to use an associative array for the $variables parameter.
  $header = array(
    theme('table_select_header_cell'),
    array(
      'data' => t('Email'),
      'field' => 'es.email',
    ),
    array(
      'data' => t('User ID'),
      'field' => 'es.user_id',
    ),
    array('data' => t('Enabled Organizers')),
    array('data' => t('Enabled Venues')),
    array(
      'data' => t('User Key'),
      'field' => 'es.user_key',
    ),
  );
  /*
   $output = drupal_render($form['eventbrite_subuser_venue_access']);
   */
  $output .= drupal_render($form['options']);
  if (isset($form['user_id']) && is_array($form['user_id'])) {
    foreach (element_children($form['user_id']) as $key) {
      $rows[] = array(
        drupal_render($form['enabled_subusers'][$key]),
        drupal_render($form['email'][$key]),
        drupal_render($form['user_id'][$key]),
        drupal_render($form['enabled_organizers'][$key]),
        drupal_render($form['enabled_venues'][$key]),
        drupal_render($form['user_key'][$key]),
      );
    }
  }
  else {
    $rows[] = array(array(
        'data' => t('No subusers were found in this Eventbrite account.'),
        'colspan' => '4',
      ));
  }

  $output .= '<div class="form-item"><label>' . t('Enabled Subusers:') . '</label></div>';
  $output .= theme('table', array('header' => $header, 'rows' => $rows));
  if ($form['pager']['#value']) {
    $output .= drupal_render($form['pager']);
  }

  $output .= drupal_render_children($form);

  return $output;
}

/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function theme_eventbrite_subuser($variables) {
  $subuser = $variables['subuser'];
  $output = '<h2>' . $subuser->email;
  if ($subuser->status) {
    $output .= ' ' . t('(enabled)');
  }
  else {
    $output .= ' ' . t('(disabled)');
  }
  $output .= '</h2><br/>';

  if ($subuser->enabled_organizers) {
    $enabled_organizers = eventbrite_organizer_get_enabled();
    $output .= t('Enabled Organizers:') . '<br/>';
    $output .= '<ul>';
    foreach ($subuser->enabled_organizers as $organizer_id) {
      if (isset($enabled_organizers[$organizer_id])) {
        $output .= '<li>' . $enabled_organizers[$organizer_id] . '</li>';
      }
    }
    $output .= '</ul><br/>';
  }

  if ($subuser->enabled_venues) {
    $enabled_venues = eventbrite_venue_get_enabled();
    $output .= t('Enabled Venues:') . '<br/>';
    $output .= '<ul>';
    foreach ($subuser->enabled_venues as $venue_id) {
      if (isset($enabled_venues[$venue_id])) {
        $output .= '<li>' . $enabled_venues[$venue_id] . '</li>';
      }
    }
    $output .= '</ul></br>';
  }

  return $output;
}

