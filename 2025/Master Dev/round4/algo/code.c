/*******
* Read input from STDIN
* Use: printf(...) or fprintf( stdout, ...) to output your result to stdout.
* Use: fprintf(stderr, ...);  to output debugging information to stderr.
* ***/
#include <stdlib.h>
#include <stdio.h>
#include "libisograd.h"

int main(void) {
  int N, C;
  if (scanf("%d %d", &N, &C) != 2) {
    return 0;
  }

  // On ignore x, y, on ne garde que nbPizzas et l'index
  int *tour = (int *)malloc(sizeof(int) * (N > 0 ? N : 1));
  if (!tour) return 0;
  int tour_len = 0;
  int load = 0;

  for (int i = 0; i < N; i++) {
    int x, y, nb;
    if (scanf("%d %d %d", &x, &y, &nb) != 3) {
      nb = 0; // entrée invalide, on sécurise
    }

    if (load + nb <= C) {
      // On ajoute cette commande à la tournée courante
      tour[tour_len++] = i;
      load += nb;
    } else {
      // On imprime la tournée courante
      if (tour_len > 0) {
        for (int k = 0; k < tour_len; k++) {
          if (k) putchar(' ');
          printf("%d", tour[k]);
        }
        putchar('\n');
      }
      // Nouvelle tournée qui commence avec cette commande
      tour_len = 1;
      tour[0] = i;
      load = nb;
    }
  }

  // Imprimer la dernière tournée s'il en reste une
  if (tour_len > 0) {
    for (int k = 0; k < tour_len; k++) {
      if (k) putchar(' ');
      printf("%d", tour[k]);
    }
    // Pas de newline final pour matcher les samples
  }

  free(tour);
  return 0;
}