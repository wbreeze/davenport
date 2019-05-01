#include "network.h"
#include "solution_graph.h"

void solution_graph_add_edge(unsigned char *solution, int node_ct,
  int u, int v)
{
  int edge_index = RCI(u,v,node_ct);
  if (solution[edge_index] == 0) {
    solution[edge_index] = 1;
    for (int w = 0; w < node_ct; ++w) {
      if (solution[RCI(v,w,node_ct)] != 0) {
        solution[RCI(u,w,node_ct)] = 1;
      }
    }
    for (int t = 0; t < node_ct; ++t) {
      if (solution[RCI(t,u,node_ct)] != 0) {
        for (int w = 0; w < node_ct; ++w) {
          if (solution[RCI(u,w,node_ct)] != 0) {
            solution[RCI(t,w,node_ct)] = 1;
          }
        }
      }
    }
  }
}
