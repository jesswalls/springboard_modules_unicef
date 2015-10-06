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
  function paymentImages() {
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

  // Change payment method image on hover
  function hoverInImage() {
      var gateway = $(this).attr('data-gateway');
      var paymentId = this.id;
      var labelImg = Drupal.settings.fundraiser[gateway].selected_image;
      $(this).attr('src', labelImg);
  }

  // Change payment method image after hover to selected default.
  function hoverOutImage() {
      var gateway = $(this).attr('data-gateway');
      var parentLabel = $(this).parent();
      var labelParent = parentLabel.attr('for');
      var checked = $('#' + labelParent).is(':checked');
      if (!checked) {
          var labelImg = Drupal.settings.fundraiser[gateway].unselected_image;
          $(this).attr('src', labelImg);
      }
  }

  // Call change to payment method images and submit button on page load and selection/hover.
  try {
      if (Drupal.settings.fundraiser.enabled_count >= 1) {
          // Set button text when page first loaded
          // Loop over payment method radio fields to find selected
          var paymentMethods = $('input[class*="fundraiser-payment-methods"]');
          var paymentMethodSelected;
          for(var i = 0; i < paymentMethods.length; i++){
              if(paymentMethods[i].checked){
                  paymentMethodSelected = paymentMethods[i];
              }
          }
          // Call our button/image change function with checked payment method on load.
          paymentImages.call(paymentMethodSelected);

          // Change payment option image based on payment selection and hover.
          $('input[class*="fundraiser-payment-methods"]').change(paymentImages);
      }
  } catch(e) {}
  // Show payment option "selected" images when rolling over.
  $('img[id*="payment-option-img"]').hover(hoverInImage, hoverOutImage);

  })(jQuery); }
}
