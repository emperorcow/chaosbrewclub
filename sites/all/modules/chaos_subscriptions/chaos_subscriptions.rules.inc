<?php
/*
function chaos_subscriptions_rules_action_info() {
	$actions = array();

	$actions['chaos_subscriptions_action_create_hash'] = array(
		'label' => t('Create a secured hash to validate replies.'),
		'group' => t('Validated SMTP Replies'),
		'parameter' => array(
			'account' => array(
				'type' => 'user',
				'label' => t('The user to bind the hash to.'),
			),
			'node' => array(
				'type' => 'node',
				'label' => t('The node to bind the hash to.'),
				'optional' => TRUE,
				'allow null' => TRUE,
				'default value' => null,
			),
			'threadid' => array(
				'type' => 'integer',
				'label' => t('The thread_id of a private message to bind the hash to.'),
				'optional' => TRUE,
				'allow null' => TRUE,
				'default value' => null,
			),
		),
		'provides' => array(
			'validator_hash' => array(
				'type' => 'text',
				'label' => t('Validator hash to track secured replies.'),
			),
		),
	);

	return $actions;
}

function chaos_subscriptions_action_create_hash($account, $node, $tid) {
	$fields = array();
	$tmpnum = 1;

	if(isset($node)) {
		$fields['type'] = 'node';
		$tmpnum = $node->nid;
	} elseif(isset($tid)) {
		$fields['type'] = 'pm';
		$tmpnum = $tid;
	} else {
		return false;
	}

	$fields['nonce'] = chaos_subscriptions_generate_hash($account->uid, $tmpnum);
	$fields['id'] = $tmpnum;
	$fields['uid'] = $account->uid;

	try {
		db_insert('chaos_subscriptions_nonces')
			->fields($fields)
			->execute();
	} catch (Exception $e) {
		drupal_set_message(t("Unable to send notification email to subscribers."), 'error');
		watchdog_exception('chaos_subscriptions', $e, 'Error occured while generating nonce.');
	}

	return array('validator_hash' => $fields['nonce']);
}


function chaos_subscriptions_generate_hash($uid, $nid) {
	return md5(time() . $uid . $nid . drupal_random_bytes(200));
}


function chaos_subscriptions_rules_event_info() {
	$events = array();

	$events['chaos_subscriptions_event_new_smtp_node'] = array( 
		'label' => t('New validated SMTP comment reply exists'),
		'group' => t('Validated SMTP Replies'),
		'variables' => array(
			'user' => array(
				'type' => 'user',
				'label' => t('User that posted the message'),
			),
			'node' => array(
				'type' => 'node',
				'label' => t('Source node where the comment will be posted.'),
			),
			'email_body' => array(
				'type' => 'text_formatted',
				'label' => t('Body of the message received'),
			),
		),
	);
	$events['chaos_subscriptions_event_new_smtp_pm'] = array( 
		'label' => t('New validated SMTP private message reply exists'),
		'group' => t('Validated SMTP Replies'),
		'variables' => array(
			'user' => array(
				'type' => 'user',
				'label' => t('User that posted the message'),
			),
			'tid' => array(
				'type' => 'integer',
				'label' => t('Thread ID of the private message to be sent.'),
			),
			'email_body' => array(
				'type' => 'text',
				'label' => t('Body of the message received'),
			),
		),
	);

	return $events;
}*/
