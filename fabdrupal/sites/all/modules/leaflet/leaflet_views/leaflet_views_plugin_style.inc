<?php

/**
 * @file
 * Extension of the Views Plugin Style for Leaflet Map
 * Adapted from the GeoField Map views module and the OpenLayers Views module.
 */
class leaflet_views_plugin_style extends views_plugin_style {

  /**
   * If this view is displaying an entity, save the entity type and info.
   */
  function init(&$view, &$display, $options = NULL) {
    parent::init($view, $display, $options);

    foreach (entity_get_info() as $key => $info) {
      if ($view->base_table == $info['base table']) {
        $this->entity_type = $key;
        $this->entity_info = $info;
        break;
      }
    }
  }

  /**
   * Set default options
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['data_source'] = array('default' => '');
    $options['name_field'] = array('default' => '');
    $options['description_field'] = array('default' => '');
    $options['view_mode'] = array('default' => 'full');
    $options['map'] = array('default' => '');
    $options['height'] = array('default' => '400');
    $options['icon'] = array();
    return $options;
  }

  /**
   * Options form
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    // Get list of fields in this view & flag available geodata fields
    $handlers = $this->display->handler->get_handlers('field');

    $fields = array();
    $fields_data = array();
    foreach ($handlers as $field_id => $handler) {
      $fields[$field_id] = $handler->ui_name();

      if (!empty($handler->field_info['type']) && $handler->field_info['type'] == 'geofield') {
        $fields_data[$field_id] = $handler->ui_name();
      }
    }

    // Check whether we have a geofield we can work with
    if (!count($fields_data)) {
      $form['error'] = array(
        '#markup' => t('Please add at least one geofield to the view'),
      );
      return;
    }

    // Map preset.
    $form['data_source'] = array(
      '#type' => 'select',
      '#title' => t('Data Source'),
      '#description' => t('Which field contains geodata?'),
      '#options' => $fields_data,
      '#default_value' => $this->options['data_source'],
      '#required' => TRUE,
    );

    // Name field
    $form['name_field'] = array(
      '#type' => 'select',
      '#title' => t('Title Field'),
      '#description' => t('Choose the field which will appear as a title on tooltips.'),
      // '#options' => $fields,
      '#options' => array_merge(array('' => ''), $fields),
      '#default_value' => $this->options['name_field'],
    );

    $desc_options = array_merge(array(
        '' => '',
    ), $fields);

    // Add an option to render the entire entity using a view mode
    if ($this->entity_type) {
      $desc_options += array(
        '#rendered_entity' => '<' . t('!entity entity', array('!entity' => $this->entity_type)) . '>',
      );
    }

    $form['description_field'] = array(
      '#type' => 'select',
      '#title' => t('Description Content'),
      '#description' => t('Choose the field or rendering method which will appear as a description on tooltips or popups.'),
      '#required' => FALSE,
      '#options' => $desc_options,
      '#default_value' => $this->options['description_field'],
    );

    // Taken from openlayers_views_style_data::options_form().
    // Create view mode options
    if ($this->entity_type) {

      // Get the labels (human readable) of the view modes
      $view_mode_options = array();
      foreach ($this->entity_info['view modes'] as $key => $view_mode) {
        $view_mode_options[$key] = $view_mode['label'];
      }

      //output the form
      $form['view_mode'] = array(
        '#type' => 'select',
        '#title' => t('View mode'),
        '#description' => t('View modes are ways of displaying entities.'),
        '#options' => $view_mode_options,
        '#default_value' => !empty($this->options['view_mode']) ?
          $this->options['view_mode'] : 'full',
        '#states' => array(
          'visible' => array(
            ':input[name="style_options[description_field]"]' => array('value' => '#rendered_entity'),
          ),
        ),
      );
    }

    // Choose a map preset
    $map_options = array();
    foreach (leaflet_map_get_info() as $key => $map) {
      $map_options[$key] = t($map['label']);
    }

    $form['map'] = array(
      '#title' => t('Map'),
      '#type' => 'select',
      '#options' => $map_options,
      '#default_value' => $this->options['map'] ? $this->options['map'] : '',
      '#required' => TRUE,
    );

    $form['height'] = array(
      '#title' => t('Map height'),
      '#type' => 'textfield',
      '#field_suffix' => t('px'),
      '#size' => 4,
      '#default_value' => $this->options['height'],
      '#required' => FALSE,
    );

    $form['hide_empty'] = array(
      '#title' => t('Hide empty'),
      '#type' => 'checkbox',
      '#description' => t('Hide the Leaflet map if there are no results to display.'),
      '#default_value' => isset($this->options['hide_empty']) ? $this->options['hide_empty'] : TRUE
    );

    $form['icon'] = array(
      '#title' => t('Map Icon'),
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => !isset($this->options['icon']['iconUrl']),
    );

    $form['icon']['iconUrl'] = array(
      '#title' => t('Icon URL'),
      '#description' => t('Can be an absolute or relative URL.'),
      '#type' => 'textfield',
      '#maxlength' => 999,
      '#default_value' => isset($this->options['icon']['iconUrl']) ? $this->options['icon']['iconUrl'] : '',
      '#element_validate' => array('leaflet_icon_validate')
    );

    $form['icon']['shadowUrl'] = array(
      '#title' => t('Icon Shadow URL'),
      '#type' => 'textfield',
      '#maxlength' => 999,
      '#default_value' => isset($this->options['icon']['shadowUrl']) ? $this->options['icon']['shadowUrl'] : '',
      '#element_validate' => array('leaflet_icon_validate')
    );

    $form['icon']['iconSize'] = array(
      '#title' => t('Icon Size'),
      '#type' => 'fieldset',
      '#collapsible' => FALSE,
      '#description' => t('Size of the icon image in pixels.')
    );

    $form['icon']['iconSize']['x'] = array(
      '#title' => t('Width'),
      '#type' => 'textfield',
      '#maxlength' => 3,
      '#size' => 3,
      '#default_value' => isset($this->options['icon']['iconSize']['x']) ? $this->options['icon']['iconSize']['x'] : '',
      '#element_validate' => array('element_validate_integer_positive'),
    );

    $form['icon']['iconSize']['y'] = array(
      '#title' => t('Height'),
      '#type' => 'textfield',
      '#maxlength' => 3,
      '#size' => 3,
      '#default_value' => isset($this->options['icon']['iconSize']['y']) ? $this->options['icon']['iconSize']['y'] : '',
      '#element_validate' => array('element_validate_integer_positive'),
    );

    $form['icon']['iconAnchor'] = array(
      '#title' => t('Icon Anchor'),
      '#type' => 'fieldset',
      '#collapsible' => FALSE,
      '#description' => t('The coordinates of the "tip" of the icon (relative to its top left corner). The icon will be aligned so that this point is at the marker\'s geographical location.')
    );

    $form['icon']['iconAnchor']['x'] = array(
      '#title' => t('X'),
      '#type' => 'textfield',
      '#maxlength' => 3,
      '#size' => 3,
      '#default_value' => isset($this->options['icon']['iconAnchor']['x']) ? $this->options['icon']['iconAnchor']['x'] : '',
      '#element_validate' => array('element_validate_number'),
    );

    $form['icon']['iconAnchor']['y'] = array(
      '#title' => t('Y'),
      '#type' => 'textfield',
      '#maxlength' => 3,
      '#size' => 3,
      '#default_value' => isset($this->options['icon']['iconAnchor']['y']) ? $this->options['icon']['iconAnchor']['y'] : '',
      '#element_validate' => array('element_validate_number'),
    );

    $form['icon']['shadowAnchor'] = array(
      '#title' => t('Shadow Anchor'),
      '#type' => 'fieldset',
      '#collapsible' => FALSE,
      '#description' => t('The point from which the shadow is shown.')
    );
    $form['icon']['shadowAnchor']['x'] = array(
      '#title' => t('X'),
      '#type' => 'textfield',
      '#maxlength' => 3,
      '#size' => 3,
      '#default_value' => isset($this->options['icon']['shadowAnchor']['x']) ? $this->options['icon']['shadowAnchor']['x'] : '',
      '#element_validate' => array('element_validate_number'),
    );
    $form['icon']['shadowAnchor']['y'] = array(
      '#title' => t('Y'),
      '#type' => 'textfield',
      '#maxlength' => 3,
      '#size' => 3,
      '#default_value' => isset($this->options['icon']['shadowAnchor']['y']) ? $this->options['icon']['shadowAnchor']['y'] : '',
      '#element_validate' => array('element_validate_number'),
    );

    $form['icon']['popupAnchor'] = array(
      '#title' => t('Popup Anchor'),
      '#type' => 'fieldset',
      '#collapsible' => FALSE,
      '#description' => t('The point from which the marker popup opens, relative to the anchor point.')
    );

    $form['icon']['popupAnchor']['x'] = array(
      '#title' => t('X'),
      '#type' => 'textfield',
      '#maxlength' => 3,
      '#size' => 3,
      '#default_value' => isset($this->options['icon']['popupAnchor']['x']) ? $this->options['icon']['popupAnchor']['x'] : '',
      '#element_validate' => array('element_validate_number'),
    );

    $form['icon']['popupAnchor']['y'] = array(
      '#title' => t('Y'),
      '#type' => 'textfield',
      '#maxlength' => 3,
      '#size' => 3,
      '#default_value' => isset($this->options['icon']['popupAnchor']['y']) ? $this->options['icon']['popupAnchor']['y'] : '',
      '#element_validate' => array('element_validate_number'),
    );
  }

  /**
   * Validate the options form.
   */
  function options_validate(&$form, &$form_state) {
    if (!is_numeric($form_state['values']['style_options']['height']) || $form_state['values']['style_options']['height'] < 0) {
      form_error($form['height'], t('Map height needs to be a positive number'));
    }
  }

