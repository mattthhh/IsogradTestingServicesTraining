/*******
* Read input from STDIN
* Use: printf(...) or fprintf( stdout, ...) to output your result to stdout.
* Use: fprintf(stderr, ...);  to output debugging information to stderr.
* ***/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libisograd.h"

#define MAX_L 100
#define MAX_B 20
#define BASE 1000000000U
#define MAX_DIGITS 64

typedef struct {
  int len;
  unsigned int d[MAX_DIGITS];
} BigInt;

static void big_zero(BigInt *a) {
  a->len = 1;
  memset(a->d, 0, sizeof(a->d));
}

static void big_set_uint(BigInt *a, unsigned int value) {
  big_zero(a);
  if (value == 0) {
    return;
  }
  int idx = 0;
  while (value > 0) {
    a->d[idx++] = value % BASE;
    value /= BASE;
  }
  a->len = idx;
}

static int big_is_zero(const BigInt *a) {
  return a->len == 1 && a->d[0] == 0;
}

static void big_add(BigInt *dest, const BigInt *src) {
  unsigned long long carry = 0ULL;
  int maxLen = dest->len > src->len ? dest->len : src->len;

  for (int i = 0; i < maxLen; ++i) {
    unsigned long long sum = carry;
    if (i < dest->len) {
      sum += dest->d[i];
    }
    if (i < src->len) {
      sum += src->d[i];
    }
    dest->d[i] = (unsigned int)(sum % BASE);
    carry = sum / BASE;
  }

  dest->len = maxLen;
  if (carry > 0) {
    dest->d[dest->len++] = (unsigned int)carry;
  }
}

static void big_print(const BigInt *a) {
  printf("%u", a->d[a->len - 1]);
  for (int i = a->len - 2; i >= 0; --i) {
    printf("%09u", a->d[i]);
  }
}

int main(void) {
  int A, B, L;

  if (scanf("%d", &A) != 1) {
    return 0;
  }
  if (scanf("%d", &B) != 1) {
    return 0;
  }
  if (scanf("%d", &L) != 1) {
    return 0;
  }

  BigInt dp[MAX_L + 1][MAX_B + 1];
  // dp[i][c] : nombre de séquences sur i mouvements, avec c mouvements depuis la dernière respiration

  for (int i = 0; i <= L; ++i) {
    for (int c = 0; c <= B; ++c) {
      big_zero(&dp[i][c]);
    }
  }

  big_set_uint(&dp[0][0], 1);

  for (int i = 0; i < L; ++i) {
    for (int c = 0; c <= B; ++c) {
      if (big_is_zero(&dp[i][c])) {
        continue;
      }

      if (c < B) {
        big_add(&dp[i + 1][c + 1], &dp[i][c]);
      }
      if (c >= A) {
        big_add(&dp[i + 1][0], &dp[i][c]);
      }
    }
  }

  BigInt result;
  big_zero(&result);
  for (int c = 0; c <= B; ++c) {
    big_add(&result, &dp[L][c]);
  }

  big_print(&result);
  return 0;
}