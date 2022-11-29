#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_ansi/async/async.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "chess-test/chess-test.h"
#include "chess/chess.h"
#include "fen2svg/fen2svg.h"
#include "fen2svg/unsortedlinkedlist.h"
#include "incbin/incbin.h"
#include "log/log.h"
#include "ms/ms.h"
#include "str/str.h"
#include "string-utils/string-utils.h"
#include "tempdir.c/tempdir.h"
#include "timestamp/timestamp.h"
#include "timestamp/timestamp.h"
INCBIN(fens, "assets/fens.txt");
#define QTY          (lines.count - 1)
#define FEN_STYLE    AC_RESETALL AC_YELLOW_BLACK AC_ITALIC AC_CURLY_UNDERLINE
static struct StringFNStrings lines;

TEST t_chess_test_fens(){
  char *s;
  char *fmt = "png";

  asprintf(&s, "%d Fens Loaded", lines.count);
  size_t        len = 0;
  unsigned char *buf;

  for (size_t i = 0; i < QTY && lines.strings[i]; i++) {
    bool ok = require(chess)->fen->is->valid(lines.strings[i]);
    log_info(
      "Fen '"AC_RESETALL AC_YELLOW "%s"AC_RESETALL "' OK? %s%s",
      lines.strings[i],
      ok?AC_GREEN:AC_RED,
      ok?"Yes":"No"
      );
  }
  PASSm(s);
}

TEST t_chess_test_fen_players(){
  for (size_t i = 0; i < QTY; i++) {
    char *player = require(chess)->fen->get->player(lines.strings[i]);
    log_info(FEN_STYLE "%s"AC_RESETALL "- %s", lines.strings[i], player);
  }
  PASS();
}

TEST t_chess_test_fen_bulk_moves(){
  unsigned long st[10], dur[10];
  struct Vector *v  = vector_new();
  int           lim = 999;

  for (int i = 0; i < lim && i < lines.count; i++)
    vector_push(v, (void *)lines.strings[i]);

  st[0] = timestamp();
  size_t qty     = 0;
  char   **moves = require(chess)->fen->get->moves(vector_to_array(v), vector_size(v), &qty);

  ASSERT_NEQm("invalid moves", moves, NULL);
  ASSERT_GTEm("no moves", qty, 0);
  for (int i = 0; i < qty; i++)
    log_info("%d> %s -> %s", i + 1, (char *)vector_get(v, i), moves[i]);
  //char **moves=require(chess)->fen->get->moves(lines.strings,lines.count,&qty);
  Dn(qty);
//  Ds(moves[0]);

  st[0] = timestamp();
  PASS();
}

TEST t_chess_test_fen_moves(){
  unsigned long st[10], dur[10];

  st[0] = timestamp();
  for (size_t i = 0; i < QTY; i++) {
    st[1] = timestamp();
    char *move = require(chess)->fen->get->move(lines.strings[i]);
    dur[1] = timestamp() - st[1];
    st[2]  = timestamp();
    char *player = require(chess)->fen->get->player(lines.strings[i]);
    dur[2] = timestamp() - st[2];
    st[3]  = timestamp();
    bool valid = require(chess)->fen->is->valid(lines.strings[i]);
    dur[3] = timestamp() - st[3];
    st[4]  = timestamp();
    int black = require(chess)->fen->score->black(lines.strings[i]);
    dur[4] = timestamp() - st[4];
    st[5]  = timestamp();
    int white = require(chess)->fen->score->white(lines.strings[i]);
    dur[5] = timestamp() - st[5];
    st[6]  = timestamp();
    bool is_over = require(chess)->fen->is->over(lines.strings[i]);
    dur[6] = timestamp() - st[6];
    PASS();

    log_info(FEN_STYLE "%s"AC_RESETALL "\n\t"AC_RESETALL AC_CYAN "%s"AC_RESETALL "'s Move %s:%s, "
             "|player:%s:%s"
             "|valid:%s:%s"
             "\n\t"
             "|score:%d:%s/%d:%s"
             "|is over?:%s:%s",
             lines.strings[i],
             player,
             move,
             milliseconds_to_string(dur[1]),
             player,
             milliseconds_to_string(dur[2]),
             valid?"Yes":"No",
             milliseconds_to_string(dur[3]),
             white,
             milliseconds_to_string(dur[4]),
             black,
             milliseconds_to_string(dur[5]),
             is_over?"Yes":"No",
             milliseconds_to_string(dur[6])
             );
  }
  char *s;

  asprintf(&s, "Finished in %s", milliseconds_to_string(timestamp() - st[0]));
  PASSm(s);
} /* t_chess_test_fen_moves */

