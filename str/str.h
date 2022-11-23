#pragma once
#ifndef STR_H
#define STR_H
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
#include "c_stringfn/include/stringfn.h"
#include "module/def.h"
#include "module/module.h"
#include "module/require.h"
//////////////////////////////////////

module(str) {
  define(str, CLIB_MODULE);

  char *(*lowercase)(const char *);
  char *(*uppercase)(const char *);

  char *(*replace)(char *, char, char);

  bool (*equal)(const char *, const char *);
  char *(*trim)(const char *);

  struct StringFNStrings (*split_lines)(const char *);
};

int  str_init(module(str) * exports);
void str_deinit(module(str) * exports);

exports(str) {
  .lowercase   = stringfn_to_lowercase,
  .uppercase   = stringfn_to_uppercase,
  .replace     = stringfn_replace,
  .init        = str_init,
  .deinit      = str_deinit,
  .equal       = stringfn_equal,
  .trim        = stringfn_trim,
  .split_lines = stringfn_split_lines_and_trim,
};

#define str_m    module(str)

#endif
