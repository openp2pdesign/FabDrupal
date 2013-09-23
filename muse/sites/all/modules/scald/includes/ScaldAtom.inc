<?php
/**
 * @file
 * Defines a class for Scald Atoms.
 */

class ScaldAtom {
  /**
   * Constructs a ScaldAtom object.
   */
  public function __construct($type, $provider, array $values = array()) {
    // Add default values.
    $values += array(
      'title' => '',
      'type' => $type,
      'provider' => $provider,
      'publisher' => $GLOBALS['user']->uid,
      'actions' => scald_atom_defaults($type)->actions,
      'data' => array(),
    );

    foreach ($values as $key => $value) {
      $this->$key = $value;
    }
  }
}
