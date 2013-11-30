<?php

/**
 * @file
 * Provides a function for each action in the Eventbrite API.
 */

module_load_include('inc', 'eventbrite', 'eventbrite.common');

/*
 * This function fetches the user's list of events from Eventbrite
 */
function _eventbrite_api_get_events() {
  // Build a new request object
  $request = _eventbrite_common_new_request('user_list_events', 'get');

  if ($result = _eventbrite_common_process_request($request)) {
    $xml_object = $result->object;
    $events = array();
    foreach ($xml_object as $key => $xml_event) {
      if ($key == 'event' && $event = _eventbrite_api_populate_event($xml_event)) {
        $events[$event->id] = $event;
      }
    }
    return $events;
  }
}

/*
 * This function fetches the user's list of venues from Eventbrite
 */
function _eventbrite_api_get_venues() {
  // Pull in venue handling functions
  module_load_include('inc', 'eventbrite', 'eventbrite.venue');

  // Build a new request object
  $request = _eventbrite_common_new_request('user_list_venues', 'get');

  if ($result = _eventbrite_common_process_request($request)) {
    $xml_object = $result->object;
    $venues = array();

    foreach ($xml_object as $key => $xml_event) {
      if ($key == 'venue' && $venue = _eventbrite_api_populate_venue($xml_event)) {
        $venues[$venue->venue_id] = $venue;

        // If $result->updated then these venues should be saved to the DB
        // If no caching is allowed then these values may or may not be new
        // TODO: Look at $result->prev_cache to see if each specific venue has changed before resaving
        if ($result->updated) {
          $venue->user_key = $result->user_key;
//          $venue->module = $result->module;

          eventbrite_venue_save_local($venue);
        }
      }
    }
    return $venues;
  }
}

/*
 * This function fetches the user's list of venues from Eventbrite
 */
function _eventbrite_api_get_organizers() {
  // Pull in venue handling functions
  module_load_include('inc', 'eventbrite', 'eventbrite.organizer');

  // Build a new request object
  $request = _eventbrite_common_new_request('user_list_organizers', 'get');

  if ($result = _eventbrite_common_process_request($request)) {
    $xml_object = $result->object;
    $organizers = array();

    foreach ($xml_object as $key => $xml_event) {
      if ($key == 'organizer' && $organizer = _eventbrite_api_populate_organizer($xml_event)) {
        $organizers[$organizer->organizer_id] = $organizer;

        // If $result->updated then these venues should be saved to the DB
        // If no caching is allowed then these values may or may not be new
        // TODO: Look at $result->prev_cache to see if each specific venue has changed before resaving
        if ($result->updated) {
          $organizer->user_key = $result->user_key;
          eventbrite_organizer_save_local($organizer);
        }
      }
    }
    return $organizers;
  }
}

/*
 * This function fetches one user by user key
 */
function _eventbrite_api_get_user($user_key = '', $key_type = '') {
  // Build a new request object
  $request = _eventbrite_common_new_request('user_get', 'get');

  switch ($key_type) {
    case 'email':
      $request->params['email'] = $user_key;
      break;
    case 'user_id':
      $request->params['user_id'] = $user_key;
      break;
    case 'user_key':
      $request->user_key = $user_key;
      break;
  }
  if ($user_key) {
    $request->$key_type = $user_key;
  }

  if ($result = _eventbrite_common_process_request($request)) {
    $xml_object = $result->object;
    if ($eb_user = _eventbrite_api_populate_user($xml_object)) {
      return $eb_user;
    }
  }
}

/*
 * This function fetches one events by Id
 */
function _eventbrite_api_get_event($event_id) {
  // Build a new request object
  $request = _eventbrite_common_new_request('event_get', 'get');

  $request->params['id'] = $event_id;

  if ($result = _eventbrite_common_process_request($request)) {
    $xml_object = $result->object;
    $event = _eventbrite_api_populate_event($xml_object);
    return $event;
  }
}

