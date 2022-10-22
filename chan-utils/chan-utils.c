#pragma once
#ifndef CHAN_UTILS_C
#define CHAN_UTILS_C
#define LOCAL_DEBUG_MODE    CHAN_UTILS_DEBUG_MODE
////////////////////////////////////////////
#include "chan-utils/chan-utils.h"
#include "module/require.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "ms/ms.h"
#include "timestamp/timestamp.h"

////////////////////////////////////////////
static bool CHAN_UTILS_DEBUG_MODE = false;
///////////////////////////////////////////////////////////////////////
static void __attribute__((constructor)) __constructor__chan_utils(void){
  if (getenv("DEBUG") != NULL || getenv("DEBUG_chan_utils") != NULL) {
    log_debug("Enabling chan_utils Debug Mode");
    CHAN_UTILS_DEBUG_MODE = true;
  }
}
static const cu_run_t cu_run = ^bool(CU_RUN_ARGS){
  char *msg;
  asprintf(&msg,"Running %lu items with concurrency %lu", vector_size(req->items),req->concurrency);
  fprintf(stdout, "%s\n",msg);
  req->threads[req->concurrency];
  for(size_t i=0;i<req->concurrency;i++){
    asprintf(&msg,"\t- Creating queue #%lu", i);
    fprintf(stdout, "%s\n",msg);
    req->queues[i] = workqueue_new();
    printf("Queue Size: %zu Backlog Size: %zu\n", workqueue_get_queue_size(req->queues[i]), workqueue_get_backlog_size(req->queues[i]));
  }
  for(size_t i=0;i<req->concurrency;i++){
    if (!workqueue_push(req->queues[i], work_fn, (void*)(req->args))){
      fprintf(stderr, "Failed to push work function to queue\n");
      exit(1);
    }    
  }
  for(size_t i=0;i<req->concurrency;i++){
    asprintf(&msg,"\t- Starting reader thread #%lu", i);
    fprintf(stdout, "%s\n",msg);
  }
  for(size_t i=0;i<req->concurrency;i++){
    asprintf(&msg,"\t- Starting wait readers done thread #%lu",i);
    fprintf(stdout, "%s\n",msg);
  }
  for(size_t i=0;i<vector_size(req->items);i++){
    asprintf(&msg,"\t- Sending data to reader thread #%lu",i);
    chan_send(req->chans[CHAN_UTILS_CHAN_TYPE_CHAN],(void*)(vector_get(req->items,i)));
    fprintf(stdout, "%s\n",msg);
  }
  for(size_t i=0;i<req->concurrency;i++){
    asprintf(&msg,"\t- Closing reader chan #%lu",i);
    fprintf(stdout, "%s\n",msg);
  }
  for(size_t i=0;i<vector_size(req->items);i++){
    asprintf(&msg,"\t- Waiting for reader result msg #%lu", i);
    fprintf(stdout, "%s\n",msg);
  }
  for(size_t i=0;i<req->concurrency;i++)
    printf("Backlog Size: %zu\n", workqueue_get_backlog_size(req->queues[i]));
  for(size_t i=0;i<req->concurrency;i++)
    workqueue_drain(req->queues[i]);
  for(size_t i=0;i<req->concurrency;i++)
    printf("Backlog Size: %zu\n", workqueue_get_backlog_size(req->queues[i]));
  for(size_t i=0;i<req->concurrency;i++)
    workqueue_release(req->queues[i]);  
  return(true);
};

void work_fn(void *){

}

void cu_chans_receive(void *RECV){
  struct chan_utils_receive_t *recv = (struct chan_utils_receive_t*)RECV;
  void **msg;
  while (chan_recv(recv->chans[CHAN_UTILS_CHAN_TYPE_CHAN], &msg) == 0) {
    if(msg){
      chan_send(recv->chans[CHAN_UTILS_CHAN_TYPE_ITEM_DONE],(void*)0);
    }
  }
  chan_send(recv->chans[CHAN_UTILS_CHAN_TYPE_ITEMS_DONE],(void*)0);
}
void cu_chans_start(void *REQ){
  struct chan_utils_req_t *req = (struct chan_utils_req_t*)REQ;
  for(size_t i=0;i<req->concurrency;i++){
//    pthread_create(req->recv.threads[i], NULL, req->recv.cb->fxn, (void*)(req->recv.cb->args));
  }
}
void cu_chans_send(void *REQ){
  struct chan_utils_req_t *req = (struct chan_utils_req_t*)REQ;
  for(size_t i=0;i<req->concurrency;i++){
  }
}
void cu_chan_wait(void *RECV){
  struct chan_utils_receive_t *recv = (struct chan_utils_receive_t*)RECV;
  void **msg;
  chan_recv(recv->chans[CHAN_UTILS_CHAN_TYPE_ITEMS_DONE],&msg);
}
void cu_chans_wait(void *REQ){
  struct chan_utils_req_t *req = (struct chan_utils_req_t*)REQ;
  for(size_t i=0;i<req->concurrency;i++){
    pthread_create(&(req->recv.threads[CHAN_UTILS_THREAD_TYPE_WAIT_DONE]), NULL, cu_chan_wait, (void*)0);
  }
}
/*
static const cu_concurrency_t cu_concurrency = ^ int(module(cu) *exports, size_t concurrency){
  exports->__concurrency = concurrency;
  return(EXIT_SUCCESS);
};
*/
#endif
