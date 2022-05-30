#pragma once
#ifndef ANSI_UTILS_C
#define ANSI_UTILS_C
#include "ansi-utils.h"

TerminalCapabilities_t TerminalCapabilities = {
  .RestorePalette            = false,
  .AltScreenInitiallyEnabled = false,
  .IsTTY                     = false,
};


char *au_draw_box(int BOX_SIZE){
  int  W = BOX_SIZE * 2, H = BOX_SIZE;
  char *out = malloc(1024);
  char *BG  = AC_RESETALL AC_BLACK "" AC_BG24(255, 255, 255);

  sprintf(out, "%s", BG);
  for (int y = 0; y < H; y++) {
    for (int x = 0; x < W; x++) {
      strcat(out, " ");
    }
    strcat(out, "\n");
  }
  return(out);
}


int au_term_size(int *w, int *h) {
  struct winsize ws;
  int            ret = ioctl(1, TIOCGWINSZ, &ws);

  if (ret < 0) {
    return(ret);
  }
  *w = ws.ws_col;
  *h = ws.ws_row;
  return(0);
}


static void await_c1(unsigned char c1){
  unsigned char c;
  bool          in_esc = false;

  while ((c = getchar())) {
    if (c == c1) {
      break;
    }
    if (in_esc && c == (char)(c1 - 0x40)) {
      break;
    }
    if (!in_esc && c == 0x1b) {
      in_esc = true;
    }else{
      in_esc = false;
    }
  }
}


static char *read_csi(){
  await_c1(0x9B);
  char csi[32];
  int  i = 0;

  for ( ; i < sizeof(csi) - 1; i++) {
    char c = csi[i] = getchar();
    if (c >= 0x40 && c <= 0x7e) {
      break;
    }
  }
  csi[++i] = 0;
  return(strdup(csi));
}


char *strdup_escaped(const char *tmp) {
  char *ret = malloc(strlen(tmp) * 4 + 1);
  char *dst = ret;

  for ( ; *tmp; tmp++) {
    if (*tmp >= ' ' && *tmp <= 126 && *tmp != '\\') {
      *dst = *tmp;
      ++dst;
    } else {
      dst += sprintf(dst, "\\x%02hhx", (unsigned char)*tmp);
    }
  }
  *dst = 0;
  return(ret);
}


static bool query_dec_mode(int mode){
  printf("\x1b[?%d$p", mode);
  char *s = NULL;

  do {
    if (s) {
      free(s);
    }
    s = read_csi();
    int  reply_mode, reply_value;
    char reply_cmd;
    if (sscanf(s, "?%d;%d$%c", &reply_mode, &reply_value, &reply_cmd) < 3) {
      continue;
    }
    if (reply_cmd != 'y') {
      continue;
    }

    if (reply_mode != mode) {
      continue;
    }

    free(s);

    if (reply_value == 1 || reply_value == 3) {
      return(true);
    }
    if (reply_value == 2 || reply_value == 4) {
      return(false);
    }

    printf("Unrecognised reply to DECRQM: %d\n", reply_value);
    return(false);
  } while (1);
}


void au_restore_palette(){
  printf(AC_RESTORE_PALETTE);
}


void au_save_palette(){
  printf(AC_SAVE_PALETTE);
}


char * AC_cur(int par, char type) {
  register char *ret = (char *)malloc(strlen(ACCSI) + sizeof(char) * 6);

  sprintf(ret, ACCSI "%d%c", par, type);
  return(ret);
}


char * AC_cur_pos(int x, int y, char type) {
  register char *ret = (char *)malloc(strlen(ACCSI) + strlen(ACTKN(x)) + strlen(ACTKN(y)) + sizeof(char) * 2);

  sprintf(ret, ACCSI "%d;%d%c", x, y, type);
  return(ret);
}


char * AC_cur_prv(int par, bool state) {
  register char *ret = (char *)malloc(strlen(ACCSIP) + sizeof(char) * 7);

  sprintf(ret, ACCSIP "%d%c", par, (((int)state) ? 'h' : 'l'));
  return(ret);
}


static void do_dec_mode(int mode, BoolQuery val, const char *name){
  if (query_dec_mode(mode)) {
    printf("%s on\n", name);
  }else{
    printf("%s off\n", name);
  }
}


static bool seticanon(bool icanon, bool echo){
  struct termios termios;

  tcgetattr(0, &termios);
  bool ret = (termios.c_lflag & ICANON);

  if (icanon) {
    termios.c_lflag |= ICANON;
  }else{
    termios.c_lflag &= ~ICANON;
  }
  if (echo) {
    termios.c_lflag |= ECHO;
  }else{
    termios.c_lflag &= ~ECHO;
  }
  tcsetattr(0, TCSANOW, &termios);
  return(ret);
}


void restoreicanon(void){
  seticanon(TerminalCapabilities.Wasicanon, true);
}

#endif
