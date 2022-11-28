#pragma once
#ifndef OPT_H
#define OPT_H
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
#include "optparse99/optparse99.h"
//////////////////////////////////////
#include "module/def.h"
#include "module/module.h"
#include "module/require.h"
//////////////////////////////////////
enum opt_log_mode_t {
  OPT_LOG_MODE_NONE = 1,
  OPT_LOG_MODE_ERROR,
  OPT_LOG_MODE_INFO,
  OPT_LOG_MODE_DEBUG,
  OPT_LOG_MODES_QTY,
};

module(opt) {
  define(opt, CLIB_MODULE);
  enum opt_log_mode_t log_mode;
  module(opt_cmd) {
    size_t (*qty)(void);
    bool (*add)(struct optparse_cmd *cmd);
  } *cmd;
  module(opt_config) {
    char *name, *description, *about;
  } *config;
  module(opt_option) {
    size_t (*qty)(void);
    bool (*add)(struct optparse_opt *option);
  } *option;
};

int opt_init(module(opt) *exports);
void opt_deinit(module(opt) *exports);
void __opt_test(void);
size_t __opt_option_qty(void);
size_t __opt_cmd_qty(void);
bool __opt_cmd_add(struct optparse_cmd *cmd);
bool __opt_option_add(struct optparse_opt *cmd);

exports(opt) {
  .log_mode = OPT_LOG_MODE_NONE,
  .init     = opt_init,
  .deinit   = opt_deinit,
};

#define opt_m    module(opt)

#endif
