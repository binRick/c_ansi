#pragma once
#ifndef EXEC_C
#define EXEC_C
////////////////////////////////////////////

////////////////////////////////////////////
#include "exec/exec.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "fs/fs.h"
#include "log/log.h"
#include "ms/ms.h"
#include "reproc/reproc/include/reproc/drain.h"
#include "reproc/reproc/include/reproc/export.h"
#include "reproc/reproc/include/reproc/reproc.h"
#include "str/str.h"
#include "subprocess.h/subprocess.h"
#include "timestamp/timestamp.h"
#include "which/src/which.h"

////////////////////////////////////////////
void __xxxxxx(const char *cmd){
}

char * __exec_exec(const int argc, const char **argv){
  return(0);
}

char * __exec_env(const char *cmd){
  return(0);
}

char *__exec_sh(const char *cmd){
  char        *output = NULL, *errout = NULL;
  reproc_sink sink            = reproc_sink_string(&output);
  reproc_sink sink_err        = reproc_sink_string(&errout);
  const char  *command_line[] = { which("sh"), "--norc", "--noprofile", "-c", cmd, NULL };
  reproc_t    *process        = NULL;
  int         r               = REPROC_ENOMEM;
  int         ec              = 0;

  errno = 0;
  if (!(process = reproc_new())) {
    ec = 100;
    goto finish;
  }
  errno = 0;
  if ((r = reproc_start(process, command_line, (reproc_options){
    .redirect.parent = false,
    .deadline = 15000,
  })
       ) < 0) {
    ec = 200;
    goto finish;
  }
  errno = 0;
  r     = reproc_drain(process, sink, sink_err);
  errno = 0;
  if ((r = reproc_wait(process, REPROC_INFINITE)) < 0) {
    ec = 300;
    goto finish;
  }
finish:
  reproc_destroy(process);
  if (r < 0) {
    log_error(AC_RED "Error Code: %d" AC_RESETALL "\n", ec);
    log_error(AC_RED "%d" AC_RESETALL "\n", r);
    log_error(AC_RED "%s" AC_RESETALL "\n", reproc_strerror(r));
  }
  if (strlen(errout) > 0)
    log_error(AC_RED "%s" AC_RESETALL "\n", errout);

  return(require(str)->trim(output));
} /* __exec_sh */

////////////////////////////////////////////
int exec_init(module(exec) *exports) {
  clib_module_init(exec, exports);
  return(EXIT_SUCCESS);
}

void exec_deinit(module(exec) *exports) {
  clib_module_deinit(exec);
}

////////////////////////////////////////////
////////////////////////////////////////////
#endif
