#pragma once
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

// Module Type Interface
module(tp_confirm) {
  define(tp_confirm, CLIB_MODULE);
  //////////////////////////////////////////////////////////////////////////////////////
  //     Config
  //////////////////////////////////////////////////////////////////////////////////////
  enum tp_confirm_mode_t mode;
  //////////////////////////////////////////////////////////////////////////////////////
  //     Properties
  //////////////////////////////////////////////////////////////////////////////////////
  struct Vector *options;
  //////////////////////////////////////////////////////////////////////////////////////
  //     Utility Functions
  //////////////////////////////////////////////////////////////////////////////////////
  bool                       (*add_option)(struct tp_confirm_option_t *NEW_OPTION);
  size_t                     (*get_options_qty)(void);
  struct tp_confirm_option_t *(*init_option)(char *NEW_OPTION_TEXT);
  //////////////////////////////////////////////////////////////////////////////////////
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
