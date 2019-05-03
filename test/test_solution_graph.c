#include <cutter.h>
#include "../src/network.h"
#include "../src/solution_graph.h"
#include "test_helper.h"

void test_solution_graph_create(void)
{
  const int node_ct = 5;
  int *majority_graph = edge_array_calloc(node_ct);
  SolutionGraph *sol = solution_graph_create(majority_graph, node_ct);
  cut_assert_not_null(sol);

  cut_assert_equal_int(node_ct, sol->node_ct);
  cut_assert_false(sol->disagreement_count);
  clear_solution_array(sol->solution, node_ct);
  cut_assert_false(sol->set_point);
  clear_edge_stack(sol->edge_stack, node_ct);

  sol = solution_graph_destroy(sol);
  cut_assert_null(sol);
  free(majority_graph);
}

void test_solution_graph_add_edge(void)
{
  const int node_ct = 5;
  int *majority_graph = edge_array_calloc(node_ct);
  SolutionGraph *sol = solution_graph_create(majority_graph, node_ct);

  solution_graph_add_edge(sol, 0, 4);
  cut_assert_true(solution_graph_has_edge(sol, 0, 4));
  cut_assert_false(solution_graph_has_edge(sol, 0 ,1));
  cut_assert_false(solution_graph_has_edge(sol, 0 ,3));

  solution_graph_add_edge(sol, 1, 3);
  cut_assert_true(solution_graph_has_edge(sol, 1 ,3));
  cut_assert_false(solution_graph_has_edge(sol, 1 ,4));
  cut_assert_false(solution_graph_has_edge(sol, 0 ,1));
  cut_assert_false(solution_graph_has_edge(sol, 0 ,3));

  solution_graph_add_edge(sol, 0, 1);
  cut_assert_true(solution_graph_has_edge(sol, 0 ,1));
  cut_assert_true(solution_graph_has_edge(sol, 0 ,3));
  cut_assert_false(solution_graph_has_edge(sol, 1 ,4));

  solution_graph_add_edge(sol, 3, 2);
  cut_assert_true(solution_graph_has_edge(sol, 3 ,2));
  cut_assert_true(solution_graph_has_edge(sol, 0 ,2));
  cut_assert_true(solution_graph_has_edge(sol, 1 ,2));
  cut_assert_false(solution_graph_has_edge(sol, 1 ,4));
  cut_assert_false(solution_graph_has_edge(sol, 4 ,2));

  sol = solution_graph_destroy(sol);
  free(majority_graph);
}
