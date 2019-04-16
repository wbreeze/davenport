#include <cutter.h>
#include <limits.h>
#include <stdlib.h>
#include "test_helper.h"
#include "test_preflow_push.h"
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

Network *network_new(int node_ct)
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

void network_free(Network *network)
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

void test_push_excess(void)
{
  int node_ct = 2;
  Network *n = network_new(node_ct);
  int send = 4;
  int from = 0;
  int to = 1;

  n->excess[from] = send;
  n->capacity[RCI(from,to,node_ct)] = send + 1;
  n->flow[RCI(from,to,node_ct)] = 0;
  push(n->capacity, n->flow, n->excess, node_ct, from, to);
  cut_assert_equal_int(0, n->excess[from]);
  cut_assert_equal_int(send, n->excess[to]);
  cut_assert_equal_int(send, n->flow[RCI(from,to,node_ct)]);
  cut_assert_equal_int(-send, n->flow[RCI(to,from,node_ct)]);
  network_free(n);
}

void test_push_capacity(void)
{
  int node_ct = 2;
  Network *n = network_new(node_ct);
  int send = 4;
  int cap = 2;
  int from = 0;
  int to = 1;

  n->excess[from] = send;
  n->capacity[RCI(from,to,node_ct)] = cap;
  n->flow[RCI(from,to,node_ct)] = 0;
  push(n->capacity, n->flow, n->excess, node_ct, from, to);
  cut_assert_equal_int(send - cap, n->excess[from]);
  cut_assert_equal_int(cap, n->excess[to]);
  cut_assert_equal_int(cap, n->flow[RCI(from,to,node_ct)]);
  cut_assert_equal_int(-cap, n->flow[RCI(to,from,node_ct)]);
  network_free(n);
}

void test_push_residual(void)
{
  int node_ct = 2;
  Network *n = network_new(node_ct);
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
  cut_assert_equal_int(send - residual, n->excess[from]);
  cut_assert_equal_int(residual, n->excess[to]);
  cut_assert_equal_int(cap, n->flow[RCI(from,to,node_ct)]);
  cut_assert_equal_int(-residual, n->flow[RCI(to,from,node_ct)]);
  network_free(n);
}

void test_relabel_max(void)
{
  int node_ct = 4;
  Network *n = network_new(node_ct);
  int from = 0;
  int label = 3;
  n->labels[from] = label;

  relabel(n->capacity, n->flow, n->labels, node_ct, from);
  cut_assert_equal_int(n->labels[from], label);

  network_free(n);
}

void test_relabel_least(void)
{
  int node_ct = 4;
  Network *n = network_new(node_ct);
  int from = 0;
  int to = 1;
  for(int l = 0; l < node_ct; ++l)
    n->labels[l] = l;
  for(int v = to; v < node_ct; ++v)
    n->capacity[RCI(from, v, node_ct)] = 1;

  relabel(n->capacity, n->flow, n->labels, node_ct, from);
  cut_assert_equal_int(n->labels[from], n->labels[to] + 1);

  network_free(n);
}

void test_relabel_residual(void)
{
  int node_ct = 4;
  Network *n = network_new(node_ct);
  int from = 0;
  int to = 2;
  for(int l = 0; l < node_ct; ++l)
    n->labels[l] = l;
  for(int v = to; v < node_ct; ++v)
    n->capacity[RCI(from, v, node_ct)] = 1;

  relabel(n->capacity, n->flow, n->labels, node_ct, from);
  cut_assert_equal_int(n->labels[from], n->labels[to] + 1);

  network_free(n);
}

void setup_discharge_capacities(Network *n, int node_ct, int from, int cap)
{
  for (int v = from + 1; v < node_ct; ++v)
  {
    n->capacity[RCI(from,v,node_ct)] = cap;
  }
}

void test_discharge_no_excess(void)
{
  int node_ct = 4;
  int from = 0;
  int cap = 2;
  int from_label = 1;
  Network *n = network_new(node_ct);
  setup_discharge_capacities(n, node_ct, from, cap);
  n->labels[from] = from_label;
  copy_int_array(n->node_scratch, n->labels, node_ct);
  copy_int_array(n->edge_scratch, n->flow, ECT(node_ct));

  discharge(n->capacity, n->flow, n->excess, n->labels, n->seen, node_ct, from);

  assert_equal_int_array(n->node_scratch, n->labels, node_ct);
  clear_int_array(n->node_scratch, node_ct);
  assert_equal_int_array(n->node_scratch, n->excess, node_ct);
  assert_equal_int_array(n->edge_scratch, n->flow, node_ct);

  network_free(n);
}

void test_discharge_saturates(void)
{
  int node_ct = 4;
  int from = 0;
  int cap = 2;
  int from_excess = (node_ct - 1) * cap;
  int from_label = 1;
  Network *n = network_new(node_ct);
  setup_discharge_capacities(n, node_ct, from, cap);
  n->excess[from] = from_excess;
  n->labels[from] = from_label;
  copy_int_array(n->node_scratch, n->labels, node_ct);

  discharge(n->capacity, n->flow, n->excess, n->labels, n->seen, node_ct, from);

  assert_equal_int_array(n->node_scratch, n->labels, node_ct);

  set_int_array(n->node_scratch, cap, node_ct);
  n->node_scratch[from] = 0;
  assert_equal_int_array(n->node_scratch, n->excess, node_ct);

  assert_equal_int_array(n->capacity, n->flow, node_ct);

  network_free(n);
}

