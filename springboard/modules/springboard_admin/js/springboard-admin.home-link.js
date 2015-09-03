(function ($) {

Drupal.springboardAdminHomeLink = Drupal.springboardAdminHomeLink || {};

/**
 * Attach behavior to adjust the links placement.
 */
Drupal.behaviors.springboardAdminHomeLink = {
  attach: function(context) {
    // Adjust the top setting of the link if the toolbar is active.
    if ($('#toolbar', context).length) {
      Drupal.springboardAdminHomeLink.toolbarAdjust();

      $(window).resize(function() {
        Drupal.springboardAdminHomeLink.toolbarAdjust();
      });
    }
  }
};

/**
 * Ajdust the top setting to work with the toolbar.
 */
Drupal.springboardAdminHomeLink.toolbarAdjust = function() {
  $('#springboard-admin-home-link').css('top', Drupal.toolbar.height());
};

})(jQuery);
