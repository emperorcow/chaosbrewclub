<?php

function chaostheme_preprocess_flag(&$vars) {
	if($vars['flag']->name == 'subscribe_forum' or $vars['flag']->name == 'subscribe_thread') {
		$image_file = path_to_theme() . '/images/flag-' . ($vars['action'] == 'flag' ? 'off' : 'on') . '.png';
		if (file_exists($image_file)) {
			$vars['link_text'] = '<img src="' . base_path() . $image_file . '" />';
		}
	}
}

function chaostheme_preprocess_html(&$vars) {
	drupal_add_css('//fonts.googleapis.com/css?family=Oswald:300,400', array('type' => 'external'));
}

function chaostheme_form_alter(&$form, &$form_state, &$form_id) {
	if(isset($form['ms_membership'])) {
		if($form['ms_membership']['mpid']['#type'] == 'radios') {
			//$form['#theme'][] = 'chaostheme_pre_render';
		}
	}

	if($form_id == 'role_delegation_roles_form') {
		drupal_set_title("Edit Roles: ".$form['account']['#value']->name);
	}
	if($form_id == 'user_profile_form') {
		drupal_set_title("Edit User: ".$form['#user']->name);
	}
}

/* The following is a terrible god awful hack.  If your inheriting this from me
   I'm sorry and CHAOS owe's you another beer.  I did this because I couldn't
   figure out a half decent way to do this elegantly without hard coding it. 
   So... I'm sorry 
             - Lucas
   */
/*
function chaostheme_radios($element) {
	if($element['element']['#parents'][0] == 'mpid') {

		$html = <<<END
		<table class='ms-membership-purchase'>
			<thead>
				<tr>
					<td> </td>
					<td>Monthly</td>
					<td>Annual</td>
				</tr>
			</thead>
			<tbody>
				<tr class='web_member'>
					<td class='label'>Web Only Member</td>
					<td class='ms-membership-item' colspan='2'><input type='radio' id='edit-mpid-0' name='mpid' value='0' class='form-radio' /><label class='option' for='edit-mpid-0'>Free</label></td>
				</tr>
				<tr class='trial_membership'>
					<td class='label'>Trial Membership</td>
					<td class='ms-membership-item' colspan='2'><input id='edit-mpid-7'class='form-radio' type='radio' value='7' name='mpid'><label class='option' for='edit-mpid-7'>$25.00 for 1 Month</label></td>
				</tr>
				<tr class='friend_of_chaos'>
					<td class='label'>Friend of CHAOS</td>
					<td class='ms-membership-item'><input id='edit-mpid-1'class='form-radio' type='radio' value='1' name='mpid'><label class='option' for='edit-mpid-1'>$21.00 every 3 Months</label></td>
					<td class='ms-membership-item'><input id='edit-mpid-4'class='form-radio' type='radio' value='4' name='mpid'><label class='option' for='edit-mpid-4'>$77.00 every Year</label></td>
				</tr>
				<tr class='apprentice_membership'>
					<td class='label'>Apprentice Membership</td>
					<td class='ms-membership-item'><input id='edit-mpid-2'class='form-radio' type='radio' value='2' name='mpid'><label class='option' for='edit-mpid-2'>$15.00 every Month</label></td>
					<td class='ms-membership-item'><input id='edit-mpid-5'class='form-radio' type='radio' value='5' name='mpid'><label class='option' for='edit-mpid-5'>$165.00 every Year</label></td>
				</tr>
				<tr class='brewer_membership'>
					<td class='label'>Brewer Membership</td>
					<td class='ms-membership-item'><input id='edit-mpid-3'class='form-radio' type='radio' value='3' name='mpid'><label class='option' for='edit-mpid-3'>$26.00 every Month</label></td>
					<td class='ms-membership-item'><input id='edit-mpid-6'class='form-radio' type='radio' value='6' name='mpid'><label class='option' for='edit-mpid-6'>$286.00 every Year</label></td>
				</tr>
			</tbody>
		</table>
END;

		return _chaostheme_condense_html($html);
	} else {
		return theme_radios($element);
	}
}

function chaostheme_ms_membership_user_page_alter(&$form) {

	if(isset($form['ms_membership']['#title'])) {
		if($form['ms_membership']['#title'] == 'Purchase Membership') {;

			$html = <<<END
	<table class="ms-membership-purchase">
		<thead>
			<tr>
				<td> </td>
				<td>Monthly</td>
				<td>Annual</td>
			</tr>
		</thead>
		<tbody>
			<tr class="trial_membership">
				<td class="label">Trial Membership</td>
				<td class="ms_membership_plan_purchase_link-7 ms-membership-item" colspan="2"><a href="/membership/purchase/7">$25.00 for 1 Month</a></td>
			</tr>
			<tr class="friend_of_chaos">
				<td class="label">Friend of CHAOS</td>
				<td class="ms_membership_plan_purchase_link-1 ms-membership-item"><a href="/membership/purchase/1">$21.00 every 3 Months</a></td>
				<td class="ms_membership_plan_purchase_link-4 ms-membership-item"><a href="/membership/purchase/4">$77.00 every Year</a></td>
			</tr>
			<tr class="apprentice_membership">
				<td class="label">Apprentice Membership</td>
				<td class="ms_membership_plan_purchase_link-2 ms-membership-item"><a href="/membership/purchase/2">$15.00 every Month</a></td>
				<td class="ms_membership_plan_purchase_link-5 ms-membership-item"><a href="/membership/purchase/5">$165.00 every Year</a></td>
			</tr>
			<tr class="brewer_membership">
				<td class="label">Brewer Membership</td>
				<td class="ms_membership_plan_purchase_link-3 ms-membership-item"><a href="/membership/purchase/3">$26.00 every Month</a></td>
				<td class="ms_membership_plan_purchase_link-6 ms-membership-item"><a href="/membership/purchase/6">$286.00 every Year</a></td>
			</tr>
		</tbody>
	</table>
END;

			$form['ms_membership'] = array(
				'#type' => 'fieldset',
				'#title' => t('Purchase Membership'),
			);
			$form['ms_membership']['table'] = array(
				'#type' => 'markup',
				'#markup' => _chaostheme_condense_html($html),
			);
		}
	}
}
*/
function _chaostheme_condense_html($html) {
	$search = array(
		'/\>[^\S ]+/s', //strip whitespaces after tags, except space
		'/[^\S ]+\</s', //strip whitespaces before tags, except space
		'/(\s)+/s'  // shorten multiple whitespace sequences
	);
	$replace = array(
		'>',
		'<',
		'\\1'
	);

	return preg_replace($search, $replace, $html);
}

