#pragma once
#ifndef PROC_C
#define PROC_C
////////////////////////////////////////////

////////////////////////////////////////////
#include "proc/proc.h"
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
#include <libproc.h>
#include <CoreFoundation/CoreFoundation.h>
#include <dlfcn.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/sysctl.h>
#include <sys/time.h>
#include <sys/proc_info.h>
#include <mach/mach.h>
#include <mach/mach_vm.h>
#include <sys/types.h>
#include <sys/proc_info.h>

#include <mach/mach.h>
#include <mach/task.h>
#include <mach/mach_init.h>
#include <mach/host_info.h>
#include <mach/mach_host.h>
#include <mach/mach_traps.h>
#include <CoreFoundation/CoreFoundation.h>
#include <IOKit/IOKitLib.h>
#include <IOKit/storage/IOBlockStorageDriver.h>
#include <IOKit/storage/IOMedia.h>
#include <Carbon/Carbon.h>
#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFString.h>
#include <CoreFoundation/CoreFoundation.h>
#include <CoreServices/CoreServices.h>
#include <sys/proc_info.h>
#include <sys/sysctl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <IOKit/ps/IOPowerSources.h>
#include <IOKit/ps/IOPSKeys.h>
#include <libproc.h>
#include <sys/resource.h>
#include <Carbon/Carbon.h>
#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFString.h>
#include <CoreFoundation/CoreFoundation.h>
#include <CoreServices/CoreServices.h>
#include <IOKit/ps/IOPSKeys.h>
#include <IOKit/ps/IOPowerSources.h>
#include <assert.h>
#include <ctype.h>
#include <dirent.h>
#include <dlfcn.h>
#include <errno.h>
#include <fnmatch.h>
#include <getopt.h>
#include <inttypes.h>
#include <libgen.h>
#include <libproc.h>
#include <mach/mach_time.h>
#include <pthread.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/proc_info.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/sysctl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>
//#include <ApplicationServices/ApplicationServices.h>

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/types.h>
#include <mach/bootstrap.h>
#include <mach/host_priv.h>
#include <mach/mach_error.h>
#include <mach/mach_host.h>
#include <device/device_types.h>
#include <CoreFoundation/CoreFoundation.h>
#include <IOKit/IOKitLib.h>
#include <IOKit/storage/IOBlockStorageDriver.h>

#include <libproc.h>

#include <fcntl.h>
#include <nlist.h>
#include <sys/param.h>
#include <sys/sysctl.h>
#include <pwd.h>

#include <sys/resource.h>

#include <sys/socket.h>
#include <net/if.h>
#include <net/route.h>
#include <net/if_types.h>
#include <ifaddrs.h>
#include <mach/mach_port.h>
#include <mach/mach_vm.h>
#include <mach/mach_types.h>
#include <mach/message.h>
#include <mach/processor_set.h>
#include <mach/task.h>
#include <mach/thread_act.h>
#include <mach/shared_region.h>
#include <mach/vm_map.h>
#include <sys/sysctl.h>
#include <stdio.h>
#include <stdlib.h>
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
#include <mach-o/loader.h>
#include <CoreFoundation/CoreFoundation.h>
#include <IOKit/IOKitLib.h>
#include <IOKit/storage/IOBlockStorageDriver.h>
#include <IOKit/storage/IOMedia.h>
#include <IOKit/IOBSD.h>
struct process_env_t {
  char *key;
  char *val;
};
////////////////////////////////////////////
static inline void  proc_info(char *message);
static inline void  proc_error(char *message);
static inline void  proc_debug(char *message);
static inline int   proc_GetPID();


static int __proc_argmax() {
  int    argmax, mib[] = { CTL_KERN, KERN_ARGMAX };
  size_t size = sizeof(argmax);

  if (sysctl(mib, 2, &argmax, &size, NULL, 0) == 0)
    return(argmax);

  return(0);
}

char *__proc_pid_cmdline(pid_t pid){
  struct StringBuffer *sb = stringbuffer_new();
  int           mib[3], nargs;
  char          *procargs = NULL, *arg_ptr, *arg_end, *curr_arg;
  size_t        len, argmax;

  if (pid < 1)
    return(NULL);

  argmax = __proc_argmax();
  if (!argmax)
    return(NULL);

  procargs = (char *)malloc(argmax);
  if (procargs == NULL)
    return(NULL);

  mib[0] = CTL_KERN;
  mib[1] = KERN_PROCARGS2;
  mib[2] = (pid_t)pid;
  if (sysctl(mib, 3, procargs, &argmax, NULL, 0) < 0) {
    free(procargs);
    return(NULL);
  }

  arg_end = &procargs[argmax];
  memcpy(&nargs, procargs, sizeof(nargs));
  arg_ptr  = procargs + sizeof(nargs);
  len      = strlen(arg_ptr);
  arg_ptr += len + 1;
  if (arg_ptr == arg_end) {
    free(procargs);
    return(NULL);
  }

  for ( ; arg_ptr < arg_end; arg_ptr++)
    if (*arg_ptr != '\0')
      break;

  curr_arg = arg_ptr;
  while (arg_ptr < arg_end && nargs > 0)
    if (*arg_ptr++ == '\0') {
      stringbuffer_append_string(sb," ");
      stringbuffer_append_string(sb,curr_arg);
      curr_arg = arg_ptr;
      nargs--;
    }
  if (procargs)
    free(procargs);
  char *s = stringbuffer_to_string(sb);
  stringbuffer_release(sb);
  return(s);
}

