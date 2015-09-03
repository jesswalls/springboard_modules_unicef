<?php

/**
 * @file
 * Administration page callbacks for the fundraiser module.
 */

/**
 * Display a table of recurring donations for admin users.
 */
function fundraiser_sustainers_admin() {
  $headers = array(
    'Master Donation ID',
    'User',
    'Amount',
    'Charge Date',
    'Status',
  );
  $rows = array();
  // Get the data.
  $donation_sets = _fundraiser_sustainers_get_donation_sets();
  if ($donation_sets) {
    foreach ($donation_sets as $donation_set) {
      if (isset($donation_set->master_did)) {
        $this_donation = fundraiser_donation_get_donation($donation_set->master_did);
        $next_charge = _fundraiser_sustainers_get_donations_next_charge($donation_set->master_did);
        if (isset($next_charge->did)) {
          $next_charge = fundraiser_donation_get_donation($next_charge->did);
          $row = array();
          $row[] = l($donation_set->master_did, 'admin/config/system/fundraiser/recurring/' . $donation_set->master_did . '/view');
          $row[] = $this_donation->user->name;
          $row[] = $next_charge->donation['amount_formatted'];
          $row[] = date('m/d/y', $donation_set->next_charge);
          $row[] = $donation_set->status;
          $rows[] = $row;
        }
      }
    }
  }
  $output = '<h2>All Recurring Orders</h2>';
  $output .= theme('table', array('header' => $headers, 'rows' => $rows));
  return $output;
}

/**
 * Display a table of recurring donations for admin users by master donation id.
 */
function fundraiser_sustainers_admin_view($did) {

  if (arg(4) == 'recurring' && arg(6) == 'view') {
    $headers = array(
      'Donation ID',
      'Amount',
      'Charge Date',
      'Sustainer Key',
      'Processed Status',
      'Attempts',
    );
  }
  else {
    $headers = array(
      'Donation ID',
      'Amount',
      'Charge Date',
      'Processed Status',
      'Attempts',
    );
  }
  $rows = array();
  // Get the data.
  $donation = fundraiser_donation_get_donation($did);
  $donation_set = _fundraiser_sustainers_get_donations_recurr_by_member($did);
  if ($donation_set) {
    $donation_set = _fundraiser_sustainers_get_donations_recurr_by_masterdid($donation_set[0]->master_did);
  }
  if ($donation_set) {
    foreach ($donation_set as $this_donation) {
      $this_donation = fundraiser_donation_get_donation($this_donation->did);
      $row = array();
      if (user_access('view any commerce_order entity of bundle commerce_order')) {
        $row[] = l($this_donation->did, 'admin/commerce/orders/' . $this_donation->did);
      }
      else {
        $row[] = $this_donation->did;
      }

      $row[] = $this_donation->donation['amount_formatted'];
      $row[] = date('m/d/y', $this_donation->recurring->next_charge);
      if (arg(4) == 'recurring' && arg(6) == 'view') {
        $row[] = $this_donation->recurring->sustainer_key;
      }
      $row[] = $this_donation->status_label;
      $row[] = $this_donation->recurring->attempts;
      $rows[] = $row;
    }
  }
  $output = '<h2>Recurring Orders For #' . $donation_set[0]->master_did . '</h2>';
  $output .= theme('table', array('header' => $headers, 'rows' => $rows));
  return $output;
}

/**
 * Provides a way for admins to edit recurring donation info directly.
 */
function fundraiser_sustainers_admin_edit($did) {
  if (is_numeric($did)) {
    // Get the master did and return the form for that.
    $sustainer_info = _fundraiser_sustainers_get_recurring_by_did($did);
    return fundraiser_sustainers_edit_form($sustainer_info->master_did);
  }
}
