#pragma once
#include <assert.h>
#include <ctype.h>
#include <dirent.h>
#include <err.h>
#include <errno.h>
#include <inttypes.h>
#include <libgen.h>
#include <limits.h>
#include <locale.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>
#include <wchar.h>
#include <wctype.h>
//////////////////////////////////////////////////////////
typedef struct ColorInfo                                    ColorInfo;
typedef struct Ansi_t                                       Ansi_t;
typedef struct CSEQ                                         CSEQ;
typedef struct SEQ                                          SEQ;
typedef struct RGB_t                                        RGB_t;
typedef struct { double L;   double a;   double b; }        LabColor;
typedef struct { double L;   double C;   double h; }        LChColor;
typedef struct { double r;   double g;    double b; }       RGBColor;
typedef struct { double rl;    double gl;    double bl; }   SRGBColor;
typedef struct { double x;    double y;   double z; }       XYZColor;
//////////////////////////////////////////////////////////
struct Ansi_t {
  const char *fg;
  const char *bg;
};
struct RGB_t {
  uint32_t red;
  uint32_t green;
  uint32_t blue;
  uint32_t alpha;
};
struct SEQ {
  const char *fg;
  const char *bg;
};
struct CSEQ {
  struct SEQ *ansi;
  struct SEQ *truecolor;
};
struct RGB {
  float red;
  float green;
  float blue;
};
struct ColorInfo {
  struct RGB_t  *rgb;
  struct Ansi_t *ansi;
  struct Ansi_t *truecolor;
  const char    *hex;
  const char    *name;
  int           ansicode;
};
struct hexstring { char hex[7]; };
struct RGB_Double { double r;   double g;   double b; };
struct RGB_Int { int r;     int g;   int b; };
struct HSV_Double { double h;    double s;   double v; };
struct HSL {
  float hue;
  float saturation;
  float luminance;
};
struct HSV {
  float hue;
  float saturation;
  float value;
};
//////////////////////////////////////////////////////////
static inline RGBColor ansi_to_rgb(int ansi_num);
static inline LabColor ansi_to_lab(int ansi_num);
void print_ansi_color(int red, int green, int blue, int wl, char *word);
void print_ansi_to_rgb(int ansi_code);
void ansi_256_fg(FILE *file, int color);
void ansi_256_bg(FILE *file, int color);
void ansi_truecolor_fg(FILE *file, int r, int g, int b);
void ansi_truecolor_bg(FILE *file, int r, int g, int b);
void ansi_reset(FILE *file);
bool is_in_rgb_range(struct RGB rgb);
float get_rgb_min(struct RGB rgb);
float get_rgb_max(struct RGB rgb);
float get_rgb_range(struct RGB rgb);
float rgb_to_hue(struct RGB rgb);
float rgb_to_hsl_luminance(struct RGB rgb);
float rgb_to_hsl_saturation(struct RGB rgb);
float rgb_to_hsv_value(struct RGB rgb);
float rgb_to_hsv_saturation(struct RGB rgb);
unsigned char luminanceFromRGB(unsigned char r, unsigned char g, unsigned char b);
void print_cube(FILE *file, int g);

