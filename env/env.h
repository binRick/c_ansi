#pragma once
#ifndef ENV_H
#define ENV_H
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
enum env_log_mode_t {
  ENV_LOG_MODE_NONE = 1,
  ENV_LOG_MODE_ERROR,
  ENV_LOG_MODE_INFO,
  ENV_LOG_MODE_DEBUG,
  ENV_LOG_MODES_QTY,
};

module(env) {
  define(env, CLIB_MODULE);

  enum env_log_mode_t log_mode;
  int                 pid;

  int                 (*GetPID)();
  void                (*info)(char *);
  void                (*debug)(char *);
  void                (*error)(char *);
};

int env_init(module(env) *exports);
void env_deinit(module(env) *exports);

exports(env) {
  .log_mode = ENV_LOG_MODE_NONE,
  .init     = env_init,
  .deinit   = env_deinit,
  .pid      = -1,
};

#define env_m    module(env)

#endif
