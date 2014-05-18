<?php
$groupbuys = (chaos_groupbuy_name_options());

$plugin = array(
	'plan_name' => t('Group Buy Product'),
	'plan_name_plural' => t('Group Buy Products'),
	'purchase_name' => t('Purchase'),
	'purchase_name_plural' => t('Purchases'),
	'plan_fields' => array(
		'title' => array(
			'#type' => 'textfield',
			'#data_type' => 'text',
			'#title' => t('Product Name'),
			'#array_parents' => array('product'),
			'#description' => t('Name of the product that fits under the subcategory.'),
			'#required' => TRUE,
			'#default_value' => '',
		),
		'gid' => array(
			'#type' => 'select',
			'#data_type' => 'integer',
			'#title' => t('Group Buy ID'),
			'#array_parents' => array('product'),
			'#description' => TRUE,
			'#required' => TRUE,
			'#options' => $groupbuys,
			'#default_value' => '',
		),
		'itemid' => array(
			'#type' => 'textfield',
			'#data_type' => 'text',
			'#title' => t('Item ID'),
			'#array_parents' => array('product'),
			'#description' => t('The Country Malt Group item code'),
			'#required' => TRUE,
			'#default_value' => '',
		),
		'is_large' => array(
			'#type' => 'checkbox',
			'#data_type' => 'boolean',
			'#title' => t('Is a full pallet item'),
			'#array_parents' => array('product'),
			'#description' => t('Whether or not the product will count in total against the pallet count'),
			'#required' => TRUE,
			'#default_value' => TRUE,
		),
		'size' => array(
			'#type' => 'textfield',
			'#data_type' => 'integer',
			'#title' => t('Item Size'),
			'#array_parents' => array('product'),
			'#description' => t('The size of the item in pounds.'),
			'#required' => TRUE,
			'#default_value' => '55',
		),
		'category' => array(
			'#type' => 'textfield',
			'#data_type' => 'text',
			'#title' => t('Category'),
			'#array_parents' => array('product'),
			'#description' => t('Grouping of the item.'),
			'#required' => TRUE,
			'#default_value' => '',
		),
		'subcategory' => array(
			'#type' => 'textfield',
			'#data_type' => 'text',
			'#title' => t('Subcategory'),
			'#array_parents' => array('product'),
			'#description' => t('Grouping within the category'),
			'#required' => TRUE,
			'#default_value' => '',
		)
	)
);
