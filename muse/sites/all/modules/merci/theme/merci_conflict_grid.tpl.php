<?php

?>

<div><?php print  t("The dates and times for %name conflict with one or more existing reservations", array('%name' => $title)); ?> </div>

<div class="merci-availability-key">
<span class="available"></span> = available 
<span class="unavailable"></span> = unavailable
</div>

<?php foreach ($reservations_by_date as $date => $items): ?>

<table class="merci-availability-schedule">

  <thead><tr>

  <th><?php print  date('m/d/Y',strtotime($date)) ?></th>

    <?php foreach ($pretty_hours[$date] as $time): ?>

      <th colspan="4"><?php print  $time ?> </th>

    <?php endforeach; ?>

    </tr></thead>

    <tbody>

    <?php foreach ($items as $times): ?>

      <tr><th> <?php print htmlspecialchars($title); ?> </th>
        <?php foreach ($times as $time => $available): ?>

         <td class="<?php print $available['class'] . ' '; print strstr($time, ':45') ? 'hourborder' : ''; ?>">
            <?php print $available['class'] == 'available' ? 0 : l('X', 'node/' . $available['data'], array('attributes' => array('class' => 'unavailable'))); ?>
        </td>

        <?php endforeach; ?>

      </tr>

      <?php endforeach; ?>

    </tbody>
</table>

<?php endforeach; ?>


