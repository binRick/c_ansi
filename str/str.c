#pragma once
#ifndef STR_C
#define STR_C
////////////////////////////////////////////
////////////////////////////////////////////
#include "str/str.h"
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
#include "emojis/emojis.h"
static const char *digit_emojis[][32];



inline size_t __str_get_emojis_qty(){
  size_t qty=0;
  struct Vector *v=get_emojis_t_v();
  qty=vector_size(v);
  vector_release(v);
  return qty;
}
inline char **__str_get_emojis_arr(int *qty){
    struct Vector *v=get_emojis_t_v();
    *qty=vector_size(v);
    return(vector_to_array(v));
}

inline struct Vector *__str_get_emojis(){
    return(get_emojis_t_v());
}

inline char **__str_get_digit_type(enum digit_emoji_type_t type, const int digit){
  if(digit>9){
    struct StringBuffer *sb=stringbuffer_new();
    char *s,*s0,*s1;
    int i0;
    asprintf(&s,"%d",digit);
    for(size_t i=0;i<strlen(s);i++){
      asprintf(&s0,"%c",s[i]);
      i0=atoi(s0);
      stringbuffer_append_string(sb,require(str)->emoji->digit(type,i0));
      free(s0);
    }
    free(s);
    s1=stringbuffer_to_string(sb);
    stringbuffer_release(sb);
    return(s1);
  }
  char **d;
  if((d=__str_get_digits_type(type))){
    return(d[digit]);
  }
  return 0;
}

inline char **__str_get_digits_type(enum digit_emoji_type_t type){
  if(type>=DIGIT_EMOJI_TYPES_QTY)return(0);
  return(digit_emojis[type]);
}

static const char *digit_emojis[][32]={
 [DIGIT_EMOJI_TYPE_CIRCLE] = {
  "⓪",
  "①",
  "②",
  "③",
  "④",
  "⑤",
  "⑥",
  "⑦",
  "⑧",
  "⑨",
 },
 [DIGIT_EMOJI_TYPE_SMALL] = {  
  "0⃣",
  "1⃣",
  "2⃣",
  "3⃣",
  "4⃣",
  "5⃣",
  "6⃣",
  "7⃣",
  "8⃣",
  "9⃣",
 },
};
////////////////////////////////////////////
static inline void  str_info(char *message);
static inline void  str_error(char *message);
static inline void  str_debug(char *message);
static inline int   str_GetPID();

////////////////////////////////////////////
int str_init(module(str) *exports) {
  clib_module_init(str, exports);
  exports->emoji=require(str_emoji);
  exports->emojis=require(str_emojis);
  /*
  exports->lines->fn=require(str_lines_fn);
  exports->lines->arr=require(str_lines_arr);
  exports->lines->vec=require(str_lines_vec);
  */
  return(EXIT_SUCCESS);
}

void str_deinit(module(str) *exports) {
  clib_module_deinit(str);
}

////////////////////////////////////////////
#endif
