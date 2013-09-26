<?php
/**
 * @file
 * open_api.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function open_api_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "oauth_common" && $api == "oauth") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "services" && $api == "services") {
    return array("version" => "3");
  }
}

/**
 * Implements hook_views_api().
 */
function open_api_views_api() {
  return array("api" => "3.0");
}
