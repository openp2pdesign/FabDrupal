<?php
/**
 * @file
 * fabdrupal_blog.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function fabdrupal_blog_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "scald" && $api == "context_config") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function fabdrupal_blog_views_api() {
  return array("api" => "3.0");
}
