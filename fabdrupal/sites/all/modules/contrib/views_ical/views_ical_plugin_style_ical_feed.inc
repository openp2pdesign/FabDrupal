<?php

/**
 * @file
 * Views style plugin for the Views iCal module.
 */

/**
 * Default style plugin to render an iCal feed.
 */
class views_ical_plugin_style_ical_feed extends views_plugin_style_rss {

  function attach_to($display_id, $path, $title) {
    $display = $this->view->display[$display_id]->handler;
    $url_options = array();
    $input = $this->view->get_exposed_input();
    if ($input) {
      $url_options['query'] = $input;
    }
    $url_options['absolute'] = TRUE;
    $url = url($this->view->get_url(NULL, $path), $url_options);
    if (empty($this->preview)) {
      $this->view->feed_icon = '';
      drupal_add_html_head_link(array(
        'rel' => 'alternate',
        'type' => 'application/calendar',
        'title' => $title,
        'href' => $url
      ));
    }
  }

  function render() {
    if (empty($this->row_plugin)) {
      debug('views_plugin_style_default: Missing row plugin');
      return;
    }
    $rows = array();
    foreach ($this->view->result as $row_index => $row) {
      $this->view->row_index = $row_index;
      $rows[] = $this->row_plugin->render($row);
    }

    $output = theme($this->theme_functions(),
      array(
        'view' => $this->view,
        'options' => $this->options,
        'rows' => $rows
      ));
    unset($this->view->row_index);
    return $output;
  }
}
