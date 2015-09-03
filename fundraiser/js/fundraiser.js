Drupal.behaviors.fundraiserBehavior = {
  attach: function(context, settings) { (function($) {

  // Auto-populate the internal name field
  $("#edit-title").blur(function() {
    var title = $(this).attr('value');
    var currently = $("#edit-internal-name").attr('value');
    if (currently.length == 0) {
      $("#edit-internal-name").val(title);
    }
  });

  // Auto-populate label fields when amount is entered.
  $('#ask-amounts input[id*="amount"]').blur(function() {
    var amount = $(this).val();
    var label = $(this).parents('tr').find('input[id*="label"]').val();
    if (label == '') {
      $(this).parents('tr').find('input[id*="label"]').val("$" + amount);
    }
  });

  // Payment selection triggered changes.
  var paymentImages = function() {
      var gateway = $(this).val();
      var paymentId = this.id;
      var text = Drupal.settings.fundraiser[gateway].text;
      var labelImg = Drupal.settings.fundraiser[gateway].selected_image;
      // Automatically change submit button text when payment gateway selected.
      $("#edit-submit").val(text);
      $('label[for='+paymentId+'] img').attr('src', labelImg);
      $("input[name='submitted[payment_information][payment_method]']").each(function(gateway) {
          if (!$(this).is(":checked")) {
              var gateway = $(this).val();
              var paymentId = this.id;
              var labelImg = Drupal.settings.fundraiser[gateway].unselected_image;
              $('label[for='+paymentId+'] img').attr('src', labelImg);
          }
      })
  }
  var hoverInImage = function() {
      var gateway = $(this).attr('data-gateway');
      var paymentId = this.id;
      var labelImg = Drupal.settings.fundraiser[gateway].selected_image;
      $(this).attr('src', labelImg);
  }
  var hoverOutImage = function() {
      var gateway = $(this).attr('data-gateway');
      var parentLabel = $(this).parent();
      var labelParent = parentLabel.attr('for');
      var checked = $('#' + labelParent).is(':checked');
      if (!checked) {
          var labelImg = Drupal.settings.fundraiser[gateway].unselected_image;
          $(this).attr('src', labelImg);
      }
  }
  var enabledGateways = Drupal.settings.fundraiser.enabled_count;
  if (enabledGateways >= 1) {
      // Change payment option image based on payment selection and hover.
      $('input[class*="fundraiser-payment-methods"]').change(paymentImages);
      // Set button text when page first loaded
      $('input[class*="fundraiser-payment-methods"]').trigger('change');
  }
  // Show payment option "selected" images when rolling over.
  $('img[id*="payment-option-img"]').hover(hoverInImage, hoverOutImage);

  })(jQuery); }
}
