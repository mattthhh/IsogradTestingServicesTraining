/*******
* Read input from STDIN
* Use: printf(...) or fprintf( stdout, ...) to output your result to stdout.
* Use: fprintf(stderr, ...);  to output debugging information to stderr.
* ***/
#include <stdlib.h>
#include <stdio.h>
#include "libisograd.h"

int main() {
  int yeux, jambes, queues;
  if (scanf("%d", &yeux) != 1) {
    fprintf(stderr, "Erreur de lecture des yeux\n");
    return 1;
  }
  if (scanf("%d", &jambes) != 1) {
    fprintf(stderr, "Erreur de lecture des jambes\n");
    return 1;
  }
  if (scanf("%d", &queues) != 1) {
    fprintf(stderr, "Erreur de lecture des queues\n");
    return 1;
  }

  int trouve = 0;
  int h, c, o;
  for (h = 0; h <= 100 && !trouve; ++h) {
    for (c = 0; c <= 100 && !trouve; ++c) {
      o = (yeux - 2*h - 2*c) / 2;
      if (o < 0 || o > 100) continue;
      if (2*h + 2*c + 2*o != yeux) continue;
      if (2*h + 4*c + 2*o != jambes) continue;
      if (c + o != queues) continue;
      trouve = 1;
      break;
    }
    if (trouve) break;
  }
  if (trouve) {
    printf("%d\n%d\n%d", h, c, o);
  } else {
    printf("Hallucination");
  }
  return 0;
}