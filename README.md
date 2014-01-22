FabDrupal
=========
## A Drupal distribution for FabLabs
Projects documentation, Machine description and reservation, Suppliers and Partners Mapping, Blog, Event registration, Open REST API (anonymous and registered access)

# Use FabDrupal
Download from Releases the [fabdrupal-7.x-0.21.tgz](https://github.com/OpenP2PDesignOrg/FabDrupal/releases/download/v0.21/fabdrupal-7.x-0.21.tgz) package and install as a normal Drupal package. You will be asked to insert a Flickr API key at the end of the installation process. You will have to manually select the option for the machine reservation after the install is done by going to Structure &gt; Content Types &gt; Machines and under MERCI Settings check Resource.
You will probably have to reorganize the menu.

## fabdrupal.distro
The Make, Install and Profile file that organize the distribution

## features
The packages of the custom modules for the distribution

## fabdrupal + db.sql
This is the development environment of the FabDrupal distribution: folder and MySQL database.
*Warning:* use only in the development, not in production! In production, remember to change the admin and the website e-mail.

### Admin user:

username = admin<br>
password = admin<br>


### Database:

[https://www.dropbox.com/s/dw818gfddjqjjgs/db.sql](https://www.dropbox.com/s/dw818gfddjqjjgs/db.sql)
