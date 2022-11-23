#pragma once
#ifndef ANSI_C
#define ANSI_C
#define LOCAL_DEBUG_MODE    ANSI_DEBUG_MODE
////////////////////////////////////////////
#include "ansi/ansi.h"
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
static bool ANSI_DEBUG_MODE = false;
///////////////////////////////////////////////////////////////////////
static void __attribute__((constructor)) __constructor__ansi(void){
  if (getenv("DEBUG") != NULL || getenv("DEBUG_ansi") != NULL) {
    log_debug("Enabling ansi Debug Mode");
    ANSI_DEBUG_MODE = true;
  }
}
////////////////////////////////////////////
int
ansi_init(module(ansi) *exports) {
  clib_module_init(ansi, exports);
  return 0;
}

void
ansi_deinit(module(ansi) *exports) {
  clib_module_deinit(ansi);
}
#undef LOCAL_DEBUG_MODE
#endif
