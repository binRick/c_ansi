#pragma once
#include "term-termpaint.h"
#include "term-termpaint.h"
#include "termpaint.h"
#include "termpaint_image.h"
#include "termpaintx.h"
#include "termpaintx_ttyrescue.h"
#include "tp-message-box.h"
#include "tp-utils.h"
#include <assert.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdarg.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
////////////////////////////////////////////////////
#include "ansi-codes.h"
#include "ansi-utils/ansi-utils.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/include/vector.h"
#include "module/def.h"
#include "module/module.h"
////////////////////////////////////////////////////
#include "wildcardcmp/wildcardcmp.h"
////////////////////////////////////////////////////
#include "module/require.h"
#include "tiny-regex-c/re.h"
#include "tp.h"
//////////////////////////////////////////////////////////////////
extern termpaint_attr *attr_bottom_msg;

unsigned int          BORDER_STYLE = 0,
                      BORDER_FG_COLOR_RED = 255, BORDER_FG_COLOR_GREEN = 255,
                      BORDER_FG_COLOR_BLUE = 255, BORDER_BG_COLOR_RED = 17,
                      BORDER_BG_COLOR_GREEN = 0, BORDER_BG_COLOR_BLUE = 255;

///////////////////////////////////////////////
///        Menus                            ///
///////////////////////////////////////////////
#define CYCLE_BORDER_STYLE()              { do { BORDER_STYLE = BORDER_STYLE >= (BORDER_STYLES_QTY - 1) ? 0 : BORDER_STYLE + 1; } while (0); }
#define INCREASE_BOTTOM_MSG_FG_RED()      { do { BORDER_FG_COLOR_RED = BORDER_FG_COLOR_RED >= MAX_RGB ? 0 : BORDER_FG_COLOR_RED + 1; redraw_bottom_msg(); } while (0); }
#define INCREASE_BOTTOM_MSG_FG_GREEN()    { do { BORDER_FG_COLOR_GREEN = BORDER_FG_COLOR_GREEN >= MAX_RGB ? 0 : BORDER_FG_COLOR_GREEN + 1; redraw_bottom_msg(); } while (0); }
#define INCREASE_BOTTOM_MSG_FG_BLUE()     { do { BORDER_FG_COLOR_BLUE = BORDER_FG_COLOR_BLUE >= MAX_RGB ? 0 : BORDER_FG_COLOR_BLUE + 1; redraw_bottom_msg(); } while (0); }
#define INCREASE_BOTTOM_MSG_BG_RED()      { do { BORDER_BG_COLOR_RED = BORDER_BG_COLOR_RED >= MAX_RGB ? 0 : BORDER_BG_COLOR_RED + 1; redraw_bottom_msg(); } while (0); }
#define INCREASE_BOTTOM_MSG_BG_GREEN()    { do { BORDER_BG_COLOR_GREEN = BORDER_BG_COLOR_GREEN >= MAX_RGB ? 0 : BORDER_BG_COLOR_GREEN + 1; redraw_bottom_msg(); } while (0); }
#define INCREASE_BOTTOM_MSG_BG_BLUE()     { do { BORDER_BG_COLOR_BLUE = BORDER_BG_COLOR_BLUE >= MAX_RGB ? 0 : BORDER_BG_COLOR_BLUE + 1; redraw_bottom_msg(); } while (0); }
#define BOTTOM_MSG_ROW_O
#define TERMINAL_KEY_MENU_ROW_OFFSET    26
#define TERMINAL_KEY_MENU_COL_OFFSET    3
#define TERMINAL_KEY_MENU_ITEM(ROW, LETTER, TEXT)                           \
  { do{                                                                     \
      termpaint_surface_write_with_attr(surface,                            \
                                        TERMINAL_KEY_MENU_COL_OFFSET,       \
                                        TERMINAL_KEY_MENU_ROW_OFFSET + ROW, \
                                        LETTER "> " TEXT,                   \
                                        attr_ui                             \
                                        );                                  \
    }while (0); }
#define TERMINAL_KEY_MENU()                                            \
  { do{                                                                \
      TERMINAL_KEY_MENU_ITEM(0, "B", "     Toggle Border Style");      \
      TERMINAL_KEY_MENU_ITEM(1, "C", "     Clear Bottom Message");     \
      TERMINAL_KEY_MENU_ITEM(2, "r", "     Refresh Screen");           \
      TERMINAL_KEY_MENU_ITEM(3, "T", "     Inspect Terminal");         \
      TERMINAL_KEY_MENU_ITEM(4, "t", "     Toggle Title");             \
      TERMINAL_KEY_MENU_ITEM(5, "v", "     Toggle Cursor Visibility"); \
      TERMINAL_KEY_MENU_ITEM(6, "c", "     Toggle Cursor Style");      \
      TERMINAL_KEY_MENU_ITEM(7, "❰ ❱", "   Change Select");            \
      TERMINAL_KEY_MENU_ITEM(8, "Esc", "   Undo Choice ❌");            \
      TERMINAL_KEY_MENU_ITEM(9, "Enter", " Follow Menu Path");         \
    }while (0); }
enum change_selection_type_t {
  CHANGE_SELECTION_TYPE_NEXT,
  CHANGE_SELECTION_TYPE_PREV,
  CHANGE_SELECTION_TYPE_FIRST,
  CHANGE_SELECTION_TYPE_LAST,
  CHANGE_SELECTION_TYPE_PAGE_DOWN,
  CHANGE_SELECTION_TYPE_PAGE_UP,
  CHANGE_SELECTION_TYPES_QTY,
};
volatile size_t
  surface_updates_qty = 0
;
cursor_profile_t
*cursor_profile
;
static event *key_wait(void);
static char *tp__basename(const char *path);

static volatile unsigned int
                                  title_updates_qty         = 0;
static struct tp_confirm_option_t AC_CONFIRM_DEFAULT_OPTION = {
  .text           = "undefined",
  .selected       = false,
  .color          = AC_RED,
  .selected_color = AC_GREEN,
};
const int
                                  screen_bg = TERMPAINT_COLOR_BRIGHT_YELLOW,
  ui_fg                                     = TERMPAINT_COLOR_BLACK,
  win_message                               = TERMPAINT_COLOR_GREEN,
  tile_border                               = TERMPAINT_COLOR_BLACK,
  tile_background                           = TERMPAINT_COLOR_LIGHT_GREY
