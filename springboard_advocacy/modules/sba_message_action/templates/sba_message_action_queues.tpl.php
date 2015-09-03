<?php print $tabs; ?>
<h2>Current Message Queue Activity</h2>
<div class="container queue-overview-container">
  <div class="row">
    <div class="span4">
      <div class="well">
        <h2 class="text-info"><?php print $queueReadyItems; ?></h2>
        Ready
      </div>
    </div>
    <div class="span4">
      <div class="well">
        <h2 class="text-info"><?php print $queuePausedItems; ?></h2>
        Paused
      </div>
    </div>
    <div class="span4">
      <div class="well">
        <h2 class="text-info"><?php print $queueCanceledItems; ?></h2>
        Canceled
      </div>
    </div>
  </div>
  <h2>Queue Actions:</h2>
  <div class="row">
    <div class="span12">
      <div class="well">
            <?php print $queueActionsForm; ?>
        </div>
      </div>
    </div>
  </div>
</div>
