#pragma once
#ifndef ASYNC_C
#define ASYNC_C
////////////////////////////////////////////
#include "../async/async.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_eventemitter/include/eventemitter.h"
#include "c_workqueue/include/workqueue.h"
#include "c_fsio/include/fsio.h"
#include "clamp/clamp.h"
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
#include "which/src/which.h"
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
void ** __async_each_arr(size_t concurrency, void **items,size_t qty, async_worker_cb cb){

  return(NULL);
}
void **__async_filter_arr__queued(size_t concurrency, struct Vector *items, async_worker_cb cb, size_t bufs_qty){
}
void **__async_filter_bufs__queued(size_t concurrency, struct Vector *items, async_worker_cb cb, size_t bufs_qty){
}
void **__async_filter_arr__workqueue(size_t concurrency, struct Vector *items, async_worker_cb cb, size_t bufs_qty){
}
void **__async_filter_bufs__workqueue(size_t concurrency, struct Vector *items, async_worker_cb cb, size_t bufs_qty){
}
void **__async_each_arr__queued(size_t concurrency, struct Vector *items, async_worker_cb cb, size_t bufs_qty){
}
void **__async_each_bufs__queued(size_t concurrency, struct Vector *items, async_worker_cb cb, size_t bufs_qty){
}
void **__async_each_arr__workqueue(size_t concurrency, struct Vector *items, async_worker_cb cb, size_t bufs_qty){
}
void **__async_each_bufs__workqueue(size_t concurrency, struct Vector *items, async_worker_cb cb, size_t bufs_qty){
}
struct Vector *__async_filter_vec__chan(size_t concurrency, struct Vector *items, async_worker_cb cb){

}
struct Vector *__async_each_vec__queued(size_t concurrency, struct Vector *items, async_worker_cb cb){
  Dn(concurrency);
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
////////////////////////////////////////////
int async_init(module(async) *exports) {
  clib_module_init(async, exports);
  return(0);

  exports->each = calloc(1,sizeof(module(async_each)));
  exports->each->queued = calloc(1,sizeof(module(async_each_queued)));
  exports->each->chan = calloc(1,sizeof(module(async_each_chan)));
  exports->filter->queued = calloc(1,sizeof(module(async_each_queued)));
  exports->filter->chan = calloc(1,sizeof(module(async_each_chan)));
  exports->each->queued->bufs=__async_each_bufs__queued;
  exports->each->queued->arr=__async_each_arr__queued;
  exports->each->queued->vec=__async_each_vec__queued;
  exports->each->chan->bufs=__async_each_bufs__queued;
  exports->each->chan->arr=__async_each_arr__queued;
  exports->each->chan->vec=__async_each_vec__queued;
  exports->each->arr=__async_each_arr__queued;
  exports->each->vec=__async_each_vec__queued;
  exports->each->arr=__async_each_arr__queued;
  Ds("kk");
  return(EXIT_SUCCESS);
}

void async_deinit(module(async) *exports) {
  free(exports->each);
  free(exports->each->queued);
  free(exports->each->chan);
  free(exports->filter->chan);
  free(exports->filter->queued);
  clib_module_deinit(async);
}
////////////////////////////////////////////
#endif
