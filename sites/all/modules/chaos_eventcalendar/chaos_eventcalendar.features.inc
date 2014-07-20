<?php
/**
 * @file
 * chaos_eventcalendar.features.inc
 */

/**
 * Implements hook_views_api().
 */
function chaos_eventcalendar_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function chaos_eventcalendar_node_info() {
  $items = array(
    'event' => array(
      'name' => t('Event'),
      'base' => 'node_content',
      'description' => t('Use event for all general group based gatherings.'),
      'has_title' => '1',
      'title_label' => t('Name'),
      'help' => '',
    ),
  );
  return $items;
}
