<?php
// $Id$

/**
 * @file
 * Contains the functions used to theme the outputs of this module.
 *
 * Currently this modules implements two custom form elements. The first
 * is a slider that is used on the configuration page to set the thresholds.
 *
 * The second element is used to display the results of the checks after
 * submitting the node_form.
 */


/**
 * Defines the slider form element and its default values
 */
function seo_checker_elements() {
  $type['slider'] = array(
    '#input' => TRUE,
    '#steps' => 100,
    '#size' => 3,
    '#theme' => 'slider',
  );
  $type['seo_check_results'] = array(
    '#results' => array(),
    '#theme' => 'seo_check_results',
  );
  return $type;
}

/**
 * Implementation of hook_theme().
 */
function seo_checker_theme($existing, $type, $theme, $path) {
  return array(
    'slider' => array(
       'template' => 'slider-atleast',
       'path' => "$path/theme",
       'arguments' => array('element' => NULL),
    ),
    'seo_check_results' => array(
      'arguments' => array('element' => NULL),
    )
  );
}

/**
 * Implementation of template_preprocess().
 */
function template_preprocess_slider(&$args) {
  if (module_exists('jquery_ui')) {
    switch ($args['element']['#slider_type']) {
      case 'at_least':
        $args['template_files'][] = 'slider-atleast';
        break;
      case 'range':
        $args['template_files'][] = 'slider-range';
        break;
    }
  } else {
    $args['template_files'][] = 'slider-nojquery';
  }
}

/**
 * By default the check results are themed as a normal form item whose
 * value contains the check results, rendered as a table.
 */
function theme_seo_check_results($element) {
  $output = '<b>'.t('SEO Check Results').':</b>';
  $output .= theme(
    'table',
    array(t('Rule'), t('Message'), t('Achieved'), t('Required'), t('Passed')),
    $element['#results'],
    array()
  );
  return $output;
}
