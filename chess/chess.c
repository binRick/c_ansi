#pragma once
#ifndef CHESS_C
#define CHESS_C
#define DEBUG_MODE false
#define CHESS_DEFAULT_DEPTH 10
////////////////////////////////////////////
#include "chess/chess.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "glib.h"
#include "vips/vips.h"
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
#include "fen2svg/unsortedlinkedlist.h"
#include "fen2svg/fen2svg.h"
#include "incbin/incbin.h"
#include "which/src/which.h"
#include "str/str.h"
#include "tempdir.c/tempdir.h"
#define STOCKFISH_EVALUATE_FEN_FMT "printf \"position fen %s\\ngo depth %d\" | %s"
INCTXT(svg_template,"assets/template.svg");
#define SVG_FILE "dia00001.svg"
static char *__chess_print_piece(uint8_t piece);
static char *__chess_render_fen_cmd(char *fen, int depth);
char *__chess_fen_ansi(char *fen);
////////////////////////////////////////////

static char *__chess_render_fen_cmd(char *fen, int depth){
  char *s;
  asprintf(&s,STOCKFISH_EVALUATE_FEN_FMT,fen,depth,which("stockfish"));
  return(s);
}

int __chess_fen_black_score(char *fen){
  Board board;
  load_fen(&board, fen);
  int scores[2];
  get_material_scores(&board,&scores[0],&scores[1]);
  return(scores[1]);
}

int __chess_fen_white_score(char *fen){
  Board board;
  load_fen(&board, fen);
  int scores[2];
  get_material_scores(&board,&scores[0],&scores[1]);
  return(scores[0]);
}

bool __chess_fen_print(char *fen){
  Board board;
  load_fen(&board, fen);
  print_fancy(&board);
  return(true);
}

unsigned char *__chess_fen_image(char *fen, char *fmt, size_t *len){
  *len=0;
  VipsImage *image_svg;
  int argc=6,r=rand()%1000;
  char *fen_file,*template,*dir,*j,*tempdir,*svg,*_fmt,*svg_file;
  unsigned char *png;

  asprintf(&tempdir,"%s%lld-%d",gettempdir(),timestamp(),r);
  fsio_mkdirs(tempdir,0777);
  asprintf(&fen_file,"%s/%lld.fen",tempdir,timestamp());
  asprintf(&svg_file,"%s/%s",tempdir,SVG_FILE);
  asprintf(&template,"%s/template.svg",tempdir);
  char *argv[] = {"./fen2svg","-b","-c","-m","-f",fen_file,NULL};
  j= stringfn_join(argv," ",0,argc);
  dir=getwd(0);
  chdir(tempdir);
  fsio_write_text_file(fen_file,fen);
  fsio_write_text_file(template,require(chess)->svg_template);
  if(fsio_file_exists(svg_file))
    fsio_remove(SVG_FILE);
  if(fen2svg_main(argc,argv)!=0){
    log_error("Failed to generate svg from fen");
    return(NULL);
  }
  if(!fsio_file_exists(SVG_FILE)){
    log_error("Failed to find svg file %s",SVG_FILE);
    return(NULL);
  }
  svg=fsio_read_text_file(SVG_FILE);
  fsio_remove(SVG_FILE);
  fsio_remove(fen_file);
  fsio_remove(template);
  chdir(dir);
  fsio_remove(tempdir);
  if(!(image_svg=vips_image_new_from_buffer((const void*)svg,strlen(svg),"",NULL))){
    log_error("Failed to decode svg");
    return 0;
  }
  if(DEBUG_MODE)
    log_info("%dx%d",
      vips_image_get_width(image_svg),
      vips_image_get_height(image_svg)
      );

  asprintf(&_fmt,".%s",fmt);
  if(vips_image_write_to_buffer(image_svg,_fmt,&png,len,NULL)){
    log_error("Failed to write %s buffer",fmt);
    return(NULL);
  }
  free(_fmt);
  g_object_unref(image_svg);
  return(png);
}

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
  free(f);

