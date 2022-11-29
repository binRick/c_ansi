#pragma once
#ifndef ASYNC_H
#define ASYNC_H
//////////////////////////////////////
#include <assert.h>
#include <ctype.h>
#include <err.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//////////////////////////////////////
#include "module/def.h"
#include "module/module.h"
#include "module/require.h"
//////////////////////////////////////
#define async_each      async_chan_items
#define async_each_v    async_chan_items_v
typedef void *(^async_worker_cb)(void *);

module(async) {
  define(async, CLIB_MODULE);
  module(async_each) {
    module(async_each_queued) {
      struct Vector *(*vec)(size_t concurrency, struct Vector *items, async_worker_cb cb);
      void **(*arr)(size_t concurrency, void **items, size_t qty, async_worker_cb cb);
      void **(*bufs)(size_t concurrency, void **items, size_t qty, async_worker_cb cb);
    }*queued;
    module(async_each_chan) {
      struct Vector *(*vec)(size_t concurrency, struct Vector *items, async_worker_cb cb);
      void **(*arr)(size_t concurrency, void **items, size_t qty, async_worker_cb cb);
      void **(*bufs)(size_t concurrency, void **items, size_t qty, async_worker_cb cb);
    }*chan;
    struct Vector *(*vec)(size_t concurrency, struct Vector *items, async_worker_cb cb);
    void **(*arr)(size_t concurrency, void **items,size_t qty, async_worker_cb cb);
    void **(*bufs)(size_t concurrency, void **items, size_t qty, async_worker_cb cb);
  }*each;
  module(async_filter) {
    module(async_filter_queued) {
      struct Vector *(*vec)(size_t concurrency, struct Vector *items, async_worker_cb cb);
      void **(*arr)(size_t concurrency, void **items, size_t qty, async_worker_cb cb);
    }*queued;
    module(async_filter_chan) {
      struct Vector *(*vec)(size_t concurrency, struct Vector *items, async_worker_cb cb);
      void **(*arr)(size_t concurrency, void **items, size_t qty, async_worker_cb cb);
    }*chan;
    struct Vector *(*vec)(size_t concurrency, struct Vector *items, async_worker_cb cb);
    void **(*arr)(size_t concurrency, void **items,size_t qty, async_worker_cb cb);
  }*filter;
  struct Vector *(*vec)(size_t concurrency, struct Vector *items, async_worker_cb cb);
  struct Vector *(*async_chan_items_v)(size_t concurrency, struct Vector *items, async_worker_cb cb);
  void **(*async_chan_items)(size_t concurrency, void **items, int in_qty, int *out_qty, async_worker_cb cb);
  void **(*async_chan_bufs)(size_t concurrency, void **items, size_t item_len, int in_qty, int *out_qty, async_worker_cb cb);
};

int async_init(module(async) *exports);
void async_deinit(module(async) *exports);
struct Vector *__async_each_vec(size_t concurrency, struct Vector *items, async_worker_cb cb);
struct Vector *async_chan_items_v(size_t concurrency, struct Vector *items, async_worker_cb cb);
void **async_chan_items(size_t concurrency, void **items, int in_qty, int *out_qty, async_worker_cb cb);
void **async_chan_bufs(size_t concurrency, void **items, size_t item_len, int in_qty, int *out_qty, async_worker_cb cb);
void ** __async_each_arr(size_t concurrency, void **items,size_t qty, async_worker_cb cb);

exports(async) {
  .init     = async_init,
  .deinit   = async_deinit,
};

#define async_m    module(async)

#endif
