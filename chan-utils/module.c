#pragma once
#ifndef CHAN_MODULE_C
#define CHAN_MODULE_C
#include "chan-utils/module.h"

void cu_deinit(module(cu) *exports) {
  return;
}

int cu_init(module(cu) *exports) {
  clib_module_init(cu, exports);
  return 0;
}


#endif
