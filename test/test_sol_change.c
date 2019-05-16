#include <cutter.h>
#include "../src/network.h"
#include "../src/solution_graph.h"
#include "test_helper.h"

typedef struct SGC {
  int up_count;
  int dn_count;
  int last_u;
  int last_v;
} SGC;

void sg_test_edge_change(void *context, int u, int v, int dir)
{
  SGC *sgc = (SGC *)context;
  cut_assert_true(dir == 1 || dir == -1);
  if (dir == 1) sgc->up_count += 1;
  if (dir == -1) sgc->dn_count += 1;
  sgc->last_u = u;
  sgc->last_v = v;
}

void test_solution_graph_change_notice_rollback(void)
{
  const int node_ct = 5;
  int *majority_graph = edge_array_calloc(node_ct);
  SolutionGraph *sol = solution_graph_create(majority_graph, node_ct);
  SGC sgc = {
    .up_count = 0,
    .dn_count = 0
  };
  solution_graph_on_edge_change(sol, sg_test_edge_change, &sgc);

  int u = 0;
  int v = 4;
  int set_point = solution_graph_add_edge(sol, u, v);
  solution_graph_rollback(sol, set_point);

  cut_assert_equal_int(1, sgc.up_count);
  cut_assert_equal_int(1, sgc.dn_count);
  cut_assert_equal_int(u, sgc.last_u);
  cut_assert_equal_int(v, sgc.last_v);

  sol = solution_graph_destroy(sol);
  free(majority_graph);
}

void test_solution_graph_change_notice_transitive(void)
{
  const int node_ct = 5;
  int *majority_graph = edge_array_calloc(node_ct);
  SolutionGraph *sol = solution_graph_create(majority_graph, node_ct);
  SGC sgc = {
    .up_count = 0,
    .dn_count = 0
  };
  solution_graph_on_edge_change(sol, sg_test_edge_change, &sgc);

  int t = 0;
  int u = 1;
  int v = 4;
  int w = 3;
  int set_point = solution_graph_add_edge(sol, t, v);
  solution_graph_add_edge(sol, w, v);
  solution_graph_add_edge(sol, u, w);

  cut_assert_equal_int(u, sgc.last_u);
  cut_assert_equal_int(v, sgc.last_v);

  solution_graph_rollback(sol, set_point);

  cut_assert_equal_int(4, sgc.up_count);
  cut_assert_equal_int(4, sgc.dn_count);
  cut_assert_equal_int(t, sgc.last_u);
  cut_assert_equal_int(v, sgc.last_v);

  sol = solution_graph_destroy(sol);
  free(majority_graph);
}
