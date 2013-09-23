<?php

/**
 * @file
 * merci views handlers 
 */


/**
 * Type setting Bucket|Resource.
 */
class merci_handler_field_merci_node_type_type_setting extends views_handler_field {
  function construct() {
    parent::construct();
    $this->additional_fields['merci_type_setting'] = 'merci_type_setting';
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
    parent::render($values);
    $type_setting = $values->{$this->aliases['merci_type_setting']};
    switch ($type_setting) {
      case 'bucket':
        return t('Bucket');

      case 'resource':
        return t('Resource');

      default:
        return t('Disabled');
    }
  }
}

/**
 * Item status.
 */
class merci_handler_field_merci_node_type_status extends views_handler_field {
  function construct() {
    parent::construct();
    // TODO: does this need an alias?
    $this->additional_fields['merci_active_status'] = 'merci_active_status';
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
    parent::render($values);
    $statuses = merci_node_type_status();
    $status = $values->{$this->aliases['merci_active_status']};
    return $statuses[$status];
  }
}

/**
 * Reservation status.
 */
class merci_handler_field_merci_reservation_status extends views_handler_field {
  function construct() {
    parent::construct();
    // TODO: does this need an alias?
    $this->additional_fields['merci_reservation_status'] = 'merci_reservation_status';
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
    parent::render($values);
    $statuses = merci_record_status();
    $status = $values->{$this->aliases['merci_reservation_status']};
    return $statuses[$status];
  }
}

/**
 * Bucket/resource default availability.
 */
class merci_handler_field_merci_bucket_resource_node_default_availability extends views_handler_field {
  function construct() {
    parent::construct();
    $this->additional_fields['merci_default_availability'] = 'merci_default_availability';
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
    parent::render($values);
    $availabilities = merci_item_status();
    $availability = $values->{$this->aliases['merci_default_availability']};
    return $availabilities[$availability];
  }
}

/**
 * Bucket|Resource sub type.
 */
class merci_handler_field_merci_bucket_resource_node_sub_type extends views_handler_field {


  function construct() {
    parent::construct();
    $this->additional_fields['merci_sub_type'] = 'merci_sub_type';
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
    parent::render($values);
    $sub_type = $values->{$this->aliases['merci_sub_type']};
    switch ($sub_type) {
      case MERCI_SUB_TYPE_ITEM:
        return t('Item');

      case MERCI_SUB_TYPE_RESERVATION:
        return t('Reservation placeholder');

      default:
        return t('Unknown');
    }
  }
}

/**
 * Bucket/resource default availability.
 */
class merci_handler_field_merci_reservation_item_node_item_status extends views_handler_field {
  function construct() {
    parent::construct();
    $this->additional_fields['merci_item_status'] = 'merci_item_status';
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
    parent::render($values);
    $availabilities =  merci_item_reservation_status();
    $availability = $values->{$this->aliases['merci_item_status']};
    return $availabilities[$availability];
  }
}
