<?php
/**
 * @file
 * MS Core Pages functions
 *
 * Copyright 2008-2012 Leighton Whiting - MoneyScripts.net
 */

/**
 * Page callback: Adds a product to the cart.
 */
function ms_core_purchase_product(MsProduct $product, $checkout = FALSE) {
  ms_core_add_cart_product($product);

  // If option is set, go straight to checkout.
  if ($checkout) {
    drupal_goto('ms/checkout');
  }

  drupal_goto();
}

/**
 * Page callback: Lists the Order Details.
 *
 * @param string $order_key
 *   The order key.
 *
 * @see ms_core_menu().
 */
function ms_core_view_order_details(MsOrder $order) {
  global $user;
  $output = '';
  if ($order) {
    // Add the CSS.
    drupal_add_css(drupal_get_path('module', 'ms_core') . '/css/ms_core.css');
    $account = user_load($order->uid);
    $headers = array();
    $attr = array('id' => 'ms-core-order-details-table');
    $actions = array();
    if (user_access('cancel own recurring moneyscripts orders') && $cancel_url = ms_core_get_cancel_url($order)) {
      $actions[] = l(t('Cancel Recurring Payments'), $cancel_url,
        array('attributes' => array('target' => '_blank'), 'query' => drupal_get_destination()));
    }
    if (user_access('edit own payment info') && $billing_url = ms_core_get_billing_url($order)) {
      $actions[] = l(t('Update Billing Information'), $billing_url,
        array('query' => drupal_get_destination()));
    }
    if ($order->status == 'checkout' AND $user->uid == $order->uid) {
      $actions[] = l(t('Checkout'), 'ms/resume-checkout/' . $order->order_key);
      $actions[] = l(t('Delete'), 'user/' . $user->uid . '/order-history/delete/' . $order->order_key);
    }

    if (user_access('administer moneyscripts orders')) {
      $actions[] = l(t('Edit'), 'admin/moneyscripts/orders/edit/' . $order->order_key);
    }

    $rows = array(
      array(
        'data' => array(t('Order', array(), array('context' => 'ms_core')) . ' #', $order->order_number),
        'class' => array('ms_order_oid'),
      ),
      array(
        'data' => array(t('User'), isset($account->name) ? l($account->name, 'user/' . $account->uid) : t('N/A')),
        'class' => array('ms_order_user'),
      ),
      array(
        'data' => array(t('Created'), format_date($order->created)),
        'class' => array('ms_order_created'),
      ),
      array(
        'data' => array(t('Total'), ms_core_format_money($order->total, $order->currency, 'order_total')),
        'class' => array('ms_order_total'),
      ),
      array(
        'data' => array(t('Status'), ms_core_get_order_status($order->status)),
        'class' => array('ms_order_status'),
      ),
      array(
        'data' => array(t('Actions'), implode($actions, ' | ')),
        'class' => array('ms_order_actions'),
      ),
      array(
        'data' => array(array(
            'data' => ms_core_get_order_details_table($order),
            'colspan' => 2,
          )),
        'class' => array('ms_order_details'),
      ),
      array(
        'data' => array(t('Order Type'), ms_core_get_order_type($order)),
        'class' => array('ms_order_type'),
      ),
      array(
        'data' => array(array(
            'data' => ms_core_get_order_payments_table($order),
            'colspan' => 2,
          )),
        'class' => array('ms_order_payments_row'),
      ),
      array(
        'data' => array(array(
            'data' => ms_core_get_order_customer_information_table($order),
            'colspan' => 2,
          )),
        'class' => array('ms_order_address_row'),
      ),
      array(
        'data' => array(array(
            'data' => ms_core_get_order_history_table($order),
            'colspan' => 2,
          )),
        'class' => array('ms_order_history_row'),
      ),
    );

    if (!empty($order->data['notes'])) {
      $rows[] = array(
        'data' => array(array(
            'data' => theme_item_list(array('items' => $order->data['notes'], 'title' => t('Notes'), 'type' => 'ul', 'attributes' => array())),
            'colspan' => 2,
          )),
        'class' => array('ms_order_notes_row'),
      );
    }

    // Output the table.
    $output .= theme('table', array('header' => $headers, 'rows' => $rows, 'attributes' => $attr));
    return $output;
  }
  else {
    drupal_not_found();
  }
}

