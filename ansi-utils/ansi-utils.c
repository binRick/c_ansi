#pragma once
#ifndef ANSI_UTILS_C
#define ANSI_UTILS_C
#include "ansi-utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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


#endif
