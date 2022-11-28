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
#include "str-truncate.c/src/str-truncate.h"
#include "occurences.c/occurrences.h"
#include "str-flatten.c/src/str-flatten.h"
#include "module/def.h"
#include "module/module.h"
#include "module/require.h"
#include "smaz/smaz.h"
#include "is_number.c/is_number.h"
#include "slug.c/src/slug.h"
#include "genpassword.c/src/genpassword.h"
//////////////////////////////////////
enum digit_emoji_type_t {
  DIGIT_EMOJI_TYPE_SMALL,
  DIGIT_EMOJI_TYPE_CIRCLE,
  DIGIT_EMOJI_TYPES_QTY,
};
typedef bool (*str_filter_fxn_t)(char *LINE);
typedef bool (^str_filter_block_t)(char *LINE);
typedef void (*str_each_fxn_t)(char *LINE);
typedef void (^str_each_block_t)(char *LINE);

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
  module(str_is) {
    bool (*number)(const char *num, int len);
  } *is;
  int *(*compress)(char *in,int inlen,char *out,int outlen);
  int *(*decompress)(char *in,int inlen,char *out,int outlen);
  char *(*lowercase)(const char *);
  char *(*uppercase)(const char *);
  char *(*replace)(char *, char, char);
  char *(*password)(int len);
  char *(*slug)(char *);
  bool (*equal)(const char *, const char *);
  char *(*trim)(const char *);
  char *(*truncate)(const char *, int len);
  module(__str_split) {
    define(__str_split, CLIB_MODULE);
    struct StringFNStrings (*lines)(const char *);
    struct Vector *(*vec)(const char *);
    char **(*arr)(const char *, int *qty);
  } *split;
  module(__str_filter) {
    define(__str_filter, CLIB_MODULE);
    module(__str_filter_arr) {
      define(__str_filter_arr, CLIB_MODULE);
      struct Vector *(^block)(struct Vector *v, str_filter_block_t *block);
      struct Vector *(*fxn)(struct Vector *v, str_filter_fxn_t *fxn);
    } *arr;
    module(__str_filter_lines) {
      define(__str_filter_lines, CLIB_MODULE);
      struct Vector *(^block)(struct Vector *v, str_filter_block_t *block);
      struct Vector *(*fxn)(struct Vector *v, str_filter_fxn_t *fxn);
    } *lines;
    module(__str_filter_vec) {
      define(__str_filter_vec, CLIB_MODULE);
      struct Vector *(^block)(struct Vector *v, str_each_block_t *block);
      struct Vector *(*fxn)(struct Vector *v, str_each_fxn_t *fxn);
    } *vec;
  } *filter;
  module(__str_each) {
    define(__str_each, CLIB_MODULE);
    module(__str_each_arr) {
      define(__str_each_arr, CLIB_MODULE);
      void (*block)(struct Vector *v, str_each_block_t *block);
      void (*fxn)(struct Vector *v, str_each_fxn_t *fxn);
    } *arr;
    module(__str_each_vec) {
      define(__str_each_vec, CLIB_MODULE);
      void (*block)(struct Vector *v, str_each_block_t *block);
      void (*fxn)(struct Vector *v, str_each_fxn_t *fxn);
    } *vec;
    struct StringFNStrings (*lines)(struct StringFNStrings *lines);
    char *(*ch)(char *, char, char);
    char *(*str)(char *, char*, char*);
  } *each;
  module(__str_repl) {
    define(__str_repl, CLIB_MODULE);
    struct Vector *(*vec)(struct Vector *v);
    char **(*arr)(const char **arr, int qty, int *new_qty);
    struct StringFNStrings (*lines)(struct StringFNStrings *lines);
    char *(*ch)(char *, char, char);
    char *(*str)(char *, char*, char*);
  } *repl;
  module(__str_match) {
    define(__str_split, CLIB_MODULE);
    char *(*vec)(struct Vector *v);
    char *(*arr)(const char **arr, int qty);
    char *(*lines)(struct StringFNStrings *lines);
  } *match;
  module(__str_join) {
    define(__str_split, CLIB_MODULE);
    char *(*vec)(struct Vector *v);
    char *(*arr)(const char **arr, int qty);
    char *(*lines)(struct StringFNStrings *lines);
  } *join;
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
struct Vector *__str_each_block(struct Vector *v, str_each_block_t *block);
bool __str_filter_block(struct Vector *v, str_filter_block_t block);
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
  .slug   = slug,
  .password   = generate_password,
  .compress   = smaz_compress,
  .decompress   = smaz_decompress,
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
