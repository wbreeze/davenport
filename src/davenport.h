#ifndef DAVENPORT_H
#define DAVENPORT_H

// defined here for testing

#include "network.h"
#include "tarjan.h"

#define DV_EDGE_CT(node_ct) (ECT(node_ct) / 2)

typedef struct Davenport {
  int node_ct;
  const int *majority_graph;
  unsigned char *solution_graph;
  int *components;
  int *topo_sort;
  int edge_ct;
  int *edge_list;
  Tarjan *tarjan;
  int solution_ct;
  int *solution;
  int best_found;
} Davenport;

// public interface

/*
 Create data structure for Kemeny order computation.
 Accepts an existing majority graph and count of nodes (alternatives)
 The majority_graph contains integer weights, where the weight at
 RCI(u,v,node_ct) is zero, or represents a majority weight of preference
 for alternative index u over v.
 The caller represents the following:
 - majority_graph has memory allocated to ECT(node_ct) * sizeof(int)
 - that memory is not freed before calling davenport_destroy with the
   returned pointer to the Davenport data structure.
 - if majority_graph[RCI(u,v,node_ct)] is non-zero, then
   majority_graph[RCI(v,u,node_ct)] is zero. (There are no reverse edges,
   nor edges to self.)
*/
Davenport *davenport_create(const int *majority_graph, int node_ct);

/*
 Free the storage allocated for Kemeny order computation and the
 data structure used to track it.
 Always returns NULL.
*/
Davenport *davenport_destroy(Davenport *d);

/*
 Compute Kemeny-Young partial orders for the current majority graph.
 Returns the count of solutions, also available as d->solution_ct.
*/
int davenport_compute(Davenport *d);

/*
 Return the computed solution at the given offset.
 Returns NULL if d->solution_ct <= offset.
*/
int *davenport_solution(Davenport *d, int offset);

#endif
