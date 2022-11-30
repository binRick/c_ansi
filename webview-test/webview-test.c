
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
#include "incbin/incbin.h"
#include "log/log.h"
#include "module/def.h"
#include "module/module.h"
#include "module/require.h"
#include "ms/ms.h"
#include "tempdir.c/tempdir.h"
#include "timestamp/timestamp.h"
#include "webview-test/webview-test.h"
#include "which/src/which.h"
#include "webview/webview.h"

TEST t_webview_test2(){
  PASS();
}

TEST t_webview_test1(){
  /*
  webview_t w = webview_create(0, NULL);
  webview_set_title(w, "Basic Example");
  webview_set_size(w, 480, 320, WEBVIEW_HINT_NONE);
  webview_set_html(w, "Thanks for using webview!");
  webview_run(w);
  webview_destroy(w);
  */

  PASS();
}

SUITE(s_webview_test) {
  RUN_TEST(t_webview_test1);
  if (isatty(STDOUT_FILENO))
    RUN_TEST(t_webview_test2);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_webview_test);
  GREATEST_MAIN_END();
}
