#include <cutter.h>
#include "../src/network.h"
#include "../src/preference_graph.h"
#include "test_helper.h"

void test_preference_graph_add_preference(void)
{
  const int node_ct = 5;
  int *preference_graph = edge_array_calloc(node_ct);

  int j1[] = { 5, 4, 2, 3, 1 };
  preference_graph_add_preference(preference_graph, j1, node_ct);
  cut_assert_equal_int(0, preference_graph[RCI(0,1,node_ct)]);
  cut_assert_equal_int(0, preference_graph[RCI(0,2,node_ct)]);
  cut_assert_equal_int(0, preference_graph[RCI(0,3,node_ct)]);
  cut_assert_equal_int(0, preference_graph[RCI(0,4,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(1,0,node_ct)]);
  cut_assert_equal_int(0, preference_graph[RCI(1,2,node_ct)]);
  cut_assert_equal_int(0, preference_graph[RCI(1,3,node_ct)]);
  cut_assert_equal_int(0, preference_graph[RCI(1,4,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(2,0,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(2,1,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(2,3,node_ct)]);
  cut_assert_equal_int(0, preference_graph[RCI(2,4,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(3,0,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(3,1,node_ct)]);
  cut_assert_equal_int(0, preference_graph[RCI(3,2,node_ct)]);
  cut_assert_equal_int(0, preference_graph[RCI(3,4,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(4,0,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(4,1,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(4,2,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(4,3,node_ct)]);

  int j2[] = { 1, 2, 4, 6, 3 };
  preference_graph_add_preference(preference_graph, j2, node_ct);
  cut_assert_equal_int(1, preference_graph[RCI(0,1,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(0,2,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(0,3,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(0,4,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(1,0,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(1,2,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(1,3,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(1,4,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(2,0,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(2,1,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(2,3,node_ct)]);
  cut_assert_equal_int(0, preference_graph[RCI(2,4,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(3,0,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(3,1,node_ct)]);
  cut_assert_equal_int(0, preference_graph[RCI(3,2,node_ct)]);
  cut_assert_equal_int(0, preference_graph[RCI(3,4,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(4,0,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(4,1,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(4,2,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(4,3,node_ct)]);

  int j3[] = { 7, 1, 2, 4, 3 };
  preference_graph_add_preference(preference_graph, j3, node_ct);
  cut_assert_equal_int(1, preference_graph[RCI(0,1,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(0,2,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(0,3,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(0,4,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(1,0,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(1,2,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(1,3,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(1,4,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(2,0,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(2,1,node_ct)]);
  cut_assert_equal_int(3, preference_graph[RCI(2,3,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(2,4,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(3,0,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(3,1,node_ct)]);
  cut_assert_equal_int(0, preference_graph[RCI(3,2,node_ct)]);
  cut_assert_equal_int(0, preference_graph[RCI(3,4,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(4,0,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(4,1,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(4,2,node_ct)]);
  cut_assert_equal_int(3, preference_graph[RCI(4,3,node_ct)]);

  int j4[] = { 1, 3, 5, 2, 4 };
  preference_graph_add_preference(preference_graph, j4, node_ct);
  cut_assert_equal_int(2, preference_graph[RCI(0,1,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(0,2,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(0,3,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(0,4,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(1,0,node_ct)]);
  cut_assert_equal_int(3, preference_graph[RCI(1,2,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(1,3,node_ct)]);
  cut_assert_equal_int(3, preference_graph[RCI(1,4,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(2,0,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(2,1,node_ct)]);
  cut_assert_equal_int(3, preference_graph[RCI(2,3,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(2,4,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(3,0,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(3,1,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(3,2,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(3,4,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(4,0,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(4,1,node_ct)]);
  cut_assert_equal_int(3, preference_graph[RCI(4,2,node_ct)]);
  cut_assert_equal_int(3, preference_graph[RCI(4,3,node_ct)]);

  int j5[] = { 2, 5, 1, 4, 3 };
  preference_graph_add_preference(preference_graph, j5, node_ct);
  cut_assert_equal_int(3, preference_graph[RCI(0,1,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(0,2,node_ct)]);
  cut_assert_equal_int(3, preference_graph[RCI(0,3,node_ct)]);
  cut_assert_equal_int(3, preference_graph[RCI(0,4,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(1,0,node_ct)]);
  cut_assert_equal_int(3, preference_graph[RCI(1,2,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(1,3,node_ct)]);
  cut_assert_equal_int(3, preference_graph[RCI(1,4,node_ct)]);
  cut_assert_equal_int(3, preference_graph[RCI(2,0,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(2,1,node_ct)]);
  cut_assert_equal_int(4, preference_graph[RCI(2,3,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(2,4,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(3,0,node_ct)]);
  cut_assert_equal_int(3, preference_graph[RCI(3,1,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(3,2,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(3,4,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(4,0,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(4,1,node_ct)]);
  cut_assert_equal_int(3, preference_graph[RCI(4,2,node_ct)]);
  cut_assert_equal_int(4, preference_graph[RCI(4,3,node_ct)]);

  int j6[] = { 1, 2, 5, 4, 3 };
  preference_graph_add_preference(preference_graph, j6, node_ct);
  cut_assert_equal_int(4, preference_graph[RCI(0,1,node_ct)]);
  cut_assert_equal_int(3, preference_graph[RCI(0,2,node_ct)]);
  cut_assert_equal_int(4, preference_graph[RCI(0,3,node_ct)]);
  cut_assert_equal_int(4, preference_graph[RCI(0,4,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(1,0,node_ct)]);
  cut_assert_equal_int(4, preference_graph[RCI(1,2,node_ct)]);
  cut_assert_equal_int(3, preference_graph[RCI(1,3,node_ct)]);
  cut_assert_equal_int(4, preference_graph[RCI(1,4,node_ct)]);
  cut_assert_equal_int(3, preference_graph[RCI(2,0,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(2,1,node_ct)]);
  cut_assert_equal_int(4, preference_graph[RCI(2,3,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(2,4,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(3,0,node_ct)]);
  cut_assert_equal_int(3, preference_graph[RCI(3,1,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(3,2,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(3,4,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(4,0,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(4,1,node_ct)]);
  cut_assert_equal_int(4, preference_graph[RCI(4,2,node_ct)]);
  cut_assert_equal_int(5, preference_graph[RCI(4,3,node_ct)]);

  int j7[] = { 2, 4, 1, 3, 5 };
  preference_graph_add_preference(preference_graph, j7, node_ct);
  cut_assert_equal_int(5, preference_graph[RCI(0,1,node_ct)]);
  cut_assert_equal_int(3, preference_graph[RCI(0,2,node_ct)]);
  cut_assert_equal_int(5, preference_graph[RCI(0,3,node_ct)]);
  cut_assert_equal_int(5, preference_graph[RCI(0,4,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(1,0,node_ct)]);
  cut_assert_equal_int(4, preference_graph[RCI(1,2,node_ct)]);
  cut_assert_equal_int(3, preference_graph[RCI(1,3,node_ct)]);
  cut_assert_equal_int(5, preference_graph[RCI(1,4,node_ct)]);
  cut_assert_equal_int(4, preference_graph[RCI(2,0,node_ct)]);
  cut_assert_equal_int(3, preference_graph[RCI(2,1,node_ct)]);
  cut_assert_equal_int(5, preference_graph[RCI(2,3,node_ct)]);
  cut_assert_equal_int(3, preference_graph[RCI(2,4,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(3,0,node_ct)]);
  cut_assert_equal_int(4, preference_graph[RCI(3,1,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(3,2,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(3,4,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(4,0,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(4,1,node_ct)]);
  cut_assert_equal_int(4, preference_graph[RCI(4,2,node_ct)]);
  cut_assert_equal_int(5, preference_graph[RCI(4,3,node_ct)]);

  free(preference_graph);
}

void test_preference_graph_add_preference_with_ties(void)
{
  const int node_ct = 4;
  int *preference_graph = edge_array_calloc(node_ct);

  int j1[] = { 5, 4, 4, 3 };
  preference_graph_add_preference(preference_graph, j1, node_ct);
  cut_assert_equal_int(0, preference_graph[RCI(0,1,node_ct)]);
  cut_assert_equal_int(0, preference_graph[RCI(0,2,node_ct)]);
  cut_assert_equal_int(0, preference_graph[RCI(0,3,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(1,0,node_ct)]);
  cut_assert_equal_int(0, preference_graph[RCI(1,2,node_ct)]);
  cut_assert_equal_int(0, preference_graph[RCI(1,3,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(2,0,node_ct)]);
  cut_assert_equal_int(0, preference_graph[RCI(2,1,node_ct)]);
  cut_assert_equal_int(0, preference_graph[RCI(2,3,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(3,0,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(3,1,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(3,2,node_ct)]);

  int j2[] = { 1, 1, 3, 3 };
  preference_graph_add_preference(preference_graph, j2, node_ct);
  cut_assert_equal_int(0, preference_graph[RCI(0,1,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(0,2,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(0,3,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(1,0,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(1,2,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(1,3,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(2,0,node_ct)]);
  cut_assert_equal_int(0, preference_graph[RCI(2,1,node_ct)]);
  cut_assert_equal_int(0, preference_graph[RCI(2,3,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(3,0,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(3,1,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(3,2,node_ct)]);

  int j3[] = { 1, 2, 3, 3 };
  preference_graph_add_preference(preference_graph, j3, node_ct);
  cut_assert_equal_int(1, preference_graph[RCI(0,1,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(0,2,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(0,3,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(1,0,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(1,2,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(1,3,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(2,0,node_ct)]);
  cut_assert_equal_int(0, preference_graph[RCI(2,1,node_ct)]);
  cut_assert_equal_int(0, preference_graph[RCI(2,3,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(3,0,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(3,1,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(3,2,node_ct)]);

  int j4[] = { 2, 2, 2, 1 };
  preference_graph_add_preference(preference_graph, j4, node_ct);
  cut_assert_equal_int(1, preference_graph[RCI(0,1,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(0,2,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(0,3,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(1,0,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(1,2,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(1,3,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(2,0,node_ct)]);
  cut_assert_equal_int(0, preference_graph[RCI(2,1,node_ct)]);
  cut_assert_equal_int(0, preference_graph[RCI(2,3,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(3,0,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(3,1,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(3,2,node_ct)]);

  int j5[] = { 1, 1, 1, 1 };
  preference_graph_add_preference(preference_graph, j5, node_ct);
  cut_assert_equal_int(1, preference_graph[RCI(0,1,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(0,2,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(0,3,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(1,0,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(1,2,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(1,3,node_ct)]);
  cut_assert_equal_int(1, preference_graph[RCI(2,0,node_ct)]);
  cut_assert_equal_int(0, preference_graph[RCI(2,1,node_ct)]);
  cut_assert_equal_int(0, preference_graph[RCI(2,3,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(3,0,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(3,1,node_ct)]);
  cut_assert_equal_int(2, preference_graph[RCI(3,2,node_ct)]);

  free(preference_graph);
}
