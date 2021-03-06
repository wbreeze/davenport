#include <cutter.h>
#include "../src/network.h"
#include "../src/solution_graph.h"
#include "array_init.h"
#include "test_helper.h"

void test_ranking_order_sorted_complete(void)
{
  const int node_ct = 5;
  int *mg = edge_array_calloc(node_ct);
  SolutionGraph *sol = solution_graph_create(mg, node_ct);
  int topological_sort[node_ct];
  int_array_init(topological_sort, node_ct, 0, 1, 2, 3, 4);

  for (int i = 1; i < node_ct; ++i) {
    solution_graph_add_edge(sol, i-1, i);
  }

  int ranking[node_ct];
  solution_graph_rank_sort_items(sol, topological_sort, ranking);

  int expected[node_ct];
  int_array_init(expected, node_ct, 1, 2, 3, 4, 5);
  assert_equal_int_array(expected, ranking, node_ct);

  solution_graph_destroy(sol);
  free(mg);
}

void test_ranking_order_sorted_reverse(void)
{
  const int node_ct = 5;
  int *mg = edge_array_calloc(node_ct);
  SolutionGraph *sol = solution_graph_create(mg, node_ct);
  int topological_sort[node_ct];
  int_array_init(topological_sort, node_ct, 4, 3, 2, 1, 0);

  for (int i = node_ct - 1; 0 < i; --i) {
    solution_graph_add_edge(sol, i, i - 1);
  }

  int ranking[node_ct];
  solution_graph_rank_sort_items(sol, topological_sort, ranking);

  int expected[node_ct];
  int_array_init(expected, node_ct, 5, 4, 3, 2, 1);
  assert_equal_int_array(expected, ranking, node_ct);

  solution_graph_destroy(sol);
  free(mg);
}

void test_ranking_order_partial_two_second(void)
{
  const int node_ct = 5;
  int *mg = edge_array_calloc(node_ct);
  SolutionGraph *sol = solution_graph_create(mg, node_ct);
  int topological_sort[node_ct];
  int_array_init(topological_sort, node_ct, 0, 1, 4, 3, 2);

  solution_graph_add_edge(sol, 0, 1);
  solution_graph_add_edge(sol, 0, 4);
  solution_graph_add_edge(sol, 1, 3);
  solution_graph_add_edge(sol, 3, 2);

  int ranking[node_ct];
  solution_graph_rank_sort_items(sol, topological_sort, ranking);

  int expected[node_ct];
  int_array_init(expected, node_ct, 1, 2, 5, 4, 2);
  assert_equal_int_array(expected, ranking, node_ct);

  solution_graph_destroy(sol);
  free(mg);
}

void test_ranking_order_partial_two_first_and_last(void)
{
  const int node_ct = 5;
  int *mg = edge_array_calloc(node_ct);
  SolutionGraph *sol = solution_graph_create(mg, node_ct);
  int topological_sort[node_ct];
  int_array_init(topological_sort, node_ct, 4, 3, 1, 0, 2);

  solution_graph_add_edge(sol, 1, 0);
  solution_graph_add_edge(sol, 1, 2);
  solution_graph_add_edge(sol, 4, 1);
  solution_graph_add_edge(sol, 3, 1);

  int ranking[node_ct];
  solution_graph_rank_sort_items(sol, topological_sort, ranking);

  int expected[node_ct];
  int_array_init(expected, node_ct, 4, 3, 4, 1, 1);
  assert_equal_int_array(expected, ranking, node_ct);

  solution_graph_destroy(sol);
  free(mg);
}

void test_ranking_order_partial_two_roots(void)
{
  const int node_ct = 5;
  int *mg = edge_array_calloc(node_ct);
  SolutionGraph *sol = solution_graph_create(mg, node_ct);
  int topological_sort[node_ct];
  int_array_init(topological_sort, node_ct, 4, 2, 1, 3, 0);

  solution_graph_add_edge(sol, 2, 3);
  solution_graph_add_edge(sol, 2, 1);
  solution_graph_add_edge(sol, 1, 0);
  solution_graph_add_edge(sol, 4, 0);

  int ranking[node_ct];
  solution_graph_rank_sort_items(sol, topological_sort, ranking);

  int expected[node_ct];
  int_array_init(expected, node_ct, 5, 3, 1, 3, 1);
  assert_equal_int_array(expected, ranking, node_ct);

  solution_graph_destroy(sol);
  free(mg);
}
