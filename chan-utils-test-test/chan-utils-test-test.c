
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "chan-utils-test-test/chan-utils-test-test.h"
#include "chan-utils/chan-utils.h"
#include "log/log.h"
#include "ms/ms.h"
#include "timestamp/timestamp.h"
#include "chan-utils/chan-utils.h"


TEST t_chan_utils_test_test2(){
  PASS();
}

TEST t_chan_utils_test_test1(){
  module(cu) *c = require(cu);
  cu_items_done_t items_done = ^void(struct Vector *items){
    log_info("items done");
    return;
  };
  cu_item_done_t item_done = ^void(void *item){
    log_info("item done");
    return;
  };
  struct Vector *v = vector_new();
  vector_push(v,(void*)strdup("Xxxxxxx"));
  vector_push(v,(void*)strdup("Xxxxxxx"));
  vector_push(v,(void*)strdup("Xxxxxxx"));
  vector_push(v,(void*)strdup("Xxxxxxx"));
  vector_push(v,(void*)strdup("Xxxxxxx"));
  vector_push(v,(void*)strdup("Xxxxxxx"));
  struct chan_utils_req_t *req = c->new(v, 3, item_done, items_done);
  if(!c->run(req)){
    log_error("failed to run");
    FAIL();
  }

  PASS();
}

SUITE(s_chan_utils_test_test) {
  RUN_TEST(t_chan_utils_test_test1);
  if (isatty(STDOUT_FILENO)) {
    RUN_TEST(t_chan_utils_test_test2);
  }
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_chan_utils_test_test);
  GREATEST_MAIN_END();
}
