<?php
/**
 * @file
 * Theme functions for integrating the HybridAuth module.
 */

/**
 * Template preprocess function for hybridauth_widget.
 */
function template_preprocess_hybridauth_widget(&$vars, $hook) {
  $element = $vars['element'];
  $providers = array();
  if ($element['#hybridauth_destination']) {
    $query = array('destination' => $element['#hybridauth_destination']);
  }
  else {
    $query = drupal_get_destination();
  }

  if ($element['#hybridauth_widget_type'] == 'list') {
    $onclick = '';
    if (!empty($element['#hybridauth_onclick'])) {
      $onclick = $element['#hybridauth_onclick'];
    }
    elseif ($element['#hybridauth_window_type'] == 'current') {
      $onclick = "jQuery(this).parents('.hybridauth-widget').after('<div>' + Drupal.t('Contacting') + ' ' + this.title + '...</div>');";
    }
    elseif ($element['#hybridauth_window_type'] == 'popup') {
      $onclick = "popup_window = window.open(this.href, 'hybridauth', 'location=no,menubar=no,resizable=yes,scrollbars=yes,status=no,titlebar=yes,toolbar=no,channelmode=yes,fullscreen=yes,width=800,height=500'); popup_window.focus(); return false;";
    }
    foreach (hybridauth_get_enabled_providers() as $provider_id => $provider_name) {
      $providers[] = l(
        theme('hybridauth_provider_icon', array('icon_pack' => $element['#hybridauth_widget_icon_pack'], 'provider_id' => $provider_id, 'provider_name' => $provider_name)),
        'hybridauth/window/' . $provider_id,
        array(
          'html' => TRUE,
          'query' => $query,
          'attributes' => array(
            'title' => $provider_name,
            'class' => array('hybridauth-widget-provider'),
            'rel' => array('nofollow'),
            'onclick' => $onclick,
          ),
        )
      );
    }
  }
  else {
    $provider_id = 'none';
    $class = array();
    if ($element['#hybridauth_widget_use_overlay']) {
      $class = array('ctools-use-modal', 'ctools-modal-hybridauthmodal');
      ctools_include('modal');
      ctools_modal_add_js();
      $settings = array(
        'hybridauthmodal' => array(
          'modalSize' => array(
            'type' => 'scale',
            'width' => '400px',
            'height' => '200px',
            'addWidth' => 0,
            'addHeight' => 0,
            'contentRight' => 25,
            'contentBottom' => 45,
          ),
          'modalTheme' => 'HybridAuthModalDialog',
          // 'throbberTheme' => 'HybridAuthModalThrobber',
          'modalOptions' => array(
            'opacity' => 0.55,
            'background' => '#000',
          ),
          'animation' => 'fadeIn',
          'animationSpeed' => 'slow',
          'closeText' => t('Close'),
          'closeImage' => '',
          // 'loadingText' => t('Loading...'),
          /* 'throbber' => theme('image', array(
            'path' => ctools_image_path('throbber.gif'),
            'title' => t('Loading...'),
            'alt' => t('Loading'),
          )), */
        ),
      );
      drupal_add_js($settings, 'setting');
    }

    $providers[] = l(
      ($element['#hybridauth_widget_type'] == 'link') ?
        $element['#hybridauth_widget_link_text'] :
        theme('hybridauth_provider_icon', array('icon_pack' => $element['#hybridauth_widget_icon_pack'], 'provider_id' => $provider_id, 'provider_name' => $element['#hybridauth_widget_link_title'])),
      'hybridauth/providers/nojs/' . $element['#hybridauth_widget_icon_pack'],
      array(
        'html' => TRUE,
        'query' => $query,
        'attributes' => array(
          'title' => $element['#hybridauth_widget_link_title'],
          'class' => $class,
          'rel' => array('nofollow'),
        ),
      )
    );
  }

  _hybridauth_add_icon_pack_files($element['#hybridauth_widget_icon_pack']);

  $vars['providers'] = $providers;
}

/**
 * Template preprocess function for hybridauth_provider_icon.
 */
function template_preprocess_hybridauth_provider_icon(&$vars, $hook) {
  _hybridauth_add_icon_pack_files($vars['icon_pack']);
  if (!isset($vars['provider_name'])) {
    $vars['provider_name'] = hybridauth_get_provider_name($vars['provider_id']);
  }
  $icon_pack_classes = array(
    'hybridauth-icon',
    drupal_html_class('hybridauth-icon-' . $vars['icon_pack']),
    drupal_html_class('hybridauth-' . $vars['provider_id']),
    drupal_html_class('hybridauth-' . $vars['provider_id'] . '-' . $vars['icon_pack']),
  );
  $vars['icon_pack_classes'] = implode(' ', $icon_pack_classes);
}
