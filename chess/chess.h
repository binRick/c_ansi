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

module(chess) {
  define(chess, CLIB_MODULE);
  const char *svg_template;
  module(chess_stockfish){
    char *(*exec)(const char *cmd);
    char *(*fen)(const char *fen);
  } *stockfish;
  module(chess_fen){
    char *(*move)(const char *fen);
    unsigned char *(*svg)(const char *fen, size_t *len);
    unsigned char *(*png)(const char *fen, size_t *len);
    bool (*print)(const char *fen);
    char *(*cmd)(const char *fen,int depth);
    module(chess_fen_image){
      unsigned char *(*buffer)(char *fen, char *fmt, size_t *len);
      char *(*ansi)(char *fen);
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
      char *(*move)(const char *fen);
      char *(*player)(const char *fen);
    } *get;
  } *fen;
  void (*chessterm)(char *fen);
};

int __chess_init(module(chess) *exports);
void __chess_deinit(module(chess) *exports);
char *__chess_exec_stockfish(const char *cmd);
char *__chess_exec_stockfish_fen(const char *fen);
void __chessterm(char *fen);
unsigned char *__chess_fen_image(char *fen, char *fmt, size_t *len);

exports(chess) {
  .init     = __chess_init,
  .deinit   = __chess_deinit,
  .chessterm   = __chessterm,
};

#define chess_m    module(chess)

#endif
