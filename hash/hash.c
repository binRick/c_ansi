#pragma once
#ifndef HASH_C
#define HASH_C
////////////////////////////////////////////

////////////////////////////////////////////
#include "hash/hash.h"
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
static inline void  hash_info(char *message);
static inline void  hash_error(char *message);
static inline void  hash_debug(char *message);
static inline int   hash_GetPID();

////////////////////////////////////////////
int hash_init(module(hash) *exports) {
  clib_module_init(hash, exports);
  exports->pid      = getpid();
  exports->log_mode = HASH_LOG_MODE_NONE;
  exports->info     = hash_info;
  exports->error    = hash_error;
  exports->debug    = hash_debug;
  return(EXIT_SUCCESS);
}

void hash_deinit(module(hash) *exports) {
  clib_module_deinit(hash);
}

////////////////////////////////////////////
static inline int hash_GetPID(){
  return(require(hash)->pid);
}

static inline void hash_info(char *message) {
  if (require(hash)->log_mode >= HASH_LOG_MODE_INFO)
    fprintf(stdout, " info: %s\n", message);
}

static inline void hash_error(char *message) {
  if (require(hash)->log_mode >= HASH_LOG_MODE_ERROR)
    fprintf(stderr, "error: %s\n", message);
}

static inline void hash_debug(char *message) {
  if (require(hash)->log_mode >= HASH_LOG_MODE_DEBUG)
    fprintf(stderr, "debug: %s\n", message);
}
////////////////////////////////////////////
#endif
