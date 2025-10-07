/*******
* Read input from STDIN
* Use: printf(...) or fprintf( stdout, ...) to output your result to stdout.
* Use: fprintf(stderr, ...);  to output debugging information to stderr.
* ***/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libisograd.h"
#include <limits.h>

#define MAX_TYPES_PER_CENTER 10

typedef struct {
  int x;
  int y;
  int type_count;
  int type_ids[MAX_TYPES_PER_CENTER];
  int type_qty[MAX_TYPES_PER_CENTER];
  int total_remaining;
} Center;

typedef struct {
  int x;
  int y;
  int prefs[3];
} Student;

typedef struct {
  int center_idx;
  int type_idx;
} TypeCenter;

typedef struct {
  int type_id;
  int count;
  int capacity;
  TypeCenter *centers;
} TypeEntry;

#define MAX_PREF_CANDIDATES 12

typedef struct {
  int dist;
  short center_idx;
  short type_idx;
} PrefCandidate;

typedef struct {
  int count;
  PrefCandidate options[MAX_PREF_CANDIDATES];
} PrefCandidateList;

typedef struct {
  int student_idx;
  unsigned short pref_rank;
  unsigned short dist;
} SeatCandidate;

typedef struct {
  int count;
  int capacity;
  SeatCandidate *items;
} SeatCandidateList;

typedef struct {
  long long metric;
  unsigned short dist;
  unsigned short pref_rank;
  int student_idx;
  short center_idx;
  short type_idx;
} GlobalCandidate;

typedef struct {
  int student_idx;
  int option_count;
  int min_dist;
} StudentPriority;

static int compare_student_priority(const void *a, const void *b) {
  const StudentPriority *sa = (const StudentPriority *)a;
  const StudentPriority *sb = (const StudentPriority *)b;
  // Fewer options = higher priority (constrained students first)
  if (sa->option_count < sb->option_count) {
    return -1;
  }
  if (sa->option_count > sb->option_count) {
    return 1;
  }
  // Tie-break: closer distance = higher priority
  if (sa->min_dist < sb->min_dist) {
    return -1;
  }
  if (sa->min_dist > sb->min_dist) {
    return 1;
  }
  return 0;
}

static int manhattan_distance(int ax, int ay, int bx, int by) {
  int dx = ax - bx;
  if (dx < 0) {
    dx = -dx;
  }
  int dy = ay - by;
  if (dy < 0) {
    dy = -dy;
  }
  return dx + dy;
}

static TypeEntry *ensure_type_entry(TypeEntry **entries, int *count, int *capacity, int type_id) {
  for (int i = 0; i < *count; i++) {
    if ((*entries)[i].type_id == type_id) {
      return &((*entries)[i]);
    }
  }

  if (*count == *capacity) {
    int new_capacity = (*capacity == 0) ? 16 : (*capacity * 2);
    TypeEntry *resized = (TypeEntry *)realloc(*entries, sizeof(TypeEntry) * new_capacity);
    if (!resized) {
      return NULL;
    }
    *entries = resized;
    *capacity = new_capacity;
  }

  TypeEntry *entry = &((*entries)[*count]);
  entry->type_id = type_id;
  entry->count = 0;
  entry->capacity = 4;
  entry->centers = (TypeCenter *)malloc(sizeof(TypeCenter) * entry->capacity);
  if (!entry->centers) {
    return NULL;
  }
  (*count)++;
  return entry;
}

static int append_type_center(TypeEntry *entry, int center_idx, int type_idx) {
  if (!entry) {
    return 0;
  }
  if (entry->count == entry->capacity) {
    int new_capacity = entry->capacity * 2;
    TypeCenter *resized = (TypeCenter *)realloc(entry->centers, sizeof(TypeCenter) * new_capacity);
    if (!resized) {
      return 0;
    }
    entry->centers = resized;
    entry->capacity = new_capacity;
  }
  entry->centers[entry->count].center_idx = center_idx;
  entry->centers[entry->count].type_idx = type_idx;
  entry->count++;
  return 1;
}

static int compare_type_entries(const void *a, const void *b) {
  const TypeEntry *ea = (const TypeEntry *)a;
  const TypeEntry *eb = (const TypeEntry *)b;
  if (ea->type_id < eb->type_id) {
    return -1;
  }
  if (ea->type_id > eb->type_id) {
    return 1;
  }
  return 0;
}

