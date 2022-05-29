#pragma once
#include <stdio.h>
#include <string.h>
#ifndef ANSI_CODES_H
#define ANSI_CODES_H

#define color_reset() \
  printf("\x1b[0m")

#define color_set(r, g, b) \
  printf("\x1b[38;2;%d;%d;%dm", r, g, b)

#define colorB_set(br, bg, bb) \
  printf("\x1b[48;2;%d;%d;%dm", br, bg, bb)

#define colorAll_set(r, g, b, br, bg, bb) \
  printf("\x1b[38;2;%d;%d;%d;48;2;%d;%d;%dm", r, g, b, br, bg, bb)

#define color256_set(code) \
  printf("\x1b[38;5;%dm", code)

#define color256B_set(code) \
  printf("\x1b[48;5;%dm", code)

#define ACCSI     "\e["
#define ACCSIP    "\e[?"
#define ACOSC     "\e]"
#define ACDCS     "\e(B"
#define ACDEC     "\e(0"
#define ACRIS     "\ec"
#define ACBCK     "\u007f"
#define ACPAS     "\u001a"

#define ACCUU(times)      (AC_cur(times, 'A'))
#define ACCUD(times)      (AC_cur(times, 'B'))
#define ACCUF(times)      (AC_cur(times, 'C'))
#define ACCUB(times)      (AC_cur(times, 'D'))
#define ACCNL(times)      (AC_cur(times, 'E'))
#define ACCPL(times)      (AC_cur(times, 'F'))
#define ACCHA(times)      (AC_cur(times, 'G'))
#define ACCUP(x, y)       (AC_cur_pos(x, y, 'H'))
#define ACHVP(x, y)       (AC_cur_pos(x, y, 'f'))


#define ACSSR(t, b, r)    {                                                      \
    r = (char *)calloc(strlen(ACCSI) + 3 + strlen(t) + strlen(b), sizeof(char)); \
    strcat(r, ACCSI);                                                            \
    strcat(r, t);                                                                \
    strcat(r, ";");                                                              \
    strcat(r, b);                                                                \
    strcat(r, "r\0");                                                            \
}
#define ACTKN(token)      (#token)


#define acs(s)            AC_RESETALL s AC_RESETALL
#define acsl(s)           AC_RESETALL s AC_RESETALL "\n"
#define ansistr(s)        s AC_RESETALL
#define ansistrln(s)      s AC_RESETALL "\n"

#define AC_ESC                         "\x1b"
#define AC_RESETALL                    AC_ESC "[0m"

#define AC_BLACK                       "\x1b[30m"
#define AC_BLACK_BLACK                 "\x1b[30m\x1b[40m"
#define AC_BLACK_RED                   "\x1b[30m\x1b[41m"
#define AC_BLACK_GREEN                 "\x1b[30m\x1b[42m"
#define AC_BLACK_YELLOW                "\x1b[30m\x1b[43m"
#define AC_BLACK_BLUE                  "\x1b[30m\x1b[44m"
#define AC_BLACK_MAGENTA               "\x1b[30m\x1b[45m"
#define AC_BLACK_CYAN                  "\x1b[30m\x1b[46m"
#define AC_BLACK_WHITE                 "\x1b[30m\x1b[47m"
#define AC_BRIGHT_BLACK                "\x1b[30;1m"
#define AC_BRIGHT_BLACK_BLACK          "\x1b[30;1m\x1b[40m"
#define AC_BRIGHT_BLACK_RED            "\x1b[30;1m\x1b[41m"
#define AC_BRIGHT_BLACK_GREEN          "\x1b[30;1m\x1b[42m"
#define AC_BRIGHT_BLACK_YELLOW         "\x1b[30;1m\x1b[43m"
#define AC_BRIGHT_BLACK_BLUE           "\x1b[30;1m\x1b[44m"
#define AC_BRIGHT_BLACK_MAGENTA        "\x1b[30;1m\x1b[45m"
#define AC_BRIGHT_BLACK_CYAN           "\x1b[30;1m\x1b[46m"
#define AC_BRIGHT_BLACK_WHITE          "\x1b[30;1m\x1b[47m"

