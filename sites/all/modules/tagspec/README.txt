-- SUMMARY --

Tagspec is a developer library that provides a tag specification form element and an API for using tag specifications in render arrays.

This module is for developers and should only be installed if it is a dependency of another module.

There are many occasions where you need to allow HTML to be specified in an form for developers but use it as a render array.
Traditionally this has been handled by a proliferation of text fields for the various elements and different kinds of attributes.
This usually leaves a case off or makes it difficult to specify  certain kinds of attributes, or worst of all, a drop down menu of allowed tags that hasn't been updated since HTML 3 and a single textbox for adding classes with no way to add other attributes.

Tagspec solves this by providing a text box to enter the tag (without brackets) and any attributes, such as class, role, or even something complicated like a data-* attribute.
It then parses it using a proper HTML parser and extracts the various attributes into a format that is easily usable in render arrays.

The tagspec form element has a number of options to suit a wide variety of use cases. By default, all options are shown:
* #tagspec_hide_no_explode - The no explode keys textbox takes a space separated list of attributes to store as strings even if their value contains spaces. Useful for data-* attributes containing JSON. Works for any attribute except id and class, which have to be handled specially as Drupal render arrays tend to handle them specially.
* #tagspec_hide_keep_id - Keep original id attribute even if not specified in tagspec.
* #tagspec_hide_merge_classes - Merge classes in render array with any defined above.
* #tagspec_hide_merge_attrs - Merge attributes in render array with any defined in the tagspec.

Example

	$form['tag'] = array(
		'#type'                     => 'tagspec',
		'#title'                    => t('Wrapper tag'),
		'#tagspec_hide_keep_id'     => TRUE,
		'#tagspec_hide_merge_class' => TRUE,
		'#tagspec_hide_merge_attrs' => TRUE,
	);

This defines a form element that takes a Tag Specification, No explode keys, and hides the keep id, merge classes, and merge attributes checkboxes.

If the form is filled out as such:

	Tag specification: main id=main-content-area class="main-content grid-8 grid-fill" itemprop=mainContentOfPage role=main data-x="1 2" data-some-js-doohickey="a b c"
	No explode keys: data-some-js-doohickey

The form value will be

	$result = array(
		"raw_specification" => 'main id=main-content-area class="main-content grid-8 grid-fill" itemprop=mainContentOfPage role=main data-x="1 2" data-some-js-doohickey="a b c"'
		"tag" => "main",
		"id" => "main-content-area",
		"classes" => array("main-content", "grid-8", "grid-fill"),
		"no_explode" => array("data-some-js-doohickey"),
		"merge_classes" => TRUE,
		"merge_attributes" => TRUE,
		"keep_id" => TRUE,
		"string_attributes" => array("data-some-js-doohickey" => "a b c"),
		"array_attributes" => array(
			"itemprop" => array("mainContentOfPage"),
			"role" => array("main"),
			"data-x" => array("1", "2"),
		),
	);

The module provides many helpers for dealing with odd render arrays coming from other modules and turning the above directly into a render array.



For a full description of the module, visit the project page:
  https://drupal.org/projects/tagspec

To submit bug reports and feature suggestions, or to track changes:
  https://drupal.org/project/issues/tagspec


-- REQUIREMENTS --

simpplehtmldom API ( https://drupal.org/project/simplehtmldom ) and the simplehtmldom library ( http://simplehtmldom.sourceforge.net/ ).


-- INSTALLATION --

Install as usual, see
https://drupal.org/documentation/install/modules-themes/modules-7 for further
information.

-- CONTACT --

Current maintainers:
* James Frasche (soapboxcicero) - https://drupal.org/user/2111168

This project has been sponsored by:
* MorseMedia
  Visit https://morsemedia.net

