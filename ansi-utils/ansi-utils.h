#pragma once
#ifndef ANSI_UTILS_H
#define ANSI_UTILS_H
#include "../ansi-codes/ansi-codes.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>


typedef struct {
  bool RestorePalette, IsTTY, AltScreenInitiallyEnabled, Wasicanon;
} TerminalCapabilities_t;

typedef enum {
  OFF,
  ON,
  QUERY,
} BoolQuery;


#endif
