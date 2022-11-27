#pragma once
#ifndef TERM_TESTS_UTILS_C
#define TERM_TESTS_UTILS_C
#include "tp.h"

int min(int a, int b) {
  return((a < b) ? a : b);
}

char *tp__basename(const char *path){
  const char *slash = strrchr(path, '/');

  if (slash)
    path = slash + 1;
  return((char *)path);
}

char *cell_at(board_t *board, int x, int y) {
  return(&board->cells[((board->height + y) % board->height) * board->width + ((board->width + x) % board->width)]);
}

char *str_repeat(char str[], unsigned int times){
  if (times < 1)
    return(NULL);

  char   *result;
  size_t str_len = strlen(str);
  result = malloc(sizeof(char) * str_len + 1);

  while (times--)
    strcat(result, str);
  return(result);
}

#endif
