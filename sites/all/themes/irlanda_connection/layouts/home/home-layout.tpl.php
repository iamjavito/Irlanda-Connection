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
  <div class="section-main">
    <div class="section-content" role="main">
      <?php if ($action_links): ?>
        <ul class="action-links"><?php print render($action_links); ?></ul>
      <?php endif; ?>
      <!-- Header Image -->
      <div id="zone-graphic-header" style="background-image: url(sites/default/files/storage/images/home_page/home-top-img.png);">
        <h1>CURSOS DE INGLÉS EN EL EXTRANJERO</h1>
        <div id='btn-home' class="btn">
          <a href="?q=destinos">DESCUBRE EL MUNDO CON NOSOTROS</a>
        </div>
      </div>
      <div id="zone-graphic-first" style="background-image: url(sites/default/files/storage/images/home_page/porqueingles-img.png);">
        <?php print render($page['wrapper-first']); ?>
      </div>
      <div id="zone-graphic-destinos" style="background-image: url(sites/default/files/storage/images/home_page/destinos-img.png);">
          <h2>DESTINOS</h2>
        <?php print render($page['wrapper-second']); ?>
      </div>
      <div id="zone-graphic-third" style="background-image: url(sites/default/files/storage/images/home_page/porquenosotros-img.png);">
        <?php print render($page['wrapper-third']); ?>
      </div>
    </div>
  </div>

  <footer class="section-footer" role="contentinfo">
    <?php print render($page['footer']); ?>
  </footer>
</div>
