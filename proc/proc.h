#pragma once
#ifndef PROC_H
#define PROC_H
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
enum proc_log_mode_t {
  PROC_LOG_MODE_NONE = 1,
  PROC_LOG_MODE_ERROR,
  PROC_LOG_MODE_INFO,
  PROC_LOG_MODE_DEBUG,
  PROC_LOG_MODES_QTY,
};

module(proc) {
  define(proc, CLIB_MODULE);

  enum proc_log_mode_t log_mode;
  int                  pid;

  int                  (*GetPID)();
  void                 (*info)(char *);
  void                 (*debug)(char *);
  void                 (*error)(char *);
  char                 *(*pid_cwd)(pid_t pid);
  pid_t                (*pid_ppid)(pid_t pid);
  char                 *(*pid_cmdline)(pid_t pid);
  struct kinfo_proc    *(*pid_info)(pid_t pid);
  struct Vector        *(*pid_env)(pid_t pid);
  pid_t                *(*pids)(size_t *qty);
  pid_t                *(*with_env_key)(const char *key, size_t *qty);
  pid_t                *(*with_env_key_val)(const char *key, const char *val, size_t *qty);
  size_t               (*qty)(void);
};

int  proc_init(module(proc) * exports);
void proc_deinit(module(proc) * exports);
char *__proc_pid_cmdline(pid_t pid);
char *__proc_pid_cwd(pid_t pid);
pid_t __proc_pid_ppid(pid_t pid);
pid_t *__proc_pids(size_t *qty);
struct kinfo_proc *__proc_pid_info(pid_t pid);
struct Vector *__proc_pid_env(int process);
pid_t *__proc_pids_with_env_key(const char *key, size_t *qty);
pid_t *__proc_pids_with_env_key_val(const char *key, const char *val, size_t *qty);
size_t __proc_pids_qty(void);

exports(proc) {
  .log_mode         = PROC_LOG_MODE_NONE,
  .init             = proc_init,
  .qty              = __proc_pids_qty,
  .pids             = __proc_pids,
  .with_env_key     = __proc_pids_with_env_key,
  .with_env_key_val = __proc_pids_with_env_key_val,
  .deinit           = proc_deinit,
  .pid_cwd          = __proc_pid_cwd,
  .pid_ppid         = __proc_pid_ppid,
  .pid_info         = __proc_pid_info,
  .pid_cmdline      = __proc_pid_cmdline,
  .pid_env          = __proc_pid_env,
  .pid              = -1,
};

#define proc_m    module(proc)

#endif
