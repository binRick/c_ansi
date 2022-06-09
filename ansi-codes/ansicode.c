/*
 * Copyright (C) 2021 taylor.fish <contact@taylor.fish>
 *
 * This file is part of rgbto256.
 *
 * rgbto256 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * rgbto256 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with rgbto256. If not, see <https://www.gnu.org/licenses/>.
 */

#include "ansicode.h"

#define C256_FG_CODE         "\x1b[38;5;%dm"
#define C256_BG_CODE         "\x1b[48;5;%dm"
#define TRUECOLOR_FG_CODE    "\x1b[38;2;%d;%d;%dm"
#define TRUECOLOR_BG_CODE    "\x1b[48;2;%d;%d;%dm"
#define RESET_CODE           "\x1b[0m"


void ansi_256_fg(FILE *file, int color) {
  fprintf(file, C256_FG_CODE, color);
}


void ansi_256_bg(FILE *file, int color) {
  fprintf(file, C256_BG_CODE, color);
}


void ansi_truecolor_fg(FILE *file, int r, int g, int b) {
  fprintf(file, TRUECOLOR_FG_CODE, r, g, b);
}


void ansi_truecolor_bg(FILE *file, int r, int g, int b) {
  fprintf(file, TRUECOLOR_BG_CODE, r, g, b);
}


void ansi_reset(FILE *file) {
  fputs(RESET_CODE, file);
}
