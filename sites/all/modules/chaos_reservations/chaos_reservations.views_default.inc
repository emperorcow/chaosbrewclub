<?php
/**
 * @file
 * chaos_reservations.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function chaos_reservations_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'brewhouse_reservations';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Brewhouse Reservations';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Brewhouse Reservations';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'views_content_cache';
  $handler->display->display_options['cache']['results_min_lifespan'] = '-1';
  $handler->display->display_options['cache']['results_max_lifespan'] = '518400';
  $handler->display->display_options['cache']['output_min_lifespan'] = '-1';
  $handler->display->display_options['cache']['output_max_lifespan'] = '518400';
  $handler->display->display_options['cache']['keys'] = array(
    'comment' => array(
      'changed' => 0,
    ),
    'node' => array(
      'brewhouse_reservation' => 'brewhouse_reservation',
      'alchemist_application' => 0,
      'article' => 0,
      'page' => 0,
      'brewhouse_image' => 0,
      'door_code' => 0,
      'event' => 0,
      'forum' => 0,
      'front_page_image' => 0,
      'media_gallery' => 0,
      'newsletter_callout' => 0,
      'sponsor' => 0,
      'poll' => 0,
      'project' => 0,
      'recipe' => 0,
      'simplenews' => 0,
    ),
    'node_only' => array(
      'node_changed' => 0,
    ),
  );
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'fullcalendar';
  $handler->display->display_options['style_options']['weekMode'] = 'variable';
  $handler->display->display_options['style_options']['timeformat'] = 'h:mmt';
  $handler->display->display_options['style_options']['fields']['title_field'] = 'php';
  $handler->display->display_options['style_options']['fields']['title'] = TRUE;
  /* Header: Global: Unfiltered text */
  $handler->display->display_options['header']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['header']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['header']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['header']['area_text_custom']['label'] = 'Add New Link';
  $handler->display->display_options['header']['area_text_custom']['empty'] = TRUE;
  $handler->display->display_options['header']['area_text_custom']['content'] = '<a class=\'addnew\' href=\'/brewhouse/reservation/new\'>Add New Reservation</a>';
  /* Footer: Global: Text area */
  $handler->display->display_options['footer']['area']['id'] = 'area';
  $handler->display->display_options['footer']['area']['table'] = 'views';
  $handler->display->display_options['footer']['area']['field'] = 'area';
  $handler->display->display_options['footer']['area']['label'] = 'Legend';
  $handler->display->display_options['footer']['area']['empty'] = TRUE;
  $handler->display->display_options['footer']['area']['content'] = '<div id="legend">
 <ul>
  <li><span style="color:#fd8b12">&#9632;</span> Alchemist</li>
  <li><span style="color: #cc3338">&#9632;</span> Brewer</li>
  <li><span style="color: #33c8cc">&#9632;</span> Brewer (Introductory)</li>
  <li><span style="color: #3380cc">&#9632;</span> Apprentice</li>
  <li><span style="color: #339999">&#9632;</span> Trial</li>
  <li><span style="color: #00cc00">&#9632;</span> Bottling</li>
 </ul>
</div>
<div style="clear: both"> </div>
';
  $handler->display->display_options['footer']['area']['format'] = 'full_html';
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['required'] = TRUE;
  /* Field: Content: Date */
  $handler->display->display_options['fields']['field_date']['id'] = 'field_date';
  $handler->display->display_options['fields']['field_date']['table'] = 'field_data_field_date';
  $handler->display->display_options['fields']['field_date']['field'] = 'field_date';
  $handler->display->display_options['fields']['field_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_date']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_repeat_rule' => 'show',
  );
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['alter']['text'] = '[name] [field_brew_bay]';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_user'] = FALSE;
  /* Field: Content: Brew Bay */
  $handler->display->display_options['fields']['field_brew_bay']['id'] = 'field_brew_bay';
  $handler->display->display_options['fields']['field_brew_bay']['table'] = 'field_data_field_brew_bay';
  $handler->display->display_options['fields']['field_brew_bay']['field'] = 'field_brew_bay';
  $handler->display->display_options['fields']['field_brew_bay']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_brew_bay']['element_label_colon'] = FALSE;
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_output'] = '<?php if($data->field_field_brew_bay[0][\'raw\'][\'value\'] == 0) {
    print "Closed";
} else {
    print $data->users_node_name;
}
?>';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = '';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'brewhouse_reservation' => 'brewhouse_reservation',
  );

  /* Display: Desktop */
  $handler = $view->new_display('block', 'Desktop', 'block_1');

  /* Display: Mobile */
  $handler = $view->new_display('block', 'Mobile', 'block_2');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'fullcalendar';
  $handler->display->display_options['style_options']['defaultView'] = 'basicWeek';
  $handler->display->display_options['style_options']['left'] = 'today next,prev';
  $handler->display->display_options['style_options']['timeformat'] = 'h:mmt';
  $handler->display->display_options['style_options']['fields']['title_field'] = 'php';
  $handler->display->display_options['style_options']['fields']['title'] = TRUE;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $export['brewhouse_reservations'] = $view;

  return $export;
}
