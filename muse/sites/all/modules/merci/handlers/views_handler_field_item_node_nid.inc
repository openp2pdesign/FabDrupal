<?php

/**
 * @file
 * MERCI - Managed Equipment Reservation Checkout and Inventory
 */

/**
 * Field handler for terms.
 */
class views_handler_field_item_node_nid extends views_handler_field_prerender_list {
  function init(&$view, &$options) {
    parent::init($view, $options);
    if ($view->base_table == 'node_revisions') {
      $this->additional_fields['vid'] = array(
        'table' => 'node_revisions',
        'field' => 'vid',
      );
    }
    else {
      $this->additional_fields['vid'] = array(
        'table' => 'node',
        'field' => 'vid',
      );
    }
  }

  /**
   * Add this term to the query
   */
  function query() {
    $this->add_additional_fields();
  }

  function pre_render(&$values) {
    $this->field_alias = $this->aliases['vid'];
    $vids = array();
    foreach ($values as $result) {
      if (!empty($result->{$this->aliases['vid']})) {
        $vids[] = $result->{$this->aliases['vid']};
      }
    }

    if ($vids) {

      // TODO Please convert this statement to the D7 database API syntax.
      $result = db_query("SELECT m.vid as node_vid, m.did, m.merci_item_status, pn.nid AS pnid, pn.title AS ptitle, tn.nid AS tnid, tn.title AS ttitle, nt.type, nt.name FROM {merci_reservation_detail} m INNER JOIN {node} pn ON m.merci_placeholder_nid = pn.nid INNER JOIN {node_type} nt ON pn.type = nt.type LEFT JOIN {node} tn ON m.merci_item_nid = tn.nid WHERE m.vid IN (" . implode(', ', $vids) . ")");

      foreach($result as $item) {
        $this->items[$item->node_vid][$item->pnid]['name'] = check_plain($item->ttitle ? $item->ttitle : $item->name);
      }
    }
  }

  function render_item($count, $item) {
    return $item['name'];
  }

}

