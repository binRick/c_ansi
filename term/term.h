#pragma once
#ifndef TERM_H
#define TERM_H
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
enum term_log_mode_t {
  TERM_LOG_MODE_NONE = 1,
  TERM_LOG_MODE_ERROR,
  TERM_LOG_MODE_INFO,
  TERM_LOG_MODE_DEBUG,
  TERM_LOG_MODES_QTY,
};

module(term) {
  define(term, CLIB_MODULE);

  enum term_log_mode_t log_mode;
  int                  pid;

  int                  (*GetPID)();
  void                 (*info)(char *);
  void                 (*debug)(char *);
  void                 (*error)(char *);
};

int term_init(module(term) *exports);
void term_deinit(module(term) *exports);

exports(term) {
  .log_mode = TERM_LOG_MODE_NONE,
  .init     = term_init,
  .deinit   = term_deinit,
  .pid      = -1,
};

#define term_m    module(term)

#endif