//  stop_engine(&white_engine);
}

char *__chess_fen_get_move(const char *fen){
  char *move;
  char *res=require(chess)->stockfish->exec(require(chess)->fen->cmd(fen,CHESS_DEFAULT_DEPTH));
  if(stringfn_starts_with(res,"bestmove")){
    struct StringFNStrings words= stringfn_split_words(res);
    move=strdup(words.strings[words.count-1]);
  }
  return(move);
}

char *__chess_exec_stockfish(const char *cmd){
  size_t buf_len=1024;
  const char  *command_line[] = { which("sh"),"-c", cmd, NULL};
  struct subprocess_s proc;
  int result,ret;
  unsigned index = 0;
  unsigned bytes_read = 0;
  static char data[1048576 + 1] = {0};
  if((result= subprocess_create(command_line, subprocess_option_enable_async, &proc))!=0){
    log_error("subprocess error");
    return(NULL);
  }
  do {
    bytes_read = subprocess_read_stdout(&proc, data + index,sizeof(data) - 1 - index);
    index += bytes_read;
  } while (bytes_read != 0);
  subprocess_join(&proc, &ret);
  subprocess_destroy(&proc);
  char *s;
  if(strlen(data)>0){
    stringfn_mut_trim((char*)data);
    struct StringFNStrings lines=stringfn_split_lines_and_trim((char*)data);
    if(lines.count>0)
      s = strdup(lines.strings[lines.count-1]);
    stringfn_release_strings_struct(lines);
  }
  return(s);
}

bool __chess_fen_over(const char *fen){
  Board board;
  load_fen(&board, fen);
  int s[2]={0,0};
  get_material_scores(&board, &(s[0]), &(s[1]));
  return(is_gameover(&board));
}

bool __chess_fen_valid(const char *fen){
  Board board;
  load_fen(&board, fen);
  int s[2]={0,0};
  get_material_scores(&board, &(s[0]), &(s[1]));
  return(s[0]>0&&s[1]>0);
}

char *__chess_fen_get_player_to_move(char *fen){
  if(require(chess)->fen->is->move->white(fen))
    return "white";
  else if(require(chess)->fen->is->move->black(fen))
    return "black";
  return "UNKNOWN";
}

////////////////////////////////////////////
bool __chess_fen_is_white_move(const char *fen){
  Board *board=calloc(1,sizeof(Board));
  load_fen(board, fen);
  bool move;
  move = (board->to_move==1);
  free(board);
  return(move);
}

bool __chess_fen_is_black_move(const char *fen){
  Board *board=calloc(1,sizeof(Board));
  load_fen(board, fen);
  bool move;
  move = (board->to_move==0);
  free(board);
  return(move);
}

