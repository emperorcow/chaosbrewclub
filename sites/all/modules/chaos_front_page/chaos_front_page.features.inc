<?php
/**
 * @file
 * chaos_front_page.features.inc
 */

/**
 * Implements hook_views_api().
 */
function chaos_front_page_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function chaos_front_page_node_info() {
  $items = array(
    'brewhouse_image' => array(
      'name' => t('Brewhouse Image'),
      'base' => 'node_content',
      'description' => t('Images for the "About Brewhouse" page'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
