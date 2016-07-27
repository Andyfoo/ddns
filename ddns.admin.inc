<?php

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

  foreach(ddns_services() as $provider => $url) {
    $pu = str_replace('.', '_', $provider);
    $form['ddns_services']['ddns_' . $pu . '_enabled'] = array(
      '#type' => 'checkbox',
      '#title' => $provider,
      '#default_value' => variable_get('ddns_' . $pu . '_enabled', 0),
    );
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
    if (strpos($url, '[USERNAME]') !== FALSE) {
      $form['ddns_services']['ddns_' . $pu . '_settings']['ddns_' . $pu . '_username'] = array(
        '#type' => 'textfield',
        '#title' => t('Username'),
        '#description' => t('The username for the service.'),
        '#default_value' => variable_get('ddns_' . $pu . '_username', ''),
      );
    };
    if (strpos($url, '[PASSWORD]') !== FALSE) {
      $form['ddns_services']['ddns_' . $pu . '_settings']['ddns_' . $pu . '_password'] = array(
        '#type' => 'textfield',
        '#title' => t('Password'),
        '#description' => t('The password for the service.'),
        '#default_value' => variable_get('ddns_' . $pu . '_password', ''),
      );
    };
    if (strpos($url, '[DOMAIN]') !== FALSE) {
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
