<?php
/**
 * @file
 * A class to represent a single day's worth of sustainer log data.
 */

/**
 * Class FundraiserSustainersDailySnapshot.
 */
class FundraiserSustainersDailySnapshot {

  /**
   * Today. Used for some calculations and display.
   *
   * @var DateTime
   */
  protected $today;

  /**
   * The day of this Snapshot.
   *
   * @var DateTime
   */
  protected $date;

  /**
   * The timestamp of the day start. Used for database queries.
   *
   * @var int
   */
  protected $beginTimestamp;

  /**
   * The timestamp of the day start of the following day.
   *
   * Used for database queries.
   *
   * @var int
   */
  protected $endTimestamp;

  /**
   * Number of charges originally scheduled.
   *
   * @var int
   */
  protected $scheduledCharges;

  /**
   * Value (in cents) of charges originally scheduled.
   *
   * @var int
   */
  protected $scheduledValue;

  /**
   * Number of charges that were retried on this day.
   *
   * @var int
   */
  protected $retriedCharges;

  /**
   * Value (in cents) retried on this day.
   *
   * @var int
   */
  protected $retriedValue;

  /**
   * Number of successful charges completed so far in this day.
   *
   * @var int
   */
  protected $successfulCharges;

  /**
   * Value (in cents) of successful charges completed.
   *
   * @var int
   */
  protected $successfulValue;

  /**
   * Number of charges that are rescheduled after failing to complete.
   *
   * @var int
   */
  protected $failedRescheduledCharges;

  /**
   * Value (in cents) rescheduled after failing to complete.
   *
   * @var int
   */
  protected $failedRescheduledValue;

  /**
   * Number of charges that permanently failed.
   *
   * @var int
   */
  protected $failedAbandonedCharges;

  /**
   * Value (in cents) that permanently failed.
   *
   * @var int
   */
  protected $failedAbandonedValue;

  /**
   * Number of charges that were auto-canceled.
   *
   * @var int
   */
  protected $failedAutocanceledCharges;

  /**
   * Value (in cents) that were auto-canceled.
   *
   * @var int
   */
  protected $failedAutocanceledValue;

  /**
   * Constructs a snapshot sets up some values, and loads data.
   *
   * @param DateTime $date
   *   The date of the desired snapshot.
   */
  public function __construct(DateTime $date) {
    $this->date = $date;
    $this->date->setTime(0, 0, 0);

    $this->beginTimestamp = $this->date->getTimestamp();

    $date_end = clone $this->date;
    $date_end->add(new DateInterval('P1D'));
    $date_end->setTime(0, 0, 0);
    $this->endTimestamp = $date_end->getTimestamp();

    $this->today = new DateTime();
    $this->today->setTime(0, 0, 0);

    $this->load();
  }

  /**
   * Get the DateTime instance for this snapshot.
   *
   * @return DateTime
   *   The DateTime for this snapshot data.
   */
  public function getDate() {
    return $this->date;
  }

  /**
   * Get the scheduled charges.
   *
   * @return int
   *   Number of charges scheduled.
   */
  public function getScheduledCharges() {
    return $this->scheduledCharges;
  }

  /**
   * Get the scheduled value.
   *
   * @return int
   *   Value in cents.
   */
  public function getScheduledValue() {
    return $this->scheduledValue;
  }

  /**
   * Get the count of charges that previously failed processing.
   *
   * @return int
   *   Count of sustainers.
   */
  public function getRetriedCharges() {
    return $this->retriedCharges;
  }

  /**
   * Get the value of retried charges.
   *
   * @return int
   *   Value in cents.
   */
  public function getRetriedValue() {
    return $this->retriedValue;
  }

  /**
   * Get the number of successfully processed sustainers for this report date.
   *
   * @return int
   *   Count of successes.
   */
  public function getSuccessfulCharges() {
    return $this->successfulCharges;
  }

  /**
   * Get the value of the successfully processed sustainer on this report date.
   *
   * @return int
   *   Value in cents.
   */
  public function getSuccessfulValue() {
    return $this->successfulValue;
  }

  /**
   * Get the number of sustainers that failed to process for this report date.
   *
   * Includes temporary and permanent failures.
   *
   * @return int
   *   Count of failures.
   */
  public function getFailedCharges() {
    return $this->getFailedRescheduledCharges() + $this->getFailedAbandonedCharges();
  }

  /**
   * Get the value of the sustainers that failed processing on this report date.
   *
   * Includes both temporary and permanent failures.
   *
   * @return int
   *   Value in cents.
   */
  public function getFailedValue() {
    return $this->getFailedRescheduledValue() + $this->getFailedAbandonedValue();
  }

  /**
   * Get the count of charges that permanently failed while processing.
   *
   * @return int
   *   Count of sustainers.
   */
  public function getFailedAbandonedCharges() {
    return $this->failedAbandonedCharges;
  }

  /**
   * Get the value of the abandoned sustainers.
   *
   * @return int
   *   Value in cents.
   */
  public function getFailedAbandonedValue() {
    return $this->failedAbandonedValue;
  }

  /**
   * Get the count of charges that were auto-canceled while processing.
   *
   * @return int
   *   Count of sustainers.
   */
  public function getFailedAutocanceledCharges() {
    return $this->failedAutocanceledCharges;
  }

  /**
   * Get the value of the auto-canceled sustainers.
   *
   * @return int
   *   Value in cents.
   */
  public function getFailedAutocanceledValue() {
    return $this->failedAutocanceledValue;
  }

  /**
   * Get the charges that failed on this report date but will be retried.
   *
   * @return int
   *   Count of sustainers.
   */
  public function getFailedRescheduledCharges() {
    return $this->failedRescheduledCharges;
  }

