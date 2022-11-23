#pragma once
#ifndef VIEW_C
#define VIEW_C
#define LOCAL_DEBUG_MODE    VIEW_DEBUG_MODE
////////////////////////////////////////////
#include "view/view.h"
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
static bool VIEW_DEBUG_MODE = false;
///////////////////////////////////////////////////////////////////////
static void __attribute__((constructor)) __constructor__view(void){
  if (getenv("DEBUG") != NULL || getenv("DEBUG_view") != NULL) {
    log_debug("Enabling view Debug Mode");
    VIEW_DEBUG_MODE = true;
  }
}
////////////////////////////////////////////
#undef LOCAL_DEBUG_MODE
#endif