;

void tp_confirm_module_deinit(module(tp_confirm) *exports) {
  clib_module_deinit(tp_confirm);
  return;
}
//////////////////////////////////////////////////////////////////////////
///        PROTOTYPES                ///
//////////////////////////////////////////////////////////////////////////
static void
event_callback(void *userdata, termpaint_event *tp_event),
rgb_color_menu(termpaint_attr * attr_ui, termpaint_attr * attr_to_change, int which_color),
update_current_key_display(termpaint_attr * attr_ui, event * evt),
indexed_color_menu(termpaint_attr * attr_ui, termpaint_attr * attr_to_change, int which_color),
write_sample(termpaint_attr * attr_ui, termpaint_attr * attr_sample, int line, char const *name, int style),
repaint_samples(termpaint_attr *, termpaint_attr *),
cycle_cursor_style(),
cycle_cursor_visiblity(),
cycle_cursor_blink(),
update_cursor_profile(),
repaint_all(termpaint_attr * attr_ui, termpaint_attr * attr_sample),
cleanup(void),
update_current_key_display(termpaint_attr * attr_ui, event * evt),
named_color_menu(termpaint_attr * attr_ui, termpaint_attr * attr_to_change, int which_color),
menu(termpaint_attr * attr_ui, termpaint_attr * attr_sample),
draw_box(),
select_prev(void),
select_next(void),
select_first(void),
select_page_down(void),
select_last(void),
select_page_up(void);
int term_tests_main(const int argc, const char **argv), tp_get_max_option_text_size();
char *str_repeat(char str[], unsigned int times), *cell_at(board_t *, int, int);
void render_tp_options(void);
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

///////////////////////////////////////////////
///        GLOBAL VARIABLES                 ///
///////////////////////////////////////////////
volatile signed long long
  mouse_wheel_val = 0
;
volatile int
  field[5][5],
  x, y,
  current_start_x,
  current_start_y;
volatile bool
  quit
;
volatile unsigned int
  cursor_x = 0, cursor_y = 1
;
termpaint_terminal
*terminal
;
termpaint_surface
*surface
;
termpaint_integration
*integration
;
termpaint_attr
*attr_ui,
*attr_sample;
event
*event_current
;
cursor_profile_t
*cursor_profile
;

///////////////////////////////////////////////
static void logging_func(termpaint_integration *integration, const char *data, int length){
  fprintf(stderr, AC_RESETALL AC_GREEN "[logging_func] len:%d|data:'%s'\n" AC_RESETALL "\n", length, data);
}

int term_tests_main(const int argc, const char **argv) {
    printf("Main start\n");
  repaint_all(attr_ui, attr_sample);
  menu(attr_ui, attr_sample);

  termpaint_attr_free(attr_sample);
  attr_sample = NULL;
  termpaint_attr_free(attr_ui);
  attr_ui = NULL;
  cleanup();
  return(0);
}

static void draw_box() {
  const int screen_width     = termpaint_surface_width(surface),
            screen_height    = termpaint_surface_height(surface),
            top_left_x       = (screen_width / 2) - 12,
            top_left_y       = (screen_height / 2) - 2;
  bool TITLE_RESTORE_CAPABLE = termpaint_terminal_capable(terminal, TERMPAINT_CAPABILITY_TITLE_RESTORE);

  termpaint_terminal_set_title(terminal, "🔥💣💥🔫💊", TERMPAINT_TITLE_MODE_PREFER_RESTORE);

  termpaint_surface_write_with_colors(surface, top_left_x, top_left_y,
                                      "┌───────────────────────┐",
                                      ui_fg, win_message);

  termpaint_surface_write_with_colors(surface,
                                      screen_width / 2 - 12, screen_height / 2 - 1,
                                      "│        OK!            │",
                                      ui_fg, win_message);

  termpaint_surface_write_with_colors(surface,
                                      screen_width / 2 - 12, screen_height / 2,
                                      "│                       │",
                                      ui_fg, win_message);

  termpaint_surface_write_with_colors(surface,
                                      screen_width / 2 - 12, screen_height / 2 + 1,
                                      "│ Press x to do it      │",
                                      ui_fg, win_message);

  termpaint_surface_write_with_colors(surface,
                                      screen_width / 2 - 12, screen_height / 2 + 2,
                                      "└───────────────────────┘",
                                      ui_fg, win_message);
  termpaint_terminal_flush_logged(terminal, false);
  // repaint_all(attr_ui, attr_sample);
} /* popup_box */

static void update_cursor_profile(){
  termpaint_terminal_set_cursor_position(terminal, cursor_profile->x, cursor_profile->y);
  termpaint_terminal_set_cursor_visible(terminal, cursor_profile->visible);
  termpaint_terminal_set_cursor_style(terminal, cursor_profile->style, cursor_profile->blink);
}

static void cycle_cursor_blink(){
  if (cursor_profile->blink) {
    cursor_profile->blink = false;
  }else{
    cursor_profile->blink = true;
  }
  update_cursor_profile();
}

static void cycle_cursor_visiblity(){
  if (cursor_profile->visible) {
    cursor_profile->visible = false;
  }else{
    cursor_profile->visible = true;
  }
  update_cursor_profile();
}

static void cycle_cursor_style(){
  if (cursor_profile->style == TERMPAINT_CURSOR_STYLE_BAR) {
    cursor_profile->style = TERMPAINT_CURSOR_STYLE_BLOCK;
  }else if (cursor_profile->style == TERMPAINT_CURSOR_STYLE_BLOCK) {
    cursor_profile->style = TERMPAINT_CURSOR_STYLE_UNDERLINE;
  }else{
    cursor_profile->style = TERMPAINT_CURSOR_STYLE_BAR;
  }

  update_cursor_profile();
}

