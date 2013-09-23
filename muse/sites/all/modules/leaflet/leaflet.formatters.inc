<?php

/**
 * Implements hook_field_formatter_info().
 */
function leaflet_field_formatter_info() {
  $formatters = array();

  if (module_exists('geofield')) {
    $formatters['geofield_leaflet'] = array(
      'label' => t('Leaflet'),
      'field types' => array('geofield'),
      'settings' => array('leaflet_map' => '', 'icon' => '', 'height' => 400, 'popup' => 0),
    );
  }

  return $formatters;
}

/**
 * Implements hook_field_formatter_settings_form().
 */
function leaflet_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  $element = array();

  if ($display['type'] == 'geofield_leaflet') {
    $options = array('' => t('-- Select --'));
    foreach (leaflet_map_get_info() as $key => $map) {
      $options[$key] = t($map['label']);
    }

    $element['leaflet_map'] = array(
      '#title' => t('Leaflet Map'),
      '#type' => 'select',
      '#options' => $options,
      '#default_value' => $settings['leaflet_map'],
      '#required' => TRUE,
    );
    $element['height'] = array(
      '#title' => t('Map Height'),
      '#type' => 'textfield',
      '#default_value' => $settings['height'],
      '#field_suffix' => t('px'),
      '#element_validate' => array('element_validate_integer_positive'),
    );
    $element['popup'] = array(
      '#title' => t('Popup'),
      '#description' => t('Show a popup for single location fields.'),
      '#type' => 'checkbox',
      '#default_value' => $settings['popup'],
    );
    $element['icon'] = array(
      '#title' => t('Map Icon'),
      '#description' => t('These settings will overwrite the icon settings defined in the map definition.'),
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => !isset($settings['icon']['iconUrl']),
    );
    $element['icon']['iconUrl'] = array(
      '#title' => t('Icon URL'),
      '#description' => t('Can be an absolute or relative URL.'),
      '#type' => 'textfield',
      '#maxlength' => 999,
      '#default_value' => $settings['icon']['iconUrl'],
      '#element_validate' => array('leaflet_icon_validate')
    );
    $element['icon']['shadowUrl'] = array(
      '#title' => t('Icon Shadow URL'),
      '#type' => 'textfield',
      '#maxlength' => 999,
      '#default_value' => $settings['icon']['shadowUrl'],
      '#element_validate' => array('leaflet_icon_validate')
    );

    $element['icon']['iconSize'] = array(
      '#title' => t('Icon Size'),
      '#type' => 'fieldset',
      '#collapsible' => FALSE,
      '#description' => t('Size of the icon image in pixels.')
    );
    $element['icon']['iconSize']['x'] = array(
      '#title' => t('Width'),
      '#type' => 'textfield',
      '#maxlength' => 3,
      '#size' => 3,
      '#default_value' => isset($settings['icon']['iconSize']['x']) ? $settings['icon']['iconSize']['x'] : '',
      '#element_validate' => array('element_validate_integer_positive'),
    );
    $element['icon']['iconSize']['y'] = array(
      '#title' => t('Height'),
      '#type' => 'textfield',
      '#maxlength' => 3,
      '#size' => 3,
      '#default_value' => isset($settings['icon']['iconSize']['y']) ? $settings['icon']['iconSize']['y'] : '',
      '#element_validate' => array('element_validate_integer_positive'),
    );

    $element['icon']['iconAnchor'] = array(
      '#title' => t('Icon Anchor'),
      '#type' => 'fieldset',
      '#collapsible' => FALSE,
      '#description' => t('The coordinates of the "tip" of the icon (relative to
        its top left corner). The icon will be aligned so that this point is at the marker\'s geographical location.')
    );
    $element['icon']['iconAnchor']['x'] = array(
      '#title' => t('X'),
      '#type' => 'textfield',
      '#maxlength' => 3,
      '#size' => 3,
      '#default_value' => isset($settings['icon']['iconAnchor']['x']) ? $settings['icon']['iconAnchor']['x'] : '',
      '#element_validate' => array('element_validate_number'),
    );
    $element['icon']['iconAnchor']['y'] = array(
      '#title' => t('Y'),
      '#type' => 'textfield',
      '#maxlength' => 3,
      '#size' => 3,
      '#default_value' => isset($settings['icon']['iconAnchor']['y']) ? $settings['icon']['iconAnchor']['y'] : '',
      '#element_validate' => array('element_validate_number'),
    );

    $element['icon']['shadowAnchor'] = array(
      '#title' => t('Shadow Anchor'),
      '#type' => 'fieldset',
      '#collapsible' => FALSE,
      '#description' => t('The point from which the shadow is shown.')
    );
    $element['icon']['shadowAnchor']['x'] = array(
      '#title' => t('X'),
      '#type' => 'textfield',
      '#maxlength' => 3,
      '#size' => 3,
      '#default_value' => isset($settings['icon']['shadowAnchor']['x']) ? $settings['icon']['shadowAnchor']['x'] : '',
      '#element_validate' => array('element_validate_number'),
    );
    $element['icon']['shadowAnchor']['y'] = array(
      '#title' => t('Y'),
      '#type' => 'textfield',
      '#maxlength' => 3,
      '#size' => 3,
      '#default_value' => isset($settings['icon']['shadowAnchor']['y']) ? $settings['icon']['shadowAnchor']['y'] : '',
      '#element_validate' => array('element_validate_number'),
    );

    $element['icon']['popupAnchor'] = array(
      '#title' => t('Popup Anchor'),
      '#type' => 'fieldset',
      '#collapsible' => FALSE,
      '#description' => t('The point from which the marker popup opens, relative
        to the anchor point.')
    );
    $element['icon']['popupAnchor']['x'] = array(
      '#title' => t('X'),
      '#type' => 'textfield',
      '#maxlength' => 3,
      '#size' => 3,
      '#default_value' => isset($settings['icon']['popupAnchor']['x']) ? $settings['icon']['popupAnchor']['x'] : '',
      '#element_validate' => array('element_validate_number'),
    );
    $element['icon']['popupAnchor']['y'] = array(
      '#title' => t('Y'),
      '#type' => 'textfield',
      '#maxlength' => 3,
      '#size' => 3,
      '#default_value' => isset($settings['icon']['popupAnchor']['y']) ? $settings['icon']['popupAnchor']['y'] : '',
      '#element_validate' => array('element_validate_number'),
    );
  }

  return $element;
}

