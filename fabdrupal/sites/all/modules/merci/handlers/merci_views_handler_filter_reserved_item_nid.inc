<?php
class merci_views_handler_filter_reserved_item_nid extends views_handler_filter_many_to_one {
  function get_value_options() {
    $this->value_options = $this->allowed_values();
  }

  // Get allowed values from hook_allowed_values(), if any,
  // or from content_allowed_values();
  function allowed_values() {
    $options = array();
    $merci_types = merci_content_types();
    foreach ($merci_types as $merci_type => $type_setting) {
      $options += merci_get_reservable_items($merci_type);
    }
    return $options;
  }

}
