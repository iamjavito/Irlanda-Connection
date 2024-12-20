
<div class="page">
  <header class="section-header" role="banner">
    <div class="section-branding">
      <?php if ($logo): ?>
        <div class="desk-trigger">
          <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" class="site-logo"><img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" /></a>
        </div>
        <div class="mob-trigger">
          <img class="menu-icon" src="/sites/all/themes/irlanda_connection/images/icons/menu-icon.png">
          <img class="close-icon" src="/sites/all/themes/irlanda_connection/images/icons/x-icon.png">
          <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" class="site-logo"><img src="sites/default/files/storage/logo_mob.png" alt="<?php print t('Home'); ?>" /></a>
        </div>
      <?php endif; ?>
      <?php if ($site_name || $site_slogan): ?>
        <?php if ($site_name): ?>
          <h1 class="site-name">
            <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><span><?php print $site_name; ?></span></a>
          </h1>
        <?php endif; ?>

        <?php if ($site_slogan): ?>
          <h2 class="site-slogan"><?php print $site_slogan; ?></h2>
        <?php endif; ?>
      <?php endif; ?>
    </div>
    <div class="section-navbar">
      <?php print render($page['navigation']); ?>
    </div>
    <?php print render($page['header']); ?>
  </header>
  <div class="section-header-img">
    <?php print render($page['header_image']); ?>
  </div>
  <div class="section-main">
    <div class="section-content" role="main">
      <?php print render($page['sidebar_first']); ?>
      <div class="region-main-content" id="main-content">
        <?php print render($page['content']); ?>
        <?php print render($title_prefix); ?>
        <?php print render($title_suffix); ?>
        <?php print render($tabs); ?>
        <?php if ($action_links): ?>
          <ul class="action-links"><?php print render($action_links); ?></ul>
        <?php endif; ?>
        <?php print $feed_icons; ?>
      </div>
    </div>
  </div>

  <footer class="section-footer" role="contentinfo">
    <?php print render($page['footer']); ?>
  </footer>
</div>
