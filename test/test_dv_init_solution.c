#include <cutter.h>
#include <stdlib.h>
#include "../src/davenport.h"
#include "../src/network.h"
#include "test_helper.h"
#include "test_davenport.h"

void test_initialize_solution_pentagon_2(void)
{
  int node_ct = 5;
  int *majority_graph = edge_array_calloc(node_ct);
  Davenport *d = davenport_create(majority_graph, node_ct);
  set_majority_net_pentagon_2(majority_graph, node_ct);

  dv_initialize_solution(d);

  for (int u = 0; u < node_ct; ++u)
    for (int v = 0; v < node_ct; ++v)
      cut_assert_false(solution_graph_has_edge(d->solution_graph, u, v));

  d = davenport_destroy(d);
  free(majority_graph);
}

void test_initialize_solution_pentagon_5(void)
{
  int node_ct = 5;
  int *majority_graph = edge_array_calloc(node_ct);
  Davenport *d = davenport_create(majority_graph, node_ct);
  set_majority_net_pentagon_5(majority_graph, node_ct);

  dv_initialize_solution(d);

  cut_assert_false(solution_graph_has_edge(d->solution_graph,0,0));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,3,3));
  cut_assert_true(solution_graph_has_edge(d->solution_graph,3,4));
  cut_assert_true(solution_graph_has_edge(d->solution_graph,3,0));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,0,3));
  cut_assert_true(solution_graph_has_edge(d->solution_graph,3,1));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,1,3));
  cut_assert_true(solution_graph_has_edge(d->solution_graph,3,2));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,2,3));
  cut_assert_true(solution_graph_has_edge(d->solution_graph,4,0));
  cut_assert_true(solution_graph_has_edge(d->solution_graph,4,1));
  cut_assert_true(solution_graph_has_edge(d->solution_graph,4,2));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,2,4));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,1,2));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,2,1));

  d = davenport_destroy(d);
  free(majority_graph);
}

void test_initialize_solution_one_cycle_embedded(void)
{
  int node_ct = 5;
  int *majority_graph = edge_array_calloc(node_ct);
  Davenport *d = davenport_create(majority_graph, node_ct);
  set_majority_net_one_cycle_embedded(majority_graph, node_ct);

  dv_initialize_solution(d);

  cut_assert_true(solution_graph_has_edge(d->solution_graph,0,1));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,0,2));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,0,3));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,0,4));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,1,0));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,1,2));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,1,3));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,1,4));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,2,0));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,2,1));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,2,3));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,2,4));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,3,0));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,3,2));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,3,1));
  cut_assert_true(solution_graph_has_edge(d->solution_graph,3,4));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,4,0));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,4,1));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,4,2));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,4,3));

  d = davenport_destroy(d);
  free(majority_graph);
}

void test_initialize_solution_multi_cycle_embedded(void)
{
  int node_ct = 8;
  int *majority_graph = edge_array_calloc(node_ct);
  Davenport *d = davenport_create(majority_graph, node_ct);
  set_majority_net_multi_cycle_embedded(majority_graph, node_ct);

  dv_initialize_solution(d);

  cut_assert_false(solution_graph_has_edge(d->solution_graph,0,0));
  cut_assert_true(solution_graph_has_edge(d->solution_graph,0,1));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,0,2));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,0,3));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,0,4));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,0,5));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,0,6));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,0,7));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,1,0));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,1,1));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,1,2));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,1,3));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,1,4));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,1,5));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,1,6));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,1,7));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,2,0));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,2,1));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,2,2));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,2,3));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,2,4));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,2,5));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,2,6));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,2,7));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,3,0));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,3,1));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,3,2));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,3,3));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,3,4));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,3,5));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,3,6));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,3,7));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,4,0));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,4,1));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,4,2));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,4,3));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,4,4));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,4,5));
  cut_assert_true(solution_graph_has_edge(d->solution_graph,4,6));
  cut_assert_true(solution_graph_has_edge(d->solution_graph,4,7));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,5,0));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,5,1));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,5,2));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,5,3));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,5,4));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,5,5));
  cut_assert_true(solution_graph_has_edge(d->solution_graph,5,6));
  cut_assert_true(solution_graph_has_edge(d->solution_graph,5,7));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,6,0));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,6,1));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,6,2));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,6,3));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,6,4));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,6,5));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,6,6));
  cut_assert_true(solution_graph_has_edge(d->solution_graph,6,7));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,7,0));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,7,1));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,7,2));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,7,3));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,7,4));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,7,5));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,7,6));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,7,7));

  d = davenport_destroy(d);
  free(majority_graph);
}

void test_initialize_solution_two_embedded_cycles(void)
{
  int node_ct = 8;
  int *majority_graph = edge_array_calloc(node_ct);
  Davenport *d = davenport_create(majority_graph, node_ct);
  set_majority_net_two_embedded_cycles(majority_graph, node_ct);

  dv_initialize_solution(d);

  cut_assert_false(solution_graph_has_edge(d->solution_graph,0,0));
  cut_assert_true(solution_graph_has_edge(d->solution_graph,0,1));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,0,2));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,0,3));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,0,4));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,0,5));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,0,6));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,0,7));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,1,0));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,1,1));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,1,2));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,1,3));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,1,4));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,1,5));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,1,6));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,1,7));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,2,0));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,2,1));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,2,2));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,2,3));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,2,4));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,2,5));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,2,6));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,2,7));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,3,0));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,3,1));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,3,2));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,3,3));
  cut_assert_true(solution_graph_has_edge(d->solution_graph,3,4));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,3,5));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,3,6));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,3,7));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,4,0));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,4,1));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,4,2));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,4,3));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,4,4));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,4,5));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,4,6));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,4,7));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,5,0));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,5,1));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,5,2));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,5,3));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,5,4));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,5,5));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,5,6));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,5,7));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,6,0));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,6,1));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,6,2));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,6,3));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,6,4));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,6,5));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,6,6));
  cut_assert_true(solution_graph_has_edge(d->solution_graph,6,7));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,7,0));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,7,1));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,7,2));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,7,3));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,7,4));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,7,5));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,7,6));
  cut_assert_false(solution_graph_has_edge(d->solution_graph,7,7));

  d = davenport_destroy(d);
  free(majority_graph);
}
