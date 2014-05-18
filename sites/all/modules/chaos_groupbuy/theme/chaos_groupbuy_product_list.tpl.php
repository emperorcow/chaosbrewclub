<div id="groupbuy">
<div id="groupbuy_links_top">
	<div class='link' id="view-checkout-page">
		<a href="/ms/checkout">
			<img src="<?php print $module_path ?>/images/checkout.png"/>
		</a>
	</div>
	<div class='link' id="view-cart-modal">
		<a class="ctools-use-modal ctools-modal-chaos-groupbuy-modal-cart" href="/groupbuy/1/cart/nojs">
			<img src="<?php print $module_path ?>/images/viewcart.png"/>
		</a>
	</div>
	<div class='clearfix'></div>
</div>
<div id="groupbuy_time"> This group bulk buy will close on <span class='date'><?php print $end_date ?></span> at midnight.</div>
<div id="groupbuy_description">

	<?php print $description ?>
</div>
<h3>Pallet Status</h3>
<table id="groupbuy_pallets">
	<tbody>
<?php foreach($pallets as $num => $info) { ?>
		<tr class='pallet'>
			<td class='id'>#<?php print $num ?></td>
			<td class='bar'>
				<div id='progressbar-<?php print $num ?>'>
					<div class='progressbar-<?php print $num ?>-label progressbar-label'>
						<?php print $info['text'] ?>
					</div>
				</div>
			</td>
			<script>
				jQuery(function() {
					jQuery("#progressbar-<?php print $num ?>").progressbar({
						value: <?php print $info['percent'] ?>
					});
				});
			</script>
		</tr>
<?php } ?>
	</tbody>
</table>
<h3>Products Available</h3>
<div id="groupbuy_tabs">
	<ul>
<?php foreach($tree as $cat_id => $cat_name) { ?>
		<li><a href='#groupbuy-tabs-<?php print _chaos_groupbuy_machineize_name($cat_id) ?>'><?php print $cat_id ?></a></li>
<?php } ?>
	</ul>
<?php foreach($tree as $cat_id => $subcats) { ?>
	<div id="groupbuy-tabs-<?php print _chaos_groupbuy_machineize_name($cat_id) ?>" class="groupbuy-category">
<?php foreach($subcats as $subcat => $products) { ?>
		<div class="groupbuy-subcategory ctools-collapsible-container ctools-collapsed">
			<div class="ctools-collapsible-handle"><?php print $subcat ?></div>
			<div class="ctools-collapsible-content">
				<table>
					<colgroup>
						<col width="20%"/>
						<col width="50%"/>
						<col width="15%"/>
						<col width="15%"/>
					</colgroup>
					<thead><tr>
						<th>Item ID</th>
						<th>Product</th>
						<th>Price</th>
						<th> </th>
					</tr></thead>
					<tbody>
<?php usort($products, function($a, $b) {
		return strcmp($a['id'], $b['id']);
	});
?>
<?php for($i = 0, $s = count($products); $i < $s; $i++) { ?>
						<tr class="groupbuy-product-info <?php print ($i%2==0)? "odd" : "even"?>">
							<td class="itemid"><?php print $products[$i]['id'] ?></td>
							<td class="title"><?php print $products[$i]['title'] ?> <span class="size"><?php print $products[$i]['size'] ?></span></td>
							<td class="price"><?php print $products[$i]['price'] ?></td>
							<td class="link"><?php print $products[$i]['link'] ?></td>
						</tr>
<?php if ($products[$i]['description'] != "") { ?>
						<tr class="groupbuy-product-description <?php print ($i%2==0)? "odd" : "even"?>">
							<td colspan=4>
								<?php print $products[$i]['description'] ?>
							</td>
<?php } //If Has Description ?>
						</tr>
<?php } //Products ?>
					</tbody>
				</table>
			</div>
		</div>
		<br/>
<?php } //Subcategories ?>
	</div>
<?php } //Categories / Tree ?>
</div>
<div id="groupbuy_links_bottom">
	<div class='link' id="view-checkout-page">
		<a href="/ms/checkout">
			<img src="<?php print $module_path ?>/images/checkout.png"/>
		</a>
	</div>
	<div class='link' id="view-cart-modal">
		<a class="ctools-use-modal ctools-modal-chaos-groupbuy-modal-cart" href="/groupbuy/1/cart/nojs">
			<img src="<?php print $module_path ?>/images/viewcart.png"/>
		</a>
	</div>
	<div class='clearfix'></div>
</div>
</div>