function _eventbrite_api_populate_event($event_data) {
  $event = new stdClass();
  $event->id = (string) $event_data->id;
  $event->title = (string) $event_data->title;
  $event->description = str_replace("\n", ' ', html_entity_decode((string) $event_data->description));
  $event->status = (string) $event_data->status;
  $event->start_date = (string) $event_data->start_date;
  $event->end_date = (string) $event_data->end_date;
  $event->timezone = (string) $event_data->timezone;
  $event_venue = $event_data->venue;
  if (isset($event_venue->id)) {
    $event->venue_id = (integer) $event_venue->id;
  }
  return $event;
}

function _eventbrite_api_populate_user($user_data) {
  $eb_user = new stdClass();
  $eb_user->user_id = (integer) $user_data->user_id;
  $eb_user->user_key = (string) $user_data->user_key;
  $eb_user->email = (string) $user_data->email;

  if ($subusers = (array) $user_data->subusers) {
    $eb_user->subusers = array();
    foreach ($subusers['subuser'] as $subuser) {
      $eb_subuser = new stdClass();
      $eb_subuser->user_id = (integer) $subuser->id;
      $eb_subuser->email = (string) $subuser->email;

      $eb_user->subusers[] = $eb_subuser;
    }
  }

  return $eb_user;
}

function _eventbrite_api_populate_venue($venue_data) {
  $venue = new stdClass();
  $venue->venue_id = (integer) $venue_data->id;
  $venue->name = (string) $venue_data->name;
  $venue->address = (string) $venue_data->address;
  $venue->city = (string) $venue_data->city;
  $venue->region = (string) $venue_data->region;
  $venue->country = (string) $venue_data->country_code;
//  $venue->country_code = (string)$venue_data->country_code;
  $venue->longitude = (string) $venue_data->longitude;
  $venue->latitude = (string) $venue_data->latitude;

  return $venue;
}

function _eventbrite_api_populate_organizer($organizer_data) {
  $organizer = new stdClass();
  $organizer->organizer_id = (integer) $organizer_data->id;
  $organizer->name = (string) $organizer_data->name;
  $organizer->url = (string) $organizer_data->url;
  $organizer->description = (string) $organizer_data->description;

  return $organizer;
}

function _eventbrite_api_event_new($event) {
  $request = _eventbrite_common_new_request('event_new', 'save');

  // Add event data to request
  $request->params['title'] = $event->title;
  $request->params['description'] = $event->description;

  // Status is always draft on event creation, event_update will be called to update to live
  $request->params['status'] = 'draft';
  $request->params['organizer_id'] = $event->organizer_id;

  $request->params['start_date'] = $event->start_date;
  $request->params['end_date'] = $event->end_date;
  $request->params['timezone'] = $event->timezone;
  $request->params['venue_id'] = $event->venue_id;

  // Result will only return if no error
  if ($result = _eventbrite_common_process_request($request)) {
    // Populate the event coming back and return it
    $xml_object = $result->object;

    if ($event_id = (string) $xml_object->id) {

      // Record in watchdog
      $message = (string) $xml_object->message;
      watchdog('eventbrite', "Message: %message\nEventbrite Event ID: %id", array('%message' => $message, '%id' => $event_id));

      // Expire the cache of event listing
      _eventbrite_common_cache_expire('user_list_events');
      return $event_id;
    }
  }
}

function _eventbrite_api_user_new($user) {
  $request = _eventbrite_common_new_request('user_new', 'save');

  // Add event data to request
  $request->params['email'] = $user->email;
  $request->params['passwd'] = $user->passwd;

  // Result will only return if no error
  if ($result = _eventbrite_common_process_request($request)) {
    // Populate the event coming back and return it
    $xml_object = $result->object;

    if ($user_id = (integer) $xml_object->id) {
      $eb_user = new stdClass();
      $eb_user->id = $user_id;
      $eb_user->user_key = (string) $xml_object->user_key;

      // Record in watchdog
      $message = (string) $xml_object->message;
      watchdog(
        'eventbrite',
        "Message: %message\nEventbrite Subuser ID: %id\nUser key: %user_key",
        array('%message' => $message, '%id' => $eb_user->id, '%user_key' => $eb_uesr->user_key)
      );

      return $eb_user;
    }
  }
}

