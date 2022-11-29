#pragma once
#ifndef WIN_H
#define WIN_H
//////////////////////////////////////
#include <assert.h>
#include <ctype.h>
#include <err.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//////////////////////////////////////
#include "module/def.h"
#include "module/module.h"
#include "module/require.h"
//////////////////////////////////////
enum win_log_mode_t {
  WIN_LOG_MODE_NONE = 1,
  WIN_LOG_MODE_ERROR,
  WIN_LOG_MODE_INFO,
  WIN_LOG_MODE_DEBUG,
  WIN_LOG_MODES_QTY,
};

module(win) {
  define(win, CLIB_MODULE);
  enum win_log_mode_t log_mode;
  module(win_ls) {
    module(win_ls_ids) {
      struct Vector *(*vec)();
      char          **(*arr)(int *qty);

      size_t        (*qty)(void);
    } *ids;
    module(win_ls_names) {
      struct Vector *(*vec)();
      char          **(*arr)(int *qty);

      size_t        (*qty)(void);
    } *names;
  } *ls;
  size_t (*qty)();
  bool   (*open)(int width, int height);
  bool   (*resize)(int window_id);
  bool   (*move)(int window_id);
  bool   (*position)(int window_id);
  module(win_window_is){
    define(win_window_is, CLIB_MODULE);
    bool (*visible)(int window_id);
    bool (*minimized)(int window_id);
    bool (*unminimized)(int window_id);
    bool (*active)(int window_id);
    module(win_window_is_on){
      define(win_window_is_on, CLIB_MODULE);
      module(win_window_is_on_space){
        define(win_window_is_on_space, CLIB_MODULE);
        bool (*id)(int window_id, size_t space_id);
        int  (*index)(int window_id, int space_index);
        char *(*uuid)(int window_id, const char *uuid);
      } *space;
      module(win_window_is_on_display){
        define(win_window_is_on_display, CLIB_MODULE);
        bool (*id)(int window_id, size_t display_id);
        int  (*index)(int window_id, int display_index);
        char *(*uuid)(int window_id, const char *uuid);
      } *display;
    } *on;
  } *is;
  module(win_window_space){
    define(win_window_space, CLIB_MODULE);
    size_t (*id)(int window_id);
    int    (*index)(int window_id);
    int    (*offset)(int window_id);
    char   *(*uuid)(int window_id);
  } *space;
  module(win_window_display){
    define(win_window_display, CLIB_MODULE);
    size_t (*id)(int window_id);
    int    (*index)(int window_id);
    int    (*offset)(int window_id);
    char   *(*uuid)(int window_id);
  } *display;
};

int  win_init(module(win) * exports);
void win_deinit(module(win) * exports);
static bool   __win_window_id_is_active(size_t window_id);

exports(win) {
  .log_mode = WIN_LOG_MODE_NONE,
  .init     = win_init,
  .deinit   = win_deinit,
};

#define win_m    module(win)

#endif
