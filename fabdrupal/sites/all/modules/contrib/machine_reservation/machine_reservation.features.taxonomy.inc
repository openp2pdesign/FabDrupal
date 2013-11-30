<?php
/**
 * @file
 * machine_reservation.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function machine_reservation_taxonomy_default_vocabularies() {
  return array(
    'merci_equipment_group' => array(
      'name' => 'MERCI Equipment Grouping',
      'machine_name' => 'merci_equipment_group',
      'description' => 'Taxonomy for grouping buckets and resources',
      'hierarchy' => 0,
      'module' => 'merci',
      'weight' => -10,
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
    ),
  );
}
