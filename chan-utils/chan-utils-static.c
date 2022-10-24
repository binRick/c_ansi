#pragma once
#ifndef CHAN_UTILS_STATIC_C
#define CHAN_UTILS_STATIC_C
#include "chan-utils/chan-utils.h"
static const cu_new_t cu_new = ^bool(CU_NEW_ARGS){
  struct chan_utils_req_t *req = calloc(1,sizeof(chan_utils_req_t));
  return(req);
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

#endif
