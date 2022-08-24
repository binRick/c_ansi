#pragma once
#ifndef TPMB
#define TPMB
#include "term-termpaint.h"
#include "term-termpaint.h"
#include "termpaint.h"
#include "termpaint_image.h"
#include "termpaintx.h"
#include "termpaintx_ttyrescue.h"
#include "tp-utils.h"
#include "tp.h"
#include <assert.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <termios.h>
#include <unistd.h>
////////////////////////////////////////////////////
#include "ansi-codes.h"
#include "ansi-utils/ansi-utils.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "module/def.h"
#include "module/module.h"
////////////////////////////////////////////////////
#include "wildcardcmp/wildcardcmp.h"
////////////////////////////////////////////////////
#include "module/require.h"
#include "tiny-regex-c/re.h"
#include "tp.h"
#define MAX_RGB                          255
#define BORDER_STYLES_QTY                2
#define BOTTOM_MSG_BOX_HEIGHT            3
#define BOTTOM_MSG_BOX_COL_MSG_OFFSET    2
#define BOTTOM_MSG_BOX_COL               10
//////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////
///        GLOBAL VARIABLES                 ///
///////////////////////////////////////////////
volatile char
  MSG[1024],
  CACHED_BOTTOM_MSG[1024]
;
const int
  screen_bg,
  ui_fg,
  win_message,
  tile_border,
  tile_background;
void redraw_bottom_msg();
void write_bottom_msg(const char *BOTTOM_MSG);
void clear_bottom_msg(bool SKIP_FLUSH, bool FORCE_FLUSH);
const char *BORDER_STYLES;

#endif
