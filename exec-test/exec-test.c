
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "exec-test/exec-test.h"
#include "log/log.h"
#include "ms/ms.h"
#include "timestamp/timestamp.h"
#include "exec/exec.h"

TEST t_exec_test2(){
  PASS();
}

TEST t_exec_test1(){
  char *out;
  out = require(exec)->sh("pwd");
  Ds(out);
  out = require(exec)->sh("ls /");
  Ds(out);

  PASS();
}

SUITE(s_exec_test) {
  RUN_TEST(t_exec_test1);
  if (isatty(STDOUT_FILENO))
    RUN_TEST(t_exec_test2);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_exec_test);
  GREATEST_MAIN_END();
}