/**
 * Generates the invoice header html with token support.
 *
 * @param MsOrder $order
 *   The order object.
 *
 * @return string
 *   HTML for the invoice header.
 */
function ms_core_get_invoice_header(MsOrder $order) {
  $account = user_load($order->uid);
  $template = variable_get('ms_core_invoice_header', variable_get('ms_core_invoice_header', "<h2>[site:name]</h2><h4>[site:slogan]</h4>"));
  $template = token_replace($template, array(
    'ms_core_order' => $order,
    'user' => $account,
  ));
  return $template;
}

/**
 * Page callback: Displays the invoice for an order.
 *
 * @param MsOrder $order
 *   The order.
 *
 * @see ms_core_menu()
 */
function ms_core_view_order_invoice(MsOrder $order) {
  if ($order) {
    $vars = array(
      'order' => $order,
      'op' => 'view',
      'invoice_header' => ms_core_get_invoice_header($order),
    );
    return theme('ms_core_invoice', $vars);
  }
  else {
    drupal_not_found();
  }
}

/**
 * Page callback: Displays the print invoice for an order.
 *
 * @param MsOrder $order
 *   The order.
 *
 * @see ms_core_menu()
 */
function ms_core_view_order_print($order) {
  if ($order) {
    $op = 'print';
    if (ip_address() == '69.164.218.62') {
      $op = 'pdf';
    }
    $vars = array(
      'order' => $order,
      'op' => $op,
      'invoice_header' => ms_core_get_invoice_header($order),
    );
    print theme('ms_core_invoice', $vars);
    exit;
  }
  else {
    drupal_not_found();
  }
}

/**
 * Page callback: Shows the Billing Information for a user.
 *
 * @param object $user
 *   The user object.
 *
 * @see ms_core_menu()
 */
function ms_core_user_billing_info_page($user) {
  $html = array();

  drupal_alter('ms_core_billing_info', $html, $user);

  if (empty($html)) {
    return t('No Billing Information is Available.');
  }

  return drupal_render($html);
}

/**
 * Page callback: Checkout Page.
 *
 * @param string $order_key
 *   (Optional) The unique order key for checking out. If blank, then the
 *   cart from SESSION is used.
 *
 * @see ms_core_menu()
 */
