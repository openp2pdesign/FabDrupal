<?php
/**
 * @file
 * machine_reservation.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function machine_reservation_user_default_permissions() {
  $permissions = array();

  // Exported permission: administer MERCI.
  $permissions['administer MERCI'] = array(
    'name' => 'administer MERCI',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'merci',
  );

  // Exported permission: create confirmed reservations.
  $permissions['create confirmed reservations'] = array(
    'name' => 'create confirmed reservations',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'merci',
  );

  // Exported permission: create reservations.
  $permissions['create reservations'] = array(
    'name' => 'create reservations',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'merci',
  );

  // Exported permission: create reservations outside hours of operation.
  $permissions['create reservations outside hours of operation'] = array(
    'name' => 'create reservations outside hours of operation',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'merci',
  );

  // Exported permission: manage reservations.
  $permissions['manage reservations'] = array(
    'name' => 'manage reservations',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'merci',
  );

  // Exported permission: override max hours over closed days.
  $permissions['override max hours over closed days'] = array(
    'name' => 'override max hours over closed days',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'merci',
  );

  // Exported permission: suspend MERCI access.
  $permissions['suspend MERCI access'] = array(
    'name' => 'suspend MERCI access',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'merci',
  );

  // Exported permission: view all reservations.
  $permissions['view all reservations'] = array(
    'name' => 'view all reservations',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'merci',
  );

  return $permissions;
}
