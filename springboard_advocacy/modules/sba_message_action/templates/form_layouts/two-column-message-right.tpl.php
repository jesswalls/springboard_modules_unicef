<?php
/**
 * @file
 * This renders a message action form in 2 columns.
 */
?>


<div id="message-action-form-2col-column-wrapper" class="container-fluid action-message-right">
  <div class="row-fluid">
    <?php if(!empty($image)): ?>
      <div id="call-to-action" class="span8">
        <div id="call-to-action-call"><h2><?php print $call; ?></h2></div>
        <div id="call-to-action-body"> <?php print $body; ?></div>
      </div>
      <div id="image" class = "span4">
        <?php print $image; ?>
      </div>
    <?php else: ?>
      <div id="call-to-action" class="span12">
        <div id="call-to-action-call"><h2><?php print $call; ?></h2></div>
        <div id="call-to-action-body"> <?php print $body; ?></div>
      </div>
    <?php endif; ?>
  </div>
  <fieldset id="take-action-wrapper" class = "form-wrapper"><legend><?php print $form_legend ?></legend>
    <div class = "fieldset-wrapper">
      <div class="row-fluid">
        <?php print $open_form_tag ?>
        <div id="left" class="span5 message-column">
          <fieldset id="user-information-wrapper" class = "form-wrapper"><legend><?php print $user_legend ?></legend>
            <div class = "fieldset-wrapper">
              <p><?php print $webform ?></p>
            </div>
          </fieldset>
          <?php print drupal_render_children($form); ?>
          <p><?php print $social ?></p>

        </div>
        <div id="right" class="span7 message-column">
          <?php print $message_fieldset; ?>
        </div>
        <?php print $close_form_tag ?>
        <?php if(!empty($quicksign)): ?>
          <div id="quicksign-container" class="span7"><?php print $quicksign ?></div>
        <?php endif; ?>
        <?php if(!empty($participants)): ?>
          <div id="participants-container" class = "span7">
            <h4>Recent participants</h4>
            <?php print $participants ?>
          </div>
        <?php endif; ?>
      </div>
    </div>
  </fieldset>
</div>
