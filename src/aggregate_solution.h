#ifndef AGGREGATE_SOLUTION_H
#define AGGREGATE_SOLUTION_H

#include "solution_graph.h"

typedef struct AggregateSolution {
  int node_ct;
  int disagreement_ct;
  int *preference_graph;
  int *aggregate_ranking;
} AggregateSolution;

AggregateSolution *aggregate_solution_create(int node_ct);
AggregateSolution *aggregate_solution_destroy(AggregateSolution *asol);

void aggregate_solution_add_solution(AggregateSolution *asol,
  int *sol, int node_ct, int disagreement_ct);
int *aggregate_solution_ranking(AggregateSolution *asol);

#endif
