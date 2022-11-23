#include "embeds/tbl1.c"
#include "term-termpaint.h"
#include "termpaint-includes.c"
#define DEBUG_PALETTE_COLORS_TO_STDERR    false

termpaint_terminal    *terminal;
termpaint_surface     *surface;
termpaint_integration *integration;
volatile size_t       surface_updates_qty = 0;
void repaint_samples(termpaint_attr *, termpaint_attr *);
void cycle_cursor_style();
void cycle_cursor_visiblity();
void cycle_cursor_blink();
void update_cursor_profile();
void debug_cur_palette();
char *get_cur_palette_name();
char *get_cur_palette_data();
char *get_cur_palette_filename();
struct Palette get_cur_palette();
void normalize_palette_type_selection();

char           *debug     = NULL;
bool           debug_used = false;
bool           quit;
volatile char  _PALETTE_NAME[200]     = "DEFAULT_PALETTE";
char           *PALETTE_NAME          = _PALETTE_NAME;
volatile int   cur_palette_index      = 0;
volatile int   prev_cur_palette_index = 0;
volatile int   CUR_PALETTE_TYPE_ID    = 0;

int            cursor_x = 0;
int            cursor_y = 1;

termpaint_attr *attr_ui;
termpaint_attr *attr_sample;

typedef struct CURSOR_PROFILE {
  int  x;
  int  y;
  bool visible, blink;
  int  style;
} cursor_profile_t;
cursor_profile_t *cursor_profile;
typedef struct event_ {
  int           type;
  int           modifier;
  const char    *string;
  struct event_ *next;
} event;
event *event_current;

void draw_center_options(termpaint_attr *attr_ui){
  termpaint_surface_write_with_attr(surface, 29, 11, "up/down: change palette", attr_ui);
  termpaint_surface_write_with_attr(surface, 29, 12, "c: toggle cursor style", attr_ui);
  termpaint_surface_write_with_attr(surface, 29, 13, "v: toggle cursor visibility", attr_ui);
  termpaint_surface_write_with_attr(surface, 29, 14, "left/right: change select", attr_ui);
  termpaint_surface_write_with_attr(surface, 29, 15, "up/esc: undo choice", attr_ui);
  termpaint_surface_write_with_attr(surface, 29, 16, "enter: follow menu path", attr_ui);
}

static int min(int a, int b) {
  return((a < b) ? a : b);
}
enum cell_t { DEAD,
              ALIVE };
typedef struct board_t_ {
  int  width;
  int  height;
  char *cells;
} board_t;
board_t board;

#define HANDLE_EVENTS()    { do {                                                                     \
                               if (evt->type == TERMPAINT_EV_CHAR && strcmp(evt->string, "q") == 0) { \
                                 quit = true;                                                         \
                               }                                                                      \
                             } while (0); }

volatile char MSG[1024];
#define M(_MSG)            { do {                                                                                 \
                               termpaint_attr *P = termpaint_attr_new(0, TERMPAINT_RGB_COLOR(10, 20, 30));        \
                               termpaint_surface_write_with_attr(surface, 0, 31, _MSG, P);                        \
                               termpaint_surface_write_with_colors(surface,                                       \
                                                                   0, 30,                                         \
                                                                   _MSG,                                          \
                                                                   TERMPAINT_COLOR_GREEN, TERMPAINT_COLOR_BLACK); \
                               termpaint_terminal_flush(terminal, false);                                         \
                             } while (0); }

static char *tp__basename(const char *path){
  const char *slash = strrchr(path, '/');

  if (slash)
    path = slash + 1;
  return((char *)path);
}

void debug_log(termpaint_integration *integration, const char *data, int length) {
  (void)integration;
  if (debug_used && !debug) {
    return;                           // memory allocaton failure
  }
  if (debug) {
    const int oldlen     = strlen(debug);
    char      *debug_old = debug;
    debug = realloc(debug, oldlen + length + 1);
    if (debug) {
      memcpy(debug + oldlen, data, length);
      debug[oldlen + length] = 0;
    } else
      free(debug_old);
  } else
    debug = strndup(data, length);
  debug_used = true;
}

char *cell_at(board_t *board, int x, int y) {
  return(&board->cells[((board->height + y) % board->height) * board->width + ((board->width + x) % board->width)]);
}