function ms_core_checkout_page($order_key = '') {
  // Stop the caching.
  $GLOBALS['conf']['cache'] = FALSE;

  $is_cart = TRUE;
  if ($order_key && $order = ms_core_order_load_by_key($order_key)) {
    $cart = $order;
    $is_cart = FALSE;
    ms_core_set_order_session($order);
  }
  else {
    $order = ms_core_load_session_order();
    if ($order && $order->status == 'checkout') {
      $cart = $order;
      $is_cart = FALSE;
    }
    else {
      $cart = ms_core_get_cart();
    }
  }

  // Trigger the rule.
  if (module_exists('rules')) {
    rules_invoke_event('ms_core_event_cart_checkout', $cart);
  }

  if (count($cart->products) > 0) {
    // Give other modules a chance to add steps to the checkout form.
    // Invoke hook_ms_checkout_steps to get the steps.
    $steps = module_invoke_all('ms_checkout_steps', $cart);

    if (!is_array($steps)) {
      $steps = array();
    }

    // Perform each step until they have all been done.
    foreach ($steps as $step) {
      // Perform the step.
      return drupal_get_form($step['form_id'], $cart);
    }

    // Once all of the steps are done, show the final checkout form to let the
    // user choose the gateway.
    $gateways = ms_core_get_checkout_payment_gateways($cart->order_type, $cart->data['blocked_gateways']);

    // Allow other modules to alter the gateways.
    drupal_alter('ms_payment_gateway', $gateways, $cart);

    $fields = ms_core_get_checkout_fields($cart);

    // Bypass the Checkout Form?
    global $user;
    if (!count($fields) AND count($gateways) == 1 AND ($user->uid OR $cart->data['skip_registration']) AND variable_get('ms_core_skip_checkout', FALSE) AND $cart->total > 0) {
      // Save the order.
      if ($is_cart) {
        ms_core_cart_to_order();
      }
      foreach ($gateways as $gateway) {
        if (!empty($gateway['checkout_path'])) {
          // Redirect to the Gateway Payment Page.
          drupal_goto($gateway['checkout_path']);
        }
        else {
          drupal_goto('ms/checkout/payment/' . $gateway['module']);
        }
        break;
      }
    }

    $build = array();
    $build_fields = array();

    // Order the fields by weight
    usort($fields, "ms_core_sort_fields");

    foreach ($fields as $field) {
      if ($field['type'] != 'form') {
        $build_fields[$field['id']] = array(
          '#type' => 'fieldset',
          '#title' => check_plain($field['title']),
          '#collapsible' => TRUE,
          '#collapsed' => FALSE,
        );
        $build_fields[$field['id']][$field['id'] . '_html'] = array(
          '#type' => 'item',
          '#markup' => $field['html'],
        );
      }
      else {
        $build_fields[$field['id']] = array(
          '#type' => 'fieldset',
          '#title' => check_plain($field['title']),
          '#collapsible' => TRUE,
          '#collapsed' => FALSE,
        );
        $build_fields[$field['id']]['form'] = drupal_get_form($field['html']);
      }
    }

    $checkout_form = drupal_get_form('ms_core_checkout_form', $cart);

    $build['content'] = array(
      'ms_checkout_page' => array(
        '#prefix' => "<div id='ms-core-checkout-page-wrapper'>",
        '#suffix' => "</div>",
        '#markup' => theme('ms_core_checkout_page', array(
          'checkout_steps' => theme('ms_core_checkout_steps', array('steps' => ms_core_get_checkout_steps($cart), 'current' => 'checkout')),
          'order_details' => ms_core_get_order_details_table($cart, $is_cart),
          'checkout_fields' => drupal_render($build_fields),
          'checkout_form' => drupal_render($checkout_form),
        )),
      ),
    );

    $build['#attached']['css'] = array(
      drupal_get_path('module', 'ms_core') . '/css/ms_core.checkout.css',
      drupal_get_path('module', 'ms_core') . '/css/ms_core.css',
    );
    $build['#attached']['js'] = array(
      drupal_get_path('module', 'ms_core') . '/js/checkout_form.js',
    );

    return $build;
  }
  else {
    return t('There are no products in your cart. Please add one or more products before checking out.');
  }
}

/**
 * Page callback: Facilitates payment for an order and gateway.
 *
 * @param string $gateway
 *   The payment gateway to use.
 *
 * @see ms_core_menu()
 */
function ms_core_checkout_payment_page($gateway) {
  $gateway_info = ms_core_get_payment_gateway($gateway);
  // Stop the caching.
  $GLOBALS['conf']['cache'] = FALSE;

  if (!$order = ms_core_load_session_order()) {
    // The order wasn't loaded: Error
    return t('There was an error with the checkout.');
  }
  if ($order->status != 'checkout') {
    // The order is not in checkout and shouldn't be here
    return t('This order has already been through Checkout.');
  }

  $order->gateway = $gateway;
  $order->save();

  $build['#attached']['css'] = array(
    drupal_get_path('module', 'ms_core') . '/css/ms_core.checkout.css',
    drupal_get_path('module', 'ms_core') . '/css/ms_core.css',
  );

  $build['content'] = array(
    'ms_checkout_page' => array(
      '#prefix' => "<div id='ms-core-checkout-payment-page-wrapper'>",
      '#suffix' => "</div>",
      'ms_checkout_steps' => array(
        '#markup' => theme('ms_core_checkout_steps', array('steps' => ms_core_get_checkout_steps($order), 'current' => 'payment')),
      ),
    ),
  );
  $build['content']['ms_checkout_page']['ms_order_contents'] = array(
    '#markup' => ms_core_get_order_details_table($order),
  );
  $checkout_form = drupal_get_form($gateway_info['checkout_form'], $order);
  $checkout_form['#action'] = url('ms/checkout/payment/' . $gateway);
  $build['content']['ms_checkout_page']['ms_checkout_form'] = $checkout_form;
  return $build;
}

