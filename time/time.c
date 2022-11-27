#pragma once
#ifndef TIME_C
#define TIME_C
////////////////////////////////////////////

////////////////////////////////////////////
#include "time/time.h"
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

////////////////////////////////////////////
static inline void  time_info(char *message);
static inline void  time_error(char *message);
static inline void  time_debug(char *message);
static inline int   time_GetPID();

////////////////////////////////////////////
int time_init(module(time) *exports) {
  clib_module_init(time, exports);
  exports->pid      = getpid();
  exports->log_mode = TIME_LOG_MODE_NONE;
  exports->info     = time_info;
  exports->error    = time_error;
  exports->debug    = time_debug;
  return(EXIT_SUCCESS);
}

void time_deinit(module(time) *exports) {
  clib_module_deinit(time);
}

////////////////////////////////////////////
static inline int time_GetPID(){
  return(require(time)->pid);
}

static inline void time_info(char *message) {
  if (require(time)->log_mode >= TIME_LOG_MODE_INFO)
    fprintf(stdout, " info: %s\n", message);
}

static inline void time_error(char *message) {
  if (require(time)->log_mode >= TIME_LOG_MODE_ERROR)
    fprintf(stderr, "error: %s\n", message);
}

static inline void time_debug(char *message) {
  if (require(time)->log_mode >= TIME_LOG_MODE_DEBUG)
    fprintf(stderr, "debug: %s\n", message);
}
////////////////////////////////////////////
#endif
