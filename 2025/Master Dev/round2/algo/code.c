/*******
* Read input from STDIN
* Use: printf(...) or fprintf( stdout, ...) to output your result to stdout.
* Use: fprintf(stderr, ...);  to output debugging information to stderr.
* ***/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "libisograd.h"

typedef struct {
  char name[128];
  long long cnt;
} Attr;

static int cmp_desc(const void* a, const void* b) {
  const Attr* x = (const Attr*)a;
  const Attr* y = (const Attr*)b;
  if (x->cnt > y->cnt) return -1;
  if (x->cnt < y->cnt) return 1;
  return strcmp(x->name, y->name); // tie-break for determinism
}

int main(void) {
  int nbGroupes, nbAttractions;
  if (scanf("%d %d", &nbGroupes, &nbAttractions) != 2) return 0;

  // Tableau dynamique des attractions rencontrées
  int cap = nbAttractions > 0 ? nbAttractions : 16;
  if (cap < 16) cap = 16;
  Attr* arr = (Attr*)malloc(sizeof(Attr) * (size_t)cap);
  if (!arr) return 0;
  int n = 0;

  char name[128];
  for (int g = 0; g < nbGroupes; ++g) {
    int taille, nbVisites;
    if (scanf("%d %d", &taille, &nbVisites) != 2) { free(arr); return 0; }
    for (int k = 0; k < nbVisites; ++k) {
      if (scanf("%127s", name) != 1) { free(arr); return 0; }
      // Rechercher l'attraction
      int idx = -1;
      for (int i = 0; i < n; ++i) {
        if (strcmp(arr[i].name, name) == 0) { idx = i; break; }
      }
      if (idx == -1) {
        if (n >= cap) {
          cap *= 2;
          Attr* tmp = (Attr*)realloc(arr, sizeof(Attr) * (size_t)cap);
          if (!tmp) { free(arr); return 0; }
          arr = tmp;
        }
        strncpy(arr[n].name, name, sizeof(arr[n].name));
        arr[n].name[sizeof(arr[n].name)-1] = '\0';
        arr[n].cnt = 0;
        idx = n++;
      }
      arr[idx].cnt += (long long)taille;
    }
  }

  // On s'attend à n == nbAttractions, mais inutile de forcer
  qsort(arr, (size_t)n, sizeof(Attr), cmp_desc);

  for (int i = 0; i < n; ++i) {
    if (i) printf(" ");
    printf("%s", arr[i].name);
  }

  free(arr);
  return 0;
}