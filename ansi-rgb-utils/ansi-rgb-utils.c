#pragma once
/////////////////////////////////////////////////////////
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
/////////////////////////////////////////////////////////
#include "ansi-rgb-utils/ansi-rgb-utils.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "ansi-rgb-utils/ansi-rgb-utils-set.c"
#include "ansi-codes/ansi-codes.h"
#include "ansi-utils/ansi-utils.h"
#include "rgba/src/rgba.h"
#include "log/log.h"
#define AU_DELTA_E_K_L             2
#define AU_DELTA_E_K_1             0.048
#define AU_DELTA_E_K_2             0.014
static void au_rgb2lab(float r1, float g1, float b1, float *l2, float *a2, float *b2) {
  float x, y, z;

  r1 /= 255.0;
  g1 /= 255.0;
  b1 /= 255.0;

  if (r1 > 0.04045) {
    r1 = powf((r1 + 0.055) / 1.055, 2.4);
  }else{
    r1 /= 12.92;
  }

  if (g1 > 0.04045) {
    g1 = powf((g1 + 0.055) / 1.055, 2.4);
  }else{
    g1 /= 12.92;
  }

  if (b1 > 0.04045) {
    b1 = powf((b1 + 0.055) / 1.055, 2.4);
  }else{
    b1 /= 12.92;
  }

  r1 *= 100.0;
  g1 *= 100.0;
  b1 *= 100.0;

  x = r1 * 0.4124 + g1 * 0.3576 + b1 * 0.1805;
  y = r1 * 0.2126 + g1 * 0.7152 + b1 * 0.0722;
  z = r1 * 0.0193 + g1 * 0.1192 + b1 * 0.9505;

  x /= 95.047;
  y /= 100.000;
  z /= 108.883;

  if (x > 0.008856) {
    x = powf(x, 0.3333);
  }else{
    x = (7.787 * x) + 0.1379;
  }

  if (y > 0.008856) {
    y = powf(y, 0.3333);
  }else{
    y = (7.787 * y) + 0.1379;
  }

  if (z > 0.008856) {
    z = powf(z, 0.3333);
  }else{
    z = (7.787 * z) + 0.1379;
  }

  *l2 = (116.0 * y) - 16.0;
  *a2 = 500.0 * (x - y);
  *b2 = 200.0 * (y - z);
}

static float au_delta_e(float l1, float a1, float b1, float l2, float a2, float b2) {
  float deltaL, c1, c2, deltaC, deltaA, deltaB, deltaHSquared, deltaH;
  float q1, q2, q3, deltaE;

  deltaL        = l1 - l2;
  c1            = sqrtf(a1 * a1 + b1 * b1);
  c2            = sqrtf(a2 * a2 + b2 * b2);
  deltaC        = c1 - c2;
  deltaA        = a1 - a2;
  deltaB        = b1 - b2;
  deltaHSquared = deltaA * deltaA + deltaB * deltaB - deltaC * deltaC;

  if (deltaHSquared > 0) {
    deltaH = sqrtf(deltaHSquared);
  }else{
    deltaH = 0;
  }

  q1     = deltaL / AU_DELTA_E_K_L;
  q2     = deltaC / (1 + AU_DELTA_E_K_1 * c1);
  q3     = deltaH / (1 + AU_DELTA_E_K_2 * c2);
  deltaE = sqrtf(q1 * q1 + q2 * q2 + q3 * q3);

  return(deltaE);
}


static int au_closest_ansi_code(const uint32_t trp) {
  float l1, a1, b1;
  float l2, a2, b2;
  float delta, now, then = 255;
  int   i, t = 0;

  au_rgb2lab(trp >> 16 & 0xFF, trp >> 8 & 0xFF, trp & 0xFF, &l1, &a1, &b1);

  for (i = 0; i < sizeof(au_set) / sizeof(*au_set); i++) {
    au_rgb2lab(au_set[i] >> 16 & 0xFF,
            au_set[i] >> 8 & 0xFF,
            au_set[i] & 0xFF,
            &l2, &a2, &b2);
    now = au_delta_e(l1, a1, b1, l2, a2, b2);

    if (now < then) {
      then = now;
      t    = i;
    }
  }
  return(t + 16);
}

