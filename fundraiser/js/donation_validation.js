(function($) {
  Drupal.behaviors.springboardForms = {
    attach: function (context, settings) {
      // jQuery clearEle definition: clears out validation classes
      (function($){
        $.fn.clearEle = function() {
          return this.each(function() {
            $(this).removeClass('valid');
            $(this).next('label').remove();
            $(this).parents('.success').removeClass('success');
            $(this).parents('.error').removeClass('error');
            this.value = '';
          });
        }
      })(jQuery);

      $(window).ready(function(){
        // Turn autocomplete off on CC and CVV form elements.
        $('input[name*="card_number"], input[name*="card_cvv"]').attr('autocomplete','off');

        // Helper function, provides the total display.
        function _recalculate_quantity_total() {
          $('#quantity-total').empty();
          var amount = $('input[type="radio"][name*="amount"]:checked').val();
          if (amount == 'other') {
            amount = $('input[name*="other_amount"]').val();
          }
          // prevent total from displaying NaN if other amount input is incorrectly formatted.
          if (isNaN(amount) === true) {
            var total = 0.00;
          }
          else {
            var total = $('select[name*="quantity"]').val() * amount;
          }
          $('select[name*="quantity"]').after('<span id="quantity-total">Total: ' + Drupal.settings.fundraiser.currency.symbol + total + '</span>');
        }

        // When the amount changes, change the displayed total.
        $('select[name*="quantity"]').change(function() {
          _recalculate_quantity_total();
        });
        // And do the same if the amount is changed
        $('input[name*="amount"]').change(function() {
          _recalculate_quantity_total();
        });
        // And do the same if the other_amout is changed
        $('input[name*="other_amount"]').change(function() {
          _recalculate_quantity_total();
        });

        // Custom Validation Regex rules: AMEX, VISA, MASTERCARD, DISCOVER, Diner's Club, JCB
        $.validator.addMethod('creditcard', function(value, element) {
          return this.optional(element) || /^(?:4[0-9]{12}(?:[0-9]{3})?|5[1-5][0-9]{14}|6(?:011|5[0-9][0-9])[0-9]{12}|3[47][0-9]{13}|3(?:0[0-5]|[68][0-9])[0-9]{11}|(?:2131|1800|35\d{3})\d{11})$/i.test(value);
          // Doesn't work for Australian Bankcard, Dankort (PBS) cards or Switch/Solo (Paymentech)
          // Bankcard regexp below needs fixing
          //^5610\5[6-9]d{2}\d{4}\d{4}$
        }, "Enter a valid credit card number");

        // Custom amount validation
        $.validator.addMethod('amount', function(value, element) {
          // Add regexp
          return this.optional(element) || /^[0-9]*(\.\d{1,3})*(,\d{1,3})?$/i.test(value);
        }, "Enter a valid amount");

        // Custom zipcode validation
        $.validator.addMethod('zipcode', function(value, element) {
          // Validate zip code when country is US.
          var country_field = $(':input[name*="[country]"]');
          if (country_field.length && country_field.val() == 'US') {
            return this.optional(element) || /(^\d{5}((-|\s)\d{4})?$)|(^[ABCEGHJKLMNPRSTVXY]{1}\d{1}[A-Z]{1} *\d{1}[A-Z]{1}\d{1}$)/i.test(value);
          }
          return true;
        }, "Enter a valid zipcode");

        // Instantiate Form Validation
        var donationValidate = $('.fundraiser-donation-form').validate({
          // Custom keyup function checking for tab key (9) and when value is empty
          onkeyup: function (element, event) {
            if ($(element).next('.error')[0]){
              if (event.which === 9 && element.value === "") {
                return;
              } else {
                this.element(element);
              }
            }
          },
          onfocusout: function (element) {
            // Callback for real-time onfocusout of form elements
            var isValid = $(element).valid();
            //
            if (typeof validateKeyCallback != "undefined" && isValid == 0) {
              // Set status to 0
              window.validateKeyCallback.status = 0;
              validateKeyCallback.error(element);
            } else if (typeof validateKeyCallback != "undefined" && isValid == 1) {
              // Set status to 1
              window.validateKeyCallback.status = 1;
              validateKeyCallback.success(element);
            }
          },
          highlight: function(element) {
            $(element).addClass('key-validate');
            $(element).closest('.control-group').removeClass('success').addClass('error');
          },
          success: function(element) {
            $(element).text('OK').addClass('valid').closest('.control-group').removeClass('error').addClass('success');
          }
        });

        // On change and keyup check form status
        $(".fundraiser-donation-form :input.key-validate").bind('change keyup', function() {
          donationValidate.element('#' + $(this).attr('id'));
        });

        // On submission hide the button and replace it with a new value.
        // Wrap the click in a once trigger to be sure that we bind it the one time.
        $('.fundraiser-donation-form #edit-submit').once(function() {
          $('.fundraiser-donation-form #edit-submit').click(function() {
            // Validate the form
            if (donationValidate.form()) {
              $(this).hide();
              $('.fundraiser_submit_message').hide();
              $(this).after('<div class="donation-processing-wrapper">' +
                '<p class="donation-processing">Processing' +
                '<span class="donation-processing-spinner"></span>' +
                '</p>' +
                '</div>');
            }
          });
        });
        // Iterate validation settings and apply rules.
        for ($key in Drupal.settings.fundraiser.js_validation_settings) {
          if ($('input[name*="' + $key + '"]')[0]) {
            $('input[name*="' + $key + '"]').rules("add", Drupal.settings.fundraiser.js_validation_settings[$key]);
          }
        }
        // Other Amount
        if ($('input[name*="other_amount"]')[0]) {
          $('input[name*="other_amount"]').rules("add", {
            required: {
              depends: function(element) {
                if ($('input[type="radio"][name$="[amount]"][value="other"]').is(":checked"))
                  return true;
                else
                  return false;
              }
            },
            amount: true,
            min: parseFloat(Drupal.settings.fundraiserWebform.minimum_donation_amount),
            messages: {
              required: "This field is required",
              amount: "Enter a valid amount",
              min: "The amount entered is less than the minimum donation amount."
            }
          });
        }

        // Focus and Blur conditional functions
        $('input[type="radio"][name*="amount"]').change(function(){
          if ($(this).val() == 'other') {
            $('input[name*="other_amount"]').focus();
          } else {
            $('input[name*="other_amount"]').clearEle();
          }
        });
        $('input[name*="other_amount"]').focus(function(){
          $('input[type="radio"][name*="amount"][value="other"]').attr('checked', 'checked');
        })

        // Runs on Other Amount field
        $('input[name*="other_amount"]').blur(function(){
          var value = this.value;
          // check for custom validation function object
          if (typeof(window.customValidation) === 'undefined') {
            // If the value has length and includes at least one integer
            if (value.length > 0 && this.value.match(/\d/g)) {
              // if no period period
              if (!value.match(/\./)) {
                // no decimals: strip all other chars, add decimal and 00
                value = value.replace(/[^\d]+/g,'') + '.00';
              } else {
                // Remove all non-integer/period chars
                value = value.replace(/[^\d\.]+/g,'')
                  // make first decimal unique
                  .replace(/\./i,'-')
                  // replace subsequent decimals
                  .replace(/\./g,'')
                  // set first back to normal
                  .replace('-','.')
                  // match the last two digits, removing others
                  .match(/\d+\.\d{0,2}|\.\d{0,2}/);
                var newValue = value[0];
                if (newValue.match(/\.\d{2}/)) {
                } else if (newValue.match(/\.\d{1}/)) {
                  value += '0';
                } else {
                  value += '00';
                }
              }
              this.value = value;
              // total should be recalculated as value has changed without triggering .change() event handler.
              _recalculate_quantity_total();
              $(this).valid();
            }
          } else {
            window.customValidation(value);
            $(this).valid();
          }
        });

        // Ability to override the default message
        jQuery.extend(jQuery.validator.messages, {
          required: "This field is required",
          remote: "Please fix this field",
          email: "Enter a valid email address",
          url: "Enter a valid URL",
          date: "Enter a valid date",
          dateISO: "Enter a valid date (ISO)",
          number: "Must be a number", // changed
          digits: "Enter only digits",
          creditcard: "Enter a valid credit card number",
          equalTo: "Enter the same value again",
          accept: "Enter a value with a valid extension",
          maxlength: jQuery.validator.format("Enter no more than {0} characters"),
          minlength: jQuery.validator.format("Enter at least {0} characters"),
          rangelength: jQuery.validator.format("Enter a value between {0} and {1} characters long"),
          range: jQuery.validator.format("Enter a value between {0} and {1}"),
          max: jQuery.validator.format("Enter a value less than or equal to {0}"),
          min: jQuery.validator.format("Enter a value greater than or equal to {0}")
          });
        // Small helper item
        $('select').each(function(){
          if ($(this).next().is('select')) {
            $(this).next().addClass('spacer');
          }
        });
        // Implementing our own alert close
        // Bootstrap.js uses the .on method, not added until jQuery 1.7
        $('.close').click(function(){
          $(this).closest('.alert').fadeOut();
        });

      }); // window.ready
    } // attach.function
  } // drupal.behaviors
})(jQuery);
