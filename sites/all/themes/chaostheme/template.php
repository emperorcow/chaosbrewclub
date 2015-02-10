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
	$since = 0;

	// Check if this user has a membership
	if (is_array($account->ms_memberships)) {
		foreach ($account->ms_memberships as $membership) {
			// Only look at the active membership
			if ($membership->status == 'active') {
				// Check the start date
				$since = $membership->start_date;
			}
		}
	}

	// Determine membership level
	$membership_level_name = _chaos_reservations_get_user_level($account);

	// If they don't have an active membership, just use their join date
	if (!($since > 0)) {
		$membership_level_name = 'Web-only';
		$since = $account->created;
	}

	// If we've got a membership to include, do so
	$vars['membership_level'] = $membership_level_name;
	$vars['member_since'] = format_date($since, 'custom', 'M j, Y');

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
