#include "tai64n/tai64n.h"
#include <stdlib.h>

size_t tai64ts(){
  struct tai64n *t = tai64();

  if (!t)
    return(0);

  size_t ts = (t->nano * 1000) + (t->sec);

  free(t);
  return(ts);
}

struct tai64n *tai64(){
  struct tai64n  *out = calloc(1, sizeof(struct tai64n));
  struct timeval now;

  if (gettimeofday(&now, NULL) == -1)
    return(NULL);

  out->sec  = TAI0 + now.tv_sec;
  out->nano = 1000 * now.tv_usec + 500;

  return(out);
}
