/**
 * @file
 * Javascript functions for sustainer management page.
 */
Drupal.behaviors.fundraiserSustainer = {
  attach: function(context) { (function($) {

    /* Disable submit buttons on the 3 main forms when submitting */
    $('#fundraiser-sustainers-donation-amount-form').submit(function() {
      $('input[type=submit]', this).attr('disabled', 'disabled');
    });

    $('#fundraiser-sustainers-billing-update-form').submit(function() {
      $('input[type=submit]', this).attr('disabled', 'disabled');
    });

    $('#fundraiser-sustainers-cancel-form').submit(function() {
      $('input[type=submit]', this).attr('disabled', 'disabled');
    });

    // clear out the cancellation reason when it receives the focus for the first time.
    $('#edit-reason').one('focus', function() {
      $(this).val('');
    });

    // Trigger the focus so it will clear out the message if it hasn't been edited.
    $('#fundraiser-sustainers-cancel-form input[type=submit]').click(function() {
      $('#edit-reason').trigger('focus');
    });

  })(jQuery); }
}
