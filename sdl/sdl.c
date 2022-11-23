#pragma once
#ifndef SDL_C
#define SDL_C
#define LOCAL_DEBUG_MODE    SDL_DEBUG_MODE
////////////////////////////////////////////
#include "sdl/sdl.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "module/def.h"
#include "module/module.h"
#include "module/require.h"
#include "ms/ms.h"
#include "timestamp/timestamp.h"
#include "vips/vips.h"
#include <SDL2/SDL.h>
////////////////////////////////////////////
static bool SDL_DEBUG_MODE = false;

void __sdl_screenshot(module(sdl) *exports, SDL_Renderer *renderer, const char *filename) {
  int width  = 0;
  int height = 0;

  SDL_GetRendererOutputSize(renderer, &width, &height);

  SDL_Surface *screenshot = SDL_CreateRGBSurface(
    0, width, height, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);

  SDL_RenderReadPixels(
    renderer, NULL, SDL_PIXELFORMAT_ARGB8888, screenshot->pixels,
    screenshot->pitch);
  SDL_SaveBMP(screenshot, filename);
  SDL_FreeSurface(screenshot);
}

int sdl_init(module(sdl) *exports) {
  clib_module_init(sdl, exports);
  return(0);
}

void sdl_deinit(module(sdl) *exports)      {
  clib_module_deinit(sdl);
}
///////////////////////////////////////////////////////////////////////
static void __attribute__((constructor)) __constructor__sdl(void){
  if (getenv("DEBUG") != NULL || getenv("DEBUG_sdl") != NULL) {
    log_debug("Enabling sdl Debug Mode");
    SDL_DEBUG_MODE = true;
  }
}
////////////////////////////////////////////
#undef LOCAL_DEBUG_MODE

void screenshot(SDL_Renderer *renderer, const char *filename) {
  int width  = 0;
  int height = 0;

  SDL_GetRendererOutputSize(renderer, &width, &height);

  SDL_Surface *screenshot = SDL_CreateRGBSurface(
    0, width, height, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);

  SDL_RenderReadPixels(
    renderer, NULL, SDL_PIXELFORMAT_ARGB8888, screenshot->pixels,
    screenshot->pitch);
  SDL_SaveBMP(screenshot, filename);
  SDL_FreeSurface(screenshot);
}

#endif
