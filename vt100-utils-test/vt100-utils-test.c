#include "ansi-codes.h"
#include "ansi-codes.h"
#include "module/def.h"
#include "module/module.h"
#include "module/require.h"
#include "vt100-utils-test/vt100-utils-test.h"
#include "vt100-utils/vt100-utils.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
/////////////////////////////////////////////////////////////////
module(ac_confirm) * B;

/////////////////////////////////////////////////////////////////
int main(const int argc, const char **argv) {
  if (!isatty(STDOUT_FILENO)) {
    fprintf(stderr, "NO TTY!\n");
    return(1);
  }
  {
    B = require(ac_confirm);
  }

  {
    struct ac_confirm_option_t *O1 = B->init_option("Option 1");
    B->add_option(O1);
    struct ac_confirm_option_t *O2 = B->init_option("Option 2");
    O2->selected = true;
    B->add_option(O2);
    struct ac_confirm_option_t *O3 = B->init_option("Option 3");
    B->add_option(O3);
    struct ac_confirm_option_t *O4 = B->init_option("Option 4");
    B->add_option(O4);
    struct ac_confirm_option_t *O5 = B->init_option("Option 5");
    B->add_option(O5);
    struct ac_confirm_option_t *O6 = B->init_option("Option 6");
    B->add_option(O6);
    struct ac_confirm_option_t *O7 = B->init_option("Option 7");
    B->add_option(O7);
    struct ac_confirm_option_t *O8 = B->init_option("Option 8");
    B->add_option(O8);
    struct ac_confirm_option_t *O9 = B->init_option("Option 9");
    B->add_option(O9);
    printf("# options:  %lu\n", B->get_options_qty());
    fflush(STDIN_FILENO);
    fflush(stdout);
    printf(AC_HIDE_CURSOR);
    B->render_ui();
    printf(AC_SHOW_CURSOR);
    printf("render ended\n");
  }
  return(EXIT_SUCCESS);
} /* main */
