#pragma once
#ifndef CHESS_C
#define CHESS_C
#define DEBUG_MODE             false
#define CHESS_DEFAULT_DEPTH    10
#define FEN_WORDS_QTY    6
#define QOIR_IMPLEMENTATION
////////////////////////////////////////////
#include "chess/chess.h"
////////////////////////////////////////////
#include <stdlib.h>
#include <stdio.h>
#include "qoir/src/qoir.h"
#include "sqldbal/src/sqldbal.h"
#include "sqlite3.h"
////////////////////////////////////////////
#define DB_DRIVER           SQLDBAL_DRIVER_SQLITE
#define DB_PORT             NULL
#define DB_USERNAME         NULL
#define DB_PASSWORD         NULL
#define DB_DATABASE         NULL
#define DB_FILE             ".sqldbal-chess-db-1.db"
static int                  DB_FLAGS = (SQLDBAL_FLAG_SQLITE_OPEN_CREATE | SQLDBAL_FLAG_SQLITE_OPEN_READWRITE);
////////////////////////////////////////////
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
////////////////////////////////////////////
#define SCREEN_WIDTH 920
#define SCREEN_HIGHT 920
#define PADDING 50
#define DARK  0x786452FF
#define LIGHT 0xA5907EFF
#define RED   0xFF0000FF
#define GREEN 0x00A300FF
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "async/async.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "chan/src/chan.h"
#include "chan/src/queue.h"
#include "chessterm/include/board.h"
#include "chessterm/include/engine.h"
#include "chessterm/include/chessterm.h"
#include "chessterm/include/uci.h"
#include "chessterm/include/io.h"
#include "chessterm/include/engine.h"
#include "fen2svg/fen2svg.h"
#include "fen2svg/unsortedlinkedlist.h"
#include "glib.h"
#include "incbin/incbin.h"
#include "log/log.h"
#include "ms/ms.h"
#include "str/str.h"
#include "subprocess.h/subprocess.h"
#include "tempdir.c/tempdir.h"
#include "timestamp/timestamp.h"
#include "vips/vips.h"
#include "which/src/which.h"
bool __chess_sdl_draw(SDL_Window* window,SDL_Surface* surface);
SDL_Surface *__chess_decoded_surface(qoir_decode_result *decode);
qoir_decode_result *__chess_sdl_decode_qoir(unsigned char *buf, size_t len);
INCBIN(chess_piece_rook_black_qoir,"assets/pieces/r/b/w.qoir");
INCBIN(chess_piece_rook_white_qoir,"assets/pieces/r/w/w.qoir");
INCBIN(chess_piece_queen_black_qoir,"assets/pieces/q/b/w.qoir");
INCBIN(chess_piece_queen_white_qoir,"assets/pieces/q/w/w.qoir");
enum CHESS_PIECE_COLOR {
  CHESS_PIECE_COLOR_WHITE,
  CHESS_PIECE_COLOR_BLACK,
  CHESS_PIECE_COLORS_QTY,
};
enum CHESS_PIECE_TYPE {
  CHESS_PIECE_TYPE_ROOK,
  CHESS_PIECE_TYPE_QUEEN,
  CHESS_PIECE_TYPES_QTY,
};

#define ENGINE_READ  to_engine[0]
#define CLIENT_WRITE to_engine[1]
#define CLIENT_READ  from_engine[0]
#define ENGINE_WRITE from_engine[1]
static unsigned long __chess_started;
static chan_t      *engine_chan=0;

void __chess_start_engine(void){
    if(!engine_chan)
      engine_chan=chan_init(100);
    int to_engine[2];
    int from_engine[2];
    int result = pipe(to_engine);
    while (result == -1)
        result = pipe(to_engine);
    result = pipe(from_engine);
    if (result == -1)
        result = pipe(from_engine);
    chan_send(engine_chan,(void*)0);
    chan_send(engine_chan,(void*)0);
    chan_send(engine_chan,(void*)0);
    //chan_send(engine_chan,(void*)lines.strings[0]);
    pid_t child_pid = fork();
    if (child_pid){
        close(ENGINE_READ);
        close(ENGINE_WRITE);
        send_uci(CLIENT_WRITE);
        send_isready(CLIENT_WRITE);
        char* message = get_message(CLIENT_READ);
        while (!strstr(message, "readyok")){
            log_info("%d> [WAITING FOR readyok] %s Ready after %s", getpid(), message,milliseconds_to_string(timestamp()-__chess_started));
            message = get_message(CLIENT_READ);
        }
        log_debug("%s\n", message);
        free(message);
        void *msg;
        log_info("waiting for msgs");
        while(chan_recv(engine_chan,&msg)==0){
          char *s=(char*)msg;
          log_info("process msg:%s",s);

        }
        log_info("ended msgs");
    }else{
        dup2(ENGINE_READ,  0);
        dup2(ENGINE_WRITE, 1);

        close(CLIENT_READ);
        close(CLIENT_WRITE);

        char* args[] = {which("stockfish"), NULL};
        execvp(which("stockfish"), args);
    }
}
struct chess_piece_t;
struct chess_piece_t *__chess_get_piece_at_position(int x, int y);
static struct sqldbal_db *chess_db = 0;
static struct chess_piece_t {
  enum CHESS_PIECE_TYPE type;
  enum CHESS_PIECE_COLOR color;
  struct {
    int x, y;
  } position;
  struct {
    unsigned char *buf; 
    size_t (^len)(void); 
  } qoir;
} chess_pieces[CHESS_PIECE_COLORS_QTY][CHESS_PIECE_TYPES_QTY] = {
  [CHESS_PIECE_COLOR_WHITE] = {
    [CHESS_PIECE_TYPE_QUEEN] = {
      .qoir={
        .buf=gchess_piece_queen_white_qoirData,
        .len=^size_t(void){return gchess_piece_queen_white_qoirSize;},
      },
    },
    [CHESS_PIECE_TYPE_ROOK] = {
      .qoir={
        .buf=gchess_piece_rook_white_qoirData,
        .len=^size_t(void){return gchess_piece_rook_white_qoirSize;},
      },
    },
  },
  [CHESS_PIECE_COLOR_BLACK] = {
    [CHESS_PIECE_TYPE_QUEEN] = {
      .qoir={
        .buf=gchess_piece_queen_black_qoirData,
        .len=^size_t(void){return gchess_piece_queen_black_qoirSize;},
      },
    },
    [CHESS_PIECE_TYPE_ROOK] = {
      .qoir={
        .buf=gchess_piece_rook_black_qoirData,
        .len=^size_t(void){return gchess_piece_rook_black_qoirSize;},
      },
    },
  },
};

