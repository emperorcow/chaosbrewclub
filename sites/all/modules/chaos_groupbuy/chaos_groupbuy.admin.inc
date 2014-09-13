<?php

function chaos_groupbuy_form($form, &$form_state, $groupbuy = NULL) {
	$form = array();

	$form['name'] = array(
		'#type' => 'textfield',
		'#title' => t('Title'),
		'#default_value' => isset($groupbuy->name) ? $groupbuy->name : '',
		'#description' => t('Name of the group buy presented to members.'),
		'#required' => TRUE,
		'#maxlength' => 255,
	);

	$form['description'] = array(
		'#type' => 'textarea',
		'#title' => t('Description'),
		'#default_value' => isset($groupbuy->description) ? $groupbuy->description : '',
		'#description' => t('Description of the group bulk buy.'),
		'#required' => FALSE,
	);

	$form['pallet'] = array(
		'#type' => 'fieldset',
		'#title' => 'Pallet Information',
		'pallet_size' => array(
			'#type' => 'textfield',
			'#title' => t('Pallet Size'),
			'#default_value' => isset($groupbuy->pallet_size) ? $groupbuy->pallet_size : '',
			'#description' => t('The number of items that are allowed on each pallet.'),
			'#required' => TRUE,
			'#size' => 5,
			'#maxlength' => 5,
			'#element_validate' => array('element_validate_integer'),
		),
		'pallet_count' => array(
			'#type' => 'textfield',
			'#title' => t('Current Orders'),
			'#default_value' => isset($groupbuy->pallet_count) ? $groupbuy->pallet_count : '0',
			'#description' => t('The number of items currently ordered to calculate number of pallets. BE CAREFUL CHANGING THIS!'),
			'#required' => TRUE,
			'#size' => 5,
			'#maxlength' => 5,
			'#element_validate' => array('element_validate_integer'),
		),
	);

	$start = $end = NULL;

	if(isset($groupbuy->start_date)) {
		$start = new DateObject($groupbuy->start_date);
		$start = $start->format(DATE_FORMAT_DATETIME);
	}
	if(isset($groupbuy->end_date)) {
		$end = new DateObject($groupbuy->end_date);
		$end = $end->format(DATE_FORMAT_DATETIME);
	}

	$form['timing'] = array(
		'#type' => 'fieldset',
		'#title' => 'Group Buy Timing',
		'#description' => t('Dates the group buy should begin and end on'),
		'start_date' => array(
			'#type' => 'date_popup',
			'#title' => t('Start Date'),
			'#date_format' => 'Y-m-d',
			'#default_value' => $start,
		),
		'end_date' => array(
			'#type' => 'date_popup',
			'#title' => t('End Date'),
			'#date_format' => 'Y-m-d',
			'#default_value' => $end,
		),
	);

	$form['fees'] = array(
		'#type' => 'fieldset',
		'#title' => 'Fees',
		'#description' => t('An optional fee can be added to each item ordered during the buy, such as for credit card processor fees.'),
		'fee_name' => array(
			'#type' => 'textfield',
			'#title' => t('Fee Label'),
			'#size' => 32,
			'#maxlength' => 64,
			'#default_value' => isset($groupbuy->fee_name) ? $groupbuy->fee_name : '',
			'#description' => t("This is what will appear next to the Fee amount on orders."),
		),
		'fee_amount' => array(
			'#type' => 'textfield',
			'#title' => t('Fee Amount'),
			'#size' => 10,
			'#maxlength' => 10,
			'#default_value' => isset($groupbuy->fee_amount) ? $groupbuy->fee_amount : '',
			'#description' => t('The percentage amount of the fee.'),
		),
	);

	$form['actions'] = array(
		'#type' => 'actions',
		'submit' => array(
			'#type' => 'submit',
			'#value' => isset($groupbuy->gid) ? t('Update Groupbuy'): t('Create Groupbuy'),
		),
	);

	return $form;
}

