<?php
/**
 * @file
 * merci_import_example.feeds_importer_default.inc
 */

/**
 * Implements hook_feeds_importer_default().
 */
function merci_import_example_feeds_importer_default() {
  $export = array();

  $feeds_importer = new stdClass;
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'merci_item';
  $feeds_importer->config = array(
    'name' => 'MERCI Item',
    'description' => 'Import csv to merci item nodes.',
    'fetcher' => array(
      'plugin_key' => 'FeedsFileFetcher',
      'config' => array(
        'allowed_extensions' => 'txt csv tsv xml opml',
        'direct' => 0,
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsCSVParser',
      'config' => array(
        'delimiter' => ',',
        'no_headers' => 0,
      ),
    ),
    'processor' => array(
      'plugin_key' => 'MerciItemProcessor',
      'config' => array(
        'content_type' => 'article',
        'expire' => -1,
        'author' => 0,
        'mappings' => array(
          0 => array(
            'source' => 'type',
            'target' => 'type',
            'unique' => FALSE,
          ),
          1 => array(
            'source' => 'title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'body',
            'target' => 'body',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'merci_default_availability',
            'target' => 'merci_default_availability',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'merci_late_fee_per_hour',
            'target' => 'merci_late_fee_per_hour',
            'unique' => FALSE,
          ),
          5 => array(
            'source' => 'merci_rate_per_hour',
            'target' => 'merci_rate_per_hour',
            'unique' => FALSE,
          ),
          6 => array(
            'source' => 'merci_fee_free_hours',
            'target' => 'merci_fee_free_hours',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => 0,
        'input_format' => NULL,
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => 1800,
    'expire_period' => 3600,
    'import_on_create' => TRUE,
    'process_in_background' => FALSE,
  );
  $export['merci_item'] = $feeds_importer;

  $feeds_importer = new stdClass;
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'merci_type';
  $feeds_importer->config = array(
    'name' => 'MERCI Type',
    'description' => 'Import from csv to MERCI reservable type.',
    'fetcher' => array(
      'plugin_key' => 'FeedsFileFetcher',
      'config' => array(
        'allowed_extensions' => 'txt csv tsv xml opml',
        'direct' => FALSE,
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsCSVParser',
      'config' => array(
        'delimiter' => ',',
        'no_headers' => 0,
      ),
    ),
    'processor' => array(
      'plugin_key' => 'MerciTypeProcessor',
      'config' => array(
        'mappings' => array(
          0 => array(
            'source' => 'type',
            'target' => 'type',
            'unique' => FALSE,
          ),
          1 => array(
            'source' => 'name',
            'target' => 'name',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'description',
            'target' => 'description',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'merci_type_setting',
            'target' => 'merci_type_setting',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => 0,
        'input_format' => NULL,
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => 1800,
    'expire_period' => 3600,
    'import_on_create' => TRUE,
    'process_in_background' => FALSE,
  );
  $export['merci_type'] = $feeds_importer;

  return $export;
}
