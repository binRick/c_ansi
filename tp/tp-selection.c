#pragma once
#ifndef TPSELC
#define TPSELC
#include "tp-internal.h"
#include "tp-selection.h"
struct tp_confirm_option_t AC_CONFIRM_DEFAULT_OPTION = {
  .text           = "undefined",
  .selected       = false,
  .color          = AC_RED,
  .selected_color = AC_GREEN,
};
//////////////////////////////////////////////////////////////////

void tp_confirm_module_deinit(__attribute__((unused)) module(tp_confirm) *exports) {
  clib_module_deinit(tp_confirm);
  return;
}

//////////////////////////////////////////////////////////////////////////
int tp_confirm_module_init(module(tp_confirm) *exports) {
  clib_module_init(tp_confirm, exports);
  uuid4_init();
  exports->mode    = AC_CONFIRM_LOG_DEFAULT;
  exports->options = vector_new();

  return(0);
}

struct tp_confirm_option_t *tp_confirm_init_option(char *NEW_OPTION_TEXT){
  struct tp_confirm_option_t *O = calloc(1, sizeof(struct tp_confirm_option_t));

  O->text           = NEW_OPTION_TEXT ? NEW_OPTION_TEXT : AC_CONFIRM_DEFAULT_OPTION.text;
  O->selected       = AC_CONFIRM_DEFAULT_OPTION.selected;
  O->color          = AC_CONFIRM_DEFAULT_OPTION.color;
  O->selected_color = AC_CONFIRM_DEFAULT_OPTION.selected_color;
  uuid4_generate(O->uuid);
  return(O);
}

bool tp_confirm_add_option(struct tp_confirm_option_t *NEW_OPTION){
  vector_push(TP->options, (void *)NEW_OPTION);
}

size_t tp_confirm_get_options_qty(void){
  return(vector_size(TP->options));
}

////////////////////////////////////////////////////////
int get_selected_index();
////////////////////////////////////////////////////////
#define ICON0                                          ">"
#define ICON1                                          "▶"
#define ICON2                                          "➡"
#define ICON3                                          ""
#define ICON4                                          "➡"
#define ICON5                                          "▶️"
#define ICON6                                          "➡️"
#define ICON7                                          "🔛"
#define ICON8                                          "↪"
#define ICON9                                          "👉"
#define ICON10                                         "🚩"
#define ICON11                                         "✅"
#define ICON12                                         "⭐"
#define ICON13                                         "✔️"
#define ICON14                                         "☑️"
#define ICON15                                         "✳️"
////////////////////////////////////////////////////////
#define SELECTED_LEFT_ICON                             ICON1
#define SELECTED_RIGHT_ICON                            ICON3
#define SELECTED_LEFT_ICON_SIZE                        1
#define OPTION_RIGHT_EDGE_PADDING                      1
#define SELECTED_STYLE                                 (TERMPAINT_STYLE_INVERSE | TERMPAINT_STYLE_BOLD)
#define UNSELECTED_STYLE                               -1
////////////////////////////////////////////////////////
#define TERMINAL_TP_OPTIONS_ROW_TOP_OFFSET             2
#define TERMINAL_TP_OPTIONS_ROW_BOTTOM_OFFSET          2
#define TERMINAL_TP_OPTIONS_RIGHT_PERCENTAGE_OFFSET    .75
#define TERMINAL_TP_OPTIONS_RIGHT_MAX_COLS_OFFSET      2
#define TP_OPTIONS_SELECTED_LEFT_ICON_FG_COLOR         TERMPAINT_COLOR_BRIGHT_YELLOW
#define TP_OPTIONS_SELECTED_LEFT_ICON_BG_COLOR         TERMPAINT_COLOR_BLACK
#define TP_OPTIONS_UNSELECTED_FG_COLOR                 TERMPAINT_COLOR_WHITE
#define TP_OPTIONS_SELECTED_FG_COLOR                   TERMPAINT_COLOR_GREEN
#define TP_OPTIONS_UNSELECTED_BG_COLOR                 TERMPAINT_DEFAULT_COLOR
#define TP_OPTIONS_SELECTED_BG_COLOR                   TERMPAINT_DEFAULT_COLOR
#define SELECTED_LEFT_MARKER_PREFIX                    "  "
#define SELECTED_LEFT_MARKER_SUFFIX                    "  "
#define SELECTED_LEFT_MARKER                           SELECTED_LEFT_MARKER_PREFIX SELECTED_LEFT_ICON SELECTED_LEFT_MARKER_SUFFIX

