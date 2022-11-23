#pragma once
#ifndef STR_C
#define STR_C
////////////////////////////////////////////

////////////////////////////////////////////
#include "str/str.h"
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
static inline void  str_info(char *message);
static inline void  str_error(char *message);
static inline void  str_debug(char *message);
static inline int   str_GetPID();

////////////////////////////////////////////
int str_init(module(str) *exports) {
  clib_module_init(str, exports);
  return(EXIT_SUCCESS);
}

void str_deinit(module(str) *exports) {
  clib_module_deinit(str);
}

////////////////////////////////////////////
////////////////////////////////////////////
#endif
