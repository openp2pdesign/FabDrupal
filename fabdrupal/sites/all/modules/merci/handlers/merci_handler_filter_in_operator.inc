<?php

/**
 * @file
 * merci views handlers 
 */


/**
 * Filter by type_setting
 */
class merci_handler_filter_merci_node_type_type_setting extends views_handler_filter_in_operator {
  function get_value_options() {
    if (!isset($this->value_options)) {
      $this->value_title = t('Type setting');
      $options = array(
        'disabled' => t('Disabled'),
        'bucket' => t('Bucket'),
        'resource' => t('Resource'),
      );
      $this->value_options = $options;
    }
  }
}

/**
 * Filter by item status
 */
class merci_handler_filter_merci_node_type_status extends views_handler_filter_in_operator {
  function get_value_options() {
    if (!isset($this->value_options)) {
      $this->value_title = t('Status');
      $this->value_options = merci_item_status();
    }
  }
}

/**
 * Filter by reservation status
 */
class merci_handler_filter_merci_reservation_status extends views_handler_filter_in_operator {
  function get_value_options() {
    if (!isset($this->value_options)) {
      $this->value_title = t('Status');
      $this->value_options = merci_record_status();
    }
  }
}

/**
 * Filter by bucket/resource default availability.
 */
class merci_handler_filter_merci_bucket_resource_node_default_availability extends views_handler_filter_in_operator {
  function get_value_options() {
    if (!isset($this->value_options)) {
      $this->value_title = t('Default availability');
      $this->value_options = merci_item_status();
    }
  }
}

/**
 * Filter by bucket/resource sub type.
 */
class merci_handler_filter_merci_bucket_resource_node_sub_type extends views_handler_filter_in_operator {
  function get_value_options() {
    if (!isset($this->value_options)) {
      $this->value_title = t('Sub type');
      $this->value_options = array(
        MERCI_SUB_TYPE_ITEM => t('Item'),
        MERCI_SUB_TYPE_RESERVATION => t('Reservation placeholder'),
      );
    }
  }
}

/**
 * Filter by bucket/resource default availability.
 */
class merci_handler_filter_merci_reservation_item_node_item_status extends views_handler_filter_in_operator {
  function get_value_options() {
    if (!isset($this->value_options)) {
      $this->value_title = t('Availability');
      $this->value_options = merci_item_reservation_status();
    }
  }
}

