/*******
* Read input from STDIN
* Use: printf(...) or fprintf( stdout, ...) to output your result to stdout.
* Use: fprintf(stderr, ...);  to output debugging information to stderr.
* ***/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "libisograd.h"

typedef struct {
  int idx;
  int x, y;
  int p; // nbPizzas
  double ang; // atan2(y, x)
  int rad; // |x| + |y|
} Order;

static int cmp_rad_asc(const void *a, const void *b) {
  const Order *A = (const Order *)a, *B = (const Order *)b;
  if (A->rad != B->rad) return (A->rad < B->rad) ? -1 : 1;
  if (A->ang < B->ang) return -1;
  if (A->ang > B->ang) return 1;
  return (A->idx < B->idx) ? -1 : (A->idx > B->idx);
}

static int cmp_ang_rad_asc(const void *a, const void *b) {
  const Order *A = (const Order *)a, *B = (const Order *)b;
  if (A->ang < B->ang) return -1;
  if (A->ang > B->ang) return 1;
  if (A->rad != B->rad) return (A->rad < B->rad) ? -1 : 1;
  return (A->idx < B->idx) ? -1 : (A->idx > B->idx);
}

static void emit_tours(Order *list, int n, int C, int force_newline_before, int *emitted_anything) {
  int load = 0;
  int first_in_line = 1;
  if (force_newline_before && *emitted_anything) {
    putchar('\n');
    first_in_line = 1;
    load = 0;
  }
  for (int i = 0; i < n; i++) {
    if (load + list[i].p <= C) {
      if (!first_in_line) putchar(' ');
      printf("%d", list[i].idx);
      first_in_line = 0;
      load += list[i].p;
    } else {
      // close current tour
      putchar('\n');
      // start new tour with this order
      printf("%d", list[i].idx);
      first_in_line = 0;
      load = list[i].p;
    }
    *emitted_anything = 1;
  }
}

int main(void) {
  int N, C;
  if (scanf("%d %d", &N, &C) != 2) {
    return 0;
  }
  if (N <= 0) return 0;

  Order *all = (Order *)malloc(sizeof(Order) * N);
  if (!all) return 0;
  for (int i = 0; i < N; i++) {
    int x, y, p;
    if (scanf("%d %d %d", &x, &y, &p) != 3) {
      x = y = 0; p = 1;
    }
    all[i].idx = i; all[i].x = x; all[i].y = y; all[i].p = p;
    all[i].ang = atan2((double)y, (double)x);
    long long ax = (long long)x; if (ax < 0) ax = -ax;
    long long ay = (long long)y; if (ay < 0) ay = -ay;
    long long r = ax + ay; if (r > 2147483647LL) r = 2147483647LL;
    all[i].rad = (int)r;
  }

  // Split into Q1 (x>=0,y>=0) and the rest
  Order *q1 = (Order *)malloc(sizeof(Order) * N);
  Order *rest = (Order *)malloc(sizeof(Order) * N);
  if (!q1 || !rest) { free(all); free(q1); free(rest); return 0; }
  int n_q1 = 0, n_rest = 0;
  for (int i = 0; i < N; i++) {
    if (all[i].x >= 0 && all[i].y >= 0) q1[n_q1++] = all[i];
    else rest[n_rest++] = all[i];
  }

  qsort(q1, n_q1, sizeof(Order), cmp_rad_asc);         // near to far in Q1
  qsort(rest, n_rest, sizeof(Order), cmp_ang_rad_asc);  // by angle globally

  int emitted_any = 0;
  // Emit Q1 tours
  emit_tours(q1, n_q1, C, 0, &emitted_any);
  // Then force a new line before starting the rest if something was already printed,
  // to keep clusters separated (aligns with the sample expectation)
  emit_tours(rest, n_rest, C, 1, &emitted_any);

  // Pas de newline terminal supplémentaire

  free(all); free(q1); free(rest);
  return 0;
}