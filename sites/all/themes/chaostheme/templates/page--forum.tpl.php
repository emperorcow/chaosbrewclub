<?php
/**
 * @file
 * Adaptivetheme implementation to display a single Drupal page.
 *
 * Available variables:
 *
 * Adaptivetheme supplied variables:
 * - $site_logo: Themed logo - linked to front with alt attribute.
 * - $site_name: Site name linked to the homepage.
 * - $site_name_unlinked: Site name without any link.
 * - $hide_site_name: Toggles the visibility of the site name.
 * - $visibility: Holds the class .element-invisible or is empty.
 * - $primary_navigation: Themed Main menu.
 * - $secondary_navigation: Themed Secondary/user menu.
 * - $primary_local_tasks: Split local tasks - primary.
 * - $secondary_local_tasks: Split local tasks - secondary.
 * - $tag: Prints the wrapper element for the main content.
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/bartik.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['highlighted']: Items for the highlighted content region.
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['sidebar_second']: Items for the second sidebar.
 * - $page['header']: Items for the header region.
 * - $page['footer']: Items for the footer region.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see template_process()
 * @see adaptivetheme_preprocess_page()
 * @see adaptivetheme_process_page()
 */
?>
<div id="page" class="container <?php print $classes; ?>">
  <?php print render($page['menu_bar']); ?>

  <!-- region: Leaderboard -->
  <?php print render($page['leaderboard']); ?>

  <?php if ($content = render($page['submenu'])): ?>
    <div id="submenu"> <?php print $content; ?> </div>
  <?php endif; ?>

    <?php if ($site_logo): ?>
       <div id="logo"><?php print $site_logo; ?></div>
    <?php endif; ?>
  <?php if ($site_logo || $site_name || $site_slogan): ?>
      <div id="branding" class="branding-elements clearfix">
        <!-- Logo -->
      </div><!-- /end #branding -->
    <?php endif; ?>

    <!-- region: Header -->
    <?php print render($page['header']); ?>

  </header>

  <!-- Navigation elements -->
  <?php if ($primary_navigation): print $primary_navigation; endif; ?>
  <?php if ($secondary_navigation): print $secondary_navigation; endif; ?>

  <!-- Breadcrumbs -->
  <?php if ($breadcrumb): print $breadcrumb; endif; ?>


  <!-- region: Secondary Content -->
  <?php print render($page['secondary_content']); ?>

  <div id="columns" class="clearfix">
    <div id="content-column" role="main">
      <div class="content-inner">
  
		<!-- Messages and Help -->
  <?php print $messages; ?>
  <?php print render($page['help']); ?>

        <!-- region: Highlighted -->
        <?php print render($page['highlighted']); ?>

          <div id="splitmain">
          <!-- region: Split Content Left-->
          <?php if ($content = render($page['splitmain_left'])): ?>
            <div id="splitmain_left">
              <?php print $content; ?>
            </div>
          <?php endif; ?>
          <!-- region: Split Content Right-->
          <?php if ($content = render($page['splitmain_right'])): ?>
            <div id="splitmain_right">
              <?php print $content; ?>
            </div>
          <?php endif; ?>
		  	<div class='clearfix' style='width: 100%'> </div>
          </div>

        <<?php print $tag; ?> id="main-content">

          <?php print render($title_prefix); ?>
          <?php if ($title || $primary_local_tasks || $secondary_local_tasks || $action_links = render($action_links)): ?>
            <header id="main-content-header test">
              <div id="forum-section" class="section"><?php print $forum_breadcrumb; ?></div>
              <?php if ($title): ?>
                <h1 id="page-title"<?php print $attributes; ?>>
                  <?php print $title; ?>
                </h1>
              <?php endif; ?>

              <?php if ($primary_local_tasks || $secondary_local_tasks || $action_links): ?>
                <div id="tasks">

                  <?php if ($primary_local_tasks): ?>
                    <ul class="tabs primary clearfix"><?php print render($primary_local_tasks); ?></ul>
                  <?php endif; ?>

                  <?php if ($secondary_local_tasks): ?>
                    <ul class="tabs secondary clearfix"><?php print render($secondary_local_tasks); ?></ul>
                  <?php endif; ?>

                  <?php if ($action_links = render($action_links)): ?>
                    <ul class="action-links clearfix"><?php print $action_links; ?></ul>
                  <?php endif; ?>

                </div>
              <?php endif; ?>

            </header>
          <?php endif; ?>
          <?php print render($title_suffix); ?>

          <!-- region: Main Content -->
          <?php if ($content = render($page['content'])): ?>
            <div id="content" class='clearfix'>
              <?php print $content; ?>
            </div>
          <?php endif; ?>

          <!-- Feed icons (RSS, Atom icons etc -->
          <?php print $feed_icons; ?>

        </<?php print $tag; ?>><!-- /end #main-content -->

        <!-- region: Content Aside -->
        <?php print render($page['content_aside']); ?>

      </div><!-- /end .content-inner -->
    </div><!-- /end #content-column -->

    <!-- regions: Sidebar first and Sidebar second -->
    <?php $sidebar_first = render($page['sidebar_first']); print $sidebar_first; ?>
    <?php $sidebar_second = render($page['sidebar_second']); print $sidebar_second; ?>

  </div><!-- /end #columns -->

  <!-- region: Tertiary Content -->
  <?php print render($page['tertiary_content']); ?>

  <!-- region: Footer -->
    <footer id="footer" class="clearfix" role="contentinfo">
  	<?php if ($page['footer']): ?>
      	<?php print render($page['footer']); ?>
  	<?php endif; ?>
	<div id="contactfooter">Questions, Comments, or Concerns?  Hit us up at contact@chaosbrewclub.net</div>
    </footer>
</div>
