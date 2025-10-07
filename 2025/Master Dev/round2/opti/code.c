/*******
* Read input from STDIN
* Use: printf(...) or fprintf( stdout, ...) to output your result to stdout.
* Use: fprintf(stderr, ...);  to output debugging information to stderr.
* ***/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include "libisograd.h"

typedef long long ll;

// Petit hash djb2
static unsigned long djb2(const char* s) {
  unsigned long h = 5381; int c;
  while ((c = (unsigned char)*s++)) h = ((h << 5) + h) + (unsigned long)c;
  return h;
}

// Tableaux globaux utilisés par le comparateur qsort de repli
static const ll* g_deg = NULL;
static char (*g_names)[128] = NULL;
static int cmp_idx_desc(const void* a, const void* b) {
  int ia = *(const int*)a;
  int ib = *(const int*)b;
  if (g_deg[ia] != g_deg[ib]) return (g_deg[ia] > g_deg[ib]) ? -1 : 1;
  return strcmp(g_names[ia], g_names[ib]);
}

static int get_or_add_index(const char* s,
              int H,
              char** h_key,
              int* h_idx,
              unsigned char* h_used,
              char names[][128],
              int M,
              int* nNames) {
  int mask = H - 1;
  unsigned long h = djb2(s);
  int pos = (int)(h & (unsigned long)mask);
  while (h_used[pos]) {
    if (strcmp(h_key[pos], s) == 0) return h_idx[pos];
    pos = (pos + 1) & mask;
  }
  // insertion
  if (*nNames < M) {
    strncpy(names[*nNames], s, 127);
    names[*nNames][127] = '\0';
  }
  h_key[pos] = names[*nNames];
  h_idx[pos] = *nNames;
  h_used[pos] = 1;
  (*nNames)++;
  return (*nNames) - 1;
}

static void push_left(int* start, int* L, int* seq, unsigned char* placed, int x) {
  (*start)--; seq[*start] = x; placed[x] = 1; (*L)++;
}
static void push_right(int* end, int* L, int* seq, unsigned char* placed, int x) {
  (*end)++; seq[*end] = x; placed[x] = 1; (*L)++;
}

