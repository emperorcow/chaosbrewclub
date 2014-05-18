<?php

/**
 * @file
 * First Data redirected payment service DMS processing functions.
 */

/**
 * DMS payment process function.
 */
function ms_ibis_process_dms(MsOrder $order) {
  global $language;
  $ecomm_client_url = (variable_get('ms_ibis_server', 'test') == 'test') ? variable_get('client_url_test', '') : variable_get('client_url_live', '');
  $ecomm_server_url = (variable_get('ms_ibis_server', 'test') == 'test') ? variable_get('server_url_test', '') : variable_get('server_url_live', '');

  $amount = $order->amount;
  $ip = ip_address();
  // Use localhost IP address to make testing procedure for blakclist IP.
  // $ip = '192.168.1.2'.
  $currency = variable_get('ms_ibis_currency', 'EUR');
  $description = urlencode(htmlspecialchars(t('Order #!order payment', array('!order' => check_plain($order->order_number))), ENT_QUOTES));
  $lang = $language->language;
  $ibis_order_id = $order->oid;

  $merchant = new Merchant($ecomm_server_url, variable_get('ms_ibis_cert_path', ''), variable_get('ms_ibis_cert_pass', ''), 1);

  $resp = $merchant->startDMSAuth($amount, $currency, $ip, $description, $lang);

  if (substr($resp, 0, 14) == 'TRANSACTION_ID') {
    $trans_id = substr($resp, 16, 28);
    $url = $ecomm_client_url . '?trans_id=' . urlencode($trans_id) . '&ibis_order_id=' . $ibis_order_id;
    $result = db_insert('ms_ibis_transaction')
      ->fields(array(
        'trans_id' => $trans_id,
        'amount' => $amount,
        'currency' => $currency,
        'client_ip_addr' => $ip,
        'order_id' => $ibis_order_id,
        'description' => t('Order #!order payment', array('!order' => check_plain($order->order_number))),
        'language' => $language,
        't_date' => REQUEST_TIME,
        'response' => $resp,
      ))
      ->execute();

    drupal_goto($url);
  }
  else {
    ms_core_log('ms_ibis', 'startDMSAuth failed: !result', array('!result' => $resp));
    $result = db_insert('ms_ibis_error')
      ->fields(array(
        'error_time' => REQUEST_TIME,
        'action' => 'startDMSAuth',
        'response' => $resp,
      ))
      ->execute();

    drupal_set_message(t('An error occurred! Please contact merchant!'));
    drupal_goto();
  }
}

/**
 * @todo - DMS payment make function.
 */
function ms_ibis_make_dms() {
  $ecomm_server_url = (variable_get('ms_ibis_server', 'test') == 'test') ? variable_get('server_url_test', '') : variable_get('server_url_live', '');

  $id = $_REQUEST['order_id'];

  $merchant = new Merchant($ecomm_server_url, variable_get('ms_ibis_cert_path', ''), variable_get('ms_ibis_cert_pass', ''), 1);

  $result = db_query("SELECT * FROM {ms_ibis_transaction} WHERE order_id = :order_id", array(':order_id' => $id));

  $row = $result->fetchAssoc();
  $auth_id = urlencode($_REQUEST['trans_id']);
  $amount = $_REQUEST['amount'] * 100;
  $currency = urlencode($row['currency']);
  $ip = urlencode($row['client_ip_addr']);
  $desc = urlencode($row['description']);
  $language = urlencode($row['language']);

  $resp = $merchant->makeDMSTrans($auth_id, $amount, $currency, $ip, $desc, $language);

  if (substr($resp, 8, 2) == 'OK') {
    $trans_id = $row['trans_id'];
    $result = db_update('ms_ibis_transaction')
    ->fields(array(
      'dms_ok' => 'YES',
      'makeDMS_amount' => $amount,
    ))
    ->condition('trans_id', $trans_id)
    ->execute();

    ms_core_log('ms_ibis', 'DMS payment made (makeDMSTrans): !result', array('!result' => $resp));
    drupal_set_message(check_plain(t('DMS payment made: !result', array('!result' => $resp))));
    drupal_goto('admin/store/orders/' . $id);
  }
  else {
    $result = db_insert('ms_ibis_error')
    ->fields(array(
      'error_time' => REQUEST_TIME,
      'action' => 'makeDMSTrans',
      'response' => $resp,
    ))
    ->execute();

    ms_core_log('ms_ibis', 'DMS payment make failed: !result', array('!result' => $resp));
    drupal_set_message(check_plain(t('DMS payment make failed: !result', array('!result' => $resp))));

    // If failed, redirect admin back to order.
    drupal_goto('admin/store/orders/' . $id);
  }
}

/**
 * @todo - DMS payment form.
 */
function ms_ibis_make_dms_form($form, $form_state, $order) {
  global $language;

  $wrapper = entity_metadata_wrapper('commerce_order', $order_id);
  $currency = $wrapper->commerce_order_total->currency_code->value();
  $amount = $wrapper->commerce_order_total->amount->value();

  $result = db_query("SELECT trans_id FROM {ms_ibis_transaction} WHERE order_id = :order_id", array(':order_id' => $order_id));
  $trans_id = $result->fetchField();

  $data = array(
    'order_id' => $order_id,
    'lang' => $language->language,
  );

  $form['#action'] = base_path() . 'cart/ibis/make/dms';

  foreach ($data as $name => $value) {
    $form[$name] = array(
      '#type' => 'hidden',
      '#value' => $value,
    );
  }
  $form['trans_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Transaction id'),
    '#value' => $trans_id,
  );
  $form['amount'] = array(
    '#type' => 'textfield',
    '#title' => check_plain(t('Amount')),
    '#value' => $amount,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Make DMS payment'),
  );

  return $form;
}
