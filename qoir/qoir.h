#pragma once
#ifndef QOIR_H
#define QOIR_H
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
#include "qoir/src/qoir.h"
//////////////////////////////////////
enum qoir_log_mode_t {
  QOIR_LOG_MODE_NONE = 1,
  QOIR_LOG_MODE_ERROR,
  QOIR_LOG_MODE_INFO,
  QOIR_LOG_MODE_DEBUG,
  QOIR_LOG_MODES_QTY,
};

module(qoir) {
  define(qoir, CLIB_MODULE);

  enum qoir_log_mode_t log_mode;
  int                  pid;
  int                  (*GetPID)();
  qoir_decode_result   (*decode)(const unsigned char *ptr, size_t len);
  qoir_decode_result   (*decode_path)(const char *path);
};

int  qoir_init(module(qoir) * exports);
void qoir_deinit(module(qoir) * exports);
qoir_decode_result __qoir_decode(const unsigned char *ptr, size_t len);
qoir_decode_result __qoir_decode_path(const char *path);

exports(qoir) {
  .log_mode    = QOIR_LOG_MODE_NONE,
  .init        = qoir_init,
  .decode_path = __qoir_decode_path,
  .decode      = __qoir_decode,
  .deinit      = qoir_deinit,
  .pid         = -1,
};

#define qoir_m    module(qoir)

#endif
