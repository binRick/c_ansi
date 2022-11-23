#pragma once
#ifndef CACHE_H
#define CACHE_H
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
enum cache_log_mode_t {
  CACHE_LOG_MODE_NONE = 1,
  CACHE_LOG_MODE_ERROR,
  CACHE_LOG_MODE_INFO,
  CACHE_LOG_MODE_DEBUG,
  CACHE_LOG_MODES_QTY,
};

module(cache) {
  define(cache, CLIB_MODULE);

  enum cache_log_mode_t log_mode;
  int                   pid;

  int                   (*GetPID)();
  void                  (*info)(char *);
  void                  (*debug)(char *);
  void                  (*error)(char *);
  void                  (*test)(void);
};

int  cache_init(module(cache) * exports);
void cache_deinit(module(cache) * exports);
void __cache_test();

exports(cache) {
  .log_mode = CACHE_LOG_MODE_NONE,
  .init     = cache_init,
  .test     = __cache_test,
  .deinit   = cache_deinit,
  .pid      = -1,
};

#define cache_m    module(cache)

#endif
