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
#define async_each      async_chan_items
#define async_each_v    async_chan_items_v

typedef void *(^async_worker_cb)(void *);
struct Vector *async_chan_items_v(size_t concurrency, struct Vector *items, async_worker_cb cb);
void **async_chan_items(size_t concurrency, void **items, int in_qty, int *out_qty, async_worker_cb cb);
void **async_chan_bufs(size_t concurrency, void **items, size_t item_len, int in_qty, int *out_qty, async_worker_cb cb);
struct Vector *async_items_v(size_t concurrency, struct Vector *items, async_worker_cb cb);

typedef struct MapIterator MapIterator;
typedef bool (*iterator_f)(void *);
typedef bool (^iterator_b)(void *);
typedef union {
  iterator_f *f;
  iterator_b *b;
} iterator_cb;
struct iterator_t {
  iterator_cb cb;
};
typedef struct {
  struct Vector *items, *results;
} AsyncCommon;
typedef struct {
  AsyncCommon common;
  size_t      concurrency;
} AsyncMap;
typedef struct {
  AsyncCommon common;
} AsyncSeries;
typedef struct {
  AsyncCommon common;
} AsyncWaterfall;

#define Iterator_IFACE    vfunc(bool, iterate, VSelf, struct Vector *, iterator_cb *)
interface(Iterator);

bool WaterfallIterator_iterate(struct Vector *, iterator_cb *);
declImplExtern(Iterator, WaterfallIterator);

bool MapIterator_iterate(struct Vector *, iterator_cb *);
declImplExtern(Iterator, MapIterator);

bool SeriesIterator_iterate(struct Vector *, iterator_cb *);
declImplExtern(Iterator, SeriesIterator);

typedef void *(^async_iterator)(size_t index, size_t qty, void *item);
typedef void *(^wi_async_iterator)(size_t index, size_t qty, void *item, void *res);
#define ASYNC_IFACE                                    \
  vfunc(bool, iterate, VSelf, async_iterator iterator) \
  vfunc(bool, load, VSelf, struct Vector *items)
interface(ASYNC);

AsyncMap *AsyncMap_load(struct Vector *items);
AsyncSeries *AsyncSeries_load(struct Vector *items);
AsyncWaterfall *AsyncWaterfall_load(struct Vector *items);

struct Vector *AsyncMap_iterate(VSelf, async_iterator iterator, size_t concurrency);
struct Vector *AsyncSeries_iterate(VSelf, async_iterator iterator);
void          *AsyncWaterfall_iterate(VSelf, wi_async_iterator iterator);

declImplExtern(ASYNC, AsyncMap);
declImplExtern(ASYNC, AsyncSeries);
declImplExtern(ASYNC, AsyncWaterfall);

#endif
