#pragma once
#include "module/def.h"
#include "module/module.h"
#include "module/require.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *ac_confirm_render(void);
void color_reset();

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

#define AC_ESC    "\x1b"
#ifdef AC_RESETALL
#undef AC_RESETALL
#endif
#define AC_RESETALL                  AC_ESC "[0m"
#define B64_ENCODED_COLOR_PREVIEW    "G1szMG1Db2xvciAwDQobWzMxbUNvbG9yIDENChtbMzJtQ29sb3IgMg0KG1szM21Db2xvciAzDQobWzM0bUNvbG9yIDQNChtbMzVtQ29sb3IgNQ0KG1szNm1Db2xvciA2DQobWzM3bUNvbG9yIDcNChtbOTBtQ29sb3IgOA0KG1s5MW1Db2xvciA5DQobWzkybUNvbG9yIDEwDQobWzkzbUNvbG9yIDExDQobWzk0bUNvbG9yIDEyDQobWzk1bUNvbG9yIDEzDQobWzk2bUNvbG9yIDE0DQobWzk3bUNvbG9yIDE1DQoNChtbMG0jIGxzIC0tY29sb3IgLUYNCiAgICBmaWxlDQogICAgG1swMTszNG1kaXIvG1swbQ0KICAgIBtbMDE7MzJtZXhlY3V0YWJsZRtbMG0qDQogICAgG1swMTszNm1zeW1saW5rG1swbQ0KG1swbQ=="

#define acs(s)          AC_RESETALL s AC_RESETALL
#define acsl(s)         AC_RESETALL s AC_RESETALL "\n"
#define ansistr(s)      s AC_RESETALL
#define ansistrln(s)    s AC_RESETALL "\n"

#define AC_NONE    "\x1b[0m"
#define ACCSI      "\e["
#define ACCSIP     "\e[?"
#define ACOSC      "\e]"
#define ACDCS      "\x1b(B"
#define ACDEC      "\e(0"
#define ACRIS      "\ec"
#define ACBCK      "\u007f"
#define ACPAS      "\u001a"

#define AC_BUTTON(TEXT, COLOR)    COLOR "" AC_NONE COLOR AC_INVERSE " " TEXT " " AC_NONE COLOR ""


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
#define AC_BOLDBLUE                    "\x1b[94m"
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

#define AC_CURSOR_SAVE                 "\x1b7"
#define AC_CURSOR_RESTORE              "\x1b8"
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
#define AC_SAVE_PRIVATE_PALETTE        "\x1b[#P"
#define AC_RESTORE_PRIVATE_PALETTE     "\x1b[#Q"
#define AC_LOAD_PALETTE                AC_RESTORE_PALETTE

#define AC_FG8(i)           "\x1b[38;5;"#i "m"
#define AC_BG8(i)           "\x1b[48;5;"#i "m"

#define AC_FG24(r, g, b)    "\x1b[38;2;"#r ";"#g ";"#b "m"
#define AC_BG24(r, g, b)    "\x1b[48;2;"#r ";"#g ";"#b "m"