TEST t_chess_test_fen_ansi(){
  for (size_t i = 0; i < QTY; i++) {
    char *ansi = require(chess)->fen->image->ansi(lines.strings[i]);
    printf("============\n%s\n============\n", ansi);
    free(ansi);
  }
  PASS();
}

TEST t_chess_test_fen_valid(){
  int  qty = 0;
  bool valid;
  char *s;

  for (size_t i = 0; i < QTY; i++) {
    valid = require(chess)->fen->is->valid(lines.strings[i]);
    log_info(FEN_STYLE "%s"AC_RESETALL "is valid? %s%s", lines.strings[i], valid?AC_GREEN:AC_RED, valid?"Yes":"No");
    ASSERT_EQm("Invalid FEN", valid, true);
    qty++;
  }
  asprintf(&s, "Validated %d FENs", qty);
  PASSm(s);
}

TEST t_chess_test_fen_stats(){
  for (size_t i = 0; i < QTY; i++) {
    char *stats = require(chess)->fen->stats(lines.strings[i]);
    log_info(FEN_STYLE "%s" AC_RESETALL "\n%s", lines.strings[i], stats);
    free(stats);
  }
  PASS();
}

TEST t_chess_test_fen_scores(){
  for (size_t i = 0; i < QTY; i++) {
    int black = require(chess)->fen->score->black(lines.strings[i]);
    int white = require(chess)->fen->score->white(lines.strings[i]);
    log_info("%lu/%d> " FEN_STYLE "%s"AC_RESETALL "\nwhite:"AC_WHITE "%d"AC_RESETALL "|"AC_WHITE_BLACK "black"AC_RESETALL ":%d", i + 1, QTY, lines.strings[i], white, black);
  }
  PASS();
}

TEST t_chess_test_svg(){
  setenv("TMPDIR", "/tmp/", 1);
  char          *fmt = "png";
  size_t        len  = 0;
  unsigned char *buf;
  for (size_t i = 0; i < QTY; i++) {
    unsigned long s = timestamp(), dur = 0;
    char          *tf, *cf;
    asprintf(&tf, "%schess-test-svg-%lu.%s", gettempdir(), i, fmt);
    char          *h = (char *)hash_buffer((void *)lines.strings[i], strlen(lines.strings[i]));
    asprintf(&cf, "%schess-test-svg-cache-%s.%s", gettempdir(), h, fmt);
    Ds(cf);
    Dn(fsio_file_size(cf));
    if (fsio_file_size(cf) > 0) {
      len = fsio_file_size(cf);
      buf = fsio_read_binary_file(cf);
    }else{
      len = 0;
      buf = require(chess)->fen->image->buffer(lines.strings[i], fmt, &len);
      fsio_write_binary_file(cf, buf, len);
    }
    ASSERT_NEQm("Invalid image buffer", buf, NULL);
    ASSERT_GTm("Unable to generate image", len, 0);
    unsigned long s_write = timestamp(), s_dur = 0;
    fsio_write_binary_file(tf, buf, len);
    s_dur = timestamp() - s_write;
    dur   = timestamp() - s;
    log_info("Wrote %s %s Buffer to %s- "FEN_STYLE "%s"AC_RESETALL " in %s, |write:%s|",
             bytes_to_string(len), fmt,
             tf,
             lines.strings[i],
             milliseconds_to_string(dur),
             milliseconds_to_string(s_dur)
             );
    free(buf);
  }
  PASS();
}

TEST t_chess_test_fen_is_over(){
  char *over;

  for (size_t i = 0; i < QTY; i++) {
    if (require(chess)->fen->is->over(lines.strings[i]))
      asprintf(&over, "over");
    else
      asprintf(&over, "not over");
    log_info(FEN_STYLE "%s"AC_RESETALL "- %s", lines.strings[i], over);
  }
  PASS();
}

TEST t_chess_test_fen_is_move(){
  char *player;

  for (size_t i = 0; i < QTY; i++) {
    if (require(chess)->fen->is->move->black(lines.strings[i]))
      asprintf(&player, "black");
    else if (require(chess)->fen->is->move->white(lines.strings[i]))
      asprintf(&player, "white");
    else
      FAILm("Invalid move");
    log_info(FEN_STYLE "%s"AC_RESETALL "- %s's move", lines.strings[i], player);
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
  RUN_TEST(t_chess_test_fen_is_over);
  RUN_TEST(t_chess_test_fen_ansi);
  RUN_TEST(t_chess_test_fen_moves);
  RUN_TEST(t_chess_test_fen_bulk_moves);
  RUN_TEST(t_chess_test_fen_players);
  RUN_TEST(t_chess_test_fen_scores);
  RUN_TEST(t_chess_test_chessterm);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  srand(time(0));
  lines = stringfn_split_lines_and_trim((char *)gfensData);
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_chess_test);
  GREATEST_MAIN_END();
}
