/*******
* Read input from STDIN
* Use: printf(...) or fprintf( stdout, ...) to output your result to stdout.
* Use: fprintf(stderr, ...);  to output debugging information to stderr.
* ***/
#include <stdlib.h>
#include <stdio.h>
#include "libisograd.h"

#define NB_LIEUX 5

int main() {
  int prix_plein, prix_reduit;
  int economie_totale = 0;

  // Chaque ligne fournit les tarifs plein et réduit pour un lieu culturel.
  for (int i = 0; i < NB_LIEUX && scanf("%d %d", &prix_plein, &prix_reduit) == 2; i++) {
    economie_totale += prix_plein - prix_reduit;
  }

  printf("%d\n", economie_totale);

  return 0;
}