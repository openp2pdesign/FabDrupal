Eventbrite 2.x

Eventbrite 2.x offers Drupal sites the ability to manage Eventbrite events from
within Drupal. Site builders can create and edit events as well as other
Eventbrite entities such as venues, tickets, payment settings and organizers.
CCK serves as the bridge to the Eventbrite API. There is an event field that can
be attached to nodes.

The base module exposes an API for other modules to call.


Eventbrite Base Module (API)

Calls made to the server are cached to cut down on unnecessary requests as well
as decreasing page render time.
  
Exposed API functions (callable by UI submodules)

eventbrite_get($op, $id = NULL);
  Params: $op  The remote API method at Eventbrite server
               Current supported $op values are:
                 user_list_events
                 event_get
          $id  Optional param for the remote API calls that take an id key

eventbrite_save($op, $object);
  Params: $op  The remote API method at Eventbrite server
               Current supported $op values are:
                 event_new
          $id  Object to be saved

Exposed Hooks

hook_eventbrite_request_alter(&$request);
  This hook allows UI submodules to alter the request before it goes to the
  Eventbrite server. This will allow modules to alter the maximum cache time as
  well as change the user making the request. It is used by Eventbrite OG to
  allow for user authentication by group.


Installation
------------

Download the Eventbrite library: 
  https://github.com/ryanjarvinen/eventbrite.php/archive/master.zip

Extract it to sites/all/libraries. Rename the resulting folder so the included
php file is at sites/all/libraries/eventbrite/Eventbrite.php.

Enable the Eventbrite and Eventbrite Field modules.

Go to admin/config/services/eventbrite/api and enter the keys.


Usage
-----

Add a new field of type Eventbrite to a content type on your site. If you choose
widget type "autocomplete", the autocomplete will only search for events created
by the user whose key is saved on the configuration page, but it will still be
possible to type in any event ID.

Go to "Manage display" page for your content type and choose whether to display
the event as a link to the event on eventbrite.com or a registration widget
(uses an iframe).
