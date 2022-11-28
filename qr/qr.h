#pragma once
#ifndef QR_H
#define QR_H
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
#include "qrencode.h"
#include "qrcode/qrcode.h"
//////////////////////////////////////
#include "module/def.h"
#include "module/module.h"
#include "module/require.h"
//////////////////////////////////////
enum qr_log_mode_t {
  QR_LOG_MODE_NONE = 1,
  QR_LOG_MODE_ERROR,
  QR_LOG_MODE_INFO,
  QR_LOG_MODE_DEBUG,
  QR_LOG_MODES_QTY,
};

module(qr) {
  define(qr, CLIB_MODULE);
  enum qr_log_mode_t log_mode;
  bool               (*qrcode)(char *png_path);
  bool (*encode)(const char *str);
};

int qr_init(module(qr) *exports);
void qr_deinit(module(qr) *exports);
bool __qr_qrcode(char *png_path);
bool __qr_encode_str(const char *str);

exports(qr) {
  .log_mode = QR_LOG_MODE_NONE,
  .encode=__qr_encode_str,
  .init     = qr_init,
  .deinit   = qr_deinit,
  .qrcode=__qr_qrcode,
};

#define qr_m    module(qr)

#endif
