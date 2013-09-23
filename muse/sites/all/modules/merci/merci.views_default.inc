<?php

/**
 * @file
 * merci reservable item view
 */


/**
 * Implements hook_views_default_views().
 */
function merci_views_default_views() {

  $view = new view;
  $view->name = 'merci_reservable_items';
  $view->description = 'Merci Reservable Items';
  $view->tag = '';
  $view->base_table = 'node';
  $view->human_name = '';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['items_per_page'] = 0;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 0,
      'separator' => '',
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  /* Relationship: MERCI: Reservation nid (for item nid) */
  $handler->display->display_options['relationships']['vid']['id'] = 'vid';
  $handler->display->display_options['relationships']['vid']['table'] = 'merci_reservation_detail3';
  $handler->display->display_options['relationships']['vid']['field'] = 'vid';
  $handler->display->display_options['relationships']['vid']['label'] = 'Reservation for placeholder item node id';
  $handler->display->display_options['relationships']['vid']['required'] = 1;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['nid']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['nid']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['html'] = 0;
  $handler->display->display_options['fields']['nid']['hide_empty'] = 0;
  $handler->display->display_options['fields']['nid']['empty_zero'] = 0;
  $handler->display->display_options['fields']['nid']['link_to_node'] = 0;
  /* Field: Content: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'node';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  $handler->display->display_options['fields']['type']['exclude'] = TRUE;
  $handler->display->display_options['fields']['type']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['type']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['type']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['type']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['type']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['type']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['type']['alter']['html'] = 0;
  $handler->display->display_options['fields']['type']['hide_empty'] = 0;
  $handler->display->display_options['fields']['type']['empty_zero'] = 0;
  $handler->display->display_options['fields']['type']['link_to_node'] = 0;
  $handler->display->display_options['fields']['type']['machine_name'] = 0;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 1;
  $handler->display->display_options['fields']['title']['alter']['path'] = 'node/[nid]/edit?destination=admin/merci/manage/current_inventory/[type]/Available';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['link_to_node'] = 0;
  /* Field: MERCI: Allow overnight */
  $handler->display->display_options['fields']['allow_overnight']['id'] = 'allow_overnight';
  $handler->display->display_options['fields']['allow_overnight']['table'] = 'merci_node_type';
  $handler->display->display_options['fields']['allow_overnight']['field'] = 'allow_overnight';
  $handler->display->display_options['fields']['allow_overnight']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['allow_overnight']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['allow_overnight']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['allow_overnight']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['allow_overnight']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['allow_overnight']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['allow_overnight']['alter']['html'] = 0;
  $handler->display->display_options['fields']['allow_overnight']['hide_empty'] = 0;
  $handler->display->display_options['fields']['allow_overnight']['empty_zero'] = 0;
  $handler->display->display_options['fields']['allow_overnight']['not'] = 0;
  /* Field: MERCI: Allow weekends */
  $handler->display->display_options['fields']['allow_weekends']['id'] = 'allow_weekends';
  $handler->display->display_options['fields']['allow_weekends']['table'] = 'merci_node_type';
  $handler->display->display_options['fields']['allow_weekends']['field'] = 'allow_weekends';
  $handler->display->display_options['fields']['allow_weekends']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['allow_weekends']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['allow_weekends']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['allow_weekends']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['allow_weekends']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['allow_weekends']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['allow_weekends']['alter']['html'] = 0;
  $handler->display->display_options['fields']['allow_weekends']['hide_empty'] = 0;
  $handler->display->display_options['fields']['allow_weekends']['empty_zero'] = 0;
  $handler->display->display_options['fields']['allow_weekends']['not'] = 0;
  /* Field: MERCI: Bucket spare items */
  $handler->display->display_options['fields']['spare_items']['id'] = 'spare_items';
  $handler->display->display_options['fields']['spare_items']['table'] = 'merci_node_type';
  $handler->display->display_options['fields']['spare_items']['field'] = 'spare_items';
  $handler->display->display_options['fields']['spare_items']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['spare_items']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['spare_items']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['spare_items']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['spare_items']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['spare_items']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['spare_items']['alter']['html'] = 0;
  $handler->display->display_options['fields']['spare_items']['hide_empty'] = 0;
  $handler->display->display_options['fields']['spare_items']['empty_zero'] = 0;
  /* Field: MERCI: Bucket/Resource Status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'merci_node_type';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['status']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['status']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['status']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['status']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['status']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['status']['alter']['html'] = 0;
  $handler->display->display_options['fields']['status']['hide_empty'] = 0;
  $handler->display->display_options['fields']['status']['empty_zero'] = 0;
  /* Field: MERCI: Max hours per reservation */
  $handler->display->display_options['fields']['max_hours_per_reservation']['id'] = 'max_hours_per_reservation';
  $handler->display->display_options['fields']['max_hours_per_reservation']['table'] = 'merci_node_type';
  $handler->display->display_options['fields']['max_hours_per_reservation']['field'] = 'max_hours_per_reservation';
  $handler->display->display_options['fields']['max_hours_per_reservation']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['max_hours_per_reservation']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['max_hours_per_reservation']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['max_hours_per_reservation']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['max_hours_per_reservation']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['max_hours_per_reservation']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['max_hours_per_reservation']['alter']['html'] = 0;
  $handler->display->display_options['fields']['max_hours_per_reservation']['hide_empty'] = 0;
  $handler->display->display_options['fields']['max_hours_per_reservation']['empty_zero'] = 0;
  /* Contextual filter: Content: Type */
  $handler->display->display_options['arguments']['type']['id'] = 'type';
  $handler->display->display_options['arguments']['type']['table'] = 'node';
  $handler->display->display_options['arguments']['type']['field'] = 'type';
  $handler->display->display_options['arguments']['type']['default_action'] = 'default';
  $handler->display->display_options['arguments']['type']['exception']['title_enable'] = 1;
  $handler->display->display_options['arguments']['type']['title_enable'] = 1;
  $handler->display->display_options['arguments']['type']['title'] = '%1 Detail';
  $handler->display->display_options['arguments']['type']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['type']['default_argument_options']['argument'] = 'all';
  $handler->display->display_options['arguments']['type']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['type']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['type']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['type']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['type']['specify_validation'] = 1;
  /* Filter criterion: MERCI: MERCI type */
  $handler->display->display_options['filters']['type_setting']['id'] = 'type_setting';
  $handler->display->display_options['filters']['type_setting']['table'] = 'merci_node_type';
  $handler->display->display_options['filters']['type_setting']['field'] = 'type_setting';
  $handler->display->display_options['filters']['type_setting']['value'] = array(
    'bucket' => 'bucket',
    'resource' => 'resource',
  );
  $handler->display->display_options['filters']['type_setting']['expose']['operator'] = FALSE;
  /* Filter criterion: MERCI: Sub type -- resource/bucket */
  $handler->display->display_options['filters']['sub_type']['id'] = 'sub_type';
  $handler->display->display_options['filters']['sub_type']['table'] = 'merci_reservation_item_node';
  $handler->display->display_options['filters']['sub_type']['field'] = 'sub_type';
  $handler->display->display_options['filters']['sub_type']['value'] = array(
    1 => '1',
  );
  $handler->display->display_options['filters']['sub_type']['expose']['operator'] = FALSE;

  /* Display: Available Items */
  $handler = $view->new_display('page', 'Available Items', 'page_1');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'nid' => 'nid',
    'type' => 'type',
    'title' => 'title',
    'allow_overnight' => 'allow_overnight',
    'allow_weekends' => 'allow_weekends',
    'spare_items' => 'spare_items',
    'status' => 'status',
    'max_hours_per_reservation' => 'max_hours_per_reservation',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'nid' => array(
      'sortable' => 0,
      'separator' => '',
    ),
    'type' => array(
      'sortable' => 0,
      'separator' => '',
    ),
    'title' => array(
      'sortable' => 1,
      'separator' => '',
    ),
    'allow_overnight' => array(
      'sortable' => 0,
      'separator' => '',
    ),
    'allow_weekends' => array(
      'sortable' => 0,
      'separator' => '',
    ),
    'spare_items' => array(
      'sortable' => 0,
      'separator' => '',
    ),
    'status' => array(
      'sortable' => 1,
      'separator' => '',
    ),
    'max_hours_per_reservation' => array(
      'sortable' => 0,
      'separator' => '',
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['nid']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['nid']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['html'] = 0;
  $handler->display->display_options['fields']['nid']['hide_empty'] = 0;
  $handler->display->display_options['fields']['nid']['empty_zero'] = 0;
  $handler->display->display_options['fields']['nid']['link_to_node'] = 0;
  /* Field: Content: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'node';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  $handler->display->display_options['fields']['type']['exclude'] = TRUE;
  $handler->display->display_options['fields']['type']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['type']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['type']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['type']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['type']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['type']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['type']['alter']['html'] = 0;
  $handler->display->display_options['fields']['type']['hide_empty'] = 0;
  $handler->display->display_options['fields']['type']['empty_zero'] = 0;
  $handler->display->display_options['fields']['type']['link_to_node'] = 0;
  $handler->display->display_options['fields']['type']['machine_name'] = 1;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 1;
  $handler->display->display_options['fields']['title']['alter']['path'] = 'node/[nid]/edit?destination=admin/merci/manage/current_inventory/[type]/Available';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['link_to_node'] = 0;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: MERCI: MERCI type */
  $handler->display->display_options['filters']['type_setting']['id'] = 'type_setting';
  $handler->display->display_options['filters']['type_setting']['table'] = 'merci_node_type';
  $handler->display->display_options['filters']['type_setting']['field'] = 'type_setting';
  $handler->display->display_options['filters']['type_setting']['value'] = array(
    'bucket' => 'bucket',
    'resource' => 'resource',
  );
  $handler->display->display_options['filters']['type_setting']['expose']['operator'] = FALSE;
  /* Filter criterion: MERCI: Sub type -- resource/bucket */
  $handler->display->display_options['filters']['sub_type']['id'] = 'sub_type';
  $handler->display->display_options['filters']['sub_type']['table'] = 'merci_reservation_item_node';
  $handler->display->display_options['filters']['sub_type']['field'] = 'sub_type';
  $handler->display->display_options['filters']['sub_type']['value'] = array(
    1 => '1',
  );
  $handler->display->display_options['filters']['sub_type']['expose']['operator'] = FALSE;
  /* Filter criterion: MERCI: Default booking availability -- resource/bucket */
  $handler->display->display_options['filters']['default_availability']['id'] = 'default_availability';
  $handler->display->display_options['filters']['default_availability']['table'] = 'merci_reservation_item_node';
  $handler->display->display_options['filters']['default_availability']['field'] = 'default_availability';
  $handler->display->display_options['filters']['default_availability']['value'] = array(
    1 => '1',
  );
  $handler->display->display_options['filters']['default_availability']['expose']['operator'] = FALSE;
  /* Filter criterion: MERCI: Reservation Status of Item */
  $handler->display->display_options['filters']['item_status']['id'] = 'item_status';
  $handler->display->display_options['filters']['item_status']['table'] = 'merci_reservation_item_node';
  $handler->display->display_options['filters']['item_status']['field'] = 'item_status';
  $handler->display->display_options['filters']['item_status']['value'] = array(
    0 => '0',
  );
  $handler->display->display_options['filters']['item_status']['expose']['operator'] = FALSE;
  $handler->display->display_options['path'] = 'admin/merci/manage/current_inventory/%/Available';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Available';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['tab_options']['title'] = 'current inventory';
  $handler->display->display_options['tab_options']['weight'] = '0';

  /* Display: Checked Out Items */
  $handler = $view->new_display('page', 'Checked Out Items', 'page_2');
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: MERCI: Reservation nid (for item nid) */
  $handler->display->display_options['relationships']['vid']['id'] = 'vid';
  $handler->display->display_options['relationships']['vid']['table'] = 'merci_reservation_detail3';
  $handler->display->display_options['relationships']['vid']['field'] = 'vid';
  $handler->display->display_options['relationships']['vid']['label'] = 'Reservation for placeholder item node id';
  $handler->display->display_options['relationships']['vid']['required'] = 1;
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['relationship'] = 'vid';
  $handler->display->display_options['relationships']['uid']['required'] = 0;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['nid']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['nid']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['html'] = 0;
  $handler->display->display_options['fields']['nid']['hide_empty'] = 0;
  $handler->display->display_options['fields']['nid']['empty_zero'] = 0;
  $handler->display->display_options['fields']['nid']['link_to_node'] = 0;
  /* Field: Content: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'node';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  $handler->display->display_options['fields']['type']['exclude'] = TRUE;
  $handler->display->display_options['fields']['type']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['type']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['type']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['type']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['type']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['type']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['type']['alter']['html'] = 0;
  $handler->display->display_options['fields']['type']['hide_empty'] = 0;
  $handler->display->display_options['fields']['type']['empty_zero'] = 0;
  $handler->display->display_options['fields']['type']['link_to_node'] = 0;
  $handler->display->display_options['fields']['type']['machine_name'] = 1;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Item';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['name']['alter']['external'] = 0;
  $handler->display->display_options['fields']['name']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['name']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['name']['alter']['html'] = 0;
  $handler->display->display_options['fields']['name']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['name']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['name']['hide_empty'] = 0;
  $handler->display->display_options['fields']['name']['empty_zero'] = 0;
  $handler->display->display_options['fields']['name']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['name']['link_to_user'] = 1;
  $handler->display->display_options['fields']['name']['overwrite_anonymous'] = 0;
  $handler->display->display_options['fields']['name']['format_username'] = 1;
  /* Field: Content: Reservation */
  $handler->display->display_options['fields']['field_merci_date']['id'] = 'field_merci_date';
  $handler->display->display_options['fields']['field_merci_date']['table'] = 'field_data_field_merci_date';
  $handler->display->display_options['fields']['field_merci_date']['field'] = 'field_merci_date';
  $handler->display->display_options['fields']['field_merci_date']['relationship'] = 'vid';
  $handler->display->display_options['fields']['field_merci_date']['label'] = 'Time';
  $handler->display->display_options['fields']['field_merci_date']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_merci_date']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_merci_date']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_merci_date']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_merci_date']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_merci_date']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_merci_date']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_merci_date']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_merci_date']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_merci_date']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_merci_date']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_merci_date']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_merci_date']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_merci_date']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_merci_date']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_merci_date']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_merci_date']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_merci_date']['settings'] = array(
    'format_type' => 'medium',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_repeat_rule' => 'show',
  );
  $handler->display->display_options['fields']['field_merci_date']['field_api_classes'] = 0;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'node';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['relationship'] = 'vid';
  $handler->display->display_options['fields']['title_1']['label'] = 'Reservation title';
  $handler->display->display_options['fields']['title_1']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title_1']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title_1']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title_1']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title_1']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['title_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['title_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title_1']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['title_1']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title_1']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['title_1']['link_to_node'] = 1;
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['relationship'] = 'vid';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Edit reservation';
  $handler->display->display_options['fields']['edit_node']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['edit_node']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['edit_node']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['edit_node']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['edit_node']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['edit_node']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['edit_node']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['edit_node']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['edit_node']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['edit_node']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['edit_node']['alter']['html'] = 0;
  $handler->display->display_options['fields']['edit_node']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['edit_node']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['edit_node']['hide_empty'] = 0;
  $handler->display->display_options['fields']['edit_node']['empty_zero'] = 0;
  $handler->display->display_options['fields']['edit_node']['hide_alter_empty'] = 1;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: MERCI: MERCI type */
  $handler->display->display_options['filters']['type_setting']['id'] = 'type_setting';
  $handler->display->display_options['filters']['type_setting']['table'] = 'merci_node_type';
  $handler->display->display_options['filters']['type_setting']['field'] = 'type_setting';
  $handler->display->display_options['filters']['type_setting']['value'] = array(
    'bucket' => 'bucket',
    'resource' => 'resource',
  );
  $handler->display->display_options['filters']['type_setting']['group'] = 0;
  $handler->display->display_options['filters']['type_setting']['expose']['operator'] = FALSE;
  /* Filter criterion: MERCI: Reservation status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'merci_reservation';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['relationship'] = 'vid';
  $handler->display->display_options['filters']['status']['value'] = array(
    3 => '3',
  );
  $handler->display->display_options['filters']['status']['group'] = 0;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: MERCI: Sub type -- resource/bucket */
  $handler->display->display_options['filters']['sub_type']['id'] = 'sub_type';
  $handler->display->display_options['filters']['sub_type']['table'] = 'merci_reservation_item_node';
  $handler->display->display_options['filters']['sub_type']['field'] = 'sub_type';
  $handler->display->display_options['filters']['sub_type']['value'] = array(
    1 => '1',
  );
  $handler->display->display_options['path'] = 'admin/merci/manage/current_inventory/%/checked-out';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Checked Out';
  $handler->display->display_options['menu']['weight'] = '2';

  /* Display: Unavailable items */
  $handler = $view->new_display('page', 'Unavailable items', 'page_3');
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['nid']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['nid']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['html'] = 0;
  $handler->display->display_options['fields']['nid']['hide_empty'] = 0;
  $handler->display->display_options['fields']['nid']['empty_zero'] = 0;
  $handler->display->display_options['fields']['nid']['link_to_node'] = 0;
  /* Field: Content: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'node';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  $handler->display->display_options['fields']['type']['exclude'] = TRUE;
  $handler->display->display_options['fields']['type']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['type']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['type']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['type']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['type']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['type']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['type']['alter']['html'] = 0;
  $handler->display->display_options['fields']['type']['hide_empty'] = 0;
  $handler->display->display_options['fields']['type']['empty_zero'] = 0;
  $handler->display->display_options['fields']['type']['link_to_node'] = 0;
  $handler->display->display_options['fields']['type']['machine_name'] = 1;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 1;
  $handler->display->display_options['fields']['title']['alter']['path'] = 'node/[nid]/edit?destination=admin/merci/manage/current_inventory/[type]/Unavailable';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['link_to_node'] = 0;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: MERCI: MERCI type */
  $handler->display->display_options['filters']['type_setting']['id'] = 'type_setting';
  $handler->display->display_options['filters']['type_setting']['table'] = 'merci_node_type';
  $handler->display->display_options['filters']['type_setting']['field'] = 'type_setting';
  $handler->display->display_options['filters']['type_setting']['value'] = array(
    'bucket' => 'bucket',
    'resource' => 'resource',
  );
  $handler->display->display_options['filters']['type_setting']['expose']['operator'] = FALSE;
  /* Filter criterion: MERCI: Sub type -- resource/bucket */
  $handler->display->display_options['filters']['sub_type']['id'] = 'sub_type';
  $handler->display->display_options['filters']['sub_type']['table'] = 'merci_reservation_item_node';
  $handler->display->display_options['filters']['sub_type']['field'] = 'sub_type';
  $handler->display->display_options['filters']['sub_type']['value'] = array(
    1 => '1',
  );
  $handler->display->display_options['filters']['sub_type']['expose']['operator'] = FALSE;
  /* Filter criterion: MERCI: Default booking availability -- resource/bucket */
  $handler->display->display_options['filters']['default_availability']['id'] = 'default_availability';
  $handler->display->display_options['filters']['default_availability']['table'] = 'merci_reservation_item_node';
  $handler->display->display_options['filters']['default_availability']['field'] = 'default_availability';
  $handler->display->display_options['filters']['default_availability']['value'] = array(
    2 => '2',
  );
  $handler->display->display_options['filters']['default_availability']['expose']['operator'] = FALSE;
  $handler->display->display_options['path'] = 'admin/merci/manage/current_inventory/%/Unavailable';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Unavailable';
  $handler->display->display_options['menu']['weight'] = '1';

  $views[$view->name] = $view;
  return $views;

}
