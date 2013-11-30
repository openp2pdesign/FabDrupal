<?php

/**
 * @file
 * Defines page callbacks for Eventbrite Groups
 */

/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function eventbrite_og_venue_form($form_state, $venue_id = 0) {
//  $payment_settings_form = eventbrite_ui_payment_settings_form();
//  return system_settings_form($payment_settings_form);
  //drupal_set_message('yar'.$yar);
  og_set_group_context($group_node);

  // TODO: payment settings form?  THis won't do!
//  module_load_include('inc', 'eventbrite_ui', 'eventbrite_ui.forms');
//  $form = eventbrite_ui_payment_settings_form();

  return $form;
}

/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function eventbrite_og_venue_list($group_node) {
  og_set_group_context($group_node);

  module_load_include('inc', 'eventbrite', 'eventbrite.venue');

  return eventbrite_venue_list();
}

/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function eventbrite_og_default_payment_settings($form_state, $group_node) {
  og_set_group_context($group_node);

  module_load_include('inc', 'eventbrite', 'eventbrite.payment');

  // TODO: Get current values for this group from DB table
  $default_values = variable_get('eventbrite_default_payment_settings', array());

  $form = eventbrite_payment_settings_form($default_values);

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Update default settings',
  );

  return $form;
}

/*
 * Default Payment Settings Form Validate
 */
/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function eventbrite_og_default_payment_settings_validate($form, &$form_state) {
  $form_values = $form_state['values'];

  $form_errors = eventbrite_payment_settings_errors($form_values);
  foreach ($form_errors as $form_element => $error_msg) {
    form_set_error($form_element, $error_msg);
  }
}

/*
 * Default Payment Settings Form Submit
 */
/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function eventbrite_og_default_payment_settings_submit($form, &$form_state) {
  drupal_set_message('Group specific payment settings can not be customized at this time', 'error');
  // TODO: Save form values to DB table
}
