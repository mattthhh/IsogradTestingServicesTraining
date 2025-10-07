/*******
* Read input from STDIN
* Use: printf(...) or fprintf( stdout, ...) to output your result to stdout.
* Use: fprintf(stderr, ...);  to output debugging information to stderr.
* ***/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "libisograd.h"

typedef struct { double E, P, R; int idx; } Item;

static int cmp_ratio_desc(const void* a, const void* b) {
  const Item* x = (const Item*)a, *y = (const Item*)b;
  if (x->R > y->R) return -1; if (x->R < y->R) return 1;
  if (x->E > y->E) return -1; if (x->E < y->E) return 1;
  return x->idx - y->idx;
}
static int cmp_value_desc(const void* a, const void* b) {
  const Item* x = (const Item*)a, *y = (const Item*)b;
  if (x->E > y->E) return -1; if (x->E < y->E) return 1;
  if (x->R > y->R) return -1; if (x->R < y->R) return 1;
  return x->idx - y->idx;
}
static int cmp_weight_asc(const void* a, const void* b) {
  const Item* x = (const Item*)a, *y = (Item*)b;
  if (x->P < y->P) return -1; if (x->P > y->P) return 1;
  if (x->E > y->E) return -1; if (x->E < y->E) return 1;
  return x->idx - y->idx;
}
static int cmp_idx_asc(const void* a, const void* b) {
  int ia = *(const int*)a, ib = *(const int*)b; return (ia > ib) - (ia < ib);
}
static int cmp_density_asc_idx(const void* a, const void* b, void* ctx) {
  const Item* items = (const Item*)ctx;
  int ia = *(const int*)a, ib = *(const int*)b;
  double ra = items[ia].R, rb = items[ib].R;
  if (ra < rb) return -1; if (ra > rb) return 1;
  return ia - ib;
}

typedef struct {
  unsigned char* take; // size N, 1 if taken
  double usedW;
  double totalV;
} Sol;

static void greedy_build(const Item* order, int N, double C, Sol* out) {
  unsigned char* take = (unsigned char*)calloc((size_t)N, 1);
  double used = 0.0, val = 0.0;
  const double eps = 1e-9;
  for (int i = 0; i < N; ++i) {
    int idx = order[i].idx;
    if (order[i].P <= 0.0) { // poids nul, toujours prendre si valeur > 0
      take[idx] = 1; val += order[i].E; continue;
    }
    if (used + order[i].P <= C + eps) {
      take[idx] = 1; used += order[i].P; val += order[i].E;
    }
  }
  out->take = take; out->usedW = used; out->totalV = val;
}

static void copy_solution(const Sol* s, int N, Sol* out) {
  out->take = (unsigned char*)malloc((size_t)N);
  memcpy(out->take, s->take, (size_t)N);
  out->usedW = s->usedW; out->totalV = s->totalV;
}

static void free_solution(Sol* s) { free(s->take); s->take = NULL; }

static int cmp_density_asc_thunk(const void* a, const void* b) {
  // Placeholder; will be set via global pointers if needed. But to keep ANSI C, we avoid qsort_r portability.
  return 0;
}