static void event_callback(void *userdata, termpaint_event *tp_event) {
  (void)userdata;
  event *my_event = NULL;

  if (tp_event->type == TERMPAINT_EV_CHAR) {
    my_event           = malloc(sizeof(event));
    my_event->type     = tp_event->type;
    my_event->modifier = tp_event->c.modifier;
    my_event->string   = strndup(tp_event->c.string, tp_event->c.length);
    my_event->next     = NULL;
    fprintf(stderr, AC_RESETALL AC_YELLOW AC_REVERSED "[TERMPAINT_EV_CHAR]   |%d|%s|" AC_RESETALL "\n", my_event->modifier, my_event->string);
  } else if (tp_event->type == TERMPAINT_EV_MISC) {
    if (strcmp(tp_event->misc.atom, "FocusIn") == 0) {
      fprintf(stderr, AC_RESETALL AC_GREEN "Focus In" AC_RESETALL "\n");
    }else if (strcmp(tp_event->misc.atom, "FocusOut") == 0) {
      fprintf(stderr, AC_RESETALL AC_RED "Focus Out" AC_RESETALL "\n");
    }else{
      fprintf(stderr, "TERMPAINT_EV_MISC:%s\n", tp_event->misc.atom);
    }
  } else if (tp_event->type == TERMPAINT_EV_KEY) {
    fprintf(stderr, AC_RESETALL AC_YELLOW AC_REVERSED "tp_event->type:%d|%s" AC_RESETALL "\n", tp_event->type, (char *)tp_event->key.atom);
    my_event           = malloc(sizeof(event));
    my_event->type     = tp_event->type;
    my_event->modifier = tp_event->key.modifier;
    my_event->string   = strdup(tp_event->key.atom);
    my_event->next     = NULL;
//    fprintf(stderr, "TERMPAINT_EV_KEY:  |%d|%s|\n", my_event->modifier, my_event->string);
    if (strcmp(my_event->string, "ArrowUp") == 0) {
//        termpaint_image_load(terminal,"/tmp/me");
    }
  } else if (tp_event->type == TERMPAINT_EV_MOUSE) {
    if ((tp_event->mouse.action == TERMPAINT_MOUSE_PRESS && tp_event->mouse.button == 0)
        || tp_event->mouse.action == TERMPAINT_MOUSE_MOVE) {
      cursor_x = tp_event->mouse.x;
      cursor_y = tp_event->mouse.y;
    }

    //SCROLL WHEEL
    switch (tp_event->mouse.button) {
    case 4: mouse_wheel_val++;
      select_next();
      break;
    case 5: mouse_wheel_val--;
      select_prev();
      break;
    }
    sprintf(MSG, "Mouse Event>     "
            "but:%1d|"
            "act:%1d|"
            "loc:%d3x%d3|"
            "sfc:%3dx%d3|"
            "wheel:%lld|"
            "updates:%4lu|",
            tp_event->mouse.button,
            tp_event->mouse.action,
            cursor_x, cursor_y,
            termpaint_surface_width(surface), termpaint_surface_height(surface),
            mouse_wheel_val,
            surface_updates_qty
            );
    write_bottom_msg(MSG);
    //termpaint_image_save(surface,"/tmp/me");
  }

  if (my_event) {
    event *prev = event_current;
    while (prev->next) {
      prev = prev->next;
    }
    prev->next = my_event;
  }
} /* event_callback */

void tb_sig_handler(int sig){
  LOG("SIGWINCH");
  if (SIGWINCH == sig) {

    struct winsize winsz;
    ioctl(0, TIOCGWINSZ, &winsz);
    //fprintf(stderr, "SIGWINCH raised, window size: %d rows / %d columns\n", winsz.ws_row, winsz.ws_col);
    surface_size.height  = (int)winsz.ws_row;
    surface_size.width = (int)winsz.ws_col;
    int  was_width  = termpaint_surface_width(surface);
    int  was_height = termpaint_surface_height(surface);
    termpaint_surface_resize(surface, surface_size.width, surface_size.height);
    char *msg;
    asprintf(&msg, "surface size changed from %dx%d to %dx%d", was_width, was_height, termpaint_surface_width(surface), termpaint_surface_height(surface));
    fprintf(stderr, "%s\n", msg);
    repaint_all(attr_ui, attr_sample);
    menu(attr_ui, attr_sample);
    REDRAW_SURFACE_OBJECTS();
    bool force = true;
    termpaint_terminal_flush_logged(terminal, force);
    LOG(msg);
  }
}

int term_init(void) {
  attr_ui         = termpaint_attr_new(TERMPAINT_DEFAULT_COLOR, TERMPAINT_DEFAULT_COLOR);
  attr_sample     = termpaint_attr_new(TERMPAINT_DEFAULT_COLOR, TERMPAINT_DEFAULT_COLOR);
  attr_bottom_msg = termpaint_attr_new(TERMPAINT_DEFAULT_COLOR, TERMPAINT_DEFAULT_COLOR);

  cursor_profile        = malloc(sizeof(cursor_profile_t));
  event_current         = malloc(sizeof(event));
  event_current->next   = NULL;
  event_current->string = NULL;

  integration = termpaintx_full_integration_setup_terminal_fullscreen("+kbdsigint +kbdsigtstp", event_callback, NULL, &terminal);
  surface     = termpaint_terminal_get_surface(terminal);

//  bool ok = termpaint_surface_resize_mustcheck(surface, 50, 10);
  termpaint_integration_set_logging_func(integration, logging_func);

  if (termpaint_terminal_self_reported_name_and_version(terminal)) {
    char *self_reported_name_and_version = termpaint_terminal_self_reported_name_and_version(terminal);
    fprintf(stderr, AC_RESETALL AC_GREEN "[self_reported_name_and_version] %s\n" AC_RESETALL "\n", self_reported_name_and_version);
  }

//  termpaint_terminal_set_log_mask(terminal, TERMPAINT_LOG_AUTO_DETECT_TRACE | TERMPAINT_LOG_TRACE_RAW_INPUT);

  termpaint_terminal_set_mouse_mode(terminal, TERMPAINT_MOUSE_MODE_CLICKS);
  termpaint_terminal_set_mouse_mode(terminal, TERMPAINT_MOUSE_MODE_DRAG);
  termpaint_terminal_set_mouse_mode(terminal, TERMPAINT_MOUSE_MODE_MOVEMENT);
  termpaint_terminal_request_focus_change_reports(terminal, true);
    struct winsize winsz;
    ioctl(0, TIOCGWINSZ, &winsz);
    surface_size.height  = (int)winsz.ws_row;
    surface_size.width = (int)winsz.ws_col;
    sigaction(SIGWINCH, &(struct sigaction const){ 
        .sa_handler = tb_sig_handler, 
        .sa_flags = SA_NODEFER},0);
//  signal(SIGWINCH, tb_sig_handler);
  LOG("SIGWINCH LOADED");

  cursor_profile->visible = DEFAULT_CURSOR_VISIBLE;
  update_cursor_profile();

  char *d = "B";
  termpaint_terminal_add_input_data(terminal, d, strlen(d));

  clear_bottom_msg(false, false);
  REDRAW_SURFACE_OBJECTS();
  return(EXIT_SUCCESS);
}

