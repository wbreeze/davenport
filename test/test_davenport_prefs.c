#include <cutter.h>
#include <stdlib.h>
#include "../src/davenport.h"
#include "../src/network.h"
#include "../src/preference_graph.h"
#include "test_helper.h"
#include "test_davenport.h"
#include "test_davenport_callback_context.h"

void test_davenport_compute_preference_net_1(void)
{
  const int node_ct = 5;
  int *preference_graph = edge_array_calloc(node_ct);
  int *majority_graph = edge_array_calloc(node_ct);
  set_preference_net_1(preference_graph, node_ct);
  preference_graph_to_majority_graph(preference_graph, majority_graph, node_ct);

  Davenport *d = davenport_create(majority_graph, node_ct);

  CallbackContext cbx;
  cbx.dv = d;
  cbx.seen_solution_ct = 0;
  cbx.valid_solution_ct = 1;
  cbx.valid_solutions = malloc(cbx.valid_solution_ct * sizeof(int *));
  int r1[] = { 1, 2, 4, 5, 3 };
  cbx.valid_solutions[0] = r1;
  cbx.expected_disagreements = 2;

  davenport_set_solution_callback(d, &handle_solution, &cbx);

  int solution_ct = davenport_compute(d);
  cut_assert_equal_int(cbx.seen_solution_ct, solution_ct);

  free(cbx.valid_solutions);
  d = davenport_destroy(d);
  free(majority_graph);
  free(preference_graph);
}
