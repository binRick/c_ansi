#pragma once
#ifndef IMG_H
#define IMG_H
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
enum img_log_mode_t {
  IMG_LOG_MODE_NONE = 1,
  IMG_LOG_MODE_ERROR,
  IMG_LOG_MODE_INFO,
  IMG_LOG_MODE_DEBUG,
  IMG_LOG_MODES_QTY,
};

module(img) {
  define(img, CLIB_MODULE);

  enum img_log_mode_t log_mode;
  int                 pid;

  int                 (*GetPID)();
  void                (*info)(char *);
  void                (*debug)(char *);
  void                (*error)(char *);
};

int  img_init(module(img) * exports);
void img_deinit(module(img) * exports);

exports(img) {
  .log_mode = IMG_LOG_MODE_NONE,
  .init     = img_init,
  .deinit   = img_deinit,
  .pid      = -1,
};

#define img_m    module(img)

#endif