char *__chess_fen_stats(char *fen){
    char *s;
    struct StringBuffer *sb=stringbuffer_new();
    int LIGHT= 179;
    int DARK=  58;
    Board *board=calloc(1,sizeof(Board));
    load_fen(board, fen);
    if (board->to_move == 1)
        stringbuffer_append_string(sb,"Black");
    else if (board->to_move == 0)
        stringbuffer_append_string(sb,"White");
    stringbuffer_append_string(sb," to move.\nCastling: ");
    if (board->castling & 0x08)
        stringbuffer_append_string(sb,"K");
    if (board->castling & 0x04)
        stringbuffer_append_string(sb,"Q");
    if (board->castling & 0x02)
        stringbuffer_append_string(sb,"k");
    if (board->castling & 0x01)
        stringbuffer_append_string(sb,"q");
    stringbuffer_append_string(sb,"\nEn pessant: ");
    if (board->en_p == -1)
      stringbuffer_append_string(sb,"None\n");
    else{
      asprintf(&s,"%c%d\n", (board->en_p % 8) + 'a', 8 - (board->en_p / 8));
      stringbuffer_append_string(sb,s);
    }
    asprintf(&s,"Halfmoves: %d\nFullmoves: %d\n", board->halfmoves, board->moves);
    stringbuffer_append_string(sb,s);
    asprintf(&s,"Whiteking_pos: %c%d\n", (board->wking_pos % 8) + 'a',
            8 - (board->wking_pos / 8));
    stringbuffer_append_string(sb,s);
    asprintf(&s,"Blackking_pos: %c%d\n", (board->bking_pos % 8) + 'a',
            8 - (board->bking_pos / 8));
    stringbuffer_append_string(sb,s);
    free(board);
    s =stringbuffer_to_string(sb);
    stringbuffer_release(sb);
    stringfn_mut_trim(s);
    return(s);
}
char *__chess_fen_ansi(char *fen){   
    struct StringBuffer *sb=stringbuffer_new();
    int LIGHT= 179, DARK=  58,i;
    Board *board=calloc(1,sizeof(Board));
    load_fen(board, fen);
    stringbuffer_append_string(sb,"   \u2554");
    for (i = 0; i < 56; ++i)
      stringbuffer_append_string(sb,"\u2550");
    stringbuffer_append_string(sb,"\u2557");
    int white_score[6];
    int black_score[6];
    const char* piece_chars = "pbnrq";
    get_material_scores(board, white_score, black_score);
    char *s;
    asprintf(&s," %s: ", strlen(board->black_name) ? board->black_name : "Black");
    stringbuffer_append_string(sb,s);
    if (white_score[0] - black_score[0] < 0){
        asprintf(&s,"%+d ", black_score[0]-white_score[0]);
        stringbuffer_append_string(sb,s);
    }
    int j;
    for (i = 1; i < 6; ++i)
        for (j = 0; j < white_score[6 - i]; ++j)
          stringbuffer_append(sb,piece_chars[5-i]-32);
    stringbuffer_append_string(sb,"\n");
    
    for (i = 0; i < 24; ++i)
    {
        if (i % 3 == 1){
          asprintf(&s,"%+d \u2551",8-(i/3));
        }else{
          asprintf(&s,"   \u2551");
        }
        stringbuffer_append_string(sb,s);
        int j;
        for (j = 0; j < 8; ++j)
          stringbuffer_append_string(sb,"       ");
        stringbuffer_append_string(sb,"\u2551\n");
    }
    stringbuffer_append_string(sb,"   \u255a");
    for (i = 0; i < 56; ++i)
        stringbuffer_append_string(sb,"\u2550");
    asprintf(&s," %s: ", board->white_name);
    stringbuffer_append_string(sb,s);
    if (white_score[0] - black_score[0] > 0){
      asprintf(&s,"%+d ", white_score[0] - black_score[0]);
      stringbuffer_append_string(sb,s);
    }
    for (i = 1; i < 6; ++i)
        for (j = 0; j < black_score[6 - i]; ++j)
          stringbuffer_append(sb,piece_chars[5 - i]);
    stringbuffer_append_string(sb,"\n       ");
    for (i = 0; i < 8; ++i){
      asprintf(&s,"%c      ", 'a' + i);
      stringbuffer_append_string(sb,s);
    }
    stringbuffer_append_string(sb,"\n");
    stringbuffer_append_string(sb,"\e[26F\e[4C");

    Move prev_move;
    if (board->history_count > 0)
        prev_move = board->history[board->history_count - 1];
    else 
        prev_move = board->history[board->history_count];
    int8_t prev_src = prev_move.src_rank * 8 + prev_move.src_file;
    int8_t prev_dest = prev_move.dest;

    for (i = 0; i < 64; ++i)
    {
        /* Bullshit that colors them checkered-like 
         * - Courtesy of Zach Gorman
         */
        uint8_t square = board->position[i];
        if (prev_dest != -1 && (i == prev_src || i == prev_dest))
        {
            if (i == prev_src)
                stringbuffer_append_string(sb,"\e[48;5;6m");
            if (i == prev_dest)
                stringbuffer_append_string(sb,"\e[48;5;12m");
        }
        else
        {
            if (!(!(i & 1) ^ !(i & 8))) {
              asprintf(&s,"\e[48;5;%dm", LIGHT);
            }else{
              asprintf(&s,"\e[48;5;%dm", DARK);
            }
            stringbuffer_append_string(sb,s);
        }

        stringbuffer_append_string(sb,"\e[1m");
        (square & BLACK) ? stringbuffer_append_string(sb,"\e[38;5;232m") : stringbuffer_append_string(sb,"\e[37m");
        stringbuffer_append_string(sb,__chess_print_piece(square));
        stringbuffer_append_string(sb,"\e[0m");

        if (i % 8 == 7)
           stringbuffer_append_string(sb,"\u2551\e[3E\e[4C");
    }
    stringbuffer_append_string(sb,"\e[8E\n");
    free(board);
    s=stringbuffer_to_string(sb);
    stringbuffer_release(sb);
    stringfn_mut_trim(s);
    return(s);
}
static char *__chess_print_piece(uint8_t piece){
    struct StringBuffer *sb=stringbuffer_new();
    if (piece & PAWN)
    {
        stringbuffer_append_string(sb,"   O   \e[B\e[7D"
               "  ( )  \e[B\e[7D"
               "  ===  \e[2A");
    }
    else if (piece & BISHOP)
    {
        stringbuffer_append_string(sb,"  (/)  \e[B\e[7D"
               "  / \\  \e[B\e[7D"
               "  ===  \e[2A");
    }
    else if (piece & KNIGHT)
    {
        stringbuffer_append_string(sb,"  <*^  \e[B\e[7D"
               "  / |  \e[B\e[7D"
               "  ===  \e[2A");
    }
    else if (piece & ROOK)
    {
        stringbuffer_append_string(sb,"  ooo  \e[B\e[7D"
               "  | |  \e[B\e[7D"
               "  ===  \e[2A");
    }
    else if (piece & KING)
    {
        stringbuffer_append_string(sb,"  ^+^  \e[B\e[7D"
               "  )|(  \e[B\e[7D"
               "  ===  \e[2A");
    }
    else if (piece & QUEEN)
    {
        stringbuffer_append_string(sb,"  oOo  \e[B\e[7D"
               "  )|(  \e[B\e[7D"
               "  ===  \e[2A");
    }
    else
        stringbuffer_append_string(sb,"       \e[B\e[7D"
               "       \e[B\e[7D"
               "       \e[2A");
    char *s=stringbuffer_to_string(sb);
    stringbuffer_release(sb);
    return(s);
}
int __chess_init(module(chess) *exports) {
  clib_module_init(chess, exports);
  exports->svg_template=stringfn_trim(gsvg_templateData);
  {
    exports->stockfish=calloc(1,sizeof(module(chess_stockfish)));
    exports->fen=calloc(1,sizeof(module(chess_fen)));
    exports->fen->score=calloc(1,sizeof(module(chess_stockfish)));
    exports->fen->is=calloc(1,sizeof(module(chess_fen_is)));
    exports->fen->is->move=calloc(1,sizeof(module(chess_fen_is_move)));
    exports->fen->image=calloc(1,sizeof(module(chess_fen_image)));
    exports->fen->get=calloc(1,sizeof(module(chess_fen_get)));
  }
  {
    exports->fen->print=__chess_fen_print;
    exports->fen->image->buffer=__chess_fen_image;
    exports->fen->is->valid=__chess_fen_valid;
    exports->fen->is->over=__chess_fen_over;
    exports->fen->is->move->black=__chess_fen_is_black_move;
    exports->fen->is->move->white=__chess_fen_is_white_move;
    exports->fen->score->black=__chess_fen_black_score;
    exports->fen->score->white=__chess_fen_white_score;
    exports->fen->stats=__chess_fen_stats;
    exports->fen->cmd=__chess_render_fen_cmd;
    exports->fen->get->move=__chess_fen_get_move;
    exports->fen->get->player=__chess_fen_get_player_to_move;
    exports->fen->image->ansi=__chess_fen_ansi;
    exports->stockfish->exec=__chess_exec_stockfish;
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
#endif
