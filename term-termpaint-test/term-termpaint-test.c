#include "term-termpaint-test.h"

int main(int argc, char **argv) {
  (void)argc; (void)argv;
  if ((argc >= 2) && (strcmp(argv[1], "--test") == 0)) {
    printf("Test OK\n"); return(0);
  }
  printf("ok\n");
  return(term_termpaint_main(argc, argv));
}
