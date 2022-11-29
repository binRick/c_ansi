#pragma once
#ifndef TESSERACT_H
#define TESSERACT_H
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
enum tess_log_mode_t {
  TESSERACT_LOG_MODE_NONE = 1,
  TESSERACT_LOG_MODE_ERROR,
  TESSERACT_LOG_MODE_INFO,
  TESSERACT_LOG_MODE_DEBUG,
  TESSERACT_LOG_MODES_QTY,
};

struct tess_t;

module(tess) {
  define(tess, CLIB_MODULE);

  enum tess_log_mode_t log_mode;
  int                  pid;

  int                  (*GetPID)();
  void                 (*info)(char *);
  void                 (*debug)(char *);
  void                 (*error)(char *);
  struct tess_t        *tess;
  void                 (*mem)(const unsigned char *ptr, const size_t len);
};

int  tess_init(module(tess) * exports);
void tess_deinit(module(tess) * exports);
void __tess_mem(const unsigned char *ptr, const size_t len);

exports(tess) {
  .log_mode = TESSERACT_LOG_MODE_NONE,
  .init     = tess_init,
  .deinit   = tess_deinit,
  .mem      = __tess_mem,
  .pid      = -1,
};

#define tess_m    module(tess)

#endif
