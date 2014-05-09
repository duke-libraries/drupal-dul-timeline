drupal-dul-timeline
===================

How to Clone:
--------------
```git clone git@github.com:duke-libraries/drupal-dul-timeline.git dul_timeline```

Installing Module with Drush
```
drush en -y dul_timeline
```

Goals for this module
---------------------
* Provide a simple facility for Site Administrators to create Timeline pages without a lot of Drupal/PHP coding
* Scalable design

Module Layout
-------------
* dul_timeline.info
* dul_timeline.module
* dul_timeline.admin.inc
* dul_timeline.install

Drupal Hooks to be Implemented
------------------------------
* hook_menu
* hook_schema
* hook_install
* hook_uninstall

Hooks
-----

### hook_install
Use this hook to set up variable settings needed for the module, such as the master key for the Google Spreadsheet used to provide the data.

Also use this hook to add data rows to the `timeline` table (see below)

Database Tables
---------------

### timeline
```This table stores a mapping of a Timeline 'page' to the specific row in a designated Google Spreadsheet.```

#### Schema (Drupal-format)
```
'timeline' => array(
	'description' => 'Table of timeline records',
	'fields' => array(
		'tid' => array(
			'type' => 'serial',
			'unsigned' => TRUE,
			'not null' => TRUE,
			),
		'title' => array(
			'type' => 'varchar',
			'length' => 128,
			'not null' => TRUE,
			'default' => '',
			),
		'datasource_row' => array(
			'type' => 'int', 
			'unsigned' => TRUE, 
			'size' => 'small',
			),
		'url_alias' => array(
			'type' => 'varchar',
			'length' => 128,
			'not null' => TRUE,
			'default' => '',
			),
		),
	'primary key' => array('tid'),
	),
```
Other Functions Needed -- Maybe
-------------------------------
* Loader function to fetch individual Timeline record
