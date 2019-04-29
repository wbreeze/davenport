#include <cutter.h>
#include <stdlib.h>
#include "../src/davenport.h"
#include "../src/network.h"
#include "test_helper.h"
#include "test_davenport.h"

void test_dv_maybe_add_solution_empty(void)
{
  int node_ct = 5;
  int *majority_graph = edge_array_calloc(node_ct);
  Davenport *dv = davenport_create(majority_graph, node_ct);

  set_int_array(dv->components, 1, node_ct);

  int disagreement_ct = 0;
  dv_maybe_add_solution(dv, disagreement_ct);

  assert_equal_int_array(dv->components, davenport_solution(dv, 0), node_ct);
  cut_assert_equal_int(1, dv->solution_ct);

  dv = davenport_destroy(dv);
  free(majority_graph);
}

void test_dv_maybe_add_solution_replace_one(void)
{
  int node_ct = 5;
  int *majority_graph = edge_array_calloc(node_ct);
  Davenport *dv = davenport_create(majority_graph, node_ct);

  set_int_array(dv->components, 1, node_ct);
  int disagreement_ct = 5;
  dv_maybe_add_solution(dv, disagreement_ct);
  set_int_array(dv->components, 2, node_ct);
  --disagreement_ct;
  dv_maybe_add_solution(dv, disagreement_ct);

  assert_equal_int_array(dv->components, davenport_solution(dv, 0), node_ct);
  cut_assert_equal_int(1, dv->solution_ct);

  dv = davenport_destroy(dv);
  free(majority_graph);
}

void test_dv_maybe_add_solution_ignore_worse(void)
{
  int node_ct = 5;
  int *majority_graph = edge_array_calloc(node_ct);
  Davenport *dv = davenport_create(majority_graph, node_ct);

  set_int_array(dv->components, 1, node_ct);
  int disagreement_ct = 5;
  dv_maybe_add_solution(dv, disagreement_ct);

  int *solution_save = node_array_calloc(node_ct);
  memcpy(solution_save, davenport_solution(dv, 0), NSZ(node_ct));

  set_int_array(dv->components, 2, node_ct);
  ++disagreement_ct;
  dv_maybe_add_solution(dv, disagreement_ct);

  assert_equal_int_array(solution_save, davenport_solution(dv, 0), node_ct);
  cut_assert_equal_int(1, dv->solution_ct);

  dv = davenport_destroy(dv);
  free(majority_graph);
  free(solution_save);
}
