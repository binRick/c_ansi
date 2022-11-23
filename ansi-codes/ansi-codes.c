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

void tc_echo_off()
{
	struct termios term;
	tcgetattr(1, &term);
	term.c_lflag &= ~ECHO;
	tcsetattr(1, TCSANOW, &term);
}

void tc_echo_on()
{
	struct termios term;
	tcgetattr(1, &term);
	term.c_lflag |= ECHO;
	tcsetattr(1, TCSANOW, &term);
}

void tc_canon_on()
{
	struct termios term;
	tcgetattr(1, &term);
	term.c_lflag |= ICANON;
	tcsetattr(1, TCSANOW, &term);
}

void tc_canon_off()
{
	struct termios term;
	tcgetattr(1, &term);
	term.c_lflag &= ~ICANON;
	tcsetattr(1, TCSANOW, &term);
}

bool tc_set_cursor(int x, int y){
  return(fprintf(stdout, "\x1B[%d;%dH", y, x)>0);
}
bool tc_save_cursor();
bool tc_load_cursor();
void tc_get_cursor(int *x, int *y)
{
	tc_echo_off();
	tc_canon_off();
	printf("\033[6n");
	scanf("\033[%d;%dR", x, y);
}

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
