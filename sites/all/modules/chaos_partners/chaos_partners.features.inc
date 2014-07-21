<?php
/**
 * @file
 * chaos_partners.features.inc
 */

/**
 * Implements hook_views_api().
 */
function chaos_partners_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function chaos_partners_node_info() {
  $items = array(
    'sponsor' => array(
      'name' => t('Partner'),
      'base' => 'node_content',
      'description' => t('Local organizations, pubs, shops, and other establishments that are offering CHAOS members a discount or are sponsoring the club. '),
      'has_title' => '1',
      'title_label' => t('Name'),
      'help' => '',
    ),
  );
  return $items;
}
