<?php

/**
 * @file
 * Hooks related to Scald atoms and providers.
 *
 * SCALD HOOK EXECUTION STACK
 * ==========================
 *
 * The order in which the hooks execute can be fairly important. Each hook
 * might add more information to the Atom object or potentially even remove
 * some. Knowing when a given hook fires relative to others is important. Note
 * that each hook will be called for each module that implements it in turn.
 * The order in which the module's hooks are called is determined by their
 * relative weight in the {system} table.
 *
 * The following illustrate when each of the various hooks are called relative
 * to one another. Keep in mind that there is often prior and intervening code
 * which could have a significant impact on the contents of $atom or the other
 * variables being passed to the hooks.
 *
 *
 * system_modules_submit() [The form at /admin/build/modules is submitted]
 *   -> {provider}_install() [Drupal hook]
 *   -> {provider}_enable() [Drupal hook]
 *   -> {provider}_scald_provider()
 *
 * scald_render()
 *   -> scald_fetch()
 *     -> {type_provider}_scald_fetch($mode = 'type')
 *     -> {atom_provider}_scald_fetch($mode = 'atom')
 *   -> scald_prerender()
 *     -> {type_provider}_scald_prerender($mode = 'type')
 *     -> {atom_provider}_scald_prerender($mode = 'atom')
 *     -> {transcoder_provider}_scald_prerender($mode = 'transcoder')
 *     -> {context_provider}_scald_prerender($mode = 'context')
 *   -> {context_provider}_scald_render()
 *
 * scald_register_atom(), scald_update_atom(), scald_unregister_atom()
 *   -> {type_provider}_scald_fetch($mode = 'type')
 *   -> {atom_provider}_scald_fetch($mode = 'atom')
 *   -> {relationship_provider}_scald_prerender($mode = 'relationship')
 *   -> {transcoder_provider}_scald_prerender($mode = 'transcoder')
 *
 * scald_rendered_to_sas()
 *   -> scald_rendered_to_sas_LANGUAGE()
 */

/**
 * Define information about atom providers provided by a module.
 *
 * @return
 *   An array of atom providers. This array is keyed on the unified atom type.
 *   A module can define at most one provider for each atom type. Each provider
 *   is defined by a untranslated name.
 */
function hook_scald_atom_providers() {
  return array(
    'image' => 'Image hosted on Flickr',
  );

  // This code will never be hit, but is necessary to mark the string
  // for translation on localize.d.o
  t('Image hosted on Flickr');
}

/**
 * Define information about atom players provided by a module.
 *
 * @return
 *   An array of atom players. This array is keyed on the machine-readable
 *   player name. Each player is defined as an associative array containing the
 *   following items:
 *   - "name": The untranslated human-readable name of the player.
 *   - "description": The longer description of the player.
 *   - "type": The type array that is compatible with the player. The special
 *     value '*' means this player is compatible with all atom types.
 */
function hook_scald_player() {
  return array(
    'html5' => array(
      'name' => 'HTML5 player',
      'description' => 'The HTML5 player for images and videos.',
      'type' => array('image', 'video'),
    ),
  );
}

/**
 * Settings form for player.
 *
 * It is not a really hook. Only one module is invoke.
 *
 * @param $form
 *
 * @param $form_state
 *
 * $form_state['scald'] contains atom type, context and player value.
 */
function hook_scald_player_settings_form($form, &$form_state) {
}

/**
 * Respond to atom insertion.
 *
 * It is not a really hook. Only one module is invoke. This function is a direct
 * port from Drupal 6 version of Scald. It is similar to hook_field_insert in
 * Drupal 7.
 *
 * @param $atom
 *   The atom being created.
 *
 * @param $mode
 *   Role of the callee function. Can have the following values:
 *   - "type" (not really, as we don't have type provider now)
 *   - "atom"
 *   - "transcoder"
 */
function hook_scald_register_atom($atom, $mode) {
}

/**
 * Respond to atom update.
 *
 * Similar to hook_scald_register_atom(), but this hook is invoked for existing
 * atoms.
 *
 * @param $atom
 *   The atom being created.
 *
 * @param $mode
 *   Role of the callee function. Can have the following values:
 *   - "type" (not really, as we don't have type provider now)
 *   - "atom"
 *   - "transcoder"
 *
 * @see hook_scald_register_atom().
 */
function hook_scald_update_atom($atom, $mode) {
}

/**
 * Respond to atom deletion.
 *
 * @param $atom
 *   The atom being created.
 *
 * @param $mode
 *   Role of the callee function. Can have the following values:
 *   - "type" (not really, as we don't have type provider now)
 *   - "atom"
 *   - "transcoder"
 *
 * @see hook_scald_register_atom().
 */
function hook_scald_unregister_atom($atom, $mode) {
}

/**
 * Respond to atom fetch (load).
 *
 * @param $atom
 *   The atom being created.
 *
 * @param $mode
 *   Role of the callee function. Can have the following values:
 *   - "type" (not really, as we don't have type provider now)
 *   - "atom"
 *
 * @see hook_scald_register_atom().
 */
function hook_scald_fetch($atom, $mode) {
  if ($mode == 'atom') {
    $atom->description = 'description';
    $atom->source_file = 'source path';
    $atom->thumbnail_file = 'thumbnail path';
    // Typically, for Atom Providers which are based on Drupal nodes, the $node
    // object is attached to the $atom as the base_entity member.
    $atom->base_entity = node_load($atom->sid);
  }
}

/**
 * Respond to atom actions.
 *
 * This hook is not yet implemented.
 */
function hook_scald_action($atom, $action, $mode) {
}

/**
 * Respond to atom prerender.
 *
 * @param $atom
 *   The atom being created.
 *
 * @param $mode
 *   Role of the callee function. Can have the following values:
 *   - "type" (not really, as we don't have type provider now)
 *   - "atom"
 *   - "transcoder"
 *   - "context"
 *   - "player"
 *
 */
function hook_scald_prerender($atom, $context, $options, $mode) {
}

/**
 * Respond to atom render.
 *
 * It is not a really hook. Only one module is invoke.
 *
 * @param $atom
 *   The atom being rendered.
 *
 * @param $context
 *   The context used to render.
 *
 * @param $options
 *   The options which is a string in JSON format.
 */
function hook_scald_render($atom, $context, $options) {
}

/**
 * Convert from a rendered format to SAS.
 */
function hook_scald_rendered_to_sas_LANGUAGE($text) {
}