void __chess_sql_test(void){
  log_info("sql test");
}

bool __chess_sdl_fen_load(const char *fen) {
  require(chess)->fen->cur=calloc(1,sizeof(struct chess_fen_t));
  Di(require(chess)->fen->cur->valid);
  require(chess)->fen->cur->valid=true;
  Di(require(chess)->fen->cur->valid);
  Ds(require(chess)->fen->cur->text);
  asprintf(&(require(chess)->fen->cur->text),"%s",fen);
  Ds(require(chess)->fen->cur->text);
  Ds(fen);
  return(true);
}

struct chess_piece_t *__chess_get_piece_at_position(int x, int y){
  for(int c=0;c<CHESS_PIECE_COLORS_QTY;c++)
    for(int t=0;t<CHESS_PIECE_TYPES_QTY;t++)
      if(chess_pieces[c][t].position.x==x && chess_pieces[c][t].position.y==y){
        log_info("found piece match @%dx%d",x,y);
        return(&(chess_pieces[c][t]));
      }
  if(DEBUG_MODE)
    log_warn("no piece found @%dx%d",x,y);
  return(0);
}

#define STOCKFISH_EVALUATE_FEN_FMT    "printf \"position fen %s\\ngo depth %d\" | %s"
INCTXT(svg_template, "assets/template.svg");
#define SVG_FILE                      "dia00001.svg"
static char *__chess_print_piece(uint8_t piece);
static char *__chess_render_fen_cmd(char *fen, int depth);
char *__chess_fen_ansi(char *fen);
////////////////////////////////////////////

static char *__chess_render_fen_cmd(char *fen, int depth){
  char *s;

  asprintf(&s, STOCKFISH_EVALUATE_FEN_FMT, fen, depth, which("stockfish"));
  return(s);
}

int __chess_fen_black_score(char *fen){
  Board board;

  load_fen(&board, fen);
  int scores[2];

  get_material_scores(&board, &scores[0], &scores[1]);
  return(scores[1]);
}

int __chess_fen_white_score(char *fen){
  Board board;

  load_fen(&board, fen);
  int scores[2];

  get_material_scores(&board, &scores[0], &scores[1]);
  return(scores[0]);
}

unsigned char *__chess_fen_image(char *fen, char *fmt, size_t *len){
  *len = 0;
  VipsImage     *image_svg;
  int           argc = 6, r = rand() % 1000;
  char          *fen_file, *template, *dir, *j, *tempdir, *svg, *_fmt, *svg_file;
  unsigned char *png;

  asprintf(&tempdir, "%s%lld-%d", gettempdir(), timestamp(), r);
  fsio_mkdirs(tempdir, 0777);
  asprintf(&fen_file, "%s/%lld.fen", tempdir, timestamp());
  asprintf(&svg_file, "%s/%s", tempdir, SVG_FILE);
  asprintf(&template, "%s/template.svg", tempdir);
  char *argv[] = { "./fen2svg", "-b", "-c", "-m", "-f", fen_file, NULL };
  j   = stringfn_join(argv, " ", 0, argc);
  dir = getwd(0);
  chdir(tempdir);
  fsio_write_text_file(fen_file, fen);
  fsio_write_text_file(template, require(chess)->svg_template);
  if (fsio_file_exists(svg_file))
    fsio_remove(SVG_FILE);
  if (fen2svg_main(argc, argv) != 0) {
    log_error("Failed to generate svg from fen");
    return(NULL);
  }
  if (!fsio_file_exists(SVG_FILE)) {
    log_error("Failed to find svg file %s", SVG_FILE);
    return(NULL);
  }
  svg = fsio_read_text_file(SVG_FILE);
  fsio_remove(SVG_FILE);
  fsio_remove(fen_file);
  fsio_remove(template);
  chdir(dir);
  fsio_remove(tempdir);
  if (!(image_svg = vips_image_new_from_buffer((const void *)svg, strlen(svg), "", NULL))) {
    log_error("Failed to decode svg");
    return(0);
  }
  if (DEBUG_MODE)
    log_info("%dx%d",
             vips_image_get_width(image_svg),
             vips_image_get_height(image_svg)
             );

  asprintf(&_fmt, ".%s", fmt);
  if (vips_image_write_to_buffer(image_svg, _fmt, &png, len, NULL)) {
    log_error("Failed to write %s buffer", fmt);
    return(NULL);
  }
  free(_fmt);
  g_object_unref(image_svg);
  return(png);
} /* __chess_fen_image */