/**
 * Implement template_preprocess_author_pane().
 * Add membership level info to the author pane
 */
function chaostheme_preprocess_author_pane(&$vars) {
	$account = $vars['account'];
	// Check if this user has a membership
	if (is_array($account->ms_memberships)) {
		foreach ($account->ms_memberships as $membership) {
			// Only look at the active membership
			if ($membership->status == 'active') {
				// Check the start date
				$since = $membership->start_date;

				// Find the name of the membership
				$membership_plan = ms_products_plan_load($membership->sku);
				if ($membership_plan) {
					$membership_level_name = $membership_plan->name;
				}
			}
		}
	}

	// If we've got a membership to include, do so
	if ($since > 0) {
		$vars['membership_level'] = $membership_level_name;
		$vars['member_since'] = format_date($since, 'custom', 'M j, Y');
	}

	// Hide the default "Joined" line
	unset($vars['joined']);

	// Use our template, not the one from advanced forum
	if (($i = array_search('advanced_forum_author_pane', $vars['theme_hook_suggestions'])) !== FALSE) {
		unset($vars['theme_hook_suggestions'][$i]);
	}
	// Re-set the theme name
	$vars['theme_hook_suggestion'] = 'author-pane';
}


function chaostheme_preprocess_page(&$vars, $hook) {
	if($vars["theme_hook_suggestions"][0] == "page__forum") {
		$vars["forum_breadcrumb"] = _get_forum_breadcrumb();
	} elseif (isset($vars["node"])) {
		if($vars["node"]->type == 'forum' ||
		   $vars["node"]->type == 'poll' ||
		   $vars["node"]->type == 'project') {
			$vars['theme_hook_suggestions'][0] = 'page__node__forum';
			$vars["forum_breadcrumb"] = _get_forum_breadcrumb();
		}	
	}
	if(arg(0) == 'user' && is_numeric(arg(1))) {
		if(user_access('administer users')) {
			$user = user_load(arg(1));
			drupal_set_title($user->name);
		}
	}
}

function _get_forum_breadcrumb() {
	$current = drupal_get_breadcrumb();

	if (count($current) == 1) {
		// Rename Forums -> Discussions
		$current[0] = "<a href='/forums'>Discussion Index</a>";
	} else {
		unset($current[0]);
		// Rename Forums -> Discussions
		$current[1] = str_replace("Forums", "Discussion Index", $current[1]);
	}
	return join(" <span class='separator'>&gt;</span> ", $current);
}

function chaostheme_fullcalendar_classes_alter(&$classes, $entity) {
	if($entity->type == 'event') {
		$term = taxonomy_term_load($entity->field_event_type[$entity->language][0]['tid']);
		$classes[] = 'event_'.strtolower($term->name);
	}
}
