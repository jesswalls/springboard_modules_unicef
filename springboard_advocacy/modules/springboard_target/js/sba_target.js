(function ($) {

    $(document).ready(function () {
        // Remove jQuery uniform stylings
        if ($.isFunction($.fn.uniform)) {
            $('select').each(function () {
                $.uniform.restore(this);
            });
        }
    });
})(jQuery);