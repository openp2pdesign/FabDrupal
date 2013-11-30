<?php
/**
 * @file
 * fabdrupal_blog.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function fabdrupal_blog_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "scald" && $api == "context_config") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function fabdrupal_blog_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}
