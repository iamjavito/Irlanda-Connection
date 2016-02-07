-- SUMMARY --

Zone adds nesting to Drupal's region and block system.

Zone replaces part of Drupal's region system in zone enabled themes, allowing very flexible and exacting HTML to be created.

Zone gets rid of region templates and takes over the page template (requires some boilerplate in your theme, noted below).
This is only for themes that declare that themselves zone enabled—all others use the standard Drupal system.

Drupal's standard system could be described as a list of regions that may contain a list of blocks.

Zone creates a tree of zones. Leaves in the zone tree can be declared to be regions and then may contain lists of blocks.

Each zone can have any HTML (including no HTML) specified as its wrapper tag (using Tagspec ( https://www.drupal.org/project/tagspec )).

By default a zone with no children (either other zones or blocks, in the case of zones marked as regions) is not rendered, though it will be if "Render if empty" is selected.

A zone's visibility can be modified by hook_zone_visibility_alter.
All zone's are visible by default unless "Hide by default" is selected. Zones that are hidden will not be rendered.

On hook_page_build, the zone tree is turned into a render array.

Putting all of this together it allows the creation of very complex themes that can easily be modified programmatically without having to create elaborate hacks in templates or preprocess functions.

To use zones in a theme add

	zone_enabled = true
	;the following are mandatory even though we're overriding this part of the system
	regions[content] = Content
	regions[page_top] = Page Top
	regions[page_bottom] = Page Bottom

and change your page.tpl.php to

	<?php echo drupal_render($page['content']);?>

If you look at a page rendered in your theme you'll now see a warning that no zones are defined, so define some zones.

IMPORTANT: You MUST create a zone whose machine name is content!

For a full description of the module, visit the project page:
  https://drupal.org/projects/zone

To submit bug reports and feature suggestions, or to track changes:
  https://drupal.org/project/issues/zone


-- REQUIREMENTS --

Tagspec ( https://drupal.org/project/tagspec )


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