static void cleanup(void) {
  termpaint_terminal_free_with_restore(terminal);
  while (event_current) {
    free((void *)event_current->string);
    event *next = event_current->next;
    free(event_current);
    event_current = next;
  }
}

static event *key_wait(void) {
  while (!event_current->next) {
    redraw_bottom_msg();
    if (!termpaintx_full_integration_do_iteration(integration)) {
      cleanup();
      exit(1);
    }
  }

  free((void *)event_current->string);
  event *next = event_current->next;

  free(event_current);
  event_current = next;
  return(next);
}

static void write_sample(termpaint_attr *attr_ui, termpaint_attr *attr_sample, int line, char const *name, int style) {
  termpaint_surface_write_with_attr(surface, 0, line, name, attr_ui);
  termpaint_attr_reset_style(attr_sample);
  termpaint_attr_set_style(attr_sample, style);
  termpaint_surface_write_with_attr(surface, 11, line, "Sample", attr_sample);
}

static void repaint_samples(termpaint_attr *attr_ui, termpaint_attr *attr_sample){
  write_sample(attr_ui, attr_sample, 3, "No Style:", 0);
  write_sample(attr_ui, attr_sample, 4, "Bold:", TERMPAINT_STYLE_BOLD);
  write_sample(attr_ui, attr_sample, 5, "Italic:", TERMPAINT_STYLE_ITALIC);
  write_sample(attr_ui, attr_sample, 6, "Blinking:", TERMPAINT_STYLE_BLINK);
  write_sample(attr_ui, attr_sample, 7, "Underline:", TERMPAINT_STYLE_UNDERLINE);
  write_sample(attr_ui, attr_sample, 8, "Strikeout:", TERMPAINT_STYLE_STRIKE);
  write_sample(attr_ui, attr_sample, 9, "Inverse:", TERMPAINT_STYLE_INVERSE);

  write_sample(attr_ui, attr_sample, 11, "Overline:", TERMPAINT_STYLE_OVERLINE);
  write_sample(attr_ui, attr_sample, 12, "Dbl under:", TERMPAINT_STYLE_UNDERLINE_DBL);
  write_sample(attr_ui, attr_sample, 13, "curly:", TERMPAINT_STYLE_UNDERLINE_CURLY);

  termpaint_attr *attr_url = termpaint_attr_clone(attr_sample);

  termpaint_attr_set_patch(attr_url, true, "\e]8;;http://example.com\a", "\e]8;;\a");
  write_sample(attr_ui, attr_url, 14, "url:", 0);
  termpaint_attr_free(attr_url);
  char *st = malloc(32);
  sprintf(st, "%d", cursor_profile->style);
  termpaint_surface_write_with_attr(surface, 0, 15, "Cursor:", attr_ui);
  termpaint_attr_reset_style(attr_sample);
  termpaint_surface_write_with_attr(surface, 11, 15, " ", attr_sample);
  cursor_profile->x = 11;
  cursor_profile->y = 15;
  free(st);
  update_cursor_profile();
}

static void repaint_all(termpaint_attr *attr_ui, termpaint_attr *attr_sample){
  termpaint_surface_clear_with_attr(surface, attr_ui);
  termpaint_surface_write_with_attr(surface, 1, 0, "Terminal UI", attr_ui);
  repaint_samples(attr_ui, attr_sample);

  termpaint_surface_write_with_attr(surface, 25, 2, "Select Color", attr_ui);

  termpaint_surface_write_with_attr(surface, 2, 20, "q: Quit", attr_ui);
} /* repaint_all */

static void update_current_key_display(termpaint_attr *attr_ui, event *evt) {
  if (evt->type == TERMPAINT_EV_CHAR || evt->type == TERMPAINT_EV_KEY) {
    char buff[100];
    snprintf(buff, 100, "%-20.20s mod: %d", evt->string, evt->modifier);
    termpaint_surface_write_with_attr(surface, 0, 23, "Last key: ", attr_ui);
    termpaint_surface_write_with_attr(surface, 11, 23, buff, attr_ui);
  }
}

static void named_color_menu(termpaint_attr *attr_ui, termpaint_attr *attr_to_change, int which_color) {
  int color = 0;

  while (!quit) {
    surface_updates_qty++;
    {
      termpaint_attr *preview = termpaint_attr_new(0, TERMPAINT_INDEXED_COLOR + color);
      termpaint_surface_write_with_attr(surface, 50, 7, "  ", preview);
      termpaint_attr_free(preview);
    }
    termpaint_surface_write_with_attr(surface, 25, 7, "  Black", attr_ui);
    termpaint_surface_write_with_attr(surface, 25, 8, "  Red", attr_ui);
    termpaint_surface_write_with_attr(surface, 25, 9, "  Green", attr_ui);
    termpaint_surface_write_with_attr(surface, 25, 10, "  Yellow", attr_ui);
    termpaint_surface_write_with_attr(surface, 25, 11, "  Blue", attr_ui);
    termpaint_surface_write_with_attr(surface, 25, 12, "  Magenta", attr_ui);
    termpaint_surface_write_with_attr(surface, 25, 13, "  Cyan", attr_ui);
    termpaint_surface_write_with_attr(surface, 25, 14, "  Light Grey", attr_ui);
    termpaint_surface_write_with_attr(surface, 25, 15, "  Dark Grey", attr_ui);
    termpaint_surface_write_with_attr(surface, 25, 16, "  Bright Red", attr_ui);
    termpaint_surface_write_with_attr(surface, 25, 17, "  Bright Green", attr_ui);
    termpaint_surface_write_with_attr(surface, 25, 18, "  Bright Yellow", attr_ui);
    termpaint_surface_write_with_attr(surface, 25, 19, "  Bright Blue", attr_ui);
    termpaint_surface_write_with_attr(surface, 25, 20, "  Bright Magenta", attr_ui);
    termpaint_surface_write_with_attr(surface, 25, 21, "  Bright Cyan", attr_ui);
    termpaint_surface_write_with_attr(surface, 25, 22, "  White", attr_ui);

    termpaint_surface_write_with_attr(surface, 25, 7 + color, "*", attr_ui);

    event *evt = key_wait();
    update_current_key_display(attr_ui, evt);
    HANDLE_EVENTS();

    if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "ArrowUp") == 0) {
      color = color - 1;
      if (color < 0) {
        color = 15;
      }
    }

    if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "ArrowDown") == 0) {
      color = (color + 1) % 16;
    }

    if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "Enter") == 0) {
      int tp_color = TERMPAINT_NAMED_COLOR + color;
      if (which_color == 0) {
        termpaint_attr_set_fg(attr_to_change, tp_color);
      } else if (which_color == 1) {
        termpaint_attr_set_bg(attr_to_change, tp_color);
      } else {
        termpaint_attr_set_deco(attr_to_change, tp_color);
      }
      return;
    }

    if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "Escape") == 0) {
      return;
    }
  }
} /* named_color_menu */

