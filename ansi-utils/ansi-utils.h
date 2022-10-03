#pragma once
#include "ansi-codes/ansi-codes.h"
//#include "vt100utils/vt100utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
///////////////////////////////////////////////////////////////////////////////////yy
typedef struct {
  bool RestorePalette, IsTTY, AltScreenInitiallyEnabled, Wasicanon;
} TerminalCapabilities_t;
typedef enum {
  OFF,
  ON,
  QUERY,
} BoolQuery;
///////////////////////////////////////////////////////////////////////////////////yy
int au_term_size(int *w, int *h);
char *random_rgb();
char *strdup_escaped(const char *tmp);
void restoreicanon(void);
bool seticanon(bool icanon, bool echo);
char *au_draw_box(int BOX_SIZE);
char * AC_cur(int par, char type);
char * AC_cur_prv(int par, bool state);
void au_save_palette();
void au_restore_palette();
char * AC_cur_pos(int x, int y, char type);
///////////////////////////////////////////////////////////////////////////////////yy
#define BIN2DEC(b)    (((b) >= 0 && (b) <= 9) ? (b) + '0' : (b))
#define DEC2BIN(d)    (((d) >= '0' && (d) <= '9') ? (d) - '0' : (d))
#define BIN2HEX(b)    (((b) >= 0 && (b) <= 9)?(b) + '0':        \
                       ((b) >= 10 && (b) <= 15)?(b) - 10 + 'A': \
                       (b))
#define HEX2BIN(h)    (((h) >= '0' && (h) <= '9')?(h) - '0':      \
                       ((h) >= 'A' && (h) <= 'F')?(h) - 'A' + 10: \
                       ((h) >= 'a' && (h) <= 'f')?(h) - 'a' + 10: \
                       (h))

#define BRIGHT_COLOR_GOLDEN_RATIO    1.618;
void bright_color_init(float alpha);
void bright_color(int i, float color[4]);
size_t ansi_utils_tty_copy(const char *s);
