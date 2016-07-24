<?php

/**
 * Page callback: ddns settings
 *
 * @see ddns_menu()
 */
function ddns_settings_form($form, &$form_state) {
  module_load_include('inc','ddns','ddns.services');

  $form['ddns_description'] = array(
    '#markup' => t('The current IP address of the server is <b>@address</b>.', array(
        '@address' => ddns_current_ip(),
      )
    )
  );
  // Create a submit button and handle variable setting
  return system_settings_form($form);
}
