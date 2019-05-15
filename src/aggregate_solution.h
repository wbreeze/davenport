#ifndef AGGREGATE_SOLUTION_H
#define AGGREGATE_SOLUTION_H

#include "solution_graph.h"

typedef struct AggregateSolution {
  int node_ct;
  int disagreement_ct;
  int *preference_graph;
  int *aggregate_ranking;
} AggregateSolution;

/*
 Build a data structure which, with aggregate_solution_add_solution,
 can function as a DavenportSolutionCallback in order to create a composite
 of multiple solutions returned by the Davenport algorithm.
*/
AggregateSolution *aggregate_solution_create(int node_ct);

/*
 Free memory allocated for asol to the heap and return NULL
*/
AggregateSolution *aggregate_solution_destroy(AggregateSolution *asol);

/*
 Suitable as a DavenportSolutionCallback, collects solutions with
 the latest value for disagreement_ct into a preference graph.
*/
void aggregate_solution_add_solution(AggregateSolution *asol,
  int *sol, int node_ct, int disagreement_ct);

/*
 Use the Tarjan algorithm to find components in the preference graph built-up
 from calls to aggregate_solution_add_solution. This means that rankings
 ...B,C... and ...C,B... cause B and C to show-up as a two-alternative
 component.

 Initialize a solution graph from the components and the preference graph, just
 as is done in "Algorithm 1" from the Davenport paper. We use the preference
 graph equivalently to the majority graph, because the inter-component edges
 must necessarily have edges in one direction only (otherwise they would be
 within components).

 Make a topological sort of the solution graph and components to produce the
 returned aggregate ranking / partial order.

 The returned data is valid until asol is destroyed. It has length
 asol->node_ct.  A subsequent call to this method will overwrite the data.
*/
int *aggregate_solution_ranking(AggregateSolution *asol);

#endif
