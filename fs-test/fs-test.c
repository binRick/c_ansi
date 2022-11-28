
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "fs-test/fs-test.h"
#include "fs/fs.h"
#include "log/log.h"
#include "ms/ms.h"
#include "str/str.h"
#include "timestamp/timestamp.h"

TEST t_fs_test_normalize(){
  char *s;
  log_info("%s",(require(fs)->normalize("/tmp//xx")));
  log_info("%s",(require(fs)->normalize("/tmp//xx/123//")));
  log_info("%s",(require(fs)->normalize("/tmp//")));
  PASS();
}

TEST t_fs_test2(){
  PASS();
}

TEST t_fs_test1(){
  long len = require(fs)->file_size("/etc/passwd");

  ASSERT_GTm("Invalid file size", len, 32);
  char                   *passwd = require(fs)->read_text_file("/etc/passwd");
  struct StringFNStrings lines = require(str)->split_lines(passwd);
  char                   *tf = require(fs)->tmpfile();
  char                   *td = require(fs)->tmpdir();
  char                   *tfe0 = require(fs)->tmpfile_extension("qoir");
  char                   *tfe1 = require(fs)->tmpfile_extension(".qoir");
  int                    png_files_qty = 0, qoir_files_qty = 0;
  char                   **tmp_png_files  = require(fs)->match_files("/tmp", "*.png", &png_files_qty);
  char                   **tmp_qoir_files = require(fs)->match_files("/tmp", "*.qoir", &qoir_files_qty);

  Di(png_files_qty);
  Di(qoir_files_qty);

  Ds(tf);
  Ds(tfe0);
  Ds(tfe1);
  Ds(td);
  Di(lines.count);
  PASS();
}

SUITE(s_fs_test) {
  RUN_TEST(t_fs_test1);
  RUN_TEST(t_fs_test_normalize);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_fs_test);
  GREATEST_MAIN_END();
}
