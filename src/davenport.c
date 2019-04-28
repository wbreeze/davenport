#include <stdlib.h>
#include "davenport.h"
#include "edge_selection.h"
#include "network.h"
#include "tarjan.h"

Davenport *davenport_create(const int *majority_graph, int node_ct)
{
  Davenport *d = malloc(sizeof(struct Davenport));
  d->node_ct = node_ct;
  d->majority_graph = majority_graph;
  d->solution = solution_array_calloc(node_ct);
  d->components = node_array_calloc(node_ct);
  d->edge_ct = 0;
  d->edge_list = calloc(DV_EDGE_CT(node_ct), sizeof(int));
  d->tarjan = tarjan_create(node_ct);
  d->solution_ct = 0;

  return d;
}

Davenport *davenport_destroy(Davenport * d)
{
  d->tarjan = tarjan_destroy(d->tarjan);
  free(d->edge_list);
  free(d->components);
  free(d->solution);
  free(d);
  return NULL;
}

/*
 Add an edge (u,v) to the solution graph and maintain transitive closure.
 This works provided the solution graph is already transitive.
 By always calling this method to add edges, we ensure that is the case.
 We don't do any work if the edge is already in the graph.
*/
void dv_add_solution_edge(Davenport *d, int u, int v)
{
  int edge_index = RCI(u,v,d->node_ct);
  if (d->solution[edge_index] == 0) {
    d->solution[edge_index] = 1;
    for (int w = 0; w < d->node_ct; ++w) {
      if (d->solution[RCI(v,w,d->node_ct)] != 0) {
        d->solution[RCI(u,w,d->node_ct)] = 1;
      }
    }
    for (int t = 0; t < d->node_ct; ++t) {
      if (d->solution[RCI(t,u,d->node_ct)] != 0) {
        for (int w = 0; w < d->node_ct; ++w) {
          if (d->solution[RCI(u,w,d->node_ct)] != 0) {
            d->solution[RCI(t,w,d->node_ct)] = 1;
          }
        }
      }
    }
  }
}

void dv_initialize_solution(Davenport *d)
{
  tarjan_identify_components(d->tarjan, d->majority_graph, d->node_ct,
    d->components);
  for (int u = 0; u < d->node_ct; ++u) {
    for (int v = 0; v < d->node_ct; ++v) {
      if (0 < d->majority_graph[RCI(u,v,d->node_ct)])
      {
        if (d->components[u] != d->components[v])
        {
          dv_add_solution_edge(d, u, v);
        } else {
          d->edge_list[d->edge_ct++] = RCI(u,v,d->node_ct);
        }
      }
    }
  }
  sort_edge_selection(d->majority_graph, d->edge_list, d->edge_ct);
}

int davenport_compute(Davenport *d)
{
  d->solution_ct = 1;
  return 1;
}

const int *davenport_solution(Davenport *d, int offset)
{
  const int *solution = NULL;
  if (offset < d->solution_ct) {
    const int fake[4] = {1,2,3,4};
    solution = fake;
  }
  return solution;
}
