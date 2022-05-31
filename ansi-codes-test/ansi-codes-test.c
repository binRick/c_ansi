#include "ansi-codes-test.h"
#include <assert.h>
#include <stdlib.h>
#define INCBIN_SILENCE_BITCODE_WARNING
#include "../submodules/http-get.c/src/http-get.h"
#include "../submodules/incbin/incbin.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


static int file_exists(const char *path) {
  struct stat b;

  return(stat(path, &b));
}

INCBIN(char, __TEST_INCLUDE_0__, "test-include-0.txt");


int main(int argc, char **argv) {
  (void)argc; (void)argv;

  printf("test-include-0.txt size:    %d\n", g__TEST_INCLUDE_0__Size);
  printf("test-include-0.txt content: %s\n", g__TEST_INCLUDE_0__Data);

  http_get_response_t *res = http_get("https://api.github.com/repos/clibs/clib/releases/latest");

  printf("\nok=%d\n", res->ok);
  printf("status=%lu\n", res->status);
  printf("content=%s\n\n", res->data);
  http_get_free(res);

  char *f = "./google.html";
  int  ok = http_get_file("http://google.com", f);

  printf("\nok=%d\n", ok);
  printf("file exists:%d\n\n", file_exists(f));


  printf("OK\n");
  return(0);
}
