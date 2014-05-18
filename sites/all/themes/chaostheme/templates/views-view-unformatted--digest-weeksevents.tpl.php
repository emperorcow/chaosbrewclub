<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>
<?php if (!empty($title)): ?>
<b><?php print $title; ?></b>
<?php endif; ?>
<ul>
<?php foreach ($rows as $id => $row): ?>
	<li><?php print $row; ?></li>
<?php endforeach; ?>
</ul>
