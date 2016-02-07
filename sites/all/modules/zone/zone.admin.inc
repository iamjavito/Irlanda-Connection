<?php

function _zone_rebuild($theme) {
	zone_load_for($theme, TRUE);
	_block_rehash($theme);
	drupal_static_reset('block_list');
	drupal_theme_rebuild();
}

function zones_manage_form($form, &$state, $theme) {
	$zones = zone_load_for($theme);
	$zones = $zones['list'];

	if(count($zones) == 0) {
		$form['none'] = array(
			'#markup' => t('No zones defined for @theme yet', array('@theme' => $theme)),
		);
		return $form;
	}

	$form['tree'] = array(
		'#tree'   => TRUE,
		'#theme'  => 'zone_tabledrag_components',
	);

	foreach($zones as $i => $zone) {
		$form['tree'][$i] = array();
		$f = &$form['tree'][$i];
		$f['#attributes']['class'] = array();
		if($zone['hidden']) {
			$f['#attributes']['class'][] = 'zone-def-hidden';
		}
		if($zone['region']) {
			$f['#attributes']['class'][] = 'zone-def-region';
			$f['#attributes']['class'][] = 'tabledrag-leaf';
		}

		$indent = theme('indentation', array('size' => $zone['depth']));

		$f['indent'] = array(
			'#markup' => $indent,
		);

		$mach = ' <small>(machine name: <code>' . $zone['machine_name'] . '</code>)</small>';
		$f['label'] = array(
			'#type'   => 'item',
			'#markup' => $zone['name'] . $mach,
		);

		$f['zid'] = array(
			'#type'          => 'textfield',
			'#default_value' => $zone['id'],
			'#size'          => 3,
			'#attributes'    => array('class' => array('zone-def-id', 'tabledrag-hide'), 'disabled' => 'disabled'),
		);
		$f['parent'] = array(
			'#type'          => 'textfield',
			'#size'          => 3,
			'#default_value' => $zone['parent'],
			'#attributes'    => array('class' => array('zone-def-parent')),
		);
		$f['weight'] = array(
			'#type'          => 'textfield',
			'#size'          => 3,
			'#default_value' => $zone['weight'],
			'#attributes'    => array('class' => array('zone-def-weight')),
		);

		$sum = '';
		if($zone['region']) {
			$sum .= '<div class=region>Region</div>';
		}
		if($zone['hidden']) {
			$sum .= '<div class=hidden>Hidden</div>';
		}
		$f['summary'] = array(
			'#type'   => 'markup',
			'#markup' => $sum,
		);

		$f['edit'] = array(
			'#type'   => 'markup',
			'#markup' => l('edit', 'admin/structure/zones/edit/' . $zone['id']),
		);
	}

	$form['submit'] = array(
		'#type'  => 'submit',
		'#value' => t('Save'),
	);

	return $form;
}

function zones_manage_form_submit($form, &$state) {
	foreach($state['values']['tree'] as $v) {
		db_update('zones')
			->fields(array(
				'parent' => $v['parent'],
				'weight' => $v['weight'],
			))
			->condition('id', $v['zid'], '=')
			->execute();
	}
	_zone_rebuild($state['build_info']['args'][0]);
}

//everything else is creating/editing zones

function zones_new_form($form, &$state, $theme) {
	$w = db_query('select 1+max(z.weight) from {zones} z where theme=:theme', array(
		'theme' => $theme,
	))->fetchColumn(0);
	return zones_edit_form($form, $state, array('theme' => $theme, 'weight' => $w));
}

function zones_new_form_submit($form, &$state) {
	zones_edit_form_submit($form, $state);
}

function _zonedef($arr, $key, $def) {
	if(isset($arr[$key])) {
		return $arr[$key];
	}
	return $def;
}

