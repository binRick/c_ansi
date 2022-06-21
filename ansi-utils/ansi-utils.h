#pragma once
#include "ansi-codes.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
char *strdup_escaped(const char *tmp);
void restoreicanon(void);
char *au_draw_box(int BOX_SIZE);
char * AC_cur(int par, char type);
char * AC_cur_prv(int par, bool state);
void au_save_palette();
void au_restore_palette();
char * AC_cur_pos(int x, int y, char type);
///////////////////////////////////////////////////////////////////////////////////yy
