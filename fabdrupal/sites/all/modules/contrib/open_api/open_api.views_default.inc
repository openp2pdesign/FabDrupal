<?php
/**
 * @file
 * open_api.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function open_api_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'events_service';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Events: Service';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Events';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Date */
  $handler->display->display_options['fields']['field_event_date']['id'] = 'field_event_date';
  $handler->display->display_options['fields']['field_event_date']['table'] = 'field_data_field_event_date';
  $handler->display->display_options['fields']['field_event_date']['field'] = 'field_event_date';
  $handler->display->display_options['fields']['field_event_date']['label'] = 'date';
  $handler->display->display_options['fields']['field_event_date']['type'] = 'services';
  $handler->display->display_options['fields']['field_event_date']['settings'] = array(
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  /* Field: Content: Tags */
  $handler->display->display_options['fields']['field_event_tags']['id'] = 'field_event_tags';
  $handler->display->display_options['fields']['field_event_tags']['table'] = 'field_data_field_event_tags';
  $handler->display->display_options['fields']['field_event_tags']['field'] = 'field_event_tags';
  $handler->display->display_options['fields']['field_event_tags']['label'] = 'tags';
  $handler->display->display_options['fields']['field_event_tags']['type'] = 'services';
  $handler->display->display_options['fields']['field_event_tags']['settings'] = array(
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  $handler->display->display_options['fields']['field_event_tags']['delta_offset'] = '0';
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = 'body';
  $handler->display->display_options['fields']['body']['type'] = 'services';
  $handler->display->display_options['fields']['body']['settings'] = array(
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'event' => 'event',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'events-list';

  /* Display: Services */
  $handler = $view->new_display('services', 'Services', 'services_1');
  $handler->display->display_options['path'] = 'events-list';
  $translatables['events_service'] = array(
    t('Master'),
    t('Events'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('date'),
    t('tags'),
    t('body'),
    t('Page'),
    t('Services'),
  );
  $export['events_service'] = $view;

  $view = new view();
  $view->name = 'faq_service';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'FAQ: Service';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'FAQ: Service';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'question';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = 'answer';
  $handler->display->display_options['fields']['body']['type'] = 'services';
  $handler->display->display_options['fields']['body']['settings'] = array(
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'faq' => 'faq',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'faq-list';

  /* Display: Services */
  $handler = $view->new_display('services', 'Services', 'services_1');
  $handler->display->display_options['path'] = 'faq-list';
  $translatables['faq_service'] = array(
    t('Master'),
    t('FAQ: Service'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('question'),
    t('answer'),
    t('Page'),
    t('Services'),
  );
  $export['faq_service'] = $view;

  $view = new view();
  $view->name = 'machines_service';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Machines: Service';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Machines';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Manufacturer */
  $handler->display->display_options['fields']['field_manufacturer']['id'] = 'field_manufacturer';
  $handler->display->display_options['fields']['field_manufacturer']['table'] = 'field_data_field_manufacturer';
  $handler->display->display_options['fields']['field_manufacturer']['field'] = 'field_manufacturer';
  $handler->display->display_options['fields']['field_manufacturer']['label'] = 'manufacturer';
  $handler->display->display_options['fields']['field_manufacturer']['type'] = 'services';
  $handler->display->display_options['fields']['field_manufacturer']['settings'] = array(
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  /* Field: Content: Link */
  $handler->display->display_options['fields']['field_manufacturer_link']['id'] = 'field_manufacturer_link';
  $handler->display->display_options['fields']['field_manufacturer_link']['table'] = 'field_data_field_manufacturer_link';
  $handler->display->display_options['fields']['field_manufacturer_link']['field'] = 'field_manufacturer_link';
  $handler->display->display_options['fields']['field_manufacturer_link']['label'] = 'link';
  $handler->display->display_options['fields']['field_manufacturer_link']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_manufacturer_link']['type'] = 'services';
  $handler->display->display_options['fields']['field_manufacturer_link']['settings'] = array(
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  /* Field: Content: Power */
  $handler->display->display_options['fields']['field_machine_power']['id'] = 'field_machine_power';
  $handler->display->display_options['fields']['field_machine_power']['table'] = 'field_data_field_machine_power';
  $handler->display->display_options['fields']['field_machine_power']['field'] = 'field_machine_power';
  $handler->display->display_options['fields']['field_machine_power']['label'] = 'power';
  $handler->display->display_options['fields']['field_machine_power']['type'] = 'services';
  $handler->display->display_options['fields']['field_machine_power']['settings'] = array(
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  /* Field: Content: Work Area: X */
  $handler->display->display_options['fields']['field_work_area_x']['id'] = 'field_work_area_x';
  $handler->display->display_options['fields']['field_work_area_x']['table'] = 'field_data_field_work_area_x';
  $handler->display->display_options['fields']['field_work_area_x']['field'] = 'field_work_area_x';
  $handler->display->display_options['fields']['field_work_area_x']['label'] = 'work area x';
  $handler->display->display_options['fields']['field_work_area_x']['type'] = 'services';
  $handler->display->display_options['fields']['field_work_area_x']['settings'] = array(
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  /* Field: Content: Work Area: Y */
  $handler->display->display_options['fields']['field_work_area_y']['id'] = 'field_work_area_y';
  $handler->display->display_options['fields']['field_work_area_y']['table'] = 'field_data_field_work_area_y';
  $handler->display->display_options['fields']['field_work_area_y']['field'] = 'field_work_area_y';
  $handler->display->display_options['fields']['field_work_area_y']['label'] = 'work area y';
  $handler->display->display_options['fields']['field_work_area_y']['type'] = 'services';
  $handler->display->display_options['fields']['field_work_area_y']['settings'] = array(
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  /* Field: Content: Work Area: Z */
  $handler->display->display_options['fields']['field_work_area_z']['id'] = 'field_work_area_z';
  $handler->display->display_options['fields']['field_work_area_z']['table'] = 'field_data_field_work_area_z';
  $handler->display->display_options['fields']['field_work_area_z']['field'] = 'field_work_area_z';
  $handler->display->display_options['fields']['field_work_area_z']['label'] = 'work area y';
  $handler->display->display_options['fields']['field_work_area_z']['type'] = 'services';
  $handler->display->display_options['fields']['field_work_area_z']['settings'] = array(
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  /* Field: Content: File Types */
  $handler->display->display_options['fields']['field_file_type']['id'] = 'field_file_type';
  $handler->display->display_options['fields']['field_file_type']['table'] = 'field_data_field_file_type';
  $handler->display->display_options['fields']['field_file_type']['field'] = 'field_file_type';
  $handler->display->display_options['fields']['field_file_type']['label'] = 'file types';
  $handler->display->display_options['fields']['field_file_type']['type'] = 'services';
  $handler->display->display_options['fields']['field_file_type']['settings'] = array(
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  /* Field: Content: Materials */
  $handler->display->display_options['fields']['field_machine_materials']['id'] = 'field_machine_materials';
  $handler->display->display_options['fields']['field_machine_materials']['table'] = 'field_data_field_machine_materials';
  $handler->display->display_options['fields']['field_machine_materials']['field'] = 'field_machine_materials';
  $handler->display->display_options['fields']['field_machine_materials']['label'] = 'materials';
  $handler->display->display_options['fields']['field_machine_materials']['type'] = 'services';
  $handler->display->display_options['fields']['field_machine_materials']['settings'] = array(
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  $handler->display->display_options['fields']['field_machine_materials']['delta_offset'] = '0';
  /* Field: Content: Image */
  $handler->display->display_options['fields']['field_machine_image']['id'] = 'field_machine_image';
  $handler->display->display_options['fields']['field_machine_image']['table'] = 'field_data_field_machine_image';
  $handler->display->display_options['fields']['field_machine_image']['field'] = 'field_machine_image';
  $handler->display->display_options['fields']['field_machine_image']['label'] = 'image';
  $handler->display->display_options['fields']['field_machine_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_machine_image']['type'] = 'services';
  $handler->display->display_options['fields']['field_machine_image']['settings'] = array(
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'machine' => 'machine',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'machines-list';

  /* Display: Services */
  $handler = $view->new_display('services', 'Services', 'services_1');
  $handler->display->display_options['path'] = 'machines-list';
  $translatables['machines_service'] = array(
    t('Master'),
    t('Machines'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('title'),
    t('manufacturer'),
    t('link'),
    t('power'),
    t('work area x'),
    t('work area y'),
    t('file types'),
    t('materials'),
    t('image'),
    t('Page'),
    t('Services'),
  );
  $export['machines_service'] = $view;

  $view = new view();
  $view->name = 'materials_service';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Materials: Service';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Materials';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Image */
  $handler->display->display_options['fields']['field_material_image']['id'] = 'field_material_image';
  $handler->display->display_options['fields']['field_material_image']['table'] = 'field_data_field_material_image';
  $handler->display->display_options['fields']['field_material_image']['field'] = 'field_material_image';
  $handler->display->display_options['fields']['field_material_image']['label'] = 'image';
  $handler->display->display_options['fields']['field_material_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_material_image']['type'] = 'services';
  $handler->display->display_options['fields']['field_material_image']['settings'] = array(
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = 'body';
  $handler->display->display_options['fields']['body']['type'] = 'services';
  $handler->display->display_options['fields']['body']['settings'] = array(
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'material' => 'material',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'materials-list';

  /* Display: Services */
  $handler = $view->new_display('services', 'Services', 'services_1');
  $handler->display->display_options['path'] = 'materials-list';
  $translatables['materials_service'] = array(
    t('Master'),
    t('Materials'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('title'),
    t('image'),
    t('body'),
    t('Page'),
    t('Services'),
  );
  $export['materials_service'] = $view;

  $view = new view();
  $view->name = 'partners_service';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Partners: Service';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Partners';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'title';
  /* Field: Content: Postal Address */
  $handler->display->display_options['fields']['field_partners_postal_address']['id'] = 'field_partners_postal_address';
  $handler->display->display_options['fields']['field_partners_postal_address']['table'] = 'field_data_field_partners_postal_address';
  $handler->display->display_options['fields']['field_partners_postal_address']['field'] = 'field_partners_postal_address';
  $handler->display->display_options['fields']['field_partners_postal_address']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_partners_postal_address']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['field_partners_postal_address']['type'] = 'services';
  $handler->display->display_options['fields']['field_partners_postal_address']['settings'] = array(
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  /* Field: Content: partners_leaflet */
  $handler->display->display_options['fields']['field_partners_leaflet']['id'] = 'field_partners_leaflet';
  $handler->display->display_options['fields']['field_partners_leaflet']['table'] = 'field_data_field_partners_leaflet';
  $handler->display->display_options['fields']['field_partners_leaflet']['field'] = 'field_partners_leaflet';
  $handler->display->display_options['fields']['field_partners_leaflet']['label'] = 'coordinates';
  $handler->display->display_options['fields']['field_partners_leaflet']['click_sort_column'] = 'wkt';
  $handler->display->display_options['fields']['field_partners_leaflet']['type'] = 'services';
  $handler->display->display_options['fields']['field_partners_leaflet']['settings'] = array(
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  /* Field: Content: Tags */
  $handler->display->display_options['fields']['field_partners_tags']['id'] = 'field_partners_tags';
  $handler->display->display_options['fields']['field_partners_tags']['table'] = 'field_data_field_partners_tags';
  $handler->display->display_options['fields']['field_partners_tags']['field'] = 'field_partners_tags';
  $handler->display->display_options['fields']['field_partners_tags']['label'] = 'tags';
  $handler->display->display_options['fields']['field_partners_tags']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_partners_tags']['delta_offset'] = '0';
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = 'body';
  $handler->display->display_options['fields']['body']['type'] = 'services';
  $handler->display->display_options['fields']['body']['settings'] = array(
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'partner' => 'partner',
  );

  /* Display: Services */
  $handler = $view->new_display('services', 'Services', 'services_1');
  $handler->display->display_options['path'] = 'partners-list';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['path'] = 'partners-list';
  $translatables['partners_service'] = array(
    t('Master'),
    t('Partners'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('title'),
    t('Postal Address'),
    t('coordinates'),
    t('tags'),
    t('body'),
    t('Services'),
    t('Page'),
  );
  $export['partners_service'] = $view;

  $view = new view();
  $view->name = 'projects_service';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Projects: Service';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Projects';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: External repository */
  $handler->display->display_options['fields']['field_external_repository']['id'] = 'field_external_repository';
  $handler->display->display_options['fields']['field_external_repository']['table'] = 'field_data_field_external_repository';
  $handler->display->display_options['fields']['field_external_repository']['field'] = 'field_external_repository';
  $handler->display->display_options['fields']['field_external_repository']['label'] = 'external repository';
  $handler->display->display_options['fields']['field_external_repository']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_external_repository']['type'] = 'services';
  $handler->display->display_options['fields']['field_external_repository']['settings'] = array(
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  /* Field: Content: Machines */
  $handler->display->display_options['fields']['field_machines']['id'] = 'field_machines';
  $handler->display->display_options['fields']['field_machines']['table'] = 'field_data_field_machines';
  $handler->display->display_options['fields']['field_machines']['field'] = 'field_machines';
  $handler->display->display_options['fields']['field_machines']['label'] = 'machines';
  $handler->display->display_options['fields']['field_machines']['type'] = 'services';
  $handler->display->display_options['fields']['field_machines']['settings'] = array(
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  $handler->display->display_options['fields']['field_machines']['delta_offset'] = '0';
  /* Field: Content: Materials */
  $handler->display->display_options['fields']['field_materials']['id'] = 'field_materials';
  $handler->display->display_options['fields']['field_materials']['table'] = 'field_data_field_materials';
  $handler->display->display_options['fields']['field_materials']['field'] = 'field_materials';
  $handler->display->display_options['fields']['field_materials']['label'] = 'materials';
  $handler->display->display_options['fields']['field_materials']['type'] = 'services';
  $handler->display->display_options['fields']['field_materials']['settings'] = array(
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  $handler->display->display_options['fields']['field_materials']['delta_offset'] = '0';
  /* Field: Content: Project image */
  $handler->display->display_options['fields']['field_project_image']['id'] = 'field_project_image';
  $handler->display->display_options['fields']['field_project_image']['table'] = 'field_data_field_project_image';
  $handler->display->display_options['fields']['field_project_image']['field'] = 'field_project_image';
  $handler->display->display_options['fields']['field_project_image']['label'] = 'project image';
  $handler->display->display_options['fields']['field_project_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_project_image']['type'] = 'services';
  $handler->display->display_options['fields']['field_project_image']['settings'] = array(
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  /* Field: Content: Project files */
  $handler->display->display_options['fields']['field_project_files']['id'] = 'field_project_files';
  $handler->display->display_options['fields']['field_project_files']['table'] = 'field_data_field_project_files';
  $handler->display->display_options['fields']['field_project_files']['field'] = 'field_project_files';
  $handler->display->display_options['fields']['field_project_files']['label'] = 'project files';
  $handler->display->display_options['fields']['field_project_files']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_project_files']['type'] = 'services';
  $handler->display->display_options['fields']['field_project_files']['settings'] = array(
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  $handler->display->display_options['fields']['field_project_files']['delta_offset'] = '0';
  /* Field: Content: Tags */
  $handler->display->display_options['fields']['field_project_tags']['id'] = 'field_project_tags';
  $handler->display->display_options['fields']['field_project_tags']['table'] = 'field_data_field_project_tags';
  $handler->display->display_options['fields']['field_project_tags']['field'] = 'field_project_tags';
  $handler->display->display_options['fields']['field_project_tags']['label'] = 'tags';
  $handler->display->display_options['fields']['field_project_tags']['type'] = 'services';
  $handler->display->display_options['fields']['field_project_tags']['settings'] = array(
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  $handler->display->display_options['fields']['field_project_tags']['delta_offset'] = '0';
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = 'body';
  $handler->display->display_options['fields']['body']['type'] = 'services';
  $handler->display->display_options['fields']['body']['settings'] = array(
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'project' => 'project',
  );

  /* Display: Services */
  $handler = $view->new_display('services', 'Services', 'services_1');
  $handler->display->display_options['path'] = 'projects-list';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['path'] = 'projects-list';
  $translatables['projects_service'] = array(
    t('Master'),
    t('Projects'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('title'),
    t('external repository'),
    t('machines'),
    t('materials'),
    t('project image'),
    t('project files'),
    t('tags'),
    t('body'),
    t('Services'),
    t('Page'),
  );
  $export['projects_service'] = $view;

  $view = new view();
  $view->name = 'staff_service';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'users';
  $view->human_name = 'Staff: Service';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Staff';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access user profiles';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = 'name';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  /* Field: User: Picture */
  $handler->display->display_options['fields']['picture']['id'] = 'picture';
  $handler->display->display_options['fields']['picture']['table'] = 'users';
  $handler->display->display_options['fields']['picture']['field'] = 'picture';
  $handler->display->display_options['fields']['picture']['label'] = 'image';
  /* Field: User: Roles */
  $handler->display->display_options['fields']['rid']['id'] = 'rid';
  $handler->display->display_options['fields']['rid']['table'] = 'users_roles';
  $handler->display->display_options['fields']['rid']['field'] = 'rid';
  $handler->display->display_options['fields']['rid']['label'] = 'role';
  /* Field: User: Bio */
  $handler->display->display_options['fields']['field_bio']['id'] = 'field_bio';
  $handler->display->display_options['fields']['field_bio']['table'] = 'field_data_field_bio';
  $handler->display->display_options['fields']['field_bio']['field'] = 'field_bio';
  $handler->display->display_options['fields']['field_bio']['label'] = 'bio';
  $handler->display->display_options['fields']['field_bio']['type'] = 'services';
  $handler->display->display_options['fields']['field_bio']['settings'] = array(
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  /* Sort criterion: User: Created date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'users';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: User: Roles */
  $handler->display->display_options['filters']['rid']['id'] = 'rid';
  $handler->display->display_options['filters']['rid']['table'] = 'users_roles';
  $handler->display->display_options['filters']['rid']['field'] = 'rid';
  $handler->display->display_options['filters']['rid']['value'] = array(
    3 => '3',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'staff-list';

  /* Display: Services */
  $handler = $view->new_display('services', 'Services', 'services_1');
  $handler->display->display_options['path'] = 'staff-list';
  $translatables['staff_service'] = array(
    t('Master'),
    t('Staff'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('name'),
    t('image'),
    t('role'),
    t('bio'),
    t('Page'),
    t('Services'),
  );
  $export['staff_service'] = $view;

  $view = new view();
  $view->name = 'suppliers_service';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Suppliers: Service';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Suppliers';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'title';
  /* Field: Content: Postal address */
  $handler->display->display_options['fields']['field_suppliers_postaddress']['id'] = 'field_suppliers_postaddress';
  $handler->display->display_options['fields']['field_suppliers_postaddress']['table'] = 'field_data_field_suppliers_postaddress';
  $handler->display->display_options['fields']['field_suppliers_postaddress']['field'] = 'field_suppliers_postaddress';
  $handler->display->display_options['fields']['field_suppliers_postaddress']['label'] = 'postal address';
  $handler->display->display_options['fields']['field_suppliers_postaddress']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['field_suppliers_postaddress']['type'] = 'services';
  $handler->display->display_options['fields']['field_suppliers_postaddress']['settings'] = array(
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  /* Field: Content: suppliers_leaflet */
  $handler->display->display_options['fields']['field_suppliers_leaflet']['id'] = 'field_suppliers_leaflet';
  $handler->display->display_options['fields']['field_suppliers_leaflet']['table'] = 'field_data_field_suppliers_leaflet';
  $handler->display->display_options['fields']['field_suppliers_leaflet']['field'] = 'field_suppliers_leaflet';
  $handler->display->display_options['fields']['field_suppliers_leaflet']['label'] = 'coordinates';
  $handler->display->display_options['fields']['field_suppliers_leaflet']['click_sort_column'] = 'wkt';
  $handler->display->display_options['fields']['field_suppliers_leaflet']['type'] = 'services';
  $handler->display->display_options['fields']['field_suppliers_leaflet']['settings'] = array(
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  /* Field: Content: Materials */
  $handler->display->display_options['fields']['field_suppliers_materials']['id'] = 'field_suppliers_materials';
  $handler->display->display_options['fields']['field_suppliers_materials']['table'] = 'field_data_field_suppliers_materials';
  $handler->display->display_options['fields']['field_suppliers_materials']['field'] = 'field_suppliers_materials';
  $handler->display->display_options['fields']['field_suppliers_materials']['label'] = 'materials';
  $handler->display->display_options['fields']['field_suppliers_materials']['type'] = 'services';
  $handler->display->display_options['fields']['field_suppliers_materials']['settings'] = array(
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  $handler->display->display_options['fields']['field_suppliers_materials']['delta_offset'] = '0';
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = 'body';
  $handler->display->display_options['fields']['body']['type'] = 'services';
  $handler->display->display_options['fields']['body']['settings'] = array(
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'supplier' => 'supplier',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'suppliers-list';

  /* Display: Services */
  $handler = $view->new_display('services', 'Services', 'services_1');
  $handler->display->display_options['path'] = 'suppliers-list';
  $translatables['suppliers_service'] = array(
    t('Master'),
    t('Suppliers'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('title'),
    t('postal address'),
    t('coordinates'),
    t('materials'),
    t('body'),
    t('Page'),
    t('Services'),
  );
  $export['suppliers_service'] = $view;

  return $export;
}
