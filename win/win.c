#pragma once
#ifndef WIN_C
#define WIN_C
////////////////////////////////////////////

////////////////////////////////////////////
#include "win/win.h"
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
static inline void  win_info(char *message);
static inline void  win_error(char *message);
static inline void  win_debug(char *message);
static inline int   win_GetPID();
static bool   __win_window_id_is_active(size_t window_id){
  log_info("is active..");
  return true;
}

////////////////////////////////////////////
int win_init(module(win) *exports) {
  clib_module_init(win, exports);
  exports->log_mode = WIN_LOG_MODE_NONE;
  exports->is->active=__win_window_id_is_active;
  return(EXIT_SUCCESS);
}

void win_deinit(module(win) *exports) {
  clib_module_deinit(win);
}

////////////////////////////////////////////
////////////////////////////////////////////
#endif
