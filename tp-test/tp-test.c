#include "tp-test.h"
#include "tp.h"
module(tp_confirm) * B;
#define OPTIONS_QTY    45
#define NEW_OPTION(NUM, SELECTED)                         \
  do {                                                    \
    char                       *text;                     \
    asprintf(&text, "Option %d", NUM);                    \
    struct tp_confirm_option_t *O = B->init_option(text); \
    O->selected = SELECTED;                               \
    B->add_option(O);                                     \
  } while (0)

int main(int argc, char **argv) {
  (void)argc; (void)argv;
  if ((argc >= 2) && (strcmp(argv[1], "--test") == 0)) {
    printf("Test OK\n"); return(0);
  }
  printf("ok\n");

  {
    B = require(tp_confirm);
    for (int i = 1; i <= OPTIONS_QTY; i++) {
      if (i == (int)(OPTIONS_QTY / 2)) {
        NEW_OPTION(i, true);
      }else{
        NEW_OPTION(i, false);
      }
    }

    struct tp_confirm_option_t *O = B->init_option("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"); 
    B->add_option(O);                                     

    printf("# options:  %lu\n", B->get_options_qty());
    fflush(STDIN_FILENO);
    fflush(stdout);
    printf(AC_HIDE_CURSOR);
    printf(AC_SHOW_CURSOR);
    printf("render ended\n");
  }

  return(term_tests_main(argc, argv));
}
