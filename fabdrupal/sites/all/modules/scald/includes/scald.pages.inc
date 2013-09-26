<?php
/**
 * @file
 * This file contains the various callbacks related to Scald defined pages.
 *
 * A lot of callbacks related to the creation and  edition of the atoms
 * entities are defined here.
 */

/**
 * Creates the page listing possible Scald Atom Types.
 */
function scald_atom_add() {
  $types = scald_types();
  if (empty($types)) {
    return '<p>' . t('You have not installed any Scald providers yet. Go to the <a href="@admin-modules">modules administration page</a> to install a Scald provider.', array('@admin-modules' => url('admin/modules', array('fragment' => 'edit-modules-scald')))) . '</p>';
  }

  $content = array();

  // Check if the user is allowed to create atoms of any type.
  $any = user_access('administer scald atoms') || user_access('create atom of any type');
  foreach ($types as $name => $type) {
    // Skip atom type the user isn't allowed to create.
    if (!$any && !user_access('create atom of ' . $type->type . ' type')) {
      continue;
    }
    $content[] = array(
      'title' => $type->title,
      'href'  => 'atom/add/' . $name,
      'localized_options' => array(),
      'description' => '',
    );
  }
  return theme('node_add_list', array('content' => $content));
}

/**
 * Atom add page callback.
 */
function scald_atom_add_page($js, $type, $step = NULL, $atom_id = NULL) {
  if ($js) {
    ctools_include('modal');
    ctools_include('ajax');
  }

  ctools_include('object-cache');
  ctools_include('wizard');

  $cache_id = isset($atom_id) ? 'edit:' . $atom_id : 'add';

  // Start by getting the list of all the modules that said they can provide
  // this atom type.
  $providers = scald_atom_providers();
  $sources = $providers[$type->type];
  $source = key($sources);

  // If there's more than one, provide a choice between them. Otherwise, skip
  // a step and select the only provider upfront.
  if (empty($step)) {
    if (count($sources) < 2) {
      $step = 'add';
    }
    else {
      $step = 'source';
    }
    ctools_object_cache_clear('scald_atom', $cache_id);
  }

  $form_state = array(
    'ajax' => $js,
    'scald' => ctools_object_cache_get('scald_atom', $cache_id),
  );

  if (empty($form_state['scald'])) {
    $form_state['scald'] = array(
      'type' => $type,
      'source' => isset($source) ? $source : NULL,
    );
  }

  $form_state['scald']['step'] = $step;

  $form_info = array(
    'id' => 'scald-atom-add',
    'path' => 'atom/add/' . $type->type . '/' . ($js ? 'ajax' : 'nojs') . '/%step',
    'show trail' => TRUE,
    'show back' => FALSE,
    'show cancel' => TRUE,
    'show return' => FALSE,
    'next callback' => 'scald_atom_add_wizard_next',
    'finish callback' => 'scald_atom_add_wizard_finish',
    'cancel callback' => 'scald_atom_add_wizard_cancel',
    'order' => array(
      'source' => t('Source'),
      'add' => t('Add'),
      'options' => t('Options'),
    ),
    'forms' => array(
      'source' => array(
        'form id' => 'scald_atom_add_form_source',
      ),
      'add' => array(
        'form id' => 'scald_atom_add_form_add',
      ),
      'options' => array(
        'form id' => 'scald_atom_add_form_options',
      ),
    ),
  );

  // Send this all off to our form. This is like drupal_get_form only wizardy.
  $form = ctools_wizard_multistep_form($form_info, $step, $form_state);
  $output = drupal_render($form);

  // If $output is FALSE, there was no actual form.
  if ($js) {
    // If javascript is active, we have to use a render array.
    $commands = array();
    if ($output === FALSE || !empty($form_state['complete'])) {
      // Dismiss the modal.
      $commands[] = array('command' => 'dnd_refresh');
      $commands[] = ctools_modal_command_dismiss();
    }
    elseif (!empty($form_state['cancel'])) {
      // If cancelling, return to the activity.
      $commands[] = ctools_modal_command_dismiss();
    }
    else {
      $commands = ctools_modal_form_render($form_state, $output);
    }
    print ajax_render($commands);
    exit;
  }
  else {
    if ($output === FALSE || !empty($form_state['complete'])) {
      $atom = $form_state['scald']['atom'];
      drupal_goto('atom/' . $atom->sid . '/view');
    }
    elseif (!empty($form_state['cancel'])) {
      drupal_goto('atom/add');
    }
    else {
      return $output;
    }
  }
}

/**
 * Source form.
 */
function scald_atom_add_form_source($form, &$form_state) {
  $providers = scald_atom_providers();
  $sources = $providers[$form_state['scald']['type']->type];

  // Localize the source names. Note that all the strings
  // have been marked for extraction in their corresponding
  // modules, so this call is safe.
  $sources = array_map('t', $sources);

  $form_state['title'] = t('Source');
  $form['source'] = array(
    '#title' => t('Source'),
    '#type' => 'select',
    '#options' => $sources,
    '#description' => t('Please choose the source of your new atom'),
  );

  return $form;
}

/**
 * Handles the source step form submission.
 */
function scald_atom_add_form_source_submit(&$form, &$form_state) {
  $form_state['scald']['source'] = $form_state['values']['source'];
}

/**
 * Add form.
 */
function scald_atom_add_form_add($form, &$form_state) {
  $scald = $form_state['scald'];
  $function = $scald['source'] . '_scald_add_form';
  if (function_exists($function)) {
    $function($form, $form_state);
  }
  else {
    // TODO: Figure out what should be done here.
    $form['error'] = array(
      '#markup' => 'Import without form; does it makes sense ?',
    );
  }

  return $form;
}

