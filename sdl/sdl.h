#pragma once
#ifndef SDL_H
#define SDL_H
//////////////////////////////////////
#include "module/def.h"
#include "module/def.h"
#include "module/module.h"
#include "module/require.h"
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <unistd.h>

module(sdl) {
  define(sdl, CLIB_MODULE);
  bool (*open)(int width, int height);
  bool (*resize)(int window_id);
  bool (*move)(int window_id);
  bool (*position)(int window_id);
  module(sdl_utils) {
    module(sdl_utils_win) {
    } *win;
  } *utils;
  void (*screenshot)(module(sdl) *exports, SDL_Renderer *renderer, const char *filename);
};

int  sdl_init(module(sdl) * exports);
void __sdl_screenshot(module(sdl) * exports, SDL_Renderer * renderer, const char *filename);

void sdl_deinit(module(sdl) * exports);

exports(sdl) {
  .init       = sdl_init,
  .deinit     = sdl_deinit,
  .screenshot = __sdl_screenshot,
};
#endif
