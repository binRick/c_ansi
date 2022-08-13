#include "tp-test.h"
#include "tp.h"
module(tp_confirm) * B;

int main(int argc, char **argv) {
  (void)argc; (void)argv;
  if ((argc >= 2) && (strcmp(argv[1], "--test") == 0)) {
    printf("Test OK\n"); return(0);
  }
  printf("ok\n");

  {
    B = require(tp_confirm);
    struct tp_confirm_option_t *O1 = B->init_option("Option 1");
    B->add_option(O1);
    struct tp_confirm_option_t *O2 = B->init_option("Option 2");
    O2->selected = true;
    B->add_option(O2);
    struct tp_confirm_option_t *O3 = B->init_option("Option 3");
    B->add_option(O3);
    struct tp_confirm_option_t *O4 = B->init_option("Option 4");
    B->add_option(O4);
    struct tp_confirm_option_t *O5 = B->init_option("Option 5");
    B->add_option(O5);
    struct tp_confirm_option_t *O6 = B->init_option("Option 6");
    B->add_option(O6);
    struct tp_confirm_option_t *O7 = B->init_option("Option 7");
    B->add_option(O7);
    struct tp_confirm_option_t *O8 = B->init_option("Option 8");
    B->add_option(O8);
    struct tp_confirm_option_t *O9 = B->init_option("Option 9");
    B->add_option(O9);
    printf("# options:  %lu\n", B->get_options_qty());
    fflush(STDIN_FILENO);
    fflush(stdout);
    printf(AC_HIDE_CURSOR);
    printf(AC_SHOW_CURSOR);
    printf("render ended\n");
  }

  return(term_tests_main(argc, argv));
}
