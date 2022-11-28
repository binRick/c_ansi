
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "chess-test/chess-test.h"
#include "log/log.h"
#include "ms/ms.h"
#include "timestamp/timestamp.h"
#include "chess/chess.h"
#include "incbin/incbin.h"
#include "librnd/rnd.h"
INCBIN(fens,"assets/fens.txt");
#define FENS_QTY 1
#define RANDOM_FEN_INDEX()(rnd_next_uniform_value(rnd, fens.count))
#define RANDOM_FEN_LINE()(fens.strings[RANDOM_FEN_INDEX()])
static struct StringFNStrings fens;
static struct rnd *rnd;

TEST t_chess_test_fens(){
  char *s;
  asprintf(&s,"%d Fens Loaded", fens.count);
  bool ok;
  char *fen;
  for(size_t i=0;i<FENS_QTY;i++){
    fen = RANDOM_FEN_LINE();
    ok = require(chess)->valid_fen(fen);
    log_info(
        "Fen '"AC_RESETALL AC_YELLOW "%s"AC_RESETALL "' OK? %s%s", 
        fen,
        ok?AC_GREEN:AC_RED,
        ok?"Yes":"No"
        );
//    char *out=require(chess)->stockfish.fen(fen);
    free(fen);
  }
  PASSm(s);
}

TEST t_chess_test_fen_valid(){
  PASS();
}

SUITE(s_chess_test) {
  RUN_TEST(t_chess_test_fens);
  RUN_TEST(t_chess_test_fen_valid);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  rnd = rnd_alloc();
  fens=stringfn_split_lines_and_trim(gfensData);
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_chess_test);
  GREATEST_MAIN_END();
  rnd_free(rnd);
}
