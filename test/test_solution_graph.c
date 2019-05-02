#include <cutter.h>
#include "../src/network.h"
#include "../src/solution_graph.h"
#include "test_helper.h"

#define SSZ(node_ct) (ECT(node_ct) * sizeof(unsigned char))
#define copy_solution_array(to, sol) \
  memcpy(to, sol->solution, SSZ(sol->node_ct))
#define assert_equal_solution_array(expected, sol) \
  cut_assert_equal_memory( \
    expected, SSZ(sol->node_ct), sol->solution, SSZ(sol->node_ct) \
  )

void test_solution_graph_create(void)
{
  const int node_ct = 5;
  SolutionGraph *sol = solution_graph_create(node_ct);
  cut_assert_not_null(sol);

  cut_assert_equal_int(node_ct, sol->node_ct);
  cut_assert_false(sol->disagreement_count);
  clear_solution_array(sol->solution, node_ct);
  cut_assert_false(sol->set_point);
  clear_edge_stack(sol->edge_stack, node_ct);

  sol = solution_graph_destroy(sol);
  cut_assert_null(sol);
}

void test_solution_graph_add_edge(void)
{
  const int node_ct = 5;
  SolutionGraph *sol = solution_graph_create(node_ct);

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
}

void test_solution_graph_rollback_nothing_to_do(void)
{
  const int node_ct = 5;
  SolutionGraph *sol = solution_graph_create(node_ct);

  unsigned char *save = solution_array_calloc(node_ct);
  copy_solution_array(save, sol);

  solution_graph_rollback(sol, 0);
  assert_equal_solution_array(save, sol);

  free(save);
  sol = solution_graph_destroy(sol);
}

void test_solution_graph_rollback_across_one(void)
{
  const int node_ct = 5;
  SolutionGraph *sol = solution_graph_create(node_ct);

  unsigned char *save = solution_array_calloc(node_ct);
  copy_solution_array(save, sol);

  int set_point = solution_graph_add_edge(sol, 0, 4);
  solution_graph_rollback(sol, set_point);

  assert_equal_solution_array(save, sol);

  free(save);
  sol = solution_graph_destroy(sol);
}

void test_solution_graph_rollback_across_multiple(void)
{
  const int node_ct = 5;
  SolutionGraph *sol = solution_graph_create(node_ct);

  unsigned char *save = solution_array_calloc(node_ct);
  copy_solution_array(save, sol);

  int set_point = solution_graph_add_edge(sol, 0, 4);
  solution_graph_add_edge(sol, 4, 3);
  solution_graph_add_edge(sol, 1, 4);

  solution_graph_rollback(sol, set_point);

  assert_equal_solution_array(save, sol);

  free(save);
  sol = solution_graph_destroy(sol);
}

void test_solution_graph_rollback_within_multiple(void)
{
  const int node_ct = 5;
  SolutionGraph *sol = solution_graph_create(node_ct);
  unsigned char *save = solution_array_calloc(node_ct);

  solution_graph_add_edge(sol, 0, 4);
  copy_solution_array(save, sol);
  int set_point = solution_graph_add_edge(sol, 4, 3);
  solution_graph_add_edge(sol, 1, 4);

  solution_graph_rollback(sol, set_point);

  assert_equal_solution_array(save, sol);

  free(save);
  sol = solution_graph_destroy(sol);
}

void test_solution_graph_update_disagreement_count(void)
{
}
