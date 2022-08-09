#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
/////////////////////////////////////
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/include/vector.h"
#include "emojis/emojis.h"
#include "emojis/emojis.h"
#include "utf8-iterator/source/utf-8.h"
/////////////////////////////////////
struct parsed_emoji_t {
  struct StringFNStrings chars;
  char                   *string;
  size_t                 len, chars_qty;
  utf8_iter              *iter;
  char                   *padding;
};
struct str_wchar_t {
  char    *string;
  wchar_t *wchar;
  size_t  len;
};

/////////////////////////////////////
struct str_wchar_t *str_to_str_wchar_t(const char *STR);
utf8_iter *get_emoji_iter(char *EMOJI_STRING);
struct parsed_emoji_t *get_parsed_emoji_t(char *EMOJI_STRING);
size_t u8strwid(const void *beg, const void *end, size_t *width);

/////////////////////////////////////
