#pragma once
#ifndef HL_C
#define HL_C
#define LOCAL_DEBUG_MODE    HL_DEBUG_MODE
////////////////////////////////////////////
#include "hl/hl.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "module/def.h"
#include "module/module.h"
#include "module/require.h"
#include "ms/ms.h"
#include "timestamp/timestamp.h"

////////////////////////////////////////////
static bool HL_DEBUG_MODE = false;
///////////////////////////////////////////////////////////////////////
static void __attribute__((constructor)) __constructor__hl(void){
  if (getenv("DEBUG") != NULL || getenv("DEBUG_hl") != NULL) {
    log_debug("Enabling hl Debug Mode");
    HL_DEBUG_MODE = true;
  }
}
////////////////////////////////////////////
#undef LOCAL_DEBUG_MODE
#endif
