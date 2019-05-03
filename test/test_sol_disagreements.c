#include <cutter.h>
#include "../src/network.h"
#include "../src/solution_graph.h"
#include "test_helper.h"

void test_solution_graph_update_disagreements_direct(void)
{
  const int node_ct = 8;
  int *majority_graph = edge_array_calloc(node_ct);
  set_majority_net_multi_cycle_embedded(majority_graph, node_ct);
  SolutionGraph *sol = solution_graph_create(majority_graph, node_ct);

  solution_graph_add_edge(sol, 1, 0);
  cut_assert_equal_int(6, solution_graph_disagreements(sol));
  int setpoint = solution_graph_add_edge(sol, 2, 1);
  cut_assert_equal_int(16, solution_graph_disagreements(sol));
  solution_graph_add_edge(sol, 6, 5);
  cut_assert_equal_int(20, solution_graph_disagreements(sol));

  solution_graph_rollback(sol, setpoint);
  cut_assert_equal_int(6, solution_graph_disagreements(sol));

  sol = solution_graph_destroy(sol);
  free(majority_graph);
}

void test_solution_graph_update_disagreements_transitive(void)
{
  const int node_ct = 8;
  int *majority_graph = edge_array_calloc(node_ct);
  set_majority_net_multi_cycle_embedded(majority_graph, node_ct);
  SolutionGraph *sol = solution_graph_create(majority_graph, node_ct);

  solution_graph_add_edge(sol, 1, 2);
  cut_assert_equal_int(0, solution_graph_disagreements(sol));
  solution_graph_add_edge(sol, 2, 4);
  cut_assert_equal_int(0, solution_graph_disagreements(sol));
  solution_graph_add_edge(sol, 4, 5);
  cut_assert_equal_int(0, solution_graph_disagreements(sol));
  int setpoint = solution_graph_add_edge(sol, 5, 3);
  cut_assert_equal_int(5, solution_graph_disagreements(sol));

  solution_graph_rollback(sol, setpoint);
  cut_assert_equal_int(0, solution_graph_disagreements(sol));

  sol = solution_graph_destroy(sol);
  free(majority_graph);
}
