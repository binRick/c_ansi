#pragma once
#ifndef ICON_H
#define ICON_H
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
enum icon_log_mode_t {
  ICON_LOG_MODE_NONE = 1,
  ICON_LOG_MODE_ERROR,
  ICON_LOG_MODE_INFO,
  ICON_LOG_MODE_DEBUG,
  ICON_LOG_MODES_QTY,
};

module(icon) {
  define(icon, CLIB_MODULE);

  enum icon_log_mode_t log_mode;
  int                  pid;

  int                  (*GetPID)();
  void                 (*info)(char *);
  void                 (*debug)(char *);
  void                 (*error)(char *);
};

int icon_init(module(icon) *exports);
void icon_deinit(module(icon) *exports);

exports(icon) {
  .log_mode = ICON_LOG_MODE_NONE,
  .init     = icon_init,
  .deinit   = icon_deinit,
  .pid      = -1,
};

#define icon_m    module(icon)

#endif
