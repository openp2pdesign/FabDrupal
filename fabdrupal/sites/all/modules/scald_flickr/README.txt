
-- SUMMARY --

* This module provides Flickr image import inside Scald. 
  It creates a scald provider allowing users to add atoms of type flickr image.

* This project includes all the features needed to create atoms directly 
  from Flickr, search, reuse them, and simply embed them into your drupal 
  nodes with drag and drop magic.

* The module extends scald UI to do the following :
  - Import flickr image by photo id, user_id or username, keyword
  - Search on flickr in scald drag and drop library

* See http://drupal.org/node/1895554 for a list of Scald providers 
  as separate projects for other great providers.

-- REQUIREMENTS --

* Scald module 

* This project use the Flickr API, So you need to create an API key : 
  http://www.flickr.com/services/apps/create/apply/.


-- INSTALLATION --

* To test it quickly with drush : drush en -y scald_flickr scald_dnd_library mee


-- CONFIGURATION --

* Administration » Configuration » Media » Scald Flickr Settings :

  - Configure your Flickr API key

* Configure user permissions in Administration » People » Permissions :

  - Administer flickr settings

  - Import flickr images


-- CONTACT --

Current maintainers :
* Pierre Cotiniere (pierre_cotiniere) - http://drupal.org/user/101869
* Didier Boff (B2F) - http://drupal.org/user/1767874
