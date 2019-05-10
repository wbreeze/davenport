#include <limits.h>
#include <stdlib.h>
#include "davenport.h"
#include "lower_bound.h"
#include "network.h"
#include "ranking.h"
#include "solution_graph.h"
#include "sorting.h"
#include "tarjan.h"

int modified_majority_edge_lookup(void *context, int u, int v, int node_ct)
{
  SolutionGraph *sol = (SolutionGraph *)context;
  return solution_graph_modified_majority_edge(sol, u, v);
}

void accumulate_lower_bound(void *context, int *component, int member_ct)
{
  if (1 < member_ct) {
    Davenport *d = (Davenport *)context;
    d->cycle_lower_bounds += compute_bound_edge_lookup(
      modified_majority_edge_lookup, d->solution_graph,
      d->node_ct, component, member_ct);
  }
}

Davenport *davenport_create(const int *majority_graph, int node_ct)
{
  Davenport *d = malloc(sizeof(struct Davenport));
  d->node_ct = node_ct;
  d->majority_graph = majority_graph;
  d->solution_graph = solution_graph_create(majority_graph, node_ct);
  d->components = node_array_calloc(node_ct);
  d->topo_sort = node_array_calloc(node_ct);
  d->edge_ct = 0;
  d->edge_list = calloc(DG_ECT(node_ct), sizeof(int));
  d->tarjan = tarjan_create(modified_majority_edge_lookup,
    d->solution_graph, node_ct);
  d->solution_ct = 0;
  d->solution = node_array_calloc(node_ct);
  d->best_found = INT_MAX;
  d->solution_callback = NULL;
  d->cycle_lower_bounds = 0;

  tarjan_set_component_callback(d->tarjan, &accumulate_lower_bound, d);

  return d;
}

Davenport *davenport_destroy(Davenport * d)
{
  free(d->solution);
  d->tarjan = tarjan_destroy(d->tarjan);
  free(d->edge_list);
  free(d->topo_sort);
  free(d->components);
  d->solution_graph = solution_graph_destroy(d->solution_graph);
  free(d);
  return NULL;
}

void davenport_set_solution_callback(Davenport *d,
  DavenportSolutionCallback callback, void *context)
{
  d->solution_callback = callback;
  d->solution_context = context;
}

void dv_initialize_solution(Davenport *d)
{
  tarjan_identify_components(d->tarjan, d->components);
  for (int u = 0; u < d->node_ct; ++u) {
    for (int v = 0; v < d->node_ct; ++v) {
      if (0 < d->majority_graph[RCI(u,v,d->node_ct)])
      {
        if (d->components[u] != d->components[v])
        {
          solution_graph_add_edge(d->solution_graph, u, v);
        } else {
          d->edge_list[d->edge_ct++] = RCI(u,v,d->node_ct);
        }
      }
    }
  }
  sort_edge_selection(d->majority_graph, d->edge_list, d->edge_ct);
}

/*
 Return non-zero (true) if the edge referenced from the edge_list
 at edge_list_offset or its opposite is currently part of the solution.
 Otherwise, return zero (false).
*/
unsigned char dv_edge_accounted(Davenport *d, int edge_list_offset)
{
  int edge_offset = d->edge_list[edge_list_offset];
  int r = ROW(edge_offset, d->node_ct);
  int c = COL(edge_offset, d->node_ct);
  return(solution_graph_has_edge(d->solution_graph, r, c) ||
     solution_graph_has_edge(d->solution_graph, c, r));
}

/*
 If the edge list at e_cur references an unaccounted edge, return e_cur.
 Otherwise advance e_cur until it references an unaccounted edge or
   exhausts all edges from the edge list.
*/
int next_unaccounted_edge_offset(Davenport *d, int e_cur)
{
  while(e_cur < d->edge_ct && dv_edge_accounted(d, e_cur)) ++e_cur;
  return e_cur;
}

/*
 Update the solutions.
 If the disagreement_ct is better than the best_found,
   discard current solutions and update the best_found.
 If the disagreement_ct is equal to the best found,
   add the current solution.
*/
void dv_maybe_add_solution(Davenport *d)
{
  int disagreement_ct = solution_graph_disagreements(d->solution_graph);
  if (disagreement_ct < d->best_found) {
    d->best_found = disagreement_ct;
    d->solution_ct = 0;
  }
  if (disagreement_ct == d->best_found) {
    sort_nodes_topo(d->components, d->topo_sort, d->node_ct);
    solution_graph_rank_sort_items(
      d->solution_graph, d->topo_sort, d->solution);
    if (d->solution_callback != NULL) {
      d->solution_callback(
        d->solution_context, d->solution, d->node_ct, disagreement_ct
      );
    }
    d->solution_ct += 1;
  }
}

/*
 Find an edge we haven't tried, yet.
 If there is one, check the lower bound and possibly extend by adding the edge.
 If there is none, possibly update the solutions.
*/
void dv_extend_solution(Davenport *d)
{
  d->cycle_lower_bounds = 0;
  tarjan_identify_components(d->tarjan, d->components);
  int e_cur = next_unaccounted_edge_offset(d, 0);
  if (e_cur < d->edge_ct) {
    int lower_bound = solution_graph_disagreements(d->solution_graph) +
      d->cycle_lower_bounds;
    if (lower_bound <= d->best_found)
    {
      while(e_cur < d->edge_ct) {
        int edge_offset = d->edge_list[e_cur];
        int r = ROW(edge_offset, d->node_ct);
        int c = COL(edge_offset, d->node_ct);
        int set_point = solution_graph_add_edge(d->solution_graph, r, c);
        dv_extend_solution(d);
        solution_graph_rollback(d->solution_graph, set_point);
        e_cur = next_unaccounted_edge_offset(d, ++e_cur);
      }
    }
  } else {
    dv_maybe_add_solution(d);
  }
}

int davenport_compute(Davenport *d)
{
  dv_initialize_solution(d);
  dv_extend_solution(d);
  return d->solution_ct;
}

int *davenport_last_solution(Davenport *d)
{
  return d->solution;
}
