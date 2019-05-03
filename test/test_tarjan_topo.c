#include <cutter.h>
#include "test_helper.h"
#include "../src/network.h"
#include "../src/tarjan.h"

void test_tarjan_topo_partial_no_cycles(void)
{
  const int node_ct = 4;
  int *edges = edge_array_calloc(node_ct);
  set_majority_net_partial_no_cycles(edges, node_ct);
  int *components = node_array_calloc(node_ct);

  Tarjan *t = tarjan_create(tarjan_default_edge_lookup, edges, node_ct);
  tarjan_identify_components(t, components);
  t = tarjan_destroy(t);

  int expected[node_ct] = { 4, 2, 3, 1 };
  assert_equal_int_array(expected, components, node_ct);

  free(components);
  free(edges);
}

void test_tarjan_topo_no_cycles(void)
{
  const int node_ct = 4;
  int *edges = edge_array_calloc(node_ct);
  set_majority_net_no_cycles(edges, node_ct);
  int *components = node_array_calloc(node_ct);

  Tarjan *t = tarjan_create(tarjan_default_edge_lookup, edges, node_ct);
  tarjan_identify_components(t, components);
  t = tarjan_destroy(t);

  int expected[node_ct] = { 4, 3, 2, 1 };
  assert_equal_int_array(expected, components, node_ct);

  free(components);
  free(edges);
}

void test_tarjan_topo_two_embedded_cycles(void)
{
  const int node_ct = 8;
  int *edges = edge_array_calloc(node_ct);
  set_majority_net_two_embedded_cycles(edges, node_ct);
  int *components = node_array_calloc(node_ct);

  Tarjan *t = tarjan_create(tarjan_default_edge_lookup, edges, node_ct);
  tarjan_identify_components(t, components);
  t = tarjan_destroy(t);

  int expected[node_ct] = { 8, 5, 5, 5, 2, 2, 2, 1 };
  assert_equal_int_array(expected, components, node_ct);

  free(components);
  free(edges);
}
