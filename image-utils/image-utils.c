#include "image-utils.h"
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int read_uint32(uint8_t *buf);
static int read_uint16(uint8_t *buf);
static void read_from(const char *path, char *buf, int len, int offset);
static void output_css_dimensions(int width, int height);


static void output_css_dimensions(int width, int height) {
  printf("width: %dpx;\n", width);
  printf("height: %dpx;\n", height);
}


static void read_from(const char *path, char *buf, int len, int offset) {
  // open file
  int fd = open(path, O_RDONLY);

  if (fd < 0) {
    perror("open()");
    exit(1);
  }

  // read bytes
  if (pread(fd, buf, len, offset) < 0) {
    perror("read()");
    exit(1);
  }
  close(fd);
}


static void output_gif_dimensions(const char *path) {
  char buf[4];

  read_from(path, buf, 4, 6);
  output_css_dimensions(
    read_uint16(buf),
    read_uint16(buf + 2));
}


static void output_png_dimensions(const char *path) {
  // read bytes
  char buf[8];

  read_from(path, buf, 8, 16);
  output_css_dimensions(
    read_uint32(buf),
    read_uint32(buf + 4));
}


static void output_jpeg_dimensions(const char *path) {
  fprintf(stderr, "jpeg not yet supported\n");
  exit(1);
}


static int read_uint16(uint8_t *buf) {
  return(buf[1] << 8
         | buf[0]);
}


static int read_uint32(uint8_t *buf) {
  return(buf[0] << 24
         | buf[1] << 16
         | buf[2] << 8
         | buf[3]);
}

