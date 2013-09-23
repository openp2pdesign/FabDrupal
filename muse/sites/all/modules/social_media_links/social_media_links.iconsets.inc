<?php

/**
 * @file
 * Callbacks for the icon sets.
 */

/**
 * Register the default icon sets.
 *
 * @return array
 *   Array of icon sets.
 */
function social_media_links_social_media_links_iconset_info() {
  $icons['elegantthemes'] = array(
    'name' => 'Elegant Themes Icons',
    'publisher' => 'Elegant Themes',
    'publisher url' => 'http://www.elegantthemes.com/',
    'styles' => array(
      '32' => '32x32',
    ),
    'path callback' => 'social_media_links_path_elegantthemes',
    'download url' => 'http://www.elegantthemes.com/blog/resources/beautiful-free-social-media-icons',
    'included' => TRUE,
  );

  return $icons;
}

/**
 * Callback with the informations about the elegantthemes icon set.
 *
 * @param string $platform
 *   Name of the platform for which the path is returned.
 *
 * @param string $style
 *   Size of the icons.
 *
 * @return string
 *   The image path.
 */
function social_media_links_path_elegantthemes($platform = 'twitter', $style = NULL) {
  $info = social_media_links_iconset('elegantthemes');
  $style = '32x32';

  switch ($platform) {
    case 'contact':
      $platform = 'email';
      break;
  }

  if ($info['included']) {
    $path = drupal_get_path('module', 'social_media_links') . '/libraries/elegantthemes_icons/PNG/' . $platform . '.png';
  }

  return $path;
}