int main(void) {
  int N; double C;
  if (scanf("%d %lf", &N, &C) != 2) return 0;
  Item* items = (Item*)malloc(sizeof(Item) * (size_t)N);
  if (!items) return 0;
  for (int i = 0; i < N; ++i) {
    double E, P; if (scanf("%lf %lf", &E, &P) != 2) { free(items); return 0; }
    items[i].E = E; items[i].P = P; items[i].idx = i;
    items[i].R = (P > 0.0 ? (E / P) : (E > 0.0 ? 1e300 : 0.0));
  }

  // Build three orders
  Item* ordRatio = (Item*)malloc(sizeof(Item) * (size_t)N);
  Item* ordValue = (Item*)malloc(sizeof(Item) * (size_t)N);
  Item* ordLight = (Item*)malloc(sizeof(Item) * (size_t)N);
  if (!ordRatio || !ordValue || !ordLight) { free(ordRatio); free(ordValue); free(ordLight); free(items); return 0; }
  memcpy(ordRatio, items, sizeof(Item) * (size_t)N);
  memcpy(ordValue, items, sizeof(Item) * (size_t)N);
  memcpy(ordLight, items, sizeof(Item) * (size_t)N);
  qsort(ordRatio, (size_t)N, sizeof(Item), cmp_ratio_desc);
  qsort(ordValue, (size_t)N, sizeof(Item), cmp_value_desc);
  qsort(ordLight, (size_t)N, sizeof(Item), cmp_weight_asc);

  Sol sRatio, sValue, sLight;
  greedy_build(ordRatio, N, C, &sRatio);
  greedy_build(ordValue, N, C, &sValue);
  greedy_build(ordLight, N, C, &sLight);

  // Choose best
  Sol* best = &sRatio;
  if (sValue.totalV > best->totalV) best = &sValue;
  if (sLight.totalV > best->totalV) best = &sLight;

  // Local improvement: try to include excluded items by removing worst-density included items if value increases
  const double eps = 1e-9;
  // Build arrays of indices
  int* incIdx = (int*)malloc(sizeof(int) * (size_t)N);
  int nInc = 0;
  for (int i = 0; i < N; ++i) if (best->take[i]) incIdx[nInc++] = i;
  // Sort included by density ascending (worst first)
  // Use stable bubble comparator using items data
  for (int i = 0; i < nInc; ++i) {
    for (int j = i + 1; j < nInc; ++j) {
      if (items[incIdx[i]].R > items[incIdx[j]].R) { int tmp = incIdx[i]; incIdx[i] = incIdx[j]; incIdx[j] = tmp; }
    }
  }
  // Build excluded list by density descending to attempt good candidates first
  int* excIdx = (int*)malloc(sizeof(int) * (size_t)N);
  int nExc = 0;
  for (int i = 0; i < N; ++i) if (!best->take[i]) excIdx[nExc++] = i;
  for (int i = 0; i < nExc; ++i) {
    for (int j = i + 1; j < nExc; ++j) {
      if (items[excIdx[i]].R < items[excIdx[j]].R) { int t = excIdx[i]; excIdx[i] = excIdx[j]; excIdx[j] = t; }
    }
  }

  for (int ii = 0; ii < nExc; ++ii) {
    int v = excIdx[ii]; if (best->take[v]) continue;
    double wv = items[v].P, vv = items[v].E;
    if (wv <= 0.0 && vv > 0.0) { best->take[v] = 1; best->totalV += vv; continue; }
    if (best->usedW + wv <= C + eps) { best->take[v] = 1; best->usedW += wv; best->totalV += vv; continue; }
    // Need to free capacity: remove worst density included items greedily
    double need = best->usedW + wv - C;
    double freed = 0.0, remVal = 0.0;
    int removeCount = 0;
    // Track indices to remove (store positions in incIdx)
    int* toRemove = (int*)malloc(sizeof(int) * (size_t)nInc);
    for (int k = 0; k < nInc && freed + eps < need; ++k) {
      int u = incIdx[k]; if (!best->take[u]) continue; // may have been removed earlier
      toRemove[removeCount++] = u;
      freed += items[u].P;
      remVal += items[u].E;
    }
    if (freed + eps >= need && vv > remVal + eps) {
      // apply removal
      for (int k = 0; k < removeCount; ++k) {
        int u = toRemove[k]; if (best->take[u]) { best->take[u] = 0; best->usedW -= items[u].P; best->totalV -= items[u].E; }
      }
      // include v
      best->take[v] = 1; best->usedW += wv; best->totalV += vv;
      // rebuild incIdx (since set changed)
      nInc = 0;
      for (int i = 0; i < N; ++i) if (best->take[i]) incIdx[nInc++] = i;
      for (int i = 0; i < nInc; ++i) {
        for (int j = i + 1; j < nInc; ++j) {
          if (items[incIdx[i]].R > items[incIdx[j]].R) { int tmp = incIdx[i]; incIdx[i] = incIdx[j]; incIdx[j] = tmp; }
        }
      }
    }
    free(toRemove);
  }

  // Print indices taken in ascending order, one per line, no final newline
  int* outIdx = (int*)malloc(sizeof(int) * (size_t)N);
  int outN = 0; for (int i = 0; i < N; ++i) if (best->take[i]) outIdx[outN++] = i;
  // sort ascending
  for (int i = 0; i < outN; ++i) {
    for (int j = i + 1; j < outN; ++j) if (outIdx[i] > outIdx[j]) { int t = outIdx[i]; outIdx[i] = outIdx[j]; outIdx[j] = t; }
  }
  for (int i = 0; i < outN; ++i) {
    if (i) printf("\n");
    printf("%d", outIdx[i]);
  }

  // Cleanup
  free(outIdx);
  free(excIdx);
  free(incIdx);
  free_solution(&sRatio); free_solution(&sValue); free_solution(&sLight);
  free(ordRatio); free(ordValue); free(ordLight);
  free(items);
  return 0;
}