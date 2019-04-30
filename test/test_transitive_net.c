#include <cutter.h>
#include "../src/network.h"
#include "../src/transitive_net.h"
#include "test_helper.h"

void test_transitive_add_edge(void)
{
  const int node_ct = 5;
  unsigned char *solution_graph = solution_array_calloc(node_ct);

  transitive_net_add_edge(solution_graph, node_ct, 0, 4);
  cut_assert_equal_int(1, solution_graph[RCI(0,4,node_ct)]);
  cut_assert_equal_int(0, solution_graph[RCI(0,1,node_ct)]);
  cut_assert_equal_int(0, solution_graph[RCI(0,3,node_ct)]);

  transitive_net_add_edge(solution_graph, node_ct, 1, 3);
  cut_assert_equal_int(1, solution_graph[RCI(1,3,node_ct)]);
  cut_assert_equal_int(0, solution_graph[RCI(1,4,node_ct)]);
  cut_assert_equal_int(0, solution_graph[RCI(0,1,node_ct)]);
  cut_assert_equal_int(0, solution_graph[RCI(0,3,node_ct)]);

  transitive_net_add_edge(solution_graph, node_ct, 0, 1);
  cut_assert_equal_int(1, solution_graph[RCI(0,1,node_ct)]);
  cut_assert_equal_int(1, solution_graph[RCI(0,3,node_ct)]);
  cut_assert_equal_int(0, solution_graph[RCI(1,4,node_ct)]);

  transitive_net_add_edge(solution_graph, node_ct, 3, 2);
  cut_assert_equal_int(1, solution_graph[RCI(3,2,node_ct)]);
  cut_assert_equal_int(1, solution_graph[RCI(0,2,node_ct)]);
  cut_assert_equal_int(1, solution_graph[RCI(1,2,node_ct)]);
  cut_assert_equal_int(0, solution_graph[RCI(1,4,node_ct)]);
  cut_assert_equal_int(0, solution_graph[RCI(4,2,node_ct)]);

  free(solution_graph);
}
