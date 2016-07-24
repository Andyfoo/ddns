<?php

/**
 * Available Dynamic DNS services
 *
 * Most services taken from work by the OpenWRT project
 * https://github.com/openwrt/packages/blob/master/net/ddns-scripts/files/services
 */

function ddns_services() {
  $services = array(
    'dyndns.org' => 'http://[USERNAME]:[PASSWORD]@members.dyndns.org/nic/update?hostname=[DOMAIN]&myip=[IP]',
    'changeip.com' => 'http://[USERNAME]:[PASSWORD]@nic.changeip.com/nic/update?u=[USERNAME]&p=[PASSWORD]&cmd=update&hostname=[DOMAIN]&ip=[IP]',
    'zoneedit.com' => 'http://[USERNAME]:[PASSWORD]@dynamic.zoneedit.com/auth/dynamic.html?host=[DOMAIN]&dnsto=[IP]',
  );

  return $services;
}
