#include "ansi-utils-test.h"


int main(int argc, char **argv) {
  (void)argc; (void)argv;
  printf("ok\n");
  const unsigned char S[]   = "\e[1m\e[38;2;255;128;255mPINK\e[0m";
  char *SE = strdup_escaped(S);
  printf("S:'%s'\n",S);
  printf("SE:'%s'\n",SE);
  return(0);
}
