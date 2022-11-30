#pragma once
#ifndef CHESS_H
#define CHESS_H
//////////////////////////////////////
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
////////////////////////////////////////////
#include "b64.c/b64.h"
#include "map_macro/map.h"
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
enum pieceType { Rook   = 'r',
                 Knight = 'n',
                 Bishop = 'b',
                 Queen  = 'q',
                 King   = 'k',
                 Pawn   = 'p',
                 Empty  = ' ' };
enum pieceColor { White = 'w',
                  Black = 'b' };
struct boardElement {
  int             x, y;
  enum pieceType  piece;
  enum pieceColor color;
};

struct chess_fen_t {
  char *text;
  char *player;
  char *best;
  bool valid, over;
};


module(chess) {
  define(chess, CLIB_MODULE);
  const char *svg_template;
  module(chess_stockfish){
    char *(*exec)(const char *cmd);
    char *(*fen)(const char *fen);
  } *stockfish;
  module(chess_fen){
    char          *(*move)(const char *fen);
    unsigned char *(*svg)(const char *fen, size_t *len);
    unsigned char *(*png)(const char *fen, size_t *len);
    char          *(*cmd)(const char *fen, int depth);
    module(chess_fen_image){
      unsigned char *(*buffer)(char *fen, char *fmt, size_t *len);
      char          *(*ansi)(char *fen);
    } *image;
    module(chess_fen_score){
      int (*black)(char *fen);
      int (*white)(char *fen);
    } *score;
    char *(*stats)(const char *fen);
    module(chess_fen_is){
      module(chess_fen_is_move){
        bool (*white)(char *fen);
        bool (*black)(char *fen);
      } *move;
      bool (*valid)(const char *fen);
      bool (*over)(const char *fen);
    } *is;
    module(chess_fen_get){
      char *(*best)(const char *fen);
      char *(*move)(const char *fen);
      char **(*moves)(const char **fens, size_t fens_qty, size_t *moves_qty);
      char *(*player)(const char *fen);
    } *get;
    struct chess_fen_t (*load)(const char *fen);
    struct chess_fen_t *cur;
  } *fen;
  struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *surface;
    struct {
      char *text;
      bool (*load)(const char *fen);
    } fen;
    void (*init)(void);
    void (*loop)(void);
  } sdl;
  void (*chessterm)(char *fen);
};

int  __chess_init(module(chess) * exports);
void __chess_deinit(module(chess) * exports);
void __chessterm(char *fen);
void __chess_sdl_init(void);
void __chess_sdl_loop(void);
bool __chess_sdl_fen_load(const char *fen);

exports(chess) {
  .init      = __chess_init,
  .deinit    = __chess_deinit,
  .chessterm = __chessterm,
  .sdl.init=__chess_sdl_init,
  .sdl.loop=__chess_sdl_loop,
  .sdl.fen.load=__chess_sdl_fen_load,
};

#define chess_m    module(chess)

#endif
