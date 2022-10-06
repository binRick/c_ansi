#pragma once
#ifndef ANSI_CODES_C
#define ANSI_CODES_C
#include "ansi-codes.h"
#include "ansi-utils/ansi-utils.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include <stdint.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

struct winsize *get_terminal_size(){
  struct winsize *sz = calloc(1, sizeof(struct winsize));
  ioctl(STDOUT_FILENO, TIOCGWINSZ, sz);
  return(sz);
}

int get_terminal_width(){
  return(get_terminal_size()->ws_col);
}

int get_terminal_height(){
  return(get_terminal_size()->ws_row);
}

char *AC_RGB(int R, int G, int B){
  char *s;  asprintf(&s, "\x1b[38;2; %d;%d;%dm", R, G, B); return(s);
}

void color_reset(){
  printf("\x1b[0m");
}

#endif