void __chessterm(char *fen){
  char  *f = calloc(FEN_SIZE, sizeof(char));
  int   scores[2];
  Board board;

  memcpy(board.black_name, "My Engine\0", 10);
  memcpy(board.white_name, "My Engine\0", 10);
  default_board(&board);
  Engine white_engine;

  white_engine.pid = 0;
  Engine black_engine;

  black_engine.pid = 0;
  load_fen(&board, fen);
  get_material_scores(&board, &scores[0], &scores[1]);

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
  export_fen(&board, f);
  Ds(f);

  send_ucinewgame(white_engine.write);
  send_isready(white_engine.write);
  send_position(white_engine.write, "fen", fen);

  Move engine_move;

  engine_move = Erandom_move(&board);

  Di(engine_move.src_piece);
  Di(engine_move.dest);
  Di(board.to_move);
  Di(move_piece(&board, &engine_move));
  Di(board.to_move);
  export_fen(&board, f);
  board_stats(&board);
  Di(is_gameover(&board));
  Ds("ok");
  free(f);

//  stop_engine(&white_engine);
} /* __chessterm */

char **__chess_fen_get_moves(const char **fens, size_t qty, size_t *moves_qty){
  int depth = CHESS_DEFAULT_DEPTH;

  char                   *cmd     = stringfn_join(fens, "\n", 0, qty);
  struct StringFNStrings fen_cmds = stringfn_split_lines_and_trim(cmd);
  struct Vector          *cmds_v  = vector_new();
  struct StringBuffer    *sb      = stringbuffer_new();

  stringbuffer_append_string(sb, "printf \"");
  for (size_t i = 0; i < qty; i++) {
    if (strlen(fens[i]) < 5) continue;
    char                   *l;
    char                   *f    = fens[i];
    struct StringFNStrings words = stringfn_split_words(f);
    f = stringfn_join(words.strings, " ", 0, 5);
    asprintf(&l, "position fen \\\"%s\\\"\\ngo depth %d\\n", f, depth);
    if (i < qty - 1)
      stringfn_mut_trim(l);
    vector_push(cmds_v, (void *)l);
    stringbuffer_append_string(sb, l);
  }
  stringbuffer_append_string(sb, "\"");
  char *bulk_cmd = stringbuffer_to_string(sb);

  stringbuffer_release(sb);
  char                   *res  = require(chess)->stockfish->exec(bulk_cmd);
  struct StringFNStrings lines = stringfn_split_lines_and_trim(res);

  char                   *fen_move[lines.count];
  size_t                 fen_moves_qty = 0;
  struct Vector          *v            = vector_new();

  for (int i = 0; i < lines.count; i++)
    if (stringfn_starts_with(lines.strings[i], "bestmove ")) {
      struct StringFNStrings words = stringfn_split_words(lines.strings[i]);
      if (words.count < 2) continue;
      asprintf(&(fen_move[fen_moves_qty]), "%s", words.strings[1]);
      vector_push(v, (void *)fen_move[fen_moves_qty]);
      fen_moves_qty++;
    }
  char *moves_s = stringfn_join((char **)vector_to_array(v), "\n", 0, vector_size(v));
  *moves_qty = vector_size(v);
  return(vector_to_array(v));
} /* __chess_fen_get_moves */
static void __attribute__((constructor)) __constructor__chess(void);
static void __attribute__((constructor)) __constructor__chess(void){
__chess_started=timestamp();
  chess_db=sqldbal_open(DB_DRIVER, DB_FILE, DB_PORT, DB_USERNAME, DB_PASSWORD, DB_DATABASE,DB_FLAGS, NULL, 0, &(chess_db));
}
char *__chess_fen_get_best(const char *fen){
  char *b;
 b= require(chess)->fen->get->player(fen);
 b= require(chess)->fen->cmd(fen, 10);
  Ds(fen);
  Ds(b);
  return(b);


  return(0);
}

char *__chess_fen_get_move(const char *fen){
  char *move;
  int  depth = CHESS_DEFAULT_DEPTH;

  char *res = require(chess)->stockfish->exec(require(chess)->fen->cmd(fen, depth));

  if (stringfn_starts_with(res, "bestmove")) {
    struct StringFNStrings words = stringfn_split_words(res);
    move = strdup(words.strings[words.count - 1]);
  }
  return(move);
}

