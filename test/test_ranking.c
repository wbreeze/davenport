#include <cutter.h>
#include "../src/network.h"
#include "../src/ranking.h"
#include "../src/transitive_net.h"
#include "test_helper.h"

void test_ranking_order_sorted_complete(void)
{
  const int node_ct = 5;
  unsigned char *solution_graph = solution_array_calloc(node_ct);
  int topological_sort[node_ct] = { 0, 1, 2, 3, 4 };

  for (int i = 1; i < node_ct; ++i) {
    transitive_net_add_edge(solution_graph, node_ct, i-1, i);
  }

  int ranking[node_ct];
  rank_sorted_items(solution_graph, topological_sort, node_ct, ranking);

  int expected[node_ct] = { 1, 2, 3, 4, 5 };
  assert_equal_int_array(expected, ranking, node_ct);

  free(solution_graph);
}
