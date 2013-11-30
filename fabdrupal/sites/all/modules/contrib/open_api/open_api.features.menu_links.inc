<?php
/**
 * @file
 * open_api.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function open_api_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu:node/30
  $menu_links['main-menu:node/30'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/30',
    'router_path' => 'node/%',
    'link_title' => 'API',
    'options' => array(),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -42,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('API');


  return $menu_links;
}
