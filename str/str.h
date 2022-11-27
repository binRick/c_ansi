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
enum digit_emoji_type_t {
  DIGIT_EMOJI_TYPE_SMALL,
  DIGIT_EMOJI_TYPE_CIRCLE,
  DIGIT_EMOJI_TYPES_QTY,
};

module(str) {
  define(str, CLIB_MODULE);
  module(str_emoji) {
    define(str_emoji, CLIB_MODULE);
    char **(*digits)(enum digit_emoji_type_t type);
    char *(*digit)(enum digit_emoji_type_t type, int digit);
  } *emoji;
  module(str_emojis) {
    define(str_emojis, CLIB_MODULE);
    struct Vector *(*vec)(void);
    char **(*arr)(int *qty);
    size_t (*qty)(void);
  } *emojis;

  /*
  module(str_lines) {
    module(str_lines_fn) {
      define(str_lines_fn, CLIB_MODULE);
      struct StringFNStrings (*split)(const char *);
    } *fn;
    module(str_lines_vec) {
      define(str_lines_vec, CLIB_MODULE);
        struct Vector *(*split)(const char *);
    } *vec;
    module(str_lines_arr) {
      define(str_lines_arr, CLIB_MODULE);
        char **(*split)(const char *, int *qty);
    } *arr;
  } *lines;
  */

  char *(*lowercase)(const char *);
  char *(*uppercase)(const char *);
  char *(*replace)(char *, char, char);
  bool (*equal)(const char *, const char *);
  char *(*trim)(const char *);

  struct StringFNStrings (*split_lines)(const char *);
};

int  str_init(module(str) *exports);
void str_deinit(module(str) *exports);
char **__str_get_digits_type(enum digit_emoji_type_t type);
char **__str_get_digit_type(enum digit_emoji_type_t type, const int digit);
char **__str_split_lines_arr(const char *str,int *qty);
struct Vector *__str_get_emojis(void);
char **__str_get_emojis_arr(int *qty);
size_t __str_get_emojis_qty(void);
struct StringFNStrings __str_split_lines_fn(const char *str);
/*
exports(str_lines_vec) {
  .init        = 0,
  .deinit      = 0,
  .split      = stringfn_split_lines_and_trim,
};
exports(str_lines_arr) {
  .init        = 0,
  .deinit      = 0,
  .split      = stringfn_split_lines_and_trim,
};
exports(str_lines_fn) {
  .init        = 0,
  .deinit      = 0,
  .split      = stringfn_split_lines_and_trim,
};
*/
exports(str_emojis) {
  .init        = 0,
  .deinit      = 0,
  .vec=__str_get_emojis,
  .arr=__str_get_emojis_arr,
  .qty=__str_get_emojis_qty,
};
exports(str_emoji) {
  .init        = 0,
  .deinit      = 0,
  .digits=__str_get_digits_type,
  .digit=__str_get_digit_type,
};
exports(str) {
 // .lines=0,
  .emoji=0,
  .emojis=0,
 // .fn=0,
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