void __chess_get_moves(const char *fen){
  Board board;
  load_fen(&board, fen);
  Candidate cans[MOVES_PER_POSITION];
 // get_all_moves(&board, cans);
}

static struct subprocess_s *proc_async;
void __chess_exec_stockfish_async_init(void){
  size_t buf_len = 1024;
  char   *tf, *of, *cmd_file;

  setenv("TMPDIR", "/tmp/", 1);
  asprintf(&of, "%s%d%lld.out", gettempdir(), rand() % 1000, timestamp());
  asprintf(&tf, "%s%d%lld.tmp", gettempdir(), rand() % 1000, timestamp());
  asprintf(&cmd_file, "%s%d%lld.cmd", gettempdir(), rand() % 1000, timestamp());
  proc_async = calloc(1, sizeof(struct subprocess_s));
  chan_t      *recv_chan = chan_init(100);
  unsigned    index = 0;
  unsigned    bytes_read = 0;
  static char data[1048576 + 1] = { 0 };
  const char  *command_line[] = { which("env"), which("bash"), "-c", which("stockfish"), NULL };
  int         result, ret;

  if ((result = subprocess_create(command_line, subprocess_option_enable_async, proc_async)) != 0) {
    log_error("subprocess error");
    return(NULL);
  }
  do {
    bytes_read = subprocess_read_stdout(proc_async, data + index, sizeof(data) - 1 - index);
    index     += bytes_read;
  } while (bytes_read != 0);
  subprocess_join(proc_async, &ret);
  subprocess_destroy(proc_async);
  char *s;

  if (strlen(data) > 0) {
    stringfn_mut_trim((char *)data);
    struct StringFNStrings lines = stringfn_split_lines_and_trim((char *)data);
    if (lines.count > 0)
      s = strdup(lines.strings[lines.count - 1]);
    stringfn_release_strings_struct(lines);
  }
  s = fsio_read_text_file(of);
  return(s);
}

char *__chess_exec_stockfish(const char *cmd){
  size_t buf_len = 1024;
  char   *tf, *of, *cmd_file;

  setenv("TMPDIR", "/tmp/", 1);
  asprintf(&of, "%s%d%lld.out", gettempdir(), rand() % 1000, timestamp());
  asprintf(&tf, "%s%d%lld.tmp", gettempdir(), rand() % 1000, timestamp());
  asprintf(&cmd_file, "%s%d%lld.cmd", gettempdir(), rand() % 1000, timestamp());
  fsio_write_text_file(tf, cmd);
  asprintf(&cmd, "bash -c '%s|%s' > %s\n", cmd, which("stockfish"), of);
  fsio_write_text_file(cmd_file, cmd);
  const char          *command_line[] = { which("env"), which("bash"), cmd_file, NULL };
  struct subprocess_s proc;
  int                 result, ret;
  unsigned            index             = 0;
  unsigned            bytes_read        = 0;
  static char         data[1048576 + 1] = { 0 };

  if ((result = subprocess_create(command_line, subprocess_option_enable_async, &proc)) != 0) {
    log_error("subprocess error");
    return(NULL);
  }
  do {
    bytes_read = subprocess_read_stdout(&proc, data + index, sizeof(data) - 1 - index);
    index     += bytes_read;
  } while (bytes_read != 0);
  subprocess_join(&proc, &ret);
  subprocess_destroy(&proc);
  char *s;

  if (strlen(data) > 0) {
    stringfn_mut_trim((char *)data);
    struct StringFNStrings lines = stringfn_split_lines_and_trim((char *)data);
    if (lines.count > 0)
      s = strdup(lines.strings[lines.count - 1]);
    stringfn_release_strings_struct(lines);
  }
  s = fsio_read_text_file(of);
  return(s);
}

bool __chess_fen_over(const char *fen){
  Board board;

  load_fen(&board, fen);
  int s[2] = { 0, 0 };

  get_material_scores(&board, &(s[0]), &(s[1]));
  return(is_gameover(&board));
}

bool __chess_fen_valid(const char *fen){
  if (!fen) return(false);

  struct StringFNStrings words = stringfn_split_words(fen);
  if (words.count < FEN_WORDS_QTY) return(false);

  char *color = words.strings[1];
  if (strlen(color) != 1 || (strcmp(color, "w") != 0 && strcmp(color, "b") != 0)) return(false);

  stringfn_release_strings_struct(words);
  Board board;
  load_fen(&board, fen);
  int   s[2] = { 0, 0 };
  get_material_scores(&board, &(s[0]), &(s[1]));
  return(s[0] > 0 && s[1] > 0);
}

char *__chess_fen_get_player_to_move(char *fen){
  if (require(chess)->fen->is->move->white(fen))
    return("white");
  else if (require(chess)->fen->is->move->black(fen))
    return("black");

  return("UNKNOWN");
}

////////////////////////////////////////////
bool __chess_fen_is_white_move(const char *fen){
  Board *board = calloc(1, sizeof(Board));

  load_fen(board, fen);
  bool move;

  move = (board->to_move == 1);
  free(board);
  return(move);
}

bool __chess_fen_is_black_move(const char *fen){
  Board *board = calloc(1, sizeof(Board));

  load_fen(board, fen);
  bool move;

  move = (board->to_move == 0);
  free(board);
  return(move);
}

