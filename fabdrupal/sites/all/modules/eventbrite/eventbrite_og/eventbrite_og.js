Drupal.behaviors.eventBrite = function (context) {
  $('input.eventbrite_og-enabled').click(function() {
    switch ($(this).attr('value')) {
      case '1':
        $('#edit-eventbrite-og-user-key-wrapper').show();
        $('#edit-eventbrite-subuser-email-wrapper').hide();
        break;
      case '2':
        $('#edit-eventbrite-og-user-key-wrapper').hide();
        $('#edit-eventbrite-subuser-email-wrapper').show();
        break;
      default:
        $('#edit-eventbrite-og-user-key-wrapper').hide();
        $('#edit-eventbrite-subuser-email-wrapper').hide();
    }
  });

  switch($('input:checked.eventbrite_og-enabled').val()) {
    case '1':
      $('#edit-eventbrite-subuser-email-wrapper').hide();
      break;
    case '2':
      $('#edit-eventbrite-og-user-key-wrapper').hide();
      break;
    default:
      $('#edit-eventbrite-og-user-key-wrapper').hide();
      $('#edit-eventbrite-subuser-email-wrapper').hide();
  }
};