function chaos_groupbuy_purchase_form($form, &$form_state, $groupbuy_purchase = NULL) {
	$form['gid'] = array(
		'#type' => 'textfield',
		'#title' => t('GroupBuy ID'),
		'#default_value' => isset($groupbuy_purchase->gid) ? $groupbuy_purchase->gid : '',
		'#description' => t('ID of the GroupBuy this is attached to.'),
		'#disabled' => TRUE,
	);
	$form['oid'] = array(
		'#type' => 'textfield',
		'#title' => t('Order ID'),
		'#default_value' => isset($groupbuy_purchase->oid) ? $groupbuy_purchase->oid : '',
		'#description' => t('ID of the order this is attached to.'),
		'#disabled' => TRUE,
	);
	$form['uid'] = array(
		'#type' => 'textfield',
		'#title' => t('User ID'),
		'#default_value' => isset($groupbuy_purchase->uid) ? $groupbuy_purchase->uid : '',
		'#description' => t('ID of the user this is attached to.'),
		'#disabled' => TRUE,
	);
	$form['pallet'] = array(
		'#type' => 'textfield',
		'#title' => t('Pallet'),
		'#default_value' => isset($groupbuy_purchase->pallet) ? $groupbuy_purchase->pallet : '',
		'#description' => t('Pallet this specific item was attached to.'),
		'#required' => TRUE,
	);
	$form['actions'] = array(
		'#type' => 'actions',
		'submit' => array(
			'#type' => 'submit',
			'#value' => 'Update Purchase',
		),
	);

	return $form;
}

function chaos_groupbuy_form_validate($form, &$form_state) {
}

function chaos_groupbuy_form_submit($form, &$form_state) {
	$start = new DateObject($form_state['values']['start_date']);
	$end = new DateObject($form_state['values']['end_date']);
	$form_state['values']['start_date'] = $start->format(DATE_FORMAT_UNIX);
	$form_state['values']['end_date'] = $end->format(DATE_FORMAT_UNIX);

	$form_state['values']['pallet_size'] = intval($form_state['values']['pallet_size']);
	$form_state['values']['pallet_count'] = intval($form_state['values']['pallet_count']);
	$form_state['values']['fee_amount'] = floatval($form_state['values']['fee_amount']);

	$groupbuy = entity_ui_form_submit_build_entity($form, $form_state);

	$groupbuy->save();

	drupal_set_message(t('Group buy "@name" has been saved.', array('@name' => $groupbuy->name)));
	$form_state['redirect'] = 'groupbuy/admin/manage/' . $groupbuy->gid;
}

function chaos_groupbuy_manage_pallets_callback($form, &$form_state, $gid) {
	$form['pager'] = array('#theme' => 'pager');

	$header = array(
		'user' => array('data' => t('Username'), 'field' => 'user'),
		'pallet' => array('data' => t('Pallet'), 'field' => 'pallet'),
		'itemid' => array('data' => t('Item ID'), 'field' => 'itemid'),
		'subcategory' => array('data' => t('Category'), 'field' => 'subcategory'),
		'itemname' => array('data' => t('Item'), 'field' => 'itemname'),
		'size' => array('data' => t('Size'), 'field' => 'size'),
		'quantity' => array('data' => t('Quantity'), 'field' => 'quantity'),
		'actions' => array('data' => t('Purchase Actions'), 'field' => 'actions'),
	);

	$g = chaos_groupbuy_load($gid);
	$query = new EntityFieldQuery();
	$query->entityCondition('entity_type', 'chaos_groupbuy_purchase')
		  ->propertyCondition('gid', $gid, '=');
	$query->pager(100);
	$result = $query->execute();

	$ids = array();
	if(!empty($result['chaos_groupbuy_purchase'])) {
		foreach($result['chaos_groupbuy_purchase'] as $purchase) {
			$ids[] = $purchase->groupbuy_purchase_id;
		}
	}
	$purchases = chaos_groupbuy_purchase_load_multiple($ids);

	$options = array();
	foreach($purchases as $id => $p) {
		$product = ms_core_load_order_product($p->order_product_id);
		$user = user_load($p->uid);
		$options['purchase-'.$id] = array(
			'user' => l($user->name, 'users/' . $user->name),
			'itemid' => $product->data['itemid'],
			'subcategory' => $product->data['subcategory'],
			'itemname' => $product->data['title'],
			'size' => $product->data['size'],
			'quantity' => $product->qty,
			'pallet' => $p->pallet + 1,
			'actions' => l("Edit", 'groupbuy/admin/purchase/manage/'.$id) . ' - ' . l("Delete", 'groupbuy/admin/purchase/manage/'.$id.'/delete'),
			'#disabled' => TRUE,
		);
	}

	$form['entities'] = array(
		'#type' => 'tableselect',
		'#header' => $header,
		'#options' => $options,
		'#attributes' => array('class' => array('entity-sort-table')),
		'#empty' => t('There are no orders for this group buy at this time.'),
	);

	return $form;
}