struct chess_fen_t __chess_fen_load(char *fen){
  return((struct chess_fen_t){
      .text=fen,
      .valid=require(chess)->fen->is->valid(fen),
      .over=require(chess)->fen->is->over(fen),
      .player=require(chess)->fen->get->player(fen),
      .best=require(chess)->fen->get->best(fen),
      });
}
char *__chess_fen_stats(char *fen){
  char                *s;
  struct StringBuffer *sb    = stringbuffer_new();
  int                 L  = 179;
  int                 D   = 58;
  Board               *board = calloc(1, sizeof(Board));

  load_fen(board, fen);
  if (board->to_move == 1)
    stringbuffer_append_string(sb, "Black");
  else if (board->to_move == 0)
    stringbuffer_append_string(sb, "White");
  stringbuffer_append_string(sb, " to move.\nCastling: ");
  if (board->castling & 0x08)
    stringbuffer_append_string(sb, "K");
  if (board->castling & 0x04)
    stringbuffer_append_string(sb, "Q");
  if (board->castling & 0x02)
    stringbuffer_append_string(sb, "k");
  if (board->castling & 0x01)
    stringbuffer_append_string(sb, "q");
  stringbuffer_append_string(sb, "\nEn pessant: ");
  if (board->en_p == -1)
    stringbuffer_append_string(sb, "None\n");
  else{
    asprintf(&s, "%c%d\n", (board->en_p % 8) + 'a', 8 - (board->en_p / 8));
    stringbuffer_append_string(sb, s);
  }
  asprintf(&s, "Halfmoves: %d\nFullmoves: %d\n", board->halfmoves, board->moves);
  stringbuffer_append_string(sb, s);
  asprintf(&s, "Whiteking_pos: %c%d\n", (board->wking_pos % 8) + 'a',
           8 - (board->wking_pos / 8));
  stringbuffer_append_string(sb, s);
  asprintf(&s, "Blackking_pos: %c%d\n", (board->bking_pos % 8) + 'a',
           8 - (board->bking_pos / 8));
  stringbuffer_append_string(sb, s);
  free(board);
  s = stringbuffer_to_string(sb);
  stringbuffer_release(sb);
  stringfn_mut_trim(s);
  return(s);
} /* __chess_fen_stats */

char *__chess_fen_ansi(char *fen){
  struct StringBuffer *sb = stringbuffer_new();
  int                 L = 179, D = 58, i;
  Board               *board = calloc(1, sizeof(Board));

  load_fen(board, fen);
  stringbuffer_append_string(sb, "   \u2554");
  for (i = 0; i < 56; ++i)
    stringbuffer_append_string(sb, "\u2550");
  stringbuffer_append_string(sb, "\u2557");
  int        white_score[6];
  int        black_score[6];
  const char *piece_chars = "pbnrq";

  get_material_scores(board, white_score, black_score);
  char *s;

  asprintf(&s, " %s: ", strlen(board->black_name) ? board->black_name : "Black");
  stringbuffer_append_string(sb, s);
  if (white_score[0] - black_score[0] < 0) {
    asprintf(&s, "%+d ", black_score[0] - white_score[0]);
    stringbuffer_append_string(sb, s);
  }
  int j;

  for (i = 1; i < 6; ++i)
    for (j = 0; j < white_score[6 - i]; ++j)
      stringbuffer_append(sb, piece_chars[5 - i] - 32);
  stringbuffer_append_string(sb, "\n");

  for (i = 0; i < 24; ++i) {
    if (i % 3 == 1)
      asprintf(&s, "%+d \u2551", 8 - (i / 3));
    else
      asprintf(&s, "   \u2551");
    stringbuffer_append_string(sb, s);
    int j;
    for (j = 0; j < 8; ++j)
      stringbuffer_append_string(sb, "       ");
    stringbuffer_append_string(sb, "\u2551\n");
  }
  stringbuffer_append_string(sb, "   \u255a");
  for (i = 0; i < 56; ++i)
    stringbuffer_append_string(sb, "\u2550");
  asprintf(&s, " %s: ", strlen(board->white_name) ? board->white_name:"White");
  stringbuffer_append_string(sb, s);
  if (white_score[0] - black_score[0] > 0) {
    asprintf(&s, "%+d ", white_score[0] - black_score[0]);
    stringbuffer_append_string(sb, s);
  }
  for (i = 1; i < 6; ++i)
    for (j = 0; j < black_score[6 - i]; ++j)
      stringbuffer_append(sb, piece_chars[5 - i]);
  stringbuffer_append_string(sb, "\n       ");
  for (i = 0; i < 8; ++i) {
    asprintf(&s, "%c      ", 'a' + i);
    stringbuffer_append_string(sb, s);
  }
  stringbuffer_append_string(sb, "\n");
  stringbuffer_append_string(sb, "\e[26F\e[4C");

  Move prev_move;

  if (board->history_count > 0)
    prev_move = board->history[board->history_count - 1];
  else
    prev_move = board->history[board->history_count];
  int8_t prev_src  = prev_move.src_rank * 8 + prev_move.src_file;
  int8_t prev_dest = prev_move.dest;

  for (i = 0; i < 64; ++i) {
    /* Bullshit that colors them checkered-like
     * - Courtesy of Zach Gorman
     */
    uint8_t square = board->position[i];
    if (prev_dest != -1 && (i == prev_src || i == prev_dest)) {
      if (i == prev_src)
        stringbuffer_append_string(sb, "\e[48;5;6m");
      if (i == prev_dest)
        stringbuffer_append_string(sb, "\e[48;5;12m");
    }else {
      if (!(!(i & 1) ^ !(i & 8)))
        asprintf(&s, "\e[48;5;%dm", L);
      else
        asprintf(&s, "\e[48;5;%dm", D);
      stringbuffer_append_string(sb, s);
    }

    stringbuffer_append_string(sb, "\e[1m");
    (square & BLACK) ? stringbuffer_append_string(sb, "\e[38;5;232m") : stringbuffer_append_string(sb, "\e[37m");
    stringbuffer_append_string(sb, __chess_print_piece(square));
    stringbuffer_append_string(sb, "\e[0m");

    if (i % 8 == 7)
      stringbuffer_append_string(sb, "\u2551\e[3E\e[4C");
  }
  stringbuffer_append_string(sb, "\e[8E\n");
  free(board);
  s = stringbuffer_to_string(sb);
  stringbuffer_release(sb);
  stringfn_mut_trim(s);
  return(s);
} /* __chess_fen_ansi */