  /**
   * Get the value of charges failed on this report date but will be retried.
   *
   * @return int
   *   Value in cents.
   */
  public function getFailedRescheduledValue() {
    return $this->failedRescheduledValue;
  }

  /**
   * Indicates if we should warn about this snapshot's data not making sense.
   *
   * @return bool
   *   TRUE if the snapshot data doesn't match and needs investigation.
   */
  public function shouldWarn() {
    if ($this->getScheduledCharges() + $this->getRetriedCharges() != $this->getSuccessfulCharges() + $this->getFailedCharges()) {
      return TRUE;
    }
    elseif ($this->getScheduledValue() + $this->getRetriedValue() != $this->getSuccessfulValue() + $this->getFailedValue()) {
      return TRUE;
    }

    return FALSE;
  }

  /**
   * Populates the snapshot instance with data.
   */
  protected function load() {
    $this->initializeValues();
    $this->calculateValues();
  }

  /**
   * Calculates and sets the properties for this snapshot instance.
   */
  protected function calculateValues() {
    $this->calculateScheduledProperties();
    $this->calculateOtherProperties();
  }

  /**
   * Gets the order amount from a donation/order.
   *
   * Does not handle currency code. Assumes everything is in cents.
   *
   * @param int $did
   *   Donation/order ID.
   *
   * @return int
   *   The value in cents.
   */
  protected function getValueFromOrder($did) {
    $order = commerce_order_load($did);
    $wrapper = entity_metadata_wrapper('commerce_order', $order);

    return $wrapper->commerce_order_total->amount->value();
  }

  /**
   * Calculates the scheduled charges and value.
   */
  protected function calculateScheduledProperties() {
    // success, canceled, skipped, failed, retry, processing, NULL.
    $replacements = array(
      ':begin' => $this->beginTimestamp,
      ':end' => $this->endTimestamp,
    );

    $query = "SELECT did FROM {fundraiser_sustainers_log} WHERE (new_state = 'scheduled' OR (new_state = 'retry' AND old_state = 'processing')) AND next_charge >= :begin AND next_charge < :end";

    $result = db_query($query, $replacements);

    $count = 0;
    $total = 0;
    foreach ($result as $row) {
      $count++;
      $total += $this->getValueFromOrder($row->did);
    }

    $this->scheduledCharges = $count;
    $this->scheduledValue = $total;
  }

  /**
   * Calculates all other properties for the snapshot.
   */
  protected function calculateOtherProperties() {
    $retried_charges = 0;
    $retried_value = 0;

    $successes = 0;
    $success_value = 0;

    $rescheduled_charges = 0;
    $rescheduled_value = 0;
    $abandoned_charges = 0;
    $abandoned_value = 0;
    $autocanceled_charges = 0;
    $autocanceled_value = 0;

    $replacements = array(
      ':begin' => $this->beginTimestamp,
      ':end' => $this->endTimestamp,
    );
    // Get all log events that happened on this day.
    // Ordering these so the new transitions get checked first, and earlier
    // ones get ignored if there are multiple transitions per day.
    // @todo Is that a good idea?
    $results = db_query("SELECT did, old_state, new_state FROM {fundraiser_sustainers_log} WHERE timestamp >= :begin AND timestamp < :end ORDER BY lid DESC", $replacements);

    foreach ($results as $row) {

      // Sustainer was born and at best is going into locking and processing.
      // Otherwise the charge might be getting advanced or changed.
      if (is_null($row->old_state) && $row->new_state != 'auto_canceled') {
        continue;
      }

      // Special case, master donation.
      if ($row->old_state == 'success' && $row->new_state == 'success') {
        continue;
      }

      // Get the amount value from the related commerce order.
      $value = $this->getValueFromOrder($row->did);
      if ($row->old_state == 'processing') {

        if ($row->new_state == 'success') {
          $successes++;
          $success_value += $value;
        }
        else {
          if ($row->new_state == 'retry') {
            $rescheduled_charges++;
            $rescheduled_value += $value;
          }
          elseif ($row->new_state == 'failed') {
            $abandoned_charges++;
            $abandoned_value += $value;
          }
        }
      }
      elseif ($row->old_state == 'retry' && $row->new_state == 'processing') {
        $retried_charges++;
        $retried_value += $value;
      }
      elseif ($row->new_state == 'auto_canceled') {
        $autocanceled_charges++;
        $autocanceled_value += $value;
      }
    }

    $this->retriedCharges = $retried_charges;
    $this->retriedValue = $retried_value;

    $this->successfulCharges = $successes;
    $this->successfulValue = $success_value;

    $this->failedRescheduledCharges = $rescheduled_charges;
    $this->failedRescheduledValue = $rescheduled_value;
    $this->failedAbandonedCharges = $abandoned_charges;
    $this->failedAbandonedValue = $abandoned_value;
    $this->failedAutocanceledCharges = $autocanceled_charges;
    $this->failedAutocanceledValue = $autocanceled_value;
  }

  /**
   * Sets initial values to zero.
   */
  protected function initializeValues() {
    $this->scheduledCharges = 0;
    $this->scheduledValue = 0;
    $this->retriedCharges = 0;
    $this->retriedValue = 0;

    $this->successfulCharges = 0;
    $this->successfulValue = 0;

    $this->failedRescheduledCharges = 0;
    $this->failedRescheduledValue = 0;
    $this->failedAbandonedCharges = 0;
    $this->failedAbandonedValue = 0;
    $this->failedAutocanceledCharges = 0;
    $this->failedAutocanceledValue = 0;

  }
}
