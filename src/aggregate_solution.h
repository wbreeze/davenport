#ifndef AGGREGATE_SOLUTION_IMPL_H
#define AGGREGATE_SOLUTION_IMPL_H

#include "davenport/aggregate_solution.h"

struct AggregateSolution {
  int node_ct;
  int disagreement_ct;
  int *preference_graph;
  int *aggregate_ranking;
};

#endif
