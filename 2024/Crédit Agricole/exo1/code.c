/*******
* Read input from STDIN
* Use: printf(...) or fprintf( stdout, ...) to output your result to stdout.
* Use: fprintf(stderr, ...);  to output debugging information to stderr.
* ***/
#include <stdlib.h>
#include <stdio.h>
#include "libisograd.h"

int main() {
  int N;
  if (scanf("%d", &N) != 1) {
    fprintf(stderr, "Erreur de lecture de N\n");
    return 1;
  }
  char best_name[128] = "";
  double best_avg = -1.0;
  for (int i = 0; i < N; ++i) {
    char name[128];
    double s1, s2, s3;
    if (scanf("%s %lf %lf %lf", name, &s1, &s2, &s3) != 4) {
      fprintf(stderr, "Erreur de lecture des scores pour le modèle %d\n", i+1);
      return 1;
    }
    double avg = (s1 + s2 + s3) / 3.0;
    if (avg > best_avg) {
      best_avg = avg;
      snprintf(best_name, sizeof(best_name), "%s", name);
    }
  }
  printf("%s", best_name);
  return 0;
}