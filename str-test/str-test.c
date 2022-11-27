
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
  RUN_TEST(t_str_test1);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  str = require(str);
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_str_test);
  GREATEST_MAIN_END();
}
