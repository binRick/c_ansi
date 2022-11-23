
[35m#include[0m [32m"[0m[32mansi-codes/ansi-codes.h[0m[32m"[0m
[35m#include[0m [32m"[0m[32mbytes/bytes.h[0m[32m"[0m
[35m#include[0m [32m"[0m[32mc_fsio/include/fsio.h[0m[32m"[0m
[35m#include[0m [32m"[0m[32mc_greatest/greatest/greatest.h[0m[32m"[0m
[35m#include[0m [32m"[0m[32mc_string_buffer/include/stringbuffer.h[0m[32m"[0m
[35m#include[0m [32m"[0m[32mc_stringfn/include/stringfn.h[0m[32m"[0m
[35m#include[0m [32m"[0m[32mc_vector/vector/vector.h[0m[32m"[0m
[35m#include[0m [32m"[0m[32mlog/log.h[0m[32m"[0m
[35m#include[0m [32m"[0m[32mlove-test/love-test.h[0m[32m"[0m
[35m#include[0m [32m"[0m[32mlove/love.h[0m[32m"[0m
[35m#include[0m [32m"[0m[32mms/ms.h[0m[32m"[0m
[35m#include[0m [32m"[0m[32mtimestamp/timestamp.h[0m[32m"[0m
[35m#include[0m [32m"[0m[32mmodule/require.h[0m[32m"[0m
[35m#include[0m [32m"[0m[32mmodule/module.h[0m[32m"[0m
[35m#include[0m [32m"[0m[32mincbin/incbin.h[0m[32m"[0m
module(love)[35m*[0mlove;
TEST [34mt_love_test2[0m(){
  PASS();
}

TEST [34mt_love_test1[0m(){
  love [35m=[0m require(love);
  Ds(love->test());
  PASS();
}

SUITE(s_love_test) {
  RUN_TEST(t_love_test1);
  [35mif[0m (isatty(STDOUT_FILENO))
    RUN_TEST(t_love_test2);
}

GREATEST_MAIN_DEFS();

[35mint[0m [34mmain[0m([35mint[0m argc, [35mchar[0m [35m*[0m[35m*[0margv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_love_test);
  GREATEST_MAIN_END();
}