void update_cursor_profile(){
  termpaint_terminal_set_cursor_position(terminal, cursor_profile->x, cursor_profile->y);
  termpaint_terminal_set_cursor_visible(terminal, cursor_profile->visible);
  termpaint_terminal_set_cursor_style(terminal, cursor_profile->style, cursor_profile->blink);
}

void cycle_cursor_blink(){
  if (cursor_profile->blink)
    cursor_profile->blink = false;
  else
    cursor_profile->blink = true;
  update_cursor_profile();
}

void cycle_cursor_visiblity(){
  if (cursor_profile->visible)
    cursor_profile->visible = false;
  else
    cursor_profile->visible = true;
  update_cursor_profile();
}

void cycle_cursor_style(){
  if (cursor_profile->style == TERMPAINT_CURSOR_STYLE_BAR)
    cursor_profile->style = TERMPAINT_CURSOR_STYLE_BLOCK;
  else if (cursor_profile->style == TERMPAINT_CURSOR_STYLE_BLOCK)
    cursor_profile->style = TERMPAINT_CURSOR_STYLE_UNDERLINE;
  else
    cursor_profile->style = TERMPAINT_CURSOR_STYLE_BAR;

  update_cursor_profile();
}

void event_callback(void *userdata, termpaint_event *tp_event) {
  (void)userdata;
  // remember tp_event is only valid while this callback runs, so copy everything we need.
  event *my_event = NULL;

  if (tp_event->type == TERMPAINT_EV_CHAR) {
    my_event           = malloc(sizeof(event));
    my_event->type     = tp_event->type;
    my_event->modifier = tp_event->c.modifier;
    my_event->string   = strndup(tp_event->c.string, tp_event->c.length);
    my_event->next     = NULL;
  } else if (tp_event->type == TERMPAINT_EV_KEY) {
    my_event           = malloc(sizeof(event));
    my_event->type     = tp_event->type;
    my_event->modifier = tp_event->key.modifier;
    my_event->string   = strdup(tp_event->key.atom);
    my_event->next     = NULL;
  } else if (tp_event->type == TERMPAINT_EV_MOUSE) {
    if ((tp_event->mouse.action == TERMPAINT_MOUSE_PRESS && tp_event->mouse.button == 0)
        || tp_event->mouse.action == TERMPAINT_MOUSE_MOVE) {
      cursor_x = tp_event->mouse.x;
      cursor_y = tp_event->mouse.y;
      //         char *cell = cell_at(&board, tp_event->mouse.x, tp_event->mouse.y);
      //       *cell = !*cell;
    }
    sprintf(MSG, "mouse event     "
            "button:%d|"
            "action:%d|"
            "location: %dx%d!|"
            "surface: %dx%d!|"
            "surface updates: %lu|",
            tp_event->mouse.button,
            tp_event->mouse.action,
            cursor_x, cursor_y,
            termpaint_surface_width(surface), termpaint_surface_height(surface),
            surface_updates_qty
            );
    M(MSG);
  }

  if (my_event) {
    event *prev = event_current;
    while (prev->next)
      prev = prev->next;
    prev->next = my_event;
  }
} /* event_callback */

bool init(void) {
  cursor_profile        = malloc(sizeof(cursor_profile_t));
  event_current         = malloc(sizeof(event));
  event_current->next   = NULL;
  event_current->string = NULL;
  integration           = termpaint_full_integration_setup_terminal_fullscreen("+kbdsigint +kbdsigtstp",
                                                                               event_callback, NULL,
                                                                               &terminal);
  surface = termpaint_terminal_get_surface(terminal);
  termpaint_integration_set_logging_func(integration, debug_log);

  termpaint_terminal_set_mouse_mode(terminal, TERMPAINT_MOUSE_MODE_CLICKS);
  termpaint_terminal_set_mouse_mode(terminal, TERMPAINT_MOUSE_MODE_MOVEMENT);
//  termpaint_terminal_set_mouse_mode(terminal, TERMPAINT_MOUSE_MODE_DRAG);
  termpaint_terminal_set_title(terminal, "c_palettes :: menu", TERMPAINT_TITLE_MODE_ENSURE_RESTORE);
//  termpaint_terminal_set_color(terminal,TERMPAINT_COLOR_SLOT_BACKGROUND, 100,200,100);
  cursor_profile->visible = true;
  update_cursor_profile();
//    termpaint_terminal_set_cursor_style(t.terminal, TERMPAINT_CURSOR_STYLE_TERM_DEFAULT, true);
/*
 *  termpaint_terminal_set_cursor_style(t.terminal, TERMPAINT_CURSOR_STYLE_BLOCK, false);
 *  termpaint_terminal_set_cursor_style(t.terminal, TERMPAINT_CURSOR_STYLE_BLOCK, false);
 *  termpaint_terminal_set_cursor_style(t.terminal, TERMPAINT_CURSOR_STYLE_BAR, false);
 *  termpaint_terminal_set_cursor_style(t.terminal, TERMPAINT_CURSOR_STYLE_UNDERLINE, true);
 */
//  termpaint_terminal_set_color(terminal,TERMPAINT_COLOR_SLOT_FOREGROUND, 100,200,100);
  char *d = "D";

  termpaint_terminal_add_input_data(terminal, d, strlen(d));
  //   termpaint_surface_clear_rect_with_attr_char(surface, 0, 0, 5, 5,P,"x");
  termpaint_terminal_flush(terminal, false);

  return(1);
}

