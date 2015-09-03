(function ($) {
    /**
     * Overrides  Drupal.ACDB.prototype.search in order to
     * pass extra options for state and chamber
     * to the autocomplete menu callback
     */

    Drupal.jsAC.prototype.onkeydown = function (input, e) {
        if (!e) {
            e = window.event;
        }

        switch (e.keyCode) {

            case 40: // down arrow.
                this.selectDown();
                return false;
            case 38: // up arrow.
                this.selectUp();
                return false;
            case 13: // enter
                if(this.db.uri.indexOf('message-action') != -1) {
                    return false;
                }
                return true;
            default: // All other keys.
                return true;
        }
    };
    /**
     * Fills the suggestion popup with any matches received.
     */
    Drupal.jsAC.prototype.found = function (matches) {
        // If no value in the textfield, do not show the popup.
        if (!this.input.value.length) {
            return false;
        }

        // Prepare matches.
        var ul = $('<ul></ul>');
        var ac = this;
        if(this.db.uri.indexOf('message-action') != -1) {

            var message = matches[Object.keys(matches)[Object.keys(matches).length - 1]];
            delete matches[Object.keys(matches)[Object.keys(matches).length - 1]]
        }

        for (key in matches) {

            $('<li></li>')
                .html($('<div></div>').html(matches[key]))
                .mousedown(function () { ac.select(this); })
                .mouseover(function () { ac.highlight(this); })
                .mouseout(function () { ac.unhighlight(this); })
                .data('autocompleteValue', key)
                .appendTo(ul);
        }

        if(this.db.uri.indexOf('message-action') != -1 && Object.keys(matches).length > 0) {
            $('<li></li>')
                .html($('<strong></strong>').html(message))
                .appendTo(ul);
        }

        // Show popup with matches, if any.
        if (this.popup) {
            if (ul.children().length) {
                $(this.popup).empty().append(ul).show();
                $(this.ariaLive).html(Drupal.t('Autocomplete popup'));
            }
            else {
                $(this.popup).css({ visibility: 'hidden' });
                this.hidePopup();
            }
        }
    };


    Drupal.ACDB.prototype.search = function (searchString) {
        var db = this;
        this.searchString = searchString;

        //this is the extent of the change
        if(db.uri.indexOf('message-action') != -1) {
            var chamber = $('select', '#edit-search-committee-chamber-wrapper').val();
            var state = $("#edit-search-state").val();
            searchString = searchString + "/" +  state + "/" + chamber;
            this.searchString = searchString;
        }

        searchString = searchString.replace(/^\s+|\s+$/, '');
        if (searchString.length <= 0 ||
            searchString.charAt(searchString.length - 1) == ',') {
            return;
        }
        if (this.cache[searchString]) {
            return this.owner.found(this.cache[searchString]);
        }
        if (this.timer) {
            clearTimeout(this.timer);
        }
        this.timer = setTimeout(function () {
            db.owner.setStatus('begin');
            $.ajax({
                type: 'GET',
                url: db.uri + '/' + Drupal.encodePath(searchString),
                dataType: 'json',
                success: function (matches) {
                    if (typeof matches.status == 'undefined' || matches.status != 0) {
                        //db.cache[searchString] = matches;
                        if (db.searchString == searchString) {
                            db.owner.found(matches);
                        }
                        db.owner.setStatus('found');
                    }
                },
                error: function (xmlhttp) {
                    alert(Drupal.ajaxError(xmlhttp, db.uri));
                }
            });
        }, this.delay);
    };


})(jQuery);