#define AC_BOLD                     "\x1b[1m"
#define AC_FAINT                    "\x1b[2m"
#define AC_ITALIC                   "\x1b[3m"
#define AC_UNDERLINE                "\x1b[4m"
#define AC_NO_UNDERLINE             "\x1b[4:0m"
#define AC_DOUBLE_UNDERLINE         "\x1b[4:2m"
#define AC_CURLY_UNDERLINE          "\x1b[4:3m"
#define AC_FOTTED_UNDERLINE         "\x1b[4:4m"
#define AC_DASHED_UNDERLINE         "\x1b[4:5m"
#define AC_RESET_UNDERLINE_COLOR    "\x1b[59m"
#define AC_UNDERLINE_COLOR_RED      "\x1b[58#569cd6m"
#define AC_NOUNDERLINE              "\x1b[4:0m"
#define AC_PLAIN                    "\x1b[23m"
#define AC_BLINK                    "\x1b[5m"
#define AC_NOBLINK                  "\x1b[25m"
#define AC_FAST_BLINK               "\x1b[6m"
#define AC_INVERSE                  "\x1b[7m"
#define AC_NOINVERSE                "\x1b[27m"
#define AC_RESET_TERMINAL           "\x1b]\x1b\\\x1bc"
#define AC_SET_TERMINAL_TITLE(TITLE)    "\x1b]2;" TITLE "\x1b\\"
#define AC_SET_CLIPBOARD(CONTENT)       "\x1b]52;c;" CONTENT "\a\x1b\\"
#define AC_CLEAR_CLIPBOARD(CONTENT)     "\x1b]52;c;|\x1b"
#define AC_CLIPBOARD_REQUEST    "\x1b]52;p;?\a"
#define AC_BELL                 "\a"
#ifdef AC_INVERSED
#undef AC_INVERSED
#endif
#define AC_INVERSED    AC_INVERSE
#define AC_REVERSE     "\x1b[7m"
#ifdef AC_REVERSED
#undef AC_REVERSED
#endif
#define AC_REVERSED     AC_REVERSE
#define AC_SOLID        "\x1b[7m"
#define AC_STRIKE       "\x1b[9m"
#define AC_INVISIBLE    "\x1b[8m"
#define AC_NORMAL       "\x1b[22m"
#define AC_UP(n)        "\x1b["#n "A"
#define AC_DOWN(n)      "\x1b["#n "B"
#define AC_RIGHT(n)     "\x1b["#n "C"
#define AC_LEFT(n)      "\x1b["#n "D"
#define AC_POS(x, y)    "\x1b["#x ";"#y "H"

#define AC_HOME    "\x1b[H"
#define AC_CLS     "\x1b[2J" AC_HOME


enum ac_confirm_mode_t {
  AC_CONFIRM_LOG_NONE,
  AC_CONFIRM_LOG_INFO,
  AC_CONFIRM_LOG_ERROR,
  AC_CONFIRM_LOG_DEBUG,
  AC_CONFIRM_LOG_QTY,
};

#define AC_CONFIRM_LOG_DEFAULT    AC_CONFIRM_LOG_INFO
struct ac_confirm_option_t {
  char *text;
  char *selected_color;
  char *color;
  bool selected;
  char *button_s;
};

// Module Type Interface
module(ac_confirm) {
  define(ac_confirm, CLIB_MODULE);
  //////////////////////////////////////////////////////////////////////////////////////
  //     Config
  //////////////////////////////////////////////////////////////////////////////////////
  enum ac_confirm_mode_t mode;
  //////////////////////////////////////////////////////////////////////////////////////
  //     Properties
  //////////////////////////////////////////////////////////////////////////////////////
  struct Vector *options;
  //////////////////////////////////////////////////////////////////////////////////////
  //     Utility Functions
  //////////////////////////////////////////////////////////////////////////////////////
  int                        *(*render_ui)(void);
  char                       *(*render_option_buttons)(void);
  struct ac_confirm_option_t *(*render_option)(char *TEXT, char *COLOR);
  char                       *(*render_option_button)(struct ac_confirm_option_t *OPTION);
  bool                       (*add_option)(struct ac_confirm_option_t *NEW_OPTION);
  size_t                     (*get_options_qty)(void);
  struct ac_confirm_option_t *(*init_option)(char *NEW_OPTION_TEXT);
  //////////////////////////////////////////////////////////////////////////////////////
};


int  ac_confirm_module_init(module(ac_confirm) * exports);
void ac_confirm_module_deinit(module(ac_confirm) * exports);
struct ac_confirm_option_t *ac_confirm_init_option(char *NEW_OPTION_TEXT);
bool ac_confirm_add_option(struct ac_confirm_option_t *NEW_OPTION);
size_t ac_confirm_get_options_qty(void);

exports(ac_confirm) {
  .mode                  = AC_CONFIRM_LOG_DEFAULT,
  .init                  = ac_confirm_module_init,
  .deinit                = ac_confirm_module_deinit,
  .render_ui             = NULL,
  .render_option_buttons = NULL,
  .render_option_button  = NULL,
  .render_option         = NULL,
  .get_options_qty       = ac_confirm_get_options_qty,
  .init_option           = ac_confirm_init_option,
  .add_option            = ac_confirm_add_option,
};
