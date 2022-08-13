#pragma once
#ifndef TPH
#define TPH
#include "term-termpaint.h"
#include "tp-message-box.h"
#include "tp-utils.h"
/////////////////////////////////////////////////////////////////
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <libgen.h>
#include <locale.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <wchar.h>
/////////////////////////////////////////////////////////////////
#include "tp-defines.h"
#include "tp-types.h"
/////////////////////////////////////////////////////////////////
#include "submodules/c_ansi/ansi-codes/ansi-codes.h"
#include "submodules/c_string_buffer/include/stringbuffer.h"
#include "submodules/c_stringfn/include/stringfn.h"
#include "submodules/timestamp/timestamp.h"
/////////////////////////////////////////////////////////////////
#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//////////////////////////////////////////////////
#include "module/def.h"
#include "module/module.h"
#include "module/require.h"
#include "submodules/uuid4/src/uuid4.h"
/////////////////////////////////////////////////////////////////
int term_tests_main(const int argc, const char **argv);

char *tp_confirm_render(void);
void color_reset();

enum tp_confirm_mode_t {
  AC_CONFIRM_LOG_NONE,
  AC_CONFIRM_LOG_INFO,
  AC_CONFIRM_LOG_ERROR,
  AC_CONFIRM_LOG_DEBUG,
  AC_CONFIRM_LOG_QTY,
};

#define AC_CONFIRM_LOG_DEFAULT    AC_CONFIRM_LOG_INFO
struct tp_confirm_option_t {
  char *text;
  char *selected_color;
  char *color;
  bool selected;
  char *button_s;
  char uuid[UUID4_LEN];
};

int term_init(void), min(int a, int b);
void tb_sig_handler(int sig);
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

struct surface_size_t {
  int height;
  int width;
};
static struct surface_size_t surface_size = { .width = 0, .height = 0 };

#define termpaint_terminal_flush_logged(TERMINAL, FORCE)                                                         \
  { do {                                                                                                         \
      LOG("flush...........\n");                                                                                 \
      bool          _FORCE = FORCE;                                                                              \
      static size_t last_flush_ts;                                                                               \
      static char   termpaint_terminal_flush_msg[512];                                                           \
      unsigned long ts = timestamp();                                                                            \
      if (LOG_TERMINAL_FLUSH_EVENTS) {                                                                           \
        sprintf(termpaint_terminal_flush_msg, "%s<%lu> [%s] (%lums since last) Terminal Flushed %s" AC_RESETALL, \
                (_FORCE == true) ? AC_RED : AC_YELLOW,                                                           \
                (size_t)ts,                                                                                      \
                __FUNCTION__,                                                                                    \
                (size_t)ts - last_flush_ts,                                                                      \
                (_FORCE == true) ? "(forced)" : ""                                                               \
                );                                                                                               \
        LOG(termpaint_terminal_flush_msg);                                                                       \
      }                                                                                                          \
      last_flush_ts = ts;                                                                                        \
      termpaint_terminal_flush(TERMINAL, _FORCE);                                                                \
    }  while (0); }

#define LOG_TERMINAL_FLUSH_EVENTS    true
#define DEFAULT_CURSOR_VISIBLE       false
//////////////////////////////////////////////////////////////////
#define REDRAW_BOTTOM_MSG_MIN_MS     50
//////////////////////////////////////////////////////////////////
#define REDRAW_SURFACE_OBJECTS()    { do {                                        \
                                        render_tp_options();                      \
                                        TERMINAL_KEY_MENU();                      \
                                        termpaint_terminal_flush(terminal, true); \
                                      } while (0); }
//////////////////////////////////////////////////////////////////
#define LOG(STR)                    fprintf(stderr, AC_RESETALL AC_YELLOW "%s\n" AC_RESETALL, STR)
#define TP    require(tp_confirm)

unsigned int BORDER_STYLE,
             BORDER_FG_COLOR_RED,
             BORDER_FG_COLOR_GREEN,
             BORDER_FG_COLOR_BLUE,
             BORDER_BG_COLOR_RED,
             BORDER_BG_COLOR_GREEN,
             BORDER_BG_COLOR_BLUE;

cursor_profile_t
*cursor_profile
;

#endif
