(function ($) {
    $(document).ready(function(){
        $('.webform-client-form input.required, .webform-client-form select.required').each(function(){
            if (!$(this).val()) {
                $(this).addClass('error');
            }
        });
        $('.webform-component-checkboxes.control-group span.form-required').each(function(){
            if (!$(this).closest('.webform-component-checkboxes.control-group').find('input').prop('checked')) {
                $(this).closest('.webform-component-checkboxes.control-group').addClass('error');
            }
        });
        $('.webform-component-radios.control-group span.form-required').each(function(){
            if (!$(this).closest('.webform-component-radios.control-group').find('input').prop('checked')) {
                $(this).closest('.webform-component-radios.control-group').addClass('error');
            }
        });
    });
})(jQuery);