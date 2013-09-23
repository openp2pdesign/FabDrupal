= Resource Conflict =

This module allows for users to detect overlapping dates and respond with Rules.
This is most often used for tracking bookable resources.  For example, a student 
can book a microscope for use within their lab, but only one microscope can be 
booked at a time. 

By default, this module throws a form error for every overlapping date it finds
among conflict-enabled nodes. It is intended to be customized using Rules, for 
example to only throw errors when certain field values are identical.

== Requirements ==

Entity: http://drupal.org/project/entity
Rules: http://drupal.org/project/rules
Date: http://drupal.org/project/date
Rules Forms: http://drupal.org/project/rules_forms

== Installation ==

Download the module to your modules directory, and enable it from admin/modules.

You may wish to disable or modify the built in example Rule, which shows a form error
message for conflicts as they are detected.

== Usage ==

1) Create a content type with a date field.
2) On the Content Type Edit page, enable Conflict Checking for this Content Type.
   Select the date field which should be used for conflict checking, and save 
   the form.
3) Create two nodes with overlapping dates to see the default Rule in action. Or
   create your own Rule.


== Included Rules Components ==

EVENT: A RESOURCE CONFLICT WAS DETECTED

This event is triggered any time a resource conflict is detected. By itself, this event 
will never fire.


EVENT: A RESOURCE CONFLICT NODE FORM IS VALIDATED

This rule fires during node form validation on Resource Conflict enabled content types.
You should use this event if you want to set form errors, or if you want to interact with
Rules_forms module. It provides both a node object of the node being created/edited and a 
form object for use with rules_forms. This is the event trigger for the default Rule.


CONDITION: CONTAINS A RESOURCE CONFLICT

Evaluate a node object for conflicts. Returns TRUE if there are conflicts for the node.


ACTION: LOAD A LIST OF CONFLICTING NODES

Creates a list of nodes that conflict with the given node.


ACTION: SET A FORM VALIDATION ERROR

Stores a form validation error to be fired the next time a validation hook is called on 
a conflict-enabled node. This is intended for use with the "A Resource Conflict Node Form
is Validated" Event, but you could probably find other creative uses for it. When this action
fires, the next resource conflict enabled node to go through validation will get a form error
on the resource conflict enabled date field.


== To Do ==

* Setting a form validation error currently works by setting a variable in $_SESSION, and 
retrieving it in hook_node_validate. This is open to all sorts of abuse, and if mis-used
properly could throw errors on the wrong node forms. At the very least, I should set a time
expiry on these messages to avoid accidental abuse. Proper caching would be even smarter.

* Make ANY fieldable entity capable of handling conflict detection. 


== Contact ==
This module was originally developed by Andrew Berry (andrewberry@sentex.net) 
for use at the Protein Dynamics lab at the University of Guelph.

It was re-written for Rules and Entity integration by Campbell Vertesi (campbell@vertesi.com)
for use on a private project.

Project Page: http://drupal.org/project/resource_conflict

