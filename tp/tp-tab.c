#pragma once
#ifndef TPTABC
#define TPTABC
#include "tp-internal.h"
#include "tp-tab.h"
struct tp_tab_t AC_TAB_DEFAULT_TAB = {
  .text           = "undefined",
  .selected       = false,
  .color          = AC_RED,
  .selected_color = AC_GREEN,
};
//////////////////////////////////////////////////////////////////

void tp_tab_module_deinit(__attribute__((unused)) module(tp_tab) *exports) {
  clib_module_deinit(tp_tab);
  return;
}

//////////////////////////////////////////////////////////////////////////
int tp_tab_module_init(module(tp_tab) *exports) {
  clib_module_init(tp_tab, exports);
  uuid4_init();
  exports->mode = AC_TAB_LOG_DEFAULT;
  exports->tabs = vector_new();

  return(0);
}

struct tp_tab_t *tp_tab_init(char *NEW_TAB_TEXT){
  struct tp_tab_t *O = calloc(1, sizeof(struct tp_tab_t));

  O->text           = NEW_TAB_TEXT ? NEW_TAB_TEXT : AC_TAB_DEFAULT_TAB.text;
  O->selected       = AC_TAB_DEFAULT_TAB.selected;
  O->color          = AC_TAB_DEFAULT_TAB.color;
  O->selected_color = AC_TAB_DEFAULT_TAB.selected_color;
  uuid4_generate(O->uuid);
  return(O);
}

bool tp_tab_add(struct tp_tab_t *NEW_TAB){
  vector_push(TB->tabs, (void *)NEW_TAB);
}

size_t tp_tab_get_qty(void){
  return(vector_size(TB->tabs));
}

////////////////////////////////////////////////////////

#define TERMINAL_TP_TABS_ROW_TOP_OFFSET    0

void render_tp_tabs(void){
//  fprintf(stderr, "tabs rendering....\n");
  static struct tp_tab_t *o;
  char                   *text, *marker;

  asprintf(&marker, "%s", SELECTED_LEFT_MARKER);
  termpaint_attr *o_attr_selected   = termpaint_attr_new(TERMPAINT_COLOR_BRIGHT_GREEN, TERMPAINT_COLOR_BLACK);
  termpaint_attr *o_attr_unselected = termpaint_attr_new(TERMPAINT_COLOR_BRIGHT_RED, TERMPAINT_COLOR_BLACK);
  size_t         max_tab_rows       = 5;
  size_t         rendered_tabs_qty  = 0;
  {
    for (size_t i = 0; (i < vector_size(TB->tabs)) && (i <= max_tab_rows); i++) {
      o = vector_get(TB->tabs, i);
      assert(o != NULL && o->text != NULL && strlen(o->text) > 0);
      assert(o->uuid != NULL && strlen(o->uuid) > 10);
      asprintf(&text, "%s", o->text);
      assert(strlen(text) > 0);
      {
        termpaint_surface_write_with_attr(surface, (i + 1) * 8, 0, text, o->selected ? o_attr_selected : o_attr_unselected);
        rendered_tabs_qty++;
      }
    }
  }
}

void set_tab_index(size_t NEW_TAB_INDEX){
  if (NEW_TAB_INDEX < 0)
    NEW_TAB_INDEX = TB->get_tabs_qty() - 1;
  else if (NEW_TAB_INDEX > TB->get_tabs_qty() - 1)
    NEW_TAB_INDEX = 0;
  struct tp_tab_t *NEW_TAB = (struct tp_tab_t *)vector_get(TB->tabs, NEW_TAB_INDEX);
  assert(NEW_TAB != NULL);
  for (size_t i = 0; i < TB->get_tabs_qty(); i++) {
    struct tp_tab_t *O = (struct tp_tab_t *)vector_get(TB->tabs, i);
    O->selected = false;
  }
  NEW_TAB->selected = true;
  render_tp_tabs();
  termpaint_terminal_flush_logged(terminal, false);
}

void change_tab_index(int CHANGE_TAB_TYPE) {
  char   *msg;
  size_t was           = get_selected_index();
  size_t NEW_TAB_INDEX = -1;

  for (size_t i = 0; i < TB->get_tabs_qty(); i++) {
    struct tp_tab_t *O = (struct tp_tab_t *)vector_get(TB->tabs, i);
    if (O->selected == true) {
      O->selected = false;
      switch (CHANGE_TAB_TYPE) {
      }
      set_tab_index(NEW_TAB_INDEX);
      int is = get_selected_index();
      asprintf(&msg, "selected index was %lu and is now %d :: tab type: %d", was, is, CHANGE_TAB_TYPE);
      LOG(msg);
      return;
    }
  }
  return;
} /* change_tab_index */

void select_tab_first(void){
}

void select_tab_last(void){
}

void select_tab_next(void){
  change_tab_index(CHANGE_TAB_TYPE_NEXT);
}

void select_tab_prev(void){
  change_tab_index(CHANGE_TAB_TYPE_PREV);
}

int tp_get_max_tab_text_size(){
  size_t          s = 0;
  struct tp_tab_t *O;

  for (size_t i = 0; i < TB->get_tabs_qty(); i++) {
    O = (struct tp_tab_t *)vector_get(TB->tabs, i);
    if (strlen(O->text) > s)
      s = strlen(O->text);
  }
  return(s);
}

int get_selected_tab_index(){
  struct tp_tab_t *O;

  for (size_t i = 0; i < TB->get_tabs_qty(); i++) {
    O = (struct tp_tab_t *)vector_get(TB->tabs, i);
    if (O->selected)
      return(i);
  }
  return(-1);
}

#endif
