#include <cutter.h>
#include "../src/network.h"
#include "../src/preference_graph.h"
#include "test_helper.h"

void test_preference_graph_convert_majority(void)
{
  const int node_ct = 5;
  int *preference_graph = edge_array_calloc(node_ct);
  int *majority_graph = edge_array_calloc(node_ct);
  set_preference_net_1(preference_graph, node_ct);

  preference_graph_to_majority_graph(preference_graph, majority_graph, node_ct);

  cut_assert_equal_int(3, majority_graph[RCI(0,1,node_ct)]);
  cut_assert_equal_int(0, majority_graph[RCI(0,2,node_ct)]);
  cut_assert_equal_int(3, majority_graph[RCI(0,3,node_ct)]);
  cut_assert_equal_int(3, majority_graph[RCI(0,4,node_ct)]);
  cut_assert_equal_int(0, majority_graph[RCI(1,0,node_ct)]);
  cut_assert_equal_int(1, majority_graph[RCI(1,2,node_ct)]);
  cut_assert_equal_int(0, majority_graph[RCI(1,3,node_ct)]);
  cut_assert_equal_int(3, majority_graph[RCI(1,4,node_ct)]);
  cut_assert_equal_int(1, majority_graph[RCI(2,0,node_ct)]);
  cut_assert_equal_int(0, majority_graph[RCI(2,1,node_ct)]);
  cut_assert_equal_int(3, majority_graph[RCI(2,3,node_ct)]);
  cut_assert_equal_int(0, majority_graph[RCI(2,4,node_ct)]);
  cut_assert_equal_int(0, majority_graph[RCI(3,0,node_ct)]);
  cut_assert_equal_int(1, majority_graph[RCI(3,1,node_ct)]);
  cut_assert_equal_int(0, majority_graph[RCI(3,2,node_ct)]);
  cut_assert_equal_int(0, majority_graph[RCI(3,4,node_ct)]);
  cut_assert_equal_int(0, majority_graph[RCI(4,0,node_ct)]);
  cut_assert_equal_int(0, majority_graph[RCI(4,1,node_ct)]);
  cut_assert_equal_int(1, majority_graph[RCI(4,2,node_ct)]);
  cut_assert_equal_int(3, majority_graph[RCI(4,3,node_ct)]);

  free(majority_graph);
  free(preference_graph);
}
