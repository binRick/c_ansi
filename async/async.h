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
enum async_log_mode_t {
  ASYNC_LOG_MODE_NONE = 1,
  ASYNC_LOG_MODE_ERROR,
  ASYNC_LOG_MODE_INFO,
  ASYNC_LOG_MODE_DEBUG,
  ASYNC_LOG_MODES_QTY,
};

module(async) {
  define(async, CLIB_MODULE);
  module(async_each) {
    struct Vector *(*vec)(size_t concurrency, struct Vector *items, async_worker_cb cb);
    void **(*arr)(size_t concurrency, void **items,size_t qty, async_worker_cb cb);

  }*each;
  struct Vector *(*async_chan_items_v)(size_t concurrency, struct Vector *items, async_worker_cb cb);
  void **(*async_chan_items)(size_t concurrency, void **items, int in_qty, int *out_qty, async_worker_cb cb);
  void **(*async_chan_bufs)(size_t concurrency, void **items, size_t item_len, int in_qty, int *out_qty, async_worker_cb cb);
  enum async_log_mode_t log_mode;
};

int async_init(module(async) *exports);
void async_deinit(module(async) *exports);
struct Vector *__async_each_vec(size_t concurrency, struct Vector *items, async_worker_cb cb);
struct Vector *async_chan_items_v(size_t concurrency, struct Vector *items, async_worker_cb cb);
void **async_chan_items(size_t concurrency, void **items, int in_qty, int *out_qty, async_worker_cb cb);
void **async_chan_bufs(size_t concurrency, void **items, size_t item_len, int in_qty, int *out_qty, async_worker_cb cb);
void ** __async_each_arr(size_t concurrency, void **items,size_t qty, async_worker_cb cb);

exports(async) {
  .log_mode = ASYNC_LOG_MODE_NONE,
  .init     = async_init,
  .deinit   = async_deinit,
};

#define async_m    module(async)

#endif
