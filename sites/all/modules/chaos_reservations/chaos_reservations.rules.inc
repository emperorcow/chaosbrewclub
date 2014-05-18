<?php

function chaos_reservations_rules_event_info() {
	$events['reservation_created'] = array(
		'label' => t('Brewhouse reservation created'),
		'module' => 'chaos_reservations', 
		'arguments' => array(
			'user' => array('type' => 'user', 'label' => t('The user who created the reservation')),
			'reservation' => array('type' => 'node', 'label' => t('The new reservation')),
		),
	);
	/*$events['brewhouse_closed'] => array(
		'label' => t('Brewhouse closed with reservations'),
		'module' => 'chaos_reservations',
		'arguments' => array(
			'array of reservations that overlap closure'
			'Reason for closure string'
		),
	);*/

	return $events;
}

function chaos_reservations_rules_condition_info() {
	$cond['chaos_reservations_condition_reservation_coverage'] = array(
		'label' => t('Brewhouse reservation access is covered'),
		'module' => 'chaos_reservations',
		'arguments' => array(
			'reservation' => array('type' => 'node', 'label' => t('The reservation to check against')),
		),
	);
}

function chaos_reservations_condition_reservation_coverage($node) {
	#TODO: Check to see if the reservation is fully covered by alchemists, etc.
}
