#include "tp-test.h"
#include "tp.h"
#include <assert.h>
#include <fcntl.h>
#include <pthread.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
module(tp_confirm) * B;
module(tp_tab) * T;
#define TABS_QTY       5
#define OPTIONS_QTY    45
#define NEW_TAB(NUM, SELECTED)               \
  do {                                       \
    char            *text;                   \
    asprintf(&text, "Tab %lu", (size_t)NUM); \
    struct tp_tab_t *O = T->init_tab(text);  \
    O->selected = SELECTED;                  \
    T->add_tab(O);                           \
  } while (0)
#define NEW_OPTION(NUM, SELECTED)                         \
  do {                                                    \
    char                       *text;                     \
    asprintf(&text, "Option %lu", (size_t)NUM);           \
    struct tp_confirm_option_t *O = B->init_option(text); \
    O->selected = SELECTED;                               \
    B->add_option(O);                                     \
  } while (0)

int main(int argc, char **argv) {
  assert(term_init() == EXIT_SUCCESS);
  {
    B = require(tp_confirm);
    NEW_OPTION(99, false);
    for (int i = 1; i <= OPTIONS_QTY; i++) {
      if (i == (int)(OPTIONS_QTY / 2)) {
        NEW_OPTION(i, true);
      }else{
        NEW_OPTION(i, false);
      }
    }
    T = require(tp_tab);
    NEW_TAB(1, false);
    NEW_TAB(2, true);
    NEW_TAB(2, false);
    fprintf(stderr, "# tabs:  %lu\n", T->get_tabs_qty());
    fprintf(stderr, "# options:  %lu\n", B->get_options_qty());
    fflush(STDIN_FILENO);
    fflush(stderr);
    printf(AC_HIDE_CURSOR);
    printf(AC_SHOW_CURSOR);
    fprintf(stderr, "render ended\n");
  }

  return(term_tests_main(argc, argv));
}
