function hashLink(index)
					{
						document.location.hash="item-"+index;
						return false;
						// Link from More link in verite timeline down to chronitem in table
					}

					$(document).ready(function() {


						$( "#accordion" ).accordion({
							collapsible: true,
							fillSpace: true,
							autoHeight: false
						});
	
						$( ".resizable" ).resizable();
	
						$("a.eventSourceLink").click(function(){
							$(this).next("ul.eventSourceCollections").slideToggle();
							return false;
						});


						$("a.colorbox").each(function(){
						  $(this).colorbox({ 
							rel: $(this).attr("data-group"),
							maxHeight: "100%",
							maxWidth: "100%",
							current: "{current} of {total}",
							previous: "&laquo; prev",
							next: "next &raquo;" 
							});
						});

					});