<?php  
/**
 * @file
 * Override of theme_preprocess_...
 */

/**
 * Override or insert variables into the node template.
 *
 * @param $vars
 *   An array of variables to pass to the theme template.
 */
function tb_hadelis_preprocess_node(&$vars) {
  $vars['last_changed_day'] = date('d', $vars['changed']);
  $vars['last_changed_month'] = date('M', $vars['changed']);
}

function tb_hadelis_preprocess_page(&$vars) {
}

function tb_hadelis_preprocess_block(&$vars) {
  if(($vars['block']->module == 'user' && $vars['block']->delta == 'login') ||
    ($vars['block']->module == 'system' && $vars['block']->delta == 'main-menu')) {
    $subject = $vars['block']->subject;
  	$parts = explode(" ", $subject);
  	if(count($parts) == 2) {
  	  $vars['block']->subject = $parts[0] . ' <span class="grey-title">' . $parts[1] . '</span>';
  	} 
  }
}
