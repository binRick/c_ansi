#pragma once
#ifndef ASYNC_C
#define ASYNC_C
#define LOCAL_DEBUG_MODE    ASYNC_DEBUG_MODE
////////////////////////////////////////////
#include "async/async.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "c_workqueue/include/workqueue.h"
#include "chan/src/chan.h"
#include "chan/src/queue.h"
#include "clamp/clamp.h"
#include "log/log.h"
#include "ms/ms.h"
#include "timestamp/timestamp.h"
////////////////////////////////////////////
static bool ASYNC_DEBUG_MODE = false;
static void __attribute__((constructor)) __constructor__async(void);
////////////////////////////////////////////
struct async_chan_work_t {
  async_worker_cb cb;
  void            *args;
  chan_t          *done, *work;
};
struct async_work_t {
  async_worker_cb cb;
  void            *args;
  struct Vector   *results_v;
  pthread_mutex_t mutex;
};
struct async_recv_t {
  size_t          qty;
  chan_t          *chan;
  struct Vector   *recvd;
  pthread_mutex_t mutex;
};

struct async_work_chans_t {
  chan_t *work, *done;
};

void async_chan_work_fxn(void *VOID){
  struct async_work_chans_t *chans = (struct async_work_chan_t *)VOID;
  struct async_chan_work_t  *w;

  while (chan_recv(chans->work, &w) == 0) {
    void *result;
    if (w->cb && w->args && (result = w->cb((void *)(w->args))))
      chan_send(chans->done, (void *)(result));
    free(w);
  }
}

void async_work_fxn(void *WORK){
  struct async_work_t *w = (struct async_work_t *)WORK;
  void                *result;

  result = w->cb((void *)(w->args));
  pthread_mutex_lock(&(w->mutex));
  vector_push(w->results_v, (void *)result);
  pthread_mutex_unlock(&(w->mutex));
}

void **async_chan_bufs(size_t concurrency, void **items, size_t item_len, int in_qty, int *out_qty, async_worker_cb cb){
  chan_t                    *done      = chan_init(vector_size(items));
  struct Vector             *results_v = vector_new();
  struct async_work_chans_t *chans[concurrency];

  concurrency = clamp(concurrency, 1, vector_size(items));
  pthread_t threads[concurrency];

  for (size_t i = 0; i < concurrency; i++) {
    chans[i]       = calloc(1, sizeof(struct async_work_chans_t));
    chans[i]->work = chan_init(concurrency);
    chans[i]->done = done;
    pthread_create(&(threads[i]), 0, async_chan_work_fxn, (void *)(chans[i]));
  }
  int  idx;
  void *r;

  for (size_t ii = 0; ii < vector_size(items); ii++) {
    struct async_chan_work_t *w = calloc(1, sizeof(struct async_chan_work_t));
    w->cb   = cb;
    w->args = (void *)(vector_get(items, ii));
    chan_send_buf(chans[ii % concurrency]->work, (void *)(items[ii]), item_len);
  }
}

void **async_chan_items(size_t concurrency, void **items, int in_qty, int *out_qty, async_worker_cb cb){
  size_t        qty = 0;
  struct Vector *v = vector_new(), *r;

  for (int i = 0; i < in_qty; i++)
    vector_push(v, items[i]);
  r        = async_chan_items_v(concurrency, v, cb);
  *out_qty = vector_size(r);
  return(vector_to_array(v));
}
struct Vector *async_chan_items_v(size_t concurrency, struct Vector *items, async_worker_cb cb){
  chan_t                    *done      = chan_init(vector_size(items));
  struct Vector             *results_v = vector_new();
  struct async_work_chans_t *chans[concurrency];

  concurrency = clamp(concurrency, 1, vector_size(items));
  pthread_t threads[concurrency];

  for (size_t i = 0; i < concurrency; i++) {
    chans[i]       = calloc(1, sizeof(struct async_work_chans_t));
    chans[i]->work = chan_init(concurrency);
    chans[i]->done = done;
    pthread_create(&(threads[i]), 0, async_chan_work_fxn, (void *)(chans[i]));
  }
  int  idx;
  void *r;

  for (size_t ii = 0; ii < vector_size(items); ii++) {
    struct async_chan_work_t *w = calloc(1, sizeof(struct async_chan_work_t));
    w->cb   = cb;
    w->args = (void *)(vector_get(items, ii));
    chan_send(chans[ii % concurrency]->work, (void *)w);
  }
  for (size_t i = 0; i < concurrency; i++)
    chan_close(chans[i]->work);
  for (size_t i = 0; i < concurrency; i++)
    pthread_join(&(threads[i]), 0);
  while (vector_size(results_v) < vector_size(items) && chan_recv(done, &r) == 0)
    vector_push(results_v, (void *)r);

