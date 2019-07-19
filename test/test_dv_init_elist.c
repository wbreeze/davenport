#include <cutter.h>
#include <stdlib.h>
#include "../src/davenport.h"
#include "../src/network.h"
#include "array_init.h"
#include "test_helper.h"
#include "test_davenport.h"

void test_initialize_elist_pentagon_2(void)
{
  int node_ct = 5;
  int *majority_graph = edge_array_calloc(node_ct);
  Davenport *d = davenport_create(majority_graph, node_ct);
  set_majority_net_pentagon_2(majority_graph, node_ct);

  dv_initialize_solution(d);

  const int edge_ct = 7;
  cut_assert_equal_int(edge_ct, d->edge_ct);
  int expected_weights[edge_ct];
  int_array_init(expected_weights, edge_ct, 3, 3, 3, 2, 2, 2, 2);
  for (int i = 0; i < edge_ct; ++ i)
    cut_assert_equal_int(expected_weights[i], majority_graph[d->edge_list[i]]);
}

void test_initialize_elist_pentagon_5(void)
{
  int node_ct = 5;
  int *majority_graph = edge_array_calloc(node_ct);
  Davenport *d = davenport_create(majority_graph, node_ct);
  set_majority_net_pentagon_5(majority_graph, node_ct);

  dv_initialize_solution(d);

  cut_assert_equal_int(0, d->edge_ct);
}

void test_initialize_elist_multi_cycle_embedded(void)
{
  int node_ct = 8;
  int *majority_graph = edge_array_calloc(node_ct);
  Davenport *d = davenport_create(majority_graph, node_ct);
  set_majority_net_multi_cycle_embedded(majority_graph, node_ct);

  dv_initialize_solution(d);

  cut_assert_equal_int(10, d->edge_ct);
  cut_assert_equal_int(6, majority_graph[d->edge_list[0]]);
  cut_assert_equal_int(6, majority_graph[d->edge_list[1]]);
  cut_assert_equal_int(6, majority_graph[d->edge_list[2]]);
  cut_assert_equal_int(4, majority_graph[d->edge_list[3]]);
  cut_assert_equal_int(3, majority_graph[d->edge_list[4]]);
  cut_assert_equal_int(3, majority_graph[d->edge_list[5]]);
  cut_assert_equal_int(2, majority_graph[d->edge_list[6]]);
}

void test_initialize_elist_two_embedded_cycles(void)
{
  int node_ct = 8;
  int *majority_graph = edge_array_calloc(node_ct);
  Davenport *d = davenport_create(majority_graph, node_ct);
  set_majority_net_two_embedded_cycles(majority_graph, node_ct);

  dv_initialize_solution(d);

  int edge_ct = 6;
  cut_assert_equal_int(6, d->edge_ct);
  cut_assert_equal_int(2, majority_graph[d->edge_list[0]]);
  cut_assert_equal_int(2, majority_graph[d->edge_list[1]]);
  cut_assert_equal_int(1, majority_graph[d->edge_list[3]]);
}