static char *__chess_print_piece(uint8_t piece){
  struct StringBuffer *sb = stringbuffer_new();

  if (piece & PAWN)
    stringbuffer_append_string(sb, "   O   \e[B\e[7D"
                               "  ( )  \e[B\e[7D"
                               "  ===  \e[2A");
  else if (piece & BISHOP)
    stringbuffer_append_string(sb, "  (/)  \e[B\e[7D"
                               "  / \\  \e[B\e[7D"
                               "  ===  \e[2A");
  else if (piece & KNIGHT)
    stringbuffer_append_string(sb, "  <*^  \e[B\e[7D"
                               "  / |  \e[B\e[7D"
                               "  ===  \e[2A");
  else if (piece & ROOK)
    stringbuffer_append_string(sb, "  ooo  \e[B\e[7D"
                               "  | |  \e[B\e[7D"
                               "  ===  \e[2A");
  else if (piece & KING)
    stringbuffer_append_string(sb, "  ^+^  \e[B\e[7D"
                               "  )|(  \e[B\e[7D"
                               "  ===  \e[2A");
  else if (piece & QUEEN)
    stringbuffer_append_string(sb, "  oOo  \e[B\e[7D"
                               "  )|(  \e[B\e[7D"
                               "  ===  \e[2A");
  else
    stringbuffer_append_string(sb, "       \e[B\e[7D"
                               "       \e[B\e[7D"
                               "       \e[2A");
  char *s = stringbuffer_to_string(sb);

  stringbuffer_release(sb);
  return(s);
}

int __chess_init(module(chess) *exports) {
  clib_module_init(chess, exports);
  exports->svg_template = stringfn_trim(gsvg_templateData);
  {
    exports->stockfish     = calloc(1, sizeof(module(chess_stockfish)));
    exports->fen           = calloc(1, sizeof(module(chess_fen)));
    exports->fen->score    = calloc(1, sizeof(module(chess_stockfish)));
    exports->fen->is       = calloc(1, sizeof(module(chess_fen_is)));
    exports->fen->is->move = calloc(1, sizeof(module(chess_fen_is_move)));
    exports->fen->image    = calloc(1, sizeof(module(chess_fen_image)));
    exports->fen->get      = calloc(1, sizeof(module(chess_fen_get)));
  }
  {
    exports->fen->image->buffer   = __chess_fen_image;
    exports->fen->is->valid       = __chess_fen_valid;
    exports->fen->is->over        = __chess_fen_over;
    exports->fen->is->move->black = __chess_fen_is_black_move;
    exports->fen->is->move->white = __chess_fen_is_white_move;
    exports->fen->score->black    = __chess_fen_black_score;
    exports->fen->score->white    = __chess_fen_white_score;
    exports->fen->stats           = __chess_fen_stats;
    exports->fen->load           = __chess_fen_load;
    exports->fen->cmd             = __chess_render_fen_cmd;
    exports->fen->get->move       = __chess_fen_get_move;
    exports->fen->get->best       = __chess_fen_get_best;
    exports->fen->get->moves      = __chess_fen_get_moves;
    exports->fen->get->player     = __chess_fen_get_player_to_move;
    exports->fen->image->ansi     = __chess_fen_ansi;
    exports->stockfish->exec      = __chess_exec_stockfish;
  }
  return(EXIT_SUCCESS);
}

void __chess_deinit(module(chess) *exports) {
  free(exports->stockfish);
  free(exports->fen);
  free(exports->fen->is->move);
  free(exports->fen->is);
  free(exports->fen->image);
  free(exports->fen->get);
  clib_module_deinit(chess);
}

////////////////////////////////////////////

int scc(int code){
		if(code<0){
      fprintf(stderr, "SDL error: %s\n", SDL_GetError());
			exit(1);
		}
    return code;
}
void* scp(void* buf){
  if(buf == NULL){
    fprintf(stderr, "SDL error: %s\n", SDL_GetError());
    exit(1);
  }
  return buf;
}

