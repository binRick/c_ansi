#pragma once
#ifndef KITTY_C
#define KITTY_C
////////////////////////////////////////////

////////////////////////////////////////////
#include "kitty/kitty.h"
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
static inline void  kitty_info(char *message);
static inline void  kitty_error(char *message);
static inline void  kitty_debug(char *message);
static inline int   kitty_GetPID();

////////////////////////////////////////////
int kitty_init(module(kitty) *exports) {
  clib_module_init(kitty, exports);
  exports->pid      = getpid();
  exports->log_mode = KITTY_LOG_MODE_NONE;
  exports->info     = kitty_info;
  exports->error    = kitty_error;
  exports->debug    = kitty_debug;
  return(EXIT_SUCCESS);
}

void kitty_deinit(module(kitty) *exports) {
  clib_module_deinit(kitty);
}

////////////////////////////////////////////
static inline int kitty_GetPID(){
  return(require(kitty)->pid);
}

static inline void kitty_info(char *message) {
  if (require(kitty)->log_mode >= KITTY_LOG_MODE_INFO)
    fprintf(stdout, " info: %s\n", message);
}

static inline void kitty_error(char *message) {
  if (require(kitty)->log_mode >= KITTY_LOG_MODE_ERROR)
    fprintf(stderr, "error: %s\n", message);
}

static inline void kitty_debug(char *message) {
  if (require(kitty)->log_mode >= KITTY_LOG_MODE_DEBUG)
    fprintf(stderr, "debug: %s\n", message);
}
////////////////////////////////////////////
#endif
