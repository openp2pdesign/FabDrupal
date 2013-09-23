<?php
/**
 * @file
 * Default views for the Scald module.
 */

/**
 * Implements hook_views_default_views().
 */
function scald_views_default_views() {
  $views = array();

  // Atoms listing view.
  $view = new view();
  $view->name = 'scald_atoms';
  $view->description = t('Atoms listing view provided by Scald to access atoms.');
  $view->tag = '';
  $view->base_table = 'scald_atoms';
  $view->human_name = '';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Atoms Library';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer scald atoms';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'mini';
  $handler->display->display_options['style_plugin'] = 'table';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['text']['id'] = 'text';
  $handler->display->display_options['empty']['text']['table'] = 'views';
  $handler->display->display_options['empty']['text']['field'] = 'area';
  $handler->display->display_options['empty']['text']['empty'] = FALSE;
  $handler->display->display_options['empty']['text']['content'] = 'No atom found.';
  $handler->display->display_options['empty']['text']['format'] = 'plain_text';
  $handler->display->display_options['empty']['text']['tokenize'] = 0;
  /* Relationship: Atom: Publisher */
  $handler->display->display_options['relationships']['publisher']['id'] = 'publisher';
  $handler->display->display_options['relationships']['publisher']['table'] = 'scald_atoms';
  $handler->display->display_options['relationships']['publisher']['field'] = 'publisher';
  $handler->display->display_options['relationships']['publisher']['label'] = 'Publisher';
  $handler->display->display_options['relationships']['publisher']['required'] = 0;
  /* Field: Atom: Scald ID */
  $handler->display->display_options['fields']['sid']['id'] = 'sid';
  $handler->display->display_options['fields']['sid']['table'] = 'scald_atoms';
  $handler->display->display_options['fields']['sid']['field'] = 'sid';
  /* Field: Atom: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'scald_atoms';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  /* Field: Atom: Provider */
  $handler->display->display_options['fields']['provider']['id'] = 'provider';
  $handler->display->display_options['fields']['provider']['table'] = 'scald_atoms';
  $handler->display->display_options['fields']['provider']['field'] = 'provider';
  /* Field: Atom: Base ID */
  $handler->display->display_options['fields']['base_id']['id'] = 'base_id';
  $handler->display->display_options['fields']['base_id']['table'] = 'scald_atoms';
  $handler->display->display_options['fields']['base_id']['field'] = 'base_id';
  /* Field: Atom: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'scald_atoms';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'publisher';
  $handler->display->display_options['fields']['name']['label'] = 'Publisher';
  $handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['name']['alter']['html'] = 0;
  $handler->display->display_options['fields']['name']['hide_empty'] = 0;
  $handler->display->display_options['fields']['name']['empty_zero'] = 0;
  $handler->display->display_options['fields']['name']['link_to_user'] = 1;
  $handler->display->display_options['fields']['name']['overwrite_anonymous'] = 0;
  /* Field: Atom: Representation */
  $handler->display->display_options['fields']['representation']['id'] = 'representation';
  $handler->display->display_options['fields']['representation']['table'] = 'scald_atoms';
  $handler->display->display_options['fields']['representation']['field'] = 'representation';
  $handler->display->display_options['fields']['representation']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['representation']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['representation']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['representation']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['representation']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['representation']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['representation']['alter']['html'] = 0;
  $handler->display->display_options['fields']['representation']['hide_empty'] = 0;
  $handler->display->display_options['fields']['representation']['empty_zero'] = 0;
  /* Filter criterion: Atom: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'scald_atoms';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['group'] = '0';
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Title';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  /* Filter criterion: User: Name */
  $handler->display->display_options['filters']['uid']['id'] = 'uid';
  $handler->display->display_options['filters']['uid']['table'] = 'users';
  $handler->display->display_options['filters']['uid']['field'] = 'uid';
  $handler->display->display_options['filters']['uid']['relationship'] = 'publisher';
  $handler->display->display_options['filters']['uid']['value'] = '';
  $handler->display->display_options['filters']['uid']['group'] = '0';
  $handler->display->display_options['filters']['uid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['uid']['expose']['operator_id'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['label'] = 'Publisher';
  $handler->display->display_options['filters']['uid']['expose']['operator'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['identifier'] = 'uid';
  $handler->display->display_options['filters']['uid']['expose']['required'] = FALSE;
  $handler->display->display_options['filters']['uid']['expose']['reduce'] = 0;
  /* Filter criterion: Atoms: Authors (scald_authors) */
  $handler->display->display_options['filters']['scald_authors_tid']['id'] = 'scald_authors_tid';
  $handler->display->display_options['filters']['scald_authors_tid']['table'] = 'field_data_scald_authors';
  $handler->display->display_options['filters']['scald_authors_tid']['field'] = 'scald_authors_tid';
  $handler->display->display_options['filters']['scald_authors_tid']['value'] = '';
  $handler->display->display_options['filters']['scald_authors_tid']['group'] = 1;
  $handler->display->display_options['filters']['scald_authors_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['scald_authors_tid']['expose']['operator_id'] = 'scald_authors_tid_op';
  $handler->display->display_options['filters']['scald_authors_tid']['expose']['label'] = 'Authors';
  $handler->display->display_options['filters']['scald_authors_tid']['expose']['operator'] = 'scald_authors_tid_op';
  $handler->display->display_options['filters']['scald_authors_tid']['expose']['identifier'] = 'scald_authors_tid';
  $handler->display->display_options['filters']['scald_authors_tid']['expose']['remember_roles'] = array();
  $handler->display->display_options['filters']['scald_authors_tid']['vocabulary'] = 'scald_authors';
  /* Filter criterion: Atom: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'scald_atoms';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['group'] = '0';
  $handler->display->display_options['filters']['type']['exposed'] = TRUE;
  $handler->display->display_options['filters']['type']['expose']['operator_id'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['label'] = 'Type';
  $handler->display->display_options['filters']['type']['expose']['operator'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['identifier'] = 'type';
  $handler->display->display_options['filters']['type']['expose']['required'] = FALSE;
  $handler->display->display_options['filters']['type']['expose']['reduce'] = 0;
  /* Filter criterion: Atoms: Tags (scald_tags) */
  $handler->display->display_options['filters']['scald_tags_tid']['id'] = 'scald_tags_tid';
  $handler->display->display_options['filters']['scald_tags_tid']['table'] = 'field_data_scald_tags';
  $handler->display->display_options['filters']['scald_tags_tid']['field'] = 'scald_tags_tid';
  $handler->display->display_options['filters']['scald_tags_tid']['value'] = '';
  $handler->display->display_options['filters']['scald_tags_tid']['group'] = 1;
  $handler->display->display_options['filters']['scald_tags_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['scald_tags_tid']['expose']['operator_id'] = 'scald_tags_tid_op';
  $handler->display->display_options['filters']['scald_tags_tid']['expose']['label'] = 'Tags';
  $handler->display->display_options['filters']['scald_tags_tid']['expose']['operator'] = 'scald_tags_tid_op';
  $handler->display->display_options['filters']['scald_tags_tid']['expose']['identifier'] = 'scald_tags_tid';
  $handler->display->display_options['filters']['scald_tags_tid']['expose']['remember_roles'] = array();
  $handler->display->display_options['filters']['scald_tags_tid']['vocabulary'] = 'scald_tags';
  /* Filter criterion: Atom: Actions */
  $handler->display->display_options['filters']['actions']['id'] = 'actions';
  $handler->display->display_options['filters']['actions']['table'] = 'scald_atoms';
  $handler->display->display_options['filters']['actions']['field'] = 'actions';
  $handler->display->display_options['filters']['actions']['operator'] = '&';
  $handler->display->display_options['filters']['actions']['value'] = array(
    'fetch' => 'fetch',
    'view' => 'view',
  );
  $handler->display->display_options['filters']['actions']['group'] = '0';
  $handler->display->display_options['filters']['actions']['expose']['operator'] = FALSE;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['empty'] = TRUE;
  $handler->display->display_options['header']['area']['content'] = '<ul class="action-links"><li>' . l(t('Add atom'), 'atom/add') . '</li></ul>';
  $handler->display->display_options['header']['area']['format'] = 'filtered_html';
  $handler->display->display_options['header']['area']['tokenize'] = 0;
  $handler->display->display_options['path'] = 'admin/content/atoms';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Atoms';
  $handler->display->display_options['menu']['weight'] = '-60';

  $translatables[$view->name] = array(
    t('Master'),
    t('Atoms'),
    t('Atoms Library'),
    t('Authors'),
    t('Scald Library'),
    t('No atom found.'),
    t('Tags'),
    t('Title'),
    t('Type'),
    t('Publisher'),
  );

  $views[$view->name] = $view;
  return $views;
}