  /**
   * Renders view
   */
  function render() {
    if (!empty($this->view->live_preview)) {
      return t('No preview available');
    }

    $data = array();

    if ($this->options['data_source']) {
      $this->render_fields($this->view->result);
      foreach ($this->view->result as $id => $result) {
        $geofield = $this->get_field_value($id, $this->options['data_source']);

        if (!empty($geofield)) {
          $points = leaflet_process_geofield($geofield);

          // Render the entity with the selected view mode
          if ($this->options['description_field'] === '#rendered_entity' && is_object($result)) {
            $entities = entity_load($this->entity_type, array($result->{$this->entity_info['entity keys']['id']}));

            $build = entity_view(
              $this->entity_type,
              $entities,
              $this->options['view_mode']
            );

            $description = drupal_render($build);
          }

          // Normal rendering via fields
          elseif ($this->options['description_field']) {
            $description = $this->rendered_fields[$id][$this->options['description_field']];
          }

          // Attach pop-ups if we have a description field
          if (isset($description)) {
            foreach ($points as &$point) {
              $point['popup'] = $description;
            }
          }

          // Attach also titles, they might be used later on
          if ($this->options['name_field']) {
            foreach ($points as &$point) {
              $point['label'] = $this->rendered_fields[$id][$this->options['name_field']];
            }
          }

          // Let modules modify the points data.
          drupal_alter('leaflet_views_alter_points_data', $result, $points);

          $data = array_merge($data, $points);

          if (!empty($this->options['icon']) && $this->options['icon']['iconUrl']) {
            foreach ($data as $key => $feature) {
              $data[$key]['icon'] = $this->options['icon'];
            }
          }
        }
      }

      $map = leaflet_map_get_info($this->options['map']);

      if (!empty($data) || (isset($this->options['hide_empty']) && !$this->options['hide_empty'])) {
        return leaflet_render_map($map, $data, $this->options['height'] . 'px');
      }
    }

    return '';
  }
}
