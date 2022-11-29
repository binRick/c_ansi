#pragma once
#ifndef TESSERACT_C
#define TESSERACT_C
////////////////////////////////////////////
#include "tesseract/capi.h"
////////////////////////////////////////////
#include "tess/tess.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "ms/ms.h"
#include "timestamp/timestamp.h"
struct tess_t {
  struct Pix  *img;
  TessBaseAPI *api;
};

void __tess_mem(const unsigned char *ptr, const size_t len){
  log_info("Loading %lu byte image", len);
}

////////////////////////////////////////////
static inline void  tess_info(char *message);
static inline void  tess_error(char *message);
static inline void  tess_debug(char *message);
static inline int   tess_GetPID();

////////////////////////////////////////////
int tess_init(module(tess) *exports) {
  clib_module_init(tess, exports);
  exports->pid       = getpid();
  exports->tess      = calloc(1, sizeof(struct tess_t));
  exports->tess->api = TessBaseAPICreate();
  if (!(TessBaseAPIInit3(exports->tess->api, NULL, "eng"))) {
    log_error("Failed to initialize tess API");
    return(EXIT_FAILURE);
  }
  exports->log_mode = TESSERACT_LOG_MODE_NONE;
  exports->info     = tess_info;
  exports->error    = tess_error;
  exports->debug    = tess_debug;
  return(EXIT_SUCCESS);
}

void tess_deinit(module(tess) *exports) {
//  pixDestroy(exports->tess->img);
  TessBaseAPIEnd(exports->tess->api);
  TessBaseAPIDelete(exports->tess->api);
  free(exports->tess);
  clib_module_deinit(tess);
}

////////////////////////////////////////////
static inline int tess_GetPID(){
  return(require(tess)->pid);
}

static inline void tess_info(char *message) {
  if (require(tess)->log_mode >= TESSERACT_LOG_MODE_INFO)
    fprintf(stdout, " info: %s\n", message);
}

static inline void tess_error(char *message) {
  if (require(tess)->log_mode >= TESSERACT_LOG_MODE_ERROR)
    fprintf(stderr, "error: %s\n", message);
}

static inline void tess_debug(char *message) {
  if (require(tess)->log_mode >= TESSERACT_LOG_MODE_DEBUG)
    fprintf(stderr, "debug: %s\n", message);
}
////////////////////////////////////////////
#endif