#define AC_RED_CODE                    "31"
#define AC_RED                         "\x1b[31m"
#define AC_RED_BLACK                   "\x1b[31m\x1b[40m"
#define AC_RED_RED                     "\x1b[31m\x1b[41m"
#define AC_RED_GREEN                   "\x1b[31m\x1b[42m"
#define AC_RED_YELLOW                  "\x1b[31m\x1b[43m"
#define AC_RED_BLUE                    "\x1b[31m\x1b[44m"
#define AC_RED_MAGENTA                 "\x1b[31m\x1b[45m"
#define AC_RED_CYAN                    "\x1b[31m\x1b[46m"
#define AC_RED_WHITE                   "\x1b[31m\x1b[47m"
#define AC_BRIGHT_RED                  "\x1b[31;1m"
#define AC_BRIGHT_RED_BLACK            "\x1b[31;1m\x1b[40m"
#define AC_BRIGHT_RED_RED              "\x1b[31;1m\x1b[41m"
#define AC_BRIGHT_RED_GREEN            "\x1b[31;1m\x1b[42m"
#define AC_BRIGHT_RED_YELLOW           "\x1b[31;1m\x1b[43m"
#define AC_BRIGHT_RED_BLUE             "\x1b[31;1m\x1b[44m"
#define AC_BRIGHT_RED_MAGENTA          "\x1b[31;1m\x1b[45m"
#define AC_BRIGHT_RED_CYAN             "\x1b[31;1m\x1b[46m"
#define AC_BRIGHT_RED_WHITE            "\x1b[31;1m\x1b[47m"

#define AC_GREEN                       "\x1b[32m"
#define AC_GREEN_BLACK                 "\x1b[32m\x1b[40m"
#define AC_GREEN_RED                   "\x1b[32m\x1b[41m"
#define AC_GREEN_GREEN                 "\x1b[32m\x1b[42m"
#define AC_GREEN_YELLOW                "\x1b[32m\x1b[43m"
#define AC_GREEN_BLUE                  "\x1b[32m\x1b[44m"
#define AC_GREEN_MAGENTA               "\x1b[32m\x1b[45m"
#define AC_GREEN_CYAN                  "\x1b[32m\x1b[46m"
#define AC_GREEN_WHITE                 "\x1b[32m\x1b[47m"
#define AC_BRIGHT_GREEN                "\x1b[32;1m"
#define AC_BRIGHT_GREEN_BLACK          "\x1b[32;1m\x1b[40m"
#define AC_BRIGHT_GREEN_RED            "\x1b[32;1m\x1b[41m"
#define AC_BRIGHT_GREEN_GREEN          "\x1b[32;1m\x1b[42m"
#define AC_BRIGHT_GREEN_YELLOW         "\x1b[32;1m\x1b[43m"
#define AC_BRIGHT_GREEN_BLUE           "\x1b[32;1m\x1b[44m"
#define AC_BRIGHT_GREEN_MAGENTA        "\x1b[32;1m\x1b[45m"
#define AC_BRIGHT_GREEN_CYAN           "\x1b[32;1m\x1b[46m"
#define AC_BRIGHT_GREEN_WHITE          "\x1b[32;1m\x1b[47m"

#define AC_YELLOW                      "\x1b[33m"
#define AC_YELLOW_BLACK                "\x1b[33m\x1b[40m"
#define AC_YELLOW_RED                  "\x1b[33m\x1b[41m"
#define AC_YELLOW_GREEN                "\x1b[33m\x1b[42m"
#define AC_YELLOW_YELLOW               "\x1b[33m\x1b[43m"
#define AC_YELLOW_BLUE                 "\x1b[33m\x1b[44m"
#define AC_YELLOW_MAGENTA              "\x1b[33m\x1b[45m"
#define AC_YELLOW_CYAN                 "\x1b[33m\x1b[46m"
#define AC_YELLOW_WHITE                "\x1b[33m\x1b[47m"
#define AC_BRIGHT_YELLOW               "\x1b[33;1m"
#define AC_BRIGHT_YELLOW_BLACK         "\x1b[33;1m\x1b[40m"
#define AC_BRIGHT_YELLOW_RED           "\x1b[33;1m\x1b[41m"
#define AC_BRIGHT_YELLOW_GREEN         "\x1b[33;1m\x1b[42m"
#define AC_BRIGHT_YELLOW_YELLOW        "\x1b[33;1m\x1b[43m"
#define AC_BRIGHT_YELLOW_BLUE          "\x1b[33;1m\x1b[44m"
#define AC_BRIGHT_YELLOW_MAGENTA       "\x1b[33;1m\x1b[45m"
#define AC_BRIGHT_YELLOW_CYAN          "\x1b[33;1m\x1b[46m"
#define AC_BRIGHT_YELLOW_WHITE         "\x1b[33;1m\x1b[47m"

