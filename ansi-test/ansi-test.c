#include "../ansi-codes/ansi-codes.h"
#include "../ansi-utils/ansi-utils.c"
#include "../submodules/greatest/greatest.h"
#include "ansi-test.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

char cur_type = '\0';
int  term_x = 0, term_y = 0, cur_x = 0, cur_y = 0;


void at_top_right_text(){
  au_term_size(&term_x, &term_y);
  printf(AC_POS(2, 60) "OK\n");
}


void at_cur_pos(){
  //  AC_cur_pos(&term_x,&term_y, cur_type);
  printf(AC_RED AC_BOLD "x: %d\ty: %d" AC_RESETALL, term_x, term_y);
}


void at_term_size(){
  printf(AC_RED AC_BOLD "x: %d\ty: %d" AC_RESETALL, term_x, term_y);
}


TEST basic_ansi_test0(void) {
  PASSm("Basic Ansi Test 0 OK");
}


TEST basic_ansi_test(void *closure){
  int x = *(int *)closure;

  ASSERT(x == 1);
  ASSERT_EQ(1, x);
  ASSERT_GTE(1, x);
  ASSERT_GTEm("invalid terminal size", 1, x);
  ASSERT_EQm("Yikes, x doesn't equal 1", 1, x);
  ASSERT_EQ_FMT(1, x, "%d");

  ASSERT_IN_RANGEm("not between 0 and 2", 0, x, 2);

  PASSm("Basic Ansi Tests OK");
}

SUITE(the_suite) {
  int arg = 1;

  RUN_TEST1(basic_ansi_test, &arg);
}

/* Add definitions that need to be in the test runner's main file. */
GREATEST_MAIN_DEFS();


int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(the_suite);
  RUN_TEST(basic_ansi_test0);
  GREATEST_MAIN_END();
}


int old_main(int argc, char **argv) {
  HA();
  DO_ANSI_FXN("Terminal Size", at_term_size(), AC_GREEN_BLACK);
  colorB_set(229, 43, 80);
  printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
  //at_top_right_text();
  return(0);
}

