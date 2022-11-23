#pragma once
#ifndef FS_C
#define FS_C
////////////////////////////////////////////

////////////////////////////////////////////
#include "fs/fs.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "cache/cache.h"
#include "log/log.h"
#include "ms/ms.h"
#include "qoi/qoi.h"
#include "qoir/src/qoir.h"
#include "str/str.h"
#include "string-utils/string-utils.h"
#include "timestamp/timestamp.h"
#include "tinydir/tinydir.h"
#include "which/src/which.h"
#include "wildcardcmp/wildcardcmp.h"

////////////////////////////////////////////
char *__fs_tmpdir_extension(const char *extension) {
  char *s;

  asprintf(&s, "%s.%s", require(fs)->tmpdir(), require(str)->trim(require(str)->replace(extension, '.', ' ')));
  require(fs)->mkdirs(s);
  return(s);
}

char *__fs_tmpfile_extension(const char *extension) {
  char *s;

  asprintf(&s, "%s.%s", require(fs)->tmpfile(), require(str)->trim(require(str)->replace(extension, '.', ' ')));
  return(s);
}

int fs_init(module(fs) *exports) {
  clib_module_init(fs, exports);

  return(EXIT_SUCCESS);
}

void fs_deinit(module(fs) *exports) {
  clib_module_deinit(fs);
}

////////////////////////////////////////////
char **__fs_match_files(const char *PATH, const char *GLOB, int *qty){
  struct Vector *items_v = vector_new();
  tinydir_dir   dir;

  if (tinydir_open(&dir, PATH) == -1) {
    perror("Error opening file");
    goto bail;
  }

  while (dir.has_next) {
    tinydir_file file;
    if (tinydir_readfile(&dir, &file) == -1) {
      perror("Error getting file");
      goto bail;
    }

    if (!(file.is_dir) && file.is_reg)
      if (wildcardcmp(GLOB, file.name))
        vector_push(items_v, (void *)(strdup(file.name)));

    if (tinydir_next(&dir) == -1) {
      perror("Error getting next file");
      goto bail;
    }
  }

bail:
  tinydir_close(&dir);
  *qty = (int)(size_t)vector_size(items_v);
  return(vector_to_array(items_v));
}

char *__fs_tmpfile(){
  char *s;

  asprintf(&s, "%s%d-%lld", require(fs)->tmpdir(), getpid(), timestamp());
  return(s);
}
////////////////////////////////////////////
#endif
