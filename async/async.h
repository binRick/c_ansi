#pragma once
#ifndef ASYNC_H
#define ASYNC_H
//////////////////////////////////////
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//////////////////////////////////////
#include "c_vector/vector/vector.h"
#include "c_workqueue/include/workqueue.h"
#include "chan/src/chan.h"
#include "chan/src/queue.h"
#include "interface99/interface99.h"
#include "module/def.h"
#include "module/module.h"
#include "module/require.h"
#define async_each      async_chan_items
#define async_each_v    async_chan_items_v

typedef void *(^async_worker_cb)(void *);
struct Vector *async_chan_items_v(size_t concurrency, struct Vector *items, async_worker_cb cb);
void **async_chan_items(size_t concurrency, void **items, int in_qty, int *out_qty, async_worker_cb cb);
void **async_chan_bufs(size_t concurrency, void **items, size_t item_len, int in_qty, int *out_qty, async_worker_cb cb);
struct Vector *async_items_v(size_t concurrency, struct Vector *items, async_worker_cb cb);

#endif
