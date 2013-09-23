<?php

/**
 * @file
 * Provides admin form for Flickr's Scald Provider.
 */

/**
 * Defines the flickr settings form.
 */
function scald_flickr_settings_form() {
  $form = array();
  // Flickr api key configuration.
  $scald_flickr_api_key = variable_get('scald_flickr_api_key', '');
  $form['scald_flickr_api'] = array(
    '#type' => 'fieldset',
    '#title' => t('Flickr API'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['scald_flickr_api']['scald_flickr_api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Flickr API Key'),
    '#required' => TRUE,
    '#default_value' => $scald_flickr_api_key,
  );
  if (empty($scald_flickr_api_key)) {
    $form['scald_flickr_api']['scald_flickr_api_key']['#description'] = t('API Key from Flickr. !link', array(
      '!link' => l(t('Get one!'), 'http://www.flickr.com/services/apps/by/me'))
    );
  }
  else {
    $form['scald_flickr_api']['scald_flickr_api_key']['#description'] = t('API Key from Flickr.');
  }

  $form['scald_flickr_api']['scald_flickr_api_secret'] = array(
    '#type' => 'textfield',
    '#title' => t('Flickr API Shared Secret'),
    '#required' => TRUE,
    '#default_value' => variable_get('scald_flickr_api_secret', ''),
    '#description' => t("API key's secret from Flickr."),
  );

  return system_settings_form($form);
}
