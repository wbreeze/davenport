#include <cutter.h>
#include "test_helper.h"
#include "../src/network.h"
#include "../src/tarjan.h"

/*
 See docs/tarjan_tests.md for diagrams
*/

void test_tarjan_network_1(void)
{
  int node_ct = 8;
  int *edges = edge_array_calloc(node_ct);
  int *components = node_array_calloc(node_ct);

  set_majority_tarjan_example(edges, node_ct);

  Tarjan *t = tarjan_create(tarjan_default_edge_lookup, edges, node_ct);
  tarjan_identify_components(t, components);
  t = tarjan_destroy(t);

  cut_assert_equal_int(components[0], components[1]);
  cut_assert_equal_int(components[0], components[2]);
  cut_assert_not_equal_int(components[0], components[3]);
  cut_assert_not_equal_int(components[0], components[4]);
  cut_assert_not_equal_int(components[0], components[7]);
  cut_assert_equal_int(components[3], components[5]);
  cut_assert_not_equal_int(components[3], components[4]);
  cut_assert_not_equal_int(components[3], components[7]);
  cut_assert_equal_int(components[4], components[6]);
  cut_assert_not_equal_int(components[4], components[7]);

  free(components);
  free(edges);
}

void test_tarjan_network_2(void)
{
  int node_ct = 5;
  int *edges = edge_array_calloc(node_ct);
  int *components = node_array_calloc(node_ct);

  set_majority_net_pentagon_2(edges, node_ct);

  Tarjan *t = tarjan_create(tarjan_default_edge_lookup, edges, node_ct);
  tarjan_identify_components(t, components);
  t = tarjan_destroy(t);

  cut_assert_not_equal_int(0, components[0]);
  int *expected = node_array_calloc(node_ct);
  set_int_array(expected, components[0], node_ct);
  assert_equal_int_array(expected, components, node_ct);

  free(components);
  free(edges);
}

void test_tarjan_network_3(void)
{
  int node_ct = 5;
  int *edges = edge_array_calloc(node_ct);
  int *components = node_array_calloc(node_ct);

  set_majority_net_pentagon_3(edges, node_ct);

  Tarjan *t = tarjan_create(tarjan_default_edge_lookup, edges, node_ct);
  tarjan_identify_components(t, components);
  t = tarjan_destroy(t);

  cut_assert_not_equal_int(0, components[0]);
  int *expected = node_array_calloc(node_ct);
  set_int_array(expected, components[0], node_ct);
  assert_equal_int_array(expected, components, node_ct);

  free(components);
  free(edges);
}

void test_tarjan_network_4(void)
{
  int node_ct = 5;
  int *edges = edge_array_calloc(node_ct);
  int *components = node_array_calloc(node_ct);

  set_majority_net_pentagon_4(edges, node_ct);

  Tarjan *t = tarjan_create(tarjan_default_edge_lookup, edges, node_ct);
  tarjan_identify_components(t, components);
  t = tarjan_destroy(t);

  cut_assert_not_equal_int(0, components[0]);
  cut_assert_not_equal_int(components[0], components[1]);
  cut_assert_equal_int(components[1], components[2]);
  cut_assert_equal_int(components[1], components[4]);
  cut_assert_not_equal_int(components[3], components[0]);
  cut_assert_not_equal_int(components[3], components[1]);

  free(components);
  free(edges);
}

void test_tarjan_network_5(void)
{
  int node_ct = 5;
  int *edges = edge_array_calloc(node_ct);
  int *components = node_array_calloc(node_ct);

  set_majority_net_pentagon_5(edges, node_ct);

  Tarjan *t = tarjan_create(tarjan_default_edge_lookup, edges, node_ct);
  tarjan_identify_components(t, components);
  t = tarjan_destroy(t);

  cut_assert_not_equal_int(0, components[0]);
  cut_assert_not_equal_int(components[0], components[1]);
  cut_assert_not_equal_int(components[0], components[2]);
  cut_assert_not_equal_int(components[0], components[3]);
  cut_assert_not_equal_int(components[0], components[4]);
  cut_assert_not_equal_int(components[1], components[2]);
  cut_assert_not_equal_int(components[1], components[3]);
  cut_assert_not_equal_int(components[1], components[4]);
  cut_assert_not_equal_int(components[2], components[3]);
  cut_assert_not_equal_int(components[2], components[4]);
  cut_assert_not_equal_int(components[3], components[4]);

  free(components);
  free(edges);
}
