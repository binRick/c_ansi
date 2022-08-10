#include "ansi-codes.h"
#include "ansi-rgb-utils-test.h"
#include "module/def.h"
#include "module/module.h"
#include "module/require.h"

char    *MODES[] = {
  "RGB to HSLuv",
  "HSLuv to RGB",
  "HPLuv to RGB",
  "RGB to HPLuv",
  "RGBA to String",
  "RGBA from String",
};
double  HSL[][3] = {
  { -1,  -1,  -1,  },
  { 0.1, 0.2, 0.3, },
  { -1,  -1,  -1,  },
  { 0.4, 0.5, 0.6, },
};
char    HEXES[][32] = {
  { "cyan"             },
  { "rgba(0,0,0, 1)"   },
  { "rgb(255,255,255)" },
  { "black"            },
  { "rgb(0,0,0)"       },
  { "#fff"             },
  { "#ffffff"          },
  { "#000000"          },
  { "olive"            },
  { "#808000"          },
};
int32_t VALS[4]     = { -1, -1, -1, -1 };
char    BUFS[][256] = {
  { 0 },
  { 0 },
  { 0 },
  { 0 },
};
short   OKS[]    = { -1, -1, -1, -1 };
double  RGB[][3] = {
  { 0.06666666666666667, 0.8666666666666667, 1.0 },
  { -1,                  -1,                 -1, },
  { 0.7,                 0.8,                0.9,},
  { -1,                  -1,                 -1, },
};
rgba_t  RGBA[] = {
  { .r = 0.99000, .g = 0.27, .b = 0.20, .a = 0.00 },
  { .r = 0.5,     .g = 0.3,  .b = 0.2,  .a = 0.31 },
};


int main(int argc, char **argv) {
  (void)argc; (void)argv;

  rgb2hsluv(RGB[0][0], RGB[0][1], RGB[0][2], &HSL[0][0], &HSL[0][1], &HSL[0][2]);
  log_debug("<%s> ", MODES[0]);
  log_debug("  r:%f|g:%f|b:%f", RGB[0][0], RGB[0][1], RGB[0][2]);
  log_debug("  hue:%f|saturation:%f|lightness:%f", HSL[0][0], HSL[0][1], HSL[0][2]);

  hsluv2rgb(HSL[1][0], HSL[1][1], HSL[1][2], &RGB[1][0], &RGB[1][1], &RGB[1][2]);
  log_debug("<%s> ", MODES[1]);
  log_debug("  r:%f|g:%f|b:%f", RGB[1][0], RGB[1][1], RGB[1][2]);
  log_debug("  hue:%f|saturation:%f|lightness:%f", HSL[1][0], HSL[1][1], HSL[1][2]);

  hpluv2rgb(HSL[2][0], HSL[2][1], HSL[2][2], &RGB[2][0], &RGB[2][1], &RGB[2][2]);
  log_debug("<%s> ", MODES[2]);
  log_debug("  r:%f|g:%f|b:%f", RGB[2][0], RGB[2][1], RGB[2][2]);
  log_debug("  hue:%f|saturation:%f|lightness:%f", HSL[2][0], HSL[2][1], HSL[2][2]);

  rgb2hpluv(RGB[3][0], RGB[3][1], RGB[3][2], &HSL[3][0], &HSL[3][1], &HSL[3][2]);
  log_debug("<%s> ", MODES[3]);
  log_debug("  r:%f|g:%f|b:%f", RGB[3][0], RGB[3][1], RGB[3][2]);
  log_debug("  hue:%f|saturation:%f|lightness:%f", HSL[3][0], HSL[3][1], HSL[3][2]);

  rgba_to_string(RGBA[0], BUFS[0], 256);
  log_debug("  r:%f|g:%f|b:%f|a:%f|buf:%s|", RGBA[0].r, RGBA[0].g, RGBA[0].b, RGBA[0].a, BUFS[0]);

  for (int i = 0; i < (sizeof(HEXES) / sizeof(HEXES[0])); i++) {
    double   _HSL[3] = { 0, 0, 0 };
    short    OK      = -1;
    char     _BUF[1024];
    uint32_t VAL = rgba_from_string(HEXES[i], &OK);
    log_debug("<%s> ", MODES[4]);
    log_debug("  hex:%s|", HEXES[i]);
    rgba_t _RGBA = rgba_new(VAL);
    log_debug("<%f|%f|%f|%f> ", _RGBA.r, _RGBA.b, _RGBA.g, _RGBA.a);
    log_debug("  |ok:%d|val:%d|", OK, VAL);
    rgba_to_string(_RGBA, _BUF, 256);
    log_debug("  |str::%s|", _BUF);
    rgb2hsluv(_RGBA.r, _RGBA.b, _RGBA.g, &_HSL[0], &_HSL[1], &_HSL[2]);
    log_debug("HSLUV>  hue:%f|saturation:%f|lightness:%f", _HSL[0], _HSL[1], _HSL[2]);
    rgb2hpluv(_RGBA.r, _RGBA.b, _RGBA.g, &_HSL[0], &_HSL[1], &_HSL[2]);
    log_debug("HPLUV>  hue:%f|saturation:%f|lightness:%f", _HSL[0], _HSL[1], _HSL[2]);
  }
  {
    // printf(AC_CLS);
  }
  {
    printf(AC_BUTTON("Yes", AC_GREEN) "\t");
    printf(AC_BUTTON("Yes", AC_RED) "\t");
    printf(AC_BUTTON("Yes", AC_NONE) "\t");
    printf(AC_BUTTON("No", AC_GREEN) "\t");
    printf(AC_BUTTON("No", AC_RED) "\t");
    printf(AC_BUTTON("No", AC_BLUE) "\t");
    printf(AC_BUTTON("No", AC_NONE) "\n");
  }
  {
    printf(AC_BUTTON("Yes", AC_GREEN) "\t" AC_BUTTON("No", AC_NONE) "\n");
  }
  {
    module(ac_confirm) * B = require(ac_confirm);
    struct ac_confirm_option_t *O1 = B->init_option("Option 1");
    B->add_option(O1);
    struct ac_confirm_option_t *O2 = B->init_option("Option 2");
    O2->selected = true;
    B->add_option(O2);
    struct ac_confirm_option_t *O3 = B->init_option("Option 3");
    B->add_option(O3);
    struct ac_confirm_option_t *O4 = B->init_option("Option 4");
    B->add_option(O4);
    printf("# options:  %lu\n", B->get_options_qty());
    B->render_ui();
    printf("render ended\n");
  }
  return(0);
} /* main */
