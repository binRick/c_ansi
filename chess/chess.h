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
//////////////////////////////////////
#include "module/def.h"
#include "module/module.h"
#include "module/require.h"
//////////////////////////////////////
enum chess_log_mode_t {
  CHESS_LOG_MODE_NONE = 1,
  CHESS_LOG_MODE_ERROR,
  CHESS_LOG_MODE_INFO,
  CHESS_LOG_MODE_DEBUG,
  CHESS_LOG_MODES_QTY,
};
enum chess_player_move_t {
  CHESS_PLAYER_MOVE_WHITE,
  CHESS_PLAYER_MOVE_BLACK,
};

module(chess) {
  define(chess, CLIB_MODULE);
  enum chess_log_mode_t log_mode;
  bool (*valid_fen)(const char *fen);
  module(chess_stockfish){
    define(chess_stockfish, CLIB_MODULE);
    char *(*exec)(const char **cmd,size_t qty);
    char *(*fen)(const char *fen);
  } stockfish;
  module(chess_fen){
    define(chess_fen, CLIB_MODULE);
    char *(*move)(const char *fen);
    enum chess_player_move_t (*player)(const char *fen);
    unsigned char *(*svg)(const char *fen, size_t *len);
    unsigned char *(*png)(const char *fen, size_t *len);
  } *fen;
};

int chess_init(module(chess) *exports);
void chess_deinit(module(chess) *exports);
bool __chess_fen_valid(const char *fen);
char *__chess_exec_stockfish(const char **cmds, size_t qty);
char *__chess_exec_stockfish_fen(const char *fen);

exports(chess) {
  .log_mode = CHESS_LOG_MODE_NONE,
  .valid_fen=__chess_fen_valid,
  .init     = chess_init,
  .deinit   = chess_deinit,
};

#define chess_m    module(chess)

#endif
