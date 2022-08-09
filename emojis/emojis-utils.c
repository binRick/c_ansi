#pragma once
#include <locale.h>
#include <stdbool.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <xlocale.h>
/////////////////////////////////////
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "emojis/emojis-utils.h"
#include "emojis/emojis.h"
/////////////////////////////////////

struct str_wchar_t *str_to_str_wchar_t(const char *STR){
  struct str_wchar_t *w = calloc(1, sizeof(struct str_wchar_t));

  w->string = strdup(STR);
  w->len    = mbstowcs(w->wchar, w->string, strlen(w->string));
  return(w);
}


size_t str_to_wchar_t_len(const char *STR){
  wchar_t *wcs = calloc(strlen(STR) + 1, sizeof(wchar_t));
  size_t  l    = mbstowcs(wcs, STR, strlen(STR));

  return(l);
}


wchar_t *str_to_wchar_t(const char *STR){
  wchar_t *wcs = calloc(strlen(STR) + 1, sizeof(wchar_t));
  size_t  l    = mbstowcs(wcs, STR, strlen(STR));

  return(wcs);
}

struct parsed_emoji_t *get_parsed_emoji_t(char *EMOJI_STRING){
  struct StringBuffer   *sb         = stringbuffer_new();
  struct StringBuffer   *padding_sb = stringbuffer_new();
  struct parsed_emoji_t *E          = malloc(sizeof(struct parsed_emoji_t));

  E->iter = get_emoji_iter(EMOJI_STRING);
  while (utf8_next(E->iter)) {
    char *Character = utf8_getchar(E->iter);
    stringbuffer_append_string(sb, Character);
  }
  E->len       = E->iter->length;
  E->chars_qty = E->iter->count;
  E->string    = stringbuffer_to_string(sb);
  E->padding   = "";

  for (size_t i = 0; i < E->len; i++) {
    stringbuffer_append_string(padding_sb, " ");
  }
  E->padding = stringbuffer_to_string(padding_sb);
  return(E);
}


utf8_iter *get_emoji_iter(char *EMOJI_STRING){
  utf8_iter *ITER = malloc(sizeof(utf8_iter));

  utf8_init(ITER, EMOJI_STRING);
  return(ITER);
}


#define MIN(a, b)    (((a) < (b)) ? (a) : (b))


size_t u8strwid(const void *beg, const void *end, size_t *width){
  struct Vector *__emojis_v = get_emojis_t_v();
//  const char   **emojis = emojis_emojis_a();
  const char    *__emojis[] = { "😃", "😍", "🧑", "🔢", "👍", "💯", };
  const size_t  sz          = sizeof(__emojis) / sizeof(__emojis[0]);
  const size_t  raw_len     = (const char *)end - (const char *)beg;

  /*
   * printf("beg: '%s'\n", (char*)beg);
   * printf("end: '%s'\n", (char*)end);
   * printf("raw len: '%lu'\n", raw_len);
   * printf("sz: '%lu'\n", sz);
   */
  for (size_t i = 0; i < sz; ++i) {
    if (memcmp(beg, __emojis[i], MIN(strlen(__emojis[i]), raw_len)) == 0) {
      *width = 2;       /* On my terminal emojis have width of 2 chars */
      return(0);
    }
  }
  for (size_t i = 0; i < vector_size(__emojis_v); i++) {
    struct emojis_t       *e = vector_get(__emojis_v, i);
    struct parsed_emoji_t *E = get_parsed_emoji_t(e->emoji);
    if (strcmp(E->string, beg) == 0) {
      *width = 2;
      return(0);
    }
  }
  return(1);
}
#undef MIN
