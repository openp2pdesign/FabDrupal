(function($) {
CKEDITOR.dialog.add('atomProperties', function(editor) {
  var lang = editor.lang.dnd, element, atom;

  return {
    title: lang.atom_properties,
    minWidth: 420,
    minHeight: 360,
    onShow: function() {
      if (!Drupal.dnd.atomCurrent) {
        this.hide();
        // If the library is hidden, show it
        if ($('.dnd-library-wrapper').length && !$('.dnd-library-wrapper').hasClass('library-on')) {
          $('.dnd-library-wrapper .scald-anchor').click();
        }
        else {
          alert(lang.atom_none);
        }
        return;
      }
      var elm, data, sid, context, options, legend;
      elm = $(Drupal.dnd.atomCurrent.$);
      // Get the data directly from the comment markup.
      data = Drupal.dnd.atomCurrent.getChild(0).getHtml()
        .replace(/<!--\{cke_protected\}\{C\}([\s\S]+?)-->.*/, function(match, data) {
          return decodeURIComponent(data);
        })
        .replace(/^<!--\s+scald=(.+?)\s+-->[\s\S]*$/, '$1');
      legend = Drupal.dnd.atomCurrent.getChild(1);
      legend = legend ? legend.getHtml().replace( /<!--\{cke_protected\}\{C\}([\s\S]+?)-->/g, function(match, data) {
        return decodeURIComponent(data);
      }).trim() : false;

      sid = data.split(':', 1)[0];
      context = data.substr(sid.length + 1).split(' ', 1)[0];
      options = (data.length > sid.length + context.length + 2) ? JSON.parse(data.substr(sid.length + context.length + 2)) : {link: ''};

      atom = {
        sid: sid,
        context: context,
        options: options,
        legend: legend,
        align: elm.hasClass('atom-align-left') ? 'left' : elm.hasClass('atom-align-right') ? 'right' : elm.hasClass('atom-align-center') ? 'center' : 'none'
      };
      var me = this;
      Drupal.dnd.fetchAtom(context, sid, function() {
        var type = Drupal.dnd.Atoms[atom.sid].meta.type;
        var cmbContext = me.getContentElement('info', 'cmbContext');
        cmbContext.clear();
        for (context in Drupal.settings.dnd.contexts[type]) {
          cmbContext.add(Drupal.settings.dnd.contexts[type][context], context);
        }
        me.setupContent(atom);
      });
    },
    onOk: function() {
      Drupal.dnd.Atoms[atom.sid] = Drupal.dnd.Atoms[atom.sid] || {sid: atom.sid, contexts:{}, meta: {}};
      Drupal.dnd.Atoms[atom.sid].meta.legend = this.getValueOf('info', 'txtLegend');
      Drupal.dnd.Atoms[atom.sid].meta.align = this.getValueOf('info', 'cmbAlign');
      var context = this.getValueOf('info', 'cmbContext');
      atom.options.link = this.getValueOf('info', 'txtLink');
      Drupal.dnd.fetchAtom(context, atom.sid, function() {
        var html = Drupal.theme('scaldEmbed', Drupal.dnd.Atoms[atom.sid], context, atom.options);
        // Remove the first 13 characters '<p>&nbsp;</p>'
        CKEDITOR.dom.element.createFromHtml(html.substr(13)).replace(Drupal.dnd.atomCurrent);
      });
    },
    contents: [
      {
        id: 'info',
        label: '',
        title: '',
        expand: true,
        padding: 0,
        elements: [
          {
            id: 'txtLegend',
            type: 'textarea',
            rows: 5,
            label: 'Legend',
            setup: function(atom) {
              this.setValue(atom.legend);
            }
          },
          {
            id: 'cmbContext',
            type: 'select',
            label: 'Context',
            items: [],
            setup: function(atom) {
              this.setValue(atom.context);
            }
          },
          {
            id: 'cmbAlign',
            type: 'select',
            label: 'Alignment',
            items: [['None', 'none'], ['Left', 'left'], ['Right', 'right'], ['Center', 'center']],
            setup: function(atom) {
              this.setValue(atom.align);
            }
          },
          // @todo Expose a hook to remove this hardcoded option.
          {
            id: 'txtLink',
            type: 'text',
            label: 'Link',
            setup: function(atom) {
              if (Drupal.dnd.Atoms[atom.sid].meta.type === 'image') {
                this.setValue(atom.options.link);
                this.enable();
              }
              else {
                this.setValue(editor.lang.dnd.link_image_only);
                this.disable();
              }
            }
          }
        ]
      }
    ]
  };
});
})(jQuery);
