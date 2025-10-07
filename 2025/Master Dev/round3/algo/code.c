/*******
* Read input from STDIN
* Use: printf(...) or fprintf( stdout, ...) to output your result to stdout.
* Use: fprintf(stderr, ...);  to output debugging information to stderr.
* ***/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libisograd.h"

typedef struct { double E, P; int idx; } Item;

static int cmp_descE(const void* a, const void* b) {
  const Item* x = (const Item*)a;
  const Item* y = (const Item*)b;
  if (x->E > y->E) return -1;
  if (x->E < y->E) return 1;
  return x->idx - y->idx;
}

int main(void) {
  int N; double C;
  if (scanf("%d %lf", &N, &C) != 2) return 0;
  Item* a = (Item*)malloc(sizeof(Item) * (size_t)N);
  if (!a) return 0;
  for (int i = 0; i < N; ++i) {
    if (scanf("%lf %lf", &a[i].E, &a[i].P) != 2) { free(a); return 0; }
    a[i].idx = i;
  }

  qsort(a, (size_t)N, sizeof(Item), cmp_descE);

  double used = 0.0;
  int firstPrinted = 0;
  for (int i = 0; i < N; ++i) {
    if (used + a[i].P <= C + 1e-9) {
      used += a[i].P;
      // Impression d'un index par ligne, sans newline final après la dernière ligne
      if (firstPrinted) printf("\n");
      printf("%d", a[i].idx);
      firstPrinted = 1;
    }
  }

  free(a);
  return 0;
}