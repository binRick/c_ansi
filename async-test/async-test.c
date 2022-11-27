
#include "ansi-codes/ansi-codes.h"
#include "async-test/async-test.h"
#include "async/async.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "module/def.h"
#include "module/module.h"
#include "module/require.h"
#include "ms/ms.h"
#include "timestamp/timestamp.h"

TEST t_async_module1(){
  // module(async) *a= require(async);
  PASS();
}

TEST t_async_each_a(){
  unsigned long started = timestamp();
  size_t        out_qty = 0; void **res;
  char          *msg;
  struct Vector *results_v, *items_v = vector_new();
  int           concurrency = getenv("CONCURRENCY") ? atoi(getenv("CONCURRENCY")) : 5, qty = getenv("QTY") ? atoi(getenv("QTY")) : 10;

  for (int i = 0; i < qty; i++) {
    char *dat;
    asprintf(&dat, "%s", "ok123");
    vector_push(items_v, (void *)dat);
  }
  async_worker_cb cb = ^ void *(void *VOID){
    usleep(1000 * 100);
    return((void *)stringfn_to_uppercase((char *)(VOID)));
  };

  res = async_each(concurrency, vector_to_array(items_v), vector_size(items_v), &out_qty, cb);
  for (size_t i = 0; i < out_qty; i++)
    if (greatest_get_verbosity() > 1) {
      asprintf(&msg, "Result #%lu/%lu: %s", i + 1, out_qty, (char *)(res[i]));
      log_info("%s", msg);
    }
  asprintf(&msg, "Received %lu Results from %lu Items in %s",
           out_qty,
           vector_size(items_v),
           milliseconds_to_string(timestamp() - started)
           );
  PASSm(msg);
}

TEST t_async_each_v(){
  unsigned long started = timestamp();
  char          *msg;
  struct Vector *results_v, *items_v = vector_new();
  int           concurrency = getenv("CONCURRENCY") ? atoi(getenv("CONCURRENCY")) : 5, qty = getenv("QTY") ? atoi(getenv("QTY")) : 10;

  for (int i = 0; i < qty; i++) {
    char *dat;
    asprintf(&dat, "%s", "ok123");
    vector_push(items_v, (void *)dat);
  }
  async_worker_cb cb = ^ void *(void *VOID){
    void *dat;
    dat = (void *)stringfn_to_uppercase((char *)(VOID));
    return((void *)dat);
  };

  results_v = async_each_v(concurrency, items_v, cb);
  for (size_t i = 0; i < vector_size(results_v); i++)
    if (greatest_get_verbosity() > 1) {
      asprintf(&msg, "Result #%lu/%lu: %s", i + 1, vector_size(results_v), (char *)(vector_get(results_v, i)));
      log_info("%s", msg);
    }

  asprintf(&msg, "Received %lu Results from %lu Items in %s",
           vector_size(results_v),
           vector_size(items_v),
           milliseconds_to_string(timestamp() - started)
           );
  PASSm(msg);
}

TEST t_async_v(){
  struct Vector   *results_v, *items_v = vector_new();
  async_worker_cb cb = ^ void *(void *VOID){
    size_t item = (size_t)VOID;
    sleep(1);
    return((void *)(item * 2));
  };
  size_t items[] = { 1, 5, 25, 2, 4, 1, 22, 11 };

  for (size_t i = 0; i < sizeof(items) / sizeof(items[0]); i++)
    vector_push(items_v, (void *)items[i]);
  results_v = async_items_v(10, items_v, cb);
  Dbg(vector_size(results_v), %u);
  for (size_t i = 0; i < vector_size(results_v); i++)
    Dbg((size_t)vector_get(results_v, i), %u);
  PASS();
}