struct kinfo_proc *__proc_pid_info(pid_t pid){
  struct kinfo_proc *kp = calloc(1,sizeof(struct kinfo_proc));
    int mib[4];
    size_t len;
    mib[0] = CTL_KERN;
    mib[1] = KERN_PROC;
    mib[2] = KERN_PROC_PID;
    mib[3] = pid;
    len = sizeof(struct kinfo_proc);
    errno=0;
    if (sysctl(mib, 4, kp, &len, NULL, 0) == -1) {
      log_error("failed to fetch pid info");
      return 0;
    }
    if (len == 0) {
        errno = ESRCH;
        return 0;
    }
    return kp;
}

pid_t *__proc_pids_with_env_key_val(const char *key,const char *val,size_t *qty){
  size_t q=0;
  struct Vector *v=vector_new();
  struct  process_env_t *e;
  pid_t *pids=__proc_pids(&q);
  for(size_t i=0;i<q;i++){
    struct Vector *env=__proc_pid_env(pids[i]);
    for(size_t ii=0;ii< vector_size(env);ii++){
      e=(struct process_env_t*)vector_get(env,ii);
      if(e && stringfn_equal(key,e->key) && stringfn_equal(val,e->val)){
        vector_push(v,(void*)(size_t)pids[i]);
      }
      if(e)
        free(e);
    }
    vector_release(env);
  }
  *qty=vector_size(v);
  pids=(pid_t*)vector_to_array(v);
  vector_release(v);
  return(pids);
}
pid_t *__proc_pids_with_env_key(const char *key,size_t *qty){
  size_t q=0;
  struct Vector *v=vector_new();
  struct process_env_t *e;
  struct Vector *env;
  pid_t *pids=__proc_pids(&q);
  for(size_t i=0;i<q;i++){
    env =__proc_pid_env(pids[i]);
    for(size_t ii=0;ii< vector_size(env);ii++){
      if((e=(struct process_env_t*)vector_get(env,ii)) && stringfn_equal(key,e->key))
        vector_push(v,(void*)(size_t)pids[i]);
      if(e)
        free(e);
    }
    vector_release(env);
  }
  *qty=vector_size(v);
  pids=(pid_t*)vector_to_array(v);
  vector_release(v);
  return(pids);
}
size_t __proc_pids_qty(){
  size_t qty=0;
  pid_t *p=__proc_pids(&qty);
  free(p);
  return(qty);
}

pid_t *__proc_pids(size_t *qty){
  struct Vector *processes_v      = vector_new();
  pid_t         num               = proc_listallpids(NULL, 0);
  size_t        processes_len     = sizeof(pid_t) * num * 2;
  pid_t         *processes_buffer = malloc(processes_len);
  size_t        processes_qty     = proc_listallpids(processes_buffer, processes_len);

  for (size_t i = 0; i < processes_qty; i++)
    if ((long long)processes_buffer[i] > 0)
      vector_push(processes_v, (void *)(long long)processes_buffer[i]);
  free(processes_buffer);
  *qty=vector_size(processes_v);

  pid_t *pids=calloc(*qty,sizeof(pid_t));
  for(size_t i=0;i<*qty;i++)
    pids[i]=(pid_t)(size_t)vector_get(processes_v,i);
  
  return(pids);
}

struct Vector *__proc_pid_env(pid_t pid){
  struct Vector *process_env_v = vector_new();

  if (pid <= 1)
    return(process_env_v);

  struct Vector          *vector = vector_new();
  struct StringFNStrings EnvSplit;
  int                    env_res = -1, nargs;
  char                   *procenv = NULL, *procargs, *arg_ptr, *arg_end, *env_start, *s;
  size_t                 argmax;
  int                    mib[3];

