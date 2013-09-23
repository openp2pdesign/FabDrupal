<?php

/**
 * @file
 * merci views handlers 
 */


/**
 * Views assumes dates are always Unix timestamps, so convert our DATETIME-formatted columns.
 *
 */
class views_handler_field_datetime extends views_handler_field_date {
  function query() {
    $this->ensure_my_table();
    $this->field_alias = $this->query->add_field(NULL, 'UNIX_TIMESTAMP(' . $this->table_alias . '.' . $this->field . ')', $this->table_alias . '_' . $this->field);
  }
}

