#ifndef DAVENPORT_IMPL_H
#define DAVENPORT_IMPL_H

#include "davenport/davenport.h"

#include "network.h"
#include "solution_graph.h"
#include "tarjan.h"

struct Davenport {
  int node_ct;
  const int *majority_graph;
  SolutionGraph *solution_graph;
  int *components;
  int *topo_sort;
  int edge_ct;
  int *edge_list;
  Tarjan *tarjan;
  int solution_ct;
  int *solution;
  int best_found;
  DavenportSolutionCallback solution_callback;
  void *solution_context;
  int cycle_lower_bounds;
};

#endif
