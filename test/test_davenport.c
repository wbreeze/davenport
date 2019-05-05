#include <cutter.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
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
  cut_assert_null(d->solution_callback);

  d = davenport_destroy(d);
  cut_assert_null(d);
  free(majority_graph);
}

typedef struct CallbackContext {
  Davenport *dv;
  int expected_disagreements;
  int seen_solution_ct;
  int *last_solution;
  int valid_solution_ct;
  int **valid_solutions;
} CallbackContext;

void handle_solution(void *context, int *ranking, int node_ct,
  int disagreement_ct)
{
  CallbackContext *cbx = (CallbackContext *)context;
  cbx->last_solution = ranking;
  Davenport *dv = cbx->dv;
  if (disagreement_ct == cbx->expected_disagreements) {
    ++cbx->seen_solution_ct;
    unsigned char match = (0 == cbx->valid_solution_ct);
    int next_valid = 0;
    while (match == 0 && next_valid < cbx->valid_solution_ct) {
      int cmp = memcmp(cbx->valid_solutions[next_valid], ranking, NSZ(node_ct));
      if (cmp == 0) match = 1;
      ++next_valid;
    }
    cut_assert_true(match,
      cut_message("Solution matches expected valid solution"));
  }
  if (disagreement_ct < cbx->expected_disagreements) {
    cut_fail("Have %d disagreements; best expected is %d\n", disagreement_ct,
      cbx->expected_disagreements);
  }
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
  int *solution = davenport_last_solution(d);
  assert_equal_int_array(expected, solution, node_ct);

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
  int *solution = davenport_last_solution(d);
  assert_equal_int_array(expected, solution, node_ct);

  d = davenport_destroy(d);
  free(majority_graph);
}

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
  const int expected[node_ct] = {1, 3, 4, 2, 5, 6, 7, 8};
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
  const int expected[node_ct] = {1, 4, 5, 6, 7, 8, 1, 3};
  int *solution = davenport_last_solution(d);
  assert_equal_int_array(expected, solution, node_ct);

  d = davenport_destroy(d);
  free(majority_graph);
}
