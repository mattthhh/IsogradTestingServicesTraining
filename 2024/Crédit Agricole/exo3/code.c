/*******
* Read input from STDIN
* Use: printf(...) or fprintf( stdout, ...) to output your result to stdout.
* Use: fprintf(stderr, ...);  to output debugging information to stderr.
* ***/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libisograd.h"

int main() {
  int W, H;
  if (scanf("%d %d", &W, &H) != 2) {
    fprintf(stderr, "Erreur de lecture de W et H\n");
    return 1;
  }
  int grid[50][50], next[50][50];
  char line[64];
  for (int i = 0; i < H; ++i) {
    if (scanf("%s", line) != 1) {
      fprintf(stderr, "Erreur de lecture de la ligne %d\n", i+1);
      return 1;
    }
    for (int j = 0; j < W; ++j) {
      grid[i][j] = line[j] - '0';
    }
  }

  // Pour stocker les états précédents (max 1001 états, chaque état = W*H chiffres)
  int max_steps = 1001;
  char *states[1001];
  for (int i = 0; i < max_steps; ++i) states[i] = NULL;

  int found = 0, start = -1, period = -1;
  for (int step = 0; step < max_steps && !found; ++step) {
    // Encoder l'état courant en chaîne
    char *repr = malloc(W*H+1);
    for (int i = 0, k = 0; i < H; ++i)
      for (int j = 0; j < W; ++j)
        repr[k++] = grid[i][j] + '0';
    repr[W*H] = 0;
    // Chercher si déjà vu
    for (int prev = 0; prev < step; ++prev) {
      if (states[prev] && strcmp(states[prev], repr) == 0) {
        start = prev;
        period = step - prev;
        found = 1;
        break;
      }
    }
    states[step] = repr;
    if (found) break;
    // Calculer l'état suivant
    for (int i = 0; i < H; ++i) {
      for (int j = 0; j < W; ++j) {
        int v = grid[i][j];
        if (v == 5) next[i][j] = 4;
        else if (v == 4) next[i][j] = 3;
        else if (v == 3) next[i][j] = 2;
        else if (v == 2) next[i][j] = 1;
        else if (v == 1) {
          int n5 = 0, n1 = 0;
          if (i > 0 && grid[i-1][j] == 5) n5++;
          if (i < H-1 && grid[i+1][j] == 5) n5++;
          if (j > 0 && grid[i][j-1] == 5) n5++;
          if (j < W-1 && grid[i][j+1] == 5) n5++;
          if (i > 0 && grid[i-1][j] == 1) n1++;
          if (i < H-1 && grid[i+1][j] == 1) n1++;
          if (j > 0 && grid[i][j-1] == 1) n1++;
          if (j < W-1 && grid[i][j+1] == 1) n1++;
          if (n5 >= 1) next[i][j] = 5;
          else if (n1 >= 2) next[i][j] = 1;
          else next[i][j] = 3;
        }
      }
    }
    // Copier next -> grid
    for (int i = 0; i < H; ++i)
      for (int j = 0; j < W; ++j)
        grid[i][j] = next[i][j];
  }
  // Affichage sans saut de ligne final
  printf("%d\n%d", start, period);
  // Libération mémoire
  for (int i = 0; i < max_steps; ++i) if (states[i]) free(states[i]);
  return 0;
}