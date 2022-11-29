
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "lodepng/lodepng.h"
#include "log/log.h"
#include "ms/ms.h"
#include "sdl-test/sdl-test.h"
#include "sdl/sdl.h"
#include "timestamp/timestamp.h"

TEST t_sdl_test2(){
  PASS();
}

TEST t_sdl_test1(){
//  require(sdl)->screenshot
  PASS();
}

SUITE(s_sdl_test) {
  RUN_TEST(t_sdl_test1);
  if (isatty(STDOUT_FILENO))
    RUN_TEST(t_sdl_test2);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_sdl_test);
  GREATEST_MAIN_END();
}
