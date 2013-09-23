<?php

/**
 * @file
 * Class definition of FeedsNodeProcessor.
 */

/**
 * Creates nodes from feed items.
 */
class MerciTypeProcessor extends FeedsProcessor {

  /**
   * Entity type this processor operates on.
   */
  public function entityType() {
    return 'merci_type';
  }

  /**
   * Implements parent::entityInfo().
   */
  protected function entityInfo() {
    $info = parent::entityInfo();
    $info['label'] = t('MERCI type');
    $info['label plural'] = t('MERCI types');
    return $info;
  }
  /**
   * Create a new entity.
   *
   * @param $source
   *   The feeds source that spawns this entity.
   *
   * @return
   *   A new entity object.
   */
  protected function newEntity(FeedsSource $source) {
    return new stdClass();
  }

  /**
   * Load an existing entity.
   *
   * @param $source
   *   The feeds source that spawns this entity.
   * @param $entity_id
   *   The unique id of the entity that should be loaded.
   *
   * @return
   *   A new entity object.
   */
  protected function entityLoad(FeedsSource $source, $entity_id){
  }

  /**
   * Save an entity.
   *
   * @param $entity
   *   Entity to b saved.
   */
  protected function entitySave($entity) {
    $form_state['values'] = (array) $entity;
    $form_state['values']['orig_type'] = $form_state['values']['type'];
    $form_state['values']['base'] = 'node_content';
    $form_state['values']['op'] = t('Save content type');
    module_load_include('inc', 'node', 'content_types');
    drupal_form_submit('node_type_form', $form_state);
  }

  /**
   * Delete a series of entities.
   *
   * @param $entity_ids
   *   Array of unique identity ids to be deleted.
   */
  protected function entityDeleteMultiple($entity_ids){
  }

  /**
   * Return available mapping targets.
   */
  public function getMappingTargets() {

    $targets = array(
      'type' => array(
        'name' => t('Content type'),
        'description' => t('The content type.'),
      ),
      'name' => array(
        'name' => t('Content type name'),
        'description' => t('The content type name.'),
      ),
      'description' => array(
        'name' => t('Content type description'),
        'description' => t('The content type description.'),
      ),
      'merci_type_setting' => array(
        'name' => t('MERCI type setting'),
        'description' => "The MERCI type for the selected content type.",
      ),
      'merci_max_hours_per_reservation' => array(
        'name'        => t('MERCI max hours per reservation'),
        'description' => "The maximum hours that the resource can be reserved for.",
      ),
      'merci_allow_overnight' => array(
        'name'        => t('MERCI allow overnight reservation'),
        'description' => "TRUE if the resource can be kept overnight.",
      ),
      'merci_allow_weekends' => array(
        'name'        => t('MERCI allow weekend reservation'),
        'description' => "TRUE if the resource can be kept over weekends.",
      ),
      'merci_late_fee_per_hour' => array(
        'name' => t('MERCI late fee per hour'),
        'description' => "Per hour fee if the resource is returned late.",
      ),
      'merci_rate_per_hour' => array(
        'name' => t('MERCI rate per hour'),
        'description' => "Per hour fee for use of the resource.",
      ),
      'merci_fee_free_hours' => array(
        'name' => t('MERCI fee free hours'),
        'description' => "Number of hours the item can be used before fees are charged.",
      ),
      'merci_active_status' => array(
        'name'        => t('MERCI active status'),
        'description' => "The status of the resource.",
      ),
      'merci_spare_items' => array(
        'name'        => t('MERCI spare items'),
        'description' => "Number of spare items to leave unreserved for the resource.",
      ),
      'merci_min_cancel_hours' => array(
        'name' => t('MERCI min cancel hours'),
        'description' => "Minimum number of hours a user can cancel a reservation for the item.",
      ),
      'merci_autocheckout' => array(
        'name' => t('MERCI autocheckout'),
        'description' => "TRUE if the resource is automatically checked out when Reservation starts.",
      ),
      'merci_autocheckin' => array(
        'name' => t('MERCI autocheckin'),
        'description' => "TRUE if the resource is automatically checked in when Reservation starts.",
      ),
      'merci_selfcheckout' => array(
        'name' => t('MERCI selfcheckout'),
        'description' => "TRUE if the resource is managed by selfcheckout.",
      ),
      'merci_grouping' => array(
        'name' => t('MERCI grouping'),
        'description' => "tid of MERCI Equiment Grouping vocabulary",
      ),
      'merci_auto_assign_bucket_item' => array(
        'name' => t('MERCI auto assign'),
        'description' => "TRUE if the bucket item is to be assigned automatically.",
      ),
    );

    return $targets;
  }

}


