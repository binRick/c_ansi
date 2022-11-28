
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "ms/ms.h"
#include "timestamp/timestamp.h"
#include "ts/ts.h"
#include "ts-test/ts-test.h"

TEST t_ts_test_uptime(){
  unsigned long uptime=require(ts)->uptime();
  char *s;
  asprintf(&s,"Uptime: %ld",uptime);
  PASSm(s);
}
TEST t_ts_test_ms(){
  unsigned long ms=require(ts)->ms();
  char *s;
  asprintf(&s,"Now: %ld",ms);
  PASSm(s);
}
TEST t_ts_test_ts(){
  unsigned long ts=require(ts)->ts();
  char *s;
  asprintf(&s,"Now: %ld",ts);
  PASSm(s);
}

SUITE(s_ts_test) {
  RUN_TEST(t_ts_test_ts);
  RUN_TEST(t_ts_test_ms);
  RUN_TEST(t_ts_test_uptime);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_ts_test);
  GREATEST_MAIN_END();
}
