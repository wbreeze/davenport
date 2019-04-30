#include <string.h>
#include "network.h"
#include "ranking.h"

void rank_sorted_items(const unsigned char *solution_graph,
  const int *topological_sort, int node_ct, int *ranking)
{
  // number according to distance from root
  memset(ranking, 0, node_ct * sizeof(int));
  for (int i = 0; i < node_ct; ++i) {
    int u = topological_sort[i];
    for(int j = i + 1; j < node_ct; ++j) {
      int v = topological_sort[j];
      if (solution_graph[RCI(u,v,node_ct)]) ranking[v] += 1;
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
