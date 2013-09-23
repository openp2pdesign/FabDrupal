<?php

/**
 * @file
 * MERCI - Managed Equipment Reservation Checkout and Inventory
 */


/**
 * Builds the MERCI admininstration settings form.
 */
function merci_admin_settings($form, &$form_state) {
  $form = array();

  $statuses = array();

  $statuses[MERCI_STATUS_UNCONFIRMED] = t('Unconfirmed');
  $statuses[MERCI_STATUS_PENDING] = t('Confirmed');
  $statuses[MERCI_STATUS_CHECKED_OUT] = t('Checked Out');

  $hours_of_operation = merci_load_hours_of_operation();

  $form['merci_default_reservation_status'] = array(
    '#type' => 'select',
    '#title' => t('Default Reservation Status'),
    '#options' => $statuses,
    '#default_value' => variable_get('merci_default_reservation_status', ''),
    '#description' => t('New Reservations will be set to this by default.  Use Checked Out if you are using MERCI to manage the checkout, but do not allow actual Reservations.'),
  );

  $form['merci_max_days_advance_reservation'] = array(
    '#type' => 'textfield',
    '#title' => t('Max Advance'),
    '#size' => 11,
    '#maxlength' => 11,
    '#default_value' => variable_get('merci_max_days_advance_reservation', '0'),
    '#description' => t('Maximum number of days a Reservation can be made in advance.  Set to 0 if to allow Reservations to be made an unlimitted time into the future.'),
  );

  // Weekend

  // Hours of operation

  $hours_description = '<div>' . t('Enter military time for both opening and closing time, separated by a dash, in the format') . ' <em>hh:mm-hh:mm</em></div>' . t('ex.') . ' <em>09:00-17:00</em> ' . t('would be open at 9AM, close at 5PM. Leave blank to indicate not being open.');

  $hours_description .= '<p><div>' . t('Check the box next to <em>considered a weekend</em> if MERCI should consider that day a weekend.  Item\'s cannot be checked out or reserved on weekend days unless the "Allow Weekends" setting is checked for the content type.') . '</div>';

  $hours_element = array(
    '#type' => 'textfield',
    '#title' => t('Monday hours'),
    '#size' => 11,
    '#maxlength' => 11,
    '#element_validate' => array('merci_admin_validate_hours_of_operation'),
    );

  $weekend_element = array(
    '#type' => 'checkbox',
    '#title' => t('is considered a weekend'),
  );


  $form['merci_hours'] = array(
    '#title' => t('Hours of operation'),
    '#type' => 'fieldset',
    '#description' => $hours_description,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $days_of_the_week = array(
    'sunday',
    'monday',
    'tuesday',
    'wednesday',
    'thursday',
    'friday',
    'saturday',
  );

  foreach ($days_of_the_week as $num => $day) {
    $form['merci_hours']['merci_hours_' . $day] = array(
      '#title' => t('@day hours', array('@day' => ucfirst($day))),
      '#default_value' => isset($hours_of_operation[$num]) ? implode('-', $hours_of_operation[$num]) : '',
      '#type' => 'textfield',
      '#size' => 11,
      '#maxlength' => 11,
      '#element_validate' => array('merci_admin_validate_hours_of_operation'),
    );
    $form['merci_hours']['merci_' . $day . '_is_weekend'] = array(
      '#default_value' => variable_get('merci_' . $day . '_is_weekend', 0),
      '#type' => 'checkbox',
      '#title' => t('is considered a weekend'),
    );
  }

  $form['merci_hours']['merci_hours_admin'] = array(
    '#title' => t('Admin hours'),
    '#default_value' => variable_get('merci_hours_admin', '07:00-22:00'),
    '#description' => t('This setting controls the hours shown on the conflict grid for users with Adminster MERCI permessions.  The conflict grid is normally limited to the days and hours the set above.  Because users with Admister MERCI rights can create Resevervations outside the normal hours of operation, they need to see conflicts during those times as well.'),
    '#type' => 'textfield',
    '#size' => 11,
    '#maxlength' => 11,
    '#element_validate' => array('merci_admin_validate_hours_of_operation'),
  );

  $form['merci_hours']['merci_closed_dates'] = array(
    '#type' => 'textarea',
    '#title' => t('Closed dates'),
    '#rows' => 10,
    // TODO: this doesn't seem to work...
    '#cols' => 5,
    '#default_value' => variable_get('merci_closed_dates', ''),
    '#description' => '<div>' . t('Enter dates which are closed regardless of the day of the week, one date per line, in the format') . ' <em>mm-dd</em></div>' . t('ex.') . ' <em>07-04</em> ' . t('would mean July 4th is always closed, regardless of what day of the week it falls on.'),
    '#element_validate' => array('merci_admin_validate_closed_days'),
  );

  $form['merci_advanced'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['merci_advanced']['merci_verbose_logging'] = array(
    '#type' => 'checkbox',
    '#title' => t('Verbose Logging Mode'),
    '#default_value' => variable_get('merci_verbose_logging', 0),
    '#description' => t('This option will add log messages at several points in the resevervation process making it easier to diagnose configuration issues.'),
  );

  $field             = field_info_field('field_merci_date');

  $form['merci_advanced']['merci_lock'] = array(
    '#type' => 'checkbox',
    '#title' => t('Lock Fields'),
    '#default_value' => $field['locked'],
    '#description' => t('MERCI requires a Date field to function. This field is locked by default.  Altering or deleting the Date field could cause serious problems.  Always backup before altering this field!'),
  );

  $form = system_settings_form($form);
  $form['#submit'][] = 'merci_admin_settings_submit';
  return ($form);
}

/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function merci_admin_settings_submit($form, &$form_state) {
  $field             = field_info_field('field_merci_date');
  if ($form_state['values']['merci_lock'] != $field['locked']) {
    $field['locked'] = $form_state['values']['merci_lock'];
    module_load_include('inc', 'field', 'field.crud');
    field_update_field($field);
  }
  $days_of_the_week = array(
    'sunday',
    'monday',
    'tuesday',
    'wednesday',
    'thursday',
    'friday',
    'saturday',
  );

  $hours_of_operation = array();
  foreach ($days_of_the_week as $num => $day) {
    $hours = $form_state['values']['merci_hours_' . $day];
    if (empty($hours)) {
      $hours_of_operation[$num] = NULL;
    } else {
      list ($open, $close) = explode('-', $hours);
      $hours_of_operation[$num]['open'] = trim($open);
      $hours_of_operation[$num]['close'] = trim($close);
    }
  }

  $closed_days_raw = $form_state['values']['merci_closed_dates'];
  $hours_of_operation['closed_days'] = array();
  $parts = explode("\n", $closed_days_raw);
  foreach ($parts as $date) {
    $date = trim($date);
    if (drupal_strlen($date) == 5) {
      $hours_of_operation['closed_days'][] = $date;
    }
  }
  variable_set('merci_hours_operation', $hours_of_operation);
}

function merci_admin_validate_closed_days($element, &$form_state) {
  if (empty($element['#value'])) {
    return;
  }

  $parts = explode("\n", trim($element['#value']));
  foreach ($parts as $date) {
    $date = trim($date);
    $hours_of_operation['closed_days'][] = $date;
    list($month, $day) = explode('-', $date);
    if(strlen($month) != 2) {
      form_error($element, t('Month must be two digits.'));
    }
    if(strlen($day) != 2) {
      form_error($element, t('Day must be two digits.'));
    }

    if (!checkdate($month, $day, date('Y'))) {
      form_error($element, t('Date %date is invalid', array('%date' => $date)));
    }
  }
}

function merci_admin_validate_hours_of_operation($element, &$form_state) {
  if (!empty($element['#value'])) {
    $values = explode('-', $element['#value']);
    foreach ($values as $value) {
      list ($hour, $min) = explode(':', $value);
      if ($hour > 23) {
        form_error($element, t('Hour must be less than or equal to 23.'));
      }
      if ($hour < 0) {
        form_error($element, t('Hour must be greater than or equal to 0.'));
      }
      if ($min > 59) {
        form_error($element, t('Minutes must be less than or equal to 59.'));
      }
      if ($min < 0) {
        form_error($element, t('Minutes must be greater than or equal to 0.'));
      }
    }
    if ($values[1] < $values[0]) {
        form_error($element, t('Closing time must be greater then opening time.'));
    }
  }
}

