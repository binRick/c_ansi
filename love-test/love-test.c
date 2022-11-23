
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "incbin/incbin.h"
#include "log/log.h"
#include "love-test/love-test.h"
#include "love/love.h"
#include "module/module.h"
#include "module/require.h"
#include "ms/ms.h"
#include "timestamp/timestamp.h"
#define LOVE_TEST_FILE          "love/love.h"
#define LOVE_TEST_LARGE_FILE    ".wow.c"
INCBIN(file_c, "assets/file.c");
INCBIN(file, LOVE_TEST_FILE);
INCBIN(large, LOVE_TEST_LARGE_FILE);
static const char *fmts[] = {
  "qoi", "qoir", "jpeg", "gif",
}; static size_t fmts_qty = sizeof(fmts) / sizeof(fmts[0]);
module(love) * l[10];

TEST t_love_strings(){
  module(love) * l = require(love)->cfg("s0");
  require(love)->cfg_save_png(l, "/tmp/love-test-Makefile.png");
  PASS();
}

TEST t_love_style_large_file_to_png(){
  PASS();
}

TEST t_love_style_large_file_to_path(){
  char *dst = "/tmp/styled-love-large-file.ansi", *src = LOVE_TEST_LARGE_FILE;
  bool ok = require(love)->style_file_to_path(src, dst);

  PASS();
}

TEST t_love_style_file_to_path(){
  bool ok;

  ok = require(love)->style_file_to_path(LOVE_TEST_FILE, "/tmp/styled-love-test-file.ansi");
  ok = require(love)->style_file_to_path(LOVE_TEST_FILE, "/tmp/styled-love-test-file.jpeg");
  ok = require(love)->style_file_to_path(LOVE_TEST_FILE, "/tmp/styled-love-test-file.gif");
  ok = require(love)->style_file_to_path(LOVE_TEST_FILE, "/tmp/styled-love-test-file.qoi");
  ok = require(love)->style_file_to_path(LOVE_TEST_FILE, "/tmp/styled-love-test-file.qoir");
  ASSERT_EQ(ok, true);
  PASS();
}

TEST t_love_style_file_to_png(){
  char *dst = "/tmp/styled-love-file.png", *src = LOVE_TEST_FILE;
  bool ok = require(love)->style_file_to_png(src, dst);

  ASSERT_EQ(ok, true);
  PASS();
}

TEST t_love_style_file_to_string(){
  unsigned long s = timestamp();
  char          *buf = require(love)->style_file(LOVE_TEST_FILE); size_t len = strlen(buf);
  unsigned long dur = timestamp() - s;

  Ds(buf);
  Ds(milliseconds_to_string(dur));
  PASS();
}

TEST t_love_file(){
  require(love)->file(LOVE_TEST_FILE);
  PASS();
}

TEST t_love_test2(){
  PASS();
}
enum love_test_content_t {
  LOVE_TEST_FILE_C,
};

TEST t_love_test(){
  require(love)->test();
  PASS();
}

TEST t_love_logic(){
  l[0] = require(love)->cfg("LOVE_TEST_FILE_C");
  char   *files[] = { 0 };
//  asprintf(&(files[0],"/tmp/love-test-%s","file.c"));
  size_t qty = 1;

  // l[1] = require(love)->cfg_load_str(l[0], (char*)gfile_cData);
  l[0] = require(love)->cfg("Makefile");
  Ds(require(love)->cfg_get_font(l[0]));
  require(love)->cfg_set_font(l[0], "xyzfont");
  Ds(require(love)->cfg_get_font(l[0]));
  require(love)->cfg_load_file(l[0], "Makefile");
  require(love)->cfg_render(l[0]);
  require(love)->cfg_save_png(l[0], "/tmp/love-test-Makefile.png");
  Dn(fsio_file_size("/tmp/love-test-Makefile.png"));
  PASS();

  l[1] = require(love)->cfg("love c");
  require(love)->cfg_load_file(l[1], "love/love.c");
  require(love)->cfg_save_file(l[1], "/tmp/love-test-love.c");
  require(love)->cfg_load_styled_file(l[1], "love/love.c", LOVE_STYLE_BAT);
  require(love)->cfg_render(l[1]);
  require(love)->cfg_save_png(l[0], "/tmp/love-test-love-c.png");

  l[2] = require(love)->cfg("love h");
  require(love)->cfg_load_file(l[2], "love/love.h");
  require(love)->cfg_save_file(l[2], "/tmp/love-test-love.h");
  require(love)->cfg_load_styled_file(l[2], "love/love.h", LOVE_STYLE_BAT);
  require(love)->cfg_render(l[2]);
  require(love)->cfg_save_png(l[0], "/tmp/love-test-love-h.png");

  Di(gfile_cSize);
  PASS();
}

SUITE(s_love_test) {
  RUN_TEST(t_love_test);
  RUN_TEST(t_love_strings);
  RUN_TEST(t_love_file);
  RUN_TEST(t_love_logic);
  RUN_TEST(t_love_style_file_to_string);
  RUN_TEST(t_love_style_file_to_path);
  RUN_TEST(t_love_style_file_to_png);
  RUN_TEST(t_love_style_large_file_to_path);
  RUN_TEST(t_love_style_large_file_to_png);
  if (isatty(STDOUT_FILENO))
    RUN_TEST(t_love_test2);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_love_test);
  GREATEST_MAIN_END();
}
