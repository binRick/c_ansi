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
int chess_init(module(chess) *exports) {
  clib_module_init(chess, exports);
  exports->log_mode = CHESS_LOG_MODE_NONE;
  exports->stockfish.exec=__chess_exec_stockfish;
  exports->stockfish.fen=__chess_exec_stockfish_fen;
  return(EXIT_SUCCESS);
}

void chess_deinit(module(chess) *exports) {
  clib_module_deinit(chess);
}

////////////////////////////////////////////
#endif
