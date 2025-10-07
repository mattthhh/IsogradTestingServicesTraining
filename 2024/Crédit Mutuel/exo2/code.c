/*******
* Read input from STDIN
* Use: printf(...) or fprintf( stdout, ...) to output your result to stdout.
* Use: fprintf(stderr, ...);  to output debugging information to stderr.
* ***/
#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include "libisograd.h"

typedef struct {
  int h;
  char color[6]; // "Black" ou "White"
} Wall;

int main() {
  int N;
  if (scanf("%d", &N) != 1) return 1;
  Wall walls[10010];
  for (int i = 0; i < N; i++) {
    if (scanf("%d %5s", &walls[i].h, walls[i].color) != 2) return 1;
  }

  // Déterminer les murs visibles
  int max_h = 0;
  int visible_idx[10010];
  int nb_visible = 0;
  for (int i = 0; i < N; i++) {
    if (walls[i].h > max_h) {
      max_h = walls[i].h;
      visible_idx[nb_visible++] = i;
    }
    // sinon, caché (y compris égal à max_h)
  }

  // Fusionner les murs visibles consécutifs de même couleur
  int confusion = 0;
  int i = 0;
  while (i < nb_visible) {
    int j = i+1;
    while (j < nb_visible && strcmp(walls[visible_idx[j]].color, walls[visible_idx[i]].color) == 0) {
      j++;
    }
    if (j - i > 1) {
      confusion += (j - i);
    }
    i = j;
  }
  printf("%d", confusion);
  return 0;
}