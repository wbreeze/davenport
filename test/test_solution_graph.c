#include <cutter.h>
#include "../src/network.h"
#include "../src/solution_graph.h"
#include "test_helper.h"

void test_transitive_create(void)
{
  const int node_ct = 5;
  //SolutionGraph *sol = solution_graph_create(node_ct);
  //cut_assert_not_nil(sol);
  //cut_assert_equal_int(0, sol->set_point);
  //clear_solution_array(sol->solution, node_ct);
  //clear_edge_stack(sol->edge_stack, node_ct);
}

void test_transitive_add_edge(void)
{
  const int node_ct = 5;
  unsigned char *solution_graph = solution_array_calloc(node_ct);

  solution_graph_add_edge(solution_graph, node_ct, 0, 4);
  cut_assert_equal_int(1, solution_graph[RCI(0,4,node_ct)]);
  cut_assert_equal_int(0, solution_graph[RCI(0,1,node_ct)]);
  cut_assert_equal_int(0, solution_graph[RCI(0,3,node_ct)]);

  solution_graph_add_edge(solution_graph, node_ct, 1, 3);
  cut_assert_equal_int(1, solution_graph[RCI(1,3,node_ct)]);
  cut_assert_equal_int(0, solution_graph[RCI(1,4,node_ct)]);
  cut_assert_equal_int(0, solution_graph[RCI(0,1,node_ct)]);
  cut_assert_equal_int(0, solution_graph[RCI(0,3,node_ct)]);

  solution_graph_add_edge(solution_graph, node_ct, 0, 1);
  cut_assert_equal_int(1, solution_graph[RCI(0,1,node_ct)]);
  cut_assert_equal_int(1, solution_graph[RCI(0,3,node_ct)]);
  cut_assert_equal_int(0, solution_graph[RCI(1,4,node_ct)]);

  solution_graph_add_edge(solution_graph, node_ct, 3, 2);
  cut_assert_equal_int(1, solution_graph[RCI(3,2,node_ct)]);
  cut_assert_equal_int(1, solution_graph[RCI(0,2,node_ct)]);
  cut_assert_equal_int(1, solution_graph[RCI(1,2,node_ct)]);
  cut_assert_equal_int(0, solution_graph[RCI(1,4,node_ct)]);
  cut_assert_equal_int(0, solution_graph[RCI(4,2,node_ct)]);

  free(solution_graph);
}

void test_transitive_rollback_nothing_to_do(void)
{
  const int node_ct = 5;
  unsigned char *solution_graph = solution_array_calloc(node_ct);

  free(solution_graph);
}

void test_transitive_rollback_across_one(void)
{
  
}

void test_transitive_rollback_across_multiple(void)
{
  
}

void test_transitive_update_disagreement_count(void)
{
  
}
