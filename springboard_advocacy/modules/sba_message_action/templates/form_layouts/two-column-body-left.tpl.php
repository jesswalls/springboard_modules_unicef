<?php
/**
 * @file
 * This renders a message action form in 2 columns.
 */
?>


<div id="message-action-form-2col-column-wrapper" class="container-fluid action-body-left">

  <div class="row-fluid">
    <div id="left" class="span5 message-column">
      <?php if(!empty($image)): ?>
      <div id="image">
        <?php print $image; ?>
      </div>
      <?php endif; ?>

      <div id="call-to-action">
        <div id="call-to-action-call"><h2><?php print $call; ?></h2></div>
        <div id="call-to-action-body"> <?php print $body; ?></div>
        <?php if(!empty($quicksign)): ?>
          <div id="quicksign-container"><?php print $quicksign ?></div>
        <?php endif; ?>
        <?php if(!empty($participants)): ?>
          <div id="participants-container">
            <h4 >Recent participants</h4>
            <?php print $participants ?>
          </div>
        <?php endif; ?>
        <p><?php print $social ?></p>


      </div>
    </div>

    <div id="right" class="span7 message-column">
      <fieldset id="take-action-wrapper" class = "form-wrapper"><legend><?php print $form_legend ?></legend>
        <div class = "fieldset-wrapper">
          <?php print $open_form_tag ?>
          <?php print $message_fieldset; ?>
          <fieldset id="user-information-wrapper" class = "form-wrapper"><legend><?php print $user_legend ?></legend>
            <div class = "fieldset-wrapper">
              <p><?php print $webform ?></p>
            </div>
          </fieldset>
          <?php print drupal_render_children($form); ?>
          <?php print $close_form_tag ?>
        </div>
      </fieldset>
    </div>

  </div>
</div>