void render_tp_options(void){
  static struct tp_confirm_option_t *o;
  char                              *text, *marker;
  int                               o_row         = -1;
  const int                         screen_width  = termpaint_surface_width(surface),
                                    screen_height = termpaint_surface_height(surface);

  asprintf(&marker, "%s", SELECTED_LEFT_MARKER);
  termpaint_attr *o_attr_unselected   = termpaint_attr_new(TP_OPTIONS_UNSELECTED_FG_COLOR, TP_OPTIONS_UNSELECTED_BG_COLOR);
  termpaint_attr *o_attr_selected     = termpaint_attr_new(TP_OPTIONS_SELECTED_FG_COLOR, TP_OPTIONS_SELECTED_BG_COLOR);
  termpaint_attr *marker_attr         = termpaint_attr_new(TERMPAINT_COLOR_BRIGHT_YELLOW, TERMPAINT_COLOR_BLACK);
  int            max_option_text_size = tp_get_max_option_text_size();
  int            o_col                = (screen_width - max_option_text_size) - OPTION_RIGHT_EDGE_PADDING;
  size_t         option_width         = max_option_text_size + (OPTION_RIGHT_EDGE_PADDING * 2);
  size_t         max_option_rows      = screen_height - TERMINAL_TP_OPTIONS_ROW_TOP_OFFSET - TERMINAL_TP_OPTIONS_ROW_BOTTOM_OFFSET - BOTTOM_MSG_BOX_HEIGHT;
  size_t         rendered_rows_qty    = 0;
  {
    char *msg;
    asprintf(&msg, "screen_width=%d|max_option_rows=%lu|o_col=%d|ending on row #%lu|max_option_text_size=%d", screen_width, max_option_rows, o_col, max_option_rows, max_option_text_size);
    LOG(msg);
    assert(o_col < screen_width && o_col > 0);
    for (size_t i = 0; (i < vector_size(TP->options)) && (i <= max_option_rows); i++) {
      o = vector_get(TP->options, i);
      assert(o != NULL && o->text != NULL && strlen(o->text) > 0);
      assert(o->uuid != NULL && strlen(o->uuid) > 10);
      asprintf(&text, "%s", o->text);
      assert(strlen(text) > 0);
      o_row = TERMINAL_TP_OPTIONS_ROW_TOP_OFFSET + i;
      assert(o_row < screen_height && o_row > 0);

      while (strlen(text) < option_width) {
        asprintf(&text, "%s%s", text, " ");
        if (strlen(text) >= option_width)
          break;
      }
      {
        termpaint_surface_clear_rect_with_attr(surface, o_col - strlen(marker), o_row, strlen(marker) + max_option_text_size, 1, attr_ui);
        termpaint_surface_write_with_attr(surface, o_col, o_row, text, o->selected ? o_attr_selected : o_attr_unselected);
        if (o->selected)
          termpaint_surface_write_with_attr(surface, o_col - strlen(marker) - 0, o_row, marker, marker_attr);
        rendered_rows_qty++;
      }
    }
  }
} /* render_tp_options */