void sdl_set_color_hex(SDL_Renderer* renderer, Uint32 color_hex){
  scc(SDL_SetRenderDrawColor(renderer,
                             (color_hex >> (3*8)) & 0xFF,
                             (color_hex >> (2*8)) & 0xFF,
                             (color_hex >> (1*8)) & 0xFF,
                             (color_hex >> (0*8)) & 0xFF));
}

void highlight_file(SDL_Renderer* renderer, Uint32 file){
  for(int i=0; i<8; i++){
    SDL_Rect mrect;
    mrect.x=PADDING+100*file;
    mrect.y=PADDING+100*i;
    mrect.w=100;
    mrect.h=100;
    sdl_set_color_hex(renderer, RED);
    SDL_RenderFillRect(renderer, &mrect);
  }
}

void highlight_col(SDL_Renderer* renderer, Uint32 col){
  for(int i=0; i<8; i++){
    SDL_Rect mrect;
    mrect.x=PADDING+100*i;
    mrect.y=PADDING+100*(7-col);
    mrect.w=100;
    mrect.h=100;
    sdl_set_color_hex(renderer, RED);
    SDL_RenderFillRect(renderer, &mrect);
  }
}

void highlight_sq(SDL_Renderer* renderer, int mouse_x, int mouse_y){
  if (mouse_x>PADDING+800 || mouse_y>PADDING+800 || mouse_x<PADDING || mouse_y<PADDING) return;
  int i=(mouse_x-PADDING)/100;
  int j=(mouse_y-PADDING)/100;
  SDL_Rect mrect;
  mrect.x=PADDING+100*i;
  mrect.y=PADDING+100*j;
  mrect.w=100;
  mrect.h=100;
  sdl_set_color_hex(renderer, GREEN);
  SDL_RenderFillRect(renderer, &mrect);
}
#define GRID_WIDTH 100
#define GRID_HEIGHT 100
void draw_grid(SDL_Renderer* renderer, int nb_cells, int mouse_x, int mouse_y, int mouse_pressed){
  for(int i=0; i<nb_cells; i++){
    for(int j=0; j<nb_cells; j++){
      SDL_Rect myrect;
      myrect.x=PADDING+GRID_WIDTH*i;
      myrect.y=PADDING+GRID_HEIGHT*j;
      myrect.w=GRID_WIDTH;
      myrect.h=GRID_HEIGHT;
      if(DEBUG_MODE)
        log_info("%dx%d|%dx%d|%dx%d",i,j,myrect.x,myrect.y,myrect.w,myrect.h);
      struct chess_piece_t *p;
      if((p=__chess_get_piece_at_position(myrect.x,myrect.y))){
        log_info("got piece!");
      }

      if((i+j)%2){
        sdl_set_color_hex(renderer, DARK);
      }
      else{
        sdl_set_color_hex(renderer, LIGHT);
      }
      SDL_RenderFillRect(renderer, &myrect);
    }
  }
  if(mouse_pressed) highlight_sq(renderer, mouse_x, mouse_y);
}
void __chess_sdl_init(void){

}

