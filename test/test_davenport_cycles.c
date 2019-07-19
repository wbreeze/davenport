#include <cutter.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include "../src/davenport.h"
#include "../src/network.h"
#include "array_init.h"
#include "test_helper.h"
#include "test_davenport.h"
#include "test_davenport_callback_context.h"

void test_davenport_compute_one_cycle_embedded(void)
{
  const int node_ct = 5;
  int *majority_graph = edge_array_calloc(node_ct);
  set_majority_net_one_cycle_embedded(majority_graph, node_ct);

  Davenport *d = davenport_create(majority_graph, node_ct);

  CallbackContext cbx;
  cbx.dv = d;
  cbx.seen_solution_ct = 0;
  cbx.valid_solutions = malloc(2 * sizeof(int *));
  int sol1[] = { 1, 2, 3, 4, 5 };
  int sol2[] = { 1, 4, 2, 3, 5 };
  cbx.valid_solutions[0] = sol1;
  cbx.valid_solutions[1] = sol2;
  cbx.valid_solution_ct = 2;
  cbx.expected_disagreements = 1;

  davenport_set_solution_callback(d, &handle_solution, &cbx);

  int solution_ct = davenport_compute(d);

  cut_assert_equal_int(cbx.seen_solution_ct, solution_ct);
  cut_assert_equal_int(cbx.seen_solution_ct, d->solution_ct);
  int *solution = davenport_last_solution(d);
  assert_equal_int_array(cbx.last_solution, solution, node_ct);

  free(cbx.valid_solutions);
  d = davenport_destroy(d);
  free(majority_graph);
}

void test_davenport_compute_multi_cycle_embedded(void)
{
  const int node_ct = 8;
  int *majority_graph = edge_array_calloc(node_ct);
  set_majority_net_multi_cycle_embedded(majority_graph, node_ct);

  Davenport *d = davenport_create(majority_graph, node_ct);

  CallbackContext cbx;
  cbx.dv = d;
  cbx.seen_solution_ct = 0;
  cbx.expected_disagreements = 4;
  cbx.valid_solution_ct = 0;

  davenport_set_solution_callback(d, &handle_solution, &cbx);

  int solution_ct = davenport_compute(d);

  cut_assert_equal_int(cbx.seen_solution_ct, solution_ct);
  cut_assert_equal_int(cbx.seen_solution_ct, d->solution_ct);
  int expected[node_ct];
  int_array_init(expected, node_ct, 1, 3, 4, 2, 5, 6, 7, 8);
  int *solution = davenport_last_solution(d);
  assert_equal_int_array(expected, solution, node_ct);

  d = davenport_destroy(d);
  free(majority_graph);
}

void test_davenport_compute_two_embedded_cycles(void)
{
  const int node_ct = 8;
  int *majority_graph = edge_array_calloc(node_ct);
  set_majority_net_two_embedded_cycles(majority_graph, node_ct);
  majority_graph[RCI(0,7,node_ct)] = 7;

  Davenport *d = davenport_create(majority_graph, node_ct);

  CallbackContext cbx;
  cbx.dv = d;
  cbx.seen_solution_ct = 0;
  cbx.expected_disagreements = 2;
  cbx.valid_solution_ct = 0;

  davenport_set_solution_callback(d, &handle_solution, &cbx);

  int solution_ct = davenport_compute(d);

  cut_assert_equal_int(cbx.seen_solution_ct, solution_ct);
  cut_assert_equal_int(cbx.seen_solution_ct, d->solution_ct);
  int expected[node_ct];
  int_array_init(expected, node_ct, 1, 4, 5, 6, 7, 8, 1, 3);
  int *solution = davenport_last_solution(d);
  assert_equal_int_array(expected, solution, node_ct);

  d = davenport_destroy(d);
  free(majority_graph);
}
