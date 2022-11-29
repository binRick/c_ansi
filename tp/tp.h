#pragma once
#ifndef TPH
#define TPH
#include "tp-internal.h"
/////////////////////////////////////////////////////////////////
#include "term-termpaint.h"
#include "tp-message-box.h"
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
#include "c_ansi/ansi-codes/ansi-codes.h"
#include "c_dbg/dbg.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "timestamp/timestamp.h"
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
char *tp_tabs_render(void);
void color_reset();

int term_init(void), min(int a, int b);
void tb_sig_handler(int sig);

struct surface_size_t {
  int height;
  int width;
};
static struct surface_size_t surface_size = { .width = 0, .height = 0 };

#define termpaint_terminal_flush_logged(TERMINAL, FORCE)                                                           \
  { do {                                                                                                           \
      bool          _FORCE = FORCE;                                                                                \
      static size_t last_flush_ts;                                                                                 \
      static char   termpaint_terminal_flush_msg[512];                                                             \
      unsigned long ts = timestamp();                                                                              \
      if (LOG_TERMINAL_FLUSH_EVENTS) {                                                                             \
        sprintf(termpaint_terminal_flush_msg, "%s<%lu> [%s] (%lums since last) Terminal Flushed %s" AC_RESETALL,   \
                (_FORCE == true) ? AC_RED : AC_YELLOW,                                                             \
                (size_t)ts,                                                                                        \
                __FUNCTION__,                                                                                      \
                (size_t)ts - last_flush_ts,                                                                        \
                (_FORCE == true) ? "(forced)" : ""                                                                 \
                );                                                                                                 \
/*        LOG(termpaint_terminal_flush_msg);                                                                    */ \
      }                                                                                                            \
      last_flush_ts = ts;                                                                                          \
      termpaint_terminal_flush(TERMINAL, _FORCE);                                                                  \
    }  while (0); }

#define LOG_TERMINAL_FLUSH_EVENTS    true
#define DEFAULT_CURSOR_VISIBLE       false
//////////////////////////////////////////////////////////////////
#define REDRAW_BOTTOM_MSG_MIN_MS     50
//////////////////////////////////////////////////////////////////
#define REDRAW_SURFACE_OBJECTS()    { do {                                        \
                                        render_tp_tabs();                         \
                                        render_tp_options();                      \
                                        TERMINAL_KEY_MENU();                      \
                                        termpaint_terminal_flush(terminal, true); \
                                      } while (0); }
//////////////////////////////////////////////////////////////////

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

int tp_get_max_option_text_size();
#endif
