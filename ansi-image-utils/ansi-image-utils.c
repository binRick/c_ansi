#include "ansi-image-utils/ansi-image-utils.h"
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int read_uint32(uint8_t *buf);
static int read_uint16(uint8_t *buf);
static void read_from(const char *path, char *buf, int len, int offset);

__attribute__((unused))static int read_uint16(uint8_t *buf) {
  return(buf[1] << 8
         | buf[0]
         );
}

__attribute__((unused))static int read_uint32(uint8_t *buf) {
  return(buf[0] << 24
         | buf[1] << 16
         | buf[2] << 8
         | buf[3]
         );
}

__attribute__((unused))static void read_from(const char *path, char *buf, int len, int offset) {
  int fd = open(path, O_RDONLY);

  if (fd < 0) {
    perror("open()");
    exit(1);
  }

  if (pread(fd, buf, len, offset) < 0) {
    perror("read()");
    exit(1);
  }
  close(fd);
}

bool is_jpeg(uint8_t *buf) {
  return((0xff == buf[0] && 0xd8 == buf[1]));
}

bool is_gif(uint8_t *buf) {
  return(('G' == buf[0] && 'I' == buf[1] && 'F' == buf[2]));
}

bool is_png(uint8_t *buf) {
  return(('P' == buf[1] && 'N' == buf[2] && 'G' == buf[3]));
}
