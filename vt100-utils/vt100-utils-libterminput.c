#pragma once
#include "libterminput/libterminput.h"
#include <assert.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
//#include "vt100-utils/vt100-utils.h"


int __do_libterminput(void){
  FILE *fp;

  if ((fp = fopen("input.log", "a+")) == NULL) {            // file opening mode.
    perror("Cannot open file!! ");
    exit(1);
  }
  setvbuf(fp, NULL, _IONBF, 0);

  fprintf(fp, "<%d> OK\n", getpid());
  struct libterminput_state ctx;
  union libterminput_input  input;
  struct termios            stty, saved_stty;
  int                       r;

  memset(&ctx, 0, sizeof(ctx));

  if (getenv("TEST_LIBTERMINPUT_DECSET_1005")) {
    fprintf(fp, "LIBTERMINPUT_DECSET_1005 set\n");
    libterminput_set_flags(&ctx, LIBTERMINPUT_DECSET_1005);
  }
  if (getenv("TEST_LIBTERMINPUT_MACRO_ON_CSI_M")) {
    fprintf(fp, "LIBTERMINPUT_MACRO_ON_CSI_M set\n");
    libterminput_set_flags(&ctx, LIBTERMINPUT_MACRO_ON_CSI_M);
  }
  if (getenv("TEST_LIBTERMINPUT_PAUSE_ON_CSI_P")) {
    fprintf(fp, "LIBTERMINPUT_PAUSE_ON_CSI_P set\n");
    libterminput_set_flags(&ctx, LIBTERMINPUT_PAUSE_ON_CSI_P);
  }
  if (getenv("TEST_LIBTERMINPUT_INS_ON_CSI_AT")) {
    fprintf(fp, "LIBTERMINPUT_INS_ON_CSI_AT set\n");
    libterminput_set_flags(&ctx, LIBTERMINPUT_INS_ON_CSI_AT);
  }
  if (getenv("TEST_LIBTERMINPUT_SEPARATE_BACKTAB")) {
    fprintf(fp, "LIBTERMINPUT_SEPARATE_BACKTAB set\n");
    libterminput_set_flags(&ctx, LIBTERMINPUT_SEPARATE_BACKTAB);
  }
  if (getenv("TEST_LIBTERMINPUT_ESC_ON_BLOCK")) {
    fprintf(fp, "LIBTERMINPUT_ESC_ON_BLOCK set\n");
    libterminput_set_flags(&ctx, LIBTERMINPUT_ESC_ON_BLOCK);
  }
  if (getenv("TEST_LIBTERMINPUT_AWAITING_CURSOR_POSITION")) {
    fprintf(fp, "LIBTERMINPUT_AWAITING_CURSOR_POSITION set\n");
    libterminput_set_flags(&ctx, LIBTERMINPUT_AWAITING_CURSOR_POSITION);
  }

  if (tcgetattr(STDERR_FILENO, &stty)) {
    perror("tcgetattr STDERR_FILENO");
    return(1);
  }
  saved_stty    = stty;
  stty.c_lflag &= (tcflag_t) ~(ECHO | ICANON);
  if (tcsetattr(STDERR_FILENO, TCSAFLUSH, &stty)) {
    perror("tcsetattr STDERR_FILENO TCSAFLUSH");
    return(1);
  }
  fprintf(fp, "reading\n");
  while ((r = libterminput_read(STDIN_FILENO, &input, &ctx)) > 0) {
    if (input.type == LIBTERMINPUT_NONE) {
      fprintf(fp, "none\n");
    } else if (input.type == LIBTERMINPUT_KEYPRESS) {
      fprintf(fp, "keypress:\n");
      switch (input.keypress.key) {
      case LIBTERMINPUT_SYMBOL:
        fprintf(fp, "\t%s: %s\n", "key: symbol", input.keypress.symbol);
        break;
      case LIBTERMINPUT_UP:              fprintf(fp, "\t%s: %s\n", "key", "up");              break;
      case LIBTERMINPUT_DOWN:            fprintf(fp, "\t%s: %s\n", "key", "down");            break;
      case LIBTERMINPUT_RIGHT:           fprintf(fp, "\t%s: %s\n", "key", "right");           break;
      case LIBTERMINPUT_LEFT:            fprintf(fp, "\t%s: %s\n", "key", "left");            break;
      case LIBTERMINPUT_BEGIN:           fprintf(fp, "\t%s: %s\n", "key", "begin");           break;
      case LIBTERMINPUT_TAB:             fprintf(fp, "\t%s: %s\n", "key", "tab");             break;
      case LIBTERMINPUT_BACKTAB:         fprintf(fp, "\t%s: %s\n", "key", "backtab");         break;
      case LIBTERMINPUT_F1:              fprintf(fp, "\t%s: %s\n", "key", "f1");              break;
      case LIBTERMINPUT_F2:              fprintf(fp, "\t%s: %s\n", "key", "f2");              break;
      case LIBTERMINPUT_F3:              fprintf(fp, "\t%s: %s\n", "key", "f3");              break;
      case LIBTERMINPUT_F4:              fprintf(fp, "\t%s: %s\n", "key", "f4");              break;
      case LIBTERMINPUT_F5:              fprintf(fp, "\t%s: %s\n", "key", "f5");              break;
      case LIBTERMINPUT_F6:              fprintf(fp, "\t%s: %s\n", "key", "f6");              break;
      case LIBTERMINPUT_F7:              fprintf(fp, "\t%s: %s\n", "key", "f7");              break;
      case LIBTERMINPUT_F8:              fprintf(fp, "\t%s: %s\n", "key", "f8");              break;
      case LIBTERMINPUT_F9:              fprintf(fp, "\t%s: %s\n", "key", "f9");              break;
      case LIBTERMINPUT_F10:             fprintf(fp, "\t%s: %s\n", "key", "f10");             break;
      case LIBTERMINPUT_F11:             fprintf(fp, "\t%s: %s\n", "key", "f11");             break;
      case LIBTERMINPUT_F12:             fprintf(fp, "\t%s: %s\n", "key", "f12");             break;
      case LIBTERMINPUT_HOME:            fprintf(fp, "\t%s: %s\n", "key", "home");            break;
      case LIBTERMINPUT_INS:             fprintf(fp, "\t%s: %s\n", "key", "ins");             break;
      case LIBTERMINPUT_DEL:             fprintf(fp, "\t%s: %s\n", "key", "del");             break;
      case LIBTERMINPUT_END:             fprintf(fp, "\t%s: %s\n", "key", "end");             break;
      case LIBTERMINPUT_PRIOR:           fprintf(fp, "\t%s: %s\n", "key", "prior");           break;
      case LIBTERMINPUT_NEXT:            fprintf(fp, "\t%s: %s\n", "key", "next");            break;
      case LIBTERMINPUT_ERASE:           fprintf(fp, "\t%s: %s\n", "key", "erase");           break;
      case LIBTERMINPUT_ENTER:           fprintf(fp, "\t%s: %s\n", "key", "enter");           break;
      case LIBTERMINPUT_ESC:             fprintf(fp, "\t%s: %s\n", "key", "esc");             break;
      case LIBTERMINPUT_KEYPAD_0:        fprintf(fp, "\t%s: %s\n", "key", "keypad 0");        break;
      case LIBTERMINPUT_KEYPAD_1:        fprintf(fp, "\t%s: %s\n", "key", "keypad 1");        break;
      case LIBTERMINPUT_KEYPAD_2:        fprintf(fp, "\t%s: %s\n", "key", "keypad 2");        break;
      case LIBTERMINPUT_KEYPAD_3:        fprintf(fp, "\t%s: %s\n", "key", "keypad 3");        break;
      case LIBTERMINPUT_KEYPAD_4:        fprintf(fp, "\t%s: %s\n", "key", "keypad 4");        break;
      case LIBTERMINPUT_KEYPAD_5:        fprintf(fp, "\t%s: %s\n", "key", "keypad 5");        break;
      case LIBTERMINPUT_KEYPAD_6:        fprintf(fp, "\t%s: %s\n", "key", "keypad 6");        break;
      case LIBTERMINPUT_KEYPAD_7:        fprintf(fp, "\t%s: %s\n", "key", "keypad 7");        break;
      case LIBTERMINPUT_KEYPAD_8:        fprintf(fp, "\t%s: %s\n", "key", "keypad 8");        break;
      case LIBTERMINPUT_KEYPAD_9:        fprintf(fp, "\t%s: %s\n", "key", "keypad 9");        break;
      case LIBTERMINPUT_KEYPAD_PLUS:     fprintf(fp, "\t%s: %s\n", "key", "keypad plus");     break;
      case LIBTERMINPUT_KEYPAD_MINUS:    fprintf(fp, "\t%s: %s\n", "key", "keypad minus");    break;
      case LIBTERMINPUT_KEYPAD_TIMES:    fprintf(fp, "\t%s: %s\n", "key", "keypad times");    break;
      case LIBTERMINPUT_KEYPAD_DIVISION: fprintf(fp, "\t%s: %s\n", "key", "keypad division"); break;
      case LIBTERMINPUT_KEYPAD_DECIMAL:  fprintf(fp, "\t%s: %s\n", "key", "keypad decimal");  break;
      case LIBTERMINPUT_KEYPAD_COMMA:    fprintf(fp, "\t%s: %s\n", "key", "keypad comma");    break;
      case LIBTERMINPUT_KEYPAD_POINT:    fprintf(fp, "\t%s: %s\n", "key", "keypad point");    break;
      case LIBTERMINPUT_KEYPAD_ENTER:    fprintf(fp, "\t%s: %s\n", "key", "keypad enter");    break;
      case LIBTERMINPUT_MACRO:           fprintf(fp, "\t%s: %s\n", "key", "macro");           break;
      case LIBTERMINPUT_PAUSE:           fprintf(fp, "\t%s: %s\n", "key", "pause");           break;
      default:
        fprintf(fp, "\t%s: %s\n", "key", "other");
        break;
      } /* switch */
      fprintf(fp, "\t%s: %s\n", "shift", (input.keypress.mods & LIBTERMINPUT_SHIFT) ? "yes" : "no");
      fprintf(fp, "\t%s: %s\n", "meta", (input.keypress.mods & LIBTERMINPUT_META)  ? "yes" : "no");
      fprintf(fp, "\t%s: %s\n", "ctrl", (input.keypress.mods & LIBTERMINPUT_CTRL)  ? "yes" : "no");
      fprintf(fp, "\t%s: %s (%llu)\n", "will repeat", input.keypress.times > 1 ? "yes" : "no", input.keypress.times);
    } else if (input.type == LIBTERMINPUT_BRACKETED_PASTE_START) {
      fprintf(fp, "bracketed paste start\n");
    } else if (input.type == LIBTERMINPUT_BRACKETED_PASTE_END) {
      fprintf(fp, "bracketed paste end\n");
    } else if (input.type == LIBTERMINPUT_TEXT) {
      fprintf(fp, "text:\n");
      fprintf(fp, "\tlength: %zu\n", input.text.nbytes);
      fprintf(fp, "\tdata: %.512s\n", input.text.bytes);
    } else if (input.type == LIBTERMINPUT_MOUSEEVENT) {
      fprintf(fp, "mouseevent:\n");
      switch (input.mouseevent.event) {
      case LIBTERMINPUT_PRESS:             fprintf(fp, "\t%s: %s\n", "event", "press");             break;
      case LIBTERMINPUT_RELEASE:           fprintf(fp, "\t%s: %s\n", "event", "release");           break;
      case LIBTERMINPUT_MOTION:            fprintf(fp, "\t%s: %s\n", "event", "motion");            break;
      case LIBTERMINPUT_HIGHLIGHT_INSIDE:  fprintf(fp, "\t%s: %s\n", "event", "highlight inside");  goto was_highlight;
      case LIBTERMINPUT_HIGHLIGHT_OUTSIDE: fprintf(fp, "\t%s: %s\n", "event", "highlight outside"); goto was_highlight;
      default:
        fprintf(fp, "\t%s: %s\n", "event", "other");
        break;
      }
      switch (input.mouseevent.button) {
      case LIBTERMINPUT_NO_BUTTON:    fprintf(fp, "\t%s: %s\n", "button", "none");                             break;
      case LIBTERMINPUT_BUTTON1:      fprintf(fp, "\t%s: %s\n", "button", "button 1 (left)");                  break;
      case LIBTERMINPUT_BUTTON2:      fprintf(fp, "\t%s: %s\n", "button", "button 2 (middle)");                break;
      case LIBTERMINPUT_BUTTON3:      fprintf(fp, "\t%s: %s\n", "button", "button 3 (right)");                 break;
      case LIBTERMINPUT_SCROLL_UP:    fprintf(fp, "\t%s: %s\n", "button", "scroll up");                        break;
      case LIBTERMINPUT_SCROLL_DOWN:  fprintf(fp, "\t%s: %s\n", "button", "scroll down");                      break;
      case LIBTERMINPUT_SCROLL_LEFT:  fprintf(fp, "\t%s: %s\n", "button", "scroll left");                      break;
      case LIBTERMINPUT_SCROLL_RIGHT: fprintf(fp, "\t%s: %s\n", "button", "scroll right");                     break;
      case LIBTERMINPUT_XBUTTON1:     fprintf(fp, "\t%s: %s\n", "button", "extended button 1 (X1; backward)"); break;
      case LIBTERMINPUT_XBUTTON2:     fprintf(fp, "\t%s: %s\n", "button", "extended button 2 (X2; forward)");  break;
      case LIBTERMINPUT_XBUTTON3:     fprintf(fp, "\t%s: %s\n", "button", "extended button 3 (X3)");           break;
      case LIBTERMINPUT_XBUTTON4:     fprintf(fp, "\t%s: %s\n", "button", "extended button 4 (X4)");           break;
      default:
        fprintf(fp, "\t%s: %s\n", "button", "other");
        break;
      }
      fprintf(fp, "\t%s: %s\n", "shift", (input.mouseevent.mods & LIBTERMINPUT_SHIFT) ? "yes" : "no");
      fprintf(fp, "\t%s: %s\n", "meta", (input.mouseevent.mods & LIBTERMINPUT_META)  ? "yes" : "no");
      fprintf(fp, "\t%s: %s\n", "ctrl", (input.mouseevent.mods & LIBTERMINPUT_CTRL)  ? "yes" : "no");
was_highlight:
      fprintf(fp, "\t%s: x=%zu, y=%zu\n", "position", input.mouseevent.x, input.mouseevent.y);
      if (LIBTERMINPUT_HIGHLIGHT_OUTSIDE) {
        fprintf(fp, "\t%s: x=%zu, y=%zu\n", "start", input.mouseevent.start_x, input.mouseevent.start_y);
        fprintf(fp, "\t%s: x=%zu, y=%zu\n", "end", input.mouseevent.end_x, input.mouseevent.end_y);
      }
      if (input.mouseevent.event == LIBTERMINPUT_PRESS) {
        fprintf(fp, "\033[1;4;4;10;10T");
        fflush(stdout);
      }
    } else if (input.type == LIBTERMINPUT_TERMINAL_IS_OK) {
      fprintf(fp, "terminal ok\n");
    } else if (input.type == LIBTERMINPUT_TERMINAL_IS_NOT_OK) {
      fprintf(fp, "terminal not ok\n");
    } else if (input.type == LIBTERMINPUT_CURSOR_POSITION) {
      fprintf(fp, "cursor position:\n");
      fprintf(fp, "\tx: %zu\n", input.position.x);
      fprintf(fp, "\ty: %zu\n", input.position.y);
    } else {
      fprintf(fp, "other\n");
    }
  }

  if (r < 0) {
    perror("libterminput_read STDIN_FILENO");
  }

  tcsetattr(STDERR_FILENO, TCSAFLUSH, &saved_stty);


  fprintf(fp, fp, "OK\n");
} /* __do_libterminput */