/**
 * Page callback: Allows for resuming orders in checkout.
 *
 * @param string $order_key
 *   The unique order key.
 *
 * @see ms_core_menu()
 */
function ms_core_resume_checkout_page($order_key) {
  global $user;
  $order = ms_core_order_load_by_key($order_key);
  if ($user->uid AND $user->uid == $order->uid) {
    return ms_core_checkout_page($order->order_key);
  }
  else {
    drupal_access_denied();
  }
}

/**
 * Page callback: Shows the Shopping Cart Page.
 *
 * @see ms_core_menu()
 */
function ms_core_cart_page() {
  $build = array();
  $content = '';

  // Add the CSS.
  drupal_add_css(drupal_get_path('module', 'ms_core') . '/css/ms_core.css');

  // Stop the caching.
  $GLOBALS['conf']['cache'] = FALSE;

  $is_cart = TRUE;
  $order = ms_core_load_session_order();
  if ($order && $order->status == 'checkout') {
    $cart = $order;
    $is_cart = FALSE;
  }
  else {
    $cart = ms_core_get_cart();
  }

  if ($cart) {
    $content = ms_core_get_order_details_table($cart, TRUE);
    $fields = ms_core_get_cart_fields($cart);
    $build_fields = array();

    foreach ($fields as $field) {
      if (!isset($field['type']) || $field['type'] != 'form') {
        $build_fields[$field['id']] = array(
          '#type' => 'fieldset',
          '#title' => check_plain($field['title']),
          '#collapsible' => TRUE,
          '#collapsed' => FALSE,
        );
        $build_fields[$field['id']][$field['id'] . '_html'] = array(
          '#type' => 'item',
          '#markup' => $field['html'],
        );
      }
      else {
        $build_fields[$field['id']] = array(
          '#type' => 'fieldset',
          '#title' => check_plain($field['title']),
          '#collapsible' => TRUE,
          '#collapsed' => FALSE,
        );
        $build_fields[$field['id']]['form'] = drupal_get_form($field['html']);
      }
    }

    $content .= drupal_render($build_fields);

    $redirect = variable_get('ms_core_continue_shopping_path', '');

    if (isset($_GET['ref'])) {
      $redirect = $_GET['ref'];
    }

    $content .= "<div class='ms_cart_field_div'>";
    $continue_shopping_button = drupal_get_form('ms_core_get_continue_shopping_button', $redirect);
    $content .= "<div class='ms_cart_left'>" . drupal_render($continue_shopping_button) . "</div>";

    if (count($cart->products)) {
      $checkout_button = drupal_get_form('ms_core_get_checkout_button');
      $content .= "<div class='ms_cart_right'>" . drupal_render($checkout_button) . "</div>";
    }
    $content .= "<div style='clear:both;'></div>";
    $content .= "</div>";
  }
  else {
    $content = t('There are currently no products in your shopping cart.');
  }

  $build['content']['ms_core_cart_contents']['#markup'] = $content;

  return $build;
}

/**
 * Page callback: Removes a product from the cart, then redirects.
 *
 * @param int $pid
 *   The product id.
 */
function ms_core_cart_remove_page($pid) {
  $order = ms_core_load_session_order();
  $is_cart = TRUE;
  if ($order && $order->status == 'checkout') {
    $cart = $order;
    $is_cart = FALSE;
  }
  else {
    $cart = ms_core_get_cart();
  }

  $product = $cart->products[$pid];

  if ($is_cart && isset($product->cart_product_id)) {
    ms_core_remove_cart_product($product, $cart);
    drupal_goto($_GET['destination']);
  }
  elseif (!$is_cart && isset($product->order_product_id)) {
    ms_core_remove_order_product($product, $cart);
    drupal_goto($_GET['destination']);
  }
  else {
    drupal_not_found();
  }
}

/**
 * Page callback: Removes an adjustment from the cart, then redirects.
 *
 * @param string $adjustment_id
 *   The adjustment id.
 */
function ms_core_cart_remove_adjustment_page($adjustment_id) {
  // @todo - Support removing from orders that are in the session and in
  // checkout status.
  $cart = ms_core_get_cart();

  foreach ($cart->adjustments as $adjustment) {
    if ($adjustment->id == $adjustment_id) {
      if ($adjustment->optional) {
        ms_core_remove_cart_adjustment($adjustment);
        drupal_goto();
      }
    }
  }

  drupal_not_found();
}

