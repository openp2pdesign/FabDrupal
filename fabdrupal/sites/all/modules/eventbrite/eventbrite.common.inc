<?php

/**
 * @file
 * Implements the request handling for communicating with the Eventbrite server
 */

define('EVENTBRITE_SERVER', 'https://www.eventbrite.com/xml/');

/*
 * Build a request object
 */
function _eventbrite_common_new_request($op, $op_type) {
  $request = new stdClass();
  $request->op = $op;
  $request->op_type = $op_type;
  $request->allowed_cache = ($op_type == 'get') ? 60 * variable_get('eventbrite_cache_minimum', 5) : 0;
  $request->user_key = variable_get('eventbrite_user_key', '');
  $request->params = array();
  $request->module = 'eventbrite';

  if ($request->user_key) {
    return $request;
  }
}

/*
 * Process a request object that has been modified by an API function
 */
function _eventbrite_common_process_request($request) {
  // Verify that keys have been authenticated before making and requests
  if (!eventbrite_is_valid_auth() || !($app_key = variable_get('eventbrite_app_key', ''))) {
    // TODO: Add link to admin settings form in message
    drupal_set_message('Could not authenticate with the Eventbrite server.  Please contact the site administrator.', 'error');
    $watchdog_message = t('_eventbrite_common_process_request called while eventbrite_is_valid_auth() returns false.  ' . "\n");
    $watchdog_message .= t('Verify that valid authentication keys have been entered.  ' . "\n");
    $watchdog_message .= t('Request: !request', array('!request' => $result->request)) . "\n";
    watchdog('eventbrite', $watchdog_message, NULL, WATCHDOG_ERROR);
    return FALSE;
  }

  // Invoke hook_eventbrite_request_alter for sub modules to make changes
  // Do not invoke for user_get calls, user_get should never be altered
  switch ($request->op) {
    case 'user_get':
      break;
    default:
      // Manually call each hook here since module_invoke_all doesn't support hooks with references as params
      foreach (module_implements('eventbrite_request_alter') as $module) {
        $function = $module . '_eventbrite_request_alter';
        $function($request);
      }
      break;
  }

  // Build query string from $request object
  $request->id = isset($request->params['id']) ? $request->params['id'] : 0;
  $request->params['user_key'] = $request->user_key;
  $request->params['app_key'] = $app_key;
  $param_list = array();
  foreach ($request->params as $key => $value) {
    $param_list[] = $key . '=' . urlencode($value);
  }
  $request->query_string = join('&', $param_list);

  // Check cache, if there is something there and it is recent enough then use it
//   Otherwise make a call to the Eventbrite server
  if ($request->op_type == 'get' && $request->allowed_cache) {
    if ($cached_result = _eventbrite_common_check_cache($request)) {
      // There is a cached result, check if it is recent enough to use
      $now = REQUEST_TIME;
      if (($cached_result->timestamp + $request->allowed_cache) > $now) {
        // Cache is still valid
        // Build fake result object out of the cached_result
        $result = new stdClass();
        $result->data = $cached_result->result;
        if ($result->object = simplexml_load_string($result->data)) {
          $result->source = 'cache';
          $result->updated = FALSE;
          $result->module = $request->module;
          $result->user_key = $request->user_key;

          return $result;
        }
      }
    }
  }

  if (variable_get('eventbrite_debug', 0)) {
    drupal_set_message(EVENTBRITE_SERVER . $request->op . '?' . $request->query_string); //exit(4);
  }

  // Send HTTP request to the server - since we don't have fresh data
  if ($result = drupal_http_request(EVENTBRITE_SERVER . $request->op . '?' . $request->query_string) ) {
    $result->module = $request->module;
    $result->user_key = $request->user_key;
    // Process the result if there was one, and return simplexml_load_string($result->data)
    if (_eventbrite_common_process_result($result)) {
      $result->source = 'server';

      // If this was a get operation then cache the results
      if ($request->op_type == 'get') {
        $result->updated = TRUE;


        if ($request->allowed_cache) {
          if (isset($cached_result)) {
//          	drupal_set_message('Checking to see about updating cache with new result');
            // There was already a cached result, so we'll need to update the cache
            if (strcmp($cached_result->result, $result->data)) {
              // XML return is different from the cache, return previous cached string for comparison
              $result->prev_cache = $cached_result->result;
//              drupal_set_message('New result invalidates the cached value');
            }
            else {
              // XML data returned is the same, just update the timestamp
              $result->updated = FALSE;
//              drupal_set_message('New result matches the cached value');
            }
//            drupal_set_message('Updating cache');
            // Same update call whether result from server has changed or not
            _eventbrite_common_cache_result($result->data, $request, 'update');
          }
          else {
//            drupal_set_message('Inserting into cache');
            // There was no cached result, so we'll need to insert into the cache
            _eventbrite_common_cache_result($result->data, $request, 'insert');
          }
        }
      }
      return $result;
    }
  }
}

