
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "ms/ms.h"
#include "qr/qr.h"
#include "qr-test/qr-test.h"
#include "incbin/incbin.h"
#include "tempdir.c/tempdir.h"
#include "timestamp/timestamp.h"
INCBIN(qr_passwd_png,"assets/qr-passwd.png");
static char *qr_passwd_png_file;

TEST t_qr_test_encode_str(){
  bool ok=false;
  ok = require(qr)->encode(qr_passwd_png_file);
  ASSERT_EQm("Failed to encode",ok,true);
  PASS();
}
TEST t_qr_test_qrcode_png(){
  bool ok=false;
  ok = require(qr)->qrcode(qr_passwd_png_file);
  ASSERT_EQm("Failed to qrcode",ok,true);
  PASS();
}

SUITE(s_qr_test) {
  RUN_TEST(t_qr_test_qrcode_png);
  RUN_TEST(t_qr_test_encode_str);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  asprintf(&qr_passwd_png_file,"%s%lld.png",gettempdir(),timestamp());
  Ds(qr_passwd_png_file);
  errno=0;
  if(!fsio_write_binary_file(qr_passwd_png_file,gqr_passwd_pngData,gqr_passwd_pngSize)){
    log_error("failed to write %s",qr_passwd_png_file);
    exit(EXIT_FAILURE);
  }
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_qr_test);
  GREATEST_MAIN_END();
}
