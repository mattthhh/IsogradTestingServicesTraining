/*******
* Read input from STDIN
* Use: printf(...) or fprintf( stdout, ...) to output your result to stdout.
* Use: fprintf(stderr, ...);  to output debugging information to stderr.
* ***/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libisograd.h"

typedef long long ll;

typedef struct { int u, v; ll w; int visited; } Edge;

int main(void) {
  int nbDrones;
  ll battery;
  if (scanf("%d %lld", &nbDrones, &battery) != 2) return 0;

  int nbStreets, nbInter;
  if (scanf("%d %d", &nbStreets, &nbInter) != 2) return 0;

  Edge* edges = (Edge*)malloc(sizeof(Edge) * (size_t)nbStreets);
  if (!edges) return 0;

  int* deg = (int*)calloc((size_t)nbInter, sizeof(int));
  if (!deg) { free(edges); return 0; }

  // Première passe: lire et compter les degrés
  for (int i = 0; i < nbStreets; ++i) {
    int a, b; ll w;
    if (scanf("%d %d %lld", &a, &b, &w) != 3) { free(edges); free(deg); return 0; }
    edges[i].u = a; edges[i].v = b; edges[i].w = w; edges[i].visited = 0;
    if (a >= 0 && a < nbInter) deg[a]++;
    if (b >= 0 && b < nbInter) deg[b]++;
  }

  // Allouer les listes d'adjacence
  int** adj = (int**)malloc(sizeof(int*) * (size_t)nbInter);
  int* fill = (int*)calloc((size_t)nbInter, sizeof(int));
  if (!adj || !fill) { free(edges); free(deg); free(adj); free(fill); return 0; }
  for (int n = 0; n < nbInter; ++n) {
    adj[n] = (int*)malloc(sizeof(int) * (size_t)deg[n]);
    if (!adj[n]) { // nettoyage minimal
      for (int k = 0; k < n; ++k) free(adj[k]);
      free(adj); free(fill); free(edges); free(deg);
      return 0;
    }
  }

  // Deuxième passe: remplir les adjacences selon l'ordre d'entrée (indices croissants)
  for (int i = 0; i < nbStreets; ++i) {
    int a = edges[i].u, b = edges[i].v;
    adj[a][fill[a]++] = i;
    adj[b][fill[b]++] = i;
  }

  // Simulation des drones
  for (int d = 0; d < nbDrones; ++d) {
    ll rem = battery;
    int curr = 0;
    // Impression du départ
    printf("%d", curr);

    while (rem > 0) {
      int chosenEdge = -1;
      int next = -1;
      // Trouver la première rue non visitée par ordre d'entrée (min index)
      // parmi celles incidentes à curr
      int minIdx = 2147483647;
      for (int t = 0; t < deg[curr]; ++t) {
        int ei = adj[curr][t];
        if (edges[ei].visited) continue;
        if (ei < minIdx) {
          minIdx = ei;
          chosenEdge = ei;
        }
      }
      if (chosenEdge < 0) break; // plus de rue non visitée depuis curr

      // Déterminer le voisin
      int u = edges[chosenEdge].u;
      int v = edges[chosenEdge].v;
      next = (curr == u) ? v : u;

      // Parcourir la rue (autorisé si rem > 0, même si w > rem)
      edges[chosenEdge].visited = 1;
      rem -= edges[chosenEdge].w;
      curr = next;
      printf(" %d", curr);
      // Si rem <= 0, le drone s'arrêtera au prochain tour (après arrivée)
      // La boucle while sortira car condition rem > 0 échouera
    }

    if (d < nbDrones - 1) printf("\n");
  }

  // Libération mémoire
  for (int n = 0; n < nbInter; ++n) free(adj[n]);
  free(adj); free(fill); free(edges); free(deg);
  return 0;
}