/*
 * Process the result returned by the server
 */
function _eventbrite_common_process_result(&$result) {
  // Check HTTP return code
  if ($result->code) {
    switch ($result->code) {
      // Valid HTTP Request
      case 200:
        $result->object = $xml_object = simplexml_load_string($result->data);

        // If error type is set, log to watchdog
        if (isset($xml_object->error_message)) {
          $result->success = FALSE;

          $watchdog_message = t('Error type: !error_type', array('!error_type' => $xml_object->error_type)) . "\n";
          $watchdog_message .= t('Error msg: !error_message', array('!error_message' => $xml_object->error_message)) . "\n";
          $watchdog_message .= t('Request: !request', array('!request' => $result->request)) . "\n";
          watchdog('eventbrite', $watchdog_message, NULL, WATCHDOG_WARNING);

          // TODO: Set this via drupal_set_message, ideally we could get rid of eventbrite_errors()
          eventbrite_errors(t((string) $xml_object->error_message), (string) $xml_object->error_type);
          return;
        }

        $result->success = TRUE;
        return TRUE;

      default:
        $result->success = FALSE;
        // Bad web connection
        $watchdog_message = t('Error code: !code', array('!code' => $result->code)) . "\n";
        $watchdog_message .= t('Error msg: !error', array('!error' => $result->error)) . "\n";
        $watchdog_message .= t('Request: !request', array('!request' => $result->request)) . "\n";
        watchdog('eventbrite', $watchdog_message, NULL, WATCHDOG_ERROR);

        // TODO: Set this via drupal_set_message, ideally we could get rid of eventbrite_errors()
        eventbrite_errors(t('The Eventbrite server can not be reached at this time.  Please contact the system administrator'));

        return;
    }
  }
}

/*
 * Check the cache for previous responses from Eventbrite server
 */
function _eventbrite_common_check_cache($request) {
  $result = db_query('SELECT * FROM {eventbrite_cache} WHERE op = :op AND id = :id AND query_string = :query_string', array(':op' => $request->op, ':id' => $request->id, ':query_string' => $request->query_string));

  if ($result) {
    foreach ($result AS $row) {
      return $row;
    }
  }
}

/*
 * Cache a response from the Eventbrite server
 */
function _eventbrite_common_cache_result($result, $request, $db_op) {
  $request->result = $result;
  $request->timestamp = REQUEST_TIME;
  switch ($db_op) {
    case 'insert':
      drupal_write_record('eventbrite_cache', $request);
      break;
    case 'update':
      drupal_write_record('eventbrite_cache', $request, array('op', 'id', 'query_string'));
      break;
  }
}

/*
 * Expire a cached response from the Eventbrite server
 */
function _eventbrite_common_cache_expire($op, $id = 0) {
  $values = array(
    'op' => $op,
    'id' => $id,
    'timestamp' => 0,
  );
  drupal_write_record('eventbrite_cache', $values, array('op', 'id'));
}
