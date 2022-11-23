#pragma once
#ifndef HASH_H
#define HASH_H
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
enum hash_log_mode_t {
  HASH_LOG_MODE_NONE = 1,
  HASH_LOG_MODE_ERROR,
  HASH_LOG_MODE_INFO,
  HASH_LOG_MODE_DEBUG,
  HASH_LOG_MODES_QTY,
};

module(hash) {
  define(hash, CLIB_MODULE);

  enum hash_log_mode_t log_mode;
  int                  pid;

  int                  (*GetPID)();
  void                 (*info)(char *);
  void                 (*debug)(char *);
  void                 (*error)(char *);
};

int hash_init(module(hash) *exports);
void hash_deinit(module(hash) *exports);

exports(hash) {
  .log_mode = HASH_LOG_MODE_NONE,
  .init     = hash_init,
  .deinit   = hash_deinit,
  .pid      = -1,
};

#define hash_m    module(hash)

#endif
