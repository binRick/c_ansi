#pragma once
#include "ansi-utils/ansi-utils.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

TerminalCapabilities_t TerminalCapabilities = {
  .RestorePalette            = false,
  .AltScreenInitiallyEnabled = false,
  .IsTTY                     = false,
};
static void await_c1(unsigned char c1);
static char *read_csi();
static bool query_dec_mode(int mode);
static void do_dec_mode(int mode, BoolQuery val, const char *name);


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



void restoreicanon(void){
  seticanon(TerminalCapabilities.Wasicanon, true);
}


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

  fprintf(stderr,
          "number of rows: %i, number of columns: %i, screen width: %i, screen height: %i\n",
          ws.ws_row, ws.ws_col, ws.ws_xpixel, ws.ws_ypixel
          );

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


static void do_dec_mode(int mode, BoolQuery val, const char *name){
  if (query_dec_mode(mode)) {
    printf("%s on\n", name);
  }else{
    printf("%s off\n", name);
  }
}


bool seticanon(bool icanon, bool echo){
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

#include "ansi-utils.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

char *random_rgb() {
  struct timeval tv;
  gettimeofday(&tv, NULL);  // should not fail
  unsigned int seed = (unsigned int)tv.tv_sec + (unsigned int)(1000 * tv.tv_usec);
  srand(seed);

  float hue = rand() % 360;  // range [0, 360)
  const float saturation = 0.5f;  // range [0, 1]
  const float value = 0.95f;  // range [0, 1]

	float fC = value * saturation;  // Chroma
  float fHPrime = fmod(hue / 60.0, 6);
  float fX = fC * (1 - fabs(fmod(fHPrime, 2) - 1));
  float fM = value - fC;

  float fR, fG, fB;
  if (0 <= fHPrime && fHPrime < 1) {
    fR = fC;
    fG = fX;
    fB = 0;
  } else if (1 <= fHPrime && fHPrime < 2) {
    fR = fX;
    fG = fC;
    fB = 0;
  } else if (2 <= fHPrime && fHPrime < 3) {
    fR = 0;
    fG = fC;
    fB = fX;
  } else if (3 <= fHPrime && fHPrime < 4) {
    fR = 0;
    fG = fX;
    fB = fC;
  } else if (4 <= fHPrime && fHPrime < 5) {
    fR = fX;
    fG = 0;
    fB = fC;
  } else if (5 <= fHPrime && fHPrime < 6) {
    fR = fC;
    fG = 0;
    fB = fX;
  } else {
    fR = 0;
    fG = 0;
    fB = 0;
  }

  fR += fM;
  fG += fM;
  fB += fM;

  int r = 255 * fR;
  int g = 255 * fG;
  int b = 255 * fB;

  char s[256];
  sprintf(s,"\x1b[38;2;%d;%d;%dm[%d/%d/%d]",r,g,b,r,g,b);
  return(strdup(s));
}









// lookup table of nice bright colors
static float colors[8*8*8][4];

static void RGBfromHSV( double hue, double saturation, double value, float rgb[3] )
{
  int hi = floor(hue * 6.0);
  float f = hue*6.0 - hi; 
  float v = value;
  float p = value * (1.0 - saturation);
  float q = value * (1.0 - f * saturation);
  float t = value * (1.0 - (1 - f) * saturation);

  switch( hi )
    {
    case 0:
      rgb[0] = v;
      rgb[1] = t;
      rgb[2] = p;
      break;
    case 1:
      rgb[0] = q;
      rgb[1] = v;
      rgb[2] = p;
      break;
    case 2:
      rgb[0] = p;
      rgb[1] = v;
      rgb[2] = t;
      break;
    case 3:
      rgb[0] = p;
      rgb[1] = q;
      rgb[2] = v;
      break;
    case 4:
      rgb[0] = t;
      rgb[1] = p;
      rgb[2] = v;
      break;
    default:
      rgb[0] = v;
      rgb[1] = p;
      rgb[2] = q;
    }
}

/* Initialize a table of nice bright usable unique colors. Parameter
   @alpha sets the alpha channel density (transparency) for all
   colors. */
void bright_color_init( float alpha )
{
  double h = drand48(); // # use random start value

  // a table of nice bright colors
   int num = 8;
  for(  int i=0; i<num; i++ )
    for(  int j=0; j<num; j++ )
      for(  int k=0; k<num; k++ )
	{
	  h += 1.0 / BRIGHT_COLOR_GOLDEN_RATIO;

	  float col[3];
	  RGBfromHSV( fmod(h,1.0), 0.8, 0.99, col );
	  
	   int c = (8*8*i)+(8*j)+k;
	  colors[c][0] = col[0];
	  colors[c][1] = col[1];
	  colors[c][2] = col[2];
	  colors[c][3] = alpha;
	}
}

/* Get a nice bright color from index @i in the color table. */
void bright_color( int i, float color[4] )
{
  memcpy( color, colors[ i % (8*8*8) ], 4 * sizeof(float) );
}


