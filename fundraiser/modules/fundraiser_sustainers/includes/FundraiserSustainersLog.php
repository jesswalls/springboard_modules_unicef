<?php
/**
 * @file
 * Methods for working with the Fundraiser Sustainers Log.
 */

/**
 * Class FundraiserSustainersLog.
 */
class FundraiserSustainersLog {

  /**
   * Save an entry to the sustainers log.
   *
   * @param array $values
   *   Values to save that are different from the old values, plus did. Donation
   *   ID (did) is a required key.
   * @param null|object $old_record
   *   The original record. If one is not provided it gets queried. This is used
   *   for default values and the old_state.
   *
   * @return bool|int
   *   FALSE or SAVED_NEW because a new record is always saved.
   */
  public function log(array $values, $old_record = NULL) {
    if (is_null($old_record)) {
      $old_record = _fundraiser_sustainers_get_recurring_by_did($values['did']);
    }

    $new_record = new stdClass();
    $new_record->timestamp = REQUEST_TIME;
    $new_record->did = $values['did'];

    if (isset($values['lock_id'])) {
      $new_record->lock_id = $values['lock_id'];
    }
    elseif (isset($old_record->lock_id)) {
      $new_record->lock_id = $old_record->lock_id;
    }
    else {
      $new_record->lock_id = '0';
    }

    if (isset($values['next_charge'])) {
      $new_record->next_charge = $values['next_charge'];
    }
    elseif (isset($old_record->next_charge)) {
      $new_record->next_charge = $old_record->next_charge;
    }
    else {
      $new_record->next_charge = 0;
    }

    if (isset($values['old_state'])) {
      $new_record->old_state = $values['old_state'];
    }
    elseif (isset($old_record->gateway_resp)) {
      $new_record->old_state = $old_record->gateway_resp;
    }
    else {
      $new_record->old_state = NULL;
    }

    // New state of NULL means no transition happened.
    if (isset($values['new_state'])) {
      $new_record->new_state = $values['new_state'];
    }
    elseif (isset($values['gateway_resp'])) {
      $new_record->new_state = $values['gateway_resp'];
    }
    else {
      $new_record->new_state = NULL;
    }

    if (isset($values['attempts'])) {
      $new_record->attempts = $values['attempts'];
    }
    elseif (isset($old_record->attempts)) {
      $new_record->attempts = $old_record->attempts;
    }
    else {
      $new_record->attempts = 0;
    }

    if (isset($values['cancellation_reason'])) {
      $new_record->cancellation_reason = $values['cancellation_reason'];
    }
    elseif (isset($old_record->cancellation_reason)) {
      $new_record->cancellation_reason = $old_record->cancellation_reason;
    }
    else {
      $new_record->cancellation_reason = '';
    }

    return drupal_write_record('fundraiser_sustainers_log', $new_record);
  }

  /**
   * Log that donations have been locked for processing.
   *
   * @param array $donations
   *   Array of donations, did as key and status as the value, to log as locked.
   * @param string $lock_id
   *   The new lock ID.
   */
  public function logLockedDonations(array $donations, $lock_id) {
    foreach ($donations as $did => $status) {
      $this->logLockedDonation($did, $status, $lock_id);
    }
  }

  /**
   * Log that a donation has been locked for processing.
   *
   * @param int $did
   *   The donation ID to log as locked.
   * @param string $lock_id
   *   The new lock ID.
   */
  public function logLockedDonation($did, $status, $lock_id) {
      $locked_log_record = array(
        'did' => $did,
        // Pass the old state through, a null status would signify a scheduled sustainer.
        'old_state' => empty($status) ? FUNDRAISER_SUSTAINERS_SCHEDULED_STATUS : $status,
        'new_state' => 'locked',
        'lock_id' => $lock_id,
      );
      $this->log($locked_log_record);
  }

  /**
   * Log that a sustainer has been unlocked.
   *
   * @param int $did
   *   The donation ID to log as unlocked.
   */
  public function logUnlockedDonation($did, $new_state = NULL) {
    $log_record = array(
      'did' => $did,
      'lock_id' => 0,
    );

    if (!is_null($new_state)) {
      $log_record['new_state'] = $new_state;
    }

    $this->log($log_record);
  }

  /**
   * Marks all scheduled log entries for a sustainer as 'advance_charge'.
   *
   * This way it won't get counted in metrics for scheduled donations.
   *
   * @param int $did
   *   Donation ID.
   */
  public function advanceCharge($did) {
    db_update('fundraiser_sustainers_log')
      ->fields(array('new_state' => 'advance_charge'))
      ->condition('did', $did)
      ->condition('new_state', 'scheduled')
      ->execute();
  }

  /**
   * Marks all scheduled log entries for a sustainer as 'changed_charge_day'.
   *
   * This way it won't get counted in metrics for scheduled donations.
   *
   * @param int $did
   *   Donation ID.
   */
  public function changedChargeDay($did) {
    db_update('fundraiser_sustainers_log')
      ->fields(array('new_state' => 'changed_charge_day'))
      ->condition('did', $did)
      ->condition('new_state', 'scheduled')
      ->execute();
  }
}
