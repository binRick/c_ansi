#pragma once
#include "ansi-rgb-utils.h"


void show_color(FILE *file, int color) {
  ansi_256_bg(file, color);
  fprintf(file, "                                                       ");
  ansi_reset(file);
  fprintf(file, " %3d\n", color);
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


/* rgb -> hsv saturation */
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