static void indexed_color_menu(termpaint_attr *attr_ui, termpaint_attr *attr_to_change, int which_color) {
  int color = 0;

  termpaint_surface_write_with_attr(surface, 25, 7, "  0", attr_ui);
  termpaint_surface_write_with_attr(surface, 25, 8, " 16", attr_ui);
  termpaint_surface_write_with_attr(surface, 25, 9, " 32", attr_ui);
  termpaint_surface_write_with_attr(surface, 25, 10, " 48", attr_ui);
  termpaint_surface_write_with_attr(surface, 25, 11, " 64", attr_ui);
  termpaint_surface_write_with_attr(surface, 25, 12, " 80", attr_ui);
  termpaint_surface_write_with_attr(surface, 25, 13, " 96", attr_ui);
  termpaint_surface_write_with_attr(surface, 25, 14, "112", attr_ui);
  termpaint_surface_write_with_attr(surface, 25, 15, "128", attr_ui);
  termpaint_surface_write_with_attr(surface, 25, 16, "144", attr_ui);
  termpaint_surface_write_with_attr(surface, 25, 17, "160", attr_ui);
  termpaint_surface_write_with_attr(surface, 25, 18, "176", attr_ui);
  termpaint_surface_write_with_attr(surface, 25, 19, "192", attr_ui);
  termpaint_surface_write_with_attr(surface, 25, 20, "208", attr_ui);
  termpaint_surface_write_with_attr(surface, 25, 21, "224", attr_ui);
  termpaint_surface_write_with_attr(surface, 25, 22, "240", attr_ui);

  termpaint_surface_write_with_attr(surface, 29, 6, "  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15", attr_ui);
  while (!quit) {
    surface_updates_qty++;
    {
      termpaint_attr *preview = termpaint_attr_new(0, TERMPAINT_INDEXED_COLOR + color);
      termpaint_surface_write_with_attr(surface, 28, 6, "  ", preview);
      termpaint_attr_free(preview);
    }
    termpaint_surface_clear_rect_with_attr(surface, 29, 7, 50, 16, attr_ui);
    char buff[11];
    sprintf(buff, "%3d", color);
    termpaint_surface_write_with_attr(surface, 29 + (color % 16) * 3, 7 + (color / 16), buff, attr_ui);

    event *evt = key_wait();
    update_current_key_display(attr_ui, evt);

    if (evt->type == TERMPAINT_EV_CHAR) {
      if (strcmp(evt->string, "q") == 0) {
        quit = true;
      }
    } else if (evt->type == TERMPAINT_EV_KEY) {
      if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "ArrowLeft") == 0) {
        color -= 1;
        if (color < 0) {
          color = 255;
        }
      } else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "ArrowRight") == 0) {
        color = (color + 1) % 256;
      } else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "ArrowUp") == 0) {
        color -= 16;
        if (color < 0) {
          color += 256;
        }
      } else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "ArrowDown") == 0) {
        color = (color + 16) % 256;
      }

      if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "Enter") == 0) {
        int tp_color = TERMPAINT_INDEXED_COLOR + color;
        if (which_color == 0) {
          termpaint_attr_set_fg(attr_to_change, tp_color);
        } else if (which_color == 1) {
          termpaint_attr_set_bg(attr_to_change, tp_color);
        } else {
          termpaint_attr_set_deco(attr_to_change, tp_color);
        }
        return;
      }

      if (strcmp(evt->string, "Escape") == 0) {
        return;
      }
    }
  }
} /* indexed_color_menu */

