#pragma once
#ifndef QR_C
#define QR_C
////////////////////////////////////////////
#include <stdbool.h>
bool __qr_qrcode(char *png_path);
////////////////////////////////////////////
#include "qr/qr.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "ms/ms.h"
#include "qrcode/qrcode.h"
#include "qrencode.h"
#include "timestamp/timestamp.h"

////////////////////////////////////////////
bool __qr_encode_str(const char *str){
  char *ver = QRcode_APIVersionString();

  Ds(ver);
  QRcode *qr = QRcode_encodeString(str, 0, QR_ECLEVEL_H, QR_MODE_8, 1);

  Di(qr->width);
  Di(qr->version);
  QRcode_free(qr);
  return(true);
}

bool __qr_qrcode(char *png_path){
  struct qr_code_match_list  *matches;
  struct finder_pattern_list *finder_patterns, *tmp_finder_patterns;
  struct qr_code_match_list  *tmp;
  int                        res;

  res = find_qr_codes(png_path, &matches, &finder_patterns);
  if (res == MEMORY_ERROR) {
    log_error("Memory allocation error\n");
    return(false);
  }else if (res == CANNOT_LOAD_IMAGE) {
    log_error("Cannot load image '%s'\n", png_path);
    return(false);
  }
  tmp_finder_patterns = finder_patterns;
  while (tmp_finder_patterns != NULL) {
    int center_x = (int)tmp_finder_patterns->pattern.x;
    int center_y = (int)tmp_finder_patterns->pattern.y;
    int radius   = (int)(5 * tmp_finder_patterns->pattern.module_size);
    log_info("center: %dx%d, radius: %d", center_x, center_y, radius);
    tmp_finder_patterns = tmp_finder_patterns->next;
  }
  free_finder_pattern_list(finder_patterns);
  tmp = matches;
  while (tmp != NULL) {
    int min_x = tmp->bottom_left_x;
    if (min_x > tmp->top_left_x) min_x = tmp->top_left_x;
    if (min_x > tmp->top_right_x) min_x = tmp->top_right_x;
    if (min_x > tmp->bottom_right_x) min_x = tmp->bottom_right_x;
    int max_x = tmp->bottom_left_x;
    if (max_x < tmp->top_left_x) max_x = tmp->top_left_x;
    if (max_x < tmp->top_right_x) max_x = tmp->top_right_x;
    if (max_x < tmp->bottom_right_x) max_x = tmp->bottom_right_x;
    int min_y = tmp->bottom_left_y;
    if (min_y > tmp->top_left_y) min_y = tmp->top_left_y;
    if (min_y > tmp->top_right_y) min_y = tmp->top_right_y;
    if (min_y > tmp->bottom_right_y) min_y = tmp->bottom_right_y;
    int max_y = tmp->bottom_left_y;
    if (max_y < tmp->top_left_y) max_y = tmp->top_left_y;
    if (max_y < tmp->top_right_y) max_y = tmp->top_right_y;
    if (max_y < tmp->bottom_right_y) max_y = tmp->bottom_right_y;
    int width  = (max_x - min_x);
    int height = (max_y - min_y);
    log_info("size: %dx%d", width, height);
    if (contains_text_data(tmp->message)) {
      printf("Text message: ");
      for (unsigned int j = 0; j < tmp->message->n_bytes; j++) {
        u_int8_t c = tmp->message->bytes[j];
        if (c == '<')
          printf("&lt;");
        else if (c == '>')
          printf("&gt;");
        else
          printf("%c", c);
      }
    } else {
      printf("Binary message:");
      for (unsigned int j = 0; j < tmp->message->n_bytes; j++)
        printf(" %02x", tmp->message->bytes[j]);
    }
    tmp = tmp->next;
  }
  free_qr_code_match_list(matches);
  return(true);
} /* __qr_qrcode */

////////////////////////////////////////////
int qr_init(module(qr) *exports) {
  clib_module_init(qr, exports);
  exports->log_mode = QR_LOG_MODE_NONE;
  return(EXIT_SUCCESS);
}

void qr_deinit(module(qr) *exports) {
  clib_module_deinit(qr);
}

////////////////////////////////////////////
////////////////////////////////////////////
#endif
