#pragma once
#ifndef TPSELH
#define TPSELH
#include "tp-internal.h"
#include "uuid4/src/uuid4.h"
//////////////////////////////////////////////////////////////////
extern termpaint_attr *attr_bottom_msg;
enum change_selection_type_t {
  CHANGE_SELECTION_TYPE_NEXT,
  CHANGE_SELECTION_TYPE_PREV,
  CHANGE_SELECTION_TYPE_FIRST,
  CHANGE_SELECTION_TYPE_LAST,
  CHANGE_SELECTION_TYPE_PAGE_DOWN,
  CHANGE_SELECTION_TYPE_PAGE_UP,
  CHANGE_SELECTION_TYPES_QTY,
};
enum tp_confirm_mode_t {
  AC_CONFIRM_LOG_NONE,
  AC_CONFIRM_LOG_INFO,
  AC_CONFIRM_LOG_ERROR,
  AC_CONFIRM_LOG_DEBUG,
  AC_CONFIRM_LOG_QTY,
};
enum change_selection_type_t;
enum tp_confirm_mode_t;
struct tp_confirm_option_t {
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
int get_selected_index();
#define AC_CONFIRM_LOG_DEFAULT    AC_CONFIRM_LOG_INFO
struct tp_confirm_option_t AC_CONFIRM_DEFAULT_OPTION;
struct tp_confirm_option_t *tp_confirm_init_option(char *NEW_OPTION_TEXT);
bool tp_confirm_add_option(struct tp_confirm_option_t *NEW_OPTION);

size_t tp_confirm_get_options_qty(void);

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
#define SELECTED_LEFT_ICON                             ICON4
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

module(tp_confirm) {
  define(tp_confirm, CLIB_MODULE);
  enum tp_confirm_mode_t     mode;
  struct Vector              *options;
  bool                       (*add_option)(struct tp_confirm_option_t *NEW_OPTION);
  size_t                     (*get_options_qty)(void);
  struct tp_confirm_option_t *(*init_option)(char *NEW_OPTION_TEXT);
};

int  tp_confirm_module_init(module(tp_confirm) * exports);
void tp_confirm_module_deinit(module(tp_confirm) * exports);
struct tp_confirm_option_t *tp_confirm_init_option(char *NEW_OPTION_TEXT);
bool tp_confirm_add_option(struct tp_confirm_option_t *NEW_OPTION);
size_t tp_confirm_get_options_qty(void);

exports(tp_confirm) {
  .mode            = AC_CONFIRM_LOG_DEFAULT,
  .init            = tp_confirm_module_init,
  .deinit          = tp_confirm_module_deinit,
  .get_options_qty = tp_confirm_get_options_qty,
  .init_option     = tp_confirm_init_option,
  .add_option      = tp_confirm_add_option,
  .options         = NULL,
};
void render_tp_options(void);

void set_selection_index(size_t NEW_SELECTION_INDEX);

void change_selection_index(int CHANGE_SELECTION_TYPE);

void select_page_up(void);

void select_page_down(void);

void select_first(void);

void select_last(void);

void select_next(void);

void select_prev(void);

int tp_get_max_option_text_size();

int get_selected_index();

#endif
