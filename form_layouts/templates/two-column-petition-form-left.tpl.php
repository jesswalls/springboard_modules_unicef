<?php
/**
 * @file
 * This template renders a petition enabled node in 2 columns.
 */

?>

<div id="webform-form-column-wrapper" class="form-layout-container form-left">
  <div class="form-row">

    <div id="left" class="form-col">
      <div id="webform-form" class="form-wrapper">
        <div class="form-wrapper-inner">
          <?php print render($element['webform']); ?>
        </div>
      </div>
      <div id="petition-quick-sign" class="form-wrapper">
        <div class="form-wrapper-inner">
          <?php print render($element['sba_quicksign']); ?>
        </div>
      </div>
    </div>

    <div id="right" class="form-col">
      <h1 class="form-layout-title"><?php print render($element['title']); ?></h1>
      <?php print render($element['body']); ?>
      <?php $view = views_get_view('recent_petition_signatures');
      $view->set_display('block_1');
      $view->set_arguments(array(arg(1)));
      $view->pre_execute();
      $view->execute();?>
      <?php if (isset($view->total_rows) && $view->total_rows): ?>
      <h2><?php print $view->get_title(); ?></h2>
      <?php endif; ?>
      <?php print $view->preview('block_1'); ?>
    </div>

  </div>
</div>
