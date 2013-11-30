<?php

/**
 * @file
 * Defines payment handling functions
 */

/**
 * Form constructor for the payment settings form.
 *
 * @see eventbrite_payment_default_settings_validate()
 * @see eventbrite_payment_default_settings_submit()
 */
function eventbrite_payment_default_settings($form, &$form_state) {
  $default_values = variable_get('eventbrite_default_payment_settings', array());

  $form = eventbrite_payment_settings_form($default_values, 1);

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Update default settings',
  );

  return $form;
}

/**
 * Builds the bulk of the payment settings form.
 *
 * @param $default_values
 *   (optional) An array containing the fields of a locally-stored venue.
 * @param $show_controls
 *   (optional) Whether or not to show the first two checkboxes of the form.
 */
function eventbrite_payment_settings_form($default_values = array(), $show_controls = 0) {
  if (is_object($default_values)) {
    $default_values = (array) $default_values;
  }
  $form = array();

  if ($show_controls) {
    $form['eventbrite_allow_payment_override'] = array(
      '#type' => 'checkbox',
      '#title' => t('Allow event creators/editors to override these settings'),
      '#default_value' => isset($default_values['allow_payment_override']) ? $default_values['allow_payment_override'] : 1,
      '#prefix' => '<div class="eventbrite-payment-settings-group">',
    );

    $form['eventbrite_autocreate_payment'] = array(
      '#type' => 'checkbox',
      '#title' => t('Automatically submit payment settings on creation of every event'),
      '#default_value' => isset($default_values['autocreate_payment']) ? $default_values['autocreate_payment'] : 0,
      '#suffix' => '</div>',
    );
  }
  else {
    if (isset($default_values['allow_payment_override'])) {
      $form['eventbrite_allow_payment_override'] = array(
        '#type' => 'value',
        '#value' => $default_values['allow_payment_override'],
      );
    }

    if (isset($default_values['autocreate_payment'])) {
      $form['eventbrite_autocreate_payment'] = array(
        '#type' => 'value',
        '#value' => $default_values['autocreate_payment'],
      );
    }
  }

  $form['eventbrite_accept_paypal'] = array(
    '#type' => 'checkbox',
    '#title' => t('Accept PayPal payments'),
    '#default_value' => isset($default_values['accept_paypal']) ? $default_values['accept_paypal'] : 0,
    '#prefix' => '<div class="eventbrite-payment-settings-group">',
  );

  $form['eventbrite_paypal_email'] = array(
    '#type' => 'textfield',
    '#title' => t('PayPal Email'),
    '#default_value' => isset($default_values['paypal_email']) ? $default_values['paypal_email'] : '',
    '#suffix' => '</div>',
    '#states' => array(
      'visible' => array(
        ':input[name="eventbrite_accept_paypal"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['eventbrite_accept_google'] = array(
    '#type' => 'checkbox',
    '#title' => t('Accept Google Checkout payments'),
    '#default_value' => isset($default_values['accept_google']) ? $default_values['accept_google'] : 0,
    '#prefix' => '<div class="eventbrite-payment-settings-group">',
  );

  $form['eventbrite_google_merchant_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Google Checkout Merchant ID'),
    '#default_value' => isset($default_values['google_merchant_id']) ? $default_values['google_merchant_id'] : '',
    '#states' => array(
      'visible' => array(
        ':input[name="eventbrite_accept_google"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['eventbrite_google_merchant_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Google Checkout Merchant Key'),
    '#default_value' => isset($default_values['google_merchant_key']) ? $default_values['google_merchant_key'] : '',
    '#suffix' => '</div>',
    '#states' => array(
      'visible' => array(
        ':input[name="eventbrite_accept_google"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['eventbrite_accept_check'] = array(
    '#type' => 'checkbox',
    '#title' => t('Accept "Pay by Check" payments'),
    '#default_value' => isset($default_values['accept_check']) ? $default_values['accept_check'] : 0,
    '#prefix' => '<div class="eventbrite-payment-settings-group">',
  );

  $form['eventbrite_instructions_check'] = array(
    '#type' => 'textfield',
    '#title' => 'Instructions to attendees who want to pay by check',
    '#default_value' => isset($default_values['instructions_check']) ? $default_values['instructions_check'] : '',
    '#suffix' => '</div>',
    '#states' => array(
      'visible' => array(
        ':input[name="eventbrite_accept_check"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['eventbrite_accept_cash'] = array(
    '#type' => 'checkbox',
    '#title' => t('Accept "Pay with Cash" payments'),
    '#default_value' => isset($default_values['accept_cash']) ? $default_values['accept_cash'] : 0,
    '#prefix' => '<div class="eventbrite-payment-settings-group">',
  );

  $form['eventbrite_instructions_cash'] = array(
    '#type' => 'textfield',
    '#title' => 'Instructions to attendees who want to pay with cash',
    '#default_value' => isset($default_values['instructions_cash']) ? $default_values['instructions_cash'] : '',
    '#suffix' => '</div>',
    '#states' => array(
      'visible' => array(
        ':input[name="eventbrite_accept_cash"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['eventbrite_accept_invoice'] = array(
    '#type' => 'checkbox',
    '#title' => t('Accept "Send an Invoice" payments'),
    '#default_value' => isset($default_values['accept_invoice']) ? $default_values['accept_invoice'] : 0,
    '#prefix' => '<div class="eventbrite-payment-settings-group">',
  );

  $form['eventbrite_instructions_invoice'] = array(
    '#type' => 'textfield',
    '#title' => 'Instructions to attendees who need to be sent an invoice',
    '#default_value' => isset($default_values['instructions_invoice']) ? $default_values['instructions_invoice'] : '',
    '#suffix' => '</div>',
    '#states' => array(
      'visible' => array(
        ':input[name="eventbrite_accept_invoice"]' => array('checked' => TRUE),
      ),
    ),
  );

  // If show controls = FALSE & allow_payment_override = FALSE, add readonly to each element
  if (!$show_controls && !$default_values['allow_payment_override']) {

    if ($form['eventbrite_accept_paypal']['#default_value']) {
      $form['eventbrite_accept_paypal']['#disabled'] = 1;
      $form['eventbrite_paypal_email']['#attributes']['readonly'] = 1;
    }
    else {
      unset($form['eventbrite_accept_paypal']);
      unset($form['eventbrite_paypal_email']);
    }

    if ($form['eventbrite_accept_google']['#default_value']) {
      $form['eventbrite_accept_google']['#disabled'] = 1;
      $form['eventbrite_google_merchant_id']['#attributes']['readonly'] = 1;
      $form['eventbrite_google_merchant_key']['#attributes']['readonly'] = 1;
    }
    else {
      unset($form['eventbrite_accept_google']);
      unset($form['eventbrite_google_merchant_id']);
      unset($form['eventbrite_google_merchant_key']);
    }

    if ($form['eventbrite_accept_check']['#default_value']) {
      $form['eventbrite_accept_check']['#disabled'] = 1;
      $form['eventbrite_instructions_check']['#attributes']['readonly'] = 1;
    }
    else {
      unset($form['eventbrite_accept_check']);
      unset($form['eventbrite_instructions_check']);
    }

    if ($form['eventbrite_accept_cash']['#default_value']) {
      $form['eventbrite_accept_cash']['#disabled'] = 1;
      $form['eventbrite_instructions_cash']['#attributes']['readonly'] = 1;
    }
    else {
      unset($form['eventbrite_accept_cash']);
      unset($form['eventbrite_instructions_cash']);
    }

    if ($form['eventbrite_accept_invoice']['#default_value']) {
      $form['eventbrite_accept_invoice']['#disabled'] = 1;
      $form['eventbrite_instructions_invoice']['#attributes']['readonly'] = 1;
    }
    else {
      unset($form['eventbrite_accept_invoice']);
      unset($form['eventbrite_instructions_invoice']);
    }
  }

  return $form;
}

/**
 * Form validation handler for eventbrite_payment_default_settings().
 *
 * @see eventbrite_payment_default_settings_submit()
 */
function eventbrite_payment_default_settings_validate($form, &$form_state) {
  $form_values = $form_state['values'];

  if ($form_values['eventbrite_accept_paypal']) {
    // If using PayPay check that paypal email is entered
    if (!valid_email_address($form_values['eventbrite_paypal_email'])) {
      // TODO: Does this need to actually verified that there is a PayPal account registered to this user
      form_set_error('eventbrite_paypal_email', t('Please provide a valid Paypal email.'));
    }
  }

  if ($form_values['eventbrite_accept_google']) {
    // If using Google Checkout check that Merchant ID is a 10 or 15 digit number
    if (!preg_match('/^([0-9]{10}|[0-9]{15})$/', $form_values['eventbrite_google_merchant_id'])) {
      form_set_error('eventbrite_google_merchant_id', t('To use Google Checkout you need to enter a 10 or 15 digit Google Checkout Merchant ID.'));
    }
    // If using Google Checkout check that Merchant Key is a 22 character string
    if (!preg_match('/^(.{22})$/', $form_values['eventbrite_google_merchant_key'])) {
      form_set_error('eventbrite_google_merchant_key', t('To use Google Checkout you need to enter a 22 character Google Checkout Merchant Key.'));
    }
  }
}

/**
 * Form submission handler for eventbrite_payment_default_settings().
 *
 * @see eventbrite_payment_default_settings_validate()
 */
function eventbrite_payment_default_settings_submit($form, &$form_state) {
  variable_set('eventbrite_default_payment_settings', eventbrite_payment_get_settings($form_state['values']));
}

/**
 * Converts the submitted form values into an array with shortened keys.
 *
 * Removes the "eventbrite_" prefix from the keys for the new array. The
 * resulting array is intended to be stored in the {variable} table as
 * eventbrite_default_payment_settings.
 *
 * @param $values
 *   An array or object containing the payment settings.
 *
 * @return
 *   An array of the payment settings with the "eventbrite_" prefix removed.
 */
function eventbrite_payment_get_settings($values) {
  if (is_object($values)) {
    $values = (array) $values;
  }
  $return_values = array();

  $return_values['allow_payment_override'] = $values['eventbrite_allow_payment_override'];
  $return_values['autocreate_payment'] = $values['eventbrite_autocreate_payment'];
  $return_values['accept_paypal'] = $values['eventbrite_accept_paypal'];
  $return_values['paypal_email'] = $values['eventbrite_paypal_email'];
  $return_values['accept_google'] = $values['eventbrite_accept_google'];
  $return_values['google_merchant_id'] = $values['eventbrite_google_merchant_id'];
  $return_values['google_merchant_key'] = $values['eventbrite_google_merchant_key'];
  $return_values['accept_check'] = $values['eventbrite_accept_check'];
  $return_values['instructions_check'] = $values['eventbrite_instructions_check'];
  $return_values['accept_cash'] = $values['eventbrite_accept_cash'];
  $return_values['instructions_cash'] = $values['eventbrite_instructions_cash'];
  $return_values['accept_invoice'] = $values['eventbrite_accept_invoice'];
  $return_values['instructions_invoice'] = $values['eventbrite_instructions_invoice'];

  return $return_values;
}

/**
 * Returns an array of the default payment settings.
 */
function eventbrite_payment_get_default_settings() {
  $default_payment_settings = module_invoke_all('eventbrite_default_payment_settings');

  if (empty($default_payment_settings)) {
    $default_payment_settings = variable_get('eventbrite_default_payment_settings', array());
  }

  return $default_payment_settings;
}