static TypeEntry *find_type_entry(TypeEntry *entries, int count, int type_id) {
  int left = 0;
  int right = count - 1;
  while (left <= right) {
    int mid = (left + right) / 2;
    if (entries[mid].type_id == type_id) {
      return &entries[mid];
    }
    if (entries[mid].type_id < type_id) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return NULL;
}

static void add_pref_candidate(PrefCandidateList *list, int dist, int center_idx, int type_idx) {
  PrefCandidate candidate;
  candidate.dist = dist;
  candidate.center_idx = (short)center_idx;
  candidate.type_idx = (short)type_idx;

  if (list->count < MAX_PREF_CANDIDATES) {
    int pos = list->count;
    while (pos > 0) {
      PrefCandidate *prev = &list->options[pos - 1];
      if (prev->dist < candidate.dist ||
          (prev->dist == candidate.dist && prev->center_idx <= candidate.center_idx)) {
        break;
      }
      list->options[pos] = *prev;
      pos--;
    }
    list->options[pos] = candidate;
    list->count++;
    return;
  }

  PrefCandidate *last = &list->options[MAX_PREF_CANDIDATES - 1];
  if (last->dist < candidate.dist ||
      (last->dist == candidate.dist && last->center_idx <= candidate.center_idx)) {
    return;
  }

  int pos = MAX_PREF_CANDIDATES - 1;
  while (pos > 0) {
    PrefCandidate *prev = &list->options[pos - 1];
    if (prev->dist < candidate.dist ||
        (prev->dist == candidate.dist && prev->center_idx <= candidate.center_idx)) {
      break;
    }
    list->options[pos] = *prev;
    pos--;
  }
  list->options[pos] = candidate;
}

static int append_seat_candidate(SeatCandidateList *list, int student_idx, int pref_rank, int dist) {
  if (!list) {
    return 0;
  }
  if (list->count == list->capacity) {
    int new_capacity = (list->capacity == 0) ? 8 : (list->capacity * 2);
    SeatCandidate *resized = (SeatCandidate *)realloc(list->items, sizeof(SeatCandidate) * new_capacity);
    if (!resized) {
      return 0;
    }
    list->items = resized;
    list->capacity = new_capacity;
  }
  SeatCandidate *candidate = &list->items[list->count++];
  candidate->student_idx = student_idx;
  candidate->pref_rank = (unsigned short)pref_rank;
  candidate->dist = (unsigned short)dist;
  return 1;
}

int main() {
  int d, p, e;
  if (scanf("%d %d %d", &d, &p, &e) != 3) {
    return 0;
  }

  Center *centers = (Center *)malloc(sizeof(Center) * d);
  Student *students = (Student *)malloc(sizeof(Student) * e);
  int *assignments = (int *)malloc(sizeof(int) * e);
  int *reserved_type = (int *)malloc(sizeof(int) * e);
  PrefCandidateList *pref_lists = NULL;
  TypeEntry *type_entries = NULL;
  int type_entry_count = 0;
  int type_entry_capacity = 0;
  SeatCandidateList *seat_lists = NULL;
  int *remaining_slots = NULL;
  int *unassigned_students = NULL;
  GlobalCandidate *global_candidates = NULL;

  if (!centers || !students || !assignments || !reserved_type) {
    goto cleanup;
  }

  for (int i = 0; i < d; i++) {
    int stock_slots;
    if (scanf("%d %d %d", &centers[i].x, &centers[i].y, &stock_slots) != 3) {
      goto cleanup;
    }
    centers[i].type_count = stock_slots;
    centers[i].total_remaining = 0;

    for (int j = 0; j < stock_slots; j++) {
      if (scanf("%d", &centers[i].type_ids[j]) != 1) {
        goto cleanup;
      }
    }
    for (int j = 0; j < stock_slots; j++) {
      if (scanf("%d", &centers[i].type_qty[j]) != 1) {
        goto cleanup;
      }
      centers[i].total_remaining += centers[i].type_qty[j];
    }

    for (int j = 0; j < stock_slots; j++) {
      TypeEntry *entry = ensure_type_entry(&type_entries, &type_entry_count, &type_entry_capacity,
                                           centers[i].type_ids[j]);
      if (!entry || !append_type_center(entry, i, j)) {
        goto cleanup;
      }
    }
  }

  if (type_entry_count > 1) {
    qsort(type_entries, type_entry_count, sizeof(TypeEntry), compare_type_entries);
  }

  for (int i = 0; i < e; i++) {
    if (scanf("%d %d", &students[i].x, &students[i].y) != 2) {
      goto cleanup;
    }
    if (scanf("%d %d %d", &students[i].prefs[0], &students[i].prefs[1], &students[i].prefs[2]) != 3) {
      goto cleanup;
    }
  }

  pref_lists = (PrefCandidateList *)malloc(sizeof(PrefCandidateList) * (size_t)e * 3u);
  if (!pref_lists) {
    goto cleanup;
  }
  memset(pref_lists, 0, sizeof(PrefCandidateList) * (size_t)e * 3u);

  seat_lists = (SeatCandidateList *)calloc((size_t)d * MAX_TYPES_PER_CENTER, sizeof(SeatCandidateList));
  if (!seat_lists) {
    goto cleanup;
  }

  for (int student_idx = 0; student_idx < e; student_idx++) {
    for (int pref_idx = 0; pref_idx < 3; pref_idx++) {
      PrefCandidateList *list = &pref_lists[student_idx * 3 + pref_idx];
      int desired_type = students[student_idx].prefs[pref_idx];
      TypeEntry *entry = find_type_entry(type_entries, type_entry_count, desired_type);
      if (!entry) {
        continue;
      }
      for (int k = 0; k < entry->count; k++) {
        int center_idx = entry->centers[k].center_idx;
        int type_idx = entry->centers[k].type_idx;
        if (centers[center_idx].type_qty[type_idx] <= 0) {
          continue;
        }
        int dist = manhattan_distance(students[student_idx].x, students[student_idx].y,
                                      centers[center_idx].x, centers[center_idx].y);
        add_pref_candidate(list, dist, center_idx, type_idx);
        int seat_index = center_idx * MAX_TYPES_PER_CENTER + type_idx;
        if (!append_seat_candidate(&seat_lists[seat_index], student_idx, pref_idx + 1, dist)) {
          goto cleanup;
        }
      }
    }
  }

  for (int i = 0; i < e; i++) {
    assignments[i] = -1;
    reserved_type[i] = -1;
  }

  remaining_slots = (int *)malloc(sizeof(int) * (size_t)d * MAX_TYPES_PER_CENTER);
  if (!remaining_slots) {
    goto cleanup;
  }
  for (int center_idx = 0; center_idx < d; center_idx++) {
    for (int type_idx = 0; type_idx < centers[center_idx].type_count; type_idx++) {
      remaining_slots[center_idx * MAX_TYPES_PER_CENTER + type_idx] = centers[center_idx].type_qty[type_idx];
    }
    for (int type_idx = centers[center_idx].type_count; type_idx < MAX_TYPES_PER_CENTER; type_idx++) {
      remaining_slots[center_idx * MAX_TYPES_PER_CENTER + type_idx] = 0;
    }
  }

  // Priority-based allocation with dynamic re-prioritization
  StudentPriority *priorities = (StudentPriority *)malloc(sizeof(StudentPriority) * e);
  if (!priorities) {
    goto cleanup;
  }
  
  for (int pref_wave = 0; pref_wave < 3; pref_wave++) {
    // Keep assigning until no more students can be assigned in this wave
    int assignments_made = 1;
    while (assignments_made > 0) {
      assignments_made = 0;
      int unassigned_count = 0;
      
      // Build priority list for unassigned students with CURRENT availability
      for (int student_idx = 0; student_idx < e; student_idx++) {
        if (assignments[student_idx] != -1) {
          continue;
        }
        
        PrefCandidateList *list = &pref_lists[student_idx * 3 + pref_wave];
        if (list->count == 0) {
          continue;
        }
        
        // Count CURRENTLY available options
        int available_count = 0;
        int first_dist = INT_MAX;
        for (int i = 0; i < list->count; i++) {
          int center_idx = list->options[i].center_idx;
          int type_idx = list->options[i].type_idx;
          int slot_index = center_idx * MAX_TYPES_PER_CENTER + type_idx;
          if (remaining_slots[slot_index] > 0) {
            available_count++;
            if (first_dist == INT_MAX) {
              first_dist = list->options[i].dist;
            }
          }
        }
        
        if (available_count > 0) {
          priorities[unassigned_count].student_idx = student_idx;
          priorities[unassigned_count].option_count = available_count;
          priorities[unassigned_count].min_dist = first_dist;
          unassigned_count++;
        }
      }
      
      if (unassigned_count == 0) {
        break;
      }
      
      // Sort by priority (fewer options first, then closer)
      if (unassigned_count > 1) {
        qsort(priorities, unassigned_count, sizeof(StudentPriority), compare_student_priority);
      }
      
      // Assign ONLY the most constrained student (first in sorted list)
      for (int i = 0; i < unassigned_count && assignments_made == 0; i++) {
        int student_idx = priorities[i].student_idx;
        
        if (assignments[student_idx] != -1) {
          continue;
        }
        
        PrefCandidateList *list = &pref_lists[student_idx * 3 + pref_wave];
        
        // Assign to first available center
        for (int j = 0; j < list->count; j++) {
          int center_idx = list->options[j].center_idx;
          int type_idx = list->options[j].type_idx;
          int slot_index = center_idx * MAX_TYPES_PER_CENTER + type_idx;
          
          if (remaining_slots[slot_index] > 0) {
            assignments[student_idx] = center_idx;
            reserved_type[student_idx] = type_idx;
            remaining_slots[slot_index]--;
            assignments_made = 1;
            break;
          }
        }
      }
    }
  }
  
  free(priorities);


  int unassigned_count = 0;
  for (int i = 0; i < e; i++) {
    if (assignments[i] == -1) {
      unassigned_count++;
    }
  }

  if (unassigned_count > 0) {
    unassigned_students = (int *)malloc(sizeof(int) * (size_t)unassigned_count);
    if (!unassigned_students) {
      goto cleanup;
    }
    int cursor = 0;
    for (int i = 0; i < e; i++) {
      if (assignments[i] == -1) {
        unassigned_students[cursor++] = i;
      }
    }

    for (int u = 0; u < unassigned_count; u++) {
      int student_idx = unassigned_students[u];
      int best_center = -1;
      int best_type_idx = -1;
      long long best_metric = LLONG_MAX;
      int best_dist = INT_MAX;
      int best_pref_rank = 4;
      for (int center_idx = 0; center_idx < d; center_idx++) {
        for (int type_idx = 0; type_idx < centers[center_idx].type_count; type_idx++) {
          int *slot_ptr = &remaining_slots[center_idx * MAX_TYPES_PER_CENTER + type_idx];
          if (*slot_ptr <= 0) {
            continue;
          }
          int dist = manhattan_distance(students[student_idx].x, students[student_idx].y,
                                        centers[center_idx].x, centers[center_idx].y);
          int pref_rank = 4;
          for (int pref = 0; pref < 3; pref++) {
            if (students[student_idx].prefs[pref] == centers[center_idx].type_ids[type_idx]) {
              pref_rank = pref + 1;
              break;
            }
          }
          long long metric = ((long long)pref_rank * pref_rank) * (long long)(dist + 1);
          if (metric < best_metric ||
              (metric == best_metric && (pref_rank < best_pref_rank ||
                                        (pref_rank == best_pref_rank && (dist < best_dist ||
                                                                         (dist == best_dist && (best_center < 0 || center_idx < best_center))))))) {
            best_metric = metric;
            best_center = center_idx;
            best_type_idx = type_idx;
            best_dist = dist;
            best_pref_rank = pref_rank;
          }
        }
      }

      if (best_center < 0) {
        best_center = 0;
        best_type_idx = 0;
      }

      assignments[student_idx] = best_center;
      if (best_type_idx < 0 || best_type_idx >= centers[best_center].type_count) {
        best_type_idx = 0;
      }
      reserved_type[student_idx] = best_type_idx;
      if (best_center < d) {
        int slot_index = best_center * MAX_TYPES_PER_CENTER + best_type_idx;
        if (remaining_slots[slot_index] > 0) {
          remaining_slots[slot_index]--;
        } else {
          for (int type_idx = 0; type_idx < centers[best_center].type_count; type_idx++) {
            int idx = best_center * MAX_TYPES_PER_CENTER + type_idx;
            if (remaining_slots[idx] > 0) {
              remaining_slots[idx]--;
              reserved_type[student_idx] = type_idx;
              break;
            }
          }
        }
      }
    }
  }

  for (int i = 0; i < e; i++) {
    if (i > 0) {
      printf(" ");
    }
    printf("%d", assignments[i]);
  }

cleanup:
  if (type_entries) {
    for (int i = 0; i < type_entry_count; i++) {
      free(type_entries[i].centers);
    }
    free(type_entries);
  }
  if (seat_lists) {
    for (int i = 0; i < d * MAX_TYPES_PER_CENTER; i++) {
      free(seat_lists[i].items);
    }
    free(seat_lists);
  }
  free(remaining_slots);
  free(unassigned_students);
  free(pref_lists);
  free(centers);
  free(students);
  free(assignments);
  free(reserved_type);
  free(global_candidates);

  return 0;
}