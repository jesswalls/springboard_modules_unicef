<?php
/**
 * @file
 * Theme the advocacy dashboard views.
 *
 * Available variables:
 * - $sections: an array containing the page elements and content related to
 * each view.
 */
?>
<?php foreach ($sections as $section): ?>
  <?php if (isset($section['css'])):
    drupal_add_css($section['css']); ?>
  <?php endif; ?>
  <?php if (isset($section['js'])):
    drupal_add_js($section['js']); ?>
  <?php endif; ?>
  <div class="types-wrapper p2p-views">
    <?php if (isset($section['header'])): ?>
      <h2 class="types"><?php print $section['header'];?></h2>
    <?php endif; ?>
    <div class="buttons-wrapper">
      <?php if (isset($section['manage_link'])): ?>
        <div class="sba-button"><?php print l($section['manage_link']['title'], $section['manage_link']['href'], array('attributes' => array('class' => array('button', 'more-button')))); ?></div>
      <?php endif; ?>
      <?php if (isset($section['create_link'])): ?>
        <div class="sba-button"><?php print l($section['create_link']['title'], $section['create_link']['href'], array('attributes' => array('class' => array('button', 'sba-add-button')))); ?></div>
      <?php endif; ?>
    </div>
    <?php if (isset($section['content'])): ?>
      <?php print $section['content']; ?>
      <?php if (isset($section['viewmore_link'])): print l($section['viewmore_link']['title'], $section['viewmore_link']['href'], array('attributes' => array('class' => array('button', 'more-button')))); endif; ?>
    <?php endif; ?>
  </div>
<?php endforeach; ?>