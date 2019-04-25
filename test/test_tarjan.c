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

  edges[RCI(0,1,node_ct)] = 1;
  edges[RCI(1,2,node_ct)] = 1;
  edges[RCI(2,0,node_ct)] = 1;
  edges[RCI(3,1,node_ct)] = 1;
  edges[RCI(3,2,node_ct)] = 1;
  edges[RCI(3,5,node_ct)] = 1;
  edges[RCI(4,2,node_ct)] = 1;
  edges[RCI(4,6,node_ct)] = 1;
  edges[RCI(5,3,node_ct)] = 1;
  edges[RCI(5,4,node_ct)] = 1;
  edges[RCI(6,4,node_ct)] = 1;
  edges[RCI(7,5,node_ct)] = 1;
  edges[RCI(7,6,node_ct)] = 1;
  edges[RCI(7,7,node_ct)] = 1;

  identify_components(edges, node_ct, components);

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
}

void test_tarjan_network_2(void)
{
  int node_ct = 5;
  int *edges = edge_array_calloc(node_ct);
  int *components = node_array_calloc(node_ct);

  set_majority_net_pentagon_2(edges, node_ct);

  identify_components(edges, node_ct, components);

  cut_assert_not_equal_int(0, components[0]);
  int *expected = node_array_calloc(node_ct);
  set_int_array(expected, components[0], node_ct);
  assert_equal_int_array(expected, components, node_ct);
}

void test_tarjan_network_3(void)
{
  int node_ct = 5;
  int *edges = edge_array_calloc(node_ct);
  int *components = node_array_calloc(node_ct);

  set_majority_net_pentagon_3(edges, node_ct);

  identify_components(edges, node_ct, components);

  cut_assert_not_equal_int(0, components[0]);
  int *expected = node_array_calloc(node_ct);
  set_int_array(expected, components[0], node_ct);
  assert_equal_int_array(expected, components, node_ct);
}

void test_tarjan_network_4(void)
{
  int node_ct = 5;
  int *edges = edge_array_calloc(node_ct);
  int *components = node_array_calloc(node_ct);

  set_majority_net_pentagon_4(edges, node_ct);

  identify_components(edges, node_ct, components);

  cut_assert_not_equal_int(0, components[0]);
  cut_assert_not_equal_int(components[0], components[1]);
  cut_assert_equal_int(components[1], components[2]);
  cut_assert_equal_int(components[1], components[4]);
  cut_assert_not_equal_int(components[3], components[0]);
  cut_assert_not_equal_int(components[3], components[1]);
}

void test_tarjan_network_5(void)
{
  int node_ct = 5;
  int *edges = edge_array_calloc(node_ct);
  int *components = node_array_calloc(node_ct);

  set_majority_net_pentagon_5(edges, node_ct);

  identify_components(edges, node_ct, components);

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
}
