#include "tray/tray.h"
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
#include "tempdir.c/tempdir.h"
#include "timestamp/timestamp.h"
#include "tray-test/tray-test.h"
#include "which/src/which.h"

TEST t_tray_test2(){
  PASS();
}

TEST t_tray_test1(){
  //Ds(require(tray)->name);
  PASS();
}

SUITE(s_tray_test) {
  RUN_TEST(t_tray_test1);
  if (isatty(STDOUT_FILENO))
    RUN_TEST(t_tray_test2);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_tray_test);
  GREATEST_MAIN_END();
}
