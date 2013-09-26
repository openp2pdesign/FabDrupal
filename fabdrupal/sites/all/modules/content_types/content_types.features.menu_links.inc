<?php
/**
 * @file
 * content_types.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function content_types_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu:faq
  $menu_links['main-menu:faq'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'faq',
    'router_path' => 'faq',
    'link_title' => 'FAQ',
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
    'weight' => -49,
    'parent_path' => '<front>',
  );
  // Exported menu link: main-menu:machines
  $menu_links['main-menu:machines'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'machines',
    'router_path' => 'machines',
    'link_title' => 'Machines',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -47,
    'parent_path' => '<front>',
  );
  // Exported menu link: main-menu:materials
  $menu_links['main-menu:materials'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'materials',
    'router_path' => 'materials',
    'link_title' => 'Materials',
    'options' => array(
      'attributes' => array(
        'title' => 'Materials used normally in this FabLab',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -46,
    'parent_path' => '<front>',
  );
  // Exported menu link: main-menu:node/25
  $menu_links['main-menu:node/25'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/25',
    'router_path' => 'node/%',
    'link_title' => 'The Fab Charter',
    'options' => array(
      'attributes' => array(),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'parent_path' => '<front>',
  );
  // Exported menu link: main-menu:partners
  $menu_links['main-menu:partners'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'partners',
    'router_path' => 'partners',
    'link_title' => 'Partners',
    'options' => array(
      'attributes' => array(
        'title' => 'Look at the partners of the lab',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -44,
    'parent_path' => '<front>',
  );
  // Exported menu link: main-menu:projects
  $menu_links['main-menu:projects'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'projects',
    'router_path' => 'projects',
    'link_title' => 'Projects',
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
    'weight' => -45,
  );
  // Exported menu link: main-menu:staff
  $menu_links['main-menu:staff'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'staff',
    'router_path' => 'staff',
    'link_title' => 'Staff',
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
    'weight' => -50,
    'parent_path' => '<front>',
  );
  // Exported menu link: main-menu:suppliers
  $menu_links['main-menu:suppliers'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'suppliers',
    'router_path' => 'suppliers',
    'link_title' => 'Suppliers',
    'options' => array(
      'attributes' => array(
        'title' => 'Look at the suppliers of the lab',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -45,
    'parent_path' => '<front>',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('FAQ');
  t('Machines');
  t('Materials');
  t('Partners');
  t('Projects');
  t('Staff');
  t('Suppliers');
  t('The Fab Charter');


  return $menu_links;
}