int au_hex_ansicode(char *HEX){
  int code=0;
  char gnd = '3';
  char *colp, *ptr;
  int  color;

  colp = HEX;

  if (*colp == '#') {
    *colp++;
  }
  return(au_closest_ansi_code((const uint32_t)colp));
}

LabColor ansi_to_lab(int ansi_num) {
  return(ansi_to_lab_map[ansi_num - ANSI_MAP_OFFSET]);
}

unsigned char luminanceFromRGB(unsigned char r, unsigned char g, unsigned char b) {
  return((unsigned char)(0.2126 * r + 0.7152 * g + 0.0722 * b));
}

void show_color(FILE *file, int color) {
  ansi_256_bg(file, color);
  fprintf(file, "                                                       ");
  ansi_reset(file);
  fprintf(file, " %3d\n", color);
}

static const char *top = "  \033[9%dm██████\033[3%dm▄\033[m";
static const char *mid = "  \033[9%dm██████\033[3%dm█\033[m";
static const char *bot = "  \033[3%dm ▀▀▀▀▀\033[3%dm▀\033[m";

static uint8_t    __colors;

static void po(void) {
  __colors = 0x7E;
}

static char *pr(const char *r) {
  struct StringBuffer *sb = stringbuffer_new();
  char                *s;

  for (int i = 0; i < 8; i++) {
    if (__colors & (1 << i)) {
      asprintf(&s, r, i, i);
      stringbuffer_append_string(sb, s);
    }
  }
  stringbuffer_append_string(sb, "\n");
  char *ret = stringbuffer_to_string(sb);

  stringbuffer_release(sb);
  return(ret);
}

char *get_color_boxes(void){
  struct StringBuffer *sb = stringbuffer_new();

  po();
  if (__colors) {
    printf("\n");
    stringbuffer_append_string(sb, pr(top));
    stringbuffer_append_string(sb, pr(mid));
    stringbuffer_append_string(sb, pr(mid));
    stringbuffer_append_string(sb, pr(bot));
    stringbuffer_append_string(sb, "\n");
  }
  char *ret = stringbuffer_to_string(sb);

  stringbuffer_release(sb);
  return(ret);
}

void au_print_hex_cube(FILE *file,char *hex){
  short ok;
  uint32_t val = rgba_from_string(hex,&ok), width;
  rgba_t _r;
  _r= rgba_new(val);
  width = get_terminal_width();

 fprintf(stdout,
     "\t%.2f/%.2f/%.2f/%.2f"
     "\t%s%s%s"
     "%s",
     _r.r,_r.g,_r.b,_r.a,
     strdup_escaped(au_set_fg_hex(hex)),
     "  VAL  ",
     strdup_escaped(RESET_CODE),
     "\n"
     );
}

void print_cube(FILE *file, int g) {
  for (int r = 0; r < 6; r++) {
    for (int b = 0; b < 6; b++) {
      int color = 16 + (36 * r) + (6 * g) + b;
      ansi_256_bg(file, color);
      ansi_256_fg(file, (g < 3) ? 231 : 16);
      fprintf(file, "   %3d   ", color);
    }
    ansi_reset(file);
    fprintf(file, "\n");
  }
}

char *au_set_fg_hex(const char *hex){ return au_hex(HEX_SET_FG_CODE,hex); }
char *au_set_bg_hex(const char *hex){ return au_hex(HEX_SET_BG_CODE,hex); }
char *au_fg_hex(const char *hex){ return au_hex(HEX_FG_CODE,hex); }
char *au_bg_hex(const char *hex){ return au_hex(HEX_BG_CODE,hex); }
char *au_hex(const char *fmt, const char *hex){
  char *s;
  asprintf(&s, fmt, stringfn_trim(stringfn_replace(hex,'#',' ')));
  return s;
}