void cleanup(void) {
  termpaint_terminal_free_with_restore(terminal);

  while (event_current) {
    free((void *)event_current->string);
    event *next = event_current->next;
    free(event_current);
    event_current = next;
  }
}

event * key_wait(void) {
  termpaint_terminal_flush(terminal, false);
  while (!event_current->next)
    if (!termpaint_full_integration_do_iteration(integration)) {
      cleanup();
      exit(1);
    }

  free((void *)event_current->string);
  event *next = event_current->next;

  free(event_current);
  event_current = next;
  return(next);
}

void write_sample(termpaint_attr *attr_ui, termpaint_attr *attr_sample, int line, char const *name, int style) {
  termpaint_surface_write_with_attr(surface, 0, line, name, attr_ui);
  termpaint_attr_reset_style(attr_sample);
  termpaint_attr_set_style(attr_sample, style);
  termpaint_surface_write_with_attr(surface, 11, line, "Sample", attr_sample);
}

void repaint_samples(termpaint_attr *attr_ui, termpaint_attr *attr_sample){
  write_sample(attr_ui, attr_sample, 3, "No Style:", 0);
  write_sample(attr_ui, attr_sample, 4, "Bold:", TERMPAINT_STYLE_BOLD);
  write_sample(attr_ui, attr_sample, 5, "Italic:", TERMPAINT_STYLE_ITALIC);
  write_sample(attr_ui, attr_sample, 6, "Blinking:", TERMPAINT_STYLE_BLINK);
  write_sample(attr_ui, attr_sample, 7, "Underline:", TERMPAINT_STYLE_UNDERLINE);
  write_sample(attr_ui, attr_sample, 8, "Strikeout:", TERMPAINT_STYLE_STRIKE);
  write_sample(attr_ui, attr_sample, 9, "Inverse:", TERMPAINT_STYLE_INVERSE);
//  write_sample(attr_ui, attr_sample, 10,"Dashed:", TERMPAINT_STYLE_DASHED);

  write_sample(attr_ui, attr_sample, 11, "Overline:", TERMPAINT_STYLE_OVERLINE);
  write_sample(attr_ui, attr_sample, 12, "Dbl under:", TERMPAINT_STYLE_UNDERLINE_DBL);
  write_sample(attr_ui, attr_sample, 13, "curly:", TERMPAINT_STYLE_UNDERLINE_CURLY);

  // There is not yet explicit support for URLs, so use the low level patch interface
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
  update_cursor_profile();
}

char *get_palette_type_name(int CUR_PALETTE_TYPE_ID){
  char N[32];

  switch (CUR_PALETTE_TYPE_ID) {
  case 0: sprintf(&N, "%s", "All"); break;
  case 1: sprintf(&N, "%s", "Paleta"); break;
  case 2: sprintf(&N, "%s", "KFC"); break;
  default: sprintf(&N, "%s", "UNKNOWN"); break;
  }
  return(strdup(N));
}

