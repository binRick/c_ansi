#include "../ansi-codes/ansi-codes.h"
#include "../ansi-utils/ansi-utils.c"
#include "ansi-test.h"

int  term_x, term_y, cur_x, cur_y;
char cur_type;


void at_top_right_text(){
  au_term_size(&term_x, &term_y);
  printf(AC_POS(2, 60) "OK\n");
}


void at_cur_pos(){
  //  AC_cur_pos(&term_x,&term_y, cur_type);
  printf(AC_RED AC_BOLD "x: %d\ty: %d", term_x, term_y);
}


void at_term_size(){
  au_term_size(&term_x, &term_y);
  printf(AC_RED AC_BOLD "x: %d\ty: %d", term_x, term_y);
}


int main(int argc, char **argv) {
  HA();

  DO_ANSI_FXN("Terminal Size", at_term_size(), AC_GREEN_BLACK);
  colorB_set(229, 43, 80);
  printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
  //at_top_right_text();
}

