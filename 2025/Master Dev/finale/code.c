/*******
* Read input from STDIN
* Use: printf(...) or fprintf( stdout, ...) to output your result to stdout.
* Use: fprintf(stderr, ...);  to output debugging information to stderr.
* ***/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "libisograd.h"

typedef struct {
  int id;
  double x, y, w;
  double r;     // distance au dépôt
  double theta; // angle autour du dépôt
  int assigned; // 0 non affecté, 1 affecté
} Stop;

static inline double dist(double x1, double y1, double x2, double y2) {
  double dx = x1 - x2, dy = y1 - y2;
  return sqrt(dx*dx + dy*dy);
}

static int cmp_angle_then_radius(const void* a, const void* b) {
  const Stop* sa = *(const Stop* const*)a;
  const Stop* sb = *(const Stop* const*)b;
  if (sa->theta < sb->theta) return -1;
  if (sa->theta > sb->theta) return 1;
  if (sa->r < sb->r) return -1;
  if (sa->r > sb->r) return 1;
  return sa->id - sb->id;
}

// Construit des tournées gloutonnes sur une liste ordonnée par angle
static void build_routes_and_print(const char vehicleType,
                   Stop** elig, int M,
                   double depotX, double depotY,
                   double maxDistance, int maxStops, double maxWeight,
                   double eps) {
  int i = 0;
  while (i < M) {
    // sauter stops déjà affectés
    while (i < M && elig[i]->assigned) i++;
    if (i >= M) break;

    // nouvelle tournée
    double routeWeight = 0.0;
    int routeStops = 0;
    double pathLen = 0.0;
    double lastX = depotX, lastY = depotY;

    // Pour collecter et imprimer au fur et à mesure
    // On bufferise dans un tableau local raisonnable (maxStops borné par N, mais on imprime en fin de route)
    int cap = (maxStops > 0 ? maxStops : 1);
    if (cap > 1024) cap = 1024; // taille initiale, réallouera si besoin
    int alloc = cap;
    int* routeIds = (int*)malloc(sizeof(int) * alloc);
    if (!routeIds) return; // fail safe

    int j = i;
    int addedAny = 0;
    for (; j < M; ++j) {
      Stop* s = elig[j];
      if (s->assigned) continue;
      double step = dist(lastX, lastY, s->x, s->y);
      int canAdd = 1;
      if ((double)(routeStops + 1) > (double)maxStops + eps) canAdd = 0;
      if (routeWeight + s->w > maxWeight + eps) canAdd = 0;
      if (pathLen + step > maxDistance + eps) canAdd = 0;
      if (!canAdd) break;

      // ajouter
      if (routeStops >= alloc) {
        alloc *= 2;
        int* tmp = (int*)realloc(routeIds, sizeof(int) * alloc);
        if (!tmp) { free(routeIds); return; }
        routeIds = tmp;
      }
      routeIds[routeStops++] = s->id;
      s->assigned = 1;
      routeWeight += s->w;
      pathLen += step;
      lastX = s->x;
      lastY = s->y;
      addedAny = 1;
    }

    if (!addedAny) {
      // Aucun n'a pu être ajouté en respectant l'ordre: tenter d'en prendre un seul atteignable plus loin dans la liste
      for (int t = j; t < M; ++t) {
        Stop* s = elig[t];
        if (s->assigned) continue;
        if (1 > maxStops + eps) continue;
        if (s->w > maxWeight + eps) continue;
        double step0 = dist(depotX, depotY, s->x, s->y);
        if (step0 > maxDistance + eps) continue;
        // on crée une tournée d'un seul stop
        printf("%c %d\n", vehicleType, s->id);
        s->assigned = 1;
        addedAny = 1;
        j = t + 1;
        break;
      }
    }

    if (routeStops > 0) {
      // imprimer la tournée
      printf("%c", vehicleType);
      for (int k = 0; k < routeStops; ++k) {
        printf(" %d", routeIds[k]);
      }
      printf("\n");
    }
    free(routeIds);

    // reprendre à j pour démarrer une nouvelle tournée (le stop j n'a pas été ajouté)
    i = j;
  }
}

