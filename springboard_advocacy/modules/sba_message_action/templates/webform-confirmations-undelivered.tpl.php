<?php
/**
 * @file
 * Display an undelivered messages confirmation
 *
 * Available variables:
 * - $undeliverable title.
 * - $message_count - an integer
 * - $target_count - an integer
 * - $message_count_text A string in the format "We were unable to deliver X messages to X targets."
 * - $show_message_text - a string
 * - $messages_out - a keyed array containing the undeliverable messages
 * -- $messages_out[]['target'] - The targets name with a link to the target's website if extant
 * -- $messages_out[]['subject'] - the message subject
 * -- $messages_out[]['message'] - The message

 * Other variables:
 *
 * - $messages A message-id keyed array of all messages, their recipients, the full target objects
 * - $contact The full user contact array
 *
 * @see template_preprocess()
 * @see sba_message_action_preprocess_webform_confirmations_undelivered()
 *
 */
/**
 * Javscript is included in the template so that it is
 * available when the confirmation is displayed on a redirect as well as
 * the default confirmation page.
 */
?>
<div id="sba-undeliverable-messages-container">
  <h3><?php print $undeliverable_title ?></h3>
  <p><?php print $message_count_text ?></p>
  <?php foreach($messages_out as $message): ?>
    <div class="sba-undeliverable-messages-message">
      <div class="sba-undeliverable-messages-message-recipient">
        <?php print $message['target'] ?>
      </div>
      <div class="sba-undeliverable-messages-message-subject">
        <?php print $message['subject'] ?> (<a href = "#" class="sba-message-show-message"><?php print $show_message_text ?></a>)
      </div>
      <div class="sba-undeliverable-message-body" style="display:none">
        <?php print $message['message'] ?>
      </div>
    </div>
  <?php endforeach; ?>
</div>

<script language="javascript">
  jQuery('.sba-message-show-message').on('click', function () {
    var message = jQuery(this).parents('.sba-undeliverable-messages-message-subject').siblings('.sba-undeliverable-message-body');
    message.toggle('slow', function () {
      var link = jQuery(this).siblings('.sba-undeliverable-messages-message-subject').children('.sba-message-show-message');
      if (message.is(':visible')) {
        link.text('Hide message')
      }
      if (!message.is(':visible')) {
        link.text('Show message')
      }
    });
    return false;
  })
</script>

