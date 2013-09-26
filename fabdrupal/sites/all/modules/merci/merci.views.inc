<?php


/**
 * @file
 * Expose MERCI information to Views.
 */

/**
 * Implements hook_views_data().
 */
function merci_views_data() {
  $data = array();

  // merci_node_type
  $data['merci_node_type']['table']['group'] = t('MERCI');
  $data['merci_node_type']['table']['join']['node'] = array(
    'left_field' => 'type',
    'field' => 'type',
    'type' => 'INNER',
  );
  $data['merci_node_type']['type_setting'] = array(
    'title' => t('MERCI type'),
    'help' => t('The MERCI type (Bucket|Resource).'),
    'real field' => 'merci_type_setting',
    'field' => array(
      'handler' => 'merci_handler_field_merci_node_type_type_setting',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
    'filter' => array(
      'handler' => 'merci_handler_filter_merci_node_type_type_setting',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['merci_node_type']['max_hours_per_reservation'] = array(
    'title' => t('Max hours per reservation'),
    'help' => t('The maximum hours that the item can be reserved for.'),
    'real field' => 'merci_max_hours_per_reservation',
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['merci_node_type']['allow_overnight'] = array(
    'title' => t('Allow overnight'),
    'help' => t('TRUE if the item can be kept overnight.'),
    'real field' => 'merci_allow_overnight',
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
      'label' => t('Allowed overnight'),
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['merci_node_type']['allow_weekends'] = array(
    'title' => t('Allow weekends'),
    'help' => t('TRUE if the item can be kept over weekends.'),
    'real field' => 'merci_allow_weekends',
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
      'label' => t('Allowed over weekends'),
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['merci_node_type']['late_fee_per_hour'] = array(
    'title' => t('Late fee per hour -- default'),
    'help' => t('Default per hour fee if the item is returned late (as defined by MERCI type).'),
    'real field' => 'merci_late_fee_per_hour',
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['merci_node_type']['rate_per_hour'] = array(
    'title' => t('Rate per hour -- default'),
    'help' => t('Default per hour fee for use of the item (as defined by MERCI type).'),
    'real field' => 'merci_rate_per_hour',
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['merci_node_type']['fee_free_hours'] = array(
    'title' => t('Fee free hours -- default'),
    'help' => t('Default number of hours the item can be used before fees are charged (as defined by MERCI type).'),
    'real field' => 'merci_fee_free_hours',
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['merci_node_type']['status'] = array(
    'title' => t('Bucket/Resource Status'),
    'help' => t('The status of the Bucket/Resource.'),
    'real field' => 'merci_active_status',
    'field' => array(
      'handler' => 'merci_handler_field_merci_node_type_status',
      'click sortable' => TRUE,
    ),
    // TODO: there really should be a custom handler for this.
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
    'filter' => array(
      'handler' => 'merci_handler_filter_merci_node_type_status',
    ),
    'sort' => array(
      // TODO: this needs a custom handler.
      'handler' => 'views_handler_sort',
    ),
  );
  $data['merci_node_type']['spare_items'] = array(
    'title' => t('Bucket spare items'),
    'help' => t('Number of spare items to leave unreserved for the bucket.'),
    'real field' => 'merci_spare_items',
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // merci_reservation
  $data['merci_reservation']['table']['group'] = t('MERCI');
  $data['merci_reservation']['table']['join']['node'] = array(
    'left_field' => 'vid',
    'field' => 'vid',
    'type' => 'INNER',
  );
  $data['merci_reservation']['status'] = array(
    'title' => t('Reservation status'),
    'help' => t('The status of the reservation.'),
    'real field' => 'merci_reservation_status',
    'field' => array(
      'handler' => 'merci_handler_field_merci_reservation_status',
      'click sortable' => TRUE,
    ),
    // TODO: there really should be a custom handler for this.
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
    'filter' => array(
      'handler' => 'merci_handler_filter_merci_reservation_status',
    ),
    'sort' => array(
      // TODO: this needs a custom handler.
      'handler' => 'views_handler_sort',
    ),
  );

  // merci_reservation_detail
  $data['merci_reservation_detail3']['table']['group'] = t('MERCI');
  $data['merci_reservation_detail3']['table']['join']['node'] = array(
    'left_field' => 'nid',
    'field' => 'merci_item_nid',
    'table' => 'merci_reservation_detail',
  );
  $data['merci_reservation_detail3']['date_argument'] = array(
    'group' => t('Date'),
    'title' => t('Date for reservation detail (for item nid)'),
    'help' => t('Filter any Views date field by a date argument'),
    'argument' => array(
      'handler' => 'date_api_argument_handler',
      'empty name field' => t('Undated'),
    ),
  );
  $data['merci_reservation_detail3']['vid'] = array(
    'title' => t('Reservation nid (for item nid)'),
    'help' => t('The node id of the reservation for this item id.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
      'skip base' => array('node'),
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_in_operator',
    ),
    'relationship' => array(
      'base' => 'node',
      'base field' => 'vid',
      'label' => t('Reservation for item node id'),
    ),
  );

  // merci_reservation_detail
  $data['merci_reservation_detail2']['table']['group'] = t('MERCI');
  $data['merci_reservation_detail2']['table']['join']['node'] = array(
    'left_field' => 'nid',
    'field' => 'merci_placeholder_nid',
    //'type' => 'INNER',
    'table' => 'merci_reservation_detail',
  );
  $data['merci_reservation_detail2']['date_argument'] = array(
    'group' => t('Date'),
    'title' => t('Date for reservation detail'),
    'help' => t('Filter any Views date field by a date argument'),
    'argument' => array(
      'handler' => 'date_api_argument_handler',
      'empty name field' => t('Undated'),
    ),
  );
  $data['merci_reservation_detail2']['nid'] = array(
    'title' => t('Reservation nid'),
    'help' => t('The node id of the reservation for this placeholder item.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
      'skip base' => array('node'),
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_in_operator',
    ),
    'relationship' => array(
      'base' => 'node',
      'base field' => 'nid',
      'label' => t('Reservation for placeholder item node id'),
    ),
  );


  // merci_reservation_detail
  $data['merci_reservation_detail']['table']['group'] = t('MERCI');
  $data['merci_reservation_detail']['table']['join']['node'] = array(
    'left_field' => 'vid',
    'field' => 'vid',
    //'type' => 'INNER',
  );
  $data['merci_reservation_detail']['placeholder_nid'] = array(
    'title' => t('Reserved placeholder nid'),
    'help' => t('The node id of the reserved placeholder item.'),
    'real field' => 'merci_placeholder_nid',
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
      'skip base' => array('node'),
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_in_operator',
    ),
    'relationship' => array(
      'base' => 'node',
      'field' => 'nid',
      'relationship field' => 'merci_placeholder_nid',
      'label' => t('Reserved placeholder item node id'),
    ),
  );


  $data['merci_reservation_detail']['item_nid'] = array(
    'title' => t('Reserved item nid'),
    'help' => t('The node id of the reserved item.'),
    'real field' => 'merci_item_nid',
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
      'skip base' => array('node'),
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'merci_views_handler_filter_reserved_item_nid',
      'numeric' => TRUE,
      'help' => t('<strong>Reservations</strong> are filtered for specific reserved items.'),
    ),
    'relationship' => array(
      'base' => 'node',
      'field' => 'nid',
      'relationship field' => 'merci_item_nid',
      'label' => t('Reserved item node id'),
    ),
  );
  $data['merci_reservation_detail']['item_nid2'] = array(
    'title' => t('Reserved items'),
    'help' => t('Display all items reserved by this reservation.'),
    'field' => array(
      'title' => t('Reserved items'),
      'help' => t('Display all items reserved by this reservation.'),
      'handler' => 'views_handler_field_item_node_nid',
    ),
  );


  // merci_bucket_node
  $data['merci_bucket_node']['table']['group'] = t('MERCI');
  $data['merci_bucket_node']['table']['join']['node'] = array(
    'left_field' => 'vid',
    'field' => 'vid',
    'type' => 'LEFT',
  );

  // merci_resource_node
  $data['merci_resource_node']['table']['group'] = t('MERCI');
  $data['merci_resource_node']['table']['join']['node'] = array(
    'left_field' => 'vid',
    'field' => 'vid',
    'type' => 'LEFT',
  );
  $data['merci_resource_node']['late_fee_per_hour'] = array(
    'title' => t('Late fee per hour -- resource'),
    'help' => t('Per hour fee if the item is returned late (as defined by the individual resource).'),
    'real field' => 'merci_late_fee_per_hour',
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['merci_resource_node']['rate_per_hour'] = array(
    'title' => t('Rate per hour -- resource'),
    'help' => t('Per hour fee for use of the item (as defined by the individual resource).'),
    'real field' => 'merci_rate_per_hour',
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['merci_resource_node']['fee_free_hours'] = array(
    'title' => t('Fee free hours -- resource'),
    'help' => t('Number of hours the item can be used before fees are charged (as defined by the individual resource).'),
    'real field' => 'merci_fee_free_hours',
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // merci_resource_node
  $data['merci_reservation_item_node']['table']['group'] = t('MERCI');
  $data['merci_reservation_item_node']['table']['join']['node'] = array(
    'left_field' => 'vid',
    'field' => 'vid',
    'type' => 'LEFT',
  );
  $data['merci_reservation_item_node']['default_availability'] = array(
    'title' => t('Default booking availability -- resource/bucket'),
    'help' => t('The default booking availability of a Resource or Bucket type (ex. Available|Unavailable).'),
    'real field' => 'merci_default_availability',
    'field' => array(
      'handler' => 'merci_handler_field_merci_bucket_resource_node_default_availability',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      // TODO: this needs a custom handler.
      'handler' => 'views_handler_argument_numeric',
    ),
    'filter' => array(
      'handler' => 'merci_handler_filter_merci_bucket_resource_node_default_availability',
    ),
    'sort' => array(
      // TODO: this needs a custom handler.
      'handler' => 'views_handler_sort',
    ),
  );
  $data['merci_reservation_item_node']['sub_type'] = array(
    'title' => t('Sub type -- resource/bucket'),
    'help' => t('The sub type of the Resource or Bucket (Item|Reservation placeholder).'),
    'real field' => 'merci_sub_type',
    'field' => array(
      'handler' => 'merci_handler_field_merci_bucket_resource_node_sub_type',
      'click sortable' => TRUE,
    ),
    // TODO: there really should be a custom handler for this.
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
    'filter' => array(
      'handler' => 'merci_handler_filter_merci_bucket_resource_node_sub_type',
    ),
    'sort' => array(
      // TODO: this needs a custom handler.
      'handler' => 'views_handler_sort',
    ),
  );
  $data['merci_reservation_item_node']['item_status'] = array(
    'title' => t('Reservation Status of Item'),
    'help' => t('Is the reservable item currently checked out.'),
    'real field' => 'merci_item_status',
    'field' => array(
      'handler' => 'merci_handler_field_merci_reservation_item_node_item_status',
      'click sortable' => TRUE,
    ),
    // TODO: there really should be a custom handler for this.
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
    'filter' => array(
      'handler' => 'merci_handler_filter_merci_reservation_item_node_item_status',
    ),
    'sort' => array(
      // TODO: this needs a custom handler.
      'handler' => 'views_handler_sort',
    ),
  );
  $data['node']['merci_content_type'] = array(
    'title' => t('Reservable content types'),
    'group' => t('MERCI'),
    'help' => t('Filter by reservable content types'),
    'real field' => 'type',
    'filter' => array(
      'handler' => 'merci_handler_filter_merci_node_type',
    ),
  );
  return $data;
}

/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function merci_views_plugins() {
  return array(
    'module' => 'views', // This just tells our themes are elsewhere.
    'argument validator' => array(
      'merci' => array(
        'title' => t('MERCI'),
        'handler' => 'views_plugin_argument_validate_merci_node',
        'path' => drupal_get_path('module', 'merci'), // not necessary for most modules
      ),
    ),
  );
}

function merci_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'merci') . '/handlers',
    ),
    'handlers' => array(
      'views_handler_field_item_node_nid' => array(
        'parent' => 'views_handler_field_prerender_list',
        'file' => 'views_handler_field_item_node_nid.inc',
      ),
      'merci_handler_field_merci_node_type_type_setting' => array(
        'parent' => 'views_handler_field',
        'file' => 'merci_handler_field.inc',
      ),
      'merci_handler_filter_merci_node_type_type_setting' => array(
        'parent' => 'views_handler_filter_in_operator',
        'file' => 'merci_handler_filter_in_operator.inc',
      ),
      'merci_handler_filter_merci_node_type' => array(
        'parent' => 'views_handler_filter_in_operator',
        'file' => 'merci_handler_filter_merci_node_type.inc',
      ),
      'merci_handler_field_merci_node_type_status' => array(
        'parent' => 'views_handler_field',
        'file' => 'merci_handler_field.inc',
      ),
      'merci_handler_filter_merci_node_type_status' => array(
        'parent' => 'views_handler_filter_in_operator',
        'file' => 'merci_handler_filter_in_operator.inc',
      ),
      'merci_handler_field_merci_reservation_status' => array(
        'parent' => 'views_handler_field',
        'file' => 'merci_handler_field.inc',
      ),
      'merci_handler_filter_merci_reservation_status' => array(
        'parent' => 'views_handler_filter_in_operator',
        'file' => 'merci_handler_filter_in_operator.inc',
      ),
      'merci_handler_field_merci_bucket_resource_node_default_availability' => array(
        'parent' => 'views_handler_field',
        'file' => 'merci_handler_field.inc',
      ),
      'merci_handler_filter_merci_bucket_resource_node_default_availability' => array(
        'parent' => 'views_handler_filter_in_operator',
        'file' => 'merci_handler_filter_in_operator.inc',
      ),
      'merci_handler_field_merci_bucket_resource_node_sub_type' => array(
        'parent' => 'views_handler_field',
        'file' => 'merci_handler_field.inc',
      ),
      'merci_handler_filter_merci_bucket_resource_node_sub_type' => array(
        'parent' => 'views_handler_filter_in_operator',
        'file' => 'merci_handler_filter_in_operator.inc',
      ),
      // filter
      'merci_views_handler_filter_reserved_item_nid' => array(
        'parent' => 'views_handler_filter_many_to_one',
      ),
      'merci_handler_field_merci_reservation_item_node_item_status' => array(
        'parent' => 'views_handler_field',
        'file' => 'merci_handler_field.inc',
      ),
      'merci_handler_filter_merci_reservation_item_node_item_status' => array(
        'parent' => 'views_handler_filter_in_operator',
        'file' => 'merci_handler_filter_in_operator.inc',
      ),
    ),
  );
}

