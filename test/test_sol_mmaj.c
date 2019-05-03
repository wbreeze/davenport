#include <cutter.h>
#include "../src/network.h"
#include "../src/solution_graph.h"
#include "test_helper.h"

void test_solution_graph_mmaj_no_solution_edge(void)
{
  const int node_ct = 8;
  int *majority_graph = edge_array_calloc(node_ct);
  set_majority_net_multi_cycle_embedded(majority_graph, node_ct);
  SolutionGraph *sol = solution_graph_create(majority_graph, node_ct);

  cut_assert_true(solution_graph_has_majority_edge(sol, 0, 1));
  cut_assert_true(solution_graph_has_majority_edge(sol, 4, 3));

  sol = solution_graph_destroy(sol);
  free(majority_graph);
}

void test_solution_graph_mmaj_added_solution_edge(void)
{
  const int node_ct = 8;
  int *majority_graph = edge_array_calloc(node_ct);
  set_majority_net_multi_cycle_embedded(majority_graph, node_ct);
  SolutionGraph *sol = solution_graph_create(majority_graph, node_ct);

  solution_graph_add_edge(sol, 2, 5);
  solution_graph_add_edge(sol, 1, 2);

  cut_assert_true(solution_graph_has_majority_edge(sol, 2, 5));
  cut_assert_true(solution_graph_has_majority_edge(sol, 1, 5));

  sol = solution_graph_destroy(sol);
  free(majority_graph);
}

void test_solution_graph_mmaj_reverse_solution_edge(void)
{
  const int node_ct = 8;
  int *majority_graph = edge_array_calloc(node_ct);
  set_majority_net_multi_cycle_embedded(majority_graph, node_ct);
  SolutionGraph *sol = solution_graph_create(majority_graph, node_ct);

  cut_assert_true(solution_graph_has_majority_edge(sol, 3, 1));
  solution_graph_add_edge(sol, 1, 3);
  cut_assert_false(solution_graph_has_majority_edge(sol, 3, 1));

  cut_assert_true(solution_graph_has_majority_edge(sol, 5, 3));
  solution_graph_add_edge(sol, 3, 5);
  cut_assert_false(solution_graph_has_majority_edge(sol, 5, 3));

  sol = solution_graph_destroy(sol);
  free(majority_graph);
}
