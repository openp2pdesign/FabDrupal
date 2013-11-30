<?php
/**
 * @file
 * machine_reservation.features.inc
 */

/**
 * Implements hook_views_api().
 */
function machine_reservation_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function machine_reservation_node_info() {
  $items = array(
    'machine' => array(
      'name' => t('Machine'),
      'base' => 'node_content',
      'description' => t('Use <em>machines</em> pages for the machines available in the FabLab'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
