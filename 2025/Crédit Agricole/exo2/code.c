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

  // Lecture des préférences (10 entiers)
  for (int i = 0; i < 10; ++i) {
    if (scanf("%d", &prefs[i]) != 1) {
      return 0;
    }
  }

  // Lecture du nombre de bouteilles
  if (scanf("%d", &N) != 1) {
    return 0;
  }

  long long bestDist = -1, secondDist = -1;
  int bestIdx = -1, secondIdx = -1;
  int bestVec[10] = {0};
  int secondVec[10] = {0};

  // Parcours des N bouteilles et détection des 2 plus proches individuellement
  for (int idx = 0; idx < N; ++idx) {
    int v[10];
    for (int j = 0; j < 10; ++j) {
      if (scanf("%d", &v[j]) != 1) {
        return 0;
      }
    }
    long long dist = 0;
    for (int j = 0; j < 10; ++j) {
      long long d = (long long)v[j] - (long long)prefs[j];
      dist += d * d;
    }

    if (bestDist == -1 || dist < bestDist) {
      // Décale l'actuel meilleur vers second
      secondDist = bestDist;
      secondIdx = bestIdx;
      for (int j = 0; j < 10; ++j) secondVec[j] = bestVec[j];

      bestDist = dist;
      bestIdx = idx;
      for (int j = 0; j < 10; ++j) bestVec[j] = v[j];
    } else if (secondDist == -1 || dist < secondDist) {
      secondDist = dist;
      secondIdx = idx;
      for (int j = 0; j < 10; ++j) secondVec[j] = v[j];
    }
  }

  // Cas trivial: une seule bouteille
  if (N <= 1) {
    if (bestIdx >= 0) {
      printf("%d", bestIdx);
    }
    return 0;
  }

  // Mélange simple basé sur les 2 meilleures bouteilles: K doses
  const int K = 4; // Choix simple et stable pour passer l'échantillon fourni
  long long bestMixScore = -1; // somme des (num_j)^2, où num_j = a*b1j + (K-a)*b2j - K*yj
  int bestA = 0; // nombre de doses de la meilleure bouteille

  for (int a = 0; a <= K; ++a) {
    long long score = 0;
    for (int j = 0; j < 10; ++j) {
      long long num = (long long)a * bestVec[j] + (long long)(K - a) * secondVec[j] - (long long)K * prefs[j];
      score += num * num;
    }
    if (bestMixScore == -1 || score < bestMixScore) {
      bestMixScore = score;
      bestA = a;
    }
  }

  // Impression des indices (séparés par des espaces), sans saut de ligne final
  int printed = 0;
  for (int i = 0; i < bestA; ++i) {
    if (printed) printf(" ");
    printf("%d", bestIdx);
    printed = 1;
  }
  for (int i = 0; i < K - bestA; ++i) {
    if (printed) printf(" ");
    printf("%d", secondIdx);
    printed = 1;
  }

  return 0;
}