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
#include "qr-test/qr-test.h"
#include "qr/qr.h"
#include "tempdir.c/tempdir.h"
#include "timestamp/timestamp.h"
INCBIN(qr_passwd_png, "assets/qr-passwd.png");
INCBIN(qr1_png, "assets/qr1.png");
INCBIN(qr1_32_png, "assets/qr1-32.png");
static char          *qr_passwd_png_file;
struct Vector        *files_v;
static unsigned char *files[] = {
  gqr_passwd_pngData,
  gqr1_pngData,
  gqr1_32_pngData,
};
static size_t        *file_sizes, files_qty;
static struct Vector *__qr_get_files_v(void){
  struct Vector *v = vector_new();

  for (int i = 0; files[i]; i++)
    vector_push(v, (void *)files[i]);
  return(v);
}

char *__qr_get_file_index_as_path(int index){
  char *s;
//  asprintf(&s,"%s%d
}

size_t *(^__qr_get_file_sizes)(size_t *qty) = ^ size_t *(size_t *qty){
  struct Vector *v  = vector_new();
  size_t        s[] = {
    gqr_passwd_pngSize,
    gqr1_pngSize,
    gqr1_32_pngSize,
    0,
  };
  for (int i = 0; s[i]; i++)
    vector_push(v, (void *)s[i]);
  *qty = vector_size(v);
  size_t *sizes = (size_t **)vector_to_array(v);
  return(sizes);
};

TEST t_qr_test_encode_path(){
  PASS();
}

TEST t_qr_test_encode_str(){
  size_t len = 0; unsigned char *buf;

  PASS();
  buf = require(qr)->encode->path(qr_passwd_png_file, &len);
  ASSERT_NEQm("Failed to encode", buf, NULL);
  ASSERT_GTEm("Failed to encode", len, 1);
  PASS();
}

TEST t_qr_test_qrcode_png(){
  bool          ok       = false;
  unsigned char *files[] = {
    gqr_passwd_pngData,
    gqr1_pngData,
    //  gqr1_32_pngData,
    NULL,
  };
  char          **f = files, *s;

  for (int i = 0; files[i]; i++) {
    asprintf(&s, "%sqr-test-encode-%d.png", gettempdir(), i);
    size_t len = 0; unsigned char *buf;
    //  buf = require(qr)->encode->path(files[i],&len);
  }
//  ok = require(qr)->qrcode(qr_passwd_png_file);
//  ASSERT_EQm("Failed to qrcode",ok,true);
  PASS();
}

SUITE(s_qr_test) {
  RUN_TEST(t_qr_test_qrcode_png);
  RUN_TEST(t_qr_test_encode_str);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  files_v    = __qr_get_files_v();
  file_sizes = __qr_get_file_sizes(&files_qty);
  size_t qty    = 0;
  size_t *sizes = __qr_get_file_sizes(&qty);
  Dn(qty);
  for (int i = 0; i < qty; i++)
    log_info("%s- %s", files[i], bytes_to_string(sizes[i]));
  asprintf(&qr_passwd_png_file, "%s%lld.png", gettempdir(), timestamp());
  Ds(qr_passwd_png_file);
  Dn(files_qty);
  Dn(file_sizes[files_qty - 1]);
  errno = 0;
  if (!fsio_write_binary_file(qr_passwd_png_file, gqr_passwd_pngData, gqr_passwd_pngSize)) {
    log_error("failed to write %s", qr_passwd_png_file);
    exit(EXIT_FAILURE);
  }
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_qr_test);
  GREATEST_MAIN_END();
}
