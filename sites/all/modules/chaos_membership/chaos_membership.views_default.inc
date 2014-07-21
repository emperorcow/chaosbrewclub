<?php
/**
 * @file
 * chaos_membership.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function chaos_membership_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'alchemist_applications';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Alchemist Applications';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Alchemist Applications';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    7 => '7',
    6 => '6',
    12 => '12',
    11 => '11',
    29 => '29',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '30';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'name' => 'name',
    'field_nomination_status' => 'field_nomination_status',
    'body' => 'body',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_nomination_status' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'body' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['text'] = '<a id=\'[name]\' href=\'/users/[name]\'>[name]</a>';
  $handler->display->display_options['fields']['name']['alter']['path'] = 'membership/alchemy/applications';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_user'] = FALSE;
  /* Field: Content: Nomination Status */
  $handler->display->display_options['fields']['field_nomination_status']['id'] = 'field_nomination_status';
  $handler->display->display_options['fields']['field_nomination_status']['table'] = 'field_data_field_nomination_status';
  $handler->display->display_options['fields']['field_nomination_status']['field'] = 'field_nomination_status';
  $handler->display->display_options['fields']['field_nomination_status']['label'] = 'Status';
  $handler->display->display_options['fields']['field_nomination_status']['element_label_colon'] = FALSE;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = 'Qualifications';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Actions';
  $handler->display->display_options['fields']['edit_node']['element_label_colon'] = FALSE;
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
    'alchemist_application' => 'alchemist_application',
  );

  /* Display: Alchemist Applications */
  $handler = $view->new_display('page', 'Alchemist Applications', 'full');
  $handler->display->display_options['path'] = 'membership/alchemy/applications';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');
  $handler->display->display_options['block_description'] = 'Alchemist Applications';

  /* Display: Alchemist Overview */
  $handler = $view->new_display('page', 'Alchemist Overview', 'list');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['path'] = 'membership/alchemy/applications#[name]';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_user'] = FALSE;
  /* Field: Content: Nomination Status */
  $handler->display->display_options['fields']['field_nomination_status']['id'] = 'field_nomination_status';
  $handler->display->display_options['fields']['field_nomination_status']['table'] = 'field_data_field_nomination_status';
  $handler->display->display_options['fields']['field_nomination_status']['field'] = 'field_nomination_status';
  $handler->display->display_options['fields']['field_nomination_status']['label'] = 'Status';
  $handler->display->display_options['fields']['field_nomination_status']['element_label_colon'] = FALSE;
  $handler->display->display_options['path'] = 'membership/alchemy/applicationlist';
  $export['alchemist_applications'] = $view;

  $view = new view();
  $view->name = 'membership';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'users';
  $view->human_name = 'Membership';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Membership';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access user profiles';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'datatables';
  $handler->display->display_options['style_options']['columns'] = array(
    'picture' => 'picture',
    'name' => 'name',
    'field_first_name' => 'field_first_name',
    'field_last_name' => 'field_last_name',
    'php' => 'php',
    'created' => 'created',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'picture' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_first_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_last_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
    'php' => array(
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['elements'] = array(
    'search_box' => 0,
    'table_info' => 1,
    'save_state' => 0,
    'table_tools' => 0,
  );
  $handler->display->display_options['style_options']['layout'] = array(
    'autowidth' => 0,
    'themeroller' => 0,
    'sdom' => '',
  );
  $handler->display->display_options['style_options']['pages'] = array(
    'pagination_style' => '0',
    'length_change' => 1,
    'display_length' => '100',
  );
  /* Field: User: Picture */
  $handler->display->display_options['fields']['picture']['id'] = 'picture';
  $handler->display->display_options['fields']['picture']['table'] = 'users';
  $handler->display->display_options['fields']['picture']['field'] = 'picture';
  $handler->display->display_options['fields']['picture']['exclude'] = TRUE;
  $handler->display->display_options['fields']['picture']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['picture']['image_style'] = 'thumbnail';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = 'Username';
  $handler->display->display_options['fields']['name']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['text'] = '[picture]<br/>
[name]';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  /* Field: User: First Name */
  $handler->display->display_options['fields']['field_first_name']['id'] = 'field_first_name';
  $handler->display->display_options['fields']['field_first_name']['table'] = 'field_data_field_first_name';
  $handler->display->display_options['fields']['field_first_name']['field'] = 'field_first_name';
  $handler->display->display_options['fields']['field_first_name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_first_name']['element_label_colon'] = FALSE;
  /* Field: User: Last Name */
  $handler->display->display_options['fields']['field_last_name']['id'] = 'field_last_name';
  $handler->display->display_options['fields']['field_last_name']['table'] = 'field_data_field_last_name';
  $handler->display->display_options['fields']['field_last_name']['field'] = 'field_last_name';
  $handler->display->display_options['fields']['field_last_name']['label'] = 'Name';
  $handler->display->display_options['fields']['field_last_name']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_last_name']['alter']['text'] = '[field_first_name] [field_last_name]';
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['label'] = 'Membership Level';
  $handler->display->display_options['fields']['php']['alter']['nl2br'] = TRUE;
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_value'] = '$user = user_load($data->uid);
$tmp = "";
if(isset($user->roles[6])) {
   $tmp = \'Brewer\';
} elseif(isset($user->roles[12])) {
   $tmp = \'Intro Brewer\';
} elseif(isset($user->roles[7])) {
   $tmp = \'Apprentice\';
} elseif(isset($user->roles[11])) {
   $tmp = \'Friend\';
} elseif(isset($user->roles[29])) {
   $tmp = \'Trial\';
} else {
   $tmp = \'Website\';
}
return $tmp;';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = '';
  /* Field: User: Created date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'users';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Member for';
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'raw time ago';
  /* Sort criterion: User: Created date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'users';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Global: Combine fields filter */
  $handler->display->display_options['filters']['combine']['id'] = 'combine';
  $handler->display->display_options['filters']['combine']['table'] = 'views';
  $handler->display->display_options['filters']['combine']['field'] = 'combine';
  $handler->display->display_options['filters']['combine']['operator'] = 'contains';
  $handler->display->display_options['filters']['combine']['exposed'] = TRUE;
  $handler->display->display_options['filters']['combine']['expose']['operator_id'] = 'combine_op';
  $handler->display->display_options['filters']['combine']['expose']['label'] = 'Name';
  $handler->display->display_options['filters']['combine']['expose']['description'] = 'Search by first, last or user name.';
  $handler->display->display_options['filters']['combine']['expose']['operator'] = 'combine_op';
  $handler->display->display_options['filters']['combine']['expose']['identifier'] = 'combine';
  $handler->display->display_options['filters']['combine']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    12 => 0,
    7 => 0,
    11 => 0,
    16 => 0,
    14 => 0,
    13 => 0,
    8 => 0,
    9 => 0,
    10 => 0,
    15 => 0,
  );
  $handler->display->display_options['filters']['combine']['fields'] = array(
    'name' => 'name',
    'field_first_name' => 'field_first_name',
    'field_last_name' => 'field_last_name',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'membership/list';

  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    3 => '3',
    15 => '15',
    14 => '14',
    30 => '30',
  );
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'views_data_export_xls';
  $handler->display->display_options['style_options']['attach_text'] = 'Excel File';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['filename'] = 'EventMemberList_%timestamp-mmm-%timestamp-dd-%timestamp-yyyy.xls';
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: User: First Name */
  $handler->display->display_options['fields']['field_first_name']['id'] = 'field_first_name';
  $handler->display->display_options['fields']['field_first_name']['table'] = 'field_data_field_first_name';
  $handler->display->display_options['fields']['field_first_name']['field'] = 'field_first_name';
  $handler->display->display_options['fields']['field_first_name']['label'] = '';
  $handler->display->display_options['fields']['field_first_name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_first_name']['element_label_colon'] = FALSE;
  /* Field: User: Last Name */
  $handler->display->display_options['fields']['field_last_name']['id'] = 'field_last_name';
  $handler->display->display_options['fields']['field_last_name']['table'] = 'field_data_field_last_name';
  $handler->display->display_options['fields']['field_last_name']['field'] = 'field_last_name';
  $handler->display->display_options['fields']['field_last_name']['label'] = 'Name';
  $handler->display->display_options['fields']['field_last_name']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_last_name']['alter']['text'] = '[field_last_name], [field_first_name]';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = 'Username';
  $handler->display->display_options['fields']['name']['alter']['text'] = '[picture]<br/>
[name]';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_user'] = FALSE;
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['label'] = 'Membership Level';
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_output'] = '<?php
$user = user_load($data->uid);
if(isset($user->roles[\'5\'])) {
   ?>Alchemist<?php
} elseif(isset($user->roles[6])) {
   ?>Brewer<?php
} elseif(isset($user->roles[12])) {
   ?>Brewer (Introductory)<?php
} elseif(isset($user->roles[7])) {
   ?>Apprentice<?php
} elseif(isset($user->roles[11])) {
   ?>Friend<?php
} elseif(isset($user->roles[29])) {
   ?>Trial<?php
} else {
   ?>Website<?php
}
?>';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = '';
  /* Field: Purchase: Status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'ms_products_purchases';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['relationship'] = 'ms_products_purchases';
  $handler->display->display_options['fields']['status']['label'] = 'Membership Status';
  $handler->display->display_options['fields']['status']['element_label_colon'] = FALSE;
  /* Field: Purchase: Start_date */
  $handler->display->display_options['fields']['start_date']['id'] = 'start_date';
  $handler->display->display_options['fields']['start_date']['table'] = 'ms_products_purchases';
  $handler->display->display_options['fields']['start_date']['field'] = 'start_date';
  $handler->display->display_options['fields']['start_date']['relationship'] = 'ms_products_purchases';
  $handler->display->display_options['fields']['start_date']['label'] = 'Start Date';
  $handler->display->display_options['fields']['start_date']['date_format'] = 'short';
  /* Field: Purchase: Expiration */
  $handler->display->display_options['fields']['expiration']['id'] = 'expiration';
  $handler->display->display_options['fields']['expiration']['table'] = 'ms_products_purchases';
  $handler->display->display_options['fields']['expiration']['field'] = 'expiration';
  $handler->display->display_options['fields']['expiration']['relationship'] = 'ms_products_purchases';
  $handler->display->display_options['fields']['expiration']['label'] = 'Expiration Date';
  $handler->display->display_options['fields']['expiration']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['expiration']['date_format'] = 'short';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: User: Last Name (field_last_name) */
  $handler->display->display_options['sorts']['field_last_name_value']['id'] = 'field_last_name_value';
  $handler->display->display_options['sorts']['field_last_name_value']['table'] = 'field_data_field_last_name';
  $handler->display->display_options['sorts']['field_last_name_value']['field'] = 'field_last_name_value';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  $handler->display->display_options['path'] = 'membership/eventlist';
  $handler->display->display_options['use_batch'] = 'batch';
  $export['membership'] = $view;

  $view = new view();
  $view->name = 'membership_orders';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'ms_orders';
  $view->human_name = 'Membership Orders';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Membership Orders';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'views_bulk_operations' => 'views_bulk_operations',
    'url' => 'url',
    'order_key' => 'order_key',
    'status' => 'status',
    'gateway' => 'gateway',
    'amount' => 'amount',
    'total' => 'total',
    'email_address' => 'email_address',
    'first_name' => 'first_name',
    'last_name' => 'last_name',
    'created' => 'created',
    'modified' => 'modified',
    'order_type' => 'order_type',
    'secured' => 'secured',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'views_bulk_operations' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'url' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'order_key' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'gateway' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'amount' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'total' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'email_address' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'first_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'last_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'modified' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'order_type' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'secured' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: Bulk operations: Order */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'ms_orders';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['label'] = '';
  $handler->display->display_options['fields']['views_bulk_operations']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'rules_component::rules_alter_order' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_script_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_modify_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'show_all_tokens' => 1,
        'display_values' => array(
          '_all_' => '_all_',
        ),
      ),
    ),
    'action::views_bulk_operations_argument_selector_action' => array(
      'selected' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'url' => '',
      ),
    ),
    'action::system_send_email_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
  );
  /* Field: Order: URL */
  $handler->display->display_options['fields']['url']['id'] = 'url';
  $handler->display->display_options['fields']['url']['table'] = 'views_entity_ms_order';
  $handler->display->display_options['fields']['url']['field'] = 'url';
  $handler->display->display_options['fields']['url']['exclude'] = TRUE;
  $handler->display->display_options['fields']['url']['link_to_entity'] = 0;
  /* Field: Order: Order key */
  $handler->display->display_options['fields']['order_key']['id'] = 'order_key';
  $handler->display->display_options['fields']['order_key']['table'] = 'ms_orders';
  $handler->display->display_options['fields']['order_key']['field'] = 'order_key';
  $handler->display->display_options['fields']['order_key']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['order_key']['alter']['path'] = '[url]';
  /* Field: Order: Status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'ms_orders';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  /* Field: Order: Gateway */
  $handler->display->display_options['fields']['gateway']['id'] = 'gateway';
  $handler->display->display_options['fields']['gateway']['table'] = 'ms_orders';
  $handler->display->display_options['fields']['gateway']['field'] = 'gateway';
  /* Field: Order: Amount */
  $handler->display->display_options['fields']['amount']['id'] = 'amount';
  $handler->display->display_options['fields']['amount']['table'] = 'ms_orders';
  $handler->display->display_options['fields']['amount']['field'] = 'amount';
  $handler->display->display_options['fields']['amount']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['amount']['precision'] = '0';
  $handler->display->display_options['fields']['amount']['prefix'] = '$';
  /* Field: Order: Total */
  $handler->display->display_options['fields']['total']['id'] = 'total';
  $handler->display->display_options['fields']['total']['table'] = 'ms_orders';
  $handler->display->display_options['fields']['total']['field'] = 'total';
  $handler->display->display_options['fields']['total']['precision'] = '0';
  $handler->display->display_options['fields']['total']['prefix'] = '$';
  /* Field: Order: Email address */
  $handler->display->display_options['fields']['email_address']['id'] = 'email_address';
  $handler->display->display_options['fields']['email_address']['table'] = 'ms_orders';
  $handler->display->display_options['fields']['email_address']['field'] = 'email_address';
  /* Field: Order: First name */
  $handler->display->display_options['fields']['first_name']['id'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['table'] = 'ms_orders';
  $handler->display->display_options['fields']['first_name']['field'] = 'first_name';
  /* Field: Order: Last name */
  $handler->display->display_options['fields']['last_name']['id'] = 'last_name';
  $handler->display->display_options['fields']['last_name']['table'] = 'ms_orders';
  $handler->display->display_options['fields']['last_name']['field'] = 'last_name';
  /* Field: Order: Created */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'ms_orders';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['date_format'] = 'short';
  /* Field: Order: Modified */
  $handler->display->display_options['fields']['modified']['id'] = 'modified';
  $handler->display->display_options['fields']['modified']['table'] = 'ms_orders';
  $handler->display->display_options['fields']['modified']['field'] = 'modified';
  $handler->display->display_options['fields']['modified']['date_format'] = 'short';
  /* Field: Order: Order type */
  $handler->display->display_options['fields']['order_type']['id'] = 'order_type';
  $handler->display->display_options['fields']['order_type']['table'] = 'ms_orders';
  $handler->display->display_options['fields']['order_type']['field'] = 'order_type';
  /* Field: Order: Secured */
  $handler->display->display_options['fields']['secured']['id'] = 'secured';
  $handler->display->display_options['fields']['secured']['table'] = 'ms_orders';
  $handler->display->display_options['fields']['secured']['field'] = 'secured';
  /* Sort criterion: Order: Created */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'ms_orders';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  $handler->display->display_options['sorts']['created']['granularity'] = 'minute';
  /* Filter criterion: Order: Order type */
  $handler->display->display_options['filters']['order_type']['id'] = 'order_type';
  $handler->display->display_options['filters']['order_type']['table'] = 'ms_orders';
  $handler->display->display_options['filters']['order_type']['field'] = 'order_type';
  $handler->display->display_options['filters']['order_type']['operator'] = 'contains';
  $handler->display->display_options['filters']['order_type']['exposed'] = TRUE;
  $handler->display->display_options['filters']['order_type']['expose']['operator_id'] = 'order_type_op';
  $handler->display->display_options['filters']['order_type']['expose']['label'] = 'Order type';
  $handler->display->display_options['filters']['order_type']['expose']['operator'] = 'order_type_op';
  $handler->display->display_options['filters']['order_type']['expose']['identifier'] = 'order_type';
  $handler->display->display_options['filters']['order_type']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    12 => 0,
    7 => 0,
    11 => 0,
    29 => 0,
    16 => 0,
    15 => 0,
    14 => 0,
    10 => 0,
    13 => 0,
    19 => 0,
    22 => 0,
    8 => 0,
    23 => 0,
    9 => 0,
    26 => 0,
    17 => 0,
    24 => 0,
    18 => 0,
    25 => 0,
    20 => 0,
    27 => 0,
    21 => 0,
    28 => 0,
  );
  /* Filter criterion: Order: Status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'ms_orders';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = array(
    'completed' => 'completed',
    'active' => 'active',
    'cancelled' => 'cancelled',
    'pending' => 'pending',
    'invoiced' => 'invoiced',
    'checkout' => 'checkout',
  );
  $handler->display->display_options['filters']['status']['exposed'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['operator_id'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['label'] = 'Status';
  $handler->display->display_options['filters']['status']['expose']['operator'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['identifier'] = 'status';
  $handler->display->display_options['filters']['status']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    12 => 0,
    7 => 0,
    11 => 0,
    29 => 0,
    16 => 0,
    15 => 0,
    14 => 0,
    10 => 0,
    13 => 0,
    19 => 0,
    22 => 0,
    8 => 0,
    23 => 0,
    9 => 0,
    26 => 0,
    17 => 0,
    24 => 0,
    18 => 0,
    25 => 0,
    20 => 0,
    27 => 0,
    21 => 0,
    28 => 0,
  );
  /* Filter criterion: Order: Gateway */
  $handler->display->display_options['filters']['gateway']['id'] = 'gateway';
  $handler->display->display_options['filters']['gateway']['table'] = 'ms_orders';
  $handler->display->display_options['filters']['gateway']['field'] = 'gateway';
  $handler->display->display_options['filters']['gateway']['operator'] = 'contains';
  $handler->display->display_options['filters']['gateway']['value'] = '';
  $handler->display->display_options['filters']['gateway']['exposed'] = TRUE;
  $handler->display->display_options['filters']['gateway']['expose']['operator_id'] = 'gateway_op';
  $handler->display->display_options['filters']['gateway']['expose']['label'] = 'Gateway';
  $handler->display->display_options['filters']['gateway']['expose']['operator'] = 'gateway_op';
  $handler->display->display_options['filters']['gateway']['expose']['identifier'] = 'gateway';
  $handler->display->display_options['filters']['gateway']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    12 => 0,
    7 => 0,
    11 => 0,
    29 => 0,
    16 => 0,
    15 => 0,
    14 => 0,
    10 => 0,
    13 => 0,
    19 => 0,
    22 => 0,
    8 => 0,
    23 => 0,
    9 => 0,
    26 => 0,
    17 => 0,
    24 => 0,
    18 => 0,
    25 => 0,
    20 => 0,
    27 => 0,
    21 => 0,
    28 => 0,
  );
  /* Filter criterion: Order: Email address */
  $handler->display->display_options['filters']['email_address']['id'] = 'email_address';
  $handler->display->display_options['filters']['email_address']['table'] = 'ms_orders';
  $handler->display->display_options['filters']['email_address']['field'] = 'email_address';
  $handler->display->display_options['filters']['email_address']['operator'] = 'contains';
  $handler->display->display_options['filters']['email_address']['exposed'] = TRUE;
  $handler->display->display_options['filters']['email_address']['expose']['operator_id'] = 'email_address_op';
  $handler->display->display_options['filters']['email_address']['expose']['label'] = 'Email address';
  $handler->display->display_options['filters']['email_address']['expose']['operator'] = 'email_address_op';
  $handler->display->display_options['filters']['email_address']['expose']['identifier'] = 'email_address';
  $handler->display->display_options['filters']['email_address']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    12 => 0,
    7 => 0,
    11 => 0,
    29 => 0,
    16 => 0,
    15 => 0,
    14 => 0,
    10 => 0,
    13 => 0,
    19 => 0,
    22 => 0,
    8 => 0,
    23 => 0,
    9 => 0,
    26 => 0,
    17 => 0,
    24 => 0,
    18 => 0,
    25 => 0,
    20 => 0,
    27 => 0,
    21 => 0,
    28 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/memberships/orders';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Order Management';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['membership_orders'] = $view;

  return $export;
}
