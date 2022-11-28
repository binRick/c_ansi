#pragma once
#ifndef CHESS_H
#define CHESS_H
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
#include "b64.c/b64.h"
//////////////////////////////////////
#include "module/def.h"
#include "module/module.h"
#include "module/require.h"
//////////////////////////////////////
enum chess_player_move_t {
  CHESS_PLAYER_MOVE_WHITE,
  CHESS_PLAYER_MOVE_BLACK,
};

module(chess) {
  define(chess, CLIB_MODULE);
  bool (*valid_fen)(const char *fen);
  const char *svg_template;
  module(chess_stockfish){
    char *(*exec)(const char **cmd,size_t qty);
    char *(*fen)(const char *fen);
  } *stockfish;
  module(chess_fen){
    char *(*move)(const char *fen);
    enum chess_player_move_t (*player)(const char *fen);
    unsigned char *(*svg)(const char *fen, size_t *len);
    unsigned char *(*png)(const char *fen, size_t *len);
    module(chess_fen_image){
      unsigned char *(*buffer)(char *fen, char *fmt, size_t *len);
    } *image;
  } *fen;
  void (*chessterm)(char *fen);
};

int __chess_init(module(chess) *exports);
void __chess_deinit(module(chess) *exports);
bool __chess_fen_valid(const char *fen);
char *__chess_exec_stockfish(const char **cmds, size_t qty);
char *__chess_exec_stockfish_fen(const char *fen);
void __chessterm(char *fen);
unsigned char *__chess_fen_image(char *fen, char *fmt, size_t *len);

exports(chess) {
  .valid_fen=__chess_fen_valid,
  .init     = __chess_init,
  .deinit   = __chess_deinit,
  .chessterm   = __chessterm,
};

#define chess_m    module(chess)

#endif
