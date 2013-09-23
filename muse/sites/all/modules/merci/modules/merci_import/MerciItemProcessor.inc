<?php

/**
 * @file
 * Class definition of FeedsNodeProcessor.
 */

/**
 * Creates nodes from feed items.
 */
class MerciItemProcessor extends FeedsNodeProcessor {

  /**
   * Override parent::configForm().
   */
  public function configForm(&$form_state) {
    $form = parent::configForm($form_state);
    $form['content_type']['#description'] .= t('  Content type can be overridden by mapping.');
    return $form;
  }

  /**
   * Creates a new node in memory and returns it.
   */
  protected function newEntity(FeedsSource $source) {
    $node = parent::newEntity($source);
    $node->merci_sub_type = MERCI_SUB_TYPE_ITEM; 
    return $node;
  }
  /**
   * Return available mapping targets.
   */
  public function getMappingTargets() {
    $targets = parent::getMappingTargets();

    $targets += array(
      'type' => array(
        'name' => t('Content type'),
        'description' => t('The content type of the node.'),
      ),
      'merci_default_availability' => array(
        'name' => t('MERCI default availability'),
        'description' => 'Default availability of the item .',
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
    );

    return $targets;
  }

}