function zones_edit_form($form, &$state, $zone) {
	$form['name'] = array(
		'#type'          => 'textfield',
		'#title'         => t('Name'),
		'#size'          => 40,
		'#maxlength'     => 255,
		'#required'      => TRUE,
		'#default_value' => _zonedef($zone, 'name', ''),
	);
	$form['machine_name'] = array(
		'#type'          => 'machine_name',
		'#title'         => t('Machine name'),
		'#size'          => 15,
		'#maxlength'     => 255,
		'#required'      => TRUE,
		'#default_value' => _zonedef($zone, 'machine_name', ''),
		'#machine_name'  => array(
			'source' => array('name'),
			'exists' => '_zone_machine_name_exists',
		),
	);

	$form['theme'] = array( //so machine name exists can limit per-theme
		'#type'  => 'hidden',
		'#value' => $zone['theme'],
	);
	if(isset($zone['id'])) {
		$form['zid'] = array( //for editing
			'#type'  => 'hidden',
			'#value' => $zone['id'],
		);
	}
	if(isset($zone['parent'])) {
		$form['parent'] = array(
			'#type'  => 'hidden',
			'#value' => $zone['parent'],
		);
	}
	if(isset($zone['weight'])) {
		$form['weight'] = array(
			'#type'  => 'hidden',
			'#value' => $zone['weight'],
		);
	}

	$form['tag'] = array(
		'#type'                     => 'tagspec',
		'#title'                    => t('Wrapper tag'),
		'#tagspec_hide_keep_id'     => TRUE,
		'#tagspec_hide_merge_class' => TRUE,
		'#tagspec_hide_merge_attrs' => TRUE,
		'#default_value'            => _zonedef($zone, 'tag', array()),
	);

	$form['empty'] = array(
		'#type'          => 'checkbox',
		'#title'         => t('Render if empty'),
		'#description'   => t('If unselected, and no children are present, this zone will not be rendered'),
		'#default_value' => _zonedef($zone, 'empty', FALSE),
	);
	$form['hidden'] = array(
		'#type'          => 'checkbox',
		'#title'         => t('Hide by default'),
		'#description'   => t('If selected, this zone will only be rendered if another module, like Context, tells it to'),
		'#default_value' => _zonedef($zone, 'hidden', FALSE),
	);
	$form['region'] = array(
		'#type'          => 'checkbox',
		'#title'         => t('Region'),
		'#description'   => t('If selected, this zone will be treated as a region and show up in the block list'),
		'#default_value' => _zonedef($zone, 'region', FALSE),
	);

	$form['actions'] = array('#type' => 'actions');
	$form['actions']['submit'] = array(
		'#type'  => 'submit',
		'#value' => t('Save'),
	);
	if(isset($zone['id'])) {
		$form['actions']['delete'] = array(
			'#type'  => 'submit',
			'#value' => t('Delete'),
		);
	}
	return $form;
}

//machine names are not unique, but (theme, machine_name)s are
function _zone_machine_name_exists($val, $elm, $state) {
	$theme = $state['values']['theme'];
	$q = db_query('select 1 from {zones} where machine_name=:name and theme=:theme', array(
		'name'  => $val,
		'theme' => $theme,
	));
	return $q->fetchColumn(0);
}

function zones_edit_form_submit($form, &$state) {
	$state['redirect'] = 'admin/structure/zones';
	$v = $state['values'];

	if($v['op'] == 'Save') {
		unset($v['tag']['tagspec']);
		$zone = array(
			'name' => $v['name'],
			'machine_name' => $v['machine_name'],
			'theme'        => $v['theme'],
			'tag'          => $v['tag'],
			'empty'        => $v['empty'],
			'hidden'       => $v['hidden'],
			'region'       => $v['region'],
		);
		if(isset($v['parent'])) {
			$zone['parent'] = $v['parent'];
		}
		if(isset($v['weight'])) {
			$zone['weight'] = $v['weight'];
		}
		if(isset($v['zid'])) {
			$zone['id'] = $v['zid'];
			drupal_write_record('zones', $zone, 'id');
		} else {
			drupal_write_record('zones', $zone);
		}
	} else if(isset($v['zid'])) {
		$id = $v['zid'];
		db_delete('zones')
			->condition('id', $id, '=')
			->execute();

		//reparent any children of $id.
		$parent = 0;
		if(isset($v['parent'])) {
			$parent = $v['parent'];
		}

		db_update('zones')
			->fields(array('parent' => $parent))
			->condition('parent', $id, '=')
			->execute();
	}

	_zone_rebuild($v['theme']);
}
