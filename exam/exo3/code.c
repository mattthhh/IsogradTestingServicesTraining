/*******
* Read input from STDIN
* Use: printf(...) or fprintf( stdout, ...) to output your result to stdout.
* Use: fprintf(stderr, ...);  to output debugging information to stderr.
* ***/
#include <stdlib.h>
#include <stdio.h>
#include "libisograd.h"
#include <string.h>
#include <ctype.h>

#define MAX_INGREDIENTS 2000
#define MAX_NAME_LEN 256
#define MAX_STUDENTS 10000

static char ingredients[MAX_INGREDIENTS][MAX_NAME_LEN];
static int parent[MAX_INGREDIENTS];
static int rank_u[MAX_INGREDIENTS];
static int neg_a[MAX_STUDENTS];
static int neg_b[MAX_STUDENTS];

static int find_set(int x) {
  if (parent[x] != x) {
    parent[x] = find_set(parent[x]);
  }
  return parent[x];
}

static void union_set(int a, int b) {
  int root_a = find_set(a);
  int root_b = find_set(b);
  if (root_a == root_b) {
    return;
  }
  if (rank_u[root_a] < rank_u[root_b]) {
    parent[root_a] = root_b;
  } else if (rank_u[root_a] > rank_u[root_b]) {
    parent[root_b] = root_a;
  } else {
    parent[root_b] = root_a;
    rank_u[root_a]++;
  }
}

static char *trim(char *s) {
  while (*s && isspace((unsigned char)*s)) {
    s++;
  }
  char *end = s + strlen(s);
  while (end > s && isspace((unsigned char)*(end - 1))) {
    end--;
  }
  *end = '\0';
  return s;
}

static int get_index(const char *name, int count) {
  for (int i = 0; i < count; i++) {
    if (strcmp(ingredients[i], name) == 0) {
      return i;
    }
  }
  return -1;
}

int main() {
  int ingredient_count, student_count;

  if (scanf("%d %d", &ingredient_count, &student_count) != 2) {
    return 0;
  }

  int ch;
  while ((ch = getchar()) != '\n' && ch != EOF) {
    /* consume rest of line */
  }

  if (ingredient_count > MAX_INGREDIENTS || student_count > MAX_STUDENTS) {
    return 0;
  }

  char line[512];
  for (int i = 0; i < ingredient_count;) {
    if (!fgets(line, sizeof(line), stdin)) {
      return 0;
    }
    char *name = trim(line);
    if (*name == '\0') {
      continue;
    }
    snprintf(ingredients[i], MAX_NAME_LEN, "%s", name);
    parent[i] = i;
    rank_u[i] = 0;
    i++;
  }

  for (int i = 0; i < ingredient_count; i++) {
    if (parent[i] != i) {
      parent[i] = find_set(i);
    }
  }

  int neg_count = 0;
  int ok = 1;

  for (int i = 0; i < student_count && ok;) {
    if (!fgets(line, sizeof(line), stdin)) {
      ok = 0;
      break;
    }
    char *content = trim(line);
    if (*content == '\0') {
      continue;
    }

    char *and_ptr = strstr(content, " and ");
    if (!and_ptr) {
      ok = 0;
      break;
    }

    *and_ptr = '\0';
    char *first_name = trim(content);
    char *second_part = trim(and_ptr + 5);

    int idx_first = get_index(first_name, ingredient_count);
    if (idx_first < 0) {
      ok = 0;
      break;
    }

    int is_negative = 0;
    if (strncmp(second_part, "no ", 3) == 0) {
      is_negative = 1;
      second_part = trim(second_part + 3);
    }

    int idx_second = get_index(second_part, ingredient_count);
    if (idx_second < 0) {
      ok = 0;
      break;
    }

    if (!is_negative) {
      union_set(idx_first, idx_second);
    } else {
      neg_a[neg_count] = idx_first;
      neg_b[neg_count] = idx_second;
      neg_count++;
    }

    i++;
  }

  if (ok) {
    // Un panier unique par ingrédient : il suffit de vérifier que les exclusions ne
    // regroupent jamais deux ingrédients déjà assemblés par les préférences.
    for (int i = 0; i < neg_count; i++) {
      if (find_set(neg_a[i]) == find_set(neg_b[i])) {
        ok = 0;
        break;
      }
    }
  }

  printf("%s", ok ? "yes" : "no");

  return 0;
}