void set_selection_index(size_t NEW_SELECTION_INDEX){
  if (NEW_SELECTION_INDEX < 0)
    NEW_SELECTION_INDEX = TP->get_options_qty() - 1;
  else if (NEW_SELECTION_INDEX > TP->get_options_qty() - 1)
    NEW_SELECTION_INDEX = 0;
  struct tp_confirm_option_t *NEW_SELECTION = (struct tp_confirm_option_t *)vector_get(TP->options, NEW_SELECTION_INDEX);
  assert(NEW_SELECTION != NULL);
  for (size_t i = 0; i < TP->get_options_qty(); i++) {
    struct tp_confirm_option_t *O = (struct tp_confirm_option_t *)vector_get(TP->options, i);
    O->selected = false;
  }
  NEW_SELECTION->selected = true;
  render_tp_options();
  termpaint_terminal_flush_logged(terminal, false);
}

void change_selection_index(int CHANGE_SELECTION_TYPE) {
  char   *msg;
  size_t was                 = get_selected_index();
  size_t NEW_SELECTION_INDEX = -1;

  for (size_t i = 0; i < TP->get_options_qty(); i++) {
    struct tp_confirm_option_t *O = (struct tp_confirm_option_t *)vector_get(TP->options, i);
    if (O->selected == true) {
      O->selected = false;
      switch (CHANGE_SELECTION_TYPE) {
      case CHANGE_SELECTION_TYPE_PAGE_UP:
        NEW_SELECTION_INDEX = i - (TP->get_options_qty() / 3);
        NEW_SELECTION_INDEX = (NEW_SELECTION_INDEX < 0) ? 0 : NEW_SELECTION_INDEX;
        break;
      case CHANGE_SELECTION_TYPE_PAGE_DOWN:
        NEW_SELECTION_INDEX = i + (TP->get_options_qty() / 3);
        NEW_SELECTION_INDEX = (NEW_SELECTION_INDEX > TP->get_options_qty() - 1) ? TP->get_options_qty() - 1 : NEW_SELECTION_INDEX;

        break;
      case CHANGE_SELECTION_TYPE_FIRST:
        NEW_SELECTION_INDEX = 0;
        break;
      case CHANGE_SELECTION_TYPE_LAST:
        NEW_SELECTION_INDEX = TP->get_options_qty() - 1;
        break;
      case CHANGE_SELECTION_TYPE_NEXT:
        NEW_SELECTION_INDEX = i + 1;
        break;
      case CHANGE_SELECTION_TYPE_PREV:
        if (i == 0)
          NEW_SELECTION_INDEX = TP->get_options_qty() - 1;
        else
          NEW_SELECTION_INDEX = i - 1;
        break;
      }
      set_selection_index(NEW_SELECTION_INDEX);
      int is = get_selected_index();
      asprintf(&msg, "selected index was %lu and is now %d :: selection type: %d", was, is, CHANGE_SELECTION_TYPE);
      LOG(msg);
      return;
    }
  }
  return;
} /* change_selection_index */

void select_page_up(void){
  change_selection_index(CHANGE_SELECTION_TYPE_PAGE_UP);
}

void select_page_down(void){
  change_selection_index(CHANGE_SELECTION_TYPE_PAGE_DOWN);
}

void select_first(void){
  change_selection_index(CHANGE_SELECTION_TYPE_FIRST);
}

void select_last(void){
  change_selection_index(CHANGE_SELECTION_TYPE_LAST);
}

void select_next(void){
  change_selection_index(CHANGE_SELECTION_TYPE_NEXT);
}

void select_prev(void){
  change_selection_index(CHANGE_SELECTION_TYPE_PREV);
}

int tp_get_max_option_text_size(){
  size_t                     s = 0;
  struct tp_confirm_option_t *O;

  for (size_t i = 0; i < TP->get_options_qty(); i++) {
    O = (struct tp_confirm_option_t *)vector_get(TP->options, i);
    if (strlen(O->text) > s)
      s = strlen(O->text);
  }
  return(s);
}

int get_selected_index(){
  struct tp_confirm_option_t *O;

  for (size_t i = 0; i < TP->get_options_qty(); i++) {
    O = (struct tp_confirm_option_t *)vector_get(TP->options, i);
    if (O->selected)
      return(i);
  }
  return(-1);
}

#endif
