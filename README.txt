-- SUMMARY --

The DDNS module provides a built in way to manage your DDNS (DynamicDNS) providers. Out of
the box, the module supports dozens of popular DDNS services. The module
utilizes the Drupal cron process to automatically update your providers but
will only run as often as configured to do so.

-- REQUIREMENTS --

* PHP must be compiled with cURL support

-- INSTALLATION --

The module can be installed and activated through normal conventions, but it is
recommended that a cron service from the server side is utilized to kick off
Drupal's cron job on a regular basis. The built in Drupal cron may not be
utilized as often as needed, so setting up a cron job on the server to execute
"drush cron" periodically ensures you're always updated.

-- CONFIGURATION --

* Configuration for the module can be found at the following URL:

    admin/config/development/ddns

* For each provider selected, fill in the relevant information

    Username
    Password
    Hostname

* Some services may not contain all of these fields

* The Service Update Interval window should be left as high as possible. Some
providers will blacklist your account. It is recommended to leave this at 60
minutes to ensure your account is not blacklisted.

* Some providers may require a custom user-agent to be specified. If you know
you need this, fill it in, otherwise leave it default.

-- CONTACT --

* Miles McLean (mills00013) - https://www.drupal.org/user/3348892
