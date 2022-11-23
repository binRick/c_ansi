#pragma once
#ifndef TPTABH
#define TPTABH
#include "uuid4/src/uuid4.h"
#include "tp-internal.h"
//////////////////////////////////////////////////////////////////
enum change_tab_type_t {
  CHANGE_TAB_TYPE_NEXT,
  CHANGE_TAB_TYPE_PREV,
  CHANGE_TAB_TYPES_QTY,
};
enum tp_tab_mode_t {
  AC_TAB_LOG_NONE,
  AC_TAB_LOG_INFO,
  AC_TAB_LOG_ERROR,
  AC_TAB_LOG_DEBUG,
  AC_TAB_LOG_QTY,
};
enum change_tab_type_t;
enum tp_tab_mode_t;
struct tp_tab_t {
  char *text;
  char *selected_color;
  int  selected_bg_color_rgb[3];
  int  selected_fg_color_rgb[3];
  char selected_icon[16];
  char *color;
  bool selected;
  char *button_s;
  char uuid[UUID4_LEN];
};
#define AC_TAB_LOG_DEFAULT    AC_TAB_LOG_INFO
struct tp_tab_t AC_TAB_DEFAULT_OPTION;
struct tp_tab_t *tp_tab_init(char *NEW_OPTION_TEXT);
bool tp_tab_add(struct tp_tab_t *NEW_OPTION);

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
module(tp_tab) {
  define(tp_tab, CLIB_MODULE);
  enum tp_tab_mode_t mode;
  struct Vector      *tabs;
  bool               (*add_tab)(struct tp_tab_t *NEW_OPTION);
  size_t             (*get_tabs_qty)(void);
  struct tp_tab_t    *(*init_tab)(char *NEW_OPTION_TEXT);
};

int  tp_tab_module_init(module(tp_tab) * exports);
void tp_tab_module_deinit(module(tp_tab) * exports);
struct tp_tab_t *tp_tab_init(char *NEW_OPTION_TEXT);
bool tp_tab_add(struct tp_tab_t *NEW_OPTION);
size_t tp_tab_get_qty(void);

exports(tp_tab) {
  .mode         = AC_TAB_LOG_DEFAULT,
  .init         = tp_tab_module_init,
  .deinit       = tp_tab_module_deinit,
  .get_tabs_qty = tp_tab_get_qty,
  .init_tab     = tp_tab_init,
  .add_tab      = tp_tab_add,
  .tabs         = NULL,
};
void render_tp_tabs(void);

void set_tab_index(size_t NEW_TAB_INDEX);

void change_tab_index(int CHANGE_TAB_TYPE);

void select_tab_first(void);

void select_tab_last(void);

void select_tab_next(void);

void select_tab_prev(void);

int tp_get_max_tab_text_size();

int get_selected_tab_index();

size_t tp_tab_get_qty(void);
#endif
