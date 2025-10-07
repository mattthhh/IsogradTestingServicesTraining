/*******
* Read input from STDIN
* Use: printf(...) or fprintf( stdout, ...) to output your result to stdout.
* Use: fprintf(stderr, ...);  to output debugging information to stderr.
* ***/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "libisograd.h"

typedef long long ll;

typedef struct { int u, v; ll w; int used; } Edge;

typedef struct { int to; int ei; } Adj; // neighbor node and edge index

// ---------- Min-heap for Dijkstra ----------
typedef struct { int v; ll d; } HeapNode;

typedef struct {
  HeapNode* a; int size; int cap;
  int* pos; // pos[v] = index in heap or -1
} MinHeap;

static void heap_swap(MinHeap* h, int i, int j) {
  HeapNode t = h->a[i]; h->a[i] = h->a[j]; h->a[j] = t;
  h->pos[h->a[i].v] = i;
  h->pos[h->a[j].v] = j;
}
static void heap_up(MinHeap* h, int i) {
  while (i > 0) {
    int p = (i - 1) / 2;
    if (h->a[p].d <= h->a[i].d) break;
    heap_swap(h, i, p); i = p;
  }
}
static void heap_down(MinHeap* h, int i) {
  int n = h->size;
  while (1) {
    int l = 2*i + 1, r = l + 1, m = i;
    if (l < n && h->a[l].d < h->a[m].d) m = l;
    if (r < n && h->a[r].d < h->a[m].d) m = r;
    if (m == i) break;
    heap_swap(h, i, m); i = m;
  }
}
static void heap_init(MinHeap* h, int n, int* posBuf) {
  h->a = (HeapNode*)malloc(sizeof(HeapNode) * (size_t)(n>1?n:1));
  h->size = 0; h->cap = (n>1?n:1); h->pos = posBuf;
  for (int i=0;i<n;i++) h->pos[i] = -1;
}
static void heap_free(MinHeap* h) { free(h->a); }
static void heap_reserve(MinHeap* h) {
  if (h->size == h->cap) {
    h->cap = h->cap*2 + 1;
    h->a = (HeapNode*)realloc(h->a, sizeof(HeapNode) * (size_t)h->cap);
  }
}
static void heap_push(MinHeap* h, int v, ll d) {
  heap_reserve(h);
  int i = h->size++;
  h->a[i].v = v; h->a[i].d = d; h->pos[v] = i; heap_up(h, i);
}
static HeapNode heap_pop(MinHeap* h) {
  HeapNode root = h->a[0];
  h->pos[root.v] = -1;
  h->size--;
  if (h->size > 0) { h->a[0] = h->a[h->size]; h->pos[h->a[0].v] = 0; heap_down(h, 0); }
  return root;
}
static void heap_decrease(MinHeap* h, int v, ll nd) {
  int i = h->pos[v];
  if (i < 0) { heap_push(h, v, nd); return; }
  if (nd >= h->a[i].d) return;
  h->a[i].d = nd; heap_up(h, i);
}

static const ll INFLL = (ll)4e18;

// Dijkstra from source s
static void dijkstra(int N, Adj** adj, int* deg, Edge* edges, int s, ll* dist, int* prev) {
  for (int i=0;i<N;i++){ dist[i]=INFLL; prev[i]=-1; }
  int* pos = (int*)malloc(sizeof(int)* (size_t)N);
  MinHeap heap; heap_init(&heap, N, pos);
  dist[s]=0; heap_push(&heap, s, 0);
  while (heap.size>0) {
    HeapNode hn = heap_pop(&heap);
    int u = hn.v; ll du = hn.d;
    if (du!=dist[u]) continue; // stale
    for (int k=0;k<deg[u];k++){
      int ei = adj[u][k].ei;
      int v = adj[u][k].to;
      ll w = edges[ei].w;
      if (du + w < dist[v]) {
        dist[v] = du + w; prev[v] = u; heap_decrease(&heap, v, dist[v]);
      }
    }
  }
  heap_free(&heap);
  free(pos);
}

