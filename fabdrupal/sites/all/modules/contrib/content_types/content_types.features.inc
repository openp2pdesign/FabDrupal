<?php
/**
 * @file
 * content_types.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function content_types_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "scald" && $api == "context_config") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function content_types_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function content_types_node_info() {
  $items = array(
    'faq' => array(
      'name' => t('FAQ'),
      'base' => 'node_content',
      'description' => t('Use <em>faq</em> content for the frequently asked questions in the FabLab'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'material' => array(
      'name' => t('Material'),
      'base' => 'node_content',
      'description' => t('Use <em>materials</em> pages for the materials available in the FabLab'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'partner' => array(
      'name' => t('Partner'),
      'base' => 'node_content',
      'description' => t('Use <em>partners</em> pages for the organizations and people that collaborate with the FabLab'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'project' => array(
      'name' => t('Project'),
      'base' => 'node_content',
      'description' => t('Use <em>projects</em> pages for the projects developed in the FabLab'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'supplier' => array(
      'name' => t('Supplier'),
      'base' => 'node_content',
      'description' => t('Use <em>suppliers</em> pages for the suppliers of <em>materials</em> for the FabLab'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
