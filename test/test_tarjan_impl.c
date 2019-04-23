#include <cutter.h>
#include "test_helper.h"
#include "test_tarjan.h"
#include "../src/network.h"

void test_tarjan_new(void)
{
  int node_ct = 6;
  int *edges = edge_array_calloc(node_ct);
  int *components = node_array_calloc(node_ct);
  Tarjan *tarjan = tarjan_new(edges, node_ct, components);

  cut_assert_equal_int(node_ct, tarjan->node_ct);
  cut_assert_equal_pointer(edges, tarjan->edges);
  cut_assert_equal_pointer(components, tarjan->lowlink);
  memset(tarjan->index, 1, node_ct);
  cut_assert_equal_int(1, tarjan->next_index);
  cut_assert_equal_int(0, tarjan->depth);
  set_int_array(tarjan->stack, 1, node_ct);
  memset(tarjan->onstack, 1, node_ct);

  tarjan = tarjan_destroy(tarjan);
}

void test_tarjan_push(void)
{
  int node_ct = 6;
  int *edges = edge_array_calloc(node_ct);
  int *components = node_array_calloc(node_ct);
  Tarjan *tarjan = tarjan_new(edges, node_ct, components);

  tarjan_push(tarjan, node_ct + 1);
  cut_assert_equal_int(0, tarjan->depth);

  for (int i = 0; i < node_ct; ++i) {
    tarjan_push(tarjan, i);
    cut_assert_equal_int(i, tarjan->stack[i]);
    cut_assert_true(tarjan->onstack[i]);
  }
  cut_assert_equal_int(node_ct, tarjan->depth);

  tarjan_push(tarjan, 1);
  cut_assert_equal_int(node_ct, tarjan->depth);

  tarjan = tarjan_destroy(tarjan);
}

void test_tarjan_pop(void)
{
  int node_ct = 6;
  int *edges = edge_array_calloc(node_ct);
  int *components = node_array_calloc(node_ct);
  Tarjan *tarjan = tarjan_new(edges, node_ct, components);

  int v = tarjan_pop(tarjan);
  cut_assert_equal_int(0, v);
  cut_assert_equal_int(0, tarjan->depth);

  int i = node_ct - 2;
  tarjan_push(tarjan, i);
  cut_assert_equal_int(i, tarjan->stack[0]);
  cut_assert_true(tarjan->onstack[i]);
  cut_assert_equal_int(1, tarjan->depth);

  v = tarjan_pop(tarjan);
  cut_assert_equal_int(i, v);
  cut_assert_false(tarjan->onstack[v]);
  cut_assert_equal_int(0, tarjan->depth);

  tarjan = tarjan_destroy(tarjan);
}

void test_tarjan_next_index(void)
{
  int node_ct = 6;
  int *edges = edge_array_calloc(node_ct);
  int *components = node_array_calloc(node_ct);
  Tarjan *tarjan = tarjan_new(edges, node_ct, components);

  cut_assert_equal_int(1, tarjan->next_index);
  cut_assert_equal_int(1, tarjan_next_index(tarjan));
  cut_assert_equal_int(2, tarjan->next_index);
  cut_assert_equal_int(2, tarjan_next_index(tarjan));
  cut_assert_equal_int(3, tarjan->next_index);

  tarjan = tarjan_destroy(tarjan);
}
