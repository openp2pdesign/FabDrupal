This module provides integration with Leaflet map scripting library,
http://leaflet.cloudmade.com.

To use, you must download the leaflet library from
http://leaflet.cloudmade.com/download.html or Github,
http://github.com/CloudMade/Leaflet.

In its current state, maps can be rendered via the included field formatter for
Geofield or by using the API directly.


Installation
------------

1. Normal Drupal module installation

2. Download the Leaflet library from http://leafletjs.com/. Leaflet 0.5 or higher
   is recommended

3. Enable leaflet_views for using Views and Leaflet (see below), or use the display formatters
   for fields display.


API Usage
---------
Rendering a map is as simple as calling a single method, leaflet_render_map(),
which takes 3 parameters.

$map
An associative array defining a map. See hook_leaflet_map_info(). The module
defines a default map with a OpenStreet Maps base layer.

$features
This is the tricky pary. This is an associative array of all the features you
want to plot on the map. A feature can be a point, linestring, polygon,
multipolygon, multipolygon, or json object. Additionally, features can be
grouped into layer groups so they can be controlled together,
http://leaflet.cloudmade.com/reference.html#layergroup. An feature will look
something like:

$features = array(
  array(
    'type' => 'point',
    'lat' => 1232,
    'lon' => 123.45,
    'icon' => array(
      'iconUrl' => 'sites/default/files/mymarker.png
    ),
    'popup' => l($node->title, 'node/' . $node->nid),
    'leaflet_id' => 'some unique ID'
  ),
  array(
    'type' => 'linestring',
    'points' => array(
      0 => array('lat' => 1324, 'lon' => 1232),
      1 => array('lat' => 1324, 'lon' => 1232),
      2 => array('lat' => 1324, 'lon' => 1232),
      3 => array('lat' => 1324, 'lon' => 1232),
      4 => array('lat' => 1324, 'lon' => 1232),
    ),
    'popup' => l($node->title, 'node/' . $node->nid),
    'leaflet_id' => 'some unique ID'
  ),
  array(
    'type' => 'json',
    'json' => [JSON OBJECT],
    'properties' = array(
      'style' => [style settings],
      'leaflet_id' => 'some unique ID'
    )
  )
);

Views integration
-----------------

To render a map using Views, enable the module leaflet_views.

You need to add at least one geofield to the Fields list, and select the Leaflet Map style
in Format.

In the settings of the style, select the geofield as the Data Source and select a field for Title
and Description (which will be rendered in the popup).

As a more powerful alternative, you can use node view modes to be rendered in the popup.
In the Description field, select "<entire node>" and then select a View mode.

For a tutorial, please read http://marzeelabs.org/blog/2012/09/24/building-maps-in-drupal-using-leaflet-views/

Roadmap
-------

* UI for managing maps
* Better documentation


Authors/Credits
---------------

* [levelos](http://drupal.org/user/54135)
* [pvhee](http://drupal.org/user/108811)