void repaint_all(termpaint_attr *attr_ui, termpaint_attr *attr_sample){
  termpaint_surface_clear_with_attr(surface, attr_ui);
  termpaint_surface_write_with_attr(surface, 1, 0, "Terminal UI", attr_ui);
  repaint_samples(attr_ui, attr_sample);

  termpaint_surface_write_with_attr(surface, 25, 2, "Select Color", attr_ui);

  char *cp_type_msg = malloc(1024);

  sprintf(cp_type_msg,
          "Palette Type: %s",
          get_palette_type_name(CUR_PALETTE_TYPE_ID)
          );
  termpaint_surface_write_with_attr(surface, 65, 2, cp_type_msg, attr_ui);
  free(cp_type_msg);

  char *cp_msg = malloc(1024);

  sprintf(cp_msg,
          "Current Palette: #%d/%lu %s | Type: %s |",
          (cur_palette_index + 1),
          embedded_palettes_table_qty,
          get_cur_palette_name(),
          get_palette_data_type_name(get_cur_palette_data())
          );
  termpaint_surface_write_with_attr(surface, 65, 3, cp_msg, attr_ui);
  free(cp_msg);

  char           *_msg     = malloc(1024 * 32);
  termpaint_attr *set_attr = termpaint_attr_new(TERMPAINT_DEFAULT_COLOR, TERMPAINT_DEFAULT_COLOR);

  sprintf(_msg,
          "Foreground:"
          "\t<#"
          "%s"
          "> -> "
          "%s",
          get_cur_palette().fg,
          get_cur_palette().fg
          );
  termpaint_attr_set_bg(set_attr, TERMPAINT_NAMED_COLOR + 1);
  termpaint_surface_write_with_attr(surface, 65, 5, _msg, attr_ui);

  sprintf(_msg,
          "Background:"
          "\t<#"
          "%s"
          "> -> "
          "%s",
          get_cur_palette().bg,
          get_cur_palette().bg
          );
  termpaint_attr_set_bg(set_attr, TERMPAINT_NAMED_COLOR + 2);
  termpaint_surface_write_with_attr(surface, 65, 6, _msg, set_attr);

  sprintf(_msg,
          "Cursor:"
          "\t\t\t\t\t<#"
          "%s"
          "> -> "
          "%s",
          get_cur_palette().cursor,
          get_cur_palette().cursor
          );
  termpaint_attr_set_bg(set_attr, TERMPAINT_NAMED_COLOR + 3);
  termpaint_surface_write_with_attr(surface, 65, 7, _msg, set_attr);

  free(_msg);
  termpaint_attr_free(set_attr);

  termpaint_surface_write_with_attr(surface, 2, 20, "q: Quit", attr_ui);
} /* repaint_all */

void update_current_key_display(termpaint_attr *attr_ui, event *evt) {
  if (evt->type == TERMPAINT_EV_CHAR || evt->type == TERMPAINT_EV_KEY) {
    char buff[100];
    snprintf(buff, 100, "%-20.20s mod: %d", evt->string, evt->modifier);
    termpaint_surface_write_with_attr(surface, 0, 23, "Last key: ", attr_ui);
    termpaint_surface_write_with_attr(surface, 11, 23, buff, attr_ui);
  }
}

void named_color_menu(termpaint_attr *attr_ui, termpaint_attr *attr_to_change, int which_color) {
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
      if (color < 0)
        color = 15;
    }

    if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "ArrowDown") == 0)
      color = (color + 1) % 16;

    if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "Enter") == 0) {
      int tp_color = TERMPAINT_NAMED_COLOR + color;
      if (which_color == 0)
        termpaint_attr_set_fg(attr_to_change, tp_color);
      else if (which_color == 1)
        termpaint_attr_set_bg(attr_to_change, tp_color);
      else
        termpaint_attr_set_deco(attr_to_change, tp_color);
      return;
    }

    if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "Escape") == 0)
      return;
  }
} /* named_color_menu */

void indexed_color_menu(termpaint_attr *attr_ui, termpaint_attr *attr_to_change, int which_color) {
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
      if (strcmp(evt->string, "q") == 0)
        quit = true;
    } else if (evt->type == TERMPAINT_EV_KEY) {
      if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "ArrowLeft") == 0) {
        color -= 1;
        if (color < 0)
          color = 255;
      } else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "ArrowRight") == 0)
        color = (color + 1) % 256;
      else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "ArrowUp") == 0) {
        color -= 16;
        if (color < 0)
          color += 256;
      } else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "ArrowDown") == 0)
        color = (color + 16) % 256;

      if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "Enter") == 0) {
        int tp_color = TERMPAINT_INDEXED_COLOR + color;
        if (which_color == 0)
          termpaint_attr_set_fg(attr_to_change, tp_color);
        else if (which_color == 1)
          termpaint_attr_set_bg(attr_to_change, tp_color);
        else
          termpaint_attr_set_deco(attr_to_change, tp_color);
        return;
      }

      if (strcmp(evt->string, "Escape") == 0)
        return;
    }
  }
} /* indexed_color_menu */

