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
#include "focus-test/focus-test.h"
#include "focus/focus.h"
#include "c_focus/src/c_focus.h"
#include "incbin/incbin.h"
#include "log/log.h"
#include "module/def.h"
#include "module/module.h"
#include "module/require.h"
#include "ms/ms.h"
#include "tempdir.c/tempdir.h"
#include "timestamp/timestamp.h"
#include "which/src/which.h"
#include "parson/parson.h"
static void print_focus_event(struct c_focus_event_t e);
static void handle_event(struct c_focus_event_t e);

static void handle_event(struct c_focus_event_t e){ return(print_focus_event(e)); }
static void print_focus_event(struct c_focus_event_t e){
  char *json=require(focus)->event.serialize(&e), *pretty=NULL;
  JSON_Value *j=NULL;
  if(json)
    if(!(j=json_parse_string(json)))
      log_error("Failed to parse json");
  if(j)
    pretty=json_serialize_to_string_pretty(j);

  if(pretty)
    fprintf(stdout,AC_YELLOW"%s"AC_RESETALL "\n",pretty);
  log_info("%ld> "
      "PID:%d|"
      "Display:%d|"
      "Space:%d|"
      "Window:%d|"
      "Name:%s|"
      "",
      e.time.timestamp,
      e.process.pid,
      e.display.id,
      e.space.id,
      e.window.id,
      e.app.name
      );
}


TEST t_focus_test_block(){
  require(focus)->block(^void(struct c_focus_event_t e){ return(print_focus_event(e)); });
  PASS();
}

TEST t_focus_test_async_callback(){
  PASS();
}

TEST t_focus_test_async_block(){
  PASS();
}

TEST t_focus_test_log(){
  require(focus)->log("/tmp/focus.log");
  PASS();
}
TEST t_focus_test_callback(){
  require(focus)->callback(handle_event);
  PASS();
}

SUITE(s_focus_test) {
  RUN_TEST(t_focus_test_callback);
  RUN_TEST(t_focus_test_block);
  RUN_TEST(t_focus_test_async_callback);
  RUN_TEST(t_focus_test_async_block);
  RUN_TEST(t_focus_test_log);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_focus_test);
  GREATEST_MAIN_END();
}
