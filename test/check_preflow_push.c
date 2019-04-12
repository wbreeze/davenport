#include <check.h>
#include <limits.h>
#include <stdlib.h>
#include "check_preflow_push.h"
#include "../src/network.h"
#include "../src/preflow_push.h"

typedef struct Network {
  int *excess;
  int *label;
  int *flow;
  int *capacity;
} Network;

Network *setup(int node_ct)
{
  Network *network = (Network *)malloc(sizeof(Network));
  network->excess = node_array_calloc(node_ct);
  network->label = node_array_calloc(node_ct);
  network->flow = edge_array_calloc(node_ct);
  network->capacity = edge_array_calloc(node_ct);
  return network;
}

void teardown(Network *network)
{
  free(network->excess);
  free(network->label);
  free(network->flow);
  free(network->capacity);
  free(network);
}

START_TEST(check_push_excess)
{
  int node_ct = 2;
  Network *n = setup(node_ct);
  int send = 4;
  int from = 0;
  int to = 1;

  n->excess[from] = send;
  n->capacity[RCI(from,to,node_ct)] = send + 1;
  n->flow[RCI(from,to,node_ct)] = 0;
  push(n->capacity, n->flow, n->excess, node_ct, from, to);
  ck_assert_int_eq(0, n->excess[from]);
  ck_assert_int_eq(send, n->excess[to]);
  ck_assert_int_eq(send, n->flow[RCI(from,to,node_ct)]);
  ck_assert_int_eq(-send, n->flow[RCI(to,from,node_ct)]);
  teardown(n);
}
END_TEST

START_TEST(check_push_capacity)
{
  int node_ct = 2;
  Network *n = setup(node_ct);
  int send = 4;
  int cap = 2;
  int from = 0;
  int to = 1;

  n->excess[from] = send;
  n->capacity[RCI(from,to,node_ct)] = cap;
  n->flow[RCI(from,to,node_ct)] = 0;
  push(n->capacity, n->flow, n->excess, node_ct, from, to);
  ck_assert_int_eq(send - cap, n->excess[from]);
  ck_assert_int_eq(cap, n->excess[to]);
  ck_assert_int_eq(cap, n->flow[RCI(from,to,node_ct)]);
  ck_assert_int_eq(-cap, n->flow[RCI(to,from,node_ct)]);
  teardown(n);
}
END_TEST

START_TEST(check_push_residual)
{
  int node_ct = 2;
  Network *n = setup(node_ct);
  int send = 4;
  int cap = 4;
  int existing = 2;
  int residual = cap - existing;
  int from = 0;
  int to = 1;

  n->excess[from] = send;
  n->capacity[RCI(from,to,node_ct)] = cap;
  n->flow[RCI(from,to,node_ct)] = existing;
  push(n->capacity, n->flow, n->excess, node_ct, from, to);
  ck_assert_int_eq(send - residual, n->excess[from]);
  ck_assert_int_eq(residual, n->excess[to]);
  ck_assert_int_eq(cap, n->flow[RCI(from,to,node_ct)]);
  ck_assert_int_eq(-residual, n->flow[RCI(to,from,node_ct)]);
  teardown(n);
}
END_TEST

START_TEST(check_relabel_max)
{
  int node_ct = 4;
  Network *n = setup(node_ct);
  int from = 0;

  relabel(n->capacity, n->flow, n->label, node_ct, from);
  ck_assert_int_eq(n->label[from], INT_MAX);

  teardown(n);
}
END_TEST

START_TEST(check_relabel_least)
{
  int node_ct = 4;
  Network *n = setup(node_ct);
  int from = 0;
  int to = 1;
  for(int l = 0; l < node_ct; ++l)
    n->label[l] = l;
  for(int v = to; v < node_ct; ++v)
    n->capacity[RCI(from, v, node_ct)] = 1;

  relabel(n->capacity, n->flow, n->label, node_ct, from);
  ck_assert_int_eq(n->label[from], n->label[to] + 1);

  teardown(n);
}
END_TEST

START_TEST(check_relabel_residual)
{
  int node_ct = 4;
  Network *n = setup(node_ct);
  int from = 0;
  int to = 2;
  for(int l = 0; l < node_ct; ++l)
    n->label[l] = l;
  for(int v = to; v < node_ct; ++v)
    n->capacity[RCI(from, v, node_ct)] = 1;

  relabel(n->capacity, n->flow, n->label, node_ct, from);
  ck_assert_int_eq(n->label[from], n->label[to] + 1);

  teardown(n);
}
END_TEST

Suite *make_preflow_push_suite(void)
{
  Suite *s;
  TCase *tc;

  s = suite_create("Preflow Push");
  tc = tcase_create("Core");

  suite_add_tcase (s, tc);
  tcase_add_test(tc, check_push_excess);
  tcase_add_test(tc, check_push_capacity);
  tcase_add_test(tc, check_push_residual);
  tcase_add_test(tc, check_relabel_max);
  tcase_add_test(tc, check_relabel_least);
  tcase_add_test(tc, check_relabel_residual);
  return s;
}
