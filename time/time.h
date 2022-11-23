#pragma once
#ifndef TIME_H
#define TIME_H
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
enum time_log_mode_t {
  TIME_LOG_MODE_NONE = 1,
  TIME_LOG_MODE_ERROR,
  TIME_LOG_MODE_INFO,
  TIME_LOG_MODE_DEBUG,
  TIME_LOG_MODES_QTY,
};

module(time) {
  define(time, CLIB_MODULE);

  enum time_log_mode_t log_mode;
  int                  pid;

  int                  (*GetPID)();
  void                 (*info)(char *);
  void                 (*debug)(char *);
  void                 (*error)(char *);
};

int time_init(module(time) *exports);
void time_deinit(module(time) *exports);
/*
exports(time) {
  .log_mode = TIME_LOG_MODE_NONE,
  .init     = time_init,
  .deinit   = time_deinit,
  .pid      = -1,
};

#define time_m    module(time)
*/
#endif
