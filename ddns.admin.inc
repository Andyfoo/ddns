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
    ))
  );

  $form['ddns_services'] = array(
    '#type' => 'fieldset',
    '#title' => t('Available Services'),
  );

  foreach (ddns_services() as $provider => $url) {
    $form['ddns_services'][$provider . '_enabled'] = array(
      '#type' => 'checkbox',
      '#title' => $provider,
      '#default_value' => variable_get($provider . '_enabled',0),
    );
    $form['ddns_services'][$provider . '_settings'] = array(
      '#type' => 'fieldset',
      '#states' => array(
        'visible' => array(
          ':input[name="' . $provider . '_enabled"]' => array(
            'checked' => TRUE,
          )
        )
      ),
    );
    $form['ddns_services'][$provider . '_settings'][$provider . '_username'] = array(
      '#type' => 'textfield',
      '#title' => t('Username'),
      '#description' => t('The username for the service.'),
      '#default_value' => variable_get($provider . '_username',''),
    );
    $form['ddns_services'][$provider . '_settings'][$provider . '_password'] = array(
      '#type' => 'textfield',
      '#title' => t('Password'),
      '#description' => t('The password for the service.'),
      '#default_value' => variable_get($provider . '_password',''),
    );
    $form['ddns_services'][$provider . '_settings'][$provider . '_hostname'] = array(
      '#type' => 'textfield',
      '#title' => t('Hostname'),
      '#description' => t('The hostname(s) for the service.'),
      '#default_value' => variable_get($provider . '_hostname',''),
    );
  };

  // Create a submit button and handle variable setting
  return system_settings_form($form);
}
