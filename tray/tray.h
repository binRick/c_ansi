#pragma once
#ifndef TRAY_H
#define TRAY_H
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
struct tray_priv_t;
//////////////////////////////////////
enum tray_log_mode_t {
  TRAY_LOG_MODE_NONE = 1,
  TRAY_LOG_MODE_ERROR,
  TRAY_LOG_MODE_INFO,
  TRAY_LOG_MODE_DEBUG,
  TRAY_LOG_MODES_QTY,
};

module(tray) {
  define(tray, CLIB_MODULE);
  enum tray_log_mode_t log_mode;
  struct tray_priv_t *priv;
};

int tray_init(module(tray) *exports);
void tray_deinit(module(tray) *exports);

exports(tray) {
  .log_mode = TRAY_LOG_MODE_NONE,
  .init     = tray_init,
  .deinit   = tray_deinit,
};

#define tray_m    module(tray)

#endif