/**
 * Handles the add step form submission.
 */
function scald_atom_add_form_add_submit(&$form, &$form_state) {
  $scald = $form_state['scald'];
  $atom = new ScaldAtom($scald['type']->type, $scald['source']);

  // Allow the source provider to alter it, filling in defaults value.
  $function = $atom->provider . '_scald_add_form_fill';
  if (function_exists($function)) {
    $function($atom, $form, $form_state);
  }

  // And put it in the form_state
  $form_state['scald']['atom'] = $atom;
}

/**
 * Options form.
 */
function scald_atom_add_form_options($form, &$form_state) {
  $atom = $form_state['scald']['atom'];

  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#required' => TRUE,
    '#default_value' => $atom->title,
  );

  $actions = scald_actions();
  $options = array();
  $options_default = array();
  foreach ($actions as $name => $action) {
    $options[$name] = $action['title'];
    $options_default[$name] = $atom->actions & $action['bitmask'] ? $name : '';
  }
  $form['scald_actions'] = array(
    '#type' => 'checkboxes',
    '#title' => 'Openly available actions',
    '#group' => 'additional_settings',
    '#options' => $options,
    '#default_value' => $options_default,
    '#access' => user_access('administer scald atoms'),
  );

  field_attach_form('scald_atom', $atom, $form, $form_state);

  $form['actions']['submit']['#value'] = t('Save');

  return $form;
}

/**
 * Handles the final atom creation step form submission.
 */
function scald_atom_add_form_options_submit(&$form, &$form_state) {
  $atom = $form_state['scald']['atom'];

  if (is_array($form_state['values']['scald_actions'])) {
    $bitstream = 0;
    $actions = scald_actions();
    foreach ($actions as $name => $action) {
      if (!empty($form_state['values']['scald_actions'][$name])) {
        $bitstream |= $action['bitmask'];
      }
    }
    $form_state['values']['actions'] = $bitstream;
  }

  $op = empty($atom->sid) ? t('created') : t('updated');

  // Let entity add its properties to the atom.
  entity_form_submit_build_entity('scald_atom', $atom, $form, $form_state);

  // Then save it...
  scald_atom_save($atom);

  // Add a message confirming the creation.
  drupal_set_message(t('Atom %title, of type %type has been %op', array(
    '%title' => $atom->title,
    '%type' => $atom->type,
    '%op' => $op,
  )));
}

/**
 * Handle the 'next' click on the add/edit pane form wizard.
 */
function scald_atom_add_wizard_next(&$form_state) {
  $cache_id = isset($form_state['scald']['atom']->sid) ? 'edit:' . $form_state['scald']['atom']->sid : 'add';
  ctools_object_cache_set('scald_atom', $cache_id, $form_state['scald']);
}

/**
 * Handle the 'finish' click on the add/edit pane form wizard.
 */
function scald_atom_add_wizard_finish(&$form_state) {
  $form_state['complete'] = TRUE;
}

/**
 * Handle the 'cancel' click on the add/edit pane form wizard.
 */
function scald_atom_add_wizard_cancel(&$form_state) {
  $form_state['cancel'] = TRUE;
}

/**
 * Page callback for the view of an atom.
 */
function scald_atom_page_view($atom) {
  return scald_render($atom, 'full');
}

/**
 * Atom edit page callback.
 */
function scald_atom_edit_page($js, $atom) {
  // The edit page is nothing else other than the add page, at the Options step.
  // We prepare data for this step then send back to the add page. The only
  // useful information at this step is the atom itself.
  $scald = array(
    'atom' => $atom,
  );
  $types = scald_types();
  ctools_include('object-cache');
  ctools_object_cache_set('scald_atom', 'edit:' . $atom->sid, $scald);
  return scald_atom_add_page($js, $types[$atom->type], 'options', $atom->sid);
}

/**
 * Handles the delete of an existing atom.
 */
function scald_atom_delete_confirm($form, &$form_state, $atom) {
  // Always provide entity id in the same form key as in the entity edit form.
  $form['sid'] = array('#type' => 'value', '#value' => $atom->sid);
  return confirm_form($form,
    t('Are you sure you want to delete %title?', array('%title' => $atom->title)),
    'admin/content/atoms',
    t('<p>Note that unchecking the Fetch checkbox in the "<em>Openly available actions</em>" field of this atom <a href="!url">edit form</a> makes the atom disapears for everyone but scald administrators, and is usally a better idea.</p><p>This action cannot be undone.</p>', array('!url' => url("atom/{$atom->sid}/edit"))),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Execute atom deletion.
 */
function scald_atom_delete_confirm_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    $atom = scald_atom_load($form_state['values']['sid']);
    scald_atom_delete($atom->sid);
    watchdog('scald_atom', '@type: deleted %title.', array('@type' => $atom->type, '%title' => $atom->title));
    $types = scald_type_get_names();
    drupal_set_message(t('@type %title has been deleted.', array('@type' => $types[$atom->type], '%title' => $atom->title)));
  }

  $form_state['redirect'] = 'admin/content/atoms';
}
/**
 * Fetch atoms and return in JSON format.
 *
 * @param string $context
 *   The context the atoms should be rendered in.
 * @param string $sids
 *   Comma separated list of atom ids.
 */
function scald_atom_fetch_atoms($context, $sids) {
  $output = array();
  $atoms = scald_atom_load_multiple(explode(',', $sids));
  foreach ($atoms as $sid => $atom) {
    $output[$sid][$context] = scald_render($atom, $context);
  }
  drupal_json_output($output);
}
