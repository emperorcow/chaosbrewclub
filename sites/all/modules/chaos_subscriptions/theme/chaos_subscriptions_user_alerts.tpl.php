<fieldset>
<legend class='user_subscription_legend'>Forums</legend>
<table class='forum_subscription_list'>
	<?php foreach($forums as $term) { ?>
		<tr class='category'><th colspan=2 class='chaos_subscriptions_forum'><?php print $term["name"]; ?></th></tr>
			<?php if(isset($term["children"][0])) { 
					$i = 0;
					foreach($term["children"] as $child) { ?>
				<tr <?php if($i % 2 == 0) { print "class='odd'"; } else { print "class='even'"; } $i++; ?>>
					<td class='chaos_subscriptions_forum'><?php print $child["name"]?></td>
					<td class='chaos_subscriptions_link'><?php print chaos_subscriptions_get_flag_link('subscribe_forum', $child["tid"], $user) ?></td>
				</tr>
					<?php if(isset($child["children"][0])) { 
						foreach($child["children"] as $subchild) { ?>
				<tr <?php if($i % 2 == 0) { print "class='odd'"; } else { print "class='even'"; } $i++; ?>>
					<td class='chaos_subscriptions_forum'><?php print $child["name"]?></td>
					<td class='chaos_subscriptions_link'><?php print chaos_subscriptions_get_flag_link('subscribe_forum', $child["tid"], $user) ?></td>
				</tr>
						<?php } ?>
					<?php } ?>
					<?php } ?>
			<?php } ?>
	<?php } ?>
</table>
</fieldset>
