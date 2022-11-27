#pragma once
#ifndef TS_H
#define TS_H
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
enum ts_log_mode_t {
  TS_LOG_MODE_NONE = 1,
  TS_LOG_MODE_ERROR,
  TS_LOG_MODE_INFO,
  TS_LOG_MODE_DEBUG,
  TS_LOG_MODES_QTY,
};

module(ts) {
  define(ts, CLIB_MODULE);

  enum ts_log_mode_t log_mode;
  int                pid;

  int                (*GetPID)();
  void               (*info)(char *);
  void               (*debug)(char *);
  void               (*error)(char *);
  unsigned long (*ts)(void);
  unsigned long (*ms)(void);
};

int ts_init(module(ts) *exports);
void ts_deinit(module(ts) *exports);
unsigned long __ts_ts(void);
unsigned long __ts_ms(void);

exports(ts) {
  .log_mode = TS_LOG_MODE_NONE,
  .init     = ts_init,
  .deinit   = ts_deinit,
  .ts=__ts_ts,
  .ms=__ts_ms,
  .pid      = -1,
};

#define ts_m    module(ts)

#endif