function _eventbrite_api_event_update($event) {
  $request = _eventbrite_common_new_request('event_update', 'save');

  // Add event data to request
  $request->params['event_id'] = $event->event_id;
  $request->params['title'] = $event->title;
  $request->params['description'] = $event->description;
  $request->params['status'] = $event->status;
  $request->params['organizer_id'] = $event->organizer_id;

  $request->params['start_date'] = $event->start_date;
  $request->params['end_date'] = $event->end_date;
  $request->params['timezone'] = $event->timezone;
  $request->params['venue_id'] = $event->venue_id;

  // XML data will only come back if no error
  if ($result = _eventbrite_common_process_request($request)) {
    // Populate the event coming back and return it
    $xml_object = $result->object;

    if ($event_id = (string) $xml_object->id) {
      // Record in watchdog
      $message = (string) $xml_object->message;
      watchdog('eventbrite', "Message: %message\nEventbrite Event ID: %id", array('%message' => $message, '%id' => $event_id));

      // Expire the cache of event listing
      _eventbrite_common_cache_expire('event_get', $event_id);
      _eventbrite_common_cache_expire('user_list_events');

      return $event_id;
    }
  }
}

function _eventbrite_api_organizer_update($organizer) {
  $request = _eventbrite_common_new_request('organizer_update', 'save');

  // Add venue data to request
  $request->params['id'] = $organizer->organizer_id;
  $request->params['name'] = $organizer->name;
  $request->params['description'] = $organizer->description;

  // XML data will only come back if no error
  if ($result = _eventbrite_common_process_request($request)) {
    // Populate the event coming back and return it
    $xml_object = $result->object;

    if ($organizer_id = (integer) $xml_object->id) {
      // Record in watchdog
      $message = (string) $xml_object->message;
      watchdog('eventbrite', "Message: %message\nEventbrite Organizer ID: %id", array('%message' => $message, '%id' => $organizer_id));

      // TODO: Expire the cache of venue listing
      _eventbrite_common_cache_expire('user_list_organizers');

      return $organizer_id;
    }
  }
}

function _eventbrite_api_organizer_new($organizer) {
  $request = _eventbrite_common_new_request('organizer_new', 'save');

  // Add venue data to request
  $request->params['name'] = $organizer->name;
  $request->params['description'] = $organizer->description;

  // XML data will only come back if no error
  if ($result = _eventbrite_common_process_request($request)) {
    // Populate the event coming back and return it
    $xml_object = $result->object;

    if ($organizer_id = (integer) $xml_object->id) {
      // Record in watchdog
      $message = (string) $xml_object->message;
      watchdog('eventbrite', "Message: %message\nEventbrite Organizer ID: %id", array('%message' => $message, '%id' => $organizer_id));

      // TODO: Expire the cache of venue listing
      _eventbrite_common_cache_expire('user_list_organizers');

      return $organizer_id;
    }
  }
}

function _eventbrite_api_venue_update($venue) {
  $request = _eventbrite_common_new_request('venue_update', 'save');

  // Add venue data to request
  $request->params['id'] = $venue->venue_id;
  $request->params['venue'] = $venue->name;
  $request->params['adress'] = $venue->address;
  $request->params['adress_2'] = $venue->address2;
  $request->params['city'] = $venue->city;
  $request->params['region'] = $venue->region;
  $request->params['postal_code'] = $venue->postal_code;
  $request->params['country_code'] = $venue->country_code;

  // XML data will only come back if no error
  if ($result = _eventbrite_common_process_request($request)) {
    // Populate the event coming back and return it
    $xml_object = $result->object;

    if ($venue_id = (integer) $xml_object->id) {
      // Record in watchdog
      $message = (string) $xml_object->message;
      watchdog('eventbrite', "Message: %message\nEventbrite Venue ID: %id", array('%message' => $message, '%id' => $venue_id));

      // TODO: Expire the cache of venue listing
      _eventbrite_common_cache_expire('user_list_venues');

      return $venue_id;
    }
  }
}