function chaos_groupbuy_manage_orders_callback($form, &$form_state, $gid) {
	$form['pager'] = array('#theme' => 'pager');

	$g = chaos_groupbuy_load($gid);
	$query = new EntityFieldQuery();
	$query->entityCondition('entity_type', 'chaos_groupbuy_purchase')
		  ->propertyCondition('gid', $gid, '=');
	$query->pager(100);
	$result = $query->execute();

	$ids = array();
	if(!empty($result['chaos_groupbuy_purchase'])) {
		foreach($result['chaos_groupbuy_purchase'] as $purchase) {
			$ids[] = $purchase->groupbuy_purchase_id;
		}
	}
	$purchases = chaos_groupbuy_purchase_load_multiple($ids);

	$header = array(
		'user' => array('data' => t('Username'), 'field' => 'user'),
		'orderid' => array('data' => t('Order ID'), 'field' => 'orderid'),
		'status' => array('data' => t('Status'), 'field' => 'status'),
		'gateway' => array('data' => t('Payment Gateway'), 'field' => 'gateway'),
		'date' => array('data' => t('Date'), 'field' => 'date'),
		'amount' => array('data' => t('Total'), 'field' => 'amount'),
	);

	$options = array();
	$total = 0;
	$orders = array();

	foreach($purchases as $id => $p) {
		if(isset($orders[$p->oid])) {
			continue;
		}
		$orders[$p->oid] = true;
		$o = ms_core_order_load($p->oid);
		$user = user_load($p->uid);
		$options['purchase-'.$id] = array(
			'user' => l($user->name, 'users/' . $user->name),
			'orderid' => l($o->order_key, 'admin/moneyscripts/orders/edit/' . $o->order_key),
			'status' => ucfirst($o->status),
			'gateway' => $o->gateway,
			'date' => date('M j Y', $o->created),
			'amount' => '$'.number_format($o->total, 2),
			'#disabled' => TRUE,
		);
		$total += $o->total;
	}

	$form['entities'] = array(
		'#type' => 'tableselect',
		'#header' => $header,
		'#options' => $options,
		'#attributes' => array('class' => array('entity-sort-table')),
		'#empty' => t('There are no orders for this group buy at this time.'),
		'#suffix' => "<div style='float:right;'><b>Grand Total:</b> $".number_format($total, 2)."</div>",
	);

	return $form;
}

function chaos_groupbuy_delete_products_confirm($form, &$form_state, $gid) {
	$g = chaos_groupbuy_load($gid);
	$form['gid'] = array(
		'#type' => 'value',
		'#value' => $gid,
	);
	return confirm_form($form, 
			t('Are you sure you want to delete all products for @name?', array('@name' => $g->name)), 
			'groupbuy', 
			t('This action cannot be undone, you will delete ALL products for this group buy.'), 
			t('Delete All'), 
			t('Cancel'));
}

function chaos_groupbuy_delete_products_confirm_submit($form, &$form_state) {
	if($form_state['values']['confirm']) {
		$all = ms_products_get_plans_list('chaos_groupbuy');
		foreach($all as $sku => $name) {
			$plan = ms_products_plan_load($sku);
			if($plan->gid == $form_state['values']['gid']) {
				ms_products_plan_delete($plan);
			}
		}
	}
	$form_state['redirect'] = 'groupbuy/admin/';
}

