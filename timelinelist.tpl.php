<?php

//$myResult = db_query('SELECT * FROM {timeline} WHERE url_type = :url_type, array(':url_type' => $url_type''));

$result = db_query('SELECT url_slug, dulmaster_num, dulmaster_key FROM {timeline} n WHERE n.url_type = :url_type', array(':url_type' => $url_type));


// set timeout length
$ctx = stream_context_create(array( 
	'http' => array( 
		'timeout' => 5 
		) 
	) 
); 


?>

<div class="timeline-wrapper">
	
	<?php
	
	foreach ($result as $record) {
		
		$url_slug = $record->url_slug;
		$dulmaster_num = $record->dulmaster_num;
		$dulmaster_key = $record->dulmaster_key;
		
		// Pull in Master Google Spreadsheet as JSON
		$url_dulmaster = "http://spreadsheets.google.com/feeds/list/" . $dulmaster_key . "/od6/public/values?alt=json&amp;callback=displayContent";
		$json_dulmaster = file_get_contents($url_dulmaster, 0, $ctx);
		$data_dulmaster = json_decode($json_dulmaster, TRUE);
		
		$dulmaster_name = $data_dulmaster['feed']['entry'][$dulmaster_num]['gsx$entityname']['$t'];
		$dulmaster_headshot = 'http://library.duke.edu/digitalcollections/media/jpg/' . $data_dulmaster['feed']['entry'][$dulmaster_num]['gsx$slug']['$t'] . '/med/' . $data_dulmaster['feed']['entry'][$dulmaster_num]['gsx$portraitimage']['$t'];
		$dulmaster_abstract = $data_dulmaster['feed']['entry'][$dulmaster_num]['gsx$abstract']['$t'];
		
		$timeline_url = $GLOBALS['base_path'] . $root_path .'/' . $url_type . '/' . $url_slug;
		
		
		echo '<div class="list-item">';
		
		echo '<div class="thumbnail"><a href="' . $timeline_url . '"><img src="' . $dulmaster_headshot . '"></a></div>';
		
		echo '<h2><a href="' . $timeline_url . '">' . $dulmaster_name . '</a></h2>';

		echo $dulmaster_abstract;
		
		echo '</div>';
		
		
	}
	
	
	?>
	
	
</div>
