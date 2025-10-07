/*******
* Read input from STDIN
* Use: printf(...) or fprintf( stdout, ...) to output your result to stdout.
* Use: fprintf(stderr, ...);  to output debugging information to stderr.
* ***/
#include <stdlib.h>
#include <stdio.h>
#include "libisograd.h"


typedef struct {
  int a, r, e;
} Fencer;

int beats(Fencer x, Fencer y) {
  int cnt = 0;
  if (x.a > y.a) cnt++;
  if (x.r > y.r) cnt++;
  if (x.e > y.e) cnt++;
  return cnt >= 2;
}

int main() {
  int N;
  if (scanf("%d", &N) != 1) return 1;
  Fencer f[2005];
  for (int i = 0; i < N; i++) {
    if (scanf("%d %d %d", &f[i].a, &f[i].r, &f[i].e) != 3) return 1;
  }
  // a = f[0]
  for (int b = 1; b < N; b++) {
    if (!beats(f[0], f[b])) continue;
    for (int c = 1; c < N; c++) {
      if (c == b) continue;
      if (!beats(f[b], f[c])) continue;
      for (int d = 1; d < N; d++) {
        if (d == b || d == c) continue;
        if (!beats(f[c], f[d])) continue;
        if (beats(f[d], f[0])) {
          printf("Yes");
          return 0;
        }
      }
    }
  }
  printf("No");
  return 0;
}