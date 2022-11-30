#pragma once
#ifndef FOCUS_C
#define FOCUS_C
////////////////////////////////////////////
#include "focus/focus.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_eventemitter/include/eventemitter.h"
#include "c_focus/src/c_focus.h"
#include "c_fsio/include/fsio.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "chan/src/chan.h"
#include "chan/src/queue.h"
#include "incbin/incbin.h"
#include "log/log.h"
#include "module/def.h"
#include "module/module.h"
#include "module/require.h"
#include "ms/ms.h"
#include "tempdir.c/tempdir.h"
#include "timestamp/timestamp.h"
#include "which/src/which.h"
static char *log_path;

void __focus_log_path_handler(struct c_focus_event_t e){ 
  char *json;
  if(!(json=require(focus)->event.serialize(&e))){
    log_error("Failed to serialize event");
    return;
  }
  stringfn_mut_trim(json);
  asprintf(&json,"%s\n",json);
  if(json&&log_path)
    if(!fsio_append_text_file(log_path,json))
      log_error("Failed to append log event");
  if(json)
    free(json);
}

void __focus_log_path(const char *path){
  if(!path)return;
  log_path=path;
  require(focus)->callback(__focus_log_path_handler);
}

bool __focus_stop(void){
  log_info("stopping");
  return(true);
}

bool __focus_start_callback(c_focus_event_callback_t cb){
  log_info("start cb");
  return(true);
}

bool __focus_start_block(c_focus_event_block_t cb){
  log_info("start block");
  return(true);
}
////////////////////////////////////////////
int __focus_init(module(focus) *exports) {
  clib_module_init(focus, exports);
  return(EXIT_SUCCESS);
}

void __focus_deinit(module(focus) *exports) {
  clib_module_deinit(focus);
}
////////////////////////////////////////////
#endif
