jQuery(window).load(function(){
  window.setTimeout(nucleus_set_equal_height, 100);
  nucleus_put_label_to_input("search_block_form", "Enter your keyword");
});

function nucleus_put_label_to_input(name, text) {
  jQuery('input[name="' + name + '"]').val(Drupal.t(text));
  jQuery('input[name="' + name + '"]').focus(function(){
    if(this.value == Drupal.t(text)) {
      this.value='';
    }
  }).blur(function(){
    if(this.value == '') {
      this.value=Drupal.t(text);
    }
  });	  
}
function nucleus_set_equal_height() {
//	jQuery('key1, key2, key3, ...').equalHeightColumns();
	jQuery('#mass-bottom-wrapper .views-col').matchHeights();
}