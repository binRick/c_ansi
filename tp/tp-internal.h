#pragma once
#ifndef TPIH
#define TPIH
#ifndef DBG_H_DEF_ONCE
#define DBG_H_DEF_ONCE
#include "c_dbg/c_dbg.h"
#endif
#include "term-termpaint.h"
#include "term-termpaint.h"
#include "termpaint.h"
#include "termpaint_image.h"
#include "termpaintx.h"
#include "termpaintx_ttyrescue.h"
#include <assert.h>
#include <fcntl.h>
#include <pthread.h>
#include <signal.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
////////////////////////////////////////////////////
#include "tp-defines.h"
#include "tp-message-box.h"
#include "tp-selection.h"
#include "tp-types.h"
#include "tp-utils.h"
#include "tp-tab.h"
#include "tp.h"
////////////////////////////////////////////////////
#include "ansi-codes.h"
#include "ansi-utils/ansi-utils.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/include/vector.h"
#include "module/def.h"
#include "module/module.h"
#include "ms/ms.h"
////////////////////////////////////////////////////
#include "wildcardcmp/wildcardcmp.h"
////////////////////////////////////////////////////
#include "module/require.h"
#include "tiny-regex-c/re.h"
////////////////////////////////////////////////////
#define LOG(STR)    fprintf(stderr, AC_RESETALL AC_YELLOW "%s\n" AC_RESETALL, STR)
#define TP    require(tp_confirm)
#define TB    require(tp_tab)
extern termpaint_surface  *surface;
extern termpaint_terminal *terminal;
extern termpaint_attr     *attr_bottom_msg;
const char                *TITLE_CHARS;
termpaint_attr            *attr_ui, *attr_sample;
event                     *event_current;
termpaint_terminal        *terminal;
termpaint_surface         *surface;
termpaint_integration     *integration;
cursor_profile_t          *cursor_profile;
////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////
