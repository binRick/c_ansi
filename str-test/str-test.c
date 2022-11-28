
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "ms/ms.h"
#include "str-test/str-test.h"
#include "str/str.h"
#include "timestamp/timestamp.h"
module(str) * str;


TEST t_str_filter_arr(){
  char *arr[]={"a","b","c","AAA","a"};
  Dn(sizeof(arr));
  PASS();
}
TEST t_str_filter_lines(){
//  struct StringFNStrings lines= require(str)->split->lines("a\tb\nc d");
 // Di(lines.count);
  PASS();
}
TEST t_str_filter_vec(){
  struct Vector *v=vector_new();
  vector_push(v,(void*)timestamp());
  usleep(1000*100);
  vector_push(v,(void*)timestamp());
  usleep(1000*100);
  vector_push(v,(void*)timestamp());
  usleep(1000*100);
  Dn(vector_size(v));
  PASS();
}
TEST t_str_test_emojis_qty(){
  size_t qty=0;
  qty= require(str)->emojis->qty();
  Dn(qty);
  PASS();
}
TEST t_str_test_emojis_arr(){
  size_t qty=0;
  char **chars = require(str)->emojis->arr(&qty);
  Dn(qty);
  PASS();
}
TEST t_str_test_emojis_vec(){
  struct Vector *v=require(str)->emojis->vec();
  Dn(vector_size(v));
  PASS();
}
TEST t_str_test_lines(){
  char *s = "a\n\ta bsds r\n\tasdsa";
  struct StringFNStrings lines;
  lines =require(str)->split_lines(s);
  Di(lines.count);
//  lines =require(str)->fn->split(s);
  Di(lines.count);
  PASS();
}
TEST t_str_test_digit(){
  char *digit;
  for(int i=0;i<10;i++){
    digit = require(str)->emoji->digit(DIGIT_EMOJI_TYPE_CIRCLE, i);
    if(digit)
      log_info("%d- %s", i,digit);
  }

  PASS();
}
TEST t_str_test_digits(){
  char **digits = require(str)->emoji->digits(DIGIT_EMOJI_TYPE_CIRCLE);
  ASSERT_NEQm("Invalid digits",digits,NULL);
  int i=0;
  while(digits[i]){
    log_info("%s",digits[i]);
    i++;
  }
  PASS();
}
TEST t_str_test1(){
  char *s  = "  AbCdEfg\t  sS";
  char *lc = str->lowercase(s);

  log_info("%s->%s->%s->%s",
           s,
           str->lowercase(s),
           str->uppercase(str->lowercase(s)),
           str->trim(s)
           );
  PASS();
}

SUITE(s_str_test) {
  /*
  RUN_TEST(t_str_test1);
  RUN_TEST(t_str_test_digits);
  RUN_TEST(t_str_test_digit);
  RUN_TEST(t_str_test_lines);
  RUN_TEST(t_str_test_emojis_vec);
  RUN_TEST(t_str_test_emojis_arr);
  RUN_TEST(t_str_test_emojis_qty);
  RUN_TEST(t_str_filter_arr);
  RUN_TEST(t_str_filter_lines);
  RUN_TEST(t_str_filter_vec);
  */
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  //str = require(str);
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_str_test);
  GREATEST_MAIN_END();
}
