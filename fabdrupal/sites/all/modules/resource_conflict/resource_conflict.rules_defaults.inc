<?php

/**
 * @file
 * Default rule configurations for Resource Conflict. 
 */

/**
 * Implements hook_default_rules_configuration().
 */
function resource_conflict_default_rules_configuration() {
  $rules = array();

  // Add an example reaction rule to display a warning message if conflicts detected
  $rules['rules_display_conflict_message_on_node_save'] = entity_import('rules_config', '{ "rules_display_conflict_message_on_node_save" : {
    "LABEL" : "Display conflict message on node save",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "resource_conflict", "rules" ],
      "ON" : [ "resource_conflict_node_validation" ],
      "IF" : [ { "resource_conflict_contains_conflict" : { "node" : [ "node" ] } } ],
      "DO" : [
        { "resource_conflict_load_conflict_list" : {
          "USING" : { "node" : [ "node" ] },
          "PROVIDE" : { "conflict_list" : { "conflict_list" : "Conflict List" } }
          }
        },
        { "LOOP" : {
          "USING" : { "list" : [ "conflict-list" ] },
          "ITEM" : { "list_item" : "Current list item" },
          "DO" : [
            { "resource_conflict_form_error" : { "message" : "Resource conflict detected with [list-item:title] " } }
          ]
          }
        }
      ]
    }
  }');

  return($rules);
}
?>
