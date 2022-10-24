#pragma once
#ifndef CHAN_MODULE_H
#define CHAN_MODULE_H
#include "chan-utils/chan-utils.h"
#include "chan-utils/chan-utils-types.h"
module(cu) {
  define(cu, CLIB_MODULE);
  struct chan_utils_req_t *req;
  struct chan_utils_req_t *res;
  size_t __concurrency;
  struct Vector *__items;
  struct chan_utils_req_t *(^new)(CU_NEW_ARGS);
  bool(^run)(CU_RUN_ARGS);
  CU_EACH_RET(^each)(CU_EACH_ARGS);
  CU_MAP_RET(^map)(CU_MAP_ARGS);
  CU_MAP_LIMIT_RET(^map_limit)(CU_MAP_ARGS);
};
int cu_init(module(cu) *exports);
int cu_deinit(module(cu) *exports);
exports(cu) {
//  .new = cu_new,
//  .run = cu_run,
};


#endif
