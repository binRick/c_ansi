#include "../ansi-codes/ansi-codes.h"
#include "ansi-test.h"

int main(int argc, char **argv) {
  if ((argc >= 2) && (strcmp(argv[1], "--test") == 0)) {
    printf(AC_RESETALL AC_GREEN "OK\n" AC_RESETALL);
    printf(acsl(AC_RESETALL AC_GREEN "OK"));
  }
  HA();
}

