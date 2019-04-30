#include <limits.h>
#include <stdlib.h>
#include "davenport.h"
#include "sorting.h"
#include "network.h"
#include "tarjan.h"

Davenport *davenport_create(const int *majority_graph, int node_ct)
{
  Davenport *d = malloc(sizeof(struct Davenport));
  d->node_ct = node_ct;
  d->majority_graph = majority_graph;
  d->solution_graph = solution_array_calloc(node_ct);
  d->components = node_array_calloc(node_ct);
  d->edge_ct = 0;
  d->edge_list = calloc(DV_EDGE_CT(node_ct), sizeof(int));
  d->tarjan = tarjan_create(node_ct);
  d->solution_ct = 0;
  d->solution = node_array_calloc(node_ct);
  d->best_found = INT_MAX;

  return d;
}

Davenport *davenport_destroy(Davenport * d)
{
  free(d->solution);
  d->tarjan = tarjan_destroy(d->tarjan);
  free(d->edge_list);
  free(d->components);
  free(d->solution_graph);
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
  if (d->solution_graph[edge_index] == 0) {
    d->solution_graph[edge_index] = 1;
    for (int w = 0; w < d->node_ct; ++w) {
      if (d->solution_graph[RCI(v,w,d->node_ct)] != 0) {
        d->solution_graph[RCI(u,w,d->node_ct)] = 1;
      }
    }
    for (int t = 0; t < d->node_ct; ++t) {
      if (d->solution_graph[RCI(t,u,d->node_ct)] != 0) {
        for (int w = 0; w < d->node_ct; ++w) {
          if (d->solution_graph[RCI(u,w,d->node_ct)] != 0) {
            d->solution_graph[RCI(t,w,d->node_ct)] = 1;
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

/*
 Return a weight if the edge referenced from the edge_list at edge_list_offset
 nor its opposite are yet in the solution. Otherwise, return zero.
*/
int dv_modified_edge(Davenport *d, int edge_list_offset)
{
  int edge_weight = 0;
  /*** I'm getting ahead of myself
  int edge_offset = d->edge_list[edge_list_offset];
  if (d->solution_graph[edge_offset] == 0)
  {
    int r = ROW(edge_offset, d->node_ct);
    int c = COL(edge_offset, d->node_ct);
    int reverse_edge_offset = RCI(c,r,d->node_ct);
    if (d->solution_graph[reverse_edge_offset] == 0)
      edge_weight = d->majority_graph[edge_offset];
  }
  ***/
  return edge_weight;
}

/*
 Update the solutions.
 If the disagreement_ct is better than the best_found,
   discard current solutions and update the best_found.
 If the disagreement_ct is equal to the best found,
   add the current solution.
*/
void dv_maybe_add_solution(Davenport *d, int disagreement_ct)
{
  if (disagreement_ct < d->best_found) {
    d->best_found = disagreement_ct;
    // eliminate current solutions
  }
  if (disagreement_ct == d->best_found) {
    memcpy(d->solution, d->components, NSZ(d->node_ct));
    d->solution_ct = 1;
  }
}

/*
 Find an edge we haven't tried, yet.
 If there is one, check the lower bound and possibly extend by adding the edge.
 If there is none, update the solutions.
*/
void dv_extend_solution(Davenport *d, int disagreement_ct)
{
  int e_cur = 0;
  while(e_cur < d->edge_ct && dv_modified_edge(d, e_cur) == 0) ++e_cur;
  if (e_cur < d->edge_ct) {
    // check lower bound
    // iterate through edges, trying each and recursing
  } else {
    dv_maybe_add_solution(d, disagreement_ct);
  }
}

int davenport_compute(Davenport *d)
{
  dv_initialize_solution(d);
  dv_extend_solution(d, 0);
  return d->solution_ct;
}

const int *davenport_solution(Davenport *d, int offset)
{
  const int *solution = NULL;
  if (offset < d->solution_ct) {
    solution = d->solution;
  }
  return solution;
}
