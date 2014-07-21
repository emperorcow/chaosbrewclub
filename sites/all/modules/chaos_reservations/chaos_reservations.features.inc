<?php
/**
 * @file
 * chaos_reservations.features.inc
 */

/**
 * Implements hook_views_api().
 */
function chaos_reservations_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function chaos_reservations_node_info() {
  $items = array(
    'brewhouse_reservation' => array(
      'name' => t('Brewhouse Reservation'),
      'base' => 'node_content',
      'description' => t('Request for time in the brewhouse'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
