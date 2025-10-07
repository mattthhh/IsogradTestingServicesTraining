/*******
 * * Read input from STDIN
 * Use: printf(...) or fprintf( stdout, ...) to output your result to stdout.
 * Use: fprintf(stderr, ...);  to output debugging information to stderr.
 * ***/
#include <stdlib.h>
#include <stdio.h>
#include "libisograd.h"

int main()
{
  int N;
  int I = 0;
  if (scanf("%d", &N) != 1)
    return 1;
  for (int i = 0; i < N; i++)
  {
    double x, y;
    if (scanf("%lf %lf", &x, &y) != 2)
      return 1;
    if (x * x + y * y <= 1.0)
    {
      I++;
    }
  }
  double pi_approx = 4.0 * I / N;
  printf("%.3lf", pi_approx);
  return 0;
}