#define AC_BLUE                        "\x1b[34m"
#define AC_BLUE_BLACK                  "\x1b[34m\x1b[40m"
#define AC_BLUE_RED                    "\x1b[34m\x1b[41m"
#define AC_BLUE_GREEN                  "\x1b[34m\x1b[42m"
#define AC_BLUE_YELLOW                 "\x1b[34m\x1b[43m"
#define AC_BLUE_BLUE                   "\x1b[34m\x1b[44m"
#define AC_BLUE_MAGENTA                "\x1b[34m\x1b[45m"
#define AC_BLUE_CYAN                   "\x1b[34m\x1b[46m"
#define AC_BLUE_WHITE                  "\x1b[34m\x1b[47m"
#define AC_BRIGHT_BLUE                 "\x1b[34;1m"
#define AC_BRIGHT_BLUE_BLACK           "\x1b[34;1m\x1b[40m"
#define AC_BRIGHT_BLUE_RED             "\x1b[34;1m\x1b[41m"
#define AC_BRIGHT_BLUE_GREEN           "\x1b[34;1m\x1b[42m"
#define AC_BRIGHT_BLUE_YELLOW          "\x1b[34;1m\x1b[43m"
#define AC_BRIGHT_BLUE_BLUE            "\x1b[34;1m\x1b[44m"
#define AC_BRIGHT_BLUE_MAGENTA         "\x1b[34;1m\x1b[45m"
#define AC_BRIGHT_BLUE_CYAN            "\x1b[34;1m\x1b[46m"
#define AC_BRIGHT_BLUE_WHITE           "\x1b[34;1m\x1b[47m"


#define AC_MAGENTA                     "\x1b[35m"
#define AC_MAGENTA_BLACK               "\x1b[35m\x1b[40m"
#define AC_MAGENTA_RED                 "\x1b[35m\x1b[41m"
#define AC_MAGENTA_GREEN               "\x1b[35m\x1b[42m"
#define AC_MAGENTA_YELLOW              "\x1b[35m\x1b[43m"
#define AC_MAGENTA_BLUE                "\x1b[35m\x1b[44m"
#define AC_MAGENTA_MAGENTA             "\x1b[35m\x1b[45m"
#define AC_MAGENTA_CYAN                "\x1b[35m\x1b[46m"
#define AC_MAGENTA_WHITE               "\x1b[35m\x1b[47m"
#define AC_BRIGHT_MAGENTA              "\x1b[35;1m"
#define AC_BRIGHT_MAGENTA_BLACK        "\x1b[35;1m\x1b[40m"
#define AC_BRIGHT_MAGENTA_RED          "\x1b[35;1m\x1b[41m"
#define AC_BRIGHT_MAGENTA_GREEN        "\x1b[35;1m\x1b[42m"
#define AC_BRIGHT_MAGENTA_YELLOW       "\x1b[35;1m\x1b[43m"
#define AC_BRIGHT_MAGENTA_BLUE         "\x1b[35;1m\x1b[44m"
#define AC_BRIGHT_MAGENTA_MAGENTA      "\x1b[35;1m\x1b[45m"
#define AC_BRIGHT_MAGENTA_CYAN         "\x1b[35;1m\x1b[46m"
#define AC_BRIGHT_MAGENTA_WHITE        "\x1b[35;1m\x1b[47m"


#define AC_CYAN                        "\x1b[36m"
#define AC_CYAN_BLACK                  "\x1b[36m\x1b[40m"
#define AC_CYAN_RED                    "\x1b[36m\x1b[41m"
#define AC_CYAN_GREEN                  "\x1b[36m\x1b[42m"
#define AC_CYAN_YELLOW                 "\x1b[36m\x1b[43m"
#define AC_CYAN_BLUE                   "\x1b[36m\x1b[44m"
#define AC_CYAN_MAGENTA                "\x1b[36m\x1b[45m"
#define AC_CYAN_CYAN                   "\x1b[36m\x1b[46m"
#define AC_CYAN_WHITE                  "\x1b[36m\x1b[47m"
#define AC_BRIGHT_CYAN                 "\x1b[36;1m"
#define AC_BRIGHT_CYAN_BLACK           "\x1b[36;1m\x1b[40m"
#define AC_BRIGHT_CYAN_RED             "\x1b[36;1m\x1b[41m"
#define AC_BRIGHT_CYAN_GREEN           "\x1b[36;1m\x1b[42m"
#define AC_BRIGHT_CYAN_YELLOW          "\x1b[36;1m\x1b[43m"
#define AC_BRIGHT_CYAN_BLUE            "\x1b[36;1m\x1b[44m"
#define AC_BRIGHT_CYAN_MAGENTA         "\x1b[36;1m\x1b[45m"
#define AC_BRIGHT_CYAN_CYAN            "\x1b[36;1m\x1b[46m"
#define AC_BRIGHT_CYAN_WHITE           "\x1b[36;1m\x1b[47m"


