/*******
* Read input from STDIN
* Use: printf(...) or fprintf( stdout, ...) to output your result to stdout.
* Use: fprintf(stderr, ...);  to output debugging information to stderr.
* ***/
#include <stdlib.h>
#include <stdio.h>
#include "libisograd.h"

int main(void) {
  int prefs[10];
  int N;

  // Lecture des préférences du client (10 entiers)
  for (int i = 0; i < 10; ++i) {
    if (scanf("%d", &prefs[i]) != 1) {
      return 0; // Entrée invalide ou incomplète
    }
  }

  // Lecture du nombre de bouteilles
  if (scanf("%d", &N) != 1) {
    return 0; // Entrée invalide
  }

  long long bestDist = -1; // -1 signifie non initialisé
  int bestIndex = -1;

  for (int idx = 0; idx < N; ++idx) {
    long long dist = 0;
    for (int j = 0; j < 10; ++j) {
      int v;
      if (scanf("%d", &v) != 1) {
        return 0; // Entrée invalide
      }
      long long d = (long long)v - (long long)prefs[j];
      dist += d * d;
    }

    if (bestDist == -1 || dist < bestDist) {
      bestDist = dist;
      bestIndex = idx;
    }
  }

  // Affichage de l'index de la meilleure bouteille
  if (bestIndex >= 0) {
    // Les fichiers de sortie attendus n'ont pas de saut de ligne final
    printf("%d", bestIndex);
  }

  return 0;
}