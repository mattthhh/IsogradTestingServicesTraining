/*******
* Read input from STDIN
* Use: printf(...) or fprintf( stdout, ...) to output your result to stdout.
* Use: fprintf(stderr, ...);  to output debugging information to stderr.
* ***/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libisograd.h"

#define MAX_P 1000

typedef struct {
  int *data;
  int size;
  int capacity;
} AdjList;

static void adjlist_init(AdjList *list) {
  list->size = 0;
  list->capacity = 4;
  list->data = (int *)malloc(list->capacity * sizeof(int));
}

static void adjlist_push(AdjList *list, int value) {
  if (list->size == list->capacity) {
    list->capacity *= 2;
    list->data = (int *)realloc(list->data, list->capacity * sizeof(int));
  }
  list->data[list->size++] = value;
}

int main(void) {
  int P, I;

  if (scanf("%d %d", &P, &I) != 2) {
    return 0;
  }

  if (P <= 0) {
    printf("0");
    return 0;
  }

  AdjList adj[MAX_P];
  for (int i = 0; i < P; ++i) {
    adjlist_init(&adj[i]);
  }

  for (int i = 0; i < I; ++i) {
    int A, B;
    if (scanf("%d %d", &A, &B) != 2) {
      break;
    }
    if (A < 0 || A >= P || B < 0 || B >= P) {
      continue;
    }
    adjlist_push(&adj[A], B);
    adjlist_push(&adj[B], A);
  }

  int weight[MAX_P];
  char numbered[MAX_P];

  memset(weight, 0, sizeof(weight));
  memset(numbered, 0, sizeof(numbered));

  int maxClique = 1;
  // Chaque poids correspond au nombre de voisins déjà choisis ; sur un graphe intervalle cela forme un clique.

  for (int t = P - 1; t >= 0; --t) {
    int best = -1;
    for (int v = 0; v < P; ++v) {
      if (numbered[v]) {
        continue;
      }
      if (best == -1 || weight[v] > weight[best] || (weight[v] == weight[best] && v < best)) {
        best = v;
      }
    }

    numbered[best] = 1;

    if (weight[best] + 1 > maxClique) {
      maxClique = weight[best] + 1;
    }

    for (int idx = 0; idx < adj[best].size; ++idx) {
      int u = adj[best].data[idx];
      if (!numbered[u]) {
        weight[u]++;
      }
    }
  }

  printf("%d", maxClique);

  for (int i = 0; i < P; ++i) {
    free(adj[i].data);
  }
  return 0;
}