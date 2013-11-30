<?php

/**
 * Implements hook_field_views_data().
 */
function eventbritefield_field_views_data($field) {
  $data = field_views_field_default_views_data($field);

  return $data;
}
