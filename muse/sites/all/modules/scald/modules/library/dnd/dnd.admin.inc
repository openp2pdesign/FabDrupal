<?php
/**
 * @file
 * Provides the administration related parts of the DnD module.
 */

/**
 * Provides the main DnD settings form.
 */
function dnd_admin_form() {
  $libraries = dnd_get_libraries();
  $form['dnd_callback_url'] = array(
    '#type' => 'select',
    '#title' => t('Library'),
    '#default_value' => dnd_get_library(),
    '#description' => t('The library that will available on node edit forms if they contains fields referencing rich media content, such as Multimedia Editorial Element or Resource reference fields.'),
    '#options' => $libraries,
  );
  return system_settings_form($form);
}