#define AC_WHITE                       "\x1b[37m"
#define AC_WHITE_BLACK                 "\x1b[37m\x1b[40m"
#define AC_WHITE_RED                   "\x1b[37m\x1b[41m"
#define AC_WHITE_GREEN                 "\x1b[37m\x1b[42m"
#define AC_WHITE_YELLOW                "\x1b[37m\x1b[43m"
#define AC_WHITE_BLUE                  "\x1b[37m\x1b[44m"
#define AC_WHITE_MAGENTA               "\x1b[37m\x1b[45m"
#define AC_WHITE_CYAN                  "\x1b[37m\x1b[46m"
#define AC_WHITE_WHITE                 "\x1b[37m\x1b[47m"
#define AC_BRIGHT_WHITE                "\x1b[37;1m"
#define AC_BRIGHT_WHITE_BLACK          "\x1b[37;1m\x1b[40m"
#define AC_BRIGHT_WHITE_RED            "\x1b[37;1m\x1b[41m"
#define AC_BRIGHT_WHITE_GREEN          "\x1b[37;1m\x1b[42m"
#define AC_BRIGHT_WHITE_YELLOW         "\x1b[37;1m\x1b[43m"
#define AC_BRIGHT_WHITE_BLUE           "\x1b[37;1m\x1b[44m"
#define AC_BRIGHT_WHITE_MAGENTA        "\x1b[37;1m\x1b[45m"
#define AC_BRIGHT_WHITE_CYAN           "\x1b[37;1m\x1b[46m"
#define AC_BRIGHT_WHITE_WHITE          "\x1b[37;1m\x1b[47m"

#define AC_BRIGHT_DISABLE_BLINK        "\x1b[?12l"
#define AC_BRIGHT_ENABLE_BLINK         "\x1b[?12h"

#define AC_SELECTION_BACKGROUND_RED    "\x1b]17;31\\"

#define AC_CURSOR_BAR                  "\x1b[5 q"
#define AC_CURSOR_BLOCK                "\x1b[1 q"
#define AC_CURSOR_UNDER                "\x1b[3 q"

#define AC_ALT_SCREEN_ON               "\x1b[?1049h\x1b[H"
#define AC_ALT_SCREEN_OFF              "\x1b[?1049l"

#define AC_SHOW_CURSOR                 "\x1b[?25h"
#define AC_HIDE_CURSOR                 "\x1b[?25l"

#define AC_CURSOR_COLOR(NAME)    "\x1b]12;" NAME "\x1b\\"
#define AC_CURSOR_RED                  AC_CURSOR_COLOR("red")
#define AC_CURSOR_BLACK                AC_CURSOR_COLOR("black")

#define AC_CURSOR_COLOR_RED            "'\x1b]12;31\\"
#define AC_CURSOR_COLOR_GREEN          "'\x1b]12;32\\"

#define AC_SAVE_PALETTE                "\x1b]30001\\"
#define AC_RESTORE_PALETTE             "\x1b]30101\\"
#define AC_LOAD_PALETTE                AC_RESTORE_PALETTE

#define AC_FG8(i)           "\x1b[38;5;"#i "m"
#define AC_BG8(i)           "\x1b[48;5;"#i "m"

#define AC_FG24(r, g, b)    "\x1b[38;2;"#r ";"#g ";"#b "m"
#define AC_BG24(r, g, b)    "\x1b[48;2;"#r ";"#g ";"#b "m"

#define AC_BOLD          "\x1b[1m"
#define AC_FAINT         "\x1b[2m"
#define AC_ITALIC        "\x1b[3m"
#define AC_UNDERLINE     "\x1b[4m"
#define AC_BLINK         "\x1b[5m"
#define AC_FAST_BLINK    "\x1b[6m"
#define AC_INVERSE       "\x1b[7m"
#define AC_INVERSED      AC_INVERSE
#define AC_REVERSE       "\x1b[7m"
#define AC_REVERSED      AC_REVERSE
#define AC_SOLID         "\x1b[7m"
#define AC_STRIKE        "\x1b[9m"
#define AC_INVISIBLE     "\x1b[8m"
#define AC_UP(n)        "\x1b["#n "A"
#define AC_DOWN(n)      "\x1b["#n "B"
#define AC_RIGHT(n)     "\x1b["#n "C"
#define AC_LEFT(n)      "\x1b["#n "D"
#define AC_POS(x, y)    "\x1b["#x ";"#y "H"

#define AC_HOME    "\x1b[H"
#define AC_CLS     "\x1b[2J" AC_HOME


#endif
