#include <cutter.h>
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
  memset(d->solution, 0, node_ct * sizeof(unsigned char));
  memset(d->components, 0, node_ct);
  memset(d->edge_list, 0, DV_EDGE_CT(node_ct));

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
  const int *solution = davenport_solution(d, 0);
  assert_equal_int_array(expected, solution, node_ct);
  cut_assert_null(davenport_solution(d, 1));

  d = davenport_destroy(d);
  free(majority_graph);
}
