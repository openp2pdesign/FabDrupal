<?php
/**
 * Implements hook_form_FORM_ID_alter().
 *
 * Allows the profile to alter the site configuration form.
 */
if (!function_exists("system_form_install_configure_form_alter")) {
  function system_form_install_configure_form_alter(&$form, $form_state) {
    $form['site_information']['site_name']['#default_value'] = 'FabDrupal';
  }
}

/**
 * Implements hook_form_alter().
 *
 * Select the current install profile by default.
 */
if (!function_exists("system_form_install_select_profile_form_alter")) {
  function system_form_install_select_profile_form_alter(&$form, $form_state) {
    foreach ($form['profile'] as $key => $element) {
      $form['profile'][$key]['#value'] = 'fabdrupal';
    }
  }
}


/**
 * Implements hook_install_tasks().
 */
function fabdrupal_install_tasks() {
  $tasks = array(
    'fabdrupal_machine_info' => array(
      'display_name' => st('Machine reservation'),
      'type' => 'form',
    ),
  );
  return $tasks;
}
  
  
function fabdrupal_machine_info() { 

  // Update the table for enable machine reservation
  // It works, but get resetted after...
  db_update('merci_node_type')
   ->fields(array('merci_type_setting' => 'resource'))
   ->condition('type', 'machine')
   ->execute(); 
 
  $form['help'] = array(
      '#markup' => '<p>' . st('Due to a technical limitation in the current version, you have to manually configure the possibility for machine reservation.') . '</p><p>'. st('Please go to Structure &gt; Content Types &gt; Machines and under MERCI Settings check Resource.')  .'</p>',
    );
  
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] =  array(
    '#type' => 'submit',
    '#value' => st('Continue'),
  );
  return $form;
}