#ifndef TEST_DAVENPORT_CALLBACK_CONTEXT_H
#define TEST_DAVENPORT_CALLBACK_CONTEXT_H

typedef struct CallbackContext {
  Davenport *dv;
  int expected_disagreements;
  int seen_solution_ct;
  int *last_solution;
  int valid_solution_ct;
  int **valid_solutions;
} CallbackContext;

void handle_solution(void *context, int *ranking, int node_ct,
  int disagreement_ct);

#endif
