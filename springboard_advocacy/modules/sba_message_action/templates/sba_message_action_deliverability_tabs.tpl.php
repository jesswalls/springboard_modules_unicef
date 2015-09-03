<ul class="tabs secondary">
  <?php if(user_access('view springboard advocacy reports')) { ?>
    <li><a class="<?php print preg_match('@performance@', $_SERVER['REQUEST_URI']) ? 'active':''; ?>" href="<?php print '/springboard/node/'.$nodeId.'/performance'; ?>">Overview</a></li>
  <?php } ?>
  <?php if(user_access('download springboard advocacy failed messages')) { ?>
    <li ><a class="<?php print preg_match('@queue@', $_SERVER['REQUEST_URI']) ? 'active':''; ?>" href="<?php print '/springboard/node/'.$nodeId.'/message-queue'; ?>">Manage Queue</a></li>
  <?php } ?>
  <?php if(user_access('view and administer springboard advocacy message queues')) { ?>
    <li ><a class="<?php print preg_match('@download@', $_SERVER['REQUEST_URI']) ? 'active':''; ?>" href="<?php print '/springboard/node/'.$nodeId.'/download-failed-messages'; ?>">Download Failed Messages</a></li>
  <?php } ?>
</ul>