void rgb_color_menu(termpaint_attr *attr_ui, termpaint_attr *attr_to_change, int which_color) {
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

    if (selected == &red)
      termpaint_surface_write_with_attr(surface, 32, 8, "^^^", attr_ui);
    else if (selected == &green)
      termpaint_surface_write_with_attr(surface, 39, 8, "^^^", attr_ui);
    else if (selected == &blue)
      termpaint_surface_write_with_attr(surface, 46, 8, "^^^", attr_ui);

    event *evt = key_wait();
    update_current_key_display(attr_ui, evt);

    if (evt->type == TERMPAINT_EV_CHAR) {
      if (strcmp(evt->string, "q") == 0)
        quit = true;
      else if (strcmp(evt->string, "q") == 0) {
        sprintf(MSG,
                "cur cursor style:%d|",
                cursor_profile->style
                );
        M(MSG);
        if (cursor_profile->style == TERMPAINT_CURSOR_STYLE_BAR)
          cursor_profile->style = TERMPAINT_CURSOR_STYLE_BLOCK;
        else if (cursor_profile->style == TERMPAINT_CURSOR_STYLE_BLOCK)
          cursor_profile->style = TERMPAINT_CURSOR_STYLE_UNDERLINE;
        else
          cursor_profile->style = TERMPAINT_CURSOR_STYLE_BAR;
        update_cursor_profile();
      }
    } else if (evt->type == TERMPAINT_EV_KEY) {
      if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "ArrowLeft") == 0) {
        if (selected == &green)
          selected = &red;
        else if (selected == &blue)
          selected = &green;
      } else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "b") == 0)
        cycle_cursor_blink();
      else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "v") == 0)
        cycle_cursor_visiblity();
      else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "c") == 0)
        cycle_cursor_style();
      else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "ArrowRight") == 0) {
        if (selected == &red)
          selected = &green;
        else if (selected == &green)
          selected = &blue;
      } else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "ArrowUp") == 0)
        *selected = (256 + *selected - 1) % 256;
      else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "ArrowDown") == 0)
        *selected = (*selected + 1) % 256;
      else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "PageUp") == 0)
        *selected = (256 + *selected - 16) % 256;
      else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "PageDown") == 0)
        *selected = (*selected + 16) % 256;

      if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "Enter") == 0) {
        int tp_color = TERMPAINT_RGB_COLOR(red, green, blue);
        if (which_color == 0)
          termpaint_attr_set_fg(attr_to_change, tp_color);
        else if (which_color == 1)
          termpaint_attr_set_bg(attr_to_change, tp_color);
        else
          termpaint_attr_set_deco(attr_to_change, tp_color);
        return;
      }

      if (strcmp(evt->string, "Escape") == 0)
        return;
    }
  }
} /* rgb_color_menu */

void normalize_palette_type_selection(){
  if (CUR_PALETTE_TYPE_ID < 0)
    CUR_PALETTE_TYPE_ID = 2;
  if (CUR_PALETTE_TYPE_ID > 2)
    CUR_PALETTE_TYPE_ID = 0;
  if (cur_palette_index < 1)
    cur_palette_index = embedded_palettes_table_qty - 1;
  if (cur_palette_index >= embedded_palettes_table_qty)
    cur_palette_index = 0;
  int MAX_CHANGES = 100, CHANGES = 0;

  while (CUR_PALETTE_TYPE_ID != 0 && CUR_PALETTE_TYPE_ID < 3 && (get_cur_palette().Type != (CUR_PALETTE_TYPE_ID - 1))) {
    if (prev_cur_palette_index < cur_palette_index || (prev_cur_palette_index > embedded_palettes_table_qty - 1))
      cur_palette_index++;
    else if (prev_cur_palette_index > cur_palette_index || (prev_cur_palette_index < 0))
      cur_palette_index--;
    else
      cur_palette_index++;
    if (cur_palette_index < 0)
      cur_palette_index = embedded_palettes_table_qty;

    if (cur_palette_index >= embedded_palettes_table_qty)
      cur_palette_index = 0;
    if (CHANGES > MAX_CHANGES)
      break;
    CHANGES++;
  }
  debug_cur_palette();
  repaint_all(attr_ui, attr_sample);
}

