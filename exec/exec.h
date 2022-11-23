#pragma once
#ifndef EXEC_H
#define EXEC_H
//////////////////////////////////////
#include <assert.h>
#include <ctype.h>
#include <err.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//////////////////////////////////////
#include "module/def.h"
#include "module/module.h"
#include "module/require.h"
//////////////////////////////////////
module(exec) {
  define(exec, CLIB_MODULE);
  char *(*sh)(const char *cmd);
  char *(*exec)(const int argc, const char **argv);
  char *(*env)(const char *cmd);
};
int  exec_init(module(exec) * exports);
void exec_deinit(module(exec) * exports);
char *__exec_sh(const char *cmd);
char * __exec_exec(const int argc, const char **argv);
char * __exec_env(const char *cmd);
exports(exec) {
  .sh     = __exec_sh,
  .exec   = __exec_exec,
  .env    = __exec_env,
  .init   = exec_init,
  .deinit = exec_deinit,
};
#define exec_m    module(exec)
#endif
