#pragma once
#ifndef CACHE_C
#define CACHE_C
////////////////////////////////////////////

////////////////////////////////////////////
#include "cache/cache.h"
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
#include "iowow/iowow.h"
#include "iowow/iwkv.h"
#include "fs/fs.h"

////////////////////////////////////////////
static inline void  cache_info(char *message);
static inline void  cache_error(char *message);
static inline void  cache_debug(char *message);
static inline int   cache_GetPID();

////////////////////////////////////////////
void __cache_test(){
  char *p;
  asprintf(&p,"%s%s",require(fs)->tmpdir(),"cache-iowow");
  Ds(p);
  IWKV_OPTS opts = {
    .path   = p,
    .oflags = IWKV_TRUNC // Cleanup database before open
  };
  IWKV      iwkv;
  IWDB      mydb;
  iwrc      rc = iwkv_open(&opts, &iwkv);
    if (rc) {
    iwlog_ecode_error3(rc);
    exit(1);
  }
  rc = iwkv_db(iwkv, 1, 0, &mydb);
  if (rc) {
    iwlog_ecode_error2(rc, "Failed to open mydb");
    exit(1);
  }

  IWKV_val key, val;
  key.data = "foo";
  key.size = strlen(key.data);
  val.data = "bar";
  val.size = strlen(val.data);

  rc = iwkv_put(mydb, &key, &val, 0);
  if (rc) {
    iwlog_ecode_error3(rc);
    return(rc);
  }  

  // Retrieve value associated with `foo` key
  val.data = 0;
  val.size = 0;
  rc       = iwkv_get(mydb, &key, &val);
  if (rc) {
    iwlog_ecode_error3(rc);
    return(rc);
  }

  fprintf(stdout, "get: %.*s => %.*s\n",
          (int)key.size, (char *)key.data,
          (int)val.size, (char *)val.data);

  iwkv_val_dispose(&val);
  iwkv_close(&iwkv);  
}
int cache_init(module(cache) *exports) {
  clib_module_init(cache, exports);
  exports->pid      = getpid();
  exports->log_mode = CACHE_LOG_MODE_NONE;
  exports->info     = cache_info;
  exports->error    = cache_error;
  exports->debug    = cache_debug;
  return(EXIT_SUCCESS);
}

void cache_deinit(module(cache) *exports) {
  clib_module_deinit(cache);
}

////////////////////////////////////////////
static inline int cache_GetPID(){
  return(require(cache)->pid);
}

static inline void cache_info(char *message) {
  if (require(cache)->log_mode >= CACHE_LOG_MODE_INFO)
    fprintf(stdout, " info: %s\n", message);
}

static inline void cache_error(char *message) {
  if (require(cache)->log_mode >= CACHE_LOG_MODE_ERROR)
    fprintf(stderr, "error: %s\n", message);
}

static inline void cache_debug(char *message) {
  if (require(cache)->log_mode >= CACHE_LOG_MODE_DEBUG)
    fprintf(stderr, "debug: %s\n", message);
}
////////////////////////////////////////////
#endif