char *au_bg_color(int color){
  char *s;
  asprintf(&s, C256_BG_CODE, color);
  return s;
}
char *au_fg_color(int color){
  char *s;
  asprintf(&s, C256_FG_CODE, color);
  return s;
}

////////////////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////////////////////////
bool is_in_rgb_range(struct RGB rgb) {
  if (
    rgb.red < 0
    || rgb.red > 1
    || rgb.green < 0
    || rgb.green > 1
    || rgb.blue < 0
    || rgb.blue > 1
    ) {
    return(false);
  }
  return(true);
}

float get_rgb_min(struct RGB rgb) {
  if (rgb.red <= rgb.green && rgb.red <= rgb.blue) {
    return(rgb.red);
  } else if (rgb.green <= rgb.blue) {
    return(rgb.green);
  } else {
    return(rgb.blue);
  }
}

float get_rgb_max(struct RGB rgb) {
  if (rgb.red >= rgb.green && rgb.red >= rgb.blue) {
    return(rgb.red);
  } else if (rgb.green >= rgb.blue) {
    return(rgb.green);
  } else {
    return(rgb.blue);
  }
}

/* returns max - min */
float get_rgb_range(struct RGB rgb) {
  return(get_rgb_max(rgb) - get_rgb_min(rgb));
}

/* rgb -> hsl luminance */
float rgb_to_hsl_luminance(struct RGB rgb) {
  return((get_rgb_min(rgb) + get_rgb_max(rgb)) / 2);
}

/* rgb -> hsl saturation */
float rgb_to_hsl_saturation(struct RGB rgb) {
  float min       = get_rgb_min(rgb);
  float max       = get_rgb_max(rgb);
  float luminance = rgb_to_hsl_luminance(rgb);

  if (luminance <= 0.5) {
    return((max - min) / (max + min));
  } else {
    return((max - min) / (2.0 - max - min));
  }
}

/* rgb -> hue */
float rgb_to_hue(struct RGB rgb) {
  float max   = get_rgb_max(rgb);
  float range = get_rgb_range(rgb);
  float hue;

  if (range == 0) {
    return(NAN);
  }

  if (rgb.red == max) {
    hue = fmodf((rgb.green - rgb.blue) / (range), 6);
  } else if (rgb.green == max) {
    hue = ((rgb.blue - rgb.red) / (range)) + 2;
  } else {
    hue = ((rgb.red - rgb.green) / (range)) + 4;
  }

  hue *= 60;
  if (hue < 0) {
    hue += 360;
  }
  return(hue);
}

void print_ansi_color(int red, int green, int blue, int wl, char *word) {
  for (int i = 0; i < wl; i++) {
    red   = ((255 / wl) * i);
    green = ((255 / wl) * i);
    blue  = ((255 / wl) * i);
    int x = (int)red;
    int y = (int)green;
    int z = (int)blue;
    printf("{%d,%d,%d}%c", x, y, z, word[i]);
  }
}

/* rgb -> hsv value */
float rgb_to_hsv_value(struct RGB rgb) {
  if (!is_in_rgb_range(rgb)) {
    return(-1);
  }

  return(get_rgb_max(rgb));
}

float rgb_to_hsv_saturation(struct RGB rgb) {
  if (!is_in_rgb_range(rgb)) {
    return(-1);
  }

  float value = rgb_to_hsv_value(rgb);

  if (value == 0) {
    return(-1);
  } else {
    return((get_rgb_range(rgb)) / value);
  }
}

void rgb_to_ints(struct RGBColor rgb, int *r, int *g, int *b) {
  *r = round(rgb.r * 255.0);
  *g = round(rgb.g * 255.0);
  *b = round(rgb.b * 255.0);
}

struct RGBColor rgb_from_ints(int r, int g, int b) {
  return((struct RGBColor){
    .r = r / 255.0,
    .g = g / 255.0,
    .b = b / 255.0,
  });
}
