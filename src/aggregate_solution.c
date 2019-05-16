#include <limits.h>
#include <stdlib.h>
#include "aggregate_solution.h"
#include "network.h"
#include "preference_graph.h"
#include "solution_graph.h"
#include "ranking.h"
#include "sorting.h"
#include "tarjan.h"

AggregateSolution *aggregate_solution_create(int node_ct)
{
  AggregateSolution *asol = malloc(sizeof(struct AggregateSolution));
  asol->node_ct = node_ct;
  asol->disagreement_ct = INT_MAX;
  asol->preference_graph = edge_array_calloc(node_ct);
  asol->aggregate_ranking = node_array_calloc(node_ct);
  return asol;
}

AggregateSolution *aggregate_solution_destroy(AggregateSolution *asol)
{
  free(asol->aggregate_ranking);
  free(asol->preference_graph);
  free(asol);
  return NULL;
}

void aggregate_solution_add_solution(AggregateSolution *asol,
  int *sol, int node_ct, int disagreement_ct)
{
  if (disagreement_ct != asol->disagreement_ct) {
    asol->disagreement_ct = disagreement_ct;
    edge_array_clear(asol->preference_graph, asol->node_ct);
  }
  preference_graph_add_preference(asol->preference_graph, sol, node_ct);
}

int *aggregate_solution_ranking(AggregateSolution *asol)
{
  SolutionGraph *solution_graph = solution_graph_create(asol->node_ct);
  int *topo_order = node_array_calloc(asol->node_ct);
  int *components = node_array_calloc(asol->node_ct);
  Tarjan *t = tarjan_create(&tarjan_default_edge_lookup,
    asol->preference_graph, asol->node_ct);
  tarjan_identify_components(t, components);
  for (int u = 0; u < asol->node_ct; ++u) {
    for (int v = 0; v < asol->node_ct; ++v) {
      if (0 < asol->preference_graph[RCI(u,v,asol->node_ct)] &&
          components[u] != components[v])
      {
        solution_graph_add_edge(solution_graph, u, v);
      }
    }
  }
  sort_nodes_topo(components, topo_order, asol->node_ct);
  solution_graph_rank_sort_items(solution_graph,
    topo_order, asol->aggregate_ranking);
  t = tarjan_destroy(t);
  free(components);
  free(topo_order);
  solution_graph_destroy(solution_graph);
  return asol->aggregate_ranking;
}