void test_discharge_relabels(void)
{
  int node_ct = 2;
  int cap = 4;
  int from = 0;
  int to = 1;
  int from_excess = 4;
  int to_label = 1;
  Network *n = network_new(node_ct);
  setup_discharge_capacities(n, node_ct, from, cap);
  n->excess[from] = from_excess;
  n->labels[to] = to_label;

  discharge(n->capacity, n->flow, n->excess, n->labels, n->seen, node_ct, from);

  set_int_array(n->node_scratch, 1, node_ct);
  n->node_scratch[from] = 0;
  n->node_scratch[to] = from_excess;
  assert_equal_int_array(n->node_scratch, n->excess, node_ct);

  clear_int_array(n->node_scratch, node_ct);
  n->node_scratch[to] = to_label;
  n->node_scratch[from] = to_label + 1;
  assert_equal_int_array(n->node_scratch, n->labels, node_ct);

  network_free(n);
}

void test_discharge_existing_flow(void)
{
  int node_ct = 4;
  int from = 1;
  Network *n = network_new(node_ct);
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

  assert_equal_int_array(n->node_scratch, n->labels, node_ct);

  n->edge_scratch[RCI(0,from,node_ct)] = 3;
  n->edge_scratch[RCI(from,0,node_ct)] = -3;
  n->edge_scratch[RCI(from,3,node_ct)] = 2;
  n->edge_scratch[RCI(3,from,node_ct)] = -2;
  n->edge_scratch[RCI(from,2,node_ct)] = 2;
  n->edge_scratch[RCI(2,from,node_ct)] = -2;
  assert_equal_int_array(n->edge_scratch, n->flow, node_ct);

  clear_int_array(n->node_scratch, node_ct);
  n->node_scratch[2] = 2;
  n->node_scratch[3] = 2;
  assert_equal_int_array(n->node_scratch, n->excess, node_ct);

  network_free(n);
}

void test_discharge_excess_backflow(void)
{
  int node_ct = 4;
  int from = 1;
  Network *n = network_new(node_ct);
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
  assert_equal_int_array(n->node_scratch, n->labels, node_ct);

  n->edge_scratch[RCI(0,from,node_ct)] = 2;
  n->edge_scratch[RCI(from,0,node_ct)] = -2;
  n->edge_scratch[RCI(from,3,node_ct)] = 1;
  n->edge_scratch[RCI(3,from,node_ct)] = -1;
  n->edge_scratch[RCI(from,2,node_ct)] = 1;
  n->edge_scratch[RCI(2,from,node_ct)] = -1;
  assert_equal_int_array(n->edge_scratch, n->flow, node_ct);

  clear_int_array(n->node_scratch, node_ct);
  n->node_scratch[0] = 2;
  n->node_scratch[2] = 1;
  n->node_scratch[3] = 1;
  assert_equal_int_array(n->node_scratch, n->excess, node_ct);

  network_free(n);
}

void test_saturate_from_source(void)
{
  int node_ct = 4;
  int from = 0;
  int cap_1 = 3;
  int cap_2 = 7;
  int cap_3 = 5;
  Network *n = network_new(node_ct);
  n->capacity[RCI(from, 1, node_ct)] = cap_1;
  n->capacity[RCI(from, 2, node_ct)] = cap_2;
  n->capacity[RCI(from, 3, node_ct)] = cap_3;

  saturate_from_source(n->capacity, n->flow, n->excess, node_ct, from);

  cut_assert_equal_int(0, n->excess[from]);
  cut_assert_equal_int(cap_1, n->excess[1]);
  cut_assert_equal_int(cap_2, n->excess[2]);
  cut_assert_equal_int(cap_3, n->excess[3]);

  cut_assert_equal_int(cap_1, n->flow[RCI(from, 1, node_ct)]);
  cut_assert_equal_int(cap_2, n->flow[RCI(from, 2, node_ct)]);
  cut_assert_equal_int(cap_3, n->flow[RCI(from, 3, node_ct)]);
  cut_assert_equal_int(-cap_1, n->flow[RCI(1, from, node_ct)]);
  cut_assert_equal_int(-cap_2, n->flow[RCI(2, from, node_ct)]);
  cut_assert_equal_int(-cap_3, n->flow[RCI(3, from, node_ct)]);
}

void test_saturate_max_from_source(void)
{
  int node_ct = 4;
  int from = 0;
  int cap_1 = 3;
  int cap_2 = INT_MAX;
  int cap_3 = 5;
  Network *n = network_new(node_ct);
  n->capacity[RCI(from, 1, node_ct)] = cap_1;
  n->capacity[RCI(from, 2, node_ct)] = cap_2;
  n->capacity[RCI(from, 3, node_ct)] = cap_3;

  saturate_from_source(n->capacity, n->flow, n->excess, node_ct, from);

  int cap_2_expected = cap_2 - cap_1;
  cut_assert_equal_int(0, n->excess[from]);
  cut_assert_equal_int(cap_1, n->excess[1]);
  cut_assert_equal_int(cap_2_expected, n->excess[2]);
  cut_assert_equal_int(0, n->excess[3]);

  cut_assert_equal_int(cap_1, n->flow[RCI(from, 1, node_ct)]);
  cut_assert_equal_int(cap_2_expected, n->flow[RCI(from, 2, node_ct)]);
  cut_assert_equal_int(0, n->flow[RCI(from, 3, node_ct)]);
  cut_assert_equal_int(-cap_1, n->flow[RCI(1, from, node_ct)]);
  cut_assert_equal_int(-cap_2_expected, n->flow[RCI(2, from, node_ct)]);
  cut_assert_equal_int(0, n->flow[RCI(3, from, node_ct)]);
}