  chan_close(done);
  chan_dispose(done);
  for (size_t i = 0; i < concurrency; i++) {
    chan_dispose(chans[i]->work);
    free(chans[i]);
  }

  return(results_v);
}
struct Vector *async_items_v(size_t concurrency, struct Vector *items, async_worker_cb cb){
  struct Vector    *results_v = vector_new();
  struct WorkQueue *queues[concurrency];

  for (size_t i = 0; i < concurrency; i++)
    queues[i] = workqueue_new();

  for (size_t ii = 0; ii < vector_size(items); ii++) {
    struct async_work_t *w = calloc(1, sizeof(struct async_work_t));
    w->cb        = cb;
    w->results_v = results_v;
    w->args      = (void *)vector_get(items, ii);
    workqueue_push(queues[ii % concurrency], async_work_fxn, (void *)w);
  }
  for (size_t i = 0; i < concurrency; i++)
    workqueue_drain(queues[i]);
  for (size_t i = 0; i < concurrency; i++)
    workqueue_release(queues[i]);

  return(results_v);
}

AsyncSeries *AsyncSeries_load(struct Vector *items){
  AsyncSeries *self = calloc(1, sizeof(AsyncSeries));

  self->common.items = items;
  return(self);
}

AsyncWaterfall *AsyncWaterfall_load(struct Vector *items){
  AsyncSeries *self = calloc(1, sizeof(AsyncWaterfall));

  self->common.items = items;
  return(self);
}

AsyncMap *AsyncMap_load(struct Vector *items){
  AsyncSeries *self = calloc(1, sizeof(AsyncMap));

  self->common.items = items;
  log_info("Loaded %lu Items", vector_size(self->common.items));
  return(self);
}

struct Vector *AsyncSeries_iterate(VSelf, async_iterator iterator){
  VSELF(AsyncSeries);
  log_info("Series Iterating %lu Items", vector_size(self->common.items));
  self->common.results = vector_new();
  for (size_t i = 0; i < vector_size(self->common.items); i++)
    vector_push(self->common.results, iterator(i, vector_size(self->common.items), (void *)(vector_get(self->common.items, i))));
  return(self->common.results);
}

void *AsyncWaterfall_iterate(VSelf, wi_async_iterator iterator){
  VSELF(AsyncWaterfall);
  log_info("Waterfall Iterating %lu Items", vector_size(self->common.items));
  void *res = NULL;
  self->common.results = vector_new();
  for (size_t i = 0; i < vector_size(self->common.items); i++) {
    res = iterator(i, vector_size(self->common.items), (void *)(vector_get(self->common.items, i)), res);
    vector_push(self->common.results, res);
  }
  return(self->common.results);
}

struct Vector *AsyncMap_iterate(VSelf, async_iterator iterator, size_t concurrency){
  VSELF(AsyncMap);
  log_info("Map Iterating %lu Items", vector_size(self->common.items));
  self->common.results = vector_new();
  self->concurrency    = concurrency;

  struct WorkQueue *queues[self->concurrency];
  for (size_t wq = 0; wq < self->concurrency; wq++) {
    queues[wq] = workqueue_new_with_options(vector_size(self->common.items), NULL);
    log_info("Queue Size: %zu Backlog Size: %zu\n", workqueue_get_queue_size(queues[wq]), workqueue_get_backlog_size(queues[wq]));
  }
  for (size_t wq = 0; wq < self->concurrency; wq++)
    printf("Backlog Size: %zu\n", workqueue_get_backlog_size(queues[wq]));
  for (size_t wq = 0; wq < self->concurrency; wq++)
    workqueue_drain(queues[wq]);
  for (size_t wq = 0; wq < self->concurrency; wq++)
    printf("Backlog Size: %zu\n", workqueue_get_backlog_size(queues[wq]));
  for (size_t wq = 0; wq < self->concurrency; wq++)
    workqueue_release(queues[wq]);

  for (size_t i = 0; i < vector_size(self->common.items); i++)
    vector_push(self->common.results, iterator(i, vector_size(self->common.items), (void *)(vector_get(self->common.items, i))));
  return(self->common.results);
}
implExtern(ASYNC, AsyncSeries);
implExtern(ASYNC, AsyncWaterfall);
implExtern(ASYNC, AsyncMap);
static void __attribute__((constructor)) __constructor__async(void){
  if (getenv("DEBUG") != NULL || getenv("DEBUG_async") != NULL) {
    log_debug("Enabling async Debug Mode");
    ASYNC_DEBUG_MODE = true;
  }
}
#undef LOCAL_DEBUG_MODE
#endif