static void rgb_color_menu(termpaint_attr *attr_ui, termpaint_attr *attr_to_change, int which_color) {
  int red   = 0;
  int green = 0;
  int blue  = 0;

  int *selected = &red;

  termpaint_surface_write_with_attr(surface, 29, 11, "up/down: adjust value", attr_ui);
  termpaint_surface_write_with_attr(surface, 29, 12, "page up/page down: adjust value (16 increments)", attr_ui);
  termpaint_surface_write_with_attr(surface, 29, 13, "esc: abort", attr_ui);
  termpaint_surface_write_with_attr(surface, 29, 14, "enter: activate color", attr_ui);
  termpaint_surface_write_with_attr(surface, 29, 15, "+: activate cursor visiblity", attr_ui);

  while (!quit) {
    char buff[40];
    sprintf(buff, "R: %3d G: %3d B: %3d", red, green, blue);
    termpaint_surface_write_with_attr(surface, 29, 7, buff, attr_ui);
    termpaint_surface_write_with_attr(surface, 29, 8, "                    ", attr_ui);

    {
      termpaint_attr *preview = termpaint_attr_new(0, TERMPAINT_RGB_COLOR(red, green, blue));
      termpaint_surface_write_with_attr(surface, 52, 7, "  ", preview);
      termpaint_attr_free(preview);
    }

    if (selected == &red) {
      termpaint_surface_write_with_attr(surface, 32, 8, "^^^", attr_ui);
    } else if (selected == &green) {
      termpaint_surface_write_with_attr(surface, 39, 8, "^^^", attr_ui);
    } else if (selected == &blue) {
      termpaint_surface_write_with_attr(surface, 46, 8, "^^^", attr_ui);
    }

    event *evt = key_wait();
    update_current_key_display(attr_ui, evt);

    if (evt->type == TERMPAINT_EV_CHAR) {
      if (strcmp(evt->string, "q") == 0) {
        quit = true;
      }else if (strcmp(evt->string, "q") == 0) {
        if (cursor_profile->style == TERMPAINT_CURSOR_STYLE_BAR) {
          cursor_profile->style = TERMPAINT_CURSOR_STYLE_BLOCK;
        }else if (cursor_profile->style == TERMPAINT_CURSOR_STYLE_BLOCK) {
          cursor_profile->style = TERMPAINT_CURSOR_STYLE_UNDERLINE;
        }else{
          cursor_profile->style = TERMPAINT_CURSOR_STYLE_BAR;
        }
        update_cursor_profile();
      }
    } else if (evt->type == TERMPAINT_EV_KEY) {
      LOG("event key");
      if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "ArrowLeft") == 0) {
        if (selected == &green) {
          selected = &red;
        } else if (selected == &blue) {
          selected = &green;
        }
      } else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "b") == 0) {
        cycle_cursor_blink();
      } else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "v") == 0) {
        cycle_cursor_visiblity();
      } else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "c") == 0) {
        cycle_cursor_style();
      } else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "ArrowRight") == 0) {
        if (selected == &red) {
          selected = &green;
        } else if (selected == &green) {
          selected = &blue;
        }
      } else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "ArrowUp") == 0) {
        *selected = (256 + *selected - 1) % 256;
      } else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "ArrowDown") == 0) {
        *selected = (*selected + 1) % 256;
      } else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "PageUp") == 0) {
        *selected = (256 + *selected - 16) % 256;
      } else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "PageDown") == 0) {
        *selected = (*selected + 16) % 256;
      }

      if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "Enter") == 0) {
        int tp_color = TERMPAINT_RGB_COLOR(red, green, blue);
        if (which_color == 0) {
          termpaint_attr_set_fg(attr_to_change, tp_color);
        } else if (which_color == 1) {
          termpaint_attr_set_bg(attr_to_change, tp_color);
        } else {
          termpaint_attr_set_deco(attr_to_change, tp_color);
        }
        return;
      }

      if (strcmp(evt->string, "Escape") == 0) {
        return;
      }
    }
  }
} /* rgb_color_menu */

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
////////////////////////////////////////////////////////
#define SELECTED_LEFT_ICON                             ICON3
#define SELECTED_RIGHT_ICON                            ICON3
#define SELECTED_LEFT_ICON_SIZE                        1
#define OPTION_ROW_PADDING                             1
#define SELECTED_STYLE                                 (TERMPAINT_STYLE_INVERSE | TERMPAINT_STYLE_BOLD)
#define UNSELECTED_STYLE                               -1
////////////////////////////////////////////////////////
#define TERMINAL_TP_OPTIONS_ROW_TOP_OFFSET             2
#define TERMINAL_TP_OPTIONS_ROW_BOTTOM_OFFSET          5
#define TERMINAL_TP_OPTIONS_RIGHT_PERCENTAGE_OFFSET    .75
#define TP_OPTIONS_UNSELECTED_FG_COLOR                 TERMPAINT_COLOR_WHITE
#define TP_OPTIONS_SELECTED_FG_COLOR                   TERMPAINT_COLOR_GREEN
#define TP_OPTIONS_UNSELECTED_BG_COLOR                 TERMPAINT_DEFAULT_COLOR
#define TP_OPTIONS_SELECTED_BG_COLOR                   TERMPAINT_DEFAULT_COLOR
#define SELECTED_LEFT_MARKER_PREFIX                    "  "
#define SELECTED_LEFT_MARKER_SUFFIX                    "  "
#define SELECTED_LEFT_MARKER                           SELECTED_LEFT_MARKER_PREFIX SELECTED_LEFT_ICON SELECTED_LEFT_MARKER_SUFFIX

char *str_repeat(char str[], unsigned int times){
  if (times < 1) {
    return(NULL);
  }

  char   *result;
  size_t str_len = strlen(str);
  result = malloc(sizeof(char) * str_len + 1);

  while (times--) {
    strcat(result, str);
  }
  return(result);
}

static struct tp_confirm_option_t *o;

void render_tp_options(void){
  char           *text, *marker;
  termpaint_attr *o_attr;
  int            o_col, o_row;
  int            max_option_text_size = tp_get_max_option_text_size();
  int            option_width         = max_option_text_size + (OPTION_ROW_PADDING * 2);
  char           *unselected_marker   = str_repeat(" ", strlen(SELECTED_LEFT_MARKER_PREFIX) + strlen(SELECTED_LEFT_MARKER_SUFFIX) + SELECTED_LEFT_ICON_SIZE);
  int            max_option_rows      = surface_size.height - TERMINAL_TP_OPTIONS_ROW_TOP_OFFSET - TERMINAL_TP_OPTIONS_ROW_BOTTOM_OFFSET;
  {
    for (size_t i = 0; i < vector_size(TP->options) && i <= max_option_rows; i++) {
      o = vector_get(TP->options, i);
      assert(o != NULL);
      assert(o->text != NULL);
      assert(o->uuid != NULL);
      assert(strlen(o->uuid) > 10);
      asprintf(&marker, "%s", (o->selected) ? SELECTED_LEFT_MARKER : unselected_marker);
      asprintf(&text, "%s",
               o->text
               );

      while (strlen(text) < option_width) {
        asprintf(&text, "%s%s", text, " ");
        if (strlen(text) >= option_width) {
          break;
        }
      }

      o_col  = ((surface_size.width * 100) * TERMINAL_TP_OPTIONS_RIGHT_PERCENTAGE_OFFSET / 100);
      o_row  = TERMINAL_TP_OPTIONS_ROW_TOP_OFFSET + i;
      o_attr = termpaint_attr_new(
        o->selected ? TP_OPTIONS_SELECTED_FG_COLOR : TP_OPTIONS_UNSELECTED_FG_COLOR,
        o->selected ? TP_OPTIONS_SELECTED_BG_COLOR : TP_OPTIONS_UNSELECTED_BG_COLOR
        );
      if (o->selected) {
        termpaint_attr_set_style(o_attr, SELECTED_STYLE);
      }else{
        termpaint_attr_reset_style(o_attr);
        if (UNSELECTED_STYLE != -1) {
          termpaint_attr_set_style(o_attr, UNSELECTED_STYLE);
        }
      }
//termpaint_surface_clear_rect_with_attr(surface, o_col - 10, TERMINAL_TP_OPTIONS_ROW_OFFSET + i, 40, 20, attr_ui);
      termpaint_surface_write_with_attr(surface, o_col, o_row, text, o_attr);
//      termpaint_surface_write_with_attr(surface, o_col, o_row-strlen(marker), marker, o_attr);
    }
  }
} /* render_tp_options */