TEST t_async_test2(){
  struct Vector *v[3];
  struct Vector *results[30];

  for (int i = 0; i < 3; i++) {
    v[i] = vector_new();
    vector_push(v[i], (void *)(size_t)(i + 100));
    vector_push(v[i], (void *)(size_t)(500));
  }
  wi_async_iterator wi = ^ void *(size_t index, size_t qty, void *item, void *res){
    log_info("#%lu/%lu>", index + 1, qty);
    size_t s;
    if (res)
      s = (size_t)res + (size_t)item;
    else
      s = (size_t)item;
    return((void *)s);
  };
  async_iterator I = ^ void *(size_t index, size_t qty, void *item){
    log_info("#%lu/%lu>", index + 1, qty);
    size_t s;
    s = ((size_t)item) * 2;
    return((void *)s);
  };

  AsyncSeries *s = AsyncSeries_load(v[0]);

  results[0] = AsyncSeries_iterate(s, I);
  Dbg(vector_size(results[0]), %u);
  for (size_t i = 0; i < vector_size(results[0]); i++)
    Dbg((size_t)vector_get(results[0], i), %u);

  AsyncMap *m = AsyncMap_load(v[1]);

  results[1] = AsyncMap_iterate(s, I, 1);
  Dbg(vector_size(results[1]), %u);
  for (size_t i = 0; i < vector_size(results[1]); i++)
    Dbg((size_t)vector_get(results[1], i), %u);

  AsyncWaterfall *w = AsyncWaterfall_load(v[2]);

  results[2] = AsyncWaterfall_iterate(s, wi);
  Dbg(vector_size(results[2]), %u);
  for (size_t i = 0; i < vector_size(results[2]); i++)
    Dbg((size_t)vector_get(results[2], i), %u);
  PASS();
} /* t_async_test2 */

TEST t_async_test1(){
  struct Vector *v[3];
  struct Vector *results[30];

  for (int i = 0; i < 3; i++) {
    v[i] = vector_new();
    char *s;
    asprintf(&s, "%d", i);
    vector_push(v[i], (void *)s);
    vector_push(v[i], (void *)"12399");
  }
  wi_async_iterator wi = ^ void *(size_t index, size_t qty, void *item, void *res){
    log_info("#%lu/%lu>", index + 1, qty);
    char *s;
    if (res)
      asprintf(&s, "%s,%s", (char *)res, (char *)item);
    else
      s = (char *)item;
    return((char *)s);
  };
  async_iterator I = ^ void *(size_t index, size_t qty, void *item){
    log_info("#%lu/%lu>", index + 1, qty);
    char *s;
    asprintf(&s, "%s", (char *)item);
    return((void *)s);
  };

  AsyncSeries *s = AsyncSeries_load(v[0]);

  results[0] = AsyncSeries_iterate(s, I);
  Dbg(vector_size(results[0]), %u);
  for (size_t i = 0; i < vector_size(results[0]); i++)
    Dbg((char *)vector_get(results[0], i), %s);

  results[10] = AsyncSeries_iterate(s, I);
  Dbg(vector_size(results[10]), %u);
  for (size_t i = 0; i < vector_size(results[10]); i++)
    Dbg((char *)vector_get(results[10], i), %s);

  AsyncMap *m = AsyncMap_load(v[1]);

  results[1] = AsyncMap_iterate(s, I, 1);
  Dbg(vector_size(results[1]), %u);
  for (size_t i = 0; i < vector_size(results[1]); i++)
    Dbg((char *)vector_get(results[1], i), %s);

  AsyncWaterfall *w = AsyncWaterfall_load(v[2]);

  results[2] = AsyncWaterfall_iterate(s, wi);
  Dbg(vector_size(results[2]), %u);
  for (size_t i = 0; i < vector_size(results[2]); i++)
    Dbg((char *)vector_get(results[2], i), %s);

  PASS();
} /* t_async_test1 */

SUITE(s_async_chan_v) {
  RUN_TEST(t_async_each_v);
}
SUITE(s_async_chan_a) {
  RUN_TEST(t_async_each_a);
}

SUITE(s_async_v) {
  RUN_TEST(t_async_v);
}
SUITE(s_async_module) {
  RUN_TEST(t_async_module1);
}
SUITE(s_async_test) {
  RUN_TEST(t_async_test1);
  RUN_TEST(t_async_test2);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_async_v);
  RUN_SUITE(s_async_chan_v);
  RUN_SUITE(s_async_chan_a);
  RUN_SUITE(s_async_module);
  GREATEST_MAIN_END();
}
