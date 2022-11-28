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
#define QTY (lines.count-1)
#define FEN_STYLE AC_RESETALL AC_YELLOW_BLACK AC_ITALIC AC_CURLY_UNDERLINE
static struct StringFNStrings fens;
static struct rnd *rnd;
static struct StringFNStrings lines;

TEST t_chess_test_fens(){
  char *s;
  char *fmt="png";
  asprintf(&s,"%d Fens Loaded", lines.count);
  size_t len=0;
  unsigned char *buf;
  for(size_t i=0;i<QTY && lines.strings[i];i++){
    char *fen = lines.strings[i];
    bool ok = require(chess)->fen->is->valid(fen);
    log_info(
        "Fen '"AC_RESETALL AC_YELLOW "%s"AC_RESETALL "' OK? %s%s", 
        fen,
        ok?AC_GREEN:AC_RED,
        ok?"Yes":"No"
        );
  }
  PASSm(s);
}

TEST t_chess_test_fen_ansi(){
  for(size_t i=0;i<QTY;i++){
    char *fen = lines.strings[i];
    char *ansi = require(chess)->fen->image->ansi(fen);
    printf("============\n%s\n============\n",ansi);
    free(ansi);

  }
  PASS();
}
TEST t_chess_test_fen_valid(){
  int qty=0;
  bool valid;
  char *fen,*s;
  for(size_t i=0;i<QTY;i++){
    fen = lines.strings[i];
    valid =require(chess)->fen->is->valid(fen);
    log_info(FEN_STYLE"%s"AC_RESETALL "is valid? %s%s",fen,valid?AC_GREEN:AC_RED,valid?"Yes":"No");
    ASSERT_EQm("Invalid FEN",valid,true);
    qty++;
  }
  asprintf(&s,"Validated %d FENs",qty);
  PASSm(s);
}

TEST t_chess_test_fen_print(){
  char *fen;
  for(size_t i=0;i<QTY;i++){
    fen = lines.strings[i];
    require(chess)->fen->print(fen);
  }
  PASS();
}
TEST t_chess_test_fen_stats(){
  for(size_t i=0;i<QTY;i++){
    char *fen = lines.strings[i];
    char *stats=require(chess)->fen->stats(fen);
    log_info(FEN_STYLE "%s" AC_RESETALL "\n%s",fen,stats);
    free(stats);
  }
  PASS();
}

TEST t_chess_test_fen_scores(){
  for(size_t i=0;i<QTY;i++){
    char *fen = lines.strings[i];
    int black=require(chess)->fen->score->black(fen);
    int white=require(chess)->fen->score->white(fen);
    log_info(FEN_STYLE"%s"AC_RESETALL "\nwhite:"AC_WHITE"%d"AC_RESETALL "|"AC_WHITE_BLACK "black"AC_RESETALL ":%d",fen,white,black);
  }
  PASS();
}

TEST t_chess_test_svg(){
  char *fmt="png";
  size_t len=0;
  unsigned char *buf;
  for(size_t i=0;i<QTY;i++){
    len=0;
    char *fen = lines.strings[i];
    buf = require(chess)->fen->image->buffer(fen, fmt, &len);
    ASSERT_NEQm("Invalid image buffer",buf,NULL);
    ASSERT_GTm("Unable to generate image",len,0);
    log_info("Wrote %s %s Buffer- "FEN_STYLE"%s"AC_RESETALL,bytes_to_string(len),fmt,fen);
  }
  PASS();

}

TEST t_chess_test_fen_is_move(){
  char *player;
  for(size_t i=0;i<QTY;i++){
    char *fen = lines.strings[i];
    if(require(chess)->fen->is->move->black(fen)){
      asprintf(&player,"black");
    }else if(require(chess)->fen->is->move->white(fen)){
      asprintf(&player,"white");
    }else{
      FAILm("Invalid move");
    }
    log_info(FEN_STYLE"%s"AC_RESETALL "- %s's move",fen,player);
  }
  PASS();
}
TEST t_chess_test_chessterm(){
  PASS();
}

SUITE(s_chess_test) {
  RUN_TEST(t_chess_test_svg);
  RUN_TEST(t_chess_test_fens);
  RUN_TEST(t_chess_test_fen_valid);
  RUN_TEST(t_chess_test_fen_stats);
  RUN_TEST(t_chess_test_fen_is_move);
  RUN_TEST(t_chess_test_fen_print);
  RUN_TEST(t_chess_test_fen_ansi);
  RUN_TEST(t_chess_test_fen_scores);
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
