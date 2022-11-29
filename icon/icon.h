#pragma once
#ifndef ICON_H
#define ICON_H
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

module(icon) {
  define(icon, CLIB_MODULE);
};

int  icon_init(module(icon) * exports);
void icon_deinit(module(icon) * exports);

exports(icon) {
  .init   = icon_init,
  .deinit = icon_deinit,
};

#define icon_m    module(icon)

#endif