void menu(termpaint_attr *attr_ui, termpaint_attr *attr_sample) {
  bool sample = true;
  bool reset  = true;

  while (!quit) {
    if (reset) {
      repaint_all(attr_ui, attr_sample);
      draw_center_options(attr_ui);

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

    if (evt->type == TERMPAINT_EV_CHAR && strcmp(evt->string, "q") == 0)
      quit = true;
    else if (evt->type == TERMPAINT_EV_CHAR && strcmp(evt->string, "b") == 0)
      cycle_cursor_blink();
    else if (evt->type == TERMPAINT_EV_CHAR && strcmp(evt->string, "v") == 0)
      cycle_cursor_visiblity();
    else if (evt->type == TERMPAINT_EV_CHAR && strcmp(evt->string, "c") == 0)
      cycle_cursor_style();
    else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "PageUp") == 0) {
      prev_cur_palette_index = cur_palette_index;
      CUR_PALETTE_TYPE_ID++;
      normalize_palette_type_selection();
    }else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "PageDown") == 0) {
      prev_cur_palette_index = cur_palette_index;
      CUR_PALETTE_TYPE_ID--;
      normalize_palette_type_selection();
    }else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "ArrowUp") == 0) {
      prev_cur_palette_index = cur_palette_index;
      cur_palette_index++;
      normalize_palette_type_selection();
    }else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "ArrowDown") == 0) {
      prev_cur_palette_index = cur_palette_index;
      cur_palette_index--;
      normalize_palette_type_selection();
    }else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "ArrowLeft") == 0 && !sample)
      sample = true;
    else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "ArrowRight") == 0 && sample)
      sample = false;
    else if (evt->type == TERMPAINT_EV_KEY && strcmp(evt->string, "Enter") == 0) {
      int which_color = 0;

      termpaint_surface_write_with_attr(surface, 25, 4, "* Foreground", attr_ui);
      termpaint_surface_write_with_attr(surface, 40, 4, "  Background", attr_ui);
      termpaint_surface_write_with_attr(surface, 54, 4, "  Deco", attr_ui);

      while (!quit && !reset) {
        event *evt = key_wait();
        update_current_key_display(attr_ui, evt);

        if (evt->type == TERMPAINT_EV_CHAR && strcmp(evt->string, "q") == 0)
          quit = true;

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
              if (strcmp(evt->string, "q") == 0)
                quit = true;
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
                if (type == 0)
                  named_color_menu(attr_ui, to_change, which_color);
                else if (type == 1)
                  indexed_color_menu(attr_ui, to_change, which_color);
                else
                  rgb_color_menu(attr_ui, to_change, which_color);
                reset = true;
              }
            }
          }
        }
      }
    }
  }
} /* menu */

struct Palette get_cur_palette(){
  return(get_palette(get_cur_palette_data()));
}

char *get_cur_palette_filename(){
  return(embedded_palettes_table[cur_palette_index].filename);
}

char *get_cur_palette_data(){
  return(embedded_palettes_table[cur_palette_index].data);
}

char *get_cur_palette_name(){
  return(tp__basename(get_cur_palette_filename()));
}

