#pragma once
#ifndef TS_C
#define TS_C
////////////////////////////////////////////

////////////////////////////////////////////
#include "ts/ts.h"
#include <sys/time.h>
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "ms/ms.h"
////////////////////////////////////////////
static inline void  ts_info(char *message);
static inline void  ts_error(char *message);
static inline void  ts_debug(char *message);
static inline int   ts_GetPID();

unsigned long __ts_ms(void){
  struct timeval tv;
  int            ret = gettimeofday(&tv, NULL);

  if (-1 == ret) return(-1);

  return((unsigned long)((int64_t)tv.tv_sec * 1000 + (int64_t)tv.tv_usec / 1000));
}

unsigned long __ts_ts(void){
  return(__ts_ms() / 1000);
}

////////////////////////////////////////////
int ts_init(module(ts) *exports) {
  clib_module_init(ts, exports);
  exports->pid      = getpid();
  exports->log_mode = TS_LOG_MODE_NONE;
  exports->info     = ts_info;
  exports->error    = ts_error;
  exports->debug    = ts_debug;
  return(EXIT_SUCCESS);
}

void ts_deinit(module(ts) *exports) {
  clib_module_deinit(ts);
}

////////////////////////////////////////////
static inline int ts_GetPID(){
  return(require(ts)->pid);
}

static inline void ts_info(char *message) {
  if (require(ts)->log_mode >= TS_LOG_MODE_INFO)
    fprintf(stdout, " info: %s\n", message);
}

static inline void ts_error(char *message) {
  if (require(ts)->log_mode >= TS_LOG_MODE_ERROR)
    fprintf(stderr, "error: %s\n", message);
}

static inline void ts_debug(char *message) {
  if (require(ts)->log_mode >= TS_LOG_MODE_DEBUG)
    fprintf(stderr, "debug: %s\n", message);
}
////////////////////////////////////////////
#endif
