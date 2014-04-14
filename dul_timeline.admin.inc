<?php

function dul_timeline_admin_overview() {
	# this function needs to return either a translated string, like:
	# return t("This is my page"),
	# 
	# or, it needs to return what is called a "render array".
	# consider:
	# -----------------------------------------------------
	//	$page['simple_markup'] = array(
	//		'#type' => 'markup',
	//		'#markup' => '<div>This is my markup</div>',
	//	);
	//	return $page;
	# -----------------------------------------------------
	# Render Arrays make life easier for theme developers 
	# as they can create specialized themes as needed.
	# --
	# for this function, we need to return a list of timeline entries:
	# Step 1: database fetch (I'll leave the database as an exercise)
	# Step 2: create table output.


	# STEP 1:
	# database fetch -- exercise for student :)

	# STEP 2:
	$header = array(
		t('ID'),
		t('Timeline Name'),
		t('Machine Name'),
		t('Actions'),
	);
	$rows = array();
	foreach ($dbResult as $o) {		// $o is my fancy notation for 'object'
		$rows[] = array(
			$o->id,
			$o->timeline_name,		// or whatever name used to represent the timeline name column
			$o->timeline_machine_id,
			l(t('edit'), 'admin/config/timeline/edit/' . $o->id),
			);
	}
	# now create the render array entry
	$page['timeline_table'] = array(
		# you can use either the '#type' or "#theme" attribute, but not both
		'#theme' => 'table',
		'#header' => $header,
		'#rows' => $rows,
		'#empty' => t('No Timeline entries have been created'),
	);
	return $page;
}

/**
 * page callback for data entry form for timeline record
 */
function dul_timeline_timeline_form($form, &$form_state, $timeline) {

}

/**
 * submit callback for timeline edit form
 */
function dul_timeline_timeline_form_submit($form, &$form_state) {

}