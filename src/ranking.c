#include <string.h>
#include "network.h"
#include "ranking.h"

/*
 Returns true (non-zero) if u comes strictly before v in graph g
*/
typedef int (*PrecedenceFunction)(const void* g, int node_ct, int u, int v);

void rank_sorted_items(PrecedenceFunction precedes, const void *graph,
  const int *topological_sort, int node_ct, int *ranking)
{
  // number according to distance from root
  node_array_clear(ranking, node_ct);
  for (int i = 0; i < node_ct; ++i) {
    int u = topological_sort[i];
    for(int j = i + 1; j < node_ct; ++j) {
      int v = topological_sort[j];
      if (precedes(graph, node_ct, u, v)) ranking[v] += 1;
    }
  }
  // convert distances to rankings
  int pd = ranking[topological_sort[0]];
  int pr = ranking[topological_sort[0]] = 1;
  for (int i = 1; i < node_ct; ++i) {
    int u = topological_sort[i];
    if (ranking[u] != pd) {
      pd = ranking[u];
      pr = ranking[u] = i + 1;
    } else {
      ranking[u] = pr;
    }
  }
}

int precedence_in_solution(const void *solution_graph, int node_ct,
  int u, int v)
{
  const unsigned char *sg = (const unsigned char *)solution_graph;
  return sg[RCI(u,v,node_ct)];
}

void rank_sorted_from_solution(const unsigned char *solution_graph,
  const int *topological_sort, int node_ct, int *ranking)
{
  rank_sorted_items(precedence_in_solution, solution_graph,
    topological_sort, node_ct, ranking);
}

int precedence_relation(const void *preference_graph, int node_ct,
  int u, int v)
{
  const int *pg = (const int *)preference_graph;
  return pg[RCI(u,v,node_ct)];
}

void rank_sorted_from_preference(const int *preference_graph,
  const int *topological_sort, int node_ct, int *ranking)
{
  rank_sorted_items(precedence_relation, preference_graph,
    topological_sort, node_ct, ranking);
}
