<?php
  print theme('item_list',
    array(
      'items' => $providers,
      'title' => $element['#title'],
      'type' => 'ul',
      'attributes' => array('class' => array('hybridauth-widget')),
    )
  );
?>