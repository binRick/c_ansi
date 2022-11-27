#pragma once
#ifndef KITTY_H
#define KITTY_H
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
enum kitty_log_mode_t {
  KITTY_LOG_MODE_NONE = 1,
  KITTY_LOG_MODE_ERROR,
  KITTY_LOG_MODE_INFO,
  KITTY_LOG_MODE_DEBUG,
  KITTY_LOG_MODES_QTY,
};

module(kitty) {
  define(kitty, CLIB_MODULE);

  enum kitty_log_mode_t log_mode;
  int                   pid;

  int                   (*GetPID)();
  void                  (*info)(char *);
  void                  (*debug)(char *);
  void                  (*error)(char *);
};

int  kitty_init(module(kitty) * exports);
void kitty_deinit(module(kitty) * exports);

exports(kitty) {
  .log_mode = KITTY_LOG_MODE_NONE,
  .init     = kitty_init,
  .deinit   = kitty_deinit,
  .pid      = -1,
};

#define kitty_m    module(kitty)

#endif
