#include <cutter.h>
#include <limits.h>
#include <stdlib.h>
#include "../src/davenport.h"
#include "../src/network.h"
#include "test_helper.h"
#include "test_davenport.h"

void test_davenport_create(void)
{
  int node_ct = 4;
  int *majority_graph = edge_array_calloc(node_ct);

  Davenport *d = davenport_create(majority_graph, node_ct);

  cut_assert(d != NULL);
  cut_assert_equal_pointer(majority_graph, d->majority_graph);
  cut_assert_equal_int(node_ct, d->node_ct);
  memset(d->solution_graph, 0, node_ct * sizeof(unsigned char));
  clear_int_array(d->components, node_ct);
  clear_int_array(d->topo_sort, node_ct);
  memset(d->edge_list, 0, DG_ESZ(node_ct));
  cut_assert_equal_int(0, d->solution_ct);
  clear_int_array(d->solution, node_ct);
  cut_assert_equal_int(INT_MAX, d->best_found);

  d = davenport_destroy(d);
  cut_assert_equal_pointer(NULL, d);
  free(majority_graph);
}

void test_davenport_compute_small_no_cycles(void)
{
  const int node_ct = 4;
  int *majority_graph = edge_array_calloc(node_ct);
  set_majority_net_no_cycles(majority_graph, node_ct);

  Davenport *d = davenport_create(majority_graph, node_ct);

  int solution_ct = davenport_compute(d);

  cut_assert_equal_int(1, solution_ct);
  cut_assert_equal_int(1, d->solution_ct);
  const int expected[node_ct] = {1, 2, 3, 4};
  int *solution = davenport_solution(d, 0);
  assert_equal_int_array(expected, solution, node_ct);
  cut_assert_null(davenport_solution(d, 1));

  d = davenport_destroy(d);
  free(majority_graph);
}

void test_davenport_compute_partial_no_cycles(void)
{
  const int node_ct = 4;
  int *majority_graph = edge_array_calloc(node_ct);
  set_majority_net_partial_no_cycles(majority_graph, node_ct);

  Davenport *d = davenport_create(majority_graph, node_ct);

  int solution_ct = davenport_compute(d);

  cut_assert_equal_int(1, solution_ct);
  cut_assert_equal_int(1, d->solution_ct);
  const int expected[node_ct] = {1, 2, 2, 4};
  int *solution = davenport_solution(d, 0);
  assert_equal_int_array(expected, solution, node_ct);
  cut_assert_null(davenport_solution(d, 1));

  d = davenport_destroy(d);
  free(majority_graph);
}

void test_davenport_compute_one_cycle_embedded(void)
{
  const int node_ct = 5;
  int *majority_graph = edge_array_calloc(node_ct);
  set_majority_net_one_cycle_embedded(majority_graph, node_ct);
  majority_graph[RCI(0,4,node_ct)] = 2;
  majority_graph[RCI(0,2,node_ct)] = 2;
  majority_graph[RCI(0,3,node_ct)] = 2;
  majority_graph[RCI(1,4,node_ct)] = 2;
  majority_graph[RCI(2,4,node_ct)] = 2;

  Davenport *d = davenport_create(majority_graph, node_ct);

  int solution_ct = davenport_compute(d);

  cut_assert_equal_int(1, solution_ct);
  cut_assert_equal_int(1, d->solution_ct);
  const int expected[node_ct] = {1, 2, 3, 4, 5};
  int *solution = davenport_solution(d, 0);
  assert_equal_int_array(expected, solution, node_ct);
  cut_assert_null(davenport_solution(d, 1));

  d = davenport_destroy(d);
  free(majority_graph);
}

void test_davenport_compute_multi_cycle_embedded(void)
{
  const int node_ct = 8;
  int *majority_graph = edge_array_calloc(node_ct);
  set_majority_net_multi_cycle_embedded(majority_graph, node_ct);

  Davenport *d = davenport_create(majority_graph, node_ct);

  int solution_ct = davenport_compute(d);

  cut_assert_equal_int(1, solution_ct);
  cut_assert_equal_int(1, d->solution_ct);
  const int expected[node_ct] = {1, 2, 3, 6, 4, 5, 6, 8};
  int *solution = davenport_solution(d, 0);
  assert_equal_int_array(expected, solution, node_ct);
  cut_assert_null(davenport_solution(d, 1));

  d = davenport_destroy(d);
  free(majority_graph);
}

void test_davenport_compute_two_embedded_cycles(void)
{
  const int node_ct = 8;
  int *majority_graph = edge_array_calloc(node_ct);
  set_majority_net_two_embedded_cycles(majority_graph, node_ct);

  Davenport *d = davenport_create(majority_graph, node_ct);

  int solution_ct = davenport_compute(d);

  cut_assert_equal_int(1, solution_ct);
  cut_assert_equal_int(1, d->solution_ct);
  const int expected[node_ct] = {1, 2, 3, 4, 5, 6, 7, 8};
  int *solution = davenport_solution(d, 0);
  assert_equal_int_array(expected, solution, node_ct);
  cut_assert_null(davenport_solution(d, 1));

  d = davenport_destroy(d);
  free(majority_graph);
}
