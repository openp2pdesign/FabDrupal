<?php

/**
 * @file
 * Menu callback for Leaflet More Maps admin configuration.
 */
function leaflet_more_maps_admin_configure() {
  $map_info = array();
  // @todo call hook_leaflet_map_info() ?
  _leaflet_more_maps_assemble_default_map_info($map_info);

  $all_layer_keys = array();
  foreach ($map_info as $map_key => $map) {
    foreach ($map['layers'] as $layer_key => $layer) {
      $all_layer_keys["$map_key $layer_key"] = "$map_key $layer_key"; // unique
    }
  }
  $custom_map_layers = variable_get('leaflet_more_maps_custom_maps', array());

  if (empty($custom_map_layers)) {
    for ($i = 1; $i <= LEAFLET_MORE_MAPS_NO_CUSTOM_MAPS; $i++) {
      $custom_map_layers[$i] = array(
        'map_key' => '',
        'layer_keys' => array(),
        'reverse_order' => FALSE
      );
    }
  }
  for ($i = 1; $i <= LEAFLET_MORE_MAPS_NO_CUSTOM_MAPS; $i++) {
    $form['map'][$i] = array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => $i > 1,
      '#title' => t('Custom map #@number layer selection', array('@number' => $i)),
      '#description' => t('')
    );
    $form['map'][$i]['map-key'] = array(
      '#type' => 'textfield',
      '#title' => t('Name of custom map #@number in the administrative UI', array('@number' => $i)),
      '#default_value' => $custom_map_layers[$i]['map-key'],
      '#description' => t('Use a blank field to remove this layer configuration from the set of selectable maps.')
    );
    $form['map'][$i]['layer-keys'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Select one or more layers to be included in this map.'),
      '#options' => $all_layer_keys,
      '#default_value' => $custom_map_layers[$i]['layer-keys'],
      '#description' => t('If you select two or more layers, these will be selectable via radio buttons in the layer switcher on your map.')
    );
    $form['map'][$i]['reverse-order'] = array(
      '#type' => 'checkbox',
      '#title' => t('Reverse order in layer switcher'),
      '#default_value' => $custom_map_layers[$i]['reverse-order'],
      '#description' => t('The last layer in the switcher will be the default.')
    );
    // Organise the $form_state['values'] structure available after submission
    $form['map'][$i]['map-key']['#parents'] = array('map', $i, 'map-key');
    $form['map'][$i]['layer-keys']['#parents'] = array('map', $i, 'layer-keys');
    $form['map'][$i]['reverse-order']['#parents'] = array('map', $i, 'reverse-order');
  }

  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save map configurations')
  );
  $form['#submit'][] = 'leaflet_more_maps_admin_configure_form_submit';

  $form['#theme'] = 'system_settings_form';
  return $form;
}

/**
 * Execute leaflet_admin_configure_form.
 */
function leaflet_more_maps_admin_configure_form_submit($form, &$form_state) {

  //form_state_values_clean($form_state);
  $custom_maps = $form_state['values']['map'];

  // Clear out the unticked boxes
  foreach ($custom_maps as &$custom_map) {
    $custom_map['layer-keys'] = array_filter($custom_map['layer-keys']);
  }
  variable_set('leaflet_more_maps_custom_maps', $custom_maps);

  drupal_set_message(t('The map layer configurations have been saved.'));

  // Refresh cache table or hook_leaflet_more_maps() won't be called.
  cache_clear_all('*', 'cache', TRUE);
}
