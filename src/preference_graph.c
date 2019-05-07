#include "network.h"
#include "preference_graph.h"

void preference_graph_add_preference(int *preference_graph,
  const int *rankings, int node_ct)
{
  for (int u = 0; u < node_ct - 1; ++u) {
    for (int v = u + 1; v < node_ct; ++v) {
      if (rankings[u] < rankings[v]) {
        preference_graph[RCI(u,v,node_ct)] += 1;
      }
      if (rankings[v] < rankings[u]) {
        preference_graph[RCI(v,u,node_ct)] += 1;
      }
    }
  }
}