  argmax   = __proc_argmax();
  procargs = (char *)malloc(argmax);
  mib[0]   = CTL_KERN;
  mib[1]   = KERN_PROCARGS2;
  mib[2]   = (pid_t)pid;
  if (sysctl(mib, 3, procargs, &argmax, NULL, 0) == 0) {
    arg_end = &procargs[argmax];
    memcpy(&nargs, procargs, sizeof(nargs));
    arg_ptr = procargs + sizeof(nargs);
    arg_ptr = memchr(arg_ptr, '\0', arg_end - arg_ptr);

    for ( ; arg_ptr < arg_end; arg_ptr++)
      if (*arg_ptr != '\0')
        break;
    while (arg_ptr < arg_end && nargs > 0)
      if (*arg_ptr++ == '\0')
        nargs--;
    env_start = arg_ptr;
    procenv   = calloc(1, arg_end - arg_ptr);

    while (*arg_ptr != '\0' && arg_ptr < arg_end) {
      s = memchr(arg_ptr + 1, '\0', arg_end - arg_ptr);
      if (s == NULL)
        break;
      memcpy(procenv + (arg_ptr - env_start), arg_ptr, s - arg_ptr);
      arg_ptr = s + 1;
      if (strlen(arg_ptr) < 3)
        continue;
      EnvSplit = stringfn_split(arg_ptr, '=');
      if (EnvSplit.count > 1)
        vector_push(vector, arg_ptr);
    }

    for (size_t i = 0; i < vector_size(vector); i++) {
      EnvSplit = stringfn_split(vector_get(vector, i), '=');
      struct process_env_t *pe = malloc(sizeof(struct process_env_t));
      pe->key = strdup(EnvSplit.strings[0]);
      pe->val = strdup(stringfn_join(EnvSplit.strings, "=", 1, EnvSplit.count - 1));
      if (false)
        fprintf(stderr,
                AC_RESETALL AC_BLUE "%s=>%s\n" AC_RESETALL, pe->key, pe->val);
      vector_push(process_env_v, pe);
    }
    if (procargs != NULL)
      free(procargs);
    if (procenv != NULL)
      free(procenv);
    if (vector_size(vector) > 0)
      stringfn_release_strings_struct(EnvSplit);
    vector_release(vector);
  }
  return(process_env_v);
}


static int GetBSDProcessList(struct kinfo_proc **procList, size_t *procCount){
    int                 err;
    struct kinfo_proc *        result;
    bool                done;
    static const int    name[] = { CTL_KERN, KERN_PROC, KERN_PROC_ALL, 0 };
    size_t              length;
    assert( procList != NULL);
    assert(*procList == NULL);
    assert(procCount != NULL);

    *procCount = 0;

    result = NULL;
    done = false;
    do {
        assert(result == NULL);

        // Call sysctl with a NULL buffer.

        length = 0;
        err = sysctl( (int *) name, (sizeof(name) / sizeof(*name)) - 1,
                      NULL, &length,
                      NULL, 0);
        if (err == -1) {
            err = errno;
        }

        // Allocate an appropriately sized buffer based on the results
        // from the previous call.

        if (err == 0) {
            result = malloc(length);
            if (result == NULL) {
                err = ENOMEM;
            }
        }

        // Call sysctl again with the new buffer.  If we get an ENOMEM
        // error, toss away our buffer and start again.

        if (err == 0) {
            err = sysctl( (int *) name, (sizeof(name) / sizeof(*name)) - 1,
                          result, &length,
                          NULL, 0);
            if (err == -1) {
                err = errno;
            }
            if (err == 0) {
                done = true;
            } else if (err == ENOMEM) {
                assert(result != NULL);
                free(result);
                result = NULL;
                err = 0;
            }
        }
    } while (err == 0 && ! done);

    // Clean up and establish post conditions.

    if (err != 0 && result != NULL) {
        free(result);
        result = NULL;
    }
    *procList = result;
    if (err == 0) {
        *procCount = length / sizeof(struct kinfo_proc);
    }

    assert( (err == 0) == (*procList != NULL) );

    return err;
}
pid_t __proc_pid_ppid(pid_t pid){
  struct kinfo_proc kp;
  return((int)(long)kp.kp_eproc.e_ppid);
}
char *__proc_pid_cwd(pid_t pid){
  char                      *cwd = NULL;
  struct proc_vnodepathinfo vpi;
  proc_pidinfo(pid, PROC_PIDVNODEPATHINFO, 0, &vpi, sizeof(vpi));
  if (strlen(vpi.pvi_cdir.vip_path) > 0)
    cwd = strdup(vpi.pvi_cdir.vip_path);
  return(cwd);
}
////////////////////////////////////////////
int proc_init(module(proc) *exports) {
  clib_module_init(proc, exports);
  exports->pid      = getpid();
  exports->log_mode = PROC_LOG_MODE_NONE;
  exports->info     = proc_info;
  exports->error    = proc_error;
  exports->debug    = proc_debug;
  return(EXIT_SUCCESS);
}

void proc_deinit(module(proc) *exports) {
  clib_module_deinit(proc);
}

////////////////////////////////////////////
static inline int proc_GetPID(){
  return(require(proc)->pid);
}

static inline void proc_info(char *message) {
  if (require(proc)->log_mode >= PROC_LOG_MODE_INFO)
    fprintf(stdout, " info: %s\n", message);
}

static inline void proc_error(char *message) {
  if (require(proc)->log_mode >= PROC_LOG_MODE_ERROR)
    fprintf(stderr, "error: %s\n", message);
}

static inline void proc_debug(char *message) {
  if (require(proc)->log_mode >= PROC_LOG_MODE_DEBUG)
    fprintf(stderr, "debug: %s\n", message);
}
////////////////////////////////////////////
#endif
