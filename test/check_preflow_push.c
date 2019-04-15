#include <check.h>
#include <limits.h>
#include <stdlib.h>
#include "check_helper.h"
#include "check_preflow_push.h"
#include "../src/network.h"
#include "../src/preflow_push.h"

typedef struct Network {
  int *excess;
  int *labels;
  int *seen;
  int *node_scratch;
  int *flow;
  int *capacity;
  int *edge_scratch;
} Network;

Network *setup(int node_ct)
{
  Network *network = (Network *)malloc(sizeof(Network));
  network->excess = node_array_calloc(node_ct);
  network->labels = node_array_calloc(node_ct);
  network->seen = node_array_calloc(node_ct);
  network->node_scratch = node_array_calloc(node_ct);
  network->capacity = edge_array_calloc(node_ct);
  network->flow = edge_array_calloc(node_ct);
  network->edge_scratch = edge_array_calloc(node_ct);
  return network;
}

void teardown(Network *network)
{
  free(network->excess);
  free(network->labels);
  free(network->seen);
  free(network->node_scratch);
  free(network->capacity);
  free(network->flow);
  free(network->edge_scratch);
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
  int label = 3;
  n->labels[from] = label;

  relabel(n->capacity, n->flow, n->labels, node_ct, from);
  ck_assert_int_eq(n->labels[from], label);

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
    n->labels[l] = l;
  for(int v = to; v < node_ct; ++v)
    n->capacity[RCI(from, v, node_ct)] = 1;

  relabel(n->capacity, n->flow, n->labels, node_ct, from);
  ck_assert_int_eq(n->labels[from], n->labels[to] + 1);

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
    n->labels[l] = l;
  for(int v = to; v < node_ct; ++v)
    n->capacity[RCI(from, v, node_ct)] = 1;

  relabel(n->capacity, n->flow, n->labels, node_ct, from);
  ck_assert_int_eq(n->labels[from], n->labels[to] + 1);

  teardown(n);
}
END_TEST

void setup_discharge_capacities(Network *n, int node_ct, int from, int cap)
{
  for (int v = from + 1; v < node_ct; ++v)
  {
    n->capacity[RCI(from,v,node_ct)] = cap;
  }
}

START_TEST(check_discharge_no_excess)
{
  int node_ct = 4;
  int from = 0;
  int cap = 2;
  int from_label = 1;
  Network *n = setup(node_ct);
  setup_discharge_capacities(n, node_ct, from, cap);
  n->labels[from] = from_label;
  copy_int_array(n->node_scratch, n->labels, node_ct);
  copy_int_array(n->edge_scratch, n->flow, ECT(node_ct));

  discharge(n->capacity, n->flow, n->excess, n->labels, n->seen, node_ct, from);

  check_assert_int_array_eq(n->node_scratch, n->labels, node_ct);
  clear_int_array(n->node_scratch, node_ct);
  check_assert_int_array_eq(n->node_scratch, n->excess, node_ct);
  check_assert_int_array_eq(n->edge_scratch, n->flow, node_ct);

  teardown(n);
}
END_TEST

START_TEST(check_discharge_saturates)
{
  int node_ct = 4;
  int from = 0;
  int cap = 2;
  int from_excess = (node_ct - 1) * cap;
  int from_label = 1;
  Network *n = setup(node_ct);
  setup_discharge_capacities(n, node_ct, from, cap);
  n->excess[from] = from_excess;
  n->labels[from] = from_label;
  copy_int_array(n->node_scratch, n->labels, node_ct);

  discharge(n->capacity, n->flow, n->excess, n->labels, n->seen, node_ct, from);

  check_assert_int_array_eq(n->node_scratch, n->labels, node_ct);

  set_int_array(n->node_scratch, cap, node_ct);
  n->node_scratch[from] = 0;
  check_assert_int_array_eq(n->node_scratch, n->excess, node_ct);

  check_assert_int_array_eq(n->capacity, n->flow, node_ct);

  teardown(n);
}
END_TEST