int main(void) {
  int nbGroupes, nbAttractions;
  if (scanf("%d %d", &nbGroupes, &nbAttractions) != 2) return 0;

  // Noms des attractions
  int M = nbAttractions;
  char (*names)[128] = (char (*)[128])calloc((size_t)M, sizeof(*names));
  if (!names) return 0;

  // Hash table simple pour name->index
  // Taille: puissance de 2 >= 2*M
  int H = 1;
  while (H < (M < 2 ? 2 : 2*M)) H <<= 1;
  char** h_key = (char**)calloc((size_t)H, sizeof(char*));
  int* h_idx = (int*)malloc(sizeof(int) * (size_t)H);
  unsigned char* h_used = (unsigned char*)calloc((size_t)H, 1);
  if (!h_key || !h_idx || !h_used) { free(names); free(h_key); free(h_idx); free(h_used); return 0; }

  int nNames = 0;

  // Matrice de poids (symétrique)
  ll* W = (ll*)calloc((size_t)M * (size_t)M, sizeof(ll));
  if (!W) { free(names); free(h_key); free(h_idx); free(h_used); return 0; }

  // Lecture des groupes et accumulation des poids entre paires consécutives
  for (int g = 0; g < nbGroupes; ++g) {
    int taille, nbVisites;
    if (scanf("%d %d", &taille, &nbVisites) != 2) { free(W); free(names); free(h_key); free(h_idx); free(h_used); return 0; }
    int prevIdx = -1;
    for (int k = 0; k < nbVisites; ++k) {
      char nm[128];
      if (scanf("%127s", nm) != 1) { free(W); free(names); free(h_key); free(h_idx); free(h_used); return 0; }
      int id = get_or_add_index(nm, H, h_key, h_idx, h_used, names, M, &nNames);
      if (prevIdx >= 0 && prevIdx != id) {
        // Ajoute poids symétrique
        W[(size_t)prevIdx * M + id] += (ll)taille;
        W[(size_t)id * M + prevIdx] += (ll)taille;
      }
      prevIdx = id;
    }
  }

  // Si certaines attractions n'ont pas été vues (ne devrait pas arriver), remplir avec des noms vides
  for (int i = nNames; i < M; ++i) {
    snprintf(names[i], sizeof(names[i]), "A%d", i);
    // insérer aussi dans la table pour cohérence
    unsigned long h = djb2(names[i]);
    int mask = H - 1; int pos = (int)(h & (unsigned long)mask);
    while (h_used[pos]) pos = (pos + 1) & mask;
    h_key[pos] = names[i]; h_idx[pos] = i; h_used[pos] = 1;
    nNames = i + 1;
  }

  // Degrés pondérés
  ll* deg = (ll*)calloc((size_t)M, sizeof(ll));
  if (!deg) { free(W); free(names); free(h_key); free(h_idx); free(h_used); return 0; }
  for (int i = 0; i < M; ++i) {
    ll s = 0;
    ll* row = &W[(size_t)i * M];
    for (int j = 0; j < M; ++j) s += row[j];
    deg[i] = s;
  }

  // Trouver l'arête la plus lourde pour initialiser
  ll bestW = -1; int seedA = -1, seedB = -1;
  for (int i = 0; i < M; ++i) {
    ll* row = &W[(size_t)i * M];
    for (int j = i + 1; j < M; ++j) {
      if (row[j] > bestW) { bestW = row[j]; seedA = i; seedB = j; }
    }
  }

  // Séquence avec buffer central
  int cap = 2 * M + 4;
  int* seq = (int*)malloc(sizeof(int) * (size_t)cap);
  unsigned char* placed = (unsigned char*)calloc((size_t)M, 1);
  if (!seq || !placed) { free(seq); free(placed); free(deg); free(W); free(names); free(h_key); free(h_idx); free(h_used); return 0; }
  int L = 0; int start = M; int end = M - 1;

  if (bestW > 0) {
  push_left(&start, &L, seq, placed, seedA);
  push_right(&end, &L, seq, placed, seedB);
  } else {
    // Aucun lien fort: ordonner par degré décroissant puis nom
    int* idxs = (int*)malloc(sizeof(int) * (size_t)M);
    if (!idxs) { free(seq); free(placed); free(deg); free(W); free(names); free(h_key); free(h_idx); free(h_used); return 0; }
    for (int i=0;i<M;++i) idxs[i]=i;
    g_deg = deg; g_names = names;
    qsort(idxs,(size_t)M,sizeof(int),cmp_idx_desc);
    for (int i=0;i<M;++i) push_right(&end, &L, seq, placed, idxs[i]);
    free(idxs);
  }

  // Extension gloutonne aux extrémités
  while (L < M) {
    int leftEnd = seq[start];
    int rightEnd = seq[end];
    ll bestScore = -1; int bestNode = -1; int bestSide = 0; // 0=left,1=right
    for (int v = 0; v < M; ++v) if (!placed[v]) {
      ll wl = W[(size_t)v * M + leftEnd];
      ll wr = W[(size_t)v * M + rightEnd];
      ll sc; int side;
      if (wl >= wr) { sc = wl; side = 0; } else { sc = wr; side = 1; }
      // tie-break sur degré
      ll tie = (sc << 20) + (deg[v] & ((1<<20)-1));
      if (tie > bestScore) { bestScore = tie; bestNode = v; bestSide = side; }
    }
    if (bestNode < 0) {
      // sécurité: prendre n'importe quel non placé (par nom)
      int v = -1; for (int i=0;i<M;++i) if (!placed[i]) { if (v<0 || strcmp(names[i], names[v])<0) v=i; }
      if (v<0) break;
      push_right(&end, &L, seq, placed, v);
    } else {
      if (bestSide == 0) push_left(&start, &L, seq, placed, bestNode); else push_right(&end, &L, seq, placed, bestNode);
    }
  }

  // Impression
  for (int i = start; i <= end; ++i) {
    if (i > start) printf(" ");
    printf("%s", names[seq[i]]);
  }

  // Cleanup
  free(seq); free(placed); free(deg); free(W); free(names); free(h_key); free(h_idx); free(h_used);
  return 0;
}