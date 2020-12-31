#include <config.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "davenport/network.h"
#include "davenport/preference_graph.h"
#include "davenport/davenport.h"
#include "davenport/aggregate_solution.h"

#define MAX_INPUT_LINE 2048
#define MAX_LABEL 64

typedef struct Tokenz {
  char *remainder;
  char *label;
  char *raw_label;
  char *labels;
  int type;
} Tokenz;

#define DELIMS ">="
#define TOKEN_LABEL 1
#define TOKEN_PREF 2
#define TOKEN_SAME 3
#define TOKEN_DONE 4

void next_token(Tokenz *tkz) {
  if (*tkz->remainder == '\0') {
    tkz->type = TOKEN_DONE;
  } else {
    int label_len = strcspn(tkz->remainder, DELIMS);
    if (label_len == 0) {
      switch (*tkz->remainder) {
        case '>': {
          tkz->type = TOKEN_PREF;
          break;
        }
        case '=': {
          tkz->type = TOKEN_SAME;
          break;
        }
        default: {
          printf("Error parsing at %s\n", tkz->remainder);
          tkz->type = TOKEN_DONE;
          break;
        }
      }
      tkz->remainder += strspn(tkz->remainder, DELIMS);
    } else {
      tkz->type = TOKEN_LABEL;
      int copy_ct = label_len < MAX_LABEL ? label_len : MAX_LABEL - 1;
      strncpy(tkz->raw_label, tkz->remainder, copy_ct);
      tkz->raw_label[copy_ct] = '\0';
      char *cur = tkz->raw_label;
      while (isspace(*cur) && 0 < copy_ct) { ++cur; --copy_ct; }
      strncpy(tkz->label, cur, copy_ct);
      cur = tkz->label + copy_ct;
      do {
        *cur = '\0';
        --cur;
        --copy_ct;
      } while (isspace(*cur) && 0 < copy_ct);
      tkz->remainder += label_len;
      if (strlen(tkz->label) == 0) {
        printf("Blank label given.\n");
        tkz->type = TOKEN_DONE;
      }
    }
  }
}

Tokenz *make_tokenz() {
  Tokenz *tkz = (Tokenz *)calloc(1, sizeof(Tokenz));
  tkz->label = (char *)calloc(MAX_LABEL, '\0');
  tkz->raw_label = (char *)calloc(MAX_LABEL, '\0');
  return tkz;
}

void free_tokenz(Tokenz *tkz) {
  free(tkz->label);
  free(tkz->raw_label);
  if (tkz->labels != NULL) free(tkz->labels);
  free(tkz);
}

void start_tokenz(Tokenz *tkz, char *input_line) {
  tkz->remainder = input_line;
  next_token(tkz);
}

typedef struct _PreferenceGraph {
  char *input_line;
  int node_ct;
  int *graph;
  int *rankings;
  Tokenz *tkz;
} PreferenceGraph;

void initialize_from_first_line(PreferenceGraph *pg) {
  unsigned int ct = 0;
  char *str = pg->input_line;
  do {
     str = strpbrk(str, DELIMS);
     if (str) str += strspn(str, DELIMS);
     ++ct;
  } while(str && *str);
  pg->node_ct = ct;
  pg->graph = edge_array_calloc(pg->node_ct);
  pg->rankings = (int *)calloc(pg->node_ct, sizeof(int));
}

int label_index(Tokenz *tkz) {
  int idx = 0;
  if (tkz->labels == NULL) {
    tkz->labels = strdup(tkz->label);
    printf("Label %s has index %d\n", tkz->label, idx);
  } else {
    char *cur_label = tkz->labels;
    int label_len = strcspn(cur_label, DELIMS);
    while (strncmp(cur_label, tkz->label, label_len) != 0 && 0 < label_len) {
      ++idx;
      cur_label += label_len;
      ++cur_label;
      label_len = strcspn(cur_label, DELIMS);
    }
    if (0 == label_len) {
      int labels_len = strlen(tkz->labels);
      char *new_labels = calloc(labels_len + strlen(tkz->label) + 2, sizeof(char));
      strcpy(new_labels, tkz->labels);
      new_labels[labels_len] = DELIMS[0];
      strcpy(new_labels + labels_len + 1, tkz->label);
      free(tkz->labels);
      tkz->labels = new_labels;
      printf("Label %s has index %d\n", tkz->label, idx);
    }
  }
  return idx;
}

char *tokenz_lookup_label(Tokenz *tkz, int index) {
    int idx = 0;
    char *cur_label = tkz->labels;
    while (idx < index) {
      int label_len = strcspn(cur_label, DELIMS);
      cur_label += label_len;
      ++cur_label;
      ++idx;
    }
    int label_len = strcspn(cur_label, DELIMS);
    strncpy(tkz->label, cur_label, label_len);
    tkz->label[label_len] = '\0';
    return tkz->label;
}

