#pragma once
#ifndef TERM_TERMPAINT_H
#define TERM_TERMPAINT_H
/////////////////////////////////////////////////////////////////
//#include <assert.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <libgen.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
/////////////////////////////////////////////////////////////////
#include "submodules/c_string_buffer/include/stringbuffer.h"
#include "submodules/c_stringfn/include/stringfn.h"
/////////////////////////////////////////////////////////////////
//#include "submodules/c_palettes/palette-utils/palette-utils.h"
int term_termpaint_main(int argc, char *argv[]);

/////////////////////////////////////////////////////////////////

#endif
