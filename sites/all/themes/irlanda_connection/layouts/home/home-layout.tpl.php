<div class="page">
  <header class="section-header" role="banner">
    <div class="section-branding">
      <?php if ($logo): ?>
        <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" class="site-logo"><img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" /></a>
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
    <?php print render($page['navigation']); ?>
    <div id="zone-graphic-header" style="background-image: url(sites/default/files/images/home-top-img.png);">
      <?php print render($page['header']); ?>
      <?php if ($title): ?>
        <h1>CURSOS DE INGLÉS EN EL EXTRANJERO</h1>
      <?php endif; ?>
    </div>
  </header>
  <div class="section-main">
    <div class="section-content" role="main">
      <?php print render($page['highlighted']); ?>
      <a id="main-content"></a>
      <?php print render($title_prefix); ?>
      <?php print render($title_suffix); ?>
      <?php print $messages; ?>
      <?php print render($tabs); ?>
      <?php if ($action_links): ?>
        <ul class="action-links"><?php print render($action_links); ?></ul>
      <?php endif; ?> 
      <div id="zone-graphic-first" style="background-image: url(sites/default/files/images/porqueingles-img.png);">
        <?php print render($page['wrapper-first']); ?>
      </div>
      <div id="zone-graphic-destinos" style="background-image: url(sites/default/files/images/destinos-img.png);">
        <?php print render($page['wrapper-second']); ?>        
      </div>
      <div id="zone-graphic-third" style="background-image: url(sites/default/files/images/porquenosotros-img.png);">
        <?php print render($page['wrapper-third']); ?>
      </div>
      <?php print $feed_icons; ?>
    </div>
  </div>

  <footer class="section-footer" role="contentinfo">
    <?php print render($page['footer']); ?>
  </footer>
</div>