START_TEST(check_discharge_relabels)
{
  int node_ct = 2;
  int cap = 4;
  int from = 0;
  int to = 1;
  int from_excess = 4;
  int to_label = 1;
  Network *n = setup(node_ct);
  setup_discharge_capacities(n, node_ct, from, cap);
  n->excess[from] = from_excess;
  n->labels[to] = to_label;

  discharge(n->capacity, n->flow, n->excess, n->labels, n->seen, node_ct, from);

  set_int_array(n->node_scratch, 1, node_ct);
  n->node_scratch[from] = 0;
  n->node_scratch[to] = from_excess;
  check_assert_int_array_eq(n->node_scratch, n->excess, node_ct);

  clear_int_array(n->node_scratch, node_ct);
  n->node_scratch[to] = to_label;
  n->node_scratch[from] = to_label + 1;
  check_assert_int_array_eq(n->node_scratch, n->labels, node_ct);

  teardown(n);
}
END_TEST

START_TEST(check_discharge_existing_flow)
{
  int node_ct = 4;
  int from = 1;
  Network *n = setup(node_ct);
  n->capacity[RCI(0,from,node_ct)] = 3;
  n->capacity[RCI(from,2,node_ct)] = 2;
  n->capacity[RCI(from,3,node_ct)] = 2;
  n->labels[0] = 2;
  n->labels[from] = 1;
  copy_int_array(n->node_scratch, n->labels, node_ct);
  n->flow[RCI(0,from,node_ct)] = 3;
  n->flow[RCI(from,0,node_ct)] = -3;
  n->flow[RCI(from,3,node_ct)] = 1;
  n->flow[RCI(3,from,node_ct)] = -1;
  n->excess[from] = 3;
  n->excess[3] = 1;

  discharge(n->capacity, n->flow, n->excess, n->labels, n->seen, node_ct, from);

  check_assert_int_array_eq(n->node_scratch, n->labels, node_ct);

  n->edge_scratch[RCI(0,from,node_ct)] = 3;
  n->edge_scratch[RCI(from,0,node_ct)] = -3;
  n->edge_scratch[RCI(from,3,node_ct)] = 2;
  n->edge_scratch[RCI(3,from,node_ct)] = -2;
  n->edge_scratch[RCI(from,2,node_ct)] = 2;
  n->edge_scratch[RCI(2,from,node_ct)] = -2;
  check_assert_int_array_eq(n->edge_scratch, n->flow, node_ct);

  clear_int_array(n->node_scratch, node_ct);
  n->node_scratch[2] = 2;
  n->node_scratch[3] = 2;
  check_assert_int_array_eq(n->node_scratch, n->excess, node_ct);

  teardown(n);
}
END_TEST

START_TEST(check_discharge_excess_backflow)
{
  int node_ct = 4;
  int from = 1;
  Network *n = setup(node_ct);
  n->capacity[RCI(0,from,node_ct)] = 4;
  n->capacity[RCI(from,2,node_ct)] = 1;
  n->capacity[RCI(from,3,node_ct)] = 1;
  n->excess[from] = 4;
  n->labels[0] = 2;
  n->labels[from] = 1;
  copy_int_array(n->node_scratch, n->labels, node_ct);
  n->flow[RCI(0,from,node_ct)] = 4;
  n->flow[RCI(from,0,node_ct)] = -4;

  discharge(n->capacity, n->flow, n->excess, n->labels, n->seen, node_ct, from);

  n->node_scratch[from] = 3;
  check_assert_int_array_eq(n->node_scratch, n->labels, node_ct);

  n->edge_scratch[RCI(0,from,node_ct)] = 2;
  n->edge_scratch[RCI(from,0,node_ct)] = -2;
  n->edge_scratch[RCI(from,3,node_ct)] = 1;
  n->edge_scratch[RCI(3,from,node_ct)] = -1;
  n->edge_scratch[RCI(from,2,node_ct)] = 1;
  n->edge_scratch[RCI(2,from,node_ct)] = -1;
  check_assert_int_array_eq(n->edge_scratch, n->flow, node_ct);

  clear_int_array(n->node_scratch, node_ct);
  n->node_scratch[0] = 2;
  n->node_scratch[2] = 1;
  n->node_scratch[3] = 1;
  check_assert_int_array_eq(n->node_scratch, n->excess, node_ct);

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
  tcase_add_test(tc, check_discharge_no_excess);
  tcase_add_test(tc, check_discharge_saturates);
  tcase_add_test(tc, check_discharge_relabels);
  tcase_add_test(tc, check_discharge_existing_flow);
  tcase_add_test(tc, check_discharge_excess_backflow);

  return s;
}
