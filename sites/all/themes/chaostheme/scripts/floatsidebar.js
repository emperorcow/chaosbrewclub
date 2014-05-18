(function ($) {
$(document).ready(function(){  
	var sidebartop = $("#region-sidebar").offset().top - parseFloat($("#region-sidebar").css('marginTop').replace(/auto/, 0)) - 70;
	$(window).scroll(function () {  
		var offset = $(document).scrollTop();

		if(offset >= sidebartop && $(window).width() > 1000) {
			$("#region-sidebar").addClass('fixed');
		} else {
			$("#region-sidebar").removeClass('fixed');
		}

	});  
	if($('#admin-menu').length) {
		$("#menu-bar").css('top', '29px');
		$("#columns").css('margin-top', '29px');
		$(window).scroll(function () {
			var offset = $(document).scrollTop();
	
			if(offset >= 29) {
				$("#menu-bar").css('top', '0px');
				$("#columns").css('margin-top', '0px');
			} else {
				$("#menu-bar").css('top', '29px');
				$("#columns").css('margin-top', '29px');
			}
		});
	}
});  
})(jQuery);
