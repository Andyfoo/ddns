<?php

/**
 * Page callback: ddns settings
 *
 * @see ddns_menu()
 */
function ddns_settings_form($form, &$form_state) {
  // Create a submit button and handle variable setting
  return system_settings_form($form);
}
