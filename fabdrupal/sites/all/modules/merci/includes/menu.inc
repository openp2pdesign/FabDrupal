<?php

/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function merci_taxonomy_json($node, $vid, $did) {

  merci_taxonomy_node_delete_vocabulary($node, $vid);

  $tids = $_POST['merci_reservation_items']
       ? $_POST['merci_reservation_items'][$did]['accessories']['choices'][$vid]     : $_POST[$did]['accessories']['choices'][$vid];

  merci_taxonomy_node_save_terms($node, $tids);

  merci_ahah_output('', TRUE);
}



