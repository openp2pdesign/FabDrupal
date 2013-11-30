<?php

/**
 * @file
 * Theme files for Views iCal.
 */

/**
 * Preprocess an iCal feed
 */
function template_preprocess_views_ical_vcalendar(&$vars) {
  $view = $vars['view'];
  $view_title = $view->get_title();

  $title = variable_get('site_name', 'Drupal');
  if ($slogan = variable_get('site_slogan', '')) {
    $title .= ' - ' . $slogan;
  }
  $title .= !empty($view_title) ? ': ' . $view_title : '';

  $vars['title'] = check_plain($title);

  // During live preview we don't want to output the header since the contents
  // of the feed are being displayed inside a normal HTML page.
  if (empty($vars['view']->live_preview)) {

    // Keep devel module from appending queries to ical export.
    $GLOBALS['devel_shutdown'] = FALSE;
    drupal_add_http_header('Content-Type', 'application/calendar; charset=utf-8');
  }
}

/**
 * Default theme function for all iCal rows.
 */
function template_preprocess_views_ical_vevent(&$vars) {
//  template_preprocess_views_view_fields($vars);
  $view = $vars['view'];

  // Loop through the fields for this view.
  $previous_inline = FALSE;
  $vars['fields'] = array(); // ensure it's at least an empty array.
  foreach ($view->field as $id => $field) {
    // render this even if set to exclude so it can be used elsewhere.
    if (!isset($view->row_index)) {
      $view->row_index = 0;
    }
    $field_output = $view->style_plugin->get_field($view->row_index, $id);
    $empty = $field->is_value_empty($field_output, $field->options['empty_zero']);
    if (empty($field->options['exclude']) && (!$empty || (empty($field->options['hide_empty']) && empty($vars['options']['hide_empty'])))) {
      $object = new stdClass();
      $object->handler = &$view->field[$id];
      $object->inline = !empty($vars['options']['inline'][$id]);

      $object->element_type = $object->handler->element_type(TRUE, empty($vars['options']['default_field_elements']), $object->inline);
      if ($object->element_type) {
        $class = '';
        if ($object->handler->options['element_default_classes']) {
          $class = 'field-content';
        }

        if ($classes = $object->handler->element_classes($view->row_index)) {
          if ($class) {
            $class .= ' ';
          }
          $class .=  $classes;
        }

        $pre = '<' . $object->element_type;
        if ($class) {
          $pre .= ' class="' . $class . '"';
        }
        $field_output = $pre . '>' . $field_output . '</' . $object->element_type . '>';
      }

      // Protect ourself somewhat for backward compatibility. This will prevent
      // old templates from producing invalid HTML when no element type is selected.
      if (empty($object->element_type)) {
        $object->element_type = 'span';
      }

      $object->content = $field_output;
      if (isset($view->field[$id]->field_alias) && isset($vars['row']->{$view->field[$id]->field_alias})) {
        $object->raw = $vars['row']->{$view->field[$id]->field_alias};
      }
      else {
        $object->raw = NULL; // make sure it exists to reduce NOTICE
      }

      if (!empty($vars['options']['separator']) && $previous_inline && $object->inline && $object->content) {
        $object->separator = filter_xss_admin($vars['options']['separator']);
      }

      $object->class = drupal_clean_css_identifier($id);

      $previous_inline = $object->inline;
      $object->inline_html = $object->handler->element_wrapper_type(TRUE, TRUE);
      if ($object->inline_html === '' && !empty($vars['options']['default_field_elements'])) {
        $object->inline_html = $object->inline ? 'span' : 'div';
      }

      // Set up the wrapper HTML.
      $object->wrapper_prefix = '';
      $object->wrapper_suffix = '';

      if ($object->inline_html) {
        $class = '';
        if ($object->handler->options['element_default_classes']) {
          $class = "views-field views-field-" . $object->class;
        }

        if ($classes = $object->handler->element_wrapper_classes($view->row_index)) {
          if ($class) {
            $class .= ' ';
          }
          $class .= $classes;
        }

        $object->wrapper_prefix = '<' . $object->inline_html;
        if ($class) {
          $object->wrapper_prefix .= ' class="' . $class . '"';
        }
        $object->wrapper_prefix .= '>';
        $object->wrapper_suffix = '</' . $object->inline_html . '>';
      }

      // Set up the label for the value and the HTML to make it easier
      // on the template.
      $object->label = check_plain($view->field[$id]->label());
      $object->label_html = '';
      if ($object->label) {
        $object->label_html .= $object->label;
        if ($object->handler->options['element_label_colon']) {
          $object->label_html .= ':';
        }

        $object->element_label_type = $object->handler->element_label_type(TRUE, empty($vars['options']['default_field_elements']));
        if ($object->element_label_type) {
          $class = '';
          if ($object->handler->options['element_default_classes']) {
            $class = 'views-label views-label-' . $object->class;
          }

          $element_label_class = $object->handler->element_label_classes($view->row_index);
          if ($element_label_class) {
            if ($class) {
              $class .= ' ';
            }

            $class .= $element_label_class;
          }

          $pre = '<' . $object->element_label_type;
          if ($class) {
            $pre .= ' class="' . $class . '"';
          }
          $pre .= '>';

          $object->label_html = $pre . $object->label_html . '</' . $object->element_label_type . '>';
        }
      }

      $vars['fields'][$id] = $object;
    }
  }

}