void __chess_sdl_loop(void){
  /*
  size_t len=chess_pieces[CHESS_PIECE_COLOR_WHITE][CHESS_PIECE_TYPE_ROOK].qoir.len();
  unsigned char *buf=NULL; qoir_decode_result *decoded=NULL;
  buf=calloc(len,sizeof(unsigned char *));
  memcpy(buf,chess_pieces[CHESS_PIECE_COLOR_WHITE][CHESS_PIECE_TYPE_ROOK].qoir.buf,len);
  Dn(len);
  decoded=__chess_sdl_decode_qoir(buf,len);
  Di(decoded->dst_pixbuf.pixcfg.width_in_pixels);
  Di(decoded->dst_pixbuf.pixcfg.height_in_pixels);
  */
  scc(SDL_Init(SDL_INIT_EVERYTHING));
  SDL_Window* window = scp(SDL_CreateWindow("First Window", 100, 100, SCREEN_WIDTH, SCREEN_HIGHT, SDL_WINDOW_BORDERLESS | SDL_WINDOW_ALWAYS_ON_TOP));
	SDL_Renderer* renderer = scp(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));
  int mouse_x;
  int mouse_y;
  int mouse_pressed=0;
  int file=8;
  int col=8;

	int quit=0;
	while(!quit){
		SDL_Event event;
		while(SDL_PollEvent(&event)){
			switch(event.type){
      case SDL_MOUSEBUTTONDOWN:{
        SDL_GetMouseState(&mouse_x, &mouse_y);
        mouse_pressed=1;
        printf("mouse coord: %i,%i\n", mouse_x, mouse_y); 
      } break;
      case SDL_KEYDOWN:{
        switch(event.key.keysym.sym){
        case SDLK_a:
          file=0;
          col=8;
          break;
        case SDLK_b: {
  SDL_Surface *s;
  size_t len=chess_pieces[CHESS_PIECE_COLOR_WHITE][CHESS_PIECE_TYPE_ROOK].qoir.len();
  unsigned char *buf=NULL; qoir_decode_result *decoded=NULL;
  buf=calloc(len,sizeof(unsigned char *));
  memcpy(buf,chess_pieces[CHESS_PIECE_COLOR_WHITE][CHESS_PIECE_TYPE_ROOK].qoir.buf,len);
  Dn(len);
  decoded=__chess_sdl_decode_qoir(buf,len);
  Di(decoded->dst_pixbuf.pixcfg.width_in_pixels);
  Di(decoded->dst_pixbuf.pixcfg.height_in_pixels);
  Ds(require(chess)->sdl.fen.text);
  if((s=__chess_decoded_surface(decoded))){
    log_info("got surface");
    SDL_RenderClear(renderer);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, s);
    SDL_RenderCopy(renderer, texture, NULL, &s->clip_rect);
    SDL_DestroyTexture(texture);
    SDL_RenderPresent(renderer);
    /*
    if(!(__chess_sdl_draw(window,s))){
      log_error("failed to draw surface");
    }
    */
    SDL_FreeSurface(s);
  }
          file=1;
          col=8;
                    }
          break;
        case SDLK_c:
          file=2;
          col=8;
          break;
        case SDLK_d:
          file=3;
          col=8;
          break;
        case SDLK_e:
          file=4;
          col=8;
          break;
        case SDLK_f:
          file=5;
          col=8;
          break;
        case SDLK_g:
          file=6;
          col=8;
          break;
        case SDLK_h:
          file=7;
          col=8;
          break;
        case SDLK_1:
          col=0;
          file=8;
          break;
        case SDLK_2:
          col=1;
          file=8;
          break;
        case SDLK_3:
          col=2;
          file=8;
          break;
        case SDLK_4:
          col=3;
          file=8;
          break;
        case SDLK_5:
          col=4;
          file=8;
          break;
        case SDLK_6:
          col=5;
          file=8;
          break;
        case SDLK_7:
          col=6;
          file=8;
          break;
        case SDLK_8:
          col=7;
          file=8;
          break;
        case SDLK_i:
          file=8;
          col=8;
          break;
        }
      } break;
			case SDL_QUIT:{
		    		quit=1;
			} break;
			}
		}
    scc(SDL_SetRenderDrawColor(renderer, 18, 18, 18, 255));
    scc(SDL_RenderClear(renderer));
    draw_grid(renderer, 8, mouse_x, mouse_y, mouse_pressed);
    if(file<8) highlight_file(renderer, file);
    if(col<8) highlight_col(renderer, col);
		SDL_RenderPresent(renderer);
	}

	SDL_Quit();
}

qoir_decode_result *__chess_sdl_decode_qoir(unsigned char *buf, size_t len){
  qoir_decode_options opts = {0};
  opts.pixfmt = QOIR_PIXEL_FORMAT__BGRA_PREMUL;
  qoir_decode_result *decode = calloc(1,sizeof(qoir_decode_result));
  *decode = qoir_decode(buf, len, &opts);
  free(buf);
  buf = NULL;
  len = 0;
  if (decode->status_message) {
    free(decode->owned_memory);
    fprintf(stderr, "main: load: could not decode file: %s\n",
            decode->status_message);
    return NULL;
  }
  return(decode);
}

SDL_Surface *__chess_decoded_surface(qoir_decode_result *decode){
  uint64_t now = SDL_GetPerformanceCounter();

  uint64_t elapsed = SDL_GetPerformanceCounter() - now;
  printf("%" PRIu64 " microseconds to decode %s.\n",
           (elapsed * 1000000) / SDL_GetPerformanceFrequency(),
           bytes_to_string(decode->dst_pixbuf.stride_in_bytes*decode->dst_pixbuf.pixcfg.height_in_pixels)
           );

  return SDL_CreateRGBSurfaceFrom(
      decode->dst_pixbuf.data, decode->dst_pixbuf.pixcfg.width_in_pixels,
      decode->dst_pixbuf.pixcfg.height_in_pixels, 32,
      decode->dst_pixbuf.stride_in_bytes,
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
      0x0000FF00, 0x00FF0000, 0xFF000000, 0x000000FF);
#else
      0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
#endif
}

bool __chess_sdl_draw(SDL_Window* window,SDL_Surface* surface) {
  SDL_Surface* ws = SDL_GetWindowSurface(window);
  if (!ws) {
    SDL_Renderer* r = SDL_CreateRenderer(window, -1, 0);
    if (!r) {
      fprintf(stderr, "main: draw: SDL_CreateRenderer: %s\n", SDL_GetError());
      return false;
    }
    SDL_RenderClear(r);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(r, surface);
    SDL_RenderCopy(r, texture, NULL, &surface->clip_rect);
    SDL_DestroyTexture(texture);
    SDL_RenderPresent(r);
    SDL_DestroyRenderer(r);
    return true;
  }

  // Use a direct approach.
  SDL_FillRect(ws, NULL, SDL_MapRGB(ws->format, 0x00, 0x00, 0x00));
  SDL_BlitSurface(surface, NULL, ws, NULL);
  SDL_UpdateWindowSurface(window);
  return true;
}
////////////////////////////////////////////
#endif
