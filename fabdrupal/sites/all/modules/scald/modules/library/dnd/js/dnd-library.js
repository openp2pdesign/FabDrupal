/**
 * Drag and Drop Library For Drupal
 *
 * This builds on the DnD jQuery plugin written to provide drag and drop media
 * handling to Rich Text Editors to consume, display, and attach behavior to
 * a "media library" provided via JSON and implemented for Drupal running
 * the Wysiwyg plugin.
 */

(function($) {
/**
 * Initialize our namespace.
 */
Drupal.dnd = {
  Atoms: {
  },

  // Setting for the qTip v2 library
  qTipSettings: {
    position: {
      my: 'right center',
      at: 'left center'
    },
    hide: {
      fixed: true,
      delay: 200
    },
    show: {
      solo: true
    },
    style: {
      classes: 'ui-tooltip-scald-dnd'
    }
  },

  // Additional settings for the deprecated qTip v1
  qTip1Settings: {
    position: {
      corner: {
        target: 'leftMiddle',
        tooltip: 'rightMiddle'
      }
    },
    style: {
      width: 550,
      classes: {tooltip: 'ui-tooltip-scald-dnd'}
    }
  },

  /**
   * Fetch atoms that are not present.
   *
   * @param context
   * @param atom_ids
   *   Integer or an array of atom_id.
   * @param callback (optional)
   *   Callback when all required atoms are available.
   */
  fetchAtom: function(context, atom_ids, callback) {
    // Convert to array
    atom_ids = [].concat(atom_ids);

    for (var i= 0, len=atom_ids.length; i<len; i++) {
      // Remove atom from the list if it is already available.
      if ((atom_ids[i] in Drupal.dnd.Atoms) && (context in Drupal.dnd.Atoms[atom_ids[i]].contexts)) {
        delete atom_ids[i];
      }
    }

    // Remove undefined elements.
    atom_ids = atom_ids.filter(Number);

    if (atom_ids.length) {
      $.getJSON(Drupal.settings.basePath + 'atom/fetch/' + context + '/' + atom_ids.join(), function(data) {
        for (atom_id in data) {
          Drupal.dnd.Atoms[atom_id] = Drupal.dnd.Atoms[atom_id] || {sid: atom_id, contexts: {}};
          Drupal.dnd.Atoms[atom_id].contexts = $.extend(Drupal.dnd.Atoms[atom_id].contexts, data[atom_id]);
        }
        if (callback) {
          callback();
        }
      });
    }
    else {
      if (callback) {
        callback();
      }
    }
  },

  // Refresh the library.
  refreshLibraries: function() {
    $('.dnd-library-wrapper .view-filters input[type=submit]').click();
  },

  // Convert HTML to SAS. We consider there is no nested elements.
  html2sas: function(text) {
    text = text.replace(/<!-- (scald=(\d+):([a-z_]+)) -->[\r\n\s\S]*?<!-- END scald=\2 -->/g, '[$1]');
    return text;
  },

  // Convert SAS to HTML.
  // @todo Known bug: we have to fetch atoms that are not present in the current
  // scope of Drupal.dnd.Atoms
  sas2html: function(text) {
    for (var i in Drupal.dnd.Atoms) {
      atom = Drupal.dnd.Atoms[i];
      if (text.indexOf(atom.sas) > -1) {
        text = text.replace(atom.sas, atom.editor);
      }
    }
    return text;
  }
}

/**
 *  Extend jQuery a bit
 *
 *  We add a selector to look for "empty" elements (empty elements in TinyMCE
 *  often have non-breaking spaces and <br /> tags).  An exception is required
 *  to make this work in IE.
 */
// Custom selectors
$.extend($.expr[":"], {
  'dnd_empty' : function(a, i, m) {
    return !$(a).filter(function(i) {
      return !$(this).is('br');
    }).length && !$.trim(a.textContent || a.innerText||$(a).text() || "");
  }
});

/**
 * Default atom theme function
 */
Drupal.theme.prototype.scaldEmbed = function(atom, context) {
  context = context ? context : Drupal.settings.dnd.contextDefault;
  var output = '<div class="dnd-atom-wrapper"><div class="dnd-drop-wrapper">' + atom.contexts[context] + '</div>';
  if (atom.meta.legend) {
    output += '<div class="dnd-legend-wrapper">' + atom.meta.legend + '</div>';
  }
  output += '</div>';

  // Trick: if not the image might come out and go into the current hovered
  // paragraph.
  output = '<p>&nbsp;</p>' + output;
  return output;
}

/**
 * Initialize and load drag and drop library and pass off rendering and
 * behavior attachment.
 */
Drupal.behaviors.dndLibrary = {
attach: function(context, settings) {
  if (Drupal.settings.dnd.suppress) {
    return;
  }

  Drupal.ajax.prototype.commands.dnd_refresh = Drupal.dnd.refreshLibraries;

  $('body').once('dnd', function() {
    var wrapper = $('<div class="dnd-library-wrapper"></div>').appendTo('body');
    $editor = $("<a />");
    wrapper.library_url = Drupal.settings.dnd.url;
    $.getJSON(wrapper.library_url, function(data) {
      Drupal.behaviors.dndLibrary.renderLibrary.call(wrapper, data, $editor);
    });
  });
},

renderLibrary: function(data, editor) {
  $this = $(this);

  // Save the current status
  var dndStatus = {
    search: $this.find('.scald-menu').hasClass('search-on')
    ,library: $this.find('.dnd-library-wrapper').hasClass('library-on')
  };

  $this.html(data.menu + data.anchor + data.library);

  // Rearrange some element for better logic and easier theming.
  // @todo We'd better do it on server side.
  $this.find('.scald-menu')
    .prepend($this.find('.summary'))
    .append($this.find('.view-filters').addClass('filters'));
  if (dndStatus.search) {
    $this.find('.scald-menu').addClass('search-on');
    $this.find('.dnd-library-wrapper').addClass('library-on');
  }
  $this.find('.summary .toggle').click(function() {
    // We toggle class only when animation finishes to avoid flash back.
    $('.scald-menu').animate({left: $('.scald-menu').hasClass('search-on') ? '-42px' : '-256px'}, function() {
      $(this).toggleClass('search-on');
    });
    // When display search, we certainly want to display the library, too.
    if (!$('.scald-menu').hasClass('search-on') && !$('.dnd-library-wrapper').hasClass('library-on')) {
      $('.scald-anchor').click();
    }
  });
  $this.find('.scald-anchor').click(function() {
    // We toggle class only when animation finishes to avoid flash back.
    $('.dnd-library-wrapper').animate({right: $('.dnd-library-wrapper').hasClass('library-on') ? '-276px' : '0'}, function() {
      $('.dnd-library-wrapper').toggleClass('library-on');
    });
  });

  for (atom_id in data.atoms) {
    // Store the atom data in our object
    Drupal.dnd.Atoms[atom_id] = Drupal.dnd.Atoms[atom_id] || {sid: atom_id};
    Drupal.dnd.Atoms[atom_id].contexts = Drupal.dnd.Atoms[atom_id].contexts || {};
    $.extend(true, Drupal.dnd.Atoms[atom_id], data.atoms[atom_id]);
    Drupal.dnd.Atoms[atom_id].contexts[Drupal.settings.dnd.contextDefault] = Drupal.dnd.Atoms[atom_id].editor;

    // And add a nice preview behavior if qTip is present
    if ($.prototype.qtip) {
      var settings = $.extend(Drupal.dnd.qTipSettings, {
        content: {
          text: Drupal.dnd.Atoms[atom_id].preview
        }
      });

      // When using the deprecated qTip v1 library,
      // add some additional settings.
      try {
        $.fn.qtip.styles.defaults.width.min;
        $.extend(settings, Drupal.dnd.qTip1Settings);
      }
      catch(err) {
        // On qTip 2, everything's ok
      }

      $("#sdl-" + atom_id).qtip(settings);
    }
  }

  // Preload images in editor representations
  var cached = $.data($(editor), 'dnd_preload') || {};
  for (editor_id in Drupal.dnd.Atoms) {
    if (!cached[editor_id]) {
      $representation = $(Drupal.dnd.Atoms[editor_id].editor);
      if ($representation.is('img') && $representation.get(0).src) {
        $representation.attr('src', $representation.get(0).src);
      } else {
        $('img', $representation).each(function() {
          $(this).attr('src', this.src);
        });
      }
    }
  }
  $.data($(editor), 'dnd_preload', cached);

  // Set up drag & drop data
  $('.editor-item .drop').each(function(i) {
    $(this)
      .bind('dragstart', function(e) {
        var dt = e.originalEvent.dataTransfer, id = e.target.id, $this = $(this);
        var $img;
        if ($this.is('img')) {
          $img = $this;
        }
        else {
          $this.find('img');
        }
        var id = $img.data('atom-id');
        dt.dropEffect = 'copy';
        dt.setData('Text', Drupal.dnd.Atoms[id].sas);
        dt.setData('text/html', Drupal.theme('scaldEmbed', Drupal.dnd.Atoms[id]));
        return true;
      })
      .bind('dragend', function(e) {
        return true;
      });
  });
  // Makes pager links refresh the library instead of opening it in the browser window
  $('.pager a', $this).click(function() {
    $this.get(0).library_url = this.href;
    $.getJSON(this.href, function(data) {
      Drupal.behaviors.dndLibrary.renderLibrary.call($this.get(0), data, $(editor));
    });
    return false;
  });

  // Turns Views exposed filters' submit button into an ajaxSubmit trigger
  $('.view-filters input[type=submit]', $this).click(function(e) {
    var submit = $(this);
    settings = Drupal.settings.dnd;
    $('.view-filters form', $this).ajaxSubmit({
      'url' : settings.url,
      'dataType' : 'json',
      'success' : function(data) {
        var target = submit.parents('div.dnd-library-wrapper').get(0);
        target.library_url = this.url;
        Drupal.behaviors.dndLibrary.renderLibrary.call(target, data, $(editor));
      }
    });
    e.preventDefault();
    return false;
  });

  // Makes Views exposed filters' reset button submit the form via ajaxSubmit,
  // without data, to get all the default values back.
  $('.view-filters input[type=reset]', $this).click(function(e) {
    var reset = $(this);
    $('.view-filters form', $this).ajaxSubmit({
      'url' : Drupal.settings.dnd.url,
      'dataType' : 'json',
      'success' : function(data) {
        var target = reset.parents('div.dnd-library-wrapper').get(0);
        target.library_url = Drupal.settings.dnd.url;
        Drupal.behaviors.dndLibrary.renderLibrary.call(target, data, $(editor));
      },
      'beforeSubmit': function (data, form, options) {
        // Can't use data = [], otherwise we're creating a new array
        // instead of modifying the existing one.
        data.splice(0, data.length);
      }
    });
    e.preventDefault();
    return false;
  });

  // Deals with Views Saved Searches "Save" button
  $('#views-savedsearches-save-search-form input[type=submit]', $this).click(function() {
    var submit = $(this);
    url = submit.parents('div.dnd-library-wrapper').get(0).library_url;
    $('#views-savedsearches-save-search-form', $this).ajaxSubmit({
      'url' : url,
      'dataType' : 'json',
      'success' : function(data) {
        var target = submit.parents('div.dnd-library-wrapper').get(0);
        target.library_url = this.url;
        Drupal.behaviors.dndLibrary.renderLibrary.call(target, data, $(editor));
      }
    });
    return false;
  });

  // Deals with Views Saved Searches "Delete" button
  $('#views-savedsearches-delete-search-form input[type=submit]', $this).click(function() {
    var submit = $(this);
    $('#views-savedsearches-delete-search-form', $this).ajaxSubmit({
      'url' : settings.url,
      'dataType' : 'json',
      'success' : function(data) {
        var target = submit.parents('div.dnd-library-wrapper').get(0);
        target.library_url = this.url;
        Drupal.behaviors.dndLibrary.renderLibrary.call(target, data, $(editor));
      }
    });
    return false;
  });

  // Deals with Views Saved Searches search links
  $('#views-savedsearches-delete-search-form label a', $this).click(function() {
    $this.get(0).library_url = this.href;
    $.getJSON(this.href, function(data) {
      Drupal.behaviors.dndLibrary.renderLibrary.call($this.get(0), data, $(editor));
    });
    return false;
  });

  // Attach all the behaviors to our new HTML fragment
  Drupal.attachBehaviors($this);
},

// Do garbage collection on detach
detach: function() {
}
}

}) (jQuery);
