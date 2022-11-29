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
struct qr_encode_options_t {
  int version;
  unsigned char *data;
  size_t data_len;
  char *str;
  char *path;
};

module(qr) {
  define(qr, CLIB_MODULE);
  enum qr_log_mode_t log_mode;
  bool               (*qrcode)(char *png_path);
  module(qr_encode){
    unsigned char *(*str)(const char *str, size_t *encoded_len);
    unsigned char *(*buf)(const char *buf, size_t *buf_len, size_t *encoded_len);
    unsigned char *(*path)(const char *path, size_t *encoded_len);
  } *encode;
  module(qr_decode){
    module(qr_decode_buffer){
      char *(*text)(const unsigned *buf,size_t len);
      unsigned char *(*data)(const unsigned *buf,size_t len,size_t *buf_len);
      int (*version)(const unsigned *buf,size_t len);
      bool (*valid)(const unsigned *buf,size_t len);
      int (*matches)(const unsigned *buf,size_t len);
    } *buffer;
    module(qr_decode_path){
      char *(*text)(const char *path);
      unsigned char *(*data)(const char *path, size_t *buf_len);
      int (*version)(const char *path);
      bool (*valid)(const char *path);
      int (*matches)(const char *path);
      bool (*match)(const char *path, int match_index, 
          unsigned char *data,
          size_t *len,
          size_t *capacity,
          int *bottom_left_x, int *top_left_x, int *top_right_x, int *bottom_right_x,
          int *bottom_left_y, int *top_left_y, int *to_right_y, int *bottom_right_y
          );
    } *path;
  } *decode;
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
