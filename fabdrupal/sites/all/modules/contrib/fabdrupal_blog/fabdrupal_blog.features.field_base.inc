<?php
/**
 * @file
 * fabdrupal_blog.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function fabdrupal_blog_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'scald_author_url'
  $field_bases['scald_author_url'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'scald_author_url',
    'foreign keys' => array(
      'format' => array(
        'columns' => array(
          'format' => 'format',
        ),
        'table' => 'filter_format',
      ),
    ),
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'label' => 'URL',
    'locked' => 1,
    'module' => 'text',
    'settings' => array(
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  return $field_bases;
}
