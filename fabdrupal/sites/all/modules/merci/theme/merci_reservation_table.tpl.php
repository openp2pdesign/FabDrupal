<?php


foreach ($reservations as $date => $times) {

  $date_timestamp = strtotime($date);
  $hours_date = $hours[date('w', $date_timestamp)];

  if (isset($hours_date['open'])) {

    ?>
    <table class="merci-availability-schedule">
      <thead>
        <tr>
          <th><?php print date('m/d/Y', $date_timestamp); ?></th>
          <?php
    $time = $hours_date['open'];

    while ($time < $hours_date['close']) {

      ?>
            <th colspan="4"><?php print date('g:i a', strtotime($time)); ?></th>
            <?php
      $time = date('H:i', strtotime($time .' +1 hour'));
    }
    // while

    ?>
        </tr>
      </thead>
      <tbody>
      <?php
    for ($i = 1; $i <= $count; $i++) {

      ?>
        <tr>
          <th><?php print ($count > 1) ? t($title) .' '. $i .'/'. $count : t($title); ?></th>
          <?php
      $time = $hours_date['open'];

      while ($time < $hours_date['close']) {

        $class = ($times[$time .':00'] >= $i) ? 'unavailable' : 'available';

        ?>
            <td class="<?php print $class; ?>"></td>
            <?php
        $time = date('H:i', strtotime($time .' +15 minutes'));
      }
      // while

      ?>
        </tr>
        <?php
    }
    // for

    ?>
      </tbody>
    </table>
    <?php
  }
  // if
}
// foreach

