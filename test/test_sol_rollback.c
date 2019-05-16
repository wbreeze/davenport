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
