#pragma once
#ifndef QOIR_C
#define QOIR_C
////////////////////////////////////////////

////////////////////////////////////////////
#include "qoir/qoir.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "ms/ms.h"
#include "qoir/src/qoir.h"
#include "timestamp/timestamp.h"

////////////////////////////////////////////
static inline void  qoir_info(char *message);
static inline void  qoir_error(char *message);
static inline void  qoir_debug(char *message);
static inline int   qoir_GetPID();

////////////////////////////////////////////
int qoir_init(module(qoir) *exports) {
  clib_module_init(qoir, exports);
  exports->pid      = getpid();
  exports->log_mode = QOIR_LOG_MODE_NONE;
  return(EXIT_SUCCESS);
}

void qoir_deinit(module(qoir) *exports) {
  clib_module_deinit(qoir);
}

////////////////////////////////////////////
static inline int qoir_GetPID(){
  return(require(qoir)->pid);
}

qoir_decode_result __qoir_decode_path(const char *path){
  log_info("decoding %s", path);
  unsigned char *dat = fsio_read_binary_file(path);
  size_t        len  = fsio_file_size(path);
  return(require(qoir)->decode(dat, len));
}

qoir_decode_result __qoir_decode(const unsigned char *dat, size_t len){
  log_info("decoding %lu bytes", len);
  qoir_decode_options options = { 0 };
  return(qoir_decode(dat, len, &options));
}

////////////////////////////////////////////
#endif