/**
 * Validation callback for icon urls.
 *
 * @param $element
 * @param $form_state
 * @param $form
 */
function leaflet_icon_validate($element, &$form_state, $form) {
  if (!empty($element['#value']) && !valid_url($element['#value'])) {
    form_error($element, t('Icon URL is invalid'));
  }
}

/**
 * Implements hook_field_formatter_settings_summary().
 */
function leaflet_field_formatter_settings_summary($field, $instance, $view_mode) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  $summary = '';

  if ($display['type'] == 'geofield_leaflet') {
    $summary = t('Leaflet map: @map', array('@map' => $settings['leaflet_map']));
  }

  return $summary;
}

/**
 * Implements hook_field_formatter_view().
 */
function leaflet_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  $settings = $display['settings'];

  if (count($items) == 0) {
    return '';
  }
  else {
    switch ($display['type']) {
      case 'geofield_leaflet':
        $map = leaflet_map_get_info($settings['leaflet_map']);

        $features = leaflet_process_geofield($items);

        // if only a single feature, set the popup content to the entity title
        if ($settings['popup'] && count($items) == 1) {
          $features[0]['popup'] = entity_label($entity_type, $entity);
        }

        if (!empty($settings['icon']) && $settings['icon']['iconUrl']) {
          foreach ($features as $key => $feature) {
            $features[$key]['icon'] = $settings['icon'];
          }
        }

        $element[0] = array('#markup' => leaflet_render_map($map, $features, $settings['height'] . 'px'));

        break;
    }

    return $element;
  }
}

/**
 * Convert a geofield into an array of map points for consumption by the
 * leaflet module as expected by leaflet_render_map().
 *
 * @param array $items
 *   A collection of geofield values.
 *
 * @return array
 */
function leaflet_process_geofield($items = array()) {
  $data = array();

  geophp_load();

  foreach ($items as $delta => $item) {
    // translate linestring to polyline
    if ($item['geo_type'] == 'multilinestring') {
      $item['geo_type'] = 'multipolyline';
    }
    $datum = array('type' => $item['geo_type']);
    switch ($item['geo_type']) {
      case 'point':
        $datum += array(
          'lat' => (float) $item['lat'],
          'lon' => (float) $item['lon'],
        );

        $data[] = $datum;
        break;
      case 'linestring':
        $geom = geoPHP::load($item['wkt'], 'wkt');
        $components = $geom->getComponents();

        foreach ($components as $component) {
          $datum['points'][] = array(
            'lat' => $component->getY(),
            'lon' => $component->getX(),
          );
        }

        $data[] = $datum;
        break;
      case 'polygon':
        $geom = geoPHP::load($item['wkt'], 'wkt');
        $tmp = $geom->getComponents();
        $components = $tmp[0]->getComponents();

        foreach ($components as $component) {
          $datum['points'][] = array(
            'lat' => $component->getY(),
            'lon' => $component->getX(),
          );
        }

        $data[] = $datum;
        break;
      case 'multipolygon':
      case 'multipolyline':
        $geom = geoPHP::load($item['wkt'], 'wkt');

        if ($item['geo_type'] == 'multipolyline') {
          $components = $geom->getComponents();
        }
        else {
          $tmp = $geom->getComponents();
          $components = $tmp[0]->getComponents();
        }

        foreach ($components as $key => $component) {
          $subcomponents = $component->getComponents();
          foreach ($subcomponents as $subcomponent) {
            $datum['component'][$key]['points'][] = array(
              'lat' => $subcomponent->getY(),
              'lon' => $subcomponent->getX(),
            );
          }
          unset($subcomponent);
        }

        $data[] = $datum;
        break;
    }
  }

  return $data;
}
