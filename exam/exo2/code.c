/*******
* Read input from STDIN
* Use: printf(...) or fprintf( stdout, ...) to output your result to stdout.
* Use: fprintf(stderr, ...);  to output debugging information to stderr.
* ***/
#include <stdlib.h>
#include <stdio.h>
#include "libisograd.h"
#include <string.h>

#define MAX_MESSAGES 100
#define MAX_NAME_LEN 256

int main() {
  int n;
  if (scanf("%d", &n) != 1) {
    return 0;
  }

  char stack[MAX_MESSAGES][MAX_NAME_LEN];
  int top = 0;
  int ok = 1;

  int c = getchar();
  if (c != '\n' && c != EOF) {
    ungetc(c, stdin);
  }

  // Simulation d'un empilement : le dernier vêtement déposé doit être le premier retiré.
  for (int i = 0; i < n; i++) {
    char line[MAX_NAME_LEN + 4];

    if (!fgets(line, sizeof(line), stdin)) {
      ok = 0;
      break;
    }

    if (line[0] == '\n' || line[0] == '\0') {
      i--;
      continue;
    }

    char sign = line[0];
    char *item = line + 1;
    while (*item == ' ' || *item == '\t') {
      item++;
    }

    size_t len = strlen(item);
    while (len > 0 && (item[len - 1] == '\n' || item[len - 1] == '\r')) {
      item[--len] = '\0';
    }

    if (sign == '+') {
      if (top >= MAX_MESSAGES) {
        ok = 0;
        break;
      }
  snprintf(stack[top], MAX_NAME_LEN, "%s", item);
      top++;
    } else if (sign == '-') {
      if (top == 0 || strncmp(stack[top - 1], item, MAX_NAME_LEN) != 0) {
        ok = 0;
        break;
      }
      top--;
    } else {
      ok = 0;
      break;
    }
  }

  printf("%s", ok ? "yes" : "no");

  return 0;
}