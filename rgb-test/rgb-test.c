
#include "ansi-codes/ansi-codes.h"
#include "ansi-rgb-utils/ansi-rgb-utils.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "ms/ms.h"
#include "rgb-test/rgb-test.h"
#include "timestamp/timestamp.h"

TEST t_rgb_test2(){
  PASS();
}

TEST t_rgb_test1(){
  log_info("t1");
//  print_cube(stdout,8);
//  print_cube(stdout,1);
  au_print_hex_cube(stdout, "#aabb11");
  au_print_hex_cube(stdout, "#1e1e1e");
  au_print_hex_cube(stdout, "#ffffff");
  au_print_hex_cube(stdout, "#000000");
  PASS();
}

SUITE(s_rgb_test) {
  RUN_TEST(t_rgb_test1);
  if (isatty(STDOUT_FILENO))
    RUN_TEST(t_rgb_test2);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_rgb_test);
  GREATEST_MAIN_END();
}