void debug_cur_palette(){
  if (!DEBUG_PALETTE_COLORS_TO_STDERR)

  fprintf(stderr,
          "==============\n%s\n==============\n",
          get_cur_palette_data()
          );
  fprintf(stderr,
          "Palette #%d: %s (%s) -> %lu bytes\n",
          cur_palette_index,
          get_cur_palette_name(),
          get_cur_palette_filename(),
          strlen(get_cur_palette_data())
          );
  fprintf(stderr,
          AC_RESETALL AC_BLUE AC_REVERSED     "[Palette]" AC_RESETALL "\n"
          AC_RESETALL AC_YELLOW AC_REVERSED   "\t|Name:\t\t%s|" AC_RESETALL "\n"
          AC_RESETALL AC_YELLOW AC_REVERSED   "\t|Type:\t\t%s|" AC_RESETALL "\n"
          AC_RESETALL AC_YELLOW AC_REVERSED   "\t|FG:\t\t%s|" AC_RESETALL "\n"
          AC_RESETALL AC_YELLOW AC_REVERSED   "\t|BG:\t\t%s|" AC_RESETALL "\n"
          AC_RESETALL AC_YELLOW AC_REVERSED   "\t|Cursor:\t%s|" AC_RESETALL "\n"
          ////////////////////////////////////////////////////////////////////////
          AC_RESETALL "  " AC_ITALIC AC_GREEN AC_REVERSED   "|Foreground|" AC_RESETALL "\n"
          ////////////////////////////////////////////////////////////////////////
          AC_RESETALL AC_BLACK_WHITE AC_REVERSED   "\t|Black:%10s|" AC_RESETALL "\n"
          AC_RESETALL AC_RED AC_REVERSED     "\t|Red:%10s|" AC_RESETALL "\n"
          AC_RESETALL AC_YELLOW AC_REVERSED  "\t|Yellow:%10s|" AC_RESETALL "\n"
          AC_RESETALL AC_BLUE AC_REVERSED    "\t|Blue:%10s|" AC_RESETALL "\n"
          AC_RESETALL AC_BLUE AC_REVERSED    "\t|Magenta:%10s|" AC_RESETALL "\n"
          AC_RESETALL AC_BLUE AC_REVERSED    "\t|Cyan:%10s|" AC_RESETALL "\n"
          AC_RESETALL AC_BLUE AC_REVERSED    "\t|White:%10s|" AC_RESETALL "\n"
          ////////////////////////////////////////////////////////////////////////
          AC_RESETALL "  " AC_ITALIC AC_GREEN AC_REVERSED   "|Background|" AC_RESETALL "\n"
          ////////////////////////////////////////////////////////////////////////
          AC_RESETALL AC_BLACK_WHITE AC_REVERSED   "\t|Black:%10s|" AC_RESETALL "\n"
          AC_RESETALL AC_RED AC_REVERSED     "\t|Red:%10s|" AC_RESETALL "\n"
          AC_RESETALL AC_YELLOW AC_REVERSED  "\t|Yellow:%10s|" AC_RESETALL "\n"
          AC_RESETALL AC_BLUE AC_REVERSED    "\t|Blue:%10s|" AC_RESETALL "\n"
          AC_RESETALL AC_BLUE AC_REVERSED    "\t|Magenta:%10s|" AC_RESETALL "\n"
          AC_RESETALL AC_BLUE AC_REVERSED    "\t|Cyan:%10s|" AC_RESETALL "\n"
          AC_RESETALL AC_BLUE AC_REVERSED    "\t|White:%10s|" AC_RESETALL "\n"
          ////////////////////////////////////////////////////////////////////////
          , get_cur_palette_name(),
          get_cur_palette().TypeName
          /////////////////////////////////////
          , get_cur_palette().fg,
          get_cur_palette().bg,
          get_cur_palette().cursor
          /////////////////////////////////////
          , get_cur_palette().fgColors->black,
          get_cur_palette().fgColors->red,
          get_cur_palette().fgColors->yellow,
          get_cur_palette().fgColors->blue,
          get_cur_palette().fgColors->magenta,
          get_cur_palette().fgColors->cyan,
          get_cur_palette().fgColors->white
          /////////////////////////////////////
          , get_cur_palette().bgColors->black,
          get_cur_palette().bgColors->red,
          get_cur_palette().bgColors->yellow,
          get_cur_palette().bgColors->blue,
          get_cur_palette().bgColors->magenta,
          get_cur_palette().bgColors->cyan,
          get_cur_palette().bgColors->white
          /////////////////////////////////////
          );
  fprintf(stderr,
          "%lu palette names\n",
          embedded_palettes_table_qty
          );
} /* debug_cur_palette */

int term_termpaint_main(int argc, char **argv) {
  (void)argc; (void)argv;
  if (!init())
    return(1);

  debug_cur_palette();

  attr_ui     = termpaint_attr_new(TERMPAINT_DEFAULT_COLOR, TERMPAINT_DEFAULT_COLOR);
  attr_sample = termpaint_attr_new(TERMPAINT_DEFAULT_COLOR, TERMPAINT_DEFAULT_COLOR);

  repaint_all(attr_ui, attr_sample);

  menu(attr_ui, attr_sample);

  termpaint_attr_free(attr_sample);
  attr_sample = NULL;
  termpaint_attr_free(attr_ui);
  attr_ui = NULL;

  cleanup();
  return(0);
}
