#pragma once
#ifndef OPT_C
#define OPT_C
////////////////////////////////////////////
#include "opt/opt.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_eventemitter/include/eventemitter.h"
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
#include "optparse99/optparse99.h"
#include "tempdir.c/tempdir.h"
#include "timestamp/timestamp.h"
#include "which/src/which.h"

////////////////////////////////////////////

////////////////////////////////////////////
size_t __opt_option_qty(void){
  return(666);
}

size_t __opt_cmd_qty(void){
  return(667);
}

int opt_init(module(opt) *exports) {
  clib_module_init(opt, exports);
  exports->log_mode    = OPT_LOG_MODE_NONE;
  exports->cmd         = calloc(1, sizeof(module(opt_cmd)));
  exports->option      = calloc(1, sizeof(module(opt_option)));
  exports->config      = calloc(1, sizeof(module(opt_config)));
  exports->option->qty = __opt_option_qty;
  exports->cmd->qty    = __opt_cmd_qty;
  return(EXIT_SUCCESS);
}

void opt_deinit(module(opt) *exports) {
  free(exports->cmd);
  free(exports->option);
  free(exports->config);
  clib_module_deinit(opt);
}
////////////////////////////////////////////
#endif
