(function ($) {

    Drupal.behaviors.SpringboardTaxonomyEditForm = {
        attach: function(context, settings) {
            // Do all of this only once, on page load.
            if ($('#edit-springboard-taxonomy-options').hasClass('springboard-taxonomy-edit-form-ready'))
                return;

            // Columnize the Legislative Issues list based on the average label width.
            var labelWidthsTotal = 0;
            var labelCount = 0;
            $('#edit-springboard-taxonomy-options .field-name-field-sba-legislative-issues .form-type-checkbox').each(function(){
                labelWidthsTotal += $(this).find('label').outerWidth();
                labelCount++;
            });
            var checkboxWidth =
                $('#edit-springboard-taxonomy-options .field-name-field-sba-legislative-issues .form-type-checkbox input')
                    .outerWidth()
            ;
            if (labelCount > 0) {
                var averageLabelWidth = labelWidthsTotal / labelCount;
                var bufferWidth = averageLabelWidth * 1.2;  // Add 20% buffer.
                var columnWidth = Math.ceil(averageLabelWidth + checkboxWidth + bufferWidth);
                $('#edit-springboard-taxonomy-options .field-name-field-sba-legislative-issues .form-type-checkbox')
                    .parent().columnize({width: columnWidth})
                ;
            }

            // Columnize the Organization Issues list
            labelWidthsTotal = labelCount = 0;
            $('#edit-springboard-taxonomy-options .field-name-field-sba-organization-issues .form-type-checkbox').each(function(){
                labelWidthsTotal += $(this).find('label').outerWidth();
                labelCount++;
            });
            if (labelCount > 0) {
                // When a top-level item is changed, update all of its descendants to match.
                var onChange = function(e) {
                    var isChecked = $(this).parent().find('input:not(.sba-term-indent)').get(0).checked;
                    $(this).parents('.sba-term-group').find('input.sba-term-indent').attr('checked', isChecked);
                }
                // Wrap groups and attach click behavior.
                var jqContainer = $('#edit-springboard-taxonomy-options .field-name-field-sba-organization-issues .form-type-checkbox').parent();
                console.log(jqContainer)
                $('#edit-springboard-taxonomy-options .field-name-field-sba-organization-issues .form-type-checkbox').each(function(){
                    if (!$(this).find('input').hasClass('sba-term-indent')) {
                        $(this).find('input').change(onChange);
                        // Create a new group for this top-level term.
                       jqContainer.append('<div class="sba-term-group dontsplit"></div>');
                    }
                    $(this).appendTo(jqContainer.find('div.sba-term-group:last'));
                });
                averageLabelWidth = labelWidthsTotal / labelCount;
                bufferWidth = averageLabelWidth * 1.3;
                columnWidth = Math.ceil(averageLabelWidth + checkboxWidth + bufferWidth);

                jqContainer.columnize({width: columnWidth});
            }

            // Done.
            $('#edit-springboard-taxonomy-options').addClass('springboard-taxonomy-edit-form-ready');

        }
    };

})(jQuery);