int main(void) {
  int nbDrones; ll battery;
  if (scanf("%d %lld", &nbDrones, &battery) != 2) return 0;
  int nbStreets, nbInter;
  if (scanf("%d %d", &nbStreets, &nbInter) != 2) return 0;

  Edge* edges = (Edge*)malloc(sizeof(Edge) * (size_t)nbStreets);
  if (!edges) return 0;
  int* deg = (int*)calloc((size_t)nbInter, sizeof(int));
  if (!deg) { free(edges); return 0; }

  for (int i=0;i<nbStreets;i++){
    int a,b; ll w;
    if (scanf("%d %d %lld", &a, &b, &w) != 3) { free(edges); free(deg); return 0; }
    edges[i].u=a; edges[i].v=b; edges[i].w=w; edges[i].used=0;
    deg[a]++; deg[b]++;
  }

  Adj** adj = (Adj**)malloc(sizeof(Adj*) * (size_t)nbInter);
  int* fill = (int*)calloc((size_t)nbInter, sizeof(int));
  if (!adj || !fill) { free(edges); free(deg); free(adj); free(fill); return 0; }
  for (int n=0;n<nbInter;n++){
    adj[n] = (Adj*)malloc(sizeof(Adj) * (size_t)deg[n]);
    if (!adj[n]){ for(int k=0;k<n;k++) free(adj[k]); free(adj); free(fill); free(edges); free(deg); return 0; }
  }
  for (int i=0;i<nbStreets;i++){
    int a=edges[i].u, b=edges[i].v;
    adj[a][fill[a]].to=b; adj[a][fill[a]].ei=i; fill[a]++;
    adj[b][fill[b]].to=a; adj[b][fill[b]].ei=i; fill[b]++;
  }
  free(fill);

  ll* dist = (ll*)malloc(sizeof(ll) * (size_t)nbInter);
  int* prev = (int*)malloc(sizeof(int) * (size_t)nbInter);
  if (!dist || !prev) { for(int n=0;n<nbInter;n++) free(adj[n]); free(adj); free(edges); free(deg); free(dist); free(prev); return 0; }

  for (int d=0; d<nbDrones; ++d) {
    ll rem = battery;
    int curr = 0;
    // start line
    printf("0");

    while (rem > 0) {
      // shortest paths from curr
      dijkstra(nbInter, adj, deg, edges, curr, dist, prev);

      // choose best unvisited edge by ratio gain/(reach+gain)
      int bestEi = -1; int startAtU = 1; ll bestReach = 0; double bestScore = -1.0; // score in [0,1]
      for (int ei=0; ei<nbStreets; ++ei) {
        if (edges[ei].used) continue;
        int u = edges[ei].u, v = edges[ei].v;
        ll du = dist[u], dv = dist[v];
        if (du==INFLL && dv==INFLL) continue;
        int useU = (du <= dv);
        ll reach = useU ? du : dv;
        if (reach==INFLL) continue;
        if (rem - reach <= 0) continue; // besoin d'une batterie strictement positive avant de démarrer la rue
        double ratio = (double)edges[ei].w / (double)(reach + edges[ei].w);
        // favoriser aussi les rues plus longues en léger tie-break
        double tie = ratio + 1e-12 * (double)edges[ei].w;
        if (tie > bestScore) { bestScore = tie; bestEi = ei; startAtU = useU; bestReach = reach; }
      }

      if (bestEi < 0) break;

      // reconstruct path to chosen endpoint
      int target = startAtU ? edges[bestEi].u : edges[bestEi].v;
      // build stack
      int stackCap = 32, stackSz = 0;
      int* stack = (int*)malloc(sizeof(int)* (size_t)stackCap);
      int vtx = target;
      while (vtx != -1 && vtx != curr) {
        if (stackSz >= stackCap) { stackCap*=2; stack = (int*)realloc(stack, sizeof(int)*(size_t)stackCap); }
        stack[stackSz++] = vtx;
        vtx = prev[vtx];
      }
      // walk forward
      for (int k = stackSz-1; k >= 0; --k) {
        printf(" %d", stack[k]);
      }
      free(stack);
      rem -= bestReach;
      curr = target;

      // traverse the edge to the other endpoint
      int other = startAtU ? edges[bestEi].v : edges[bestEi].u;
      printf(" %d", other);
      rem -= edges[bestEi].w; // peut devenir négatif après l'arrivée
      edges[bestEi].used = 1;
      curr = other;

      if (rem <= 0) break;
    }

    if (d < nbDrones - 1) printf("\n");
  }

  // cleanup
  for (int n=0;n<nbInter;n++) free(adj[n]);
  free(adj); free(edges); free(deg); free(dist); free(prev);
  return 0;
}