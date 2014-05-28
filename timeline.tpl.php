<?php
$thumbCount = 0;
$cbCount = 0;
?>

<div class="timeline-wrapper">

<!-- Bio Text --->
	
	<div class="abstractBio">
		<div id="personPortrait">
		
			<?php echo '<a class="colorbox cboxElement" rel="colorbox" href="' . $dulmaster_headshot . '">'; ?>
			
				<?php echo '<img class="portrait subtleBorder smallShadow" property="schema:image" src="' . $dulmaster_headshot . '" alt="' . $dulmaster_name . '">'; ?>
		
			</a>
		</div>
	
		<h1 class="splashTitle" property="schema:name"><?php echo $dulmaster_name ?></h1>

		<div class="personAbout" property="schema:description">
	
			<?php echo $dulmaster_abstract ?>
	
		</div>

		<div class="clear"></div>


	</div>
	
	



<!-- Navigation Links -->
	
	<ul class="mainLinks">
		<li><a href="#timeline-embed" onclick="_gaq.push(['_trackEvent', 'eacNav','timelineLink']);">Timeline</a></li>
		<li><a href="#collections" onclick="_gaq.push(['_trackEvent', 'eacNav','collectionsLink']);">Collections</a></li>
		<li><a href="#biography" onclick="_gaq.push(['_trackEvent', 'eacNav','biogHistLink']);">Biographical History</a></li>
 	</ul>
 	
 	<div class="clear"></div>





<!--- Timeline Embed --->
	
	<div class="iframe-timeline" id="timeline-embed">
	
		<?php echo '<iframe src="http://embed.verite.co/timeline/?source=' . $timeline_key . '&amp;font=Georgia-Helvetica&amp;maptype=toner&amp;lang=en&amp;height=450" width="100%" height="450" frameborder="0"></iframe>'; ?>
	
	</div>
	
	


	<!-- Entries: Column 1 -->
	
	<div class="grid-8 alpha">

		<h2 id="biography" class="bioTitle">Biographical History</h2>

		<?php

		foreach ($data_timeline['feed']['entry'] as $item) {
	
	
			// Normal entries
			if ($item['gsx$startdate']['$t'] != "") {
		
				$thumbCount = 0;
		
				$cbCount += 1;
		
				echo '<div class="item-wrapper">';
		
					echo '<div class="summary">';
			
						// Dates
						echo '<div class="dates">';

							// account for year only
							if (strlen($item['gsx$startdate']['$t']) == 4) {
								
								echo $item['gsx$startdate']['$t'];
								
							}
							
							else {
							
								echo date('Y M d', strtotime($item['gsx$startdate']['$t']));
								
							}
							
							// if there's an end date
							if ($item['gsx$enddate']['$t'] != "") {
								
								// account for year only
								if (strlen($item['gsx$startdate']['$t']) == 4) {
								
									echo ' &ndash; ' . $item['gsx$enddate']['$t'];
								
								}
				
								else {	
									
									echo ' &ndash; ' . date('Y M d', strtotime($item['gsx$enddate']['$t']));
									
								}
				
							}
				
						echo '</div>';
			
						// Headline
						echo '<div class="headline">';
			
							echo $item['gsx$headline']['$t'];
			
						echo '</div>';
			
					echo '</div>';
		
					echo '<div class="details">';
						
						
						// Thumbnail (if it's empty, display empty div)
						
						if ($item['gsx$mediathumbnail']['$t'] != "") {
							
							echo '<div class="timeline-thumbnail">';
			
								echo '<a class="colorbox cboxElement" data-group="colorboxgroup' . $cbCount . '" title="' . $item['gsx$mediacaption']['$t'] . '" href="' . $item['gsx$media']['$t'] . '">';
					
								echo '<img src="' . $item['gsx$mediathumbnail']['$t'] . '" alt="' . $item['gsx$mediacaption']['$t'] . '" >';
								//echo '<span class="credit">' . $item['gsx$mediacredit']['$t'] . '</span>';
					
								echo '</a>';
			
							echo '</div>';
							
							}
							
							else {
								
								echo '<div class="timeline-thumbnail">&nbsp;</div>';
								
							}
							
							
			
						// Text Description
						echo '<div class="description">';
							echo '<p>' . $item['gsx$text']['$t'] . '</p>';
						echo '</div>';
		
					echo '</div>';
		
				echo '</div>';
	
				echo '<br clear="all" />';
		
			}
	
			// Extra images
			else {
		
				$thumbCount += 1;
		
				// Thumbnail
				echo '<div class="clipwrapper">';
					echo '<div class="clip">';
				
						echo '<a class="colorbox cboxElement" data-group="colorboxgroup' . $cbCount . '" title="' . $item['gsx$mediacaption']['$t'] . '" href="' . $item['gsx$media']['$t'] . '">';
					
						echo '<img src="' . $item['gsx$mediathumbnail']['$t'] . '" alt="' . $item['gsx$mediacaption']['$t'] . '" >';
				
						echo '</a>';
				
					echo '</div>';
				echo '</div>';
		
				if ($thumbCount % 4 == 0) {
		
					echo '<br clear="all" />';
				
				}
		
			}
	
		}
		
		?>
		
	</div>
	
	
	<!-- RELATIONS: Column 2 -->
	
	<div class="grid-4 omega" id="sidebar">
		
		<div id="accordion" style="max-height: 600px;">
			
			<!-- Collections Accordian -->
			
			<?php if(isset($data_associatedcollections['feed']['entry'][0]['gsx$eacurl']['$t'])) { ?>
			
			
			<h3 id="collections"><a href="#">Associated Collections</a></h3>
			<div>
				<ul id="collections_list">
			
				<?php
			
				foreach ($data_associatedcollections['feed']['entry'] as $item) {
				
					echo '<li>';
						
						echo '<a href="' . $item['gsx$eacurl']['$t'] . '" class="linkFindingAid">' . $item['gsx$eactitle']['$t'] . '</a><br>';
							
						echo '<span class="collectionDescription">' . $item['gsx$eacdescription']['$t'] . '</span>';
						
					echo '</li>';


				}

	
				?>
			
								
				</ul>
    		</div>
    		
    		<?php } ?>
    		
    		<!-- People Accordian -->
    		
    		<?php if(isset($data_people['feed']['entry'][0]['gsx$eacurl']['$t'])) { ?>
    		
			<h3 id="people"><a href="#">People</a></h3>
			<div>
				
				<ul id="people_list">
				    
				<?php
			
				foreach ($data_people['feed']['entry'] as $item) {
				
					echo '<li>';
						
						echo '<a href="' . $item['gsx$eacurl']['$t'] . '" class="linkFindingAid">' . $item['gsx$eactitle']['$t'] . '</a> ' . $item['gsx$eacrelation']['$t'];
						
					echo '</li>';


				}

	
				?>
				    
				    		
				</ul>
    		</div>
    		
    		<?php } ?>
            
    		
    		<!-- Corporate Bodies Accordian -->
    		
    		<?php if (isset($data_corporatebodies['feed']['entry'][0]['gsx$eacurl']['$t'])) { ?>
    		
			<h3 id="corporate_bodies"><a href="#">Corporate Bodies</a></h3>
			<div>
				<ul id="corporate_bodies_list">
				
				<?php
			
				foreach ($data_corporatebodies['feed']['entry'] as $item) {
				
					echo '<li>';
						
						echo '<a href="' . $item['gsx$eacurl']['$t'] . '" class="linkFindingAid">' . $item['gsx$eactitle']['$t'] . '</a> ' . $item['gsx$eacrelation']['$t'];
						
					echo '</li>';


				}

	
				?>
					
				</ul>
    		</div>
    		
    		<?php } ?>
            
		
		</div>
		
	</div>
	
</div>
