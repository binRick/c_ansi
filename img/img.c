#pragma once
#ifndef IMG_C
#define IMG_C
////////////////////////////////////////////

////////////////////////////////////////////
#include "img/img.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "ms/ms.h"
#include "qoi/qoi.h"
#include "qoir/src/qoir.h"
#include "timestamp/timestamp.h"
////////////////////////////////////////////
static inline void  img_info(char *message);
static inline void  img_error(char *message);
static inline void  img_debug(char *message);
static inline int   img_GetPID();

////////////////////////////////////////////
int img_init(module(img) *exports) {
  clib_module_init(img, exports);
  exports->pid      = getpid();
  exports->log_mode = IMG_LOG_MODE_NONE;
  exports->info     = img_info;
  exports->error    = img_error;
  exports->debug    = img_debug;
  return(EXIT_SUCCESS);
}

void img_deinit(module(img) *exports) {
  clib_module_deinit(img);
}

////////////////////////////////////////////
static inline int img_GetPID(){
  return(require(img)->pid);
}

static inline void img_info(char *message) {
  if (require(img)->log_mode >= IMG_LOG_MODE_INFO)
    fprintf(stdout, " info: %s\n", message);
}

static inline void img_error(char *message) {
  if (require(img)->log_mode >= IMG_LOG_MODE_ERROR)
    fprintf(stderr, "error: %s\n", message);
}

static inline void img_debug(char *message) {
  if (require(img)->log_mode >= IMG_LOG_MODE_DEBUG)
    fprintf(stderr, "debug: %s\n", message);
}
////////////////////////////////////////////
#endif
