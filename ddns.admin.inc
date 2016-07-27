<?php

/**
 * @file
 *
 * Creates the administration menu for DDNS
 *
 */

/**
 * Page callback: ddns settings
 *
 * @see ddns_menu()
 */
function ddns_settings_form($form, &$form_state) {
  $form['ddns_description'] = array(
    '#markup' => t('The current IP address of the server is <b>@address</b>.', array(
      '@address' => ddns_current_ip(),
    ))
  );

  $form['ddns_services'] = array(
    '#type' => 'fieldset',
    '#title' => t('Available Services'),
  );

  // Build a form item for each one of our providers
  foreach (ddns_services() as $provider => $url) {
    // Replace periods with underscores
    // The underscores cause havoc with form IDs
    $pu = str_replace('.', '_', $provider);
    // A checkbox with the name of the provider
    $form['ddns_services']['ddns_' . $pu . '_enabled'] = array(
      '#type' => 'checkbox',
      '#title' => check_plain($provider),
      '#default_value' => variable_get('ddns_' . $pu . '_enabled', 0),
    );
    // A fieldset that only displays if the checkbox is active
    $form['ddns_services']['ddns_' . $pu . '_settings'] = array(
      '#type' => 'fieldset',
      '#states' => array(
        'visible' => array(
          ':input[name="ddns_' . $pu . '_enabled"]' => array(
            'checked' => TRUE,
          )
        )
      ),
    );
    // Check if the URL needs a username
    if (strpos($url, '[USERNAME]') !== FALSE) {
      // A field for the username
      $form['ddns_services']['ddns_' . $pu . '_settings']['ddns_' . $pu . '_username'] = array(
        '#type' => 'textfield',
        '#title' => t('Username'),
        '#description' => t('The username for the service.'),
        '#default_value' => variable_get('ddns_' . $pu . '_username', ''),
      );
    };
    // Check if the URL needs a password
    if (strpos($url, '[PASSWORD]') !== FALSE) {
      // A field for the password, plaintext
      $form['ddns_services']['ddns_' . $pu . '_settings']['ddns_' . $pu . '_password'] = array(
        '#type' => 'textfield',
        '#title' => t('Password'),
        '#description' => t('The password for the service.'),
        '#default_value' => variable_get('ddns_' . $pu . '_password', ''),
      );
    };
    // Check if the URL needs a host/domain
    if (strpos($url, '[DOMAIN]') !== FALSE) {
      // A field for the host/domain
      $form['ddns_services']['ddns_' . $pu . '_settings']['ddns_' . $pu . '_hostname'] = array(
        '#type' => 'textfield',
        '#title' => t('Hostname'),
        '#description' => t('The hostname(s) for the service.'),
        '#default_value' => variable_get('ddns_' . $pu . '_hostname', ''),
      );
    };
  };

  $form['ddns_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Settings'),
  );
  // A field for update interval, max of 9999 seconds
  $form['ddns_settings']['ddns_interval'] = array(
    '#type' => 'textfield',
    '#title' => t('Service Update Interval'),
    '#description' => t('Interval (in minutes) that services will be updated.
      This number should be left as high as possible. Some service providers
      will blacklist an account if it is updated too often.'),
    '#default_value' => variable_get('ddns_interval', 60),
    '#size' => 4,
    '#maxlength' => 4,
  );
  // A field for the connection user-agent
  $form['ddns_settings']['ddns_ua'] = array(
    '#type' => 'textfield',
    '#title' => t('User-Agent'),
    '#description' => t('The user-agent sent to providers on an update request.'),
    '#default_value' => variable_get('ddns_ua',
      'Drupal DDNS - https://www.drupal.org/project/ddns'),
    '#size' => 80,
    '#maxlength' => 255,
  );

  // Create a submit button and handle variable setting
  return system_settings_form($form);
}
