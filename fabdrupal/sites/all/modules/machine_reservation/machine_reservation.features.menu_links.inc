<?php
/**
 * @file
 * machine_reservation.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function machine_reservation_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu:reservations
  $menu_links['main-menu:reservations'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'reservations',
    'router_path' => 'reservations',
    'link_title' => 'Reservations',
    'options' => array(
      'attributes' => array(
        'title' => 'Book here the machines in the lab',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'parent_path' => 'machines',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Reservations');


  return $menu_links;
}
