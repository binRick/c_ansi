#pragma once
#ifndef TERM_CODEST_TEST_H
#define TRUE_CODES_TEST_H
#include "../ansi-codes/ansi-codes.h"
#include "../submodules/cargs/include/cargs.h"
#include <assert.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdint.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <sys/time.h>

int parse_args(int argc, char *argv[]);
int debug_args();

typedef struct CLI_ARGS {
  char *mode;
  bool verbose;
  int  count;
  bool pretty;
  int  color;
  char *palette;
  char *file;
} args_t;

static struct cag_option options[] = {
  { .identifier     = 'm',
    .access_letters = "m",
    .access_name    = "mode",
    .value_name     = "MODE",
    .description    = "Mode" },
  { .identifier     = 'v',
    .access_letters = "v",
    .access_name    = "verbose",
    .value_name     = NULL,
    .description    = "Verbose Mode" },
  { .identifier     = 'c',
    .access_letters = "c",
    .access_name    = "count",
    .value_name     = "COUNT",
    .description    = "Item Count" },
  { .identifier     = 'P',
    .access_letters = "P",
    .access_name    = "pretty",
    .value_name     = NULL,
    .description    = "JSON Pretty Mode" },
  { .identifier     = 'x',
    .access_letters = "C",
    .access_name    = "color",
    .value_name     = NULL,
    .description    = "Color Mode" },
  { .identifier     = 'p',
    .access_letters = "p",
    .access_name    = "palette",
    .value_name     = "PALETTE",
    .description    = "Palette" },
  { .identifier     = 'f',
    .access_letters = "f",
    .access_name    = "file",
    .value_name     = "FILE",
    .description    = "Palette File" },
  { .identifier     = 'h',
    .access_letters = "h",
    .access_name    = "help",
    .description    = "Shows the command help" }
};


#endif
