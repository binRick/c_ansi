#pragma once
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "../ansi-codes/ansi-codes.h"
#define X_STR(STR)     #STR
#define ANSI_ARG(S, M, C){ do{                                                      \
    if ((argc >= 2) && (strcmp(argv[1], X_STR(--S)) == 0)) \
    printf(acsl(AC_RESETALL AC_YELLOW C M));               \
}while (0); }
#define HA()           { do {                                                                        \
    ANSI_ARG(test, AC_GREEN, "Test OK");                                      \
    ANSI_ARG(save-palette, AC_SAVE_PALETTE, "Palette Saved");               \
    ANSI_ARG(load-palette, AC_LOAD_PALETTE, "Palette Loaded");              \
    ANSI_ARG(cursor-off, AC_HIDE_CURSOR, "Cursor is Off");                  \
    ANSI_ARG(cursor-on, AC_SHOW_CURSOR, "Cursor is On");                    \
    ANSI_ARG(cursor-red, AC_CURSOR_COLOR("red"), "Cursor is Red");          \
    ANSI_ARG(cursor-yellow, AC_CURSOR_COLOR("yellow"), "Cursor is Yellow"); \
    ANSI_ARG(cursor-blue, AC_CURSOR_COLOR("blue"), "Cursor is Blue");       \
    ANSI_ARG(cursor-black, AC_CURSOR_COLOR("black"), "Cursor is Black");    \
    ANSI_ARG(cursor-white, AC_CURSOR_COLOR("white"), "Cursor is White");    \
    ANSI_ARG(cursor-bar, AC_CURSOR_BAR, "Cursor is Bar");                   \
    ANSI_ARG(cursor-under, AC_CURSOR_UNDER, "Cursor is Under");             \
    ANSI_ARG(cursor-block, AC_CURSOR_BLOCK, "Cursor is Block");             \
}while (0); }

