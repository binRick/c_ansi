
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "ms/ms.h"
#include "proc-test/proc-test.h"
#include "proc/proc.h"
#include "timestamp/timestamp.h"
#include <libproc.h>
#include <sys/proc_info.h>
#include "module/def.h"
#include "module/module.h"
#include "module/require.h"

#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <utmpx.h>
#include <sys/sysctl.h>
#include <sys/vmmeter.h>
#include <libproc.h>
#include <sys/proc_info.h>
#include <netinet/tcp_fsm.h>
#include <arpa/inet.h>
#include <net/if_dl.h>
#include <pwd.h>
#include <mach/mach.h>
#include <mach/task.h>
#include <mach/mach_init.h>
#include <mach/host_info.h>
#include <mach/mach_host.h>
#include <mach/mach_traps.h>
#include <mach/mach_vm.h>
#include <mach/shared_memory_server.h>
#include <mach-o/loader.h>
#include <CoreFoundation/CoreFoundation.h>
#include <IOKit/IOKitLib.h>
#include <IOKit/storage/IOBlockStorageDriver.h>
#include <IOKit/storage/IOMedia.h>
#include <IOKit/IOBSD.h>


static pid_t pid;
static module(proc) *proc;

TEST t_proc_test_with_env_key_val(){
  char *s;
  size_t qty=0;
  const char *key="USER",*val="rick";
  pid_t *pids=proc->with_env_key_val(key,val,&qty);
  asprintf(&s,"%lu/%lu PIDs with env key %s and val %s",
      qty,
      require(proc)->qty(),
      key,val
      );
  free(pids);
  PASSm(s);
}
TEST t_proc_test_with_env_key(){
  char *s;
  size_t qty=0;
  const char *key="HOME";
  pid_t *pids=proc->with_env_key(key,&qty);
  asprintf(&s,"%lu PIDs with env key %s",qty,key);
  free(pids);
  PASSm(s);
}

TEST t_proc_test_pids(){
  char *s;
  size_t qty=0;
  pid_t *pids=proc->pids(&qty);
  asprintf(&s,"%lu PIDs",qty);
  free(pids);
  PASSm(s);
}
TEST t_proc_test_env(){
  char *s;
  struct Vector *env = proc->pid_env(pid);
  asprintf(&s,"PID %d %lu env vars", pid,vector_size(env));
  PASSm(s);
}
TEST t_proc_test_cmdline(){
  char *s;
  char *cmdline=proc->pid_cmdline(pid);
  asprintf(&s,"PID %d cmdline: %s", pid,cmdline);
  PASSm(s);
}
TEST t_proc_test_info(){
  char *s;
  struct kinfo_proc *info = proc->pid_info(pid);
  log_info("pid:%d",info->kp_proc.p_pid);
  log_info("ppid:%d",info->kp_eproc.e_ppid);
  PASS();
}

TEST t_proc_test_cwd(){
  char *path = proc->pid_cwd(pid);
  char *s;
  asprintf(&s,"PID %d path: %s", pid,path);
  PASSm(s);
}

SUITE(s_proc_test) {
  RUN_TEST(t_proc_test_cwd);
  RUN_TEST(t_proc_test_info);
  RUN_TEST(t_proc_test_cmdline);
  RUN_TEST(t_proc_test_env);
  RUN_TEST(t_proc_test_pids);
  RUN_TEST(t_proc_test_with_env_key);
  RUN_TEST(t_proc_test_with_env_key_val);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  pid = getpid();
  proc = require(proc);
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_proc_test);
  GREATEST_MAIN_END();
}
