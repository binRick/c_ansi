#pragma once
#ifndef ENV_C
#define ENV_C
////////////////////////////////////////////

////////////////////////////////////////////
#include "env/env.h"
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
static inline void  env_info(char *message);
static inline void  env_error(char *message);
static inline void  env_debug(char *message);
static inline int   env_GetPID();

////////////////////////////////////////////
int env_init(module(env) *exports) {
  clib_module_init(env, exports);
  exports->pid      = getpid();
  exports->log_mode = ENV_LOG_MODE_NONE;
  exports->info     = env_info;
  exports->error    = env_error;
  exports->debug    = env_debug;
  return(EXIT_SUCCESS);
}

void env_deinit(module(env) *exports) {
  clib_module_deinit(env);
}

////////////////////////////////////////////
static inline int env_GetPID(){
  return(require(env)->pid);
}

static inline void env_info(char *message) {
  if (require(env)->log_mode >= ENV_LOG_MODE_INFO)
    fprintf(stdout, " info: %s\n", message);
}

static inline void env_error(char *message) {
  if (require(env)->log_mode >= ENV_LOG_MODE_ERROR)
    fprintf(stderr, "error: %s\n", message);
}

static inline void env_debug(char *message) {
  if (require(env)->log_mode >= ENV_LOG_MODE_DEBUG)
    fprintf(stderr, "debug: %s\n", message);
}
////////////////////////////////////////////
#endif
