<?php
/**
 * @file
 * This file contains the Scald Atom controller.
 */

/**
 * Controller class for Scald Atoms.
 *
 * This extends DrupalDefaultEntityController, adding special handling
 * for ScaldAtom objects.
 */
class ScaldAtomController extends DrupalDefaultEntityController {
  /**
   * Overrides DrupalDefaultEntityController::attachLoad().
   */
  protected function attachLoad(&$atoms, $revision_id = FALSE) {
    foreach ($atoms as $atom) {
      $atom->data = unserialize($atom->data);
    }

    parent::attachLoad($atoms, $revision_id);
  }
}
