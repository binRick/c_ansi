#pragma once
#ifndef CHESS_C
#define CHESS_C
////////////////////////////////////////////

////////////////////////////////////////////
#include "chess/chess.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "subprocess.h/subprocess.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "chessterm/include/chessterm.h"
#include "chessterm/include/board.h"
#include "chessterm/include/uci.h"
#include "chessterm/include/engine.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "ms/ms.h"
#include "timestamp/timestamp.h"
#include "FEN2SVG/unsortedlinkedlist.h"
#include "FEN2SVG/fen2svg.h"
#include "which/src/which.h"
#include "str/str.h"
#include "reproc/reproc/include/reproc/drain.h"
#include "reproc/reproc/include/reproc/export.h"
#include "reproc/reproc/include/reproc/reproc.h"

////////////////////////////////////////////

void __chessterm(char *fen){
  char *f=calloc(FEN_SIZE,sizeof(char));
  int scores[2];
  Board board;
  memcpy(board.black_name, "My Engine\0", 10);
  memcpy(board.white_name, "My Engine\0", 10);
  default_board(&board);
  Engine white_engine;
  white_engine.pid = 0;
  Engine black_engine;
  black_engine.pid = 0;  
  load_fen(&board, fen);
  get_material_scores(&board,&scores[0],&scores[1]);

  Di(scores[0]);
  Di(scores[1]);
  Ds(fen);
  Di(is_gameover(&board));
  Di(board.to_move);
  Di(black_engine.pid);
  Di(white_engine.pid);
  Di(board.to_move);
  Di(board.history_count);
  Di(board.pos_count);
  print_fancy(&board);
  board_stats(&board);
  export_fen(&board,f);
  Ds(f);


  send_ucinewgame(white_engine.write);
  send_isready(white_engine.write);
  send_position(white_engine.write,"fen",fen);
  /*
  char *msg;
  asprintf(msg, "depth %d", white_engine.depth);
  send_go(white_engine.write, msg);
  char* message = get_message(white_engine.read);
  while (!strstr(message, "bestmove")){
    Ds(message);
    free(message);
    message = get_message(white_engine.read);
    Ds(message);
  }
  */

  Move engine_move;
  engine_move = Erandom_move(&board);

  Di(engine_move.src_piece);
  Di(engine_move.dest);
  Di(board.to_move);
  Di(move_piece(&board, &engine_move));
  Di(board.to_move);
  export_fen(&board,f);
  board_stats(&board);
  Di(is_gameover(&board));
  Ds("ok");

//  stop_engine(&white_engine);
}
char *__chess_exec_stockfish_fen(const char *fen){
  char *s[2];
  asprintf(&s[0],"position fen %s\n",fen);
  struct Vector *v=vector_new();
  vector_push(v,(void*)strdup(s[0]));
  return(__chess_exec_stockfish((char**)vector_to_array(v),vector_size(v)));
}
char *__chess_exec_stockfish(const char **cmds, size_t qty){
  struct Vector *out_lines=vector_new();
  size_t buf_len=1024;
  const char  *command_line[] = { which("sh"),"-c",which("Stockfish"), NULL };
  struct subprocess_s proc;
  int result,ret;
  unsigned index = 0;
  unsigned bytes_read = 0;
  static char data[1048576 + 1] = {0};
  if((result= subprocess_create(command_line, subprocess_option_enable_async, &proc))!=0){
    log_error("subprocess error");
    return(NULL);
  }
  Ds(cmds[0]);
  fputs(cmds[0], subprocess_stdin(&proc));
  fflush(subprocess_stdin(&proc));
  fclose(subprocess_stdin(&proc));
  do {
    bytes_read = subprocess_read_stdout(&proc, data + index,sizeof(data) - 1 - index);
    Di(bytes_read);
    Di(index);
    if (index == 0) {
    }

    index += bytes_read;
  } while (bytes_read != 0);
  subprocess_join(&proc, &ret);
  subprocess_destroy(&proc);


  return(require(str)->trim(data));
}
bool __chess_fen_valid(const char *fen){
  return(false);
}
////////////////////////////////////////////
int __chess_init(module(chess) *exports) {
  clib_module_init(chess, exports);
  {
    exports->stockfish=calloc(1,sizeof(module(chess_stockfish)));
    exports->fen=calloc(1,sizeof(module(chess_fen)));
  }
  {
    exports->stockfish->exec=__chess_exec_stockfish;
    exports->stockfish->fen=__chess_exec_stockfish_fen;
  }
  return(EXIT_SUCCESS);
}

void __chess_deinit(module(chess) *exports) {
  free(exports->stockfish);
  free(exports->fen);
  clib_module_deinit(chess);
}

////////////////////////////////////////////
#endif
