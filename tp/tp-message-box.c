#pragma once
#ifndef TPMBC
#define TPMBC

#include "term-termpaint.h"
#include "term-termpaint.h"
#include "termpaint.h"
#include "termpaint_image.h"
#include "termpaintx.h"
#include "termpaintx_ttyrescue.h"
#include "tp-utils.h"
#include "tp.h"
#include <assert.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
////////////////////////////////////////////////////
#include "ansi-codes.h"
#include "ansi-utils/ansi-utils.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "module/def.h"
#include "module/module.h"
////////////////////////////////////////////////////
#include "wildcardcmp/wildcardcmp.h"
////////////////////////////////////////////////////
#include "module/require.h"
#include "tiny-regex-c/re.h"
#include "tp-message-box.h"
#include "tp.h"
#define BOTTOM_MSG_BOX_TOP       BOTTOM_MSG_BOX_TOPS[BORDER_STYLE]
#define BOTTOM_MSG_BOX_BOTTOM    BOTTOM_MSG_BOX_BOTTOMS[BORDER_STYLE]
#define BOTTOM_MSG_BOX_SIDE      BOTTOM_MSG_BOX_SIDES[BORDER_STYLE]
#define BOTTOM_MSG_FG_COLOR      TERMPAINT_RGB_COLOR(BORDER_FG_COLOR_RED, BORDER_FG_COLOR_GREEN, BORDER_FG_COLOR_BLUE)
#define BOTTOM_MSG_BG_COLOR      TERMPAINT_RGB_COLOR(BORDER_BG_COLOR_RED, BORDER_BG_COLOR_GREEN, BORDER_BG_COLOR_BLUE)
#define BOTTOM_MSG_COLORS        BOTTOM_MSG_FG_COLOR, BOTTOM_MSG_BG_COLOR
const char
BOTTOM_MSG_BOX_TOP_SINGLE[]    = "┌───────────────────────────────────────────────────────────────────────────────────────────────────────┐",
BOTTOM_MSG_BOX_SIDE_SINGLE[]   = "│                                                                                                       │",
BOTTOM_MSG_BOX_BOTTOM_SINGLE[] = "└───────────────────────────────────────────────────────────────────────────────────────────────────────┘", BOTTOM_MSG_BOX_TOP_DOUBLE[] = "╔═══════════════════════════════════════════════════════════════════════════════════════════════════════╗",
BOTTOM_MSG_BOX_SIDE_DOUBLE[]   = "║                                                                                                       ║",
BOTTOM_MSG_BOX_BOTTOM_DOUBLE[] = "╚═══════════════════════════════════════════════════════════════════════════════════════════════════════╝",
*BOTTOM_MSG_BOX_TOPS[]         = { BOTTOM_MSG_BOX_TOP_SINGLE, BOTTOM_MSG_BOX_TOP_DOUBLE },
*BOTTOM_MSG_BOX_SIDES[]        = { BOTTOM_MSG_BOX_SIDE_SINGLE, BOTTOM_MSG_BOX_SIDE_DOUBLE },
*BOTTOM_MSG_BOX_BOTTOMS[]      = { BOTTOM_MSG_BOX_BOTTOM_SINGLE, BOTTOM_MSG_BOX_BOTTOM_DOUBLE }
;
termpaint_attr
*attr_bottom_msg
;

void draw_box() {
  const int screen_width  = termpaint_surface_width(surface),
            screen_height = termpaint_surface_height(surface),
            top_left_x    = (screen_width / 2) - 12,
            top_left_y    = (screen_height / 2) - 2;

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

void clear_bottom_msg(bool SKIP_FLUSH, __attribute__((unused)) bool FORCE_FLUSH){
  bool cursor_visible = cursor_profile->visible;

  if (cursor_visible)
    cursor_profile->visible = false;
  termpaint_surface_clear_rect_with_attr(surface,
                                         0,
                                         termpaint_surface_height(surface) - BOTTOM_MSG_BOX_HEIGHT + 1,
                                         termpaint_surface_width(surface),
                                         BOTTOM_MSG_BOX_HEIGHT,
                                         attr_bottom_msg
                                         );
  termpaint_surface_write_with_colors(surface,
                                      BOTTOM_MSG_BOX_COL,
                                      termpaint_surface_height(surface) - 3,
                                      BOTTOM_MSG_BOX_TOP,
                                      BOTTOM_MSG_COLORS
                                      );
  termpaint_surface_write_with_colors(surface,
                                      BOTTOM_MSG_BOX_COL,
                                      termpaint_surface_height(surface) - 2,
                                      BOTTOM_MSG_BOX_SIDE,
                                      BOTTOM_MSG_COLORS
                                      );
  termpaint_surface_write_with_colors(surface,
                                      BOTTOM_MSG_BOX_COL,
                                      termpaint_surface_height(surface) - 1,
                                      BOTTOM_MSG_BOX_BOTTOM,
                                      BOTTOM_MSG_COLORS
                                      );
  if (!SKIP_FLUSH) {
//    termpaint_terminal_flush_logged(terminal, FORCE_FLUSH);
  }
  cursor_profile->visible = cursor_visible;
}

void redraw_bottom_msg(){
  static long unsigned last_redraw_bottom_msg_ts = 0;
  long unsigned        ts                        = timestamp();

  if ((last_redraw_bottom_msg_ts == 0) || ((ts - last_redraw_bottom_msg_ts) > REDRAW_BOTTOM_MSG_MIN_MS)) {
    clear_bottom_msg(true, false);
    termpaint_surface_write_with_colors(surface,
                                        BOTTOM_MSG_BOX_COL + BOTTOM_MSG_BOX_COL_MSG_OFFSET,
                                        termpaint_surface_height(surface) - 2,
                                        CACHED_BOTTOM_MSG,
                                        BOTTOM_MSG_COLORS
                                        );
    termpaint_terminal_flush_logged(terminal, false);
    last_redraw_bottom_msg_ts = ts;
  }
}

void write_bottom_msg(const char *BOTTOM_MSG){
  sprintf(CACHED_BOTTOM_MSG, "%s", BOTTOM_MSG);
  redraw_bottom_msg();
}

#endif
