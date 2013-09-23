<?php

/**
 * @file
 * Simpletest case for node_example module.
 *
 * Verify example module functionality.
 */

/**
 * Functionality tests for merci module.
 * General setup and functions all merci tests should inherit.
 */
class MerciTestCase extends DrupalWebTestCase {


  public $admin_user;

  function setUp() {
    // Enable the module.
    parent::setUp(
        //'content',
        //'fieldgroup',
        //'optionwidgets',
        //'text',
        //'number',
        //'jquery_ui',
        //'date_api',
        //'date',
        //'date_timezone',
        //'date_popup',
        //'text',
        //'views',
        'merci'
        //'merci_staff'

        );

    $perms = user_permission_get_modules();
    $this->verbose('perms: ' . var_export($perms, TRUE));
    // Create admin user. 
    $this->admin_user = $this->drupalCreateUser(array(
      'administer nodes', // Required to set revision checkbox
      'bypass node access',
      'administer content types',
      'access administration pages',
      'administer site configuration',
      'view revisions',
      'revert revisions',
      //'access devel information',
      'administer MERCI',
      'manage reservations'
    ));
    // Login the admin user.
    $this->drupalLogin($this->admin_user);

    $settings = array (
      'merci_default_reservation_status' => '2',
      'merci_max_days_advance_reservation' => '0',
      'merci_saturday_is_weekend' => '1',
      'merci_sunday_is_weekend' => '1',
      'merci_hours_monday' => '09:00-17:00',
      'merci_hours_tuesday' => '09:00-17:00',
      'merci_hours_wednesday' => '09:00-17:00',
      'merci_hours_thursday' => '09:00-17:00',
      'merci_hours_friday' => '09:00-17:00',
      'merci_hours_saturday' => '09:00-17:00',
      'merci_hours_sunday' => '09:00-17:00',
      'merci_hours_admin' => '07:00-22:00',
      'merci_closed_dates' => '12-25',
      'merci_lock'    => FALSE,
    );

    $this->merciCreateConfig($settings);

    $settings = array (
      'date_default_timezone' => 'America/Los_Angeles',
      );
    $this->drupalPost('admin/config/regional/settings' , $settings, t('Save configuration'));
    $this->assertText(t("The configuration options have been saved."));

    $settings = array ( 
      'instance[widget][settings][input_format]' => 'Y-m-d H:i:s',
    );
    $this->drupalPost('admin/structure/types/manage/merci-reservation/fields/field_merci_date', $settings, t('Save settings'));
    $this->assertText(t("Saved Reservation configuration"));
  }


  function merciCreateContentType($settings,$merci_type,$merci_settings=NULL) {
    // Create resource content type
    // Disable the rating for this content type: 0 for Disabled, 1 for Enabled.
    if (node_type_get_type($settings['type'])) {
      return $settings['type'];
    }
    $content_type = $this->drupalCreateContentType($settings);
    $this->verbose('settings ' . var_export($content_type, TRUE));
    $type = $content_type->type;
    $settings = array(
        'merci_type_setting' => $merci_type,
        'merci_max_hours_per_reservation' => 5
    );
    if($merci_settings) {
      $settings = $settings + $merci_settings;
    }
    $this->drupalPost('admin/structure/types/manage/' . $type, $settings, t('Save content type'));
    $this->assertResponse(200);
    $this->assertRaw(' has been updated.', t('Settings modified successfully for content type.'));
    return $type;
  }

  function merciCreateNode($type,$settings,$pass=TRUE) {
    $this->verbose('Creating node: ' . var_export($settings, TRUE));
    $this->drupalPost('node/add/' . $type, $settings, t('Save'));
    if (array_key_exists('title', $settings)) {
      $node = entity_load('node',FALSE,array('title' => $settings['title']));
      //$this->verbose('Node created: ' . var_export($node, TRUE));
      return array_shift($node);
    }
  }

  function merciUpdateNode($nid,$settings,$pass=TRUE) {
    $this->drupalPost("node/$nid/edit", $settings, t('Save'));
    $node = node_load($nid);
    return $node;
  }

  function merciCreateConfig($settings) {
    $this->drupalPost('admin/config/system/merci' , $settings, t('Save configuration'));
    $this->assertText(t("The configuration options have been saved."));
  }

  function merciCreateItem($merci_type, $type = NULL, $merci_settings = array()) {

    $type = $type ? $type : $merci_type;
    $settings = array (
        'type'  => $type,
        );
    $type = $this->merciCreateContentType($settings, $merci_type, $merci_settings);
    // Create resource item
    $edit = array(
      'title' => $this->randomName()
    );

    $item = $this->merciCreateNode($type, $edit);
    $this->assertText(t("@title has been created", array('@title' => $edit['title'])));
    return $item;
  }
}

