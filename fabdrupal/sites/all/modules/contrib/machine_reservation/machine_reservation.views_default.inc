<?php
/**
 * @file
 * machine_reservation.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function machine_reservation_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'machines';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Machines: Page';
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
  $handler->display->display_options['row_plugin'] = 'node';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Image */
  $handler->display->display_options['fields']['field_machine_image']['id'] = 'field_machine_image';
  $handler->display->display_options['fields']['field_machine_image']['table'] = 'field_data_field_machine_image';
  $handler->display->display_options['fields']['field_machine_image']['field'] = 'field_machine_image';
  $handler->display->display_options['fields']['field_machine_image']['label'] = '';
  $handler->display->display_options['fields']['field_machine_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_machine_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_machine_image']['settings'] = array(
    'image_style' => '',
    'image_link' => '',
  );
  /* Field: Content: Manufacturer */
  $handler->display->display_options['fields']['field_manufacturer']['id'] = 'field_manufacturer';
  $handler->display->display_options['fields']['field_manufacturer']['table'] = 'field_data_field_manufacturer';
  $handler->display->display_options['fields']['field_manufacturer']['field'] = 'field_manufacturer';
  $handler->display->display_options['fields']['field_manufacturer']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_manufacturer']['settings'] = array(
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  /* Field: Content: Link */
  $handler->display->display_options['fields']['field_manufacturer_link']['id'] = 'field_manufacturer_link';
  $handler->display->display_options['fields']['field_manufacturer_link']['table'] = 'field_data_field_manufacturer_link';
  $handler->display->display_options['fields']['field_manufacturer_link']['field'] = 'field_manufacturer_link';
  $handler->display->display_options['fields']['field_manufacturer_link']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_manufacturer_link']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_manufacturer_link']['type'] = 'link_url';
  $handler->display->display_options['fields']['field_manufacturer_link']['settings'] = array(
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  /* Field: Content: Power */
  $handler->display->display_options['fields']['field_machine_power']['id'] = 'field_machine_power';
  $handler->display->display_options['fields']['field_machine_power']['table'] = 'field_data_field_machine_power';
  $handler->display->display_options['fields']['field_machine_power']['field'] = 'field_machine_power';
  $handler->display->display_options['fields']['field_machine_power']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_machine_power']['settings'] = array(
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  /* Field: Content: Work Area: X */
  $handler->display->display_options['fields']['field_work_area_x']['id'] = 'field_work_area_x';
  $handler->display->display_options['fields']['field_work_area_x']['table'] = 'field_data_field_work_area_x';
  $handler->display->display_options['fields']['field_work_area_x']['field'] = 'field_work_area_x';
  $handler->display->display_options['fields']['field_work_area_x']['label'] = '';
  $handler->display->display_options['fields']['field_work_area_x']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_work_area_x']['settings'] = array(
    'thousand_separator' => ' ',
    'decimal_separator' => '.',
    'scale' => '2',
    'prefix_suffix' => 1,
  );
  /* Field: Content: Work Area: Y */
  $handler->display->display_options['fields']['field_work_area_y']['id'] = 'field_work_area_y';
  $handler->display->display_options['fields']['field_work_area_y']['table'] = 'field_data_field_work_area_y';
  $handler->display->display_options['fields']['field_work_area_y']['field'] = 'field_work_area_y';
  $handler->display->display_options['fields']['field_work_area_y']['label'] = '';
  $handler->display->display_options['fields']['field_work_area_y']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_work_area_y']['settings'] = array(
    'thousand_separator' => ' ',
    'decimal_separator' => '.',
    'scale' => '2',
    'prefix_suffix' => 1,
  );
  /* Field: Content: Work Area: Z */
  $handler->display->display_options['fields']['field_work_area_z']['id'] = 'field_work_area_z';
  $handler->display->display_options['fields']['field_work_area_z']['table'] = 'field_data_field_work_area_z';
  $handler->display->display_options['fields']['field_work_area_z']['field'] = 'field_work_area_z';
  $handler->display->display_options['fields']['field_work_area_z']['label'] = '';
  $handler->display->display_options['fields']['field_work_area_z']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_work_area_z']['settings'] = array(
    'thousand_separator' => ' ',
    'decimal_separator' => '.',
    'scale' => '2',
    'prefix_suffix' => 1,
  );
  /* Field: Content: File Types */
  $handler->display->display_options['fields']['field_file_type']['id'] = 'field_file_type';
  $handler->display->display_options['fields']['field_file_type']['table'] = 'field_data_field_file_type';
  $handler->display->display_options['fields']['field_file_type']['field'] = 'field_file_type';
  $handler->display->display_options['fields']['field_file_type']['label'] = '';
  $handler->display->display_options['fields']['field_file_type']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_file_type']['settings'] = array(
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  /* Field: Content: Materials */
  $handler->display->display_options['fields']['field_machine_materials']['id'] = 'field_machine_materials';
  $handler->display->display_options['fields']['field_machine_materials']['table'] = 'field_data_field_machine_materials';
  $handler->display->display_options['fields']['field_machine_materials']['field'] = 'field_machine_materials';
  $handler->display->display_options['fields']['field_machine_materials']['label'] = '';
  $handler->display->display_options['fields']['field_machine_materials']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_machine_materials']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_machine_materials']['delta_offset'] = '0';
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
  $handler->display->display_options['path'] = 'machines';
  $translatables['machines'] = array(
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
    t('Manufacturer'),
    t('Link'),
    t('Power'),
    t('Page'),
  );
  $export['machines'] = $view;

  return $export;
}
