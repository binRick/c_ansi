#pragma once
#ifndef CHAN_UTILS_TYPES
#define CHAN_UTILS_TYPES_H
#define CU_NEW_ARGS\
  struct Vector *items, size_t concurrency, cu_item_done_t item_done, cu_items_done_t items_done
#define CU_RUN_ARGS\
  struct chan_utils_req_t *req
#include "chan-utils/chan-utils.h"
enum chan_utils_thread_type_t {
  CHAN_UTILS_THREAD_TYPE_SEND,
  CHAN_UTILS_THREAD_TYPE_RECV,
  CHAN_UTILS_THREAD_TYPE_RECV_DONE,
  CHAN_UTILS_THREAD_TYPE_WAIT_DONE,
  CHAN_UTILS_THREAD_TYPE_ERROR,
  CHAN_UTILS_THREAD_TYPES_QTY,
};
enum chan_utils_chan_type_queue_t {
  CHAN_UTILS_QUEUE_TYPE_SEND,
  CHAN_UTILS_QUEUE_TYPE_RECV,
  CHAN_UTILS_QUEUE_TYPE_WAIT,
  CHAN_UTILS_QUEUE_TYPES_QTY,
};
enum chan_utils_chan_type_chan_t {
  CHAN_UTILS_CHAN_TYPE_CHAN,
  CHAN_UTILS_CHAN_TYPE_ITEM_DONE,
  CHAN_UTILS_CHAN_TYPE_ITEMS_DONE,
  CHAN_UTILS_CHAN_TYPE_ERROR,
  CHAN_UTILS_CHAN_TYPES_QTY,
};
enum chan_utils_type_t {
  CHAN_UTILS_TYPES_QTY,
};
typedef void (*chan_utils_fxn_t)(void);
typedef void (^chan_utils_block_t)(void);
typedef void (^cu_item_done_t)(void *item);
typedef void (^cu_items_done_t)(struct Vector *items);
typedef  struct chan_utils_req_t *(^cu_new_t)(CU_NEW_ARGS);
typedef  bool (^cu_run_t)(CU_RUN_ARGS);
typedef int (^cu_concurrency_t)(size_t concurrency);
typedef int (^cu_items_t)(struct Vector *items);
union chan_utils_cb_t {
  struct {
    chan_utils_fxn_t *fxn;
  } fxn;
  struct {
    chan_utils_block_t *block;
  } block;
  unsigned long init, started, start_dur, dur;
  void *args;
};

struct chan_utils_receive_t {
  chan_t *chans[CHAN_UTILS_CHAN_TYPES_QTY];
  pthread_t *threads[CHAN_UTILS_THREAD_TYPES_QTY];
  struct WorkQueue *queues[CHAN_UTILS_TYPES_QTY];
  pthread_mutex_t *mutex;
  union chan_utils_cb_t *cb;
};
struct chan_utils_req_t { 
  struct chan_utils_receive_t recv;
  chan_t *chans[CHAN_UTILS_CHAN_TYPES_QTY];
  pthread_t threads[CHAN_UTILS_THREAD_TYPES_QTY];
  struct WorkQueue *queues[CHAN_UTILS_TYPES_QTY];
  pthread_mutex_t mutex;
  void *args;
  size_t concurrency;
  struct Vector *items;
  union chan_utils_cb_t cb;
  cu_item_done_t item_done;
  cu_items_done_t items_done;
};
struct chan_utils_res_t {
  struct chan_utils_req_t *req;
};
struct chan_utils_req_t *cu_init_res(struct chan_utils_req_t *req){
  struct chan_utils_res_t *res = calloc(1,sizeof(struct chan_utils_res_t));
  res->req=req;
  return(res);
}


#endif
