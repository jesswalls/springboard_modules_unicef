<?php
/**
 * @file
 * Display a delivered messages confirmation
 *
 * Available variables:
 * - $undeliverable title.
 * - $message_count - an integer
 * - $target_count - an integer
 * - $message_count_text A string in the format "We were unable to deliver X messages to X targets."
 * - $targets - a keyed array containing the message targets
 * -- $targets[]['target_person'] - The target's name, district and party, if applicable
 * -- $targets[]['link'] - a link to a popup window with the message text

 * Other variables:
 *
 * - $messages A message-id keyed array of all messages, their recipients, the full target objects
 * - $contact The full user contact array
 *
 * @see template_preprocess()
 * @see sba_message_action_preprocess_webform_confirmations_delivered()
 */
?>

<div id="sba-delivered-messages-container">
  <h3 id="sba-delivered-title"><?php print $delivered_title ?></h3>
  <div id="delivered-messages-container">
    <p><?php print $message_count_text ?></p>
    <br />
    <ul class="message-recipient-list item-list">
      <?php foreach($targets as $target): ?>
        <li>
          <?php print $target['person']; ?>
          <?php if(!empty($target['link'])): ?>
              (<?php print $target['link']; ?>)
          <?php endif;?>
        </li>
      <?php endforeach; ?>
    </ul>
  </div>
</div>

