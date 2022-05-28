#pragma once
#include <assert.h>
#include <ctype.h>
#include <dirent.h>
#include <err.h>
#include <errno.h>
#include <getopt.h>
#include <glob.h>
#include <inttypes.h>
#include <libgen.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sysexits.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>
#include <wchar.h>
#include <wctype.h>

//////////////////////////////////////////////////////////

#define SEQUENCE    "printf \"\
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

#define PALETTE     "\
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
typedef struct ColorInfo   ColorInfo;
typedef struct Ansi_t      Ansi_t;
typedef struct CSEQ        CSEQ;
typedef struct SEQ         SEQ;
struct Ansi_t {
  const char *fg;
  const char *bg;
};
typedef struct RGB_t       RGB_t;
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
//////////////////////////////////////////////////////////
typedef struct { double L;   double a;   double b; }        LabColor;
typedef struct { double L;   double C;   double h; }        LChColor;
typedef struct { double r;   double g;    double b; }       RGBColor;
typedef struct { double rl;    double gl;    double bl; }   SRGBColor;
typedef struct { double x;    double y;   double z; }       XYZColor;
//////////////////////////////////////////////////////////
void print_ansi_color(int red, int green, int blue, int wl, char *word);
void print_ansi_to_rgb(int ansi_code);

//////////////////////////////////////////////////////////
void ansi_256_fg(FILE *file, int color);
void ansi_256_bg(FILE *file, int color);
void ansi_truecolor_fg(FILE *file, int r, int g, int b);
void ansi_truecolor_bg(FILE *file, int r, int g, int b);
void ansi_reset(FILE *file);

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

bool is_in_rgb_range(struct RGB rgb);
float get_rgb_min(struct RGB rgb);
float get_rgb_max(struct RGB rgb);
float get_rgb_range(struct RGB rgb);

float rgb_to_hue(struct RGB rgb);

float rgb_to_hsl_luminance(struct RGB rgb);
float rgb_to_hsl_saturation(struct RGB rgb);

float rgb_to_hsv_value(struct RGB rgb);
float rgb_to_hsv_saturation(struct RGB rgb);

//////////////////////////////////////////////////////////

