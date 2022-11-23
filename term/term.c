#pragma once
#ifndef TERM_C
#define TERM_C
////////////////////////////////////////////

////////////////////////////////////////////
#include "term/term.h"
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
static inline void  term_info(char *message);
static inline void  term_error(char *message);
static inline void  term_debug(char *message);
static inline int   term_GetPID();

////////////////////////////////////////////
int term_init(module(term) *exports) {
  clib_module_init(term, exports);
  exports->pid      = getpid();
  exports->log_mode = TERM_LOG_MODE_NONE;
  exports->info     = term_info;
  exports->error    = term_error;
  exports->debug    = term_debug;
  return(EXIT_SUCCESS);
}

void term_deinit(module(term) *exports) {
  clib_module_deinit(term);
}

////////////////////////////////////////////
static inline int term_GetPID(){
  return(require(term)->pid);
}

static inline void term_info(char *message) {
  if (require(term)->log_mode >= TERM_LOG_MODE_INFO)
    fprintf(stdout, " info: %s\n", message);
}

static inline void term_error(char *message) {
  if (require(term)->log_mode >= TERM_LOG_MODE_ERROR)
    fprintf(stderr, "error: %s\n", message);
}

static inline void term_debug(char *message) {
  if (require(term)->log_mode >= TERM_LOG_MODE_DEBUG)
    fprintf(stderr, "debug: %s\n", message);
}
////////////////////////////////////////////
#endif
