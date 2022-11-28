#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "tempdir.c/tempdir.h"
#include "timestamp/timestamp.h"
#include "chess-test/chess-test.h"
#include "log/log.h"
#include "ms/ms.h"
#include "timestamp/timestamp.h"
#include "str/str.h"
#include "chess/chess.h"
#include "incbin/incbin.h"
#include "librnd/rnd.h"
#include "fen2svg/unsortedlinkedlist.h"
#include "fen2svg/fen2svg.h"
INCBIN(fens,"assets/fens.txt");
#define FENS_QTY 5
#define RANDOM_FEN_INDEX()(rnd_next_uniform_value(rnd, fens.count))
#define RANDOM_FEN_LINE()(fens.strings[RANDOM_FEN_INDEX()])
static struct StringFNStrings fens;
static struct rnd *rnd;
static struct StringFNStrings lines;

TEST t_chess_test_fens(){
  char *s;
  char *fmt="png";
  asprintf(&s,"%d Fens Loaded", lines.count);
  size_t len=0;
  unsigned char *buf;
  for(size_t i=0;i<FENS_QTY;i++){
    char *fen = lines.strings[i];
    bool ok = require(chess)->valid_fen(fen);
    require(chess)->chessterm(fen);
    buf = require(chess)->fen->image->buffer(fen, fmt, &len);
    log_info(
        "Fen '"AC_RESETALL AC_YELLOW "%s"AC_RESETALL "' OK? %s%s", 
        fen,
        ok?AC_GREEN:AC_RED,
        ok?"Yes":"No"
        );
  }
  PASSm(s);
}

TEST t_chess_test_fen_valid(){
  PASS();
}

#define RANDOM_FEN() (lines.strings[rand()%lines.count])
TEST t_chess_test_svg(){
  char *fmt="png";
  size_t len=0;
  char *fen=RANDOM_FEN();
  unsigned char *buf = require(chess)->fen->image->buffer(fen, fmt, &len);
  ASSERT_GTm("Unable to generate image",len,0);
  log_info("Wrote %s %s Buffer- %s",bytes_to_string(len),fmt,fen);
  PASS();
}

TEST t_chess_test_chessterm(){
  PASS();
}

SUITE(s_chess_test) {
  RUN_TEST(t_chess_test_svg);
  RUN_TEST(t_chess_test_fens);
  RUN_TEST(t_chess_test_fen_valid);
  RUN_TEST(t_chess_test_chessterm);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  srand(time(0));
  lines=stringfn_split_lines_and_trim((char*)gfensData);
  rnd = rnd_alloc();
  fens=stringfn_split_lines_and_trim(gfensData);
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_chess_test);
  GREATEST_MAIN_END();
  rnd_free(rnd);
}
