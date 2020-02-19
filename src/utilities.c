#include "ljmd.h"

/* helper function: zero out an array */
int azzero(double *d, const int n) {
  if(!d) return -1;
  int i;
  for (i = 0; i < n; ++i) {
    d[i] = 0.0;
  }
  return 0;
}