//////////////////////////////////////////////////////////
#define SEQUENCE                  "printf \"\
\\033]4;0;#$(echo $color00)\\033\\ \
\\033]4;1;#$(echo $color01)\\033\\ \
\\033]4;2;#$(echo $color02)\\033\\ \
\\033]4;3;#$(echo $color03)\\033\\ \
\\033]4;4;#$(echo $color04)\\033\\ \
\\033]4;5;#$(echo $color05)\\033\\ \
\\033]4;6;#$(echo $color06)\\033\\ \
\\033]4;7;#$(echo $color07)\\033\\ \
\\033]4;8;#$(echo $color08)\\033\\ \
\\033]4;9;#$(echo $color09)\\033\\ \
\\033]4;10;#$(echo $color10)\\033\\ \
\\033]4;11;#$(echo $color11)\\033\\ \
\\033]4;12;#$(echo $color12)\\033\\ \
\\033]4;13;#$(echo $color13)\\033\\ \
\\033]4;14;#$(echo $color14)\\033\\ \
\\033]4;15;#$(echo $color15)\\033\\ \
\\033]10;#$(echo $foreground)\\033\\ \
\\033]11;#$(echo $background)\\033\\ \
\\033]12;#$(echo $cursor)\\033\\ \
\\033[21D\""

#define PALETTE                   "\
\033[48;5;0m  \033[0m\
\033[48;5;1m  \033[0m\
\033[48;5;2m  \033[0m\
\033[48;5;3m  \033[0m\
\033[48;5;4m  \033[0m\
\033[48;5;5m  \033[0m\
\033[48;5;6m  \033[0m\
\033[48;5;7m  \033[0m\n\
\033[48;5;8m  \033[0m\
\033[48;5;9m  \033[0m\
\033[48;5;10m  \033[0m\
\033[48;5;11m  \033[0m\
\033[48;5;12m  \033[0m\
\033[48;5;13m  \033[0m\
\033[48;5;14m  \033[0m\
\033[48;5;15m  \033[0m\n"
/***********************/// Control Code CONSTANTS
#define C256_FG_CODE              "\x1b[38;5;%dm"
#define C256_BG_CODE              "\x1b[48;5;%dm"
#define TRUECOLOR_FG_CODE         "\x1b[38;2;%d;%d;%dm"
#define TRUECOLOR_BG_CODE         "\x1b[48;2;%d;%d;%dm"
#define RESET_CODE                "\x1b[0m"
#define COLOR_RGB                 L"\033[38;2;%u;%u;%um"
#define COLOR_FG_RGB              L"\033[48;2;%u;%u;%um"
#define COLOR_RESET_TO_DEFAULT    L"\033[0m"
/***********************/// HEX COLOR CONSTANTS
#define HEX_LEN                   6
static const char *HEX_VALUES = "0123456789ABCDEF";
/***********************///
#define LAB_XYZ_SIGMA             (6.0 / 29.0)
#define LAB_XYZ_SIGMA_SQUARED     (LAB_XYZ_SIGMA * LAB_XYZ_SIGMA)
#define LAB_XYZ_SIGMA_CUBED       (LAB_XYZ_SIGMA_SQUARED * LAB_XYZ_SIGMA)
#define XYZ_D65_XN                0.95047
#define XYZ_D65_YN                1.0
#define XYZ_D65_ZN                1.08883
#define VAL_25_POW_7              6103515625
/***********************/// ANSI COLOR CONSTANTS
#define ANSI_MIN                  16
#define ANSI_MAX                  256
#define ANSI_MAP_OFFSET           ANSI_MIN
#define ANSI_MAP_LEN              (ANSI_MAX - ANSI_MAP_OFFSET)
//////////////////////////////////////////////////////////
#define ESCAPE                    "\x1b"
#define BOLD                      ESCAPE "[1m"
#define DIM                       ESCAPE "[2m"
#define ITALIC                    ESCAPE "[3m"
#define UNDER                     ESCAPE "[4m"
#define BLINK                     ESCAPE "[5m"
#define INVERSE                   ESCAPE "[7m"
#define STRIKE                    ESCAPE "[8m"
// Text 256 colors
#define FG_256(code)       printf(ESCAPE "[38;5;" #code "m")
#define BG_256(code)       printf(ESCAPE "[48;5;" #code "m")
// Text RGB colors
#define FG_RGB(r, g, b)    printf(ESCAPE "[38;2;" #r ";" #g ";" #b "m")
#define BG_RGB(r, g, b)    printf(ESCAPE "[48;2;" #r ";" #g ";" #b "m")
// Disable colors
#define FG_DISABLE()       printf(ESCAPE "[39m")
#define BG_DISABLE()       printf(ESCAPE "[49m")
// Terminal utilities
#define CLEAR()            printf(ESCAPE "c")
#define RESET    ESCAPE "[0m" ESCAPE "[49m"
#define RESETF()           printf(ESCAPE "[0m" ESCAPE "[49m")
#define OUTPUT_HIDE()      printf(ESCAPE "^")
// Cursor attributes
#define CURSOR_HIDE()      printf(ESCAPE "[?25l")
#define CURSOR_SHOW()      printf(ESCAPE "[?25h")
//////////////////////////////////////////////////////////
static const double srgb_to_xyz_matrix[] = {
  0.4124, 0.3576, 0.1805,
  0.2126, 0.7152, 0.0722,
  0.0193, 0.1192, 0.9505,
};
static const double xyz_to_srgb_matrix[] = {
  3.2406255,  -1.537208,  -0.4986286,
  -0.9689307, 1.8757561,  0.0415175,
  0.0557101,  -0.2040211, 1.0569959,
};
//////////////////////////////////////////////////////////
const RGBColor      ansi_to_rgb_map[] = {
  { 0x0p+0,               0x0p+0,               0x0p+0               },
  { 0x0p+0,               0x0p+0,               0x1.7d7d7d7d7d7d8p-2 },
  { 0x0p+0,               0x0p+0,               0x1.0f0f0f0f0f0f1p-1 },
  { 0x0p+0,               0x0p+0,               0x1.5f5f5f5f5f5f6p-1 },
  { 0x0p+0,               0x0p+0,               0x1.afafafafafafbp-1 },
  { 0x0p+0,               0x0p+0,               0x1p+0               },
  { 0x0p+0,               0x1.7d7d7d7d7d7d8p-2, 0x0p+0               },
  { 0x0p+0,               0x1.7d7d7d7d7d7d8p-2, 0x1.7d7d7d7d7d7d8p-2 },
  { 0x0p+0,               0x1.7d7d7d7d7d7d8p-2, 0x1.0f0f0f0f0f0f1p-1 },
  { 0x0p+0,               0x1.7d7d7d7d7d7d8p-2, 0x1.5f5f5f5f5f5f6p-1 },
  { 0x0p+0,               0x1.7d7d7d7d7d7d8p-2, 0x1.afafafafafafbp-1 },
  { 0x0p+0,               0x1.7d7d7d7d7d7d8p-2, 0x1p+0               },
  { 0x0p+0,               0x1.0f0f0f0f0f0f1p-1, 0x0p+0               },
  { 0x0p+0,               0x1.0f0f0f0f0f0f1p-1, 0x1.7d7d7d7d7d7d8p-2 },
  { 0x0p+0,               0x1.0f0f0f0f0f0f1p-1, 0x1.0f0f0f0f0f0f1p-1 },
  { 0x0p+0,               0x1.0f0f0f0f0f0f1p-1, 0x1.5f5f5f5f5f5f6p-1 },
  { 0x0p+0,               0x1.0f0f0f0f0f0f1p-1, 0x1.afafafafafafbp-1 },
  { 0x0p+0,               0x1.0f0f0f0f0f0f1p-1, 0x1p+0               },
  { 0x0p+0,               0x1.5f5f5f5f5f5f6p-1, 0x0p+0               },
  { 0x0p+0,               0x1.5f5f5f5f5f5f6p-1, 0x1.7d7d7d7d7d7d8p-2 },
  { 0x0p+0,               0x1.5f5f5f5f5f5f6p-1, 0x1.0f0f0f0f0f0f1p-1 },
  { 0x0p+0,               0x1.5f5f5f5f5f5f6p-1, 0x1.5f5f5f5f5f5f6p-1 },
  { 0x0p+0,               0x1.5f5f5f5f5f5f6p-1, 0x1.afafafafafafbp-1 },
  { 0x0p+0,               0x1.5f5f5f5f5f5f6p-1, 0x1p+0               },
  { 0x0p+0,               0x1.afafafafafafbp-1, 0x0p+0               },
  { 0x0p+0,               0x1.afafafafafafbp-1, 0x1.7d7d7d7d7d7d8p-2 },
  { 0x0p+0,               0x1.afafafafafafbp-1, 0x1.0f0f0f0f0f0f1p-1 },
  { 0x0p+0,               0x1.afafafafafafbp-1, 0x1.5f5f5f5f5f5f6p-1 },
  { 0x0p+0,               0x1.afafafafafafbp-1, 0x1.afafafafafafbp-1 },
  { 0x0p+0,               0x1.afafafafafafbp-1, 0x1p+0               },
  { 0x0p+0,               0x1p+0,               0x0p+0               },
  { 0x0p+0,               0x1p+0,               0x1.7d7d7d7d7d7d8p-2 },
  { 0x0p+0,               0x1p+0,               0x1.0f0f0f0f0f0f1p-1 },
  { 0x0p+0,               0x1p+0,               0x1.5f5f5f5f5f5f6p-1 },
  { 0x0p+0,               0x1p+0,               0x1.afafafafafafbp-1 },
  { 0x0p+0,               0x1p+0,               0x1p+0               },
  { 0x1.7d7d7d7d7d7d8p-2, 0x0p+0,               0x0p+0               },
  { 0x1.7d7d7d7d7d7d8p-2, 0x0p+0,               0x1.7d7d7d7d7d7d8p-2 },
  { 0x1.7d7d7d7d7d7d8p-2, 0x0p+0,               0x1.0f0f0f0f0f0f1p-1 },
  { 0x1.7d7d7d7d7d7d8p-2, 0x0p+0,               0x1.5f5f5f5f5f5f6p-1 },
  { 0x1.7d7d7d7d7d7d8p-2, 0x0p+0,               0x1.afafafafafafbp-1 },
  { 0x1.7d7d7d7d7d7d8p-2, 0x0p+0,               0x1p+0               },
  { 0x1.7d7d7d7d7d7d8p-2, 0x1.7d7d7d7d7d7d8p-2, 0x0p+0               },
  { 0x1.7d7d7d7d7d7d8p-2, 0x1.7d7d7d7d7d7d8p-2, 0x1.7d7d7d7d7d7d8p-2 },
  { 0x1.7d7d7d7d7d7d8p-2, 0x1.7d7d7d7d7d7d8p-2, 0x1.0f0f0f0f0f0f1p-1 },
  { 0x1.7d7d7d7d7d7d8p-2, 0x1.7d7d7d7d7d7d8p-2, 0x1.5f5f5f5f5f5f6p-1 },
  { 0x1.7d7d7d7d7d7d8p-2, 0x1.7d7d7d7d7d7d8p-2, 0x1.afafafafafafbp-1 },
  { 0x1.7d7d7d7d7d7d8p-2, 0x1.7d7d7d7d7d7d8p-2, 0x1p+0               },
  { 0x1.7d7d7d7d7d7d8p-2, 0x1.0f0f0f0f0f0f1p-1, 0x0p+0               },
  { 0x1.7d7d7d7d7d7d8p-2, 0x1.0f0f0f0f0f0f1p-1, 0x1.7d7d7d7d7d7d8p-2 },
  { 0x1.7d7d7d7d7d7d8p-2, 0x1.0f0f0f0f0f0f1p-1, 0x1.0f0f0f0f0f0f1p-1 },
  { 0x1.7d7d7d7d7d7d8p-2, 0x1.0f0f0f0f0f0f1p-1, 0x1.5f5f5f5f5f5f6p-1 },
  { 0x1.7d7d7d7d7d7d8p-2, 0x1.0f0f0f0f0f0f1p-1, 0x1.afafafafafafbp-1 },
  { 0x1.7d7d7d7d7d7d8p-2, 0x1.0f0f0f0f0f0f1p-1, 0x1p+0               },
  { 0x1.7d7d7d7d7d7d8p-2, 0x1.5f5f5f5f5f5f6p-1, 0x0p+0               },
  { 0x1.7d7d7d7d7d7d8p-2, 0x1.5f5f5f5f5f5f6p-1, 0x1.7d7d7d7d7d7d8p-2 },
  { 0x1.7d7d7d7d7d7d8p-2, 0x1.5f5f5f5f5f5f6p-1, 0x1.0f0f0f0f0f0f1p-1 },
  { 0x1.7d7d7d7d7d7d8p-2, 0x1.5f5f5f5f5f5f6p-1, 0x1.5f5f5f5f5f5f6p-1 },
  { 0x1.7d7d7d7d7d7d8p-2, 0x1.5f5f5f5f5f5f6p-1, 0x1.afafafafafafbp-1 },
  { 0x1.7d7d7d7d7d7d8p-2, 0x1.5f5f5f5f5f5f6p-1, 0x1p+0               },
  { 0x1.7d7d7d7d7d7d8p-2, 0x1.afafafafafafbp-1, 0x0p+0               },
  { 0x1.7d7d7d7d7d7d8p-2, 0x1.afafafafafafbp-1, 0x1.7d7d7d7d7d7d8p-2 },
  { 0x1.7d7d7d7d7d7d8p-2, 0x1.afafafafafafbp-1, 0x1.0f0f0f0f0f0f1p-1 },
  { 0x1.7d7d7d7d7d7d8p-2, 0x1.afafafafafafbp-1, 0x1.5f5f5f5f5f5f6p-1 },
  { 0x1.7d7d7d7d7d7d8p-2, 0x1.afafafafafafbp-1, 0x1.afafafafafafbp-1 },
  { 0x1.7d7d7d7d7d7d8p-2, 0x1.afafafafafafbp-1, 0x1p+0               },
  { 0x1.7d7d7d7d7d7d8p-2, 0x1p+0,               0x0p+0               },
  { 0x1.7d7d7d7d7d7d8p-2, 0x1p+0,               0x1.7d7d7d7d7d7d8p-2 },
  { 0x1.7d7d7d7d7d7d8p-2, 0x1p+0,               0x1.0f0f0f0f0f0f1p-1 },
  { 0x1.7d7d7d7d7d7d8p-2, 0x1p+0,               0x1.5f5f5f5f5f5f6p-1 },
  { 0x1.7d7d7d7d7d7d8p-2, 0x1p+0,               0x1.afafafafafafbp-1 },
  { 0x1.7d7d7d7d7d7d8p-2, 0x1p+0,               0x1p+0               },
  { 0x1.0f0f0f0f0f0f1p-1, 0x0p+0,               0x0p+0               },
  { 0x1.0f0f0f0f0f0f1p-1, 0x0p+0,               0x1.7d7d7d7d7d7d8p-2 },
  { 0x1.0f0f0f0f0f0f1p-1, 0x0p+0,               0x1.0f0f0f0f0f0f1p-1 },
  { 0x1.0f0f0f0f0f0f1p-1, 0x0p+0,               0x1.5f5f5f5f5f5f6p-1 },
  { 0x1.0f0f0f0f0f0f1p-1, 0x0p+0,               0x1.afafafafafafbp-1 },
  { 0x1.0f0f0f0f0f0f1p-1, 0x0p+0,               0x1p+0               },
  { 0x1.0f0f0f0f0f0f1p-1, 0x1.7d7d7d7d7d7d8p-2, 0x0p+0               },
  { 0x1.0f0f0f0f0f0f1p-1, 0x1.7d7d7d7d7d7d8p-2, 0x1.7d7d7d7d7d7d8p-2 },
  { 0x1.0f0f0f0f0f0f1p-1, 0x1.7d7d7d7d7d7d8p-2, 0x1.0f0f0f0f0f0f1p-1 },
  { 0x1.0f0f0f0f0f0f1p-1, 0x1.7d7d7d7d7d7d8p-2, 0x1.5f5f5f5f5f5f6p-1 },
  { 0x1.0f0f0f0f0f0f1p-1, 0x1.7d7d7d7d7d7d8p-2, 0x1.afafafafafafbp-1 },
  { 0x1.0f0f0f0f0f0f1p-1, 0x1.7d7d7d7d7d7d8p-2, 0x1p+0               },
  { 0x1.0f0f0f0f0f0f1p-1, 0x1.0f0f0f0f0f0f1p-1, 0x0p+0               },
  { 0x1.0f0f0f0f0f0f1p-1, 0x1.0f0f0f0f0f0f1p-1, 0x1.7d7d7d7d7d7d8p-2 },
  { 0x1.0f0f0f0f0f0f1p-1, 0x1.0f0f0f0f0f0f1p-1, 0x1.0f0f0f0f0f0f1p-1 },
  { 0x1.0f0f0f0f0f0f1p-1, 0x1.0f0f0f0f0f0f1p-1, 0x1.5f5f5f5f5f5f6p-1 },
  { 0x1.0f0f0f0f0f0f1p-1, 0x1.0f0f0f0f0f0f1p-1, 0x1.afafafafafafbp-1 },
  { 0x1.0f0f0f0f0f0f1p-1, 0x1.0f0f0f0f0f0f1p-1, 0x1p+0               },
  { 0x1.0f0f0f0f0f0f1p-1, 0x1.5f5f5f5f5f5f6p-1, 0x0p+0               },
  { 0x1.0f0f0f0f0f0f1p-1, 0x1.5f5f5f5f5f5f6p-1, 0x1.7d7d7d7d7d7d8p-2 },
  { 0x1.0f0f0f0f0f0f1p-1, 0x1.5f5f5f5f5f5f6p-1, 0x1.0f0f0f0f0f0f1p-1 },
  { 0x1.0f0f0f0f0f0f1p-1, 0x1.5f5f5f5f5f5f6p-1, 0x1.5f5f5f5f5f5f6p-1 },
  { 0x1.0f0f0f0f0f0f1p-1, 0x1.5f5f5f5f5f5f6p-1, 0x1.afafafafafafbp-1 },
  { 0x1.0f0f0f0f0f0f1p-1, 0x1.5f5f5f5f5f5f6p-1, 0x1p+0               },
  { 0x1.0f0f0f0f0f0f1p-1, 0x1.afafafafafafbp-1, 0x0p+0               },
  { 0x1.0f0f0f0f0f0f1p-1, 0x1.afafafafafafbp-1, 0x1.7d7d7d7d7d7d8p-2 },
  { 0x1.0f0f0f0f0f0f1p-1, 0x1.afafafafafafbp-1, 0x1.0f0f0f0f0f0f1p-1 },
  { 0x1.0f0f0f0f0f0f1p-1, 0x1.afafafafafafbp-1, 0x1.5f5f5f5f5f5f6p-1 },
  { 0x1.0f0f0f0f0f0f1p-1, 0x1.afafafafafafbp-1, 0x1.afafafafafafbp-1 },
  { 0x1.0f0f0f0f0f0f1p-1, 0x1.afafafafafafbp-1, 0x1p+0               },
  { 0x1.0f0f0f0f0f0f1p-1, 0x1p+0,               0x0p+0               },
  { 0x1.0f0f0f0f0f0f1p-1, 0x1p+0,               0x1.7d7d7d7d7d7d8p-2 },
  { 0x1.0f0f0f0f0f0f1p-1, 0x1p+0,               0x1.0f0f0f0f0f0f1p-1 },
  { 0x1.0f0f0f0f0f0f1p-1, 0x1p+0,               0x1.5f5f5f5f5f5f6p-1 },
  { 0x1.0f0f0f0f0f0f1p-1, 0x1p+0,               0x1.afafafafafafbp-1 },
  { 0x1.0f0f0f0f0f0f1p-1, 0x1p+0,               0x1p+0               },
  { 0x1.5f5f5f5f5f5f6p-1, 0x0p+0,               0x0p+0               },
  { 0x1.5f5f5f5f5f5f6p-1, 0x0p+0,               0x1.7d7d7d7d7d7d8p-2 },
  { 0x1.5f5f5f5f5f5f6p-1, 0x0p+0,               0x1.0f0f0f0f0f0f1p-1 },
  { 0x1.5f5f5f5f5f5f6p-1, 0x0p+0,               0x1.5f5f5f5f5f5f6p-1 },
  { 0x1.5f5f5f5f5f5f6p-1, 0x0p+0,               0x1.afafafafafafbp-1 },
  { 0x1.5f5f5f5f5f5f6p-1, 0x0p+0,               0x1p+0               },
  { 0x1.5f5f5f5f5f5f6p-1, 0x1.7d7d7d7d7d7d8p-2, 0x0p+0               },
  { 0x1.5f5f5f5f5f5f6p-1, 0x1.7d7d7d7d7d7d8p-2, 0x1.7d7d7d7d7d7d8p-2 },
  { 0x1.5f5f5f5f5f5f6p-1, 0x1.7d7d7d7d7d7d8p-2, 0x1.0f0f0f0f0f0f1p-1 },
  { 0x1.5f5f5f5f5f5f6p-1, 0x1.7d7d7d7d7d7d8p-2, 0x1.5f5f5f5f5f5f6p-1 },
  { 0x1.5f5f5f5f5f5f6p-1, 0x1.7d7d7d7d7d7d8p-2, 0x1.afafafafafafbp-1 },
  { 0x1.5f5f5f5f5f5f6p-1, 0x1.7d7d7d7d7d7d8p-2, 0x1p+0               },
  { 0x1.5f5f5f5f5f5f6p-1, 0x1.0f0f0f0f0f0f1p-1, 0x0p+0               },
  { 0x1.5f5f5f5f5f5f6p-1, 0x1.0f0f0f0f0f0f1p-1, 0x1.7d7d7d7d7d7d8p-2 },
  { 0x1.5f5f5f5f5f5f6p-1, 0x1.0f0f0f0f0f0f1p-1, 0x1.0f0f0f0f0f0f1p-1 },
  { 0x1.5f5f5f5f5f5f6p-1, 0x1.0f0f0f0f0f0f1p-1, 0x1.5f5f5f5f5f5f6p-1 },
  { 0x1.5f5f5f5f5f5f6p-1, 0x1.0f0f0f0f0f0f1p-1, 0x1.afafafafafafbp-1 },
  { 0x1.5f5f5f5f5f5f6p-1, 0x1.0f0f0f0f0f0f1p-1, 0x1p+0               },
  { 0x1.5f5f5f5f5f5f6p-1, 0x1.5f5f5f5f5f5f6p-1, 0x0p+0               },
  { 0x1.5f5f5f5f5f5f6p-1, 0x1.5f5f5f5f5f5f6p-1, 0x1.7d7d7d7d7d7d8p-2 },
  { 0x1.5f5f5f5f5f5f6p-1, 0x1.5f5f5f5f5f5f6p-1, 0x1.0f0f0f0f0f0f1p-1 },
  { 0x1.5f5f5f5f5f5f6p-1, 0x1.5f5f5f5f5f5f6p-1, 0x1.5f5f5f5f5f5f6p-1 },
  { 0x1.5f5f5f5f5f5f6p-1, 0x1.5f5f5f5f5f5f6p-1, 0x1.afafafafafafbp-1 },
  { 0x1.5f5f5f5f5f5f6p-1, 0x1.5f5f5f5f5f5f6p-1, 0x1p+0               },
  { 0x1.5f5f5f5f5f5f6p-1, 0x1.afafafafafafbp-1, 0x0p+0               },
  { 0x1.5f5f5f5f5f5f6p-1, 0x1.afafafafafafbp-1, 0x1.7d7d7d7d7d7d8p-2 },
  { 0x1.5f5f5f5f5f5f6p-1, 0x1.afafafafafafbp-1, 0x1.0f0f0f0f0f0f1p-1 },
  { 0x1.5f5f5f5f5f5f6p-1, 0x1.afafafafafafbp-1, 0x1.5f5f5f5f5f5f6p-1 },
  { 0x1.5f5f5f5f5f5f6p-1, 0x1.afafafafafafbp-1, 0x1.afafafafafafbp-1 },
  { 0x1.5f5f5f5f5f5f6p-1, 0x1.afafafafafafbp-1, 0x1p+0               },
  { 0x1.5f5f5f5f5f5f6p-1, 0x1p+0,               0x0p+0               },
  { 0x1.5f5f5f5f5f5f6p-1, 0x1p+0,               0x1.7d7d7d7d7d7d8p-2 },
  { 0x1.5f5f5f5f5f5f6p-1, 0x1p+0,               0x1.0f0f0f0f0f0f1p-1 },
  { 0x1.5f5f5f5f5f5f6p-1, 0x1p+0,               0x1.5f5f5f5f5f5f6p-1 },
  { 0x1.5f5f5f5f5f5f6p-1, 0x1p+0,               0x1.afafafafafafbp-1 },
  { 0x1.5f5f5f5f5f5f6p-1, 0x1p+0,               0x1p+0               },
  { 0x1.afafafafafafbp-1, 0x0p+0,               0x0p+0               },
  { 0x1.afafafafafafbp-1, 0x0p+0,               0x1.7d7d7d7d7d7d8p-2 },
  { 0x1.afafafafafafbp-1, 0x0p+0,               0x1.0f0f0f0f0f0f1p-1 },
  { 0x1.afafafafafafbp-1, 0x0p+0,               0x1.5f5f5f5f5f5f6p-1 },
  { 0x1.afafafafafafbp-1, 0x0p+0,               0x1.afafafafafafbp-1 },
  { 0x1.afafafafafafbp-1, 0x0p+0,               0x1p+0               },
  { 0x1.afafafafafafbp-1, 0x1.7d7d7d7d7d7d8p-2, 0x0p+0               },
  { 0x1.afafafafafafbp-1, 0x1.7d7d7d7d7d7d8p-2, 0x1.7d7d7d7d7d7d8p-2 },
  { 0x1.afafafafafafbp-1, 0x1.7d7d7d7d7d7d8p-2, 0x1.0f0f0f0f0f0f1p-1 },
  { 0x1.afafafafafafbp-1, 0x1.7d7d7d7d7d7d8p-2, 0x1.5f5f5f5f5f5f6p-1 },
  { 0x1.afafafafafafbp-1, 0x1.7d7d7d7d7d7d8p-2, 0x1.afafafafafafbp-1 },
  { 0x1.afafafafafafbp-1, 0x1.7d7d7d7d7d7d8p-2, 0x1p+0               },
  { 0x1.afafafafafafbp-1, 0x1.0f0f0f0f0f0f1p-1, 0x0p+0               },
  { 0x1.afafafafafafbp-1, 0x1.0f0f0f0f0f0f1p-1, 0x1.7d7d7d7d7d7d8p-2 },
  { 0x1.afafafafafafbp-1, 0x1.0f0f0f0f0f0f1p-1, 0x1.0f0f0f0f0f0f1p-1 },
  { 0x1.afafafafafafbp-1, 0x1.0f0f0f0f0f0f1p-1, 0x1.5f5f5f5f5f5f6p-1 },
  { 0x1.afafafafafafbp-1, 0x1.0f0f0f0f0f0f1p-1, 0x1.afafafafafafbp-1 },
  { 0x1.afafafafafafbp-1, 0x1.0f0f0f0f0f0f1p-1, 0x1p+0               },
  { 0x1.afafafafafafbp-1, 0x1.5f5f5f5f5f5f6p-1, 0x0p+0               },
  { 0x1.afafafafafafbp-1, 0x1.5f5f5f5f5f5f6p-1, 0x1.7d7d7d7d7d7d8p-2 },
  { 0x1.afafafafafafbp-1, 0x1.5f5f5f5f5f5f6p-1, 0x1.0f0f0f0f0f0f1p-1 },
  { 0x1.afafafafafafbp-1, 0x1.5f5f5f5f5f5f6p-1, 0x1.5f5f5f5f5f5f6p-1 },
  { 0x1.afafafafafafbp-1, 0x1.5f5f5f5f5f5f6p-1, 0x1.afafafafafafbp-1 },
  { 0x1.afafafafafafbp-1, 0x1.5f5f5f5f5f5f6p-1, 0x1p+0               },
  { 0x1.afafafafafafbp-1, 0x1.afafafafafafbp-1, 0x0p+0               },
  { 0x1.afafafafafafbp-1, 0x1.afafafafafafbp-1, 0x1.7d7d7d7d7d7d8p-2 },
  { 0x1.afafafafafafbp-1, 0x1.afafafafafafbp-1, 0x1.0f0f0f0f0f0f1p-1 },
  { 0x1.afafafafafafbp-1, 0x1.afafafafafafbp-1, 0x1.5f5f5f5f5f5f6p-1 },
  { 0x1.afafafafafafbp-1, 0x1.afafafafafafbp-1, 0x1.afafafafafafbp-1 },
  { 0x1.afafafafafafbp-1, 0x1.afafafafafafbp-1, 0x1p+0               },
  { 0x1.afafafafafafbp-1, 0x1p+0,               0x0p+0               },
  { 0x1.afafafafafafbp-1, 0x1p+0,               0x1.7d7d7d7d7d7d8p-2 },
  { 0x1.afafafafafafbp-1, 0x1p+0,               0x1.0f0f0f0f0f0f1p-1 },
  { 0x1.afafafafafafbp-1, 0x1p+0,               0x1.5f5f5f5f5f5f6p-1 },
  { 0x1.afafafafafafbp-1, 0x1p+0,               0x1.afafafafafafbp-1 },
  { 0x1.afafafafafafbp-1, 0x1p+0,               0x1p+0               },
  { 0x1p+0,               0x0p+0,               0x0p+0               },
  { 0x1p+0,               0x0p+0,               0x1.7d7d7d7d7d7d8p-2 },
  { 0x1p+0,               0x0p+0,               0x1.0f0f0f0f0f0f1p-1 },
  { 0x1p+0,               0x0p+0,               0x1.5f5f5f5f5f5f6p-1 },
  { 0x1p+0,               0x0p+0,               0x1.afafafafafafbp-1 },
  { 0x1p+0,               0x0p+0,               0x1p+0               },
  { 0x1p+0,               0x1.7d7d7d7d7d7d8p-2, 0x0p+0               },
  { 0x1p+0,               0x1.7d7d7d7d7d7d8p-2, 0x1.7d7d7d7d7d7d8p-2 },
  { 0x1p+0,               0x1.7d7d7d7d7d7d8p-2, 0x1.0f0f0f0f0f0f1p-1 },
  { 0x1p+0,               0x1.7d7d7d7d7d7d8p-2, 0x1.5f5f5f5f5f5f6p-1 },
  { 0x1p+0,               0x1.7d7d7d7d7d7d8p-2, 0x1.afafafafafafbp-1 },
  { 0x1p+0,               0x1.7d7d7d7d7d7d8p-2, 0x1p+0               },
  { 0x1p+0,               0x1.0f0f0f0f0f0f1p-1, 0x0p+0               },
  { 0x1p+0,               0x1.0f0f0f0f0f0f1p-1, 0x1.7d7d7d7d7d7d8p-2 },
  { 0x1p+0,               0x1.0f0f0f0f0f0f1p-1, 0x1.0f0f0f0f0f0f1p-1 },
  { 0x1p+0,               0x1.0f0f0f0f0f0f1p-1, 0x1.5f5f5f5f5f5f6p-1 },
  { 0x1p+0,               0x1.0f0f0f0f0f0f1p-1, 0x1.afafafafafafbp-1 },
  { 0x1p+0,               0x1.0f0f0f0f0f0f1p-1, 0x1p+0               },
  { 0x1p+0,               0x1.5f5f5f5f5f5f6p-1, 0x0p+0               },
  { 0x1p+0,               0x1.5f5f5f5f5f5f6p-1, 0x1.7d7d7d7d7d7d8p-2 },
  { 0x1p+0,               0x1.5f5f5f5f5f5f6p-1, 0x1.0f0f0f0f0f0f1p-1 },
  { 0x1p+0,               0x1.5f5f5f5f5f5f6p-1, 0x1.5f5f5f5f5f5f6p-1 },
  { 0x1p+0,               0x1.5f5f5f5f5f5f6p-1, 0x1.afafafafafafbp-1 },
  { 0x1p+0,               0x1.5f5f5f5f5f5f6p-1, 0x1p+0               },
  { 0x1p+0,               0x1.afafafafafafbp-1, 0x0p+0               },
  { 0x1p+0,               0x1.afafafafafafbp-1, 0x1.7d7d7d7d7d7d8p-2 },
  { 0x1p+0,               0x1.afafafafafafbp-1, 0x1.0f0f0f0f0f0f1p-1 },
  { 0x1p+0,               0x1.afafafafafafbp-1, 0x1.5f5f5f5f5f5f6p-1 },
  { 0x1p+0,               0x1.afafafafafafbp-1, 0x1.afafafafafafbp-1 },
  { 0x1p+0,               0x1.afafafafafafbp-1, 0x1p+0               },
  { 0x1p+0,               0x1p+0,               0x0p+0               },
  { 0x1p+0,               0x1p+0,               0x1.7d7d7d7d7d7d8p-2 },
  { 0x1p+0,               0x1p+0,               0x1.0f0f0f0f0f0f1p-1 },
  { 0x1p+0,               0x1p+0,               0x1.5f5f5f5f5f5f6p-1 },
  { 0x1p+0,               0x1p+0,               0x1.afafafafafafbp-1 },
  { 0x1p+0,               0x1p+0,               0x1p+0               },
  { 0x1.010101010101p-5,  0x1.010101010101p-5,  0x1.010101010101p-5  },
  { 0x1.2121212121212p-4, 0x1.2121212121212p-4, 0x1.2121212121212p-4 },
  { 0x1.c1c1c1c1c1c1cp-4, 0x1.c1c1c1c1c1c1cp-4, 0x1.c1c1c1c1c1c1cp-4 },
  { 0x1.3131313131313p-3, 0x1.3131313131313p-3, 0x1.3131313131313p-3 },
  { 0x1.8181818181818p-3, 0x1.8181818181818p-3, 0x1.8181818181818p-3 },
  { 0x1.d1d1d1d1d1d1dp-3, 0x1.d1d1d1d1d1d1dp-3, 0x1.d1d1d1d1d1d1dp-3 },
  { 0x1.1111111111111p-2, 0x1.1111111111111p-2, 0x1.1111111111111p-2 },
  { 0x1.3939393939394p-2, 0x1.3939393939394p-2, 0x1.3939393939394p-2 },
  { 0x1.6161616161616p-2, 0x1.6161616161616p-2, 0x1.6161616161616p-2 },
  { 0x1.8989898989898p-2, 0x1.8989898989898p-2, 0x1.8989898989898p-2 },
  { 0x1.b1b1b1b1b1b1bp-2, 0x1.b1b1b1b1b1b1bp-2, 0x1.b1b1b1b1b1b1bp-2 },
  { 0x1.d9d9d9d9d9d9ep-2, 0x1.d9d9d9d9d9d9ep-2, 0x1.d9d9d9d9d9d9ep-2 },
  { 0x1.010101010101p-1,  0x1.010101010101p-1,  0x1.010101010101p-1  },
  { 0x1.1515151515151p-1, 0x1.1515151515151p-1, 0x1.1515151515151p-1 },
  { 0x1.2929292929292p-1, 0x1.2929292929292p-1, 0x1.2929292929292p-1 },
  { 0x1.3d3d3d3d3d3d4p-1, 0x1.3d3d3d3d3d3d4p-1, 0x1.3d3d3d3d3d3d4p-1 },
  { 0x1.5151515151515p-1, 0x1.5151515151515p-1, 0x1.5151515151515p-1 },
  { 0x1.6565656565656p-1, 0x1.6565656565656p-1, 0x1.6565656565656p-1 },
  { 0x1.7979797979798p-1, 0x1.7979797979798p-1, 0x1.7979797979798p-1 },
  { 0x1.8d8d8d8d8d8d9p-1, 0x1.8d8d8d8d8d8d9p-1, 0x1.8d8d8d8d8d8d9p-1 },
  { 0x1.a1a1a1a1a1a1ap-1, 0x1.a1a1a1a1a1a1ap-1, 0x1.a1a1a1a1a1a1ap-1 },
  { 0x1.b5b5b5b5b5b5bp-1, 0x1.b5b5b5b5b5b5bp-1, 0x1.b5b5b5b5b5b5bp-1 },
  { 0x1.c9c9c9c9c9c9cp-1, 0x1.c9c9c9c9c9c9cp-1, 0x1.c9c9c9c9c9c9cp-1 },
  { 0x1.ddddddddddddep-1, 0x1.ddddddddddddep-1, 0x1.ddddddddddddep-1 },
};

const LabColor      ansi_to_lab_map[] = {
  { 0x0p+0,               0x0p+0,                0x0p+0                },
  { 0x1.dda5cfe092fep+2,  0x1.332b010968089p+5,  -0x1.a2c4a323ffe92p+5 },
  { 0x1.c397c39a77298p+3, 0x1.8af9b447e90cbp+5,  -0x1.0cf90bbbcc5d8p+6 },
  { 0x1.46bc599921d96p+4, 0x1.ddb9a68684777p+5,  -0x1.455305d0721ddp+6 },
  { 0x1.a7753afb0c288p+4, 0x1.168246e235f69p+6,  -0x1.7b524c263d3c5p+6 },
  { 0x1.026bb28f00565p+5, 0x1.3cc961b545d39p+6,  -0x1.af7468cdc8f89p+6 },
  { 0x1.12e98f89bd91ap+5, -0x1.4ebd3dce7c755p+5, 0x1.4312e4fa25574p+5  },
  { 0x1.2009c797b7857p+5, -0x1.757af85ad7747p+4, -0x1.b74c22df6c479p+2 },
  { 0x1.2dc90429e2694p+5, -0x1.08c0c16763d57p+3, -0x1.cd7b32157f93p+4  },
  { 0x1.40610faffe6bcp+5, 0x1.01e7f81ac5244p+3,  -0x1.88aa2fa146942p+5 },
  { 0x1.5732683d19afap+5, 0x1.83e40beb7723cp+4,  -0x1.0eafa1c959f9dp+6 },
  { 0x1.717733050e939p+5, 0x1.3cfe271199bb8p+5,  -0x1.535dd14bf0b8cp+6 },
  { 0x1.855d6d6a40a9p+5,  -0x1.add38b8613d0cp+5, 0x1.9ed8e2f116c31p+5  },
  { 0x1.8d75e59400632p+5, -0x1.4bba60255029fp+5, 0x1.9bc9967cd9197p+3  },
  { 0x1.9638294461624p+5, -0x1.df92894b46482p+4, -0x1.1a0af7469b5d8p+3 },
  { 0x1.a27f7405620dep+5, -0x1.01478b3274c31p+4, -0x1.dac7c4ff6005cp+4 },
  { 0x1.b23282428246cp+5, -0x1.f2d6f92dec4b8p-1, -0x1.8ad27e9c4b235p+5 },
  { 0x1.c50eeb87d4546p+5, 0x1.ce5dd04eb088cp+3,  -0x1.0f54864f329cdp+6 },
  { 0x1.f1c1903bfbec6p+5, -0x1.03f0560740925p+6, 0x1.f5c2a0ffa4a01p+5  },
  { 0x1.f753cab4ad698p+5, -0x1.c2309c6e6fba8p+5, 0x1.e8ceb271c3264p+4  },
  { 0x1.fd6ff32d2df16p+5, -0x1.7c3e453198d85p+5, 0x1.3f8bed172d435p+3  },
  { 0x1.0312215c176e5p+6, -0x1.2205dc84fb2c5p+5, -0x1.5521ef09fe8f4p+3 },
  { 0x1.08bfa717bf7b1p+6, -0x1.72bdd60906ad5p+4, -0x1.eaa5b3f1c5bcap+4 },
  { 0x1.0fba6810d9114p+6, -0x1.2057de437af8p+3,  -0x1.8e651109759fp+5  },
  { 0x1.2ccf34ac5943ap+6, -0x1.2f1554f71e01cp+6, 0x1.24856676735f7p+6  },
  { 0x1.2edd7502954e5p+6, -0x1.14f39abdb9908p+6, 0x1.7350060372405p+5  },
  { 0x1.31227cf8c1bffp+6, -0x1.f37ae7f7da308p+5, 0x1.b5b001a38e9a7p+4  },
  { 0x1.3465164b9d9b7p+6, -0x1.aa81d1c22e374p+5, 0x1.da3b821a184dp+2   },
  { 0x1.38b1a71a3a50bp+6, -0x1.52292711232edp+5, -0x1.8dc0e9abb70bap+3 },
  { 0x1.3e0c0c670b182p+6, -0x1.dcb5a9eb58becp+4, -0x1.fc03f8442a0aap+4 },
  { 0x1.5ef2b8e723b8p+6,  -0x1.58bd11599bcb3p+6, 0x1.4cb983406b967p+6  },
  { 0x1.608a367f8eecep+6, -0x1.4451a3e930c1dp+6, 0x1.e643f64b1c0ecp+5  },
  { 0x1.624dcdb99d1afp+6, -0x1.2e98571e94c0ep+6, 0x1.5aee6a104dce3p+5  },
  { 0x1.64d98317145a2p+6, -0x1.10c1c216b9872p+6, 0x1.86783bc59c071p+4  },
  { 0x1.683a43eead4dp+6,  -0x1.d72ffe6847074p+5, 0x1.4324b8231e205p+2  },
  { 0x1.6c77514f49c19p+6, -0x1.80a30f01a4e1cp+5, -0x1.c46b8ae5b77d4p+3 },
  { 0x1.19cc4790ee3c8p+4, 0x1.37248dcb41bap+5,   0x1.b35039f691ae1p+4  },
  { 0x1.50d991452d17ep+4, 0x1.7d9e01cc7eb95p+5,  -0x1.d8a02833685f9p+4 },
  { 0x1.843c70971f92ap+4, 0x1.b8f531ceeec11p+5,  -0x1.90f305cec303cp+5 },
  { 0x1.c306862ec6c1cp+4, 0x1.fc111bc61cb0fp+5,  -0x1.10ca766b37931p+6 },
  { 0x1.0489187e0f4c2p+5, 0x1.212919370bc77p+6,  -0x1.52031b9e5953ep+6 },
  { 0x1.29b26a13ad27dp+5, 0x1.44ae19d6f2ad8p+6,  -0x1.8e3008e3c1f11p+6 },
  { 0x1.376d2bf64d80dp+5, -0x1.4ee40413cd236p+3, 0x1.6ef7c7668ebacp+5  },
  { 0x1.428a9ba704e27p+5, 0x1.4ec09decddp-9,     -0x1.4b29b3dcafep-8   },
  { 0x1.4e57e1ac378c4p+5, 0x1.371c696f1521fp+3,  -0x1.630f61ebd8c98p+4 },
  { 0x1.5e8aaae1c84bdp+5, 0x1.55dda009f88bfp+4,  -0x1.56b1e2393eaa8p+5 },
  { 0x1.72bed186a2778p+5, 0x1.0f5e41d64f517p+5,  -0x1.ef6259bae08ep+5  },
  { 0x1.8a62b14f3654ep+5, 0x1.754e7e7e72468p+5,  -0x1.3e784efa4fee7p+6 },
  { 0x1.9c869d394a744p+5, -0x1.f1be4ea568e1dp+4, 0x1.bae9e257af934p+5  },
  { 0x1.a3f4e08d7ddc6p+5, -0x1.65d7aa5ba22c9p+4, 0x1.12ec0fa7c48cdp+4  },
  { 0x1.ac06cc1c1535ap+5, -0x1.b81284cc15p+3,    -0x1.1dc45d49fe653p+2 },
  { 0x1.b763b729eac8p+5,  -0x1.6d51bff9b9955p+1, -0x1.96b6c6a4553acp+4 },
  { 0x1.c5ff48f904b5cp+5, 0x1.31044222b3e09p+3,  -0x1.6a2bcfa96345p+5  },
  { 0x1.d7a718ba2e08cp+5, 0x1.6ae5d4814dad9p+4,  -0x1.ffc2d6c1f55d8p+5 },
  { 0x1.00f1ad4294f38p+6, -0x1.81a52ad985c29p+5, 0x1.04b02a3755d04p+6  },
  { 0x1.0397d60eff8d8p+6, -0x1.495e70fcc947fp+5, 0x1.0be09cc2771a3p+5  },
  { 0x1.06809111feea2p+6, -0x1.0fb0a6f83f098p+5, 0x1.a044aa70ea792p+3  },
  { 0x1.0aa73acf84e55p+6, -0x1.875bad06ed5b4p+4, -0x1.e8793f013b9efp+2 },
  { 0x1.1014754ae2d4fp+6, -0x1.a5d2266c4d5fcp+3, -0x1.baff268236a02p+4 },
  { 0x1.16c45fcdfbe5ap+6, -0x1.65733a23b2868p-1, -0x1.7743f8aa8d07ap+5 },
  { 0x1.32cc3fec1d67fp+6, -0x1.f710c8f971d0cp+5, 0x1.2bd0bd8086238p+6  },
  { 0x1.34c9c6aa9b806p+6, -0x1.c9c715ebfddb1p+5, 0x1.84488966622fp+5   },
  { 0x1.36fca6f7d1185p+6, -0x1.9a288f3969fc4p+5, 0x1.d912de3824548p+4  },
  { 0x1.3a25bad5c1fc2p+6, -0x1.599f4a55707cp+5,  0x1.3516957ef034ap+3  },
  { 0x1.3e519c95dc3abp+6, -0x1.0a85f7d64c69ep+5, -0x1.45d4328afeb8ep+3 },
  { 0x1.4384c9bb5fd7fp+6, -0x1.600695d242e6dp+4, -0x1.d88584a8c6a26p+4 },
  { 0x1.6399d25b046cap+6, -0x1.2fe250a4f791bp+6, 0x1.5265bd14d70bfp+6  },
  { 0x1.65286024b415cp+6, -0x1.1d6c72d5b632cp+6, 0x1.f32176157706ap+5  },
  { 0x1.66e22d97f1ff2p+6, -0x1.09aff6996ca48p+6, 0x1.686b8f6f2abe3p+5  },
  { 0x1.695ff8b2c97c9p+6, -0x1.dcd9ae7850af8p+5, 0x1.a22bf8a61254dp+4  },
  { 0x1.6caea2d7e14f1p+6, -0x1.9879927754eb6p+5, 0x1.b316c55603476p+2  },
  { 0x1.70d594239a6bcp+6, -0x1.484103309e75fp+5, -0x1.8c8b6fd3539f8p+3 },
  { 0x1.b2910e3fe3b4p+4,  0x1.8f86eb80042cep+5,  0x1.411e9daa89eb7p+5  },
  { 0x1.d5acb747eaa5cp+4, 0x1.bde4ac00dfd6bp+5,  -0x1.fd3a7027e078ep+3 },
  { 0x1.f941baadd31b8p+4, 0x1.ea05499949889p+5,  -0x1.2f70cb12a6f2cp+5 },
  { 0x1.13ebca368e98cp+5, 0x1.1039f1a8c9b78p+6,  -0x1.ccfc348248b7bp+5 },
  { 0x1.2f8f1ec81cefap+5, 0x1.2eaac109f69e4p+6,  -0x1.2dc69b3dcfca4p+6 },
  { 0x1.4e65a3c2610b1p+5, 0x1.4ee29ac24c2fdp+6,  -0x1.6f35a9a7e5fep+6  },
  { 0x1.5a1d13ce97263p+5, 0x1.2456484b998d6p+3,  0x1.97784cb564c2bp+5  },
  { 0x1.63b5adf39fe61p+5, 0x1.0508a6762423cp+4,  0x1.a06be1e915902p+2  },
  { 0x1.6dffa74059836p+5, 0x1.760f8519e659cp+4,  -0x1.f8caa967c442p+3  },
  { 0x1.7c46240502887p+5, 0x1.0279340fd4267p+5,  -0x1.25b25c47789adp+5 },
  { 0x1.8e4d867e0249cp+5, 0x1.53a3d1753cf28p+5,  -0x1.c18dbf293b2aep+5 },
  { 0x1.a3acb9ae1e612p+5, 0x1.a9e468c76ae54p+5,  -0x1.29529d4179d17p+6 },
  { 0x1.b44059fd54924p+5, -0x1.ae05557bcb772p+3, 0x1.d735c1dbee816p+5  },
  { 0x1.bb14dce60dd4ap+5, -0x1.b1174a1d8099ap+2, 0x1.593942e0bb025p+4  },
  { 0x1.c2861260c65f8p+5, 0x1.add7e11b5f4p-9,    -0x1.a93bef691c4p-8   },
  { 0x1.cd0b2b20d57cap+5, 0x1.1a9c515bdf62dp+3,  -0x1.5077e4af0d296p+4 },
  { 0x1.daa210e1f3c76p+5, 0x1.3302420ac4032p+4,  -0x1.483fc6c1ef988p+5 },
  { 0x1.eb25e43dc143p+5,  0x1.e84e8ffcac374p+4,  -0x1.df7149a4547c6p+5 },
  { 0x1.0980248ba3eedp+6, -0x1.0ab43e5928943p+5, 0x1.0efe482594576p+6  },
  { 0x1.0c03efff02d02p+6, -0x1.b870babc2016p+4,  0x1.24a36befdf12ep+5  },
  { 0x1.0ec7d4a48e51p+6,  -0x1.57b15a75aa304p+4, 0x1.03511272a69dep+4  },
  { 0x1.12bb813205c3fp+6, -0x1.ac2e388867b72p+3, -0x1.1ab8d855ced81p+2 },
  { 0x1.17e8bdde08961p+6, -0x1.cb2f17fa7b1a2p+1, -0x1.883ee20dfc676p+4 },
  { 0x1.1e4db845bbcap+6,  0x1.dd42c234f61ccp+2,  -0x1.5e8d6c2ab86d4p+5 },
  { 0x1.39445f972d36ep+6, -0x1.94b4790e54887p+5, 0x1.33a56fc2d3f2p+6   },
  { 0x1.3b30b53b9cb22p+6, -0x1.6d388af9cbb64p+5, 0x1.9688390182453p+5  },
  { 0x1.3d50e580edd7dp+6, -0x1.435ec98c842c3p+5, 0x1.ff3180051477p+4   },
  { 0x1.405fa89033789p+6, -0x1.0a2325aac2b56p+5, 0x1.82c1d1e57da21p+3  },
  { 0x1.4469c310bf131p+6, -0x1.8679a3d442045p+4, -0x1.f027fc8d1550bp+2 },
  { 0x1.49744abd0a0e1p+6, -0x1.c4b62e6666079p+3, -0x1.b21647e2eedd9p+4 },
  { 0x1.68ae005b36ca2p+6, -0x1.0717d068dbe9p+6,  0x1.58901f51d8a32p+6  },
  { 0x1.6a332163525b2p+6, -0x1.ecce5637e5042p+5, 0x1.008fc8b33fba6p+6  },
  { 0x1.6be29a70abd2p+6,  -0x1.c8f624db6f706p+5, 0x1.771b1f25cd6c6p+5  },
  { 0x1.6e51b30bd48f9p+6, -0x1.97318df6608a5p+5, 0x1.c05d4033738f2p+4  },
  { 0x1.718d3ca7adc43p+6, -0x1.5863871435014p+5, 0x1.169cbd2f13a2ep+3  },
  { 0x1.759cc479d3c8ap+6, -0x1.0e2f1446a4424p+5, -0x1.4f858136af9dp+3  },
  { 0x1.219f4f1994dc9p+5, 0x1.e33afc70025e2p+5,  0x1.94ac9a6aec282p+5  },
  { 0x1.2de0fe3cb9c2bp+5, 0x1.02090204ef69dp+6,  -0x1.3981ee5161d7cp+1 },
  { 0x1.3acb1086611b6p+5, 0x1.12a8821ccb01fp+6,  -0x1.924437c1c5194p+4 },
  { 0x1.4c5f54092d8e3p+5, 0x1.28576ceab1685p+6,  -0x1.6f036657c191fp+5 },
  { 0x1.621882a17e702p+5, 0x1.41e5906b3d35ep+6,  -0x1.037310916b8ep+6  },
  { 0x1.7b46e6eaad158p+5, 0x1.5e25a11c26cd1p+6,  -0x1.497af68c3b8afp+6 },
  { 0x1.85120cf60962cp+5, 0x1.b55852773289cp+4,  0x1.c8479dc3861bdp+5  },
  { 0x1.8d2cd39dae2d2p+5, 0x1.02cfece8d7e04p+5,  0x1.d0f0755ce5a5cp+3  },
  { 0x1.95f17824ac562p+5, 0x1.2bec94166d343p+5,  -0x1.f02e77a7def96p+2 },
  { 0x1.a23be78c68f8cp+5, 0x1.62123574b562dp+5,  -0x1.cf11b542b28adp+4 },
  { 0x1.b1f2aebc13548p+5, 0x1.a2553c0052d9cp+5,  -0x1.868ac81d3b03ap+5 },
  { 0x1.c4d32c2e81b0ep+5, 0x1.e9881d5b27ea8p+5,  -0x1.0db23d570afacp+6 },
  { 0x1.d3a21929fc91ep+5, 0x1.44b691a97ccc7p+2,  0x1.fbfe74cc91416p+5  },
  { 0x1.d9c606fab8d04p+5, 0x1.424fa2e417982p+3,  0x1.b57cf757b1bbap+4  },
  { 0x1.e07d0e08cfbbcp+5, 0x1.e8af36cbb2af2p+3,  0x1.78c8cf7b9d624p+2  },
  { 0x1.ea058ac4cf652p+5, 0x1.63b6777835e0fp+4,  -0x1.e5edf8c473d06p+3 },
  { 0x1.f66762c127222p+5, 0x1.ea46667026dbbp+4,  -0x1.1ac70581d3882p+5 },
  { 0x1.02c5f44ff34edp+6, 0x1.40fa4ea50d112p+5,  -0x1.b3cf8edb9454fp+5 },
  { 0x1.153b965155ffbp+6, -0x1.040e722fdba92p+4, 0x1.1cf737fa0ee7fp+6  },
  { 0x1.1794536372663p+6, -0x1.732d0e22d1d7ap+3, 0x1.4659084022977p+5  },
  { 0x1.1a29e6b65a642p+6, -0x1.abdd876e9fd4bp+2, 0x1.4943bacd56fcfp+4  },
  { 0x1.1ddd2f9105f37p+6, 0x1.03f2f50d57ep-8,    -0x1.012961e36fcp-7   },
  { 0x1.22b92898f142bp+6, 0x1.07d66af5e4b93p+3,  -0x1.4261a0d565d1cp+4 },
  { 0x1.28be54abbdd1bp+6, 0x1.1b9ab93e72c98p+4,  -0x1.3c686ff4124b6p+5 },
  { 0x1.4251e86d5e6e4p+6, -0x1.1c21fe72b171ep+5, 0x1.3e8599b2f8b3fp+6  },
  { 0x1.44279a101b809p+6, -0x1.f5922fee6834bp+4, 0x1.afebc31e8182ep+5  },
  { 0x1.462f23ec0477ap+6, -0x1.ae48001a1864ep+4, 0x1.1a2bd15f94d95p+5  },
  { 0x1.491b1ef2f3fe2p+6, -0x1.4bd6667828dcbp+4, 0x1.ef477289d8a2p+3   },
  { 0x1.4cf87604c04d6p+6, -0x1.a0e4950f196d2p+3, -0x1.166fd76551f95p+2 },
  { 0x1.51ccf33c361d8p+6, -0x1.fe3a50217e42cp+1, -0x1.7c2a34b82d74bp+4 },
  { 0x1.6fdfced243074p+6, -0x1.a5a2d40abd7cap+5, 0x1.61401a04f0ae2p+6  },
  { 0x1.7158255848c86p+6, -0x1.884f43207de8ap+5, 0x1.0a6d5bf46a657p+6  },
  { 0x1.72f996a4ba44bp+6, -0x1.68a902cb7c848p+5, 0x1.8bd71101170c3p+5  },
  { 0x1.7554b3adca6dfp+6, -0x1.3c74d8894ced8p+5, 0x1.eb0c34fa4f349p+4  },
  { 0x1.787632d218b91p+6, -0x1.0443086302fbp+5,  0x1.6d0de862336aap+3  },
  { 0x1.7c65cce3ed22ap+6, -0x1.829f029f6516cp+4, -0x1.f2122869b64c1p+2 },
  { 0x1.66f0651b823a8p+5, 0x1.19b7e7b4733d5p+6,  0x1.d8c83fbb451e4p+5  },
  { 0x1.700cd561c6bbbp+5, 0x1.2603d401c798dp+6,  0x1.509597e494607p+3  },
  { 0x1.79d92a2b94c3bp+5, 0x1.32e393a638727p+6,  -0x1.8b9898753524fp+3 },
  { 0x1.877d1eafcd45p+5,  0x1.4445d0983a9ap+6,   -0x1.0d93af6e749f8p+5 },
  { 0x1.98c8e5a971f4cp+5, 0x1.598732fa86a29p+6,  -0x1.abee1203a068cp+5 },
  { 0x1.ad603024ee8a4p+5, 0x1.71dbaf44da945p+6,  -0x1.1f94897e4944ep+6 },
  { 0x1.b58695d3fc9f2p+5, 0x1.5c72629e0cf6dp+5,  0x1.fde150be352cbp+5  },
  { 0x1.bc535d7f51226p+5, 0x1.79a0d04632cccp+5,  0x1.77cd19869c4c6p+4  },
  { 0x1.c3bc753f143aep+5, 0x1.984f12d84ddc6p+5,  0x1.55d98e1e316ap+0   },
  { 0x1.ce36999ca094p+5,  0x1.c1e41b21c2ad8p+5,  -0x1.403405dc50cf4p+4 },
  { 0x1.dbc02ece420a4p+5, 0x1.f4e0dcb2281cp+5,   -0x1.41bee0df4f9b2p+5 },
  { 0x1.ec34fccead87p+5,  0x1.17a5936c2b913p+6,  -0x1.da0b94ca9b7dcp+5 },
  { 0x1.f940842a40888p+5, 0x1.6dcd92bddf1cp+4,   0x1.139cf451a2a17p+6  },
  { 0x1.feb19c17ed2cp+5,  0x1.aa3723cb845f5p+4,  0x1.11715711fef5cp+5  },
  { 0x1.02553285124cep+6, 0x1.ea37734f72b07p+4,  0x1.9dd92347b616p+3   },
  { 0x1.0696fe805d1e6p+6, 0x1.20d85c1d631f5p+5,  -0x1.04a1e76a185cep+3 },
  { 0x1.0c2624c8de5a8p+6, 0x1.56fd766400d1ap+5,  -0x1.c722a6454145cp+4 },
  { 0x1.12fd99d01ff6p+6,  0x1.959f99d446584p+5,  -0x1.7e6a5a8a9c775p+5 },
  { 0x1.23d9666bd0659p+6, 0x1.6e1447a5d0a5p+0,   0x1.2e22a12e66d74p+6  },
  { 0x1.26023f50e2504p+6, 0x1.47bb2a2e2936dp+2,  0x1.6ff17ac5f47bp+5   },
  { 0x1.2864189a9266ap+6, 0x1.2213582ff71efp+3,  0x1.9ffb26835731ap+4  },
  { 0x1.2bcf1d5c0332p+6,  0x1.d04d1727d4e0ap+3,  0x1.5ef00b404fc18p+2  },
  { 0x1.304f4a676d83bp+6, 0x1.554b1d7c7bb4ep+4,  -0x1.d6015e76ba7bdp+3 },
  { 0x1.35e764c918f3bp+6, 0x1.d5329d1d007d3p+4,  -0x1.11844bf61c351p+5 },
  { 0x1.4dded2fbabfd3p+6, -0x1.2f3870852f8f6p+4, 0x1.4c43a02deb2e4p+6  },
  { 0x1.4f99d1d82b9ap+6,  -0x1.efc84247aa3cep+3, 0x1.d0100f174e1a2p+5  },
  { 0x1.51843bdcdf3a8p+6, -0x1.78936757be123p+3, 0x1.3be7d553a1bd9p+5  },
  { 0x1.5447050d71fb6p+6, -0x1.a4e671d256bfcp+2, 0x1.3cb4fa6a24975p+4  },
  { 0x1.57ef2bbdb7d2fp+6, 0x1.2f18635d83p-8,     -0x1.2bd85fde5b2p-7   },
  { 0x1.5c8330dff3ea3p+6, 0x1.f47b83f85e7c5p+2,  -0x1.372c56784928cp+4 },
  { 0x1.79316dced5917p+6, -0x1.2d5e93659c6a9p+5, 0x1.6c6c966d9180ep+6  },
  { 0x1.7a9a1cda7ce87p+6, -0x1.141d18c258885p+5, 0x1.172085fafa629p+6  },
  { 0x1.7c2a5dfcc4d0ap+6, -0x1.f1713c692f4ebp+4, 0x1.a692d79abeb0ep+5  },
  { 0x1.7e6cf816c4592p+6, -0x1.a477aad422013p+4, 0x1.111680251dadbp+5  },
  { 0x1.816e77e2eb063p+6, -0x1.41defe389a70ap+4, 0x1.dce2865bca1f2p+3  },
  { 0x1.8536c0fa71531p+6, -0x1.96be52b0156c2p+3, -0x1.11ef5946b555dp+2 },
  { 0x1.a9dcf12030382p+5, 0x1.406feed65ee84p+6,  0x1.0ce159964de25p+6  },
  { 0x1.b0f26bc69dab6p+5, 0x1.4a09c81c11fd2p+6,  0x1.6e6afd903b9ecp+4  },
  { 0x1.b8a7b324f88dap+5, 0x1.544a38be49575p+6,  0x1.3b84335cbedcp-3   },
  { 0x1.c38876d93f6dcp+5, 0x1.627023ba4e7bap+6,  -0x1.5778f07ca0c6cp+4 },
  { 0x1.d18e7694ec3bep+5, 0x1.742d5ebb5f703p+6,  -0x1.4e44b402f3a1ap+5 },
  { 0x1.e28f396180c46p+5, 0x1.890451e73c603p+6,  -0x1.e6be6e834442cp+5 },
  { 0x1.e95ff95009d8cp+5, 0x1.d0232439e02cap+5,  0x1.1af1891fd7ef7p+6  },
  { 0x1.ef18a82d519eep+5, 0x1.e63d636bcfbdep+5,  0x1.0776db7950e9ep+5  },
  { 0x1.f55dcbfbc7f52p+5, 0x1.fde0a93bd6868p+5,  0x1.618907bb4ce3dp+3  },
  { 0x1.fe4a6e7d8c7dap+5, 0x1.0f45d8a8b7a96p+6,  -0x1.4b192f358b064p+3 },
  { 0x1.04f5c28c0b1d4p+6, 0x1.23c653c5fcc8cp+6,  -0x1.ec9d40a2aeee6p+4 },
  { 0x1.0c1915cafae53p+6, 0x1.3bdd8430f6e8bp+6,  -0x1.91738024cbe79p+5 },
  { 0x1.11ce91ea07eadp+6, 0x1.3ad24501a84a3p+5,  0x1.2b772eb2f1968p+6  },
  { 0x1.14336d3bbdec7p+6, 0x1.521ae321bf067p+5,  0x1.4e2f7c3a31134p+5  },
  { 0x1.16d60e7048894p+6, 0x1.6b19a7400b74p+5,   0x1.4d2d0bb893dc1p+4  },
  { 0x1.1a9b8500b8437p+6, 0x1.8dcae444139d1p+5,  -0x1.92378193aa8ep-3  },
  { 0x1.1f8e7c63a4a0fp+6, 0x1.b98e7005d0886p+5,  -0x1.497e9726b3795p+4 },
  { 0x1.25aed695e76d6p+6, 0x1.ed40235375cb5p+5,  -0x1.412cc6fa4e792p+5 },
  { 0x1.34ee88b64c0b5p+6, 0x1.2b7b7a92c1505p+4,  0x1.41e539eba0d4ep+6  },
  { 0x1.36e64ab660fedp+6, 0x1.5a7b2b54f85edp+4,  0x1.9ffb02a68bc4ap+5  },
  { 0x1.3912e6874751dp+6, 0x1.8d2fd8c3f4408p+4,  0x1.0252fdc0c15ecp+5  },
  { 0x1.3c33284a205fep+6, 0x1.d3fa74ad70819p+4,  0x1.7c7994333c5d2p+3  },
  { 0x1.4053b9cc9b87dp+6, 0x1.16f6b2461981p+5,   -0x1.0924ac75f6991p+3 },
  { 0x1.45794d18fad07p+6, 0x1.4c8443227d63p+5,   -0x1.bdfe026858d52p+4 },
  { 0x1.5bb6dee96dd96p+6, -0x1.ec995a199711cp+0, 0x1.5c8c730b29d6fp+6  },
  { 0x1.5d54c00eb0a74p+6, 0x1.da3cdb28ab538p-1,  0x1.f63701925d4f3p+5  },
  { 0x1.5f1f55a6742a9p+6, 0x1.011d2430c75abp+2,  0x1.6412e78096a78p+5  },
  { 0x1.61b4fa6d4d49bp+6, 0x1.0b832e6df2ebap+3,  0x1.8f35383638231p+4  },
  { 0x1.6522a2621b028p+6, 0x1.bd74207229927p+3,  0x1.4c50c54f93f5fp+2  },
  { 0x1.696f705aa0f7ep+6, 0x1.499fca4fe2d71p+4,  -0x1.c8887f9b9a999p+3 },
  { 0x1.848d909dddc53p+6, -0x1.58e500235adb1p+4, 0x1.79ee10aa351a3p+6  },
  { 0x1.85e472c92dca2p+6, -0x1.2de3a6e1c1964p+4, 0x1.267d4ab7db6d9p+6  },
  { 0x1.876122b64ff4ap+6, -0x1.fe1047c9a5e32p+3, 0x1.c6f8ee5266cfp+5   },
  { 0x1.8987cad7d41e9p+6, -0x1.79a8609757e14p+3, 0x1.328fe8f5dcb2ep+5  },
  { 0x1.8c64bd43f99ep+6,  -0x1.9db28b5d31193p+2, 0x1.327ba5a0e89c8p+4  },
  { 0x1.9p+6,             0x1.58c08b4812p-8,     -0x1.550e2e12c9p-7    },
  { 0x1.18c1475ead608p+1, 0x1.38e7a41daep-12,    -0x1.358ffd659fp-11   },
  { 0x1.5db059401c66cp+2, 0x1.85bb83b5e08p-11,   -0x1.8191c660b28p-10  },
  { 0x1.4894f743c1136p+3, 0x1.3846bad8df8p-10,   -0x1.34ed838784cp-9   },
  { 0x1.e51c6d63f5948p+3, 0x1.726d487fee4p-10,   -0x1.6e7470c0248p-9   },
  { 0x1.3dd939aba81f4p+4, 0x1.aa5e9f3e04p-10,    -0x1.a5cc369b984p-9   },
  { 0x1.86bdb9f10d082p+4, 0x1.e087611e198p-10,   -0x1.db604cf0774p-9   },
  { 0x1.cda16468c830cp+4, 0x1.0a998ccd75ep-9,    -0x1.07bdb7ece64p-8   },
  { 0x1.09675debffa7cp+5, 0x1.244c92a1f28p-9,    -0x1.212a31f726p-8    },
  { 0x1.2b3f437384df8p+5, 0x1.3d71d9acf42p-9,    -0x1.3a0a725147ap-8   },
  { 0x1.4c6eae41c4c21p+5, 0x1.5619f294508p-9,    -0x1.526edc2832cp-8   },
  { 0x1.6d078e2b867f7p+5, 0x1.6e5231134ap-9,     -0x1.6a649ea1d4cp-8   },
  { 0x1.8d189afdd0604p+5, 0x1.862584a4138p-9,    -0x1.81f68b339c8p-8   },
  { 0x1.acae1b886649ap+5, 0x1.9d9d0c62e24p-9,    -0x1.992da7efaap-8    },
  { 0x1.cbd271f0f75acp+5, 0x1.b4c07f508acp-9,    -0x1.b01196a97b4p-8   },
  { 0x1.ea8e815be51fap+5, 0x1.cb9677db8ap-9,     -0x1.c6a8dfaf2bcp-8   },
  { 0x1.0474fca6ae9bp+6,  0x1.e224abe18bcp-9,    -0x1.dcf92931514p-8   },
  { 0x1.1375c7581a1d2p+6, 0x1.f870170dbacp-9,    -0x1.f307612d9f8p-8   },
  { 0x1.224c93dede69ep+6, 0x1.073e8dbc768p-8,    -0x1.046beeda534p-7   },
  { 0x1.30fbff2913ff8p+6, 0x1.1227cd95a6cp-8,    -0x1.0f373b12cb4p-7   },
  { 0x1.3f865d917b1dap+6, 0x1.1cf58629b46p-8,    -0x1.19e74b9748p-7    },
  { 0x1.4dedc5caa1dfap+6, 0x1.27a944c06b4p-8,    -0x1.247da96d0e6p-7   },
  { 0x1.5c3419babd9a4p+6, 0x1.32446f66ed6p-8,    -0x1.2efbb6ca5dap-7   },
  { 0x1.6a5b0dbe1d206p+6, 0x1.3cc84a548eep-8,    -0x1.3962b46c7fep-7   },
  { 0x1.78642ea7f55e1p+6, 0x1.4735fc607fap-8,    -0x1.43b3c60170cp-7   },
};


static inline RGBColor ansi_to_rgb(int ansi_num) {
  return(ansi_to_rgb_map[ansi_num - ANSI_MAP_OFFSET]);
}


static inline LabColor ansi_to_lab(int ansi_num) {
  return(ansi_to_lab_map[ansi_num - ANSI_MAP_OFFSET]);
}
