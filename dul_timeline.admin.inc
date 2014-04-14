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
		t('Timeline Title'),
		t('Actions'),
	);
	$rows = array();
	foreach ($dbResult as $o) {		// $o is my fancy notation for 'object'
		$rows[] = array(
			$o->tid,
			$o->title,		// or whatever name used to represent the timeline name column
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
	$form['timeline_title'] = array(
		'#type' => 'textfield',
		'#description' => t('The title of this collections timeline'),
		'#title' => t('Title'),
		'#default_value' => $timeline->title,
		'#required' => TRUE,
		);

	// 
	#$form['dul_master_num'] = array(
	#	);

	## You will also need a textfield for the custom URL for this
	$form['url_alias'] = array(
		'#type' => 'textfield',
		'#required' => TRUE,
		'#title' => t('URL'),
		'#default_value' => $timeline->url_alias,
		);

	$form['datasource_row'] = array(
		'#type' => 'textfield',
		'#description' => t('0-index position in the Google Spreadsheet where this record resides'),
		'#title' => t('Datasource Row'),
		'#default_value' => $timeline->datasource_row,
		'#required' => TRUE,
		);

	$form['tid'] = array(
		'#type' => 'hidden',
		'#value' => $timeline->tid,
		);

	$form['actions'] = array(
		'#type' => 'actions',
		);
	$form['actions']['submit'] = array(
		'#type' => 'submit',
		'#value' => 'Submit',
		// default name of the element is "op"
		// @see https://api.drupal.org/api/drupal/developer!topics!forms_api_reference.html/7
		);
}

/**
 * submit callback for timeline edit form
 */
function dul_timeline_timeline_form_submit($form, &$form_state) {
	// save changes to the database.
	// db_merge() - handles both insert and update
	// @see https://api.drupal.org/api/drupal/includes!database!database.inc/function/db_merge/7
}

/**
 * Setting administrative for Timeline
 */
function dul_timeline_admin_settings($form, &$form_state) {
	# GET THE VARIABLE SETTINGs first
	// $dul_masterkey = variable_get('dul_timeline.dul_masterkey');
	// take that value and use it as as #default_value for the appropriate element below

	# we'll need a element 'master key'
	$form['dul_masterkey'] = array(
		'#type' => 'textfield',
		'#default_value' => '',			// use "variable_get()" to fetch this value
		'#required' => TRUE,
		'#title' => 'DUL Master Key',
		);

	$form['actions'] = array(
		'#type' => 'actions',
		);
	$form['actions']['submit'] = array(
		'#type' => 'submit',
		'#value' => 'Submit',
		// default name of the element is "op"
		// @see https://api.drupal.org/api/drupal/developer!topics!forms_api_reference.html/7
		);

	return $form;
}

function dul_timeline_admin_setting_submit($form, &$form_state) {
	// variable_set('namespace.somevarname', 'some value');\
	// one of the keys in the $form_state array is "values", which
	// represents all of the form elements, as you named in the 'dul_timeline_admin_settings' callback
	$dul_masterkey = $form_state['values']['dul_masterkey'];

	// variable_set('dul_system.myfancyvariable', 'whatever')
}