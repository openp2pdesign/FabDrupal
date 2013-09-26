<?php
/**
 * @file
 * various_settings.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function various_settings_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu:contact
  $menu_links['main-menu:contact'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'contact',
    'router_path' => 'contact',
    'link_title' => 'Contact',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -43,
  );
  // Exported menu link: main-menu:flickr
  $menu_links['main-menu:flickr'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'flickr',
    'router_path' => 'flickr',
    'link_title' => 'Gallery',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -46,
  );
  // Exported menu link: main-menu:users-map
  $menu_links['main-menu:users-map'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'users-map',
    'router_path' => 'users-map',
    'link_title' => 'Users map',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -44,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Contact');
  t('Gallery');
  t('Users map');


  return $menu_links;
}
