<?php

/**
 * @file
 * merci ui default views
 */


/**
 * Implements hook_views_default_views().
 */
function merci_ui_views_default_views() {

  $view = new view;
  $view->name = 'merci_ui_reservations';
  $view->description = '';
  $view->tag = '';
  $view->base_table = 'node';
  $view->human_name = 'merci_ui_reservations';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['title'] = 'Upcoming';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer MERCI';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = 1;
  $handler->display->display_options['exposed_form']['options']['autosubmit_hide'] = 1;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = 0;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'name' => 'name',
    'item_nid2' => 'item_nid2',
    'edit_node' => 'edit_node',
    'field_merci_date' => 'field_merci_date',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'item_nid2' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_merci_date' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 0;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['empty'] = FALSE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['text']['id'] = 'text';
  $handler->display->display_options['empty']['text']['table'] = 'views';
  $handler->display->display_options['empty']['text']['field'] = 'area';
  $handler->display->display_options['empty']['text']['empty'] = FALSE;
  $handler->display->display_options['empty']['text']['content'] = '<div class="messages status">There are no Reservations matching your criteria.</div>';
  $handler->display->display_options['empty']['text']['tokenize'] = 0;
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Relationship: MERCI: Reserved item nid */
  $handler->display->display_options['relationships']['item_nid']['id'] = 'item_nid';
  $handler->display->display_options['relationships']['item_nid']['table'] = 'merci_reservation_detail';
  $handler->display->display_options['relationships']['item_nid']['field'] = 'item_nid';
  $handler->display->display_options['relationships']['item_nid']['required'] = 0;
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
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_repeat_rule' => 'show',
  );
  $handler->display->display_options['fields']['field_merci_date']['field_api_classes'] = 0;
  /* Field: MERCI: Reserved items */
  $handler->display->display_options['fields']['item_nid2']['id'] = 'item_nid2';
  $handler->display->display_options['fields']['item_nid2']['table'] = 'merci_reservation_detail';
  $handler->display->display_options['fields']['item_nid2']['field'] = 'item_nid2';
  $handler->display->display_options['fields']['item_nid2']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['item_nid2']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['item_nid2']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['item_nid2']['alter']['external'] = 0;
  $handler->display->display_options['fields']['item_nid2']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['item_nid2']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['item_nid2']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['item_nid2']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['item_nid2']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['item_nid2']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['item_nid2']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['item_nid2']['alter']['html'] = 0;
  $handler->display->display_options['fields']['item_nid2']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['item_nid2']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['item_nid2']['hide_empty'] = 0;
  $handler->display->display_options['fields']['item_nid2']['empty_zero'] = 0;
  $handler->display->display_options['fields']['item_nid2']['hide_alter_empty'] = 1;
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = '';
  $handler->display->display_options['fields']['edit_node']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['edit_node']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['edit_node']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['edit_node']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['edit_node']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['edit_node']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['edit_node']['alter']['html'] = 0;
  $handler->display->display_options['fields']['edit_node']['hide_empty'] = 0;
  $handler->display->display_options['fields']['edit_node']['empty_zero'] = 0;
  /* Sort criterion: Content: Reservation -  start date (field_merci_date) */
  $handler->display->display_options['sorts']['field_merci_date_value']['id'] = 'field_merci_date_value';
  $handler->display->display_options['sorts']['field_merci_date_value']['table'] = 'field_data_field_merci_date';
  $handler->display->display_options['sorts']['field_merci_date_value']['field'] = 'field_merci_date_value';
  /* Sort criterion: Content: Reservation - end date (field_merci_date:value2) */
  $handler->display->display_options['sorts']['field_merci_date_value2']['id'] = 'field_merci_date_value2';
  $handler->display->display_options['sorts']['field_merci_date_value2']['table'] = 'field_data_field_merci_date';
  $handler->display->display_options['sorts']['field_merci_date_value2']['field'] = 'field_merci_date_value2';
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'merci_reservation' => 'merci_reservation',
  );
  $handler->display->display_options['filters']['type']['group'] = 0;
  $handler->display->display_options['filters']['type']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Reservation -  start date (field_merci_date) */
  $handler->display->display_options['filters']['field_merci_date_value']['id'] = 'field_merci_date_value';
  $handler->display->display_options['filters']['field_merci_date_value']['table'] = 'field_data_field_merci_date';
  $handler->display->display_options['filters']['field_merci_date_value']['field'] = 'field_merci_date_value';
  $handler->display->display_options['filters']['field_merci_date_value']['operator'] = '>=';
  $handler->display->display_options['filters']['field_merci_date_value']['group'] = 0;
  $handler->display->display_options['filters']['field_merci_date_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_merci_date_value']['expose']['operator_id'] = 'field_merci_date_value_op';
  $handler->display->display_options['filters']['field_merci_date_value']['expose']['label'] = 'Reservations from:';
  $handler->display->display_options['filters']['field_merci_date_value']['expose']['operator'] = 'field_merci_date_value_op';
  $handler->display->display_options['filters']['field_merci_date_value']['expose']['identifier'] = 'field_merci_date_value';
  $handler->display->display_options['filters']['field_merci_date_value']['expose']['multiple'] = FALSE;
  $handler->display->display_options['filters']['field_merci_date_value']['form_type'] = 'date_popup';
  $handler->display->display_options['filters']['field_merci_date_value']['default_date'] = '-1 day';

  /* Display: Upcoming */
  $handler = $view->new_display('page', 'Upcoming', 'page_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Upcoming reservations';
  $handler->display->display_options['defaults']['use_ajax'] = FALSE;
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['empty'] = TRUE;
  $handler->display->display_options['header']['area']['content'] = 'Upcoming confirmed reservations.';
  $handler->display->display_options['header']['area']['tokenize'] = 0;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'merci_reservation' => 'merci_reservation',
  );
  $handler->display->display_options['filters']['type']['group'] = 0;
  $handler->display->display_options['filters']['type']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Reservation -  start date (field_merci_date) */
  $handler->display->display_options['filters']['field_merci_date_value']['id'] = 'field_merci_date_value';
  $handler->display->display_options['filters']['field_merci_date_value']['table'] = 'field_data_field_merci_date';
  $handler->display->display_options['filters']['field_merci_date_value']['field'] = 'field_merci_date_value';
  $handler->display->display_options['filters']['field_merci_date_value']['operator'] = '>=';
  $handler->display->display_options['filters']['field_merci_date_value']['group'] = 0;
  $handler->display->display_options['filters']['field_merci_date_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_merci_date_value']['expose']['operator_id'] = 'field_merci_date_value_op';
  $handler->display->display_options['filters']['field_merci_date_value']['expose']['label'] = 'Reservations from:';
  $handler->display->display_options['filters']['field_merci_date_value']['expose']['operator'] = 'field_merci_date_value_op';
  $handler->display->display_options['filters']['field_merci_date_value']['expose']['identifier'] = 'field_merci_date_value';
  $handler->display->display_options['filters']['field_merci_date_value']['expose']['multiple'] = FALSE;
  $handler->display->display_options['filters']['field_merci_date_value']['form_type'] = 'date_popup';
  $handler->display->display_options['filters']['field_merci_date_value']['default_date'] = '-1 day';
  /* Filter criterion: MERCI: Reservation status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'merci_reservation';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = array(
    2 => '2',
  );
  $handler->display->display_options['path'] = 'admin/merci/manage/reservations/upcoming';
  $handler->display->display_options['menu']['type'] = 'default tab';
  $handler->display->display_options['menu']['title'] = 'Upcoming';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Reservations';
  $handler->display->display_options['tab_options']['weight'] = '0';

  /* Display: Incoming */
  $handler = $view->new_display('page', 'Incoming', 'page_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Incoming reservations';
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['empty'] = TRUE;
  $handler->display->display_options['header']['area']['content'] = 'Incoming reservations currently checked out.';
  $handler->display->display_options['header']['area']['tokenize'] = 0;
  $handler->display->display_options['defaults']['empty'] = FALSE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['text']['id'] = 'text';
  $handler->display->display_options['empty']['text']['table'] = 'views';
  $handler->display->display_options['empty']['text']['field'] = 'area';
  $handler->display->display_options['empty']['text']['empty'] = FALSE;
  $handler->display->display_options['empty']['text']['content'] = '<div class="messages status">Anticipating no returns.</div>';
  $handler->display->display_options['empty']['text']['tokenize'] = 0;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'merci_reservation' => 'merci_reservation',
  );
  $handler->display->display_options['filters']['type']['group'] = 0;
  $handler->display->display_options['filters']['type']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Reservation - end date (field_merci_date:value2) */
  $handler->display->display_options['filters']['field_merci_date_value2']['id'] = 'field_merci_date_value2';
  $handler->display->display_options['filters']['field_merci_date_value2']['table'] = 'field_data_field_merci_date';
  $handler->display->display_options['filters']['field_merci_date_value2']['field'] = 'field_merci_date_value2';
  $handler->display->display_options['filters']['field_merci_date_value2']['group'] = 0;
  $handler->display->display_options['filters']['field_merci_date_value2']['default_date'] = 'now';
  /* Filter criterion: MERCI: Reservation status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'merci_reservation';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = array(
    3 => '3',
  );
  $handler->display->display_options['filters']['status']['group'] = 0;
  $handler->display->display_options['path'] = 'admin/merci/manage/reservations/incoming';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Incoming';
  $handler->display->display_options['menu']['weight'] = '1';

  /* Display: Unconfirmed */
  $handler = $view->new_display('page', 'Unconfirmed', 'page_3');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Unconfirmed reservations';
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['empty'] = TRUE;
  $handler->display->display_options['header']['area']['content'] = 'Reservatations currently pending.';
  $handler->display->display_options['header']['area']['tokenize'] = 0;
  $handler->display->display_options['defaults']['empty'] = FALSE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['text']['id'] = 'text';
  $handler->display->display_options['empty']['text']['table'] = 'views';
  $handler->display->display_options['empty']['text']['field'] = 'area';
  $handler->display->display_options['empty']['text']['empty'] = FALSE;
  $handler->display->display_options['empty']['text']['content'] = '<div class="messages status">There are currently no unconfirmed reservations.</div>';
  $handler->display->display_options['empty']['text']['tokenize'] = 0;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'merci_reservation' => 'merci_reservation',
  );
  $handler->display->display_options['filters']['type']['group'] = 0;
  $handler->display->display_options['filters']['type']['expose']['operator'] = FALSE;
  /* Filter criterion: MERCI: Reservation status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'merci_reservation';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = array(
    1 => '1',
  );
  $handler->display->display_options['filters']['status']['group'] = 0;
  $handler->display->display_options['path'] = 'admin/merci/manage/reservations/unconfirmed';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Unconfirmed';
  $handler->display->display_options['menu']['weight'] = '2';

  /* Display: Overdue */
  $handler = $view->new_display('page', 'Overdue', 'page_4');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Overdue reservations';
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['empty'] = TRUE;
  $handler->display->display_options['header']['area']['content'] = 'Reservations in the checked out state which are past due.';
  $handler->display->display_options['header']['area']['tokenize'] = 0;
  $handler->display->display_options['defaults']['empty'] = FALSE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['text']['id'] = 'text';
  $handler->display->display_options['empty']['text']['table'] = 'views';
  $handler->display->display_options['empty']['text']['field'] = 'area';
  $handler->display->display_options['empty']['text']['empty'] = FALSE;
  $handler->display->display_options['empty']['text']['content'] = '<div class="messages status">There are currently no overdue reservations.</div>';
  $handler->display->display_options['empty']['text']['tokenize'] = 0;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Reservation - end date (field_merci_date:value2) */
  $handler->display->display_options['sorts']['field_merci_date_value2']['id'] = 'field_merci_date_value2';
  $handler->display->display_options['sorts']['field_merci_date_value2']['table'] = 'field_data_field_merci_date';
  $handler->display->display_options['sorts']['field_merci_date_value2']['field'] = 'field_merci_date_value2';
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'merci_reservation' => 'merci_reservation',
  );
  $handler->display->display_options['filters']['type']['group'] = 0;
  $handler->display->display_options['filters']['type']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Reservation - end date (field_merci_date:value2) */
  $handler->display->display_options['filters']['field_merci_date_value2']['id'] = 'field_merci_date_value2';
  $handler->display->display_options['filters']['field_merci_date_value2']['table'] = 'field_data_field_merci_date';
  $handler->display->display_options['filters']['field_merci_date_value2']['field'] = 'field_merci_date_value2';
  $handler->display->display_options['filters']['field_merci_date_value2']['operator'] = '<=';
  $handler->display->display_options['filters']['field_merci_date_value2']['group'] = 0;
  $handler->display->display_options['filters']['field_merci_date_value2']['granularity'] = 'minute';
  $handler->display->display_options['filters']['field_merci_date_value2']['default_date'] = 'now';
  /* Filter criterion: MERCI: Reservation status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'merci_reservation';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = array(
    3 => '3',
  );
  $handler->display->display_options['path'] = 'admin/merci/manage/reservations/overdue';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Overdue';
  $handler->display->display_options['menu']['weight'] = '3';

  /* Display: Browse */
  $handler = $view->new_display('page', 'Browse', 'page_5');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Browse reservations';
  $handler->display->display_options['defaults']['fields'] = FALSE;
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
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_repeat_rule' => 'show',
  );
  $handler->display->display_options['fields']['field_merci_date']['field_api_classes'] = 0;
  /* Field: MERCI: Reserved items */
  $handler->display->display_options['fields']['item_nid2']['id'] = 'item_nid2';
  $handler->display->display_options['fields']['item_nid2']['table'] = 'merci_reservation_detail';
  $handler->display->display_options['fields']['item_nid2']['field'] = 'item_nid2';
  $handler->display->display_options['fields']['item_nid2']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['item_nid2']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['item_nid2']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['item_nid2']['alter']['external'] = 0;
  $handler->display->display_options['fields']['item_nid2']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['item_nid2']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['item_nid2']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['item_nid2']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['item_nid2']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['item_nid2']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['item_nid2']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['item_nid2']['alter']['html'] = 0;
  $handler->display->display_options['fields']['item_nid2']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['item_nid2']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['item_nid2']['hide_empty'] = 0;
  $handler->display->display_options['fields']['item_nid2']['empty_zero'] = 0;
  $handler->display->display_options['fields']['item_nid2']['hide_alter_empty'] = 1;
  /* Field: MERCI: Reservation status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'merci_reservation';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'Status';
  $handler->display->display_options['fields']['status']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['status']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['status']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['status']['alter']['external'] = 0;
  $handler->display->display_options['fields']['status']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['status']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['status']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['status']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['status']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['status']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['status']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['status']['alter']['html'] = 0;
  $handler->display->display_options['fields']['status']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['status']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['status']['hide_empty'] = 0;
  $handler->display->display_options['fields']['status']['empty_zero'] = 0;
  $handler->display->display_options['fields']['status']['hide_alter_empty'] = 1;
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = '';
  $handler->display->display_options['fields']['edit_node']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['edit_node']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['edit_node']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['edit_node']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['edit_node']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['edit_node']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['edit_node']['alter']['html'] = 0;
  $handler->display->display_options['fields']['edit_node']['hide_empty'] = 0;
  $handler->display->display_options['fields']['edit_node']['empty_zero'] = 0;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'merci_reservation' => 'merci_reservation',
  );
  $handler->display->display_options['filters']['type']['group'] = 0;
  $handler->display->display_options['filters']['type']['expose']['operator'] = FALSE;
  /* Filter criterion: User: Name */
  $handler->display->display_options['filters']['uid']['id'] = 'uid';
  $handler->display->display_options['filters']['uid']['table'] = 'users';
  $handler->display->display_options['filters']['uid']['field'] = 'uid';
  $handler->display->display_options['filters']['uid']['relationship'] = 'uid';
  $handler->display->display_options['filters']['uid']['value'] = '';
  $handler->display->display_options['filters']['uid']['group'] = 0;
  $handler->display->display_options['filters']['uid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['uid']['expose']['operator_id'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['label'] = 'Name:';
  $handler->display->display_options['filters']['uid']['expose']['operator'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['identifier'] = 'uid';
  $handler->display->display_options['filters']['uid']['expose']['multiple'] = FALSE;
  $handler->display->display_options['filters']['uid']['expose']['reduce'] = 0;
  /* Filter criterion: Content: Reservation -  start date (field_merci_date) */
  $handler->display->display_options['filters']['field_merci_date_value']['id'] = 'field_merci_date_value';
  $handler->display->display_options['filters']['field_merci_date_value']['table'] = 'field_data_field_merci_date';
  $handler->display->display_options['filters']['field_merci_date_value']['field'] = 'field_merci_date_value';
  $handler->display->display_options['filters']['field_merci_date_value']['operator'] = '>=';
  $handler->display->display_options['filters']['field_merci_date_value']['group'] = 0;
  $handler->display->display_options['filters']['field_merci_date_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_merci_date_value']['expose']['operator_id'] = 'field_merci_date_value_op';
  $handler->display->display_options['filters']['field_merci_date_value']['expose']['label'] = 'Reservations from:';
  $handler->display->display_options['filters']['field_merci_date_value']['expose']['operator'] = 'field_merci_date_value_op';
  $handler->display->display_options['filters']['field_merci_date_value']['expose']['identifier'] = 'field_merci_date_value';
  $handler->display->display_options['filters']['field_merci_date_value']['expose']['multiple'] = FALSE;
  $handler->display->display_options['filters']['field_merci_date_value']['form_type'] = 'date_popup';
  $handler->display->display_options['filters']['field_merci_date_value']['default_date'] = '-1 day';
  /* Filter criterion: Content: Reservation -  start date (field_merci_date) */
  $handler->display->display_options['filters']['field_merci_date_value_1']['id'] = 'field_merci_date_value_1';
  $handler->display->display_options['filters']['field_merci_date_value_1']['table'] = 'field_data_field_merci_date';
  $handler->display->display_options['filters']['field_merci_date_value_1']['field'] = 'field_merci_date_value';
  $handler->display->display_options['filters']['field_merci_date_value_1']['operator'] = '<=';
  $handler->display->display_options['filters']['field_merci_date_value_1']['group'] = 0;
  $handler->display->display_options['filters']['field_merci_date_value_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_merci_date_value_1']['expose']['operator_id'] = 'field_merci_date_value_1_op';
  $handler->display->display_options['filters']['field_merci_date_value_1']['expose']['label'] = 'Reservations to:';
  $handler->display->display_options['filters']['field_merci_date_value_1']['expose']['operator'] = 'field_merci_date_value_1_op';
  $handler->display->display_options['filters']['field_merci_date_value_1']['expose']['identifier'] = 'field_merci_date_value_1';
  $handler->display->display_options['filters']['field_merci_date_value_1']['expose']['multiple'] = FALSE;
  $handler->display->display_options['filters']['field_merci_date_value_1']['form_type'] = 'date_popup';
  /* Filter criterion: MERCI: Reservable content types */
  $handler->display->display_options['filters']['merci_content_type']['id'] = 'merci_content_type';
  $handler->display->display_options['filters']['merci_content_type']['table'] = 'node';
  $handler->display->display_options['filters']['merci_content_type']['field'] = 'merci_content_type';
  $handler->display->display_options['filters']['merci_content_type']['relationship'] = 'item_nid';
  $handler->display->display_options['filters']['merci_content_type']['group'] = 0;
  $handler->display->display_options['filters']['merci_content_type']['exposed'] = TRUE;
  $handler->display->display_options['filters']['merci_content_type']['expose']['operator_id'] = 'merci_content_type_op';
  $handler->display->display_options['filters']['merci_content_type']['expose']['label'] = 'Reserved item:';
  $handler->display->display_options['filters']['merci_content_type']['expose']['operator'] = 'merci_content_type_op';
  $handler->display->display_options['filters']['merci_content_type']['expose']['identifier'] = 'merci_content_type';
  $handler->display->display_options['filters']['merci_content_type']['expose']['reduce'] = 0;
  /* Filter criterion: MERCI: Reservation status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'merci_reservation';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['group'] = 0;
  $handler->display->display_options['filters']['status']['exposed'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['operator_id'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['label'] = 'Status:';
  $handler->display->display_options['filters']['status']['expose']['operator'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['identifier'] = 'status';
  $handler->display->display_options['filters']['status']['expose']['reduce'] = 0;
  $handler->display->display_options['path'] = 'admin/merci/manage/reservations/by-type';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Browse';
  $handler->display->display_options['menu']['weight'] = '5';

  $views[$view->name] = $view;
  $view = new view;
  $view->name = 'merci_ui_user_reservations';
  $view->description = 'View is called by the merci_ui module in user/%/reservations';
  $view->tag = '';
  $view->base_table = 'node';
  $view->human_name = '';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'create reservations';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = 1;
  $handler->display->display_options['exposed_form']['options']['autosubmit_hide'] = 1;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 1,
      'separator' => '',
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['text']['id'] = 'area';
  $handler->display->display_options['empty']['text']['table'] = 'views';
  $handler->display->display_options['empty']['text']['field'] = 'area';
  $handler->display->display_options['empty']['text']['empty'] = FALSE;
  $handler->display->display_options['empty']['text']['content'] = 'You have no upcoming reservations.';
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Field: Content: Reservation */
  $handler->display->display_options['fields']['field_merci_date']['id'] = 'field_merci_date';
  $handler->display->display_options['fields']['field_merci_date']['table'] = 'field_data_field_merci_date';
  $handler->display->display_options['fields']['field_merci_date']['field'] = 'field_merci_date';
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
  /* Field: MERCI: Reserved items */
  $handler->display->display_options['fields']['item_nid2']['id'] = 'item_nid2';
  $handler->display->display_options['fields']['item_nid2']['table'] = 'merci_reservation_detail';
  $handler->display->display_options['fields']['item_nid2']['field'] = 'item_nid2';
  $handler->display->display_options['fields']['item_nid2']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['item_nid2']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['item_nid2']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['item_nid2']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['item_nid2']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['item_nid2']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['item_nid2']['alter']['html'] = 0;
  $handler->display->display_options['fields']['item_nid2']['hide_empty'] = 0;
  $handler->display->display_options['fields']['item_nid2']['empty_zero'] = 0;
  /* Field: MERCI: Reservation status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'merci_reservation';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'Status';
  $handler->display->display_options['fields']['status']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['status']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['status']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['status']['alter']['external'] = 0;
  $handler->display->display_options['fields']['status']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['status']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['status']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['status']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['status']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['status']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['status']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['status']['alter']['html'] = 0;
  $handler->display->display_options['fields']['status']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['status']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['status']['hide_empty'] = 0;
  $handler->display->display_options['fields']['status']['empty_zero'] = 0;
  $handler->display->display_options['fields']['status']['hide_alter_empty'] = 1;
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = '';
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
  $handler->display->display_options['fields']['edit_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['edit_node']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['edit_node']['hide_empty'] = 0;
  $handler->display->display_options['fields']['edit_node']['empty_zero'] = 0;
  $handler->display->display_options['fields']['edit_node']['hide_alter_empty'] = 1;
  /* Sort criterion: Content: Reservation -  start date (field_merci_date) */
  $handler->display->display_options['sorts']['field_merci_date_value']['id'] = 'field_merci_date_value';
  $handler->display->display_options['sorts']['field_merci_date_value']['table'] = 'field_data_field_merci_date';
  $handler->display->display_options['sorts']['field_merci_date_value']['field'] = 'field_merci_date_value';
  /* Contextual filter: User: Uid */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'users';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['relationship'] = 'uid';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['uid']['exception']['title_enable'] = 1;
  $handler->display->display_options['arguments']['uid']['title_enable'] = 1;
  $handler->display->display_options['arguments']['uid']['title'] = '%1 Reservations';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'user';
  $handler->display->display_options['arguments']['uid']['default_argument_options']['user'] = FALSE;
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['specify_validation'] = 1;
  $handler->display->display_options['arguments']['uid']['validate']['type'] = 'php';
  $handler->display->display_options['arguments']['uid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['uid']['not'] = 0;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'merci_reservation' => 'merci_reservation',
  );
  $handler->display->display_options['filters']['type']['expose']['operator'] = FALSE;
  /* Filter criterion: Date: Date (node) */
  $handler->display->display_options['filters']['date_filter']['id'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['table'] = 'node';
  $handler->display->display_options['filters']['date_filter']['field'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['operator'] = '>=';
  $handler->display->display_options['filters']['date_filter']['exposed'] = TRUE;
  $handler->display->display_options['filters']['date_filter']['expose']['operator_id'] = 'date_filter_op';
  $handler->display->display_options['filters']['date_filter']['expose']['label'] = 'Show Reservations Due After';
  $handler->display->display_options['filters']['date_filter']['expose']['operator'] = 'date_filter_op';
  $handler->display->display_options['filters']['date_filter']['expose']['identifier'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['form_type'] = 'date_popup';
  $handler->display->display_options['filters']['date_filter']['default_date'] = 'now -1 day';
  $handler->display->display_options['filters']['date_filter']['date_fields'] = array(
    'field_data_field_merci_date.field_merci_date_value2' => 'field_data_field_merci_date.field_merci_date_value2',
  );

  /* Display: My Reservations */
  $handler = $view->new_display('page', 'My Reservations', 'page_1');
  $handler->display->display_options['path'] = 'user/%/my-reservations';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'My Reservations';
  $handler->display->display_options['menu']['description'] = 'Takes user object and returns Reservations';
  $handler->display->display_options['menu']['weight'] = '0';

  $views[$view->name] = $view;
  $view = new view;
  $view->name = 'merci_ui_node_reservations';
  $view->description = 'View is called by the merci_ui module in node/%/reservations';
  $view->tag = '';
  $view->base_table = 'node';
  $view->human_name = '';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['title'] = 'Item Reservations';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'manage reservations';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = 1;
  $handler->display->display_options['exposed_form']['options']['autosubmit_hide'] = 1;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = 0;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 1,
      'separator' => '',
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['text']['id'] = 'area';
  $handler->display->display_options['empty']['text']['table'] = 'views';
  $handler->display->display_options['empty']['text']['field'] = 'area';
  $handler->display->display_options['empty']['text']['empty'] = FALSE;
  $handler->display->display_options['empty']['text']['content'] = 'There are no reservations for this item.';
  /* Relationship: MERCI: Reserved item nid */
  $handler->display->display_options['relationships']['item_nid']['id'] = 'item_nid';
  $handler->display->display_options['relationships']['item_nid']['table'] = 'merci_reservation_detail';
  $handler->display->display_options['relationships']['item_nid']['field'] = 'item_nid';
  $handler->display->display_options['relationships']['item_nid']['required'] = 0;
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['name']['alter']['html'] = 0;
  $handler->display->display_options['fields']['name']['hide_empty'] = 0;
  $handler->display->display_options['fields']['name']['empty_zero'] = 0;
  $handler->display->display_options['fields']['name']['link_to_user'] = 1;
  $handler->display->display_options['fields']['name']['overwrite_anonymous'] = 0;
  /* Field: Content: Reservation */
  $handler->display->display_options['fields']['field_merci_date']['id'] = 'field_merci_date';
  $handler->display->display_options['fields']['field_merci_date']['table'] = 'field_data_field_merci_date';
  $handler->display->display_options['fields']['field_merci_date']['field'] = 'field_merci_date';
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
  /* Field: MERCI: Reserved items */
  $handler->display->display_options['fields']['item_nid2']['id'] = 'item_nid2';
  $handler->display->display_options['fields']['item_nid2']['table'] = 'merci_reservation_detail';
  $handler->display->display_options['fields']['item_nid2']['field'] = 'item_nid2';
  $handler->display->display_options['fields']['item_nid2']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['item_nid2']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['item_nid2']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['item_nid2']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['item_nid2']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['item_nid2']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['item_nid2']['alter']['html'] = 0;
  $handler->display->display_options['fields']['item_nid2']['hide_empty'] = 0;
  $handler->display->display_options['fields']['item_nid2']['empty_zero'] = 0;
  /* Field: MERCI: Reservation status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'merci_reservation';
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
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'item_nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['nid']['exception']['title_enable'] = 1;
  $handler->display->display_options['arguments']['nid']['title_enable'] = 1;
  $handler->display->display_options['arguments']['nid']['title'] = 'Reservations for %1';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['specify_validation'] = 1;
  $handler->display->display_options['arguments']['nid']['validate']['type'] = 'php';
  $handler->display->display_options['arguments']['nid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['nid']['not'] = 0;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'merci_reservation' => 'merci_reservation',
  );
  $handler->display->display_options['filters']['type']['expose']['operator'] = FALSE;
  /* Filter criterion: Date: Date (node) */
  $handler->display->display_options['filters']['date_filter']['id'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['table'] = 'node';
  $handler->display->display_options['filters']['date_filter']['field'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['operator'] = '>';
  $handler->display->display_options['filters']['date_filter']['exposed'] = TRUE;
  $handler->display->display_options['filters']['date_filter']['expose']['operator_id'] = 'date_filter_op';
  $handler->display->display_options['filters']['date_filter']['expose']['label'] = 'Show Reservations Starting After';
  $handler->display->display_options['filters']['date_filter']['expose']['operator'] = 'date_filter_op';
  $handler->display->display_options['filters']['date_filter']['expose']['identifier'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['expose']['required'] = FALSE;
  $handler->display->display_options['filters']['date_filter']['form_type'] = 'date_popup';
  $handler->display->display_options['filters']['date_filter']['default_date'] = 'now -1 day';
  $handler->display->display_options['filters']['date_filter']['date_fields'] = array(
    'field_data_field_merci_date.field_merci_date_value' => 'field_data_field_merci_date.field_merci_date_value',
  );
  /* Filter criterion: MERCI: Reservation status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'merci_reservation';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['exposed'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['operator_id'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['label'] = 'Status:';
  $handler->display->display_options['filters']['status']['expose']['operator'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['identifier'] = 'status';
  $handler->display->display_options['filters']['status']['expose']['reduce'] = 0;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['path'] = 'node/%/reservations';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Reservations';
  $handler->display->display_options['menu']['description'] = 'Takes node and returns list of upcoming and/or past Reservations';
  $handler->display->display_options['menu']['weight'] = '0';

  $views[$view->name] = $view;

  return $views;
}

