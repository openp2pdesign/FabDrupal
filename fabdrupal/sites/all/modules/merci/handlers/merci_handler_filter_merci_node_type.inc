<?php
/**
 * Filter by node type
 */
class merci_handler_filter_merci_node_type extends views_handler_filter_in_operator {
  var $value_form_type = 'select';

  function get_value_options() {
    if (!isset($this->value_options)) {
      $this->value_title = t('Reservable Content types');
      $merci_types = merci_content_types();
      $options = array();

      // Group the buckets.
      $vid = variable_get('merci_equipment_grouping_vid', 0);
      // With the correct weight.
      $terms = taxonomy_get_tree($vid);
      foreach ($terms as $term) {
        $options[$term->name] = array();
      }
      // This array holds all reservable items the user may reserve.
      // Loop through each bucket type.

      foreach ($merci_types as $type => $value) {
    /*
    if ($value['merci_active_status'] != MERCI_STATUS_ACTIVE) {
      continue;
    }
     */
        if (!merci_check_content_type_user_permissions($type)) {
          continue;
        }
        $options[$value['merci_item_grouping']][$type] = $value['type_name'];
      }

      // Remove grouping keys with no items.
      foreach ($terms as $term) {
        if (empty($options[$term->name])) {
          unset ($options[$term->name]);
        }
      }

      $this->value_options = $options;
    }
  }
}
