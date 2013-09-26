<?php
/**
 * @file
 * machine_reservation.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function machine_reservation_default_rules_configuration() {
  $items = array();
  $items['rules_e_mail_for_booking_notification_to_admins'] = entity_import('rules_config', '{ "rules_e_mail_for_booking_notification_to_admins" : {
      "LABEL" : "E-mail for booking notification to admins",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules" ],
      "ON" : [ "node_insert" ],
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : { "merci_reservation" : "merci_reservation" } }
          }
        }
      ],
      "DO" : [
        { "mail_to_users_of_role" : {
            "roles" : { "value" : { "3" : "3" } },
            "subject" : "Reservation notification",
            "message" : "A new reservation has been made in the website."
          }
        }
      ]
    }
  }');
  return $items;
}
