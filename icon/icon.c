#pragma once
#ifndef ICON_C
#define ICON_C
////////////////////////////////////////////

////////////////////////////////////////////
#include "icon/icon.h"
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
#include "string-utils/string-utils.h"
#include <CoreVideo/CVPixelBuffer.h>

////////////////////////////////////////////
static inline void  icon_info(char *message);
static inline void  icon_error(char *message);
static inline void  icon_debug(char *message);
static inline int   icon_GetPID();

CFDataRef copyIconDataForURL(CFURLRef URL){
  CFDataRef data = NULL;
  if (URL) {
    FSRef ref;
    if (CFURLGetFSRef(URL, &ref)) {
      IconRef  icon = NULL;
      SInt16   label_noOneCares;
      OSStatus err = GetIconRefFromFileInfo(&ref,
                                            /*inFileNameLength*/ 0U, /*inFileName*/ NULL,
                                            kFSCatInfoNone, /*inCatalogInfo*/ NULL,
                                            kIconServicesNoBadgeFlag | kIconServicesUpdateIfNeededFlag,
                                            &icon,
                                            &label_noOneCares);
      if (err == noErr) {
        IconFamilyHandle fam = NULL;
        err = IconRefToIconFamily(icon, kSelectorAllAvailableData, &fam);
        if (err != noErr) {
        } else {
          HLock((Handle)fam);
          data = CFDataCreate(kCFAllocatorDefault, (const UInt8 *)*(Handle)fam, GetHandleSize((Handle)fam));
          HUnlock((Handle)fam);
          DisposeHandle((Handle)fam);
        }
        ReleaseIconRef(icon);
      }
    }
  }
  return(data);
}

CFDataRef copyIconDataForPath(CFStringRef path) {
  CFDataRef data = NULL;
  CFURLRef  URL  = CFURLCreateWithFileSystemPath(kCFAllocatorDefault, path, kCFURLPOSIXPathStyle, false);

  if (URL) {
    data = copyIconDataForURL(URL);
    CFRelease(URL);
  }
  return(data);
}

static CFDataRef __icon_from_path(char *path) {
  return(copyIconDataForPath(cfstring_from_cstring(path)));
}
////////////////////////////////////////////
int icon_init(module(icon) *exports) {
  clib_module_init(icon, exports);
  exports->pid      = getpid();
  exports->log_mode = ICON_LOG_MODE_NONE;
  exports->info     = icon_info;
  exports->error    = icon_error;
  exports->debug    = icon_debug;
  return(EXIT_SUCCESS);
}

void icon_deinit(module(icon) *exports) {
  clib_module_deinit(icon);
}

////////////////////////////////////////////
static inline int icon_GetPID(){
  return(require(icon)->pid);
}

static inline void icon_info(char *message) {
  if (require(icon)->log_mode >= ICON_LOG_MODE_INFO)
    fprintf(stdout, " info: %s\n", message);
}

static inline void icon_error(char *message) {
  if (require(icon)->log_mode >= ICON_LOG_MODE_ERROR)
    fprintf(stderr, "error: %s\n", message);
}

static inline void icon_debug(char *message) {
  if (require(icon)->log_mode >= ICON_LOG_MODE_DEBUG)
    fprintf(stderr, "debug: %s\n", message);
}
////////////////////////////////////////////
#endif
