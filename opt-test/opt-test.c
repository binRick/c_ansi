
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_eventemitter/include/eventemitter.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "chan/src/chan.h"
#include "chan/src/queue.h"
#include "incbin/incbin.h"
#include "log/log.h"
#include "module/def.h"
#include "module/module.h"
#include "module/require.h"
#include "ms/ms.h"
#include "opt-test/opt-test.h"
#include "opt/opt.h"
#include "tempdir.c/tempdir.h"
#include "timestamp/timestamp.h"
#include "which/src/which.h"

TEST t_opt_test_option_qty(){
  size_t qty=require(opt)->option->qty();
  Dn(qty);
  PASS();
}

SUITE(s_opt_test) {
  RUN_TEST(t_opt_test_option_qty);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_opt_test);
  GREATEST_MAIN_END();
}