void set_selection_index(size_t NEW_SELECTION_INDEX){
  if (NEW_SELECTION_INDEX < 0) {
    NEW_SELECTION_INDEX = TP->get_options_qty() - 1;
  }else if (NEW_SELECTION_INDEX > TP->get_options_qty() - 1) {
    NEW_SELECTION_INDEX = 0;
  }
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
        if (i == 0) {
          NEW_SELECTION_INDEX = TP->get_options_qty() - 1;
        }else{
          NEW_SELECTION_INDEX = i - 1;
        }
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
  int                        s = 0;
  struct tp_confirm_option_t *O;

  for (size_t i = 0; i < TP->get_options_qty(); i++) {
    O = (struct tp_confirm_option_t *)vector_get(TP->options, i);
    if (strlen(O->text) > s) {
      s = strlen(O->text);
    }
  }
  return(s);
}

int get_selected_index(){
  struct tp_confirm_option_t *O;

  for (size_t i = 0; i < TP->get_options_qty(); i++) {
    O = (struct tp_confirm_option_t *)vector_get(TP->options, i);
    if (O->selected) {
      return(i);
    }
  }
  return(-1);
}

////////////////////////////////////////////////////////
static void menu(termpaint_attr *attr_ui, termpaint_attr *attr_sample) {
  bool sample = true;
  bool reset  = true;

  while (!quit) {
    if (reset) {
      REDRAW_SURFACE_OBJECTS();
      reset = false;
    }

    if (sample) {
      termpaint_surface_write_with_attr(surface, 25, 3, "* Sample", attr_ui);
      termpaint_surface_write_with_attr(surface, 40, 3, "  UI", attr_ui);
    } else {
      termpaint_surface_write_with_attr(surface, 25, 3, "  Sample", attr_ui);
      termpaint_surface_write_with_attr(surface, 40, 3, "* UI", attr_ui);
    }

    event *evt = key_wait();
    update_current_key_display(attr_ui, evt);
    if (evt->type == TERMPAINT_EV_CHAR && strcmp(evt->string, "q") == 0) {
      quit = true;
    } else if (evt->type == TERMPAINT_EV_CHAR && strcmp(evt->string, "b") == 0) {
      cycle_cursor_blink();
    } else if (evt->type == TERMPAINT_EV_CHAR && strcmp(evt->string, "v") == 0) {
      cycle_cursor_visiblity();
    } else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "ArrowUp") == 0) {
      select_prev();
    } else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "ArrowDown") == 0) {
      select_next();
    } else if (evt->type == TERMPAINT_EV_CHAR && strcmp(evt->string, "p") == 0) {
      select_prev();
    } else if (evt->type == TERMPAINT_EV_CHAR && strcmp(evt->string, "n") == 0) {
      select_next();
    } else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "PageUp") == 0) {
      select_page_up();
    } else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "Home") == 0) {
      select_first();
    } else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "PageDown") == 0) {
      select_page_down();
    } else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "End") == 0) {
      select_last();
    } else if (evt->type == TERMPAINT_EV_CHAR && strcmp(evt->string, "t") == 0) {
      title_updates_qty++;

      static char *NEW_TITLE;
      char        *title_chars = TITLE_CHARS[title_updates_qty < 10 ? title_updates_qty : title_updates_qty % 10];
      fwprintf(stderr, L""
               AC_RESETALL AC_RED AC_ITALIC "title chars size" AC_RESETALL ": "
               AC_RESETALL AC_REVERSED AC_BLUE AC_BOLD "%lu" AC_RESETALL
               "\n",
               wcslen(title_chars)
               );

      asprintf(&NEW_TITLE, "|\t%d\t|" "\t%s\t|", title_updates_qty, title_chars);
      sprintf(MSG, "%s", NEW_TITLE);
      termpaint_terminal_set_title(terminal, NEW_TITLE, TERMPAINT_TITLE_MODE_PREFER_RESTORE);

      write_bottom_msg(MSG);
      free(NEW_TITLE);
    } else if (evt->type == TERMPAINT_EV_CHAR && strcmp(evt->string, "5") == 0) {
      INCREASE_BOTTOM_MSG_BG_RED();
    } else if (evt->type == TERMPAINT_EV_CHAR && strcmp(evt->string, "6") == 0) {
      INCREASE_BOTTOM_MSG_BG_GREEN();
    } else if (evt->type == TERMPAINT_EV_CHAR && strcmp(evt->string, "7") == 0) {
      INCREASE_BOTTOM_MSG_BG_BLUE();
    } else if (evt->type == TERMPAINT_EV_CHAR && strcmp(evt->string, "8") == 0) {
      INCREASE_BOTTOM_MSG_FG_RED();
    } else if (evt->type == TERMPAINT_EV_CHAR && strcmp(evt->string, "9") == 0) {
      INCREASE_BOTTOM_MSG_FG_GREEN();
    } else if (evt->type == TERMPAINT_EV_CHAR && strcmp(evt->string, "0") == 0) {
      INCREASE_BOTTOM_MSG_FG_BLUE();
    } else if (evt->type == TERMPAINT_EV_CHAR && strcmp(evt->string, "C") == 0) {
      sprintf(MSG, "");
      write_bottom_msg(MSG);
    } else if (evt->type == TERMPAINT_EV_CHAR && strcmp(evt->string, "r") == 0) {
      sprintf(MSG, "redrawing @ %llu", timestamp());
      write_bottom_msg(MSG);
      REDRAW_SURFACE_OBJECTS();
      termpaint_terminal_flush(terminal, true);
    } else if (evt->type == TERMPAINT_EV_CHAR && strcmp(evt->string, "B") == 0) {
      CYCLE_BORDER_STYLE();
      // sprintf(MSG, "Border Style: #%d | %s", BORDER_STYLE, BORDER_STYLES[BORDER_STYLE]);
      write_bottom_msg(MSG);
    } else if (evt->type == TERMPAINT_EV_CHAR && strcmp(evt->string, "T") == 0) {
      draw_box();
    } else if (evt->type == TERMPAINT_EV_CHAR && strcmp(evt->string, "c") == 0) {
      cycle_cursor_style();
    }else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "ArrowLeft") == 0 && !sample) {
      sample = true;
    }else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "ArrowRight") == 0 && sample) {
      sample = false;
    }else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "Enter") == 0) {
      int which_color = 0;
      termpaint_surface_write_with_attr(surface, 25, 4, "* Foreground", attr_ui);
      termpaint_surface_write_with_attr(surface, 40, 4, "  Background", attr_ui);
      termpaint_surface_write_with_attr(surface, 54, 4, "  Deco", attr_ui);

      while (!quit && !reset) {
        event *evt = key_wait();
        update_current_key_display(attr_ui, evt);

        if (evt->type == TERMPAINT_EV_CHAR && strcmp(evt->string, "q") == 0) {
          quit = true;
        }

        if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "ArrowLeft") == 0 && which_color == 1) {
          termpaint_surface_write_with_attr(surface, 25, 4, "* Foreground", attr_ui);
          termpaint_surface_write_with_attr(surface, 40, 4, "  Background", attr_ui);
          which_color = 0;
        } else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "ArrowLeft") == 0 && which_color == 2) {
          termpaint_surface_write_with_attr(surface, 40, 4, "* Background", attr_ui);
          termpaint_surface_write_with_attr(surface, 54, 4, "  Deco", attr_ui);
          which_color = 1;
        }

        if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "ArrowRight") == 0 && which_color == 0) {
          termpaint_surface_write_with_attr(surface, 25, 4, "  Foreground", attr_ui);
          termpaint_surface_write_with_attr(surface, 40, 4, "* Background", attr_ui);
          which_color = 1;
        } else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "ArrowRight") == 0 && which_color == 1) {
          termpaint_surface_write_with_attr(surface, 40, 4, "  Background", attr_ui);
          termpaint_surface_write_with_attr(surface, 54, 4, "* Deco", attr_ui);
          which_color = 2;
        }

        if (evt->type == TERMPAINT_EV_KEY && (strcmp(evt->string, "ArrowUp") == 0 || strcmp(evt->string, "Escape") == 0)) {
          termpaint_surface_clear_rect_with_attr(surface, 25, 4, 35, 1, attr_ui);
          break;
        }

        if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "Enter") == 0) {
          int type = 0;

          termpaint_surface_write_with_attr(surface, 25, 5, "* Named", attr_ui);
          termpaint_surface_write_with_attr(surface, 40, 5, "  Indexed", attr_ui);
          termpaint_surface_write_with_attr(surface, 53, 5, "  RGB", attr_ui);
          while (!quit && !reset) {
            event *evt = key_wait();
            update_current_key_display(attr_ui, evt);

            if (evt->type == TERMPAINT_EV_CHAR) {
              if (strcmp(evt->string, "q") == 0) {
                quit = true;
              }
            } else {
              if (strcmp(evt->string, "ArrowLeft") == 0 && type == 1) {
                type = 0;
                termpaint_surface_write_with_attr(surface, 25, 5, "* Named", attr_ui);
                termpaint_surface_write_with_attr(surface, 40, 5, "  Indexed", attr_ui);
              } else if (strcmp(evt->string, "ArrowLeft") == 0 && type == 2) {
                type = 1;
                termpaint_surface_write_with_attr(surface, 40, 5, "* Indexed", attr_ui);
                termpaint_surface_write_with_attr(surface, 53, 5, "  RGB", attr_ui);
              } else if (strcmp(evt->string, "ArrowRight") == 0 && type == 0) {
                type = 1;
                termpaint_surface_write_with_attr(surface, 25, 5, "  Named", attr_ui);
                termpaint_surface_write_with_attr(surface, 40, 5, "* Indexed", attr_ui);
              } else if (strcmp(evt->string, "ArrowRight") == 0 && type == 1) {
                type = 2;
                termpaint_surface_write_with_attr(surface, 40, 5, "  Indexed", attr_ui);
                termpaint_surface_write_with_attr(surface, 53, 5, "* RGB", attr_ui);
              } else if (strcmp(evt->string, "ArrowUp") == 0 || strcmp(evt->string, "Escape") == 0) {
                termpaint_surface_clear_rect_with_attr(surface, 25, 5, 35, 1, attr_ui);
                break;
              } else if (strcmp(evt->string, "Enter") == 0) {
                termpaint_surface_clear_rect_with_attr(surface, 29, 14, 25, 3, attr_ui);

                termpaint_attr *to_change = sample ? attr_sample : attr_ui;
                if (type == 0) {
                  named_color_menu(attr_ui, to_change, which_color);
                } else if (type == 1) {
                  indexed_color_menu(attr_ui, to_change, which_color);
                } else {
                  rgb_color_menu(attr_ui, to_change, which_color);
                }
                reset = true;
              }
            }
          }
        }
      }
    }
  }
} /* menu */

#define WRITE_LIT(fd, lit) write(fd, lit, sizeof lit - 1)

void handler(int sig){
        if(sig == SIGINT){
            WRITE_LIT(2, "Signal caught\n");
            execl("./recreate","./recreate", (char*)NULL);
            WRITE_LIT(2, "Couldn't run ./recreate\n");
            _exit(127);
        }
}

int main(){
    while(1);
        return 0;
}
#undef TP
