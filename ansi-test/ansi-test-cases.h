#pragma once
#ifndef AT_CASES
#define AT_CASES

#define HA_ALT_SCREEN()    { do {                                                                  \
                               _ANSI_ARG(alt - screen - on, AC_ALT_SCREEN_ON, "Alt Screen On");    \
                               _ANSI_ARG(alt - screen - off, AC_ALT_SCREEN_OFF, "Alt Screen Off"); \
                               _ANSI_ARG(test, AC_GREEN, "Test OK");                               \
                             } while (0); }

#define HA()               { do {                                                                        \
                               ANSI_ARG(test - start, AC_GREEN, "Test OK");                              \
                               ANSI_ARG(cursor - off, AC_HIDE_CURSOR, "Cursor is Off");                  \
                               ANSI_ARG(cursor - on, AC_SHOW_CURSOR, "Cursor is On");                    \
                               ANSI_ARG(cursor - red, AC_CURSOR_COLOR("red"), "Cursor is Red");          \
                               ANSI_ARG(cursor - black, AC_CURSOR_COLOR("black"), "Cursor is Black");    \
                               ANSI_ARG(cursor - white, AC_CURSOR_COLOR("white"), "Cursor is White");    \
                               ANSI_ARG(cursor - bar, AC_CURSOR_BAR, "Cursor is Bar");                   \
                               ANSI_ARG(cursor - under, AC_CURSOR_UNDER, "Cursor is Under");             \
                               ANSI_ARG(cursor - block, AC_CURSOR_BLOCK, "Cursor is Block");             \
                               ANSI_ARG(cursor - blue, AC_CURSOR_COLOR("blue"), "Cursor is Blue");       \
                               ANSI_ARG(cursor - yellow, AC_CURSOR_COLOR("yellow"), "Cursor is Yellow"); \
                               ANSI_ARG(test - end, AC_GREEN, "Test Done");                              \
                             } while (0); }

#endif
