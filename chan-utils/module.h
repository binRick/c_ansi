#pragma once
#ifndef CHAN_MODULE_H
#define CHAN_MODULE_
#include "chan-utils/chan-utils.h"
module(cu) {
  define(cu, CLIB_MODULE);
  struct chan_utils_req_t *req;
  struct chan_utils_req_t *res;
  size_t __concurrency;
  struct Vector *__items;
  struct chan_utils_req_t *(^new)(CU_NEW_ARGS);
  bool(^run)(CU_RUN_ARGS);
  int (^concurrency)(module(cu) *exports, size_t concurrency);
  int (^items)(module(cu) *exports, struct Vector *items);
};
int cu_init(module(cu) *exports);
int cu_deinit(module(cu) *exports);
/*
static const cu_items_t cu_items = ^ int(module(cu) *exports, struct Vector *items);
static const cu_items_t cu_items = ^ int(module(cu) *exports, struct Vector *items){
  exports->__items = items;
  return(EXIT_SUCCESS);
};
static const cu_concurrency_t cu_concurrency = ^ int(module(cu) *exports, size_t concurrency);
static const cu_m_t cu_run = ^ int(module(cu) *exports){
  char *msg;
  asprintf(&msg,"Running %lu Items with Concurrency %lu", vector_size(exports->__items),exports->__concurrency);
  fprintf(stdout, "%s\n",msg);
  return(EXIT_SUCCESS);
};
*/
//static const cu_run_t cu_run = ^bool(CU_RUN_ARGS);
#include "chan-utils/chan-utils-static.c"
exports(cu) {
//  .new = cu_new,
  .run = cu_run,
};


#endif