function _eventbrite_api_venue_new($venue) {
  $request = _eventbrite_common_new_request('venue_new', 'save');

  // Add venue data to request
  $request->params['venue'] = $venue->name;
  $request->params['organizer_id'] = $venue->organizer;
  $request->params['adress'] = $venue->address;
  $request->params['adress_2'] = $venue->address2;
  $request->params['city'] = $venue->city;
  $request->params['region'] = $venue->region;
  $request->params['postal_code'] = $venue->postal_code;
  $request->params['country_code'] = $venue->country;

  // XML data will only come back if no error
  if ($result = _eventbrite_common_process_request($request)) {
    // Populate the event coming back and return it
    $xml_object = $result->object;

    if ($venue_id = (integer) $xml_object->id) {
      // Record in watchdog
      $message = (string) $xml_object->message;
      watchdog('eventbrite', "Message: %message\nEventbrite Venue ID: %id", array('%message' => $message, '%id' => $venue_id));

      // TODO: Expire the cache of venue listing
      _eventbrite_common_cache_expire('user_list_venues');

      return $venue_id;
    }
  }
}


function _eventbrite_api_ticket_new($ticket) {
  $request = _eventbrite_common_new_request('ticket_new', 'save');

  // Add ticket data to request
  $request->params['event_id'] = $ticket->event_id;
  $request->params['name'] = $ticket->name;
  $request->params['quantity'] = $ticket->quantity;
  $request->params['price'] = $ticket->price;
  if (isset($request->params['description'])) {
    $request->params['description'] = $ticket->description;
  }
  if (isset($request->params['is_donation'])) {
    $request->params['is_donation'] = $ticket->is_donation;
  }

  // Result will only return if no error
  if ($result = _eventbrite_common_process_request($request)) {
    // Populate the event coming back and return it
    $xml_object = $result->object;

    // Record in watchdog
    $message = (string) $xml_object->message;
    $ticket_id = (integer) $xml_object->id;
    watchdog('eventbrite', "Message: %message\nEventbrite Ticket ID: %id", array('%message' => $message, '%id' => $ticket_id));

    return $ticket_id;
  }
}

function _eventbrite_api_ticket_update($ticket) {
  $request = _eventbrite_common_new_request('ticket_update', 'save');

  // Add ticket data to request
  $request->params['id'] = $ticket->id;
  $request->params['name'] = $ticket->name;
  $request->params['quantity'] = $ticket->quantity;
  $request->params['price'] = $ticket->price;
  if (isset($request->params['description'])) {
    $request->params['description'] = $ticket->description;
  }
  if (isset($request->params['is_donation'])) {
    $request->params['is_donation'] = $ticket->is_donation;
  }

  // XML data will only come back if no error
  if ($result = _eventbrite_common_process_request($request)) {
    // Populate the event coming back and return it
    $xml_object = $result->object;

    // Record in watchdog
    $message = (string) $xml_data->message;
    $ticket_id = (integer) $xml_object->id;
    watchdog('eventbrite', "Message: %message\nEventbrite Ticket ID: %id", array('%message' => $message, '%id' => $ticket_id));

    return $ticket_id;
  }
}

function _eventbrite_api_payment_update($payment) {
  $request = _eventbrite_common_new_request('payment_update', 'save');

  // Add payment data to request
  $request->params['event_id'] = $payment->event_id;
  $request->params['accept_paypal'] = $payment->accept_paypal;
  $request->params['paypal_email'] = $payment->paypal_email;
  $request->params['accept_google'] = $payment->accept_google;
  $request->params['google_merchant_id'] = $payment->google_merchant_id;
  $request->params['google_merchant_key'] = $payment->google_merchant_key;
  $request->params['accept_check'] = $payment->accept_check;
  $request->params['instructions_check'] = $payment->instructions_check;
  $request->params['accept_cash'] = $payment->accept_cash;
  $request->params['instructions_cash'] = $payment->instructions_cash;
  $request->params['accept_invoice'] = $payment->accept_invoice;
  $request->params['instructions_invoice'] = $payment->instructions_invoice;

  // XML data will only come back if no error
  if ($result = _eventbrite_common_process_request($request)) {
    // Populate the event coming back and return it
    $xml_object = $result->object;

    // Record in watchdog
    $message = (string) $xml_object->message;
    $event_id = (integer) $xml_object->id;
    $method = (string) $xml_object->method;
    watchdog(
      'eventbrite',
      "Message: %message\nEventbrite Payment %method for event %id",
      array('%message' => $message, '%method' => $method, '%id' => $event_id)
    );

    return $message;
  }
}
