<?php

function dul_timeline_admin_overview() {

	// Database fetch
	$dbResult = db_query('SELECT * FROM {timeline}');

	// Table Output
	$header = array(
		t('ID'),
		t('Timeline Name'),
		t('Actions'),
	);
	$rows = array();
	foreach ($dbResult as $o) {		// $o is my fancy notation for 'object'
		$rows[] = array(
			$o->tid,
			$o->timeline_name,		// or whatever name used to represent the timeline name column
			l(t('edit'), 'admin/config/timeline/edit/' . $o->tid),
			);
	}
	
	// render array
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
function dul_timeline_timeline_admin_form($form, &$form_state, $timeline) {

if ($timeline == "new") {

	$timeline = new stdClass;
	$timeline->timeline_name = "";
	$timeline->dulmaster_key = "0Ah7VCreXiBHudFpxMGY0M0FQY1daTFVKbXNSV2ItTlE";
	$timeline->dulmaster_num = "";
	$timeline->timeline_od = "od6";
	$timeline->collections_od = "od7";
	$timeline->people_od = "od4";
	$timeline->corporate_od = "od5";
	$timeline->url_type = "";
	$timeline->url_slug = "";

}

	$form['timeline_name'] = array(
		'#type' => 'textfield',
		'#description' => t('The name of this collections timeline'),
		'#title' => t('Title'),
		'#default_value' => $timeline->timeline_name,
		'#required' => TRUE,
		);
		
	$form['dulmaster_key'] = array(
		'#type' => 'textfield',
		'#description' => t('The ID of the master spreadsheet'),
		'#title' => t('Master Key'),
		'#default_value' => $timeline->dulmaster_key,
		'#required' => TRUE,
		);
		
	$form['dulmaster_num'] = array(
		'#type' => 'textfield',
		'#description' => t('0-index position in the Google Spreadsheet where this record resides'),
		'#title' => t('Master Row Number'),
		'#default_value' => $timeline->dulmaster_num,
		'#required' => TRUE,
		'#size' => 4,
		);
	
	$form['timeline_od'] = array(
		'#type' => 'textfield',
		'#description' => t('Variable for timeline data -- usually od6'),
		'#title' => t('Timeline OD Variable'),
		'#default_value' => $timeline->timeline_od,
		'#required' => TRUE,
		'#size' => 4,
		);
		
	$form['collections_od'] = array(
		'#type' => 'textfield',
		'#description' => t('Variable for collections data -- usually od7'),
		'#title' => t('Collections OD Variable'),
		'#default_value' => $timeline->collections_od,
		'#required' => TRUE,
		'#size' => 4,
		);
		
	$form['people_od'] = array(
		'#type' => 'textfield',
		'#description' => t('Variable for person data -- usually od4'),
		'#title' => t('People OD Variable'),
		'#default_value' => $timeline->people_od,
		'#required' => TRUE,
		'#size' => 4,
		);
		
	$form['corporate_od'] = array(
		'#type' => 'textfield',
		'#description' => t('Variable for corporate data -- usually od5'),
		'#title' => t('Corporate OD Variable'),
		'#default_value' => $timeline->corporate_od,
		'#required' => TRUE,
		'#size' => 4,
		);

	$form['url_type'] = array(
		'#type' => 'select',
		'#description' => t('CPF type'),
		'#required' => TRUE,
		'#title' => t('CPF'),
		'#options' => array(
			'corporations' => t('corporations'),
			'people' => t('people'),
			'families' => t('families'),
		),
		'#default_value' => $timeline->url_type,
		);
		
	$form['url_slug'] = array(
		'#type' => 'textfield',
		'#description' => t('Drupal URL slug for timeline'),
		'#required' => TRUE,
		'#title' => t('URL Slug'),
		'#default_value' => $timeline->url_slug,
		);

	

if (isset($timeline->tid)) {

	$form['tid'] = array(
		'#type' => 'hidden',
		'#value' => $timeline->tid,
		);
		
}

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

/**
 * redirect form after submit
 */
function dul_timeline_timeline_admin_form_alter(&$form, &$form_state, $form_id) {
    $form['actions']['submit']['#submit'][] = 'dul_timeline_timeline_admin_form_submit'; // custom callback name
}



/**
 * submit callback for timeline edit form
 */
function dul_timeline_timeline_admin_form_submit($form, &$form_state) {
	// save changes to the database.
	// db_merge() - handles both insert and update
	// @see https://api.drupal.org/api/drupal/includes!database!database.inc/function/db_merge/7
	
	
	db_merge('timeline')

      ->key(array(
      	'tid' => $form_state['values']['tid']
      ))
      
      ->fields(array(
      	'timeline_name' => $form_state['values']['timeline_name'],
      	'dulmaster_key' => $form_state['values']['dulmaster_key'],
      	'dulmaster_num' => $form_state['values']['dulmaster_num'],
      	'timeline_od' => $form_state['values']['timeline_od'],
      	'collections_od' => $form_state['values']['collections_od'],
      	'people_od' => $form_state['values']['people_od'],
      	'corporate_od' => $form_state['values']['corporate_od'],
      	'url_type' => $form_state['values']['url_type'],
      	'url_slug' => $form_state['values']['url_slug']
      ))
      ->execute();
      
    $form_state['redirect'] = 'admin/config/timeline';
    drupal_set_message(t('Updated!'), 'status');
}



/**
 * Setting administrative for Timeline
 */
function dul_timeline_timeline_admin_settings($form, &$form_state) {
	# GET THE VARIABLE SETTINGs first
	// $dul_masterkey = variable_get('dul_timeline.dul_masterkey');
	// take that value and use it as as #default_value for the appropriate element below

	# we'll need a element 'master key'
	$form['dul_masterkey'] = array(
		'#type' => 'textfield',
		'#default_value' => '',	// use "variable_get()" to fetch this value
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



