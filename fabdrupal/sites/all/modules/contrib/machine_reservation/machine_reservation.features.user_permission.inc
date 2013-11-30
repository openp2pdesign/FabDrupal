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

  // Exported permission: 'access rules debug'.
  $permissions['access rules debug'] = array(
    'name' => 'access rules debug',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'rules',
  );

  // Exported permission: 'administer MERCI'.
  $permissions['administer MERCI'] = array(
    'name' => 'administer MERCI',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'merci',
  );

  // Exported permission: 'administer rules'.
  $permissions['administer rules'] = array(
    'name' => 'administer rules',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'rules',
  );

  // Exported permission: 'administer rules forms'.
  $permissions['administer rules forms'] = array(
    'name' => 'administer rules forms',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'rules_forms',
  );

  // Exported permission: 'administer rules forms rules'.
  $permissions['administer rules forms rules'] = array(
    'name' => 'administer rules forms rules',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'rules_forms',
  );

  // Exported permission: 'bypass rules access'.
  $permissions['bypass rules access'] = array(
    'name' => 'bypass rules access',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'rules',
  );

  // Exported permission: 'create confirmed reservations'.
  $permissions['create confirmed reservations'] = array(
    'name' => 'create confirmed reservations',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'merci',
  );

  // Exported permission: 'create reservations'.
  $permissions['create reservations'] = array(
    'name' => 'create reservations',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'merci',
  );

  // Exported permission: 'create reservations outside hours of operation'.
  $permissions['create reservations outside hours of operation'] = array(
    'name' => 'create reservations outside hours of operation',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'merci',
  );

  // Exported permission: 'manage reservations'.
  $permissions['manage reservations'] = array(
    'name' => 'manage reservations',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'merci',
  );

  // Exported permission: 'override max hours over closed days'.
  $permissions['override max hours over closed days'] = array(
    'name' => 'override max hours over closed days',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'merci',
  );

  // Exported permission: 'suspend MERCI access'.
  $permissions['suspend MERCI access'] = array(
    'name' => 'suspend MERCI access',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'merci',
  );

  // Exported permission: 'view all reservations'.
  $permissions['view all reservations'] = array(
    'name' => 'view all reservations',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'merci',
  );

  return $permissions;
}
