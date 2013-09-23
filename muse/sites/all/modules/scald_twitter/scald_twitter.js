(function($) {

// I'm not sure if Twitter embedded widget work with AJAX content, so I'm just
// using domready.
$(function() {
  var notfound = true;
  $('.node').each(function() {
    if ($(this).find('blockquote.twitter-tweet').length > 0) {
      if ($(this).hasClass('node-full')) {
        notfound = false;
      }
      else {
        // Use simple form for teaser
        $(this).find('blockquote.twitter-tweet').removeClass('twitter-tweet');
      }
    }
  });
  if (!notfound) {
    $.getScript('//platform.twitter.com/widgets.js');
  }
});

})(jQuery);