/**
 * Page callback: Shows the default thankyou page.
 *
 * @see ms_core_menu()
 */
function ms_core_thankyou_page() {
  // Stop the caching.
  $GLOBALS['conf']['cache'] = FALSE;

  // Load some variables.
  global $user;

  if (!isset($_SESSION['ms_oid']) OR !$order = ms_core_order_load($_SESSION['ms_oid'])) {
    $order_key = arg(2);
    if ($order_key && $order = ms_core_order_load_by_key($order_key) && !empty($order->data['allow_key_login'])) {
      // Remove the allow_key_login data property.
      unset($order->data['allow_key_login']);
      ms_core_order_save($order);
      $order = ms_core_order_load($order->oid);
    }
    else {
      ms_core_log_error('ms_core', 'Unable to load order for thankyou page. Order: !order Session: !session',
        array('!order' => ms_core_print_r($order), '!session' => ms_core_print_r($_SESSION)));
      return t('There was an error loading the order. Please contact a site administrator.');
    }
  }

  $account = user_load($order->uid);

  ms_core_log('ms_core', 'New Thank You Page has been received. Here are the details for it: Order: !data User: !vars',
    array('!data' => ms_core_print_r($order), '!vars' => ms_core_print_r($user)));

  // Log the User In?
  if (!$user->uid) {
    if (variable_get('ms_core_auto_login', FALSE) && empty($order->data['disable_auto_login'])) {
      if ($order->uid) {
        // Make sure the user isn't blocked or pending admin approval.
        if ($account->status == 1) {
          ms_core_log('ms_core', 'Logging in a user on thank-you page: !account',
            array('!account' => ms_core_print_r($account)));
          $user = $account;
          user_login_finalize();
        }
        else {
          ms_core_log_error('ms_core', 'The user @user could not be automatically logged in because their account is not yet active.
            You will need to change the !user_settings so that admin approval is not required.',
            array('@user' => $account->name, '!user_settings' => l(t('User Settings'), 'admin/config/people/accounts')));
        }
      }
    }
  }

  // Set the messages in the order.
  ms_core_show_order_messages($order);

  // Invoke the thankyou page hook.
  module_invoke_all('ms_thankyou', $order);

  // Redirect to the order specific thank-you page if set.
  foreach ($order->products as $product) {
    if (!empty($product->data['thankyou_path'])) {
      drupal_goto($product->data['thankyou_path']);
    }
  }

  // Redirect to the Thankyou Page if set.
  if ($path = ms_core_variable_get('ms_core_thankyou_path', '', $order)) {
    // Redirect to the thank-you page specified in the settings for MS Core.
    drupal_goto($path);
  }

  // Otherwise, print the default thank-you page content.
  $content = variable_get('ms_core_thankyou_page_template',
"<p>Thank you for your purchase, [user:name]! Your payment has been received and your order details are below:</p>
<br />
<p>Order # [ms_core_order:orderId]</p>
<p>Order Status: [ms_core_order:orderStatus]</p>
<p>Payment: [ms_core_payment:paymentAmount] - [ms_core_payment:paymentDate]</p>
<p>Payment Method: [ms_core_payment:gatewayName]</p>
<br />
<p>Please print a copy of this page for your records.</p>
");
  $payment = ms_core_get_last_payment($order);

  // Replace the Tokens.
  $content = token_replace($content,
    array(
    'ms_core_order' => $order,
    'ms_core_payment' => $payment,
    'user' => $account,
  ));

  $build['content'] = array(
    '#attached' => array(
      'css' => array(
        drupal_get_path('module', 'ms_core') . '/css/ms_core.checkout.css',
      ),
    ),
    'ms_checkout_steps' => array(
      '#markup' => theme('ms_core_checkout_steps', array('steps' => ms_core_get_checkout_steps($order), 'current' => 'thankyou')),
    ),
    'ms_thankyou_text' => array(
      '#markup' => $content,
    ),
  );
  return $build;
}

/**
 * AJAX callback: Autocompletes a User Name.
 *
 * @param string $name
 *   The user name string to match.
 *
 * @see ms_core_menu()
 */
function ms_core_autocomplete_user($name = '') {
  $matches = array();
  if ($name) {
    $result = db_query("SELECT name FROM {users}");
    foreach ($result as $account) {
      $possible_values[] = $account->name;
    }
    foreach ($possible_values as $value) {
      if (preg_match("/$name/i", $value)) {
        $matches[$value] = $value;
      }
    }
  }
  drupal_json_output($matches);
}

/**
 * AJAX callback: Autocompletes a Node.
 *
 * @param string $title
 *   The node title to match.
 *
 * @see ms_core_menu()
 */
function ms_core_autocomplete_node($title = '') {
  $matches = array();
  if ($title) {
    $result = db_query("SELECT title, nid FROM {node} WHERE LOWER(title) LIKE LOWER(:title)", array(':title' => '%' . $title . '%'));
    foreach ($result as $node) {
      $matches[ms_core_create_autocomplete_key($node->nid)] = $node->title;
    }
  }
  drupal_json_output($matches);
}

/**
 * AJAX callback: Autocompletes a Product Name.
 *
 * @param string $name
 *   The product name to match.
 *
 * @see ms_core_menu()
 */
function ms_core_autocomplete_product($name = '') {
  $matches = array();
  if ($name) {
    $products = ms_core_get_module_products();
    foreach ($products as $key => $product) {
      if (preg_match("/$name/i", $product->module_title . ' - ' . $product->name)) {
        $matches[$key] = $product->module_title . ' - ' . $product->name;
      }
    }
  }
  drupal_json_output($matches);
}

/**
 * AJAX callback: Autocompletes a role name.
 *
 * @param string $string
 *   The role name to match.
 *
 * @see ms_core_menu()
 */
function ms_core_autocomplete_role($string) {
  $matches = array();
  $result = db_query("SELECT name FROM {role} WHERE name LIKE :string",
    array(':string' => '%' . $string . '%'));
  foreach ($result as $row) {
    $matches[$row->name] = $row->name;
  }
  print drupal_json_encode($matches);
  exit;
}

/**
 * Page callback: Downloads a CSV file.
 *
 * @param string $id
 *   The CSV id.
 *
 * @see ms_core_menu()
 */
function ms_core_csv_page($id) {
  $csv_data = cache_get('ms_core_csv_' . $id, 'cache');

  if (!$csv_data) {
    drupal_set_message(t("The CSV data could not be retreived.
      It's possible the data might have expired.
      Refresh the report page and try to retrieve the CSV file again."), 'error');
    drupal_not_found();
    exit();
  }
  else {
    ob_end_clean();
    $http_headers = array(
      'Pragma' => 'no-cache',
      'Expires' => '0',
      'Cache-Control' => 'no-cache, must-revalidate',
      'Cache-Control' => 'private',
      'Content-Transfer-Encoding' => 'binary',
      'Content-Length' => strlen($csv_data->data),
      'Content-Disposition' => 'attachment; filename="' . $id . '-' . REQUEST_TIME . '.csv"',
      'Content-type' => 'text/csv',
    );
    foreach ($http_headers as $name => $value) {
      $value = preg_replace('/\r?\n(?!\t| )/', '', $value);
      drupal_add_http_header($name, $value);
    }

    print $csv_data->data;
    exit();
  }
}

/**
 * Page callback: The return page from the checkout flow.
 */
function ms_core_checkout_return_page($order_key) {
  $order = ms_core_order_load_by_key($order_key);

  $gateway = ms_core_get_payment_gateway($order->gateway);

  if (!empty($gateway['return_callback']) && function_exists($gateway['return_callback'])) {
    $result = call_user_func($gateway['return_callback'], $order);
    if ($result) {
      drupal_goto('ms/thankyou');
    }
    else {
      // Go back to checkout.
      $order->status = 'checkout';
      $order->save();
      ms_core_set_order_session($order);
      drupal_goto('ms/checkout');
    }
  }
  else {
    drupal_set_message(t('No callback handler specified.'), 'error');
  }

  drupal_set_message(t('There was an error with the payment. Please contact a site administrator.'), 'error');
  drupal_goto();
}
