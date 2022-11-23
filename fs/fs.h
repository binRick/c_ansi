#pragma once
#ifndef FS_H
#define FS_H
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
#include "c_fsio/include/fsio.h"
#include "cache/cache.h"
#include "module/def.h"
#include "module/module.h"
#include "module/require.h"
#include "tempdir.c/tempdir.h"
#include "wildcardcmp/wildcardcmp.h"
//////////////////////////////////////
module(fs) {
  define(fs, CLIB_MODULE);

  char          **(*match_files)(const char *path, const char *glob, int *qty);
  char          *(*tmpdir)(void);
  char          *(*tmpdir_extension)(const char *extension);
  char          *(*tmpfile)(void);
  char          *(*tmpfile_extension)(const char *extension);
  bool          (*remove)(char *path);
  bool          (*mkdirs)(char *path);
  bool          (*mkdirs_parent)(char *path);
  bool          (*copy_file)(char *src, char *dst);
  long          (*file_size)(char *);
  char          *(*read_text_file)(char *);
  unsigned char *(*read_binary_file)(char *, int *len);
  bool          (*write_text_file)(char *path, char *data);
  bool          (*write_binary_file)(char *path, unsigned char *data, int len);
};

int  fs_init(module(fs) * exports);
void fs_deinit(module(fs) * exports);
char *__fs_tmpfile(module(fs) * exports);
char *__fs_tmpfile_extension(const char *extension);
char *__fs_tmpdir_extension(const char *extension);
char **__fs_match_files(const char *PATH, const char *GLOB, int *qty);

exports(fs) {
  .tmpdir            = gettempdir,
  .tmpfile           = __fs_tmpfile,
  .tmpfile_extension = __fs_tmpfile_extension,
  .tmpdir_extension  = __fs_tmpdir_extension,
  .init              = fs_init,
  .match_files       = __fs_match_files,
  .deinit            = fs_deinit,
  .remove            = fsio_remove,
  .mkdirs            = fsio_mkdirs,
  .mkdirs_parent     = fsio_mkdirs_parent,
  .copy_file         = fsio_copy_file,
  .file_size         = fsio_file_size,
  .read_text_file    = fsio_read_text_file,
  .read_binary_file  = fsio_read_binary_file,
  .write_text_file   = fsio_write_text_file,
  .write_binary_file = fsio_write_binary_file,
};

#define fs_m    module(fs)

#endif
