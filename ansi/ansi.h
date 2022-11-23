#pragma once
#ifndef ANSI_H
#define ANSI_H
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
#include "module/module.h"
#include "module/require.h"
#include "module/def.h"

// Module Type Interface
module(ansi) {
  define(ansi, CLIB_MODULE);
  void (*info)(char *);
  void (*debug)(char *);
  void (*error)(char *);
};

int
ansi_init(module(ansi) *exports);

void
ansi_deinit(module(ansi) *exports);

// Default Module Exports
exports(ansi) {
  .init = ansi_init,
  .deinit = ansi_deinit,
};

#endif