function chaos_groupbuy_export_products_form($form, $form_state, $gid) {
	$form = array();
	$items = "";

	$form['gid'] = array(
		'#type' => 'select',
		'#title' => 'Group Buy',
		'#description' => 'The group buy this export is for.',
		'#options' => chaos_groupbuy_name_options(),
		'#disabled' => TRUE,
		'#default_value' => $gid,
	);

	$products = ms_products_get_plans_list('chaos_groupbuy');

	foreach ($products as $pid => $pname) {
		$plan = ms_products_plan_load($pid);

		if($plan->gid != $gid) {
			continue;
		}

		$items .= sprintf("\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\"\n", 
					$plan->category,
					$plan->subcategory,
					$plan->title,
					$plan->description,
					$plan->itemid,
					$plan->size,
					$plan->recurring_schedule['main_amount'],
					$plan->is_large ? "TRUE" : "FALSE"
			);
	}

	$form['items'] = array(
		'#type' => 'textarea',
		'#title' => 'Products Output',
		'#description' => 'This is a CSV file that can be edited in Excel and reimported if new data is necessary.',
		'#default_value' => $items,
	);

	return $form;
}

function chaos_groupbuy_import_products_form($form, $form_state, $gid) {
	$form = array();

	$form['gid'] = array(
		'#type' => 'select',
		'#title' => 'Group Buy',
		'#description' => 'The Group Buy these products should be stored under',
		'#options' => chaos_groupbuy_name_options(),
		'#required' => TRUE,
		'#default_value' => $gid,
	);

	$form['items'] = array(
		'#type' => 'textarea',
		'#title' => 'Products CSV',
		'#description' => 'Category,SubCategory,Name,Description,ItemID,Weight/Size,Cost,Pallet Size',
		'#required' => TRUE,
	);
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => 'Import Products',
	);

	return $form;
}

function chaos_groupbuy_import_products_form_submit($form, $form_state) {
	$gid = $form_state['values']['gid'];

	$lines = explode("\n", $form_state['values']['items']);
	$i = 0;

	foreach($lines as $line) {
		if(empty($line)) {
			continue;
		}
		$info = str_getcsv($line);
		$product = new MsProductsPlan();

		$pallet = strtoupper($info[7]) == 'LARGE' ? TRUE : FALSE;
		$info[3] = str_replace("\n", "", $info[3]);

		$product->disabled = FALSE; 
		$product->api_version = 1;
		$product->bundle = 'chaos_groupbuy';
		$product->sku = $gid . "_" . strtolower(str_replace("-", "_", $info[4]));
		$product->uid = 1;
		$product->name = rtrim($info[4]);
		$product->cart_type = 'cart';
		$product->description = rtrim($info[3]);
		$product->signup_mail_subject = '';
		$product->signup_mail_body = '';
		$product->eot_mail_subject = '';
		$product->eot_mail_body = '';
		$product->cancel_mail_subject = '';
		$product->cancel_mail_body = '';
		$product->modify_mail_subject = '';
		$product->modify_mail_body = '';
		$product->expiring_mail_subject = '';
		$product->expiring_mail_body = '';
		$product->expiring_mail_days = 3;
		$product->weight = 0;
		$product->recurring_schedule = array(
			'total_occurrences' => 1,
			'main_amount' => $info[6],
			'main_length' => '0',
			'main_unit' => 'M',
			'has_trial' => FALSE,
			'trial_amount' => 0,
			'trial_length' => 0,
			'trial_unit' => '',
			'fixed_date' => 0,
			'fixed_date_discount' => 1,
			'fixed_date_type' => 'M',
			'fixed_date_string' => '',
		);
		$product->modify_options = array(
			'upgrade' => array(),
			'downgrade' => array(),
		);
		$product->allow_roles = array();
		$product->deny_roles = array();
		$product->expire_when = 'subscr_eot';
		$product->data = array(
			'allow_multiple' => 1,
			'recurring_optional' => FALSE,
			'shippable' => 0,
			'grant_credit' => 0,
			'change_plan_options' => 1,
			'override_settings' => array(),
			'allow_roles' => array(),
			'deny_roles' => array(),
			'gid' => $gid,
			'title' => rtrim($info[2]),
			'itemid' => rtrim($info[4]),
			'size' => rtrim($info[5]),
			'category' => rtrim($info[0]),
			'subcategory' => rtrim($info[1]),
			'is_large' => $pallet,
		);
		ms_products_plan_save($product);
		$i++;
	}

	$form_state['redirect'] = 'groupbuy/' . $gid;
	drupal_set_message(t('Successfully imported @n products', array('@n' => $i)));
}