char *lookup_label(PreferenceGraph *pg, int index) {
  return tokenz_lookup_label(pg->tkz, index);
}

void decode_solution(PreferenceGraph *pg, int *solution) {
  for (int rank = 1; rank <= pg->node_ct; ++rank) {
    printf("At rank %4d: ", rank);
    int have_one = 0;
    for (int idx = 0; idx < pg->node_ct; ++idx) {
      if (solution[idx] == rank) {
        if (have_one) {
          printf(" = ");
        } else {
          have_one = 1;
        }
        printf("%s", lookup_label(pg, idx));
      }
    }
    printf("\n");
  }
}

void process_line(PreferenceGraph *pg) {
  int rank = 1;
  Tokenz *tkz = pg->tkz;
  start_tokenz(tkz, pg->input_line);
  while (tkz->type != TOKEN_DONE) {
    switch (tkz->type) {
      case TOKEN_LABEL: {
        int idx = label_index(tkz);
        if (idx < pg->node_ct) {
          pg->rankings[idx] = rank;
        } else {
          printf("Unknown label \"%s\"\n", tkz->label);
        }
        break;
      }
      case TOKEN_PREF: {
        ++rank;
        break;
      }
      case TOKEN_SAME:
        break;
    }
    next_token(tkz);
  }
  preference_graph_add_preference(pg->graph, pg->rankings, pg->node_ct);
}

PreferenceGraph * pg_populate(FILE *input) {
  PreferenceGraph *pg = (PreferenceGraph *)calloc(1, sizeof(PreferenceGraph));
  pg->input_line = (char *)calloc(MAX_INPUT_LINE, sizeof(char));
  char *in = fgets(pg->input_line, MAX_INPUT_LINE, input);
  if (in != NULL) {
    initialize_from_first_line(pg);
    pg->tkz = make_tokenz();
    do {
      process_line(pg);
      in = fgets(pg->input_line, MAX_INPUT_LINE, input);
    } while (in != NULL);
  } else {
    printf("Empty file\n");
    free(pg->input_line);
    free(pg);
    pg = NULL;
  }
  return pg;
}

void pg_free(PreferenceGraph *pg) {
  if (pg != NULL) {
    free(pg->graph);
    free(pg->input_line);
    free_tokenz(pg->tkz);
    free(pg);
  }
}

typedef struct {
  int trial_ct;
  AggregateSolution *ag;
} SolutionTracker;

SolutionTracker *solution_tracker_create(int node_ct) {
  SolutionTracker *st = (SolutionTracker*)calloc(1, sizeof(SolutionTracker));
  st->trial_ct = 0;
  st->ag = aggregate_solution_create(node_ct);
  return st;
}

void solution_tracker_destroy(SolutionTracker *st) {
  aggregate_solution_destroy(st->ag);
  free(st);
}

void solution_tracker_add_solution(void *context, int *sol, int node_ct,
  int disagreement_ct)
{
  SolutionTracker *st = (SolutionTracker *)context;
  printf("Solution with %d disagreements:\n", disagreement_ct);
  node_array_print(sol, node_ct);
  ++st->trial_ct;
  aggregate_solution_add_solution(st->ag, sol, node_ct, disagreement_ct);
}

void solution_tracker_report_solution(SolutionTracker *st, PreferenceGraph *pg)
{
  int *ranking = aggregate_solution_ranking(st->ag);
  printf("%d viable solutions investigated.\n", st->trial_ct);
  node_array_printl(ranking, pg->node_ct, "Aggregate partial order solution");
  decode_solution(pg, ranking);
}

void compute_solution(PreferenceGraph *pg) {
  int node_ct = pg->node_ct;
  int *maj = edge_array_calloc(node_ct);
  preference_graph_to_majority_graph(pg->graph, maj, node_ct);
  edge_array_printl(maj, node_ct, "Majority graph");
  Davenport *solver = davenport_create(maj, node_ct);
  SolutionTracker *st = solution_tracker_create(node_ct);
  davenport_set_solution_callback(solver, &solution_tracker_add_solution, st);
  davenport_compute(solver);
  solution_tracker_report_solution(st, pg);
  solution_tracker_destroy(st);
  davenport_destroy(solver);
}

int
main (void)
{
  puts ("This is " PACKAGE_STRING ".");
  PreferenceGraph *pg = pg_populate(stdin);
  if (pg != NULL) {
    printf ("Preference graph with %d candidates is\n", pg->node_ct);
    edge_array_print(pg->graph, pg->node_ct);
    compute_solution(pg);
    pg_free(pg);
  } else {
    puts ("No preferences");
  }
  return 0;
}

