///////////////////////////////////////////////////////////////////
#include <assert.h>
#include <stdlib.h>
#define INCBIN_SILENCE_BITCODE_WARNING
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
///////////////////////////////////////////////////////////////////
#include "ansi-codes-test/ansi-codes-test.h"
#include "submodules/http-get.c/src/http-get.h"
#include "submodules/incbin/incbin.h"
///////////////////////////////////////////////////////////////////
INCBIN(char, __TEST_INCLUDE_0__, "test-include-0.txt");


int main(int argc, char **argv) {
  (void)argc; (void)argv;

  printf("test-include-0.txt size:    %d\n", g__TEST_INCLUDE_0__Size);
  printf("test-include-0.txt content: %s\n", g__TEST_INCLUDE_0__Data);
  printf("OK\n");
  return(0);
}