int main(void) {
  const double eps = 1e-6;

  // Lecture des caractéristiques vélo
  double bikeProductionCost, bikeMaxDistance, bikeMaxWeight, bikeConsoKm;
  int bikeMaxStops;
  if (scanf("%lf %lf %d %lf %lf", &bikeProductionCost, &bikeMaxDistance, &bikeMaxStops, &bikeMaxWeight, &bikeConsoKm) != 5) {
    return 0;
  }

  // Lecture des caractéristiques camionnette
  double vanProductionCost, vanMaxDistance, vanMaxWeight, vanConsoKm;
  int vanMaxStops;
  if (scanf("%lf %lf %d %lf %lf", &vanProductionCost, &vanMaxDistance, &vanMaxStops, &vanMaxWeight, &vanConsoKm) != 5) {
    return 0;
  }

  int N;
  if (scanf("%d", &N) != 1) {
    return 0;
  }

  Stop* stops = (Stop*)malloc(sizeof(Stop) * (size_t)N);
  if (!stops) return 0;

  double sumX = 0.0, sumY = 0.0;
  for (int i = 0; i < N; ++i) {
    double x, y, w;
    if (scanf("%lf %lf %lf", &x, &y, &w) != 3) { free(stops); return 0; }
    stops[i].id = i;
    stops[i].x = x;
    stops[i].y = y;
    stops[i].w = w;
    stops[i].r = 0.0;
    stops[i].theta = 0.0;
    stops[i].assigned = 0;
    sumX += x;
    sumY += y;
  }

  // Choix du dépôt au centroïde
  double depotX = (N > 0) ? (sumX / (double)N) : 0.0;
  double depotY = (N > 0) ? (sumY / (double)N) : 0.0;

  // Calcul r et angle pour chaque stop
  for (int i = 0; i < N; ++i) {
    double dx = stops[i].x - depotX;
    double dy = stops[i].y - depotY;
    stops[i].r = sqrt(dx*dx + dy*dy);
    stops[i].theta = atan2(dy, dx);
  }

  // Construire la liste éligible vélo (individuellement atteignable et poids ok)
  Stop** bikeList = (Stop**)malloc(sizeof(Stop*) * (size_t)N);
  int bikeCount = 0;
  if (!bikeList) { free(stops); return 0; }
  for (int i = 0; i < N; ++i) {
    if (stops[i].w <= bikeMaxWeight + eps && stops[i].r <= bikeMaxDistance + eps && bikeMaxStops >= 1) {
      bikeList[bikeCount++] = &stops[i];
    }
  }
  qsort(bikeList, (size_t)bikeCount, sizeof(Stop*), cmp_angle_then_radius);

  // Construire les tournées vélo (prioritaire car moins coûteux)
  if (bikeCount > 0) {
    printf("%.6f %.6f\n", depotX, depotY);
    build_routes_and_print('V', bikeList, bikeCount, depotX, depotY,
                 bikeMaxDistance, bikeMaxStops, bikeMaxWeight, eps);
  } else {
    // On imprimera les coordonnées du dépôt avant la première tournée (camionnette)
    printf("%.6f %.6f\n", depotX, depotY);
  }

  free(bikeList);

  // Construire la liste restante pour camionnettes
  Stop** vanList = (Stop**)malloc(sizeof(Stop*) * (size_t)N);
  int vanCount = 0;
  if (!vanList) { free(stops); return 0; }
  for (int i = 0; i < N; ++i) {
    if (!stops[i].assigned) {
      // Pré-filtrage: atteignable seul et poids ok pour éviter blocages
      if (stops[i].w <= vanMaxWeight + eps && stops[i].r <= vanMaxDistance + eps && vanMaxStops >= 1) {
        vanList[vanCount++] = &stops[i];
      }
    }
  }

  if (vanCount > 0) {
    qsort(vanList, (size_t)vanCount, sizeof(Stop*), cmp_angle_then_radius);
    build_routes_and_print('C', vanList, vanCount, depotX, depotY,
                 vanMaxDistance, vanMaxStops, vanMaxWeight, eps);
  }

  free(vanList);
  free(stops);
  return 0;
}