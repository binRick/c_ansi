#pragma once
#ifndef SDL_H
#define SDL_H
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
#include "module/module.h"
#include "module/def.h"
#include "module/require.h"
#include "module/def.h"
#include <SDL2/SDL.h>
//////////////////////////////////////
// Module Type Interface
module(sdl) {
  define(sdl, CLIB_MODULE);
  void (*screenshot)(module(sdl) *exports, SDL_Renderer *renderer, const char *filename);
};

int sdl_init(module(sdl) *exports);
void __sdl_screenshot(module(sdl) *exports, SDL_Renderer *renderer, const char *filename);

void sdl_deinit(module(sdl) *exports);

exports(sdl) {
  .init = sdl_init,
  .deinit = sdl_deinit,
  .screenshot=__sdl_screenshot,
};
#endif
