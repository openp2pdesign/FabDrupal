<?php 
/*
 * Available vars:
 * - $description: Containing the description of the FlickrGallery module you provided at the settings page
 * - $albums: Array that contains the image and titles with links
 */
?>
<div id='flickrgallery'>
  <div id='flickrgallery-description'><?php print $description; ?></div>
  <div id='flickrgallery-albums'>
    <?php foreach ($albums as $key => $album) : ?>
      <div class='flickr-wrap'>
        <?php print $album['image_link']; ?>
        <?php print $album['title_link'];  ?>
        <div class='flickr-total'><?php print t('Total') . ": " . $album['total']; ?></div>
      </div>
    <?php endforeach; ?>
  </div>
</div>