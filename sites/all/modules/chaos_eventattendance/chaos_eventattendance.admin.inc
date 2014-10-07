<?php

function chaos_eventattendance_form($form, &$form_state, $event = NULL) {

  $form['name'] = array(
    '#title' => t('Name'),
	  '#type' => 'textfield',
	  '#default_value' => isset($event->name) ? $event->name : '',
    '#required' => TRUE,
	);

	$form['date'] = array(
    '#type' => 'date_popup',
   	'#date_format' => 'Y-m-d',
   	'#default_value' => isset($event->date) ? $event->date : '',
    '#required' => TRUE,
  );
  $form['roles'] = array(
    '#type' => 'checkboxes', 
    '#options' => user_roles(),
    '#title' => t('What roles are allowed to attend this event?'),
    '#default_value' => isset($event->roles) ? str_getcsv($event->roles) : '',
    '#required' => TRUE,
  );
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
  	'#type' => 'submit',
   	'#value' => t('Save event'),
   	'#weight' => 40,
  );

	return $form;
}

function chaos_eventattendance_form_submit(&$form, &$form_state) {

  $roles = "";
  foreach($form_state['values']['roles'] as $roleid) {
    if($roleid != 0) {
      $roles .= $roleid . ",";
    }  
  }
  $roles = rtrim($roles, ',');

  $form_state['values']['roles'] = $roles;

  $event_type = entity_ui_form_submit_build_entity($form, $form_state);
	$event_type->save();

  drupal_set_message(t('Event "@name" has been saved.', array('@name' => $event_type->name)));
	$form_state['redirect'] = 'admin/structure/eventattendance';
}