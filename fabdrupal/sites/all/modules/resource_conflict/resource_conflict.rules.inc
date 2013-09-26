<?php
/**
 * Implementation of hook_rules_event_info()
 * Provides a Rules event for "Resource Conflict Detected"
 * Fires during node form validation
 */
function resource_conflict_rules_event_info() {
  return array(
    'resource_conflict_conflict_detected' => array(
      'group' => t('Resource Conflict'),
      'label' => t('A resource conflict was detected'),
      'module' => 'resource_conflict',
      'variables' => array(
        'node' => array(
          'type' => 'node',
          'label' => t('unsaved node'),
        ),
        'conflict_node' => array(
          'type' => 'node',
          'label' => t('conflicting node'),
        ),
      ),
    ),
    'resource_conflict_node_validation' => array(
      'group' => t('Resource Conflict'),
      'label' => t('A resource conflict node form is validated'),
      'module' => 'resource_conflict',
      'variables' => array(
        'node' => array(
          'type' => 'node',
          'label' => t('unsaved node'),
        ),
        'form' => array(
          'type' => 'form',
          'label' => 'form',
        )
      )
    )
  );
}

/** 
 * Implementation of hook_rules_condition_info()
 * Provides a Rules condition for "contains a resource conflict"
 */
function resource_conflict_rules_condition_info() {
  return array(
    'resource_conflict_contains_conflict' => array(
      'group' => t('Resource Conflict'),
      'label' => t('Contains a resource conflict'),
      'module' => 'resource_conflict',
      'parameter' => array(
        'node' => array(
          'type' => 'node',
          'label' => t('Node'),
        )
      ),
    ),
  );
}


/** 
 * Implementation of hook_rules_action_info()
 * Provides a Rules action for "load list of conflicting nodes"
 */
function resource_conflict_rules_action_info() {
  return array(
    'resource_conflict_load_conflict_list' => array(
      'group' => t('Resource Conflict'),
      'label' => t('Load a list of conflicting nodes'),
      'module' => 'resource_conflict',
      'parameter' => array(
        'node' => array(
          'type' => 'node',
          'label' => t('node to check for conflicts'),
        ),
      ),
      'provides' => array(
        'conflict_list' => array(
          'type' => 'list<node>',
          'label' => t('Conflict List'),
        ),
      ),
    ),
    'resource_conflict_form_error' => array(
      'group' => t('Resource Conflict'),
      'label' => t('Set a form validation error'),
      'module' => 'resource_conflict',
      'parameter' => array(
        'message' => array(
          'type' => 'text',
          'label' => t('Message to display'),
        ),
      ),
    ),
  );
}
