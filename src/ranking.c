#include "ranking.h"

void rank_sorted_items(const int *solution_graph, const int *topological_sort,
  int node_ct, int *ranking)
{
  for (int i = 0; i < node_ct; ++i) ranking[i] = i + 1;
}
