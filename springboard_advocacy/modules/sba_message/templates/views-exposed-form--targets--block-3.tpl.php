<?php

/**
 * @file
 * This template handles the layout of the views exposed filter form.
 *
 * Variables available:
 * - $widgets: An array of exposed form widgets. Each widget contains:
 * - $widget->label: The visible label to print. May be optional.
 * - $widget->operator: The operator for the widget. May be optional.
 * - $widget->widget: The widget itself.
 * - $sort_by: The select box to sort the view using an exposed form.
 * - $sort_order: The select box with the ASC, DESC options to define order. May be optional.
 * - $items_per_page: The select box with the available items per page. May be optional.
 * - $offset: A textfield to define the offset of the view. May be optional.
 * - $reset_button: A button to reset the exposed filter applied. May be optional.
 * - $button: The submit button for the form.
 *
 * @ingroup views_templates
 */


?>
<?php if (!empty($q)): ?>
  <?php
  // This ensures that, if clean URLs are off, the 'q' is added first so that
  // it shows up first in the URL.
  print $q;
  ?>
<?php endif; ?>
<div class="views-exposed-form">
  <div class="views-exposed-widgets clearfix">
    <?php foreach ($widgets as $id => $widget): ?>

      <!-- Wrap the state and district form elements in a container -->
      <?php if (in_array('filter-search_district_name', array_keys($widgets)) && $id == 'filter-search_state'): ?>
        <div id="state-district-wrapper" class = "views-exposed-widget">
      <?php endif; ?>

      <!-- Wrap the state and district form elements in a container -->
      <?php if (in_array('filter-search_committee', array_keys($widgets)) && $id == 'filter-search_committee'): ?>
        </div><!-- close the radio widgets wrapper -->
        <div id="committee-wrapper" class = "views-exposed-widget">
      <?php endif; ?>



      <div id="<?php print $widget->id; ?>-wrapper" class="views-exposed-widget views-widget-<?php print $id; ?>">
        <?php if (!empty($widget->label)): ?>
          <label for="<?php print $widget->id; ?>">
            <?php print $widget->label; ?>
          </label>
        <?php endif; ?>
        <?php if (!empty($widget->operator)): ?>
          <div class="views-operator">
            <?php print $widget->operator; ?>
          </div>
        <?php endif; ?>
        <div class="views-widget">
          <?php print $widget->widget; ?>
        </div>
        <?php if (!empty($widget->description)): ?>
          <div class="description">
            <?php print $widget->description; ?>
          </div>
        <?php endif; ?>
      </div><!-- end views-exposed-widgets-->

      <!-- End of wrapping the state and district form elements in a container -->
      <?php if (in_array('filter-search_district_name', array_keys($widgets)) && $id == 'filter-search_district_name'): ?>
        </div>
        <div class = "radio-widgets">
      <?php endif; ?>

      <?php if (in_array('filter-search_committee', array_keys($widgets)) && $id == 'filter-search_committee'): ?>
      </div>
      <?php endif; ?>
    <?php endforeach; ?>
  </div>
  <div class="button-container">
    <div class="views-exposed-widget views-submit-button">
      <?php print $target_button; ?>
    </div>

    <!-- Quick target button -->
    <div class="views-exposed-widget views-targets-button-wrapper">
    <?php if (user_access('add target to action')): ?>
      <div class="target-button-header">Quick Group Targeting</div>
      <div class="target-button-help">Add this group in one click.</div>
      <div class="views-exposed-widget views-targets-button">
        <input type="button" id="quick-target" name="" value="Add Now" />
      </div>
    <?php endif; ?>
    </div>
    </div>


</div>
