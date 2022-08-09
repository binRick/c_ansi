#include <stdint.h>
#include <sys/time.h>

#define TAI0    ((size_t)1 << 62)

struct tai64n {
  size_t sec;
  size_t nano;
};

size_t tai64ts(void);
struct tai64n *tai64(void);
