
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "incbin/incbin.h"
#include "log/log.h"
#include "ms/ms.h"
#include "qoir-test/qoir-test.h"
#include "qoir/qoir.h"
#include "tempdir.c/tempdir.h"
#include "timestamp/timestamp.h"
INCBIN(qoir_file_1, "assets/qoir_file_1.qoir");
module(qoir) * qoir;

TEST t_qoir_test_ptr(){
  qoir->decode(gqoir_file_1Data, gqoir_file_1Size);
  PASS();
}

TEST t_qoir_test_file(){
  char *tf;

  asprintf(&tf, "%s%lld.qoir", gettempdir(), timestamp());
  fsio_write_binary_file(tf, gqoir_file_1Data, gqoir_file_1Size);
  qoir->decode_path(tf);
  Di(qoir->pid);

  PASS();
}

SUITE(s_qoir_test) {
  RUN_TEST(t_qoir_test_file);
  RUN_TEST(t_qoir_test_ptr);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  qoir = require(qoir);
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_qoir_test);
  GREATEST_MAIN_END();
}
