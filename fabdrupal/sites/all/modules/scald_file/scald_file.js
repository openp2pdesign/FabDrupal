(function ($) {
  Drupal.behaviors.scaldFile= {
    attach: function (context, settings) {
      if (typeof CKEDITOR !== 'undefined') {
        CKEDITOR.on('instanceReady', function(ev) {
          for(var i in CKEDITOR.instances) {
            CKEDITOR.instances[i].document.appendStyleSheet(Drupal.settings.basePath + settings.scaldFile.path);
          }
        });
      }
    }
  };
})(jQuery);