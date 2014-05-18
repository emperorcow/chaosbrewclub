(function ($) {
	function runmap() {
		$('#brewhouse_img').mapster({
			fillOpacity: 1.0,
			render_highlight: {
				altImage: '/sites/all/modules/chaos_reservations/images/map-hover.jpg',
			},
			render_select: {
				altImage: '/sites/all/modules/chaos_reservations/images/map-selected.jpg',
			},
			mapKey: 'data-bay',
			singleSelect: true,
			areas: Drupal.settings.chaos_reservations_bay_selectability,
			onClick: function (e) {
				if(e.selected) {
					$('#edit-bay').val(e.key);
				} else {
					$('#edit-bay').val("0");
				}
			},
		});

		if(Drupal.settings.chaos_reservations_map_initial_select) {
			$('area.bay'+Drupal.settings.chaos_reservations_map_initial_select).mapster('set', true);
			$('#edit-bay').val(Drupal.settings.chaos_reservations_map_initial_select);
		}
	}

	Drupal.behaviors.chaos_reservations = {
		attach: function(context) {
			$('#edit-start-datepicker-popup-0', context).change(function() {
					$('#edit-end-datepicker-popup-0').val($('#edit-start-datepicker-popup-0').val());
					$('#edit-end-timepicker-popup-1').val($('#edit-start-timepicker-popup-1').val());
			});
		}
	}

	var shown = false;
	$(document).ready(function() {
		if(Drupal.settings.chaos_reservations_map_default_visibility) {
			runmap();
			$('#edit-submit').delay(700).fadeIn();
			$('#edit-cancel').delay(700).fadeIn();
			shown = true;
		} else {
			$('#reservationdiv').hide(400);
			$('#edit-submit').hide();
			$('#edit-cancel').hide();
		}
	});
	$(document).ajaxComplete(function() {
		if(!shown) {
			$('#reservationdiv').hide();
			shown = true;
		}

		runmap();

		$('#reservationdiv').slideDown(700);	
		$('#edit-submit').delay(700).fadeIn();
		$('#edit-cancel').delay(700).fadeIn();
	});
})(jQuery);
