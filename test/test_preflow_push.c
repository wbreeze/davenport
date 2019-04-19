#include <assert.h>
#include <cutter.h>
#include <limits.h>
#include <stdlib.h>
#include "test_helper.h"
#include "test_preflow_push.h"
#include "../src/network.h"
#include "../src/preflow_push.h"

void test_push_excess(void)
{
  int node_ct = 2;
  NetworkScratchSpace *n = network_scratch_space_new(node_ct);
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
  network_scratch_space_free(n);
}

void test_push_capacity(void)
{
  int node_ct = 2;
  NetworkScratchSpace *n = network_scratch_space_new(node_ct);
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
  network_scratch_space_free(n);
}

void test_push_residual(void)
{
  int node_ct = 2;
  NetworkScratchSpace *n = network_scratch_space_new(node_ct);
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
  network_scratch_space_free(n);
}

void test_relabel_max(void)
{
  int node_ct = 4;
  NetworkScratchSpace *n = network_scratch_space_new(node_ct);
  int from = 0;
  int label = 3;
  n->labels[from] = label;

  relabel(n->capacity, n->flow, n->labels, node_ct, from);
  cut_assert_equal_int(n->labels[from], label);

  network_scratch_space_free(n);
}

void test_relabel_least(void)
{
  int node_ct = 4;
  NetworkScratchSpace *n = network_scratch_space_new(node_ct);
  int from = 0;
  int to = 1;
  for(int l = 0; l < node_ct; ++l)
    n->labels[l] = l;
  for(int v = to; v < node_ct; ++v)
    n->capacity[RCI(from, v, node_ct)] = 1;

  relabel(n->capacity, n->flow, n->labels, node_ct, from);
  cut_assert_equal_int(n->labels[from], n->labels[to] + 1);

  network_scratch_space_free(n);
}

void test_relabel_residual(void)
{
  int node_ct = 4;
  NetworkScratchSpace *n = network_scratch_space_new(node_ct);
  int from = 0;
  int to = 2;
  for(int l = 0; l < node_ct; ++l)
    n->labels[l] = l;
  for(int v = to; v < node_ct; ++v)
    n->capacity[RCI(from, v, node_ct)] = 1;

  relabel(n->capacity, n->flow, n->labels, node_ct, from);
  cut_assert_equal_int(n->labels[from], n->labels[to] + 1);

  network_scratch_space_free(n);
}

void setup_discharge_capacities(NetworkScratchSpace *n, int node_ct, int from, int cap)
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
  NetworkScratchSpace *n = network_scratch_space_new(node_ct);
  setup_discharge_capacities(n, node_ct, from, cap);
  n->labels[from] = from_label;
  copy_int_array(n->node_scratch, n->labels, node_ct);
  copy_int_array(n->edge_scratch, n->flow, ECT(node_ct));

  discharge(n->capacity, n->flow, n->excess, n->labels, n->seen, node_ct, from);

  assert_equal_int_array(n->node_scratch, n->labels, node_ct);
  clear_int_array(n->node_scratch, node_ct);
  assert_equal_int_array(n->node_scratch, n->excess, node_ct);
  assert_equal_int_array(n->edge_scratch, n->flow, node_ct);

  network_scratch_space_free(n);
}

void test_discharge_saturates(void)
{
  int node_ct = 4;
  int from = 0;
  int cap = 2;
  int from_excess = (node_ct - 1) * cap;
  int from_label = 1;
  NetworkScratchSpace *n = network_scratch_space_new(node_ct);
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

  network_scratch_space_free(n);
}

void test_discharge_relabels(void)
{
  int node_ct = 2;
  int cap = 4;
  int from = 0;
  int to = 1;
  int from_excess = 4;
  int to_label = 1;
  NetworkScratchSpace *n = network_scratch_space_new(node_ct);
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

  network_scratch_space_free(n);
}

void test_discharge_existing_flow(void)
{
  int node_ct = 4;
  int from = 1;
  NetworkScratchSpace *n = network_scratch_space_new(node_ct);
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

  network_scratch_space_free(n);
}

void test_discharge_excess_backflow(void)
{
  int node_ct = 4;
  int from = 1;
  NetworkScratchSpace *n = network_scratch_space_new(node_ct);
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

  network_scratch_space_free(n);
}

void test_saturate_from_source(void)
{
  int node_ct = 4;
  int from = 0;
  int cap_1 = 3;
  int cap_2 = 7;
  int cap_3 = 5;
  NetworkScratchSpace *n = network_scratch_space_new(node_ct);
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
  NetworkScratchSpace *n = network_scratch_space_new(node_ct);
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

void test_initialize_list_ends(void)
{
  int node_ct = 8;
  int source = 0;
  int sink = 7;
  int *list = node_array_calloc(node_ct);
  initialize_list(list, node_ct, source, sink);
  cut_assert_equal_int(1, list[0]);
  cut_assert_equal_int(6, list[5]);
  for (int i = 0; i < node_ct - 2; ++i)
  {
    cut_assert_not_equal_int(source, list[i]);
    cut_assert_not_equal_int(sink, list[i]);
  }
  free(list);
}

void test_initialize_list_middle(void)
{
  int node_ct = 8;
  int source = 3;
  int sink = 4;
  int *list = node_array_calloc(node_ct);
  initialize_list(list, node_ct, source, sink);
  cut_assert_equal_int(0, list[0]);
  cut_assert_equal_int(7, list[5]);
  for (int i = 0; i < node_ct - 2; ++i)
  {
    cut_assert_not_equal_int(source, list[i]);
    cut_assert_not_equal_int(sink, list[i]);
  }
  free(list);
}

void test_move_to_front_noop(void)
{
  int node_ct = 5;
  int list[] = {1,2,3,4,5};
  int expected[] = {1,2,3,4,5};
  moveToFront(list, 0);
  assert_equal_int_array(expected, list, node_ct);
}

void test_move_to_front_middle(void)
{
  int node_ct = 5;
  int list[] = {1,2,3,4,5};
  int expected[] = {3,1,2,4,5};
  moveToFront(list, 2);
  assert_equal_int_array(expected, list, node_ct);
}

void test_move_to_front_last(void)
{
  int node_ct = 5;
  int list[] = {1,2,3,4,5};
  int expected[] = {5,1,2,3,4};
  moveToFront(list, 4);
  assert_equal_int_array(expected, list, node_ct);
}

void test_preflow_push_new(void)
{
  PreflowPush *p;

  p = preflow_push_new(NULL, 2);
  cut_assert(p != NULL);
  p = preflow_push_free(p);
  cut_assert(p == NULL);
}

void test_preflow_push_network_1(void)
{
  int node_ct = 4;
  NetworkScratchSpace *n = network_scratch_space_new(node_ct);
  n->capacity[RCI(0,1,node_ct)] = 4;
  n->capacity[RCI(1,2,node_ct)] = 3;
  n->capacity[RCI(2,3,node_ct)] = 2;
  PreflowPush *p = preflow_push_new(n->capacity, node_ct);
  int flow = max_flow_reduced_caps(p, n->flow, n->labels, 0, 3);
  cut_assert_equal_int(2, flow);
}

void test_preflow_push_network_2(void)
{
  int node_ct = 4;
  NetworkScratchSpace *n = network_scratch_space_new(node_ct);
  n->capacity[RCI(1,0,node_ct)] = 4;
  n->capacity[RCI(0,3,node_ct)] = 3;
  n->capacity[RCI(3,2,node_ct)] = 2;
  PreflowPush *p = preflow_push_new(n->capacity, node_ct);
  int flow = max_flow_reduced_caps(p, n->flow, n->labels, 1, 2);
  cut_assert_equal_int(2, flow);
}

void test_preflow_push_network_3(void)
{
  int node_ct = 6;
  NetworkScratchSpace *n = network_scratch_space_new(node_ct);
  n->capacity[RCI(0,1,node_ct)] = 4;
  n->capacity[RCI(1,3,node_ct)] = 3;
  n->capacity[RCI(3,5,node_ct)] = 2;
  n->capacity[RCI(0,2,node_ct)] = 7;
  n->capacity[RCI(2,4,node_ct)] = 6;
  n->capacity[RCI(4,5,node_ct)] = 5;
  PreflowPush *p = preflow_push_new(n->capacity, node_ct);
  int flow = max_flow_reduced_caps(p, n->flow, n->labels, 0, 5);
  cut_assert_equal_int(7, flow);
}

void test_preflow_push_network_4(void)
{
  int node_ct = 6;
  NetworkScratchSpace *n = network_scratch_space_new(node_ct);
  n->capacity[RCI(0,1,node_ct)] = 6;
  n->capacity[RCI(1,3,node_ct)] = 5;
  n->capacity[RCI(3,5,node_ct)] = 1;
  n->capacity[RCI(3,2,node_ct)] = 4;
  n->capacity[RCI(2,4,node_ct)] = 3;
  n->capacity[RCI(4,5,node_ct)] = 2;
  PreflowPush *p = preflow_push_new(n->capacity, node_ct);
  int flow = max_flow_reduced_caps(p, n->flow, n->labels, 0, 5);
  cut_assert_equal_int(3, flow);
}

void test_preflow_push_network_5(void)
{
  int node_ct = 4;
  NetworkScratchSpace *n = network_scratch_space_new(node_ct);
  n->capacity[RCI(0,1,node_ct)] = 4;
  n->capacity[RCI(1,2,node_ct)] = 3;
  n->capacity[RCI(2,3,node_ct)] = 4;
  PreflowPush *p = preflow_push_new(n->capacity, node_ct);
  int flow = max_flow_reduced_caps(p, n->flow, n->labels, 0, 3);
  cut_assert_equal_int(3, flow);
}

void test_preflow_push_network_cycles_1(void)
{
  int node_ct = 7;
  NetworkScratchSpace *n = network_scratch_space_new(node_ct);
  n->capacity[RCI(0,1,node_ct)] = 2;
  n->capacity[RCI(0,2,node_ct)] = 3;
  n->capacity[RCI(2,1,node_ct)] = 4;
  n->capacity[RCI(1,3,node_ct)] = 6;
  n->capacity[RCI(3,2,node_ct)] = 4;
  n->capacity[RCI(3,4,node_ct)] = 8;
  n->capacity[RCI(4,5,node_ct)] = 4;
  n->capacity[RCI(5,3,node_ct)] = 4;
  n->capacity[RCI(4,6,node_ct)] = 3;
  n->capacity[RCI(5,6,node_ct)] = 2;
  PreflowPush *p = preflow_push_new(n->capacity, node_ct);
  int flow = max_flow_reduced_caps(p, n->flow, n->labels, 0, 6);
  cut_assert_equal_int(5, flow);
}

void initialize_multilayer_capacities(NetworkScratchSpace *n)
{
  assert(10 <= n->node_ct);
  for(int i = 1; i <= 3; ++i) {
    n->capacity[RCI(0,i,n->node_ct)] = 4;
    for(int j = 4; j <= 6; ++j) {
      n->capacity[RCI(i,j,n->node_ct)] = 1;
    }
  }
  n->capacity[RCI(5,4,n->node_ct)] = 1;
  n->capacity[RCI(5,6,n->node_ct)] = 1;
  n->capacity[RCI(5,8,n->node_ct)] = 1;
  n->capacity[RCI(4,7,n->node_ct)] = 4;
  n->capacity[RCI(6,8,n->node_ct)] = 6;
  n->capacity[RCI(7,9,n->node_ct)] = 6;
  n->capacity[RCI(8,9,n->node_ct)] = 8;
}

void test_preflow_push_network_multilayer(void)
{
  int node_ct = 10;
  NetworkScratchSpace *n = network_scratch_space_new(node_ct);
  initialize_multilayer_capacities(n);
  PreflowPush *p = preflow_push_new(n->capacity, node_ct);
  int flow = max_flow_reduced_caps(p, n->flow, n->labels, 0, 9);
  cut_assert_equal_int(9, flow);
}

void test_preflow_push_network_multilayer_labeled(void)
{
  int node_ct = 10;
  NetworkScratchSpace *n = network_scratch_space_new(node_ct);
  initialize_multilayer_capacities(n);
  n->labels[7] = 1;
  n->labels[8] = 1;
  n->labels[4] = 2;
  n->labels[5] = 2;
  n->labels[6] = 2;
  n->labels[1] = 3;
  n->labels[2] = 3;
  n->labels[3] = 3;
  PreflowPush *p = preflow_push_new(n->capacity, node_ct);
  int flow = max_flow_reduced_caps(p, n->flow, n->labels, 0, 9);
  cut_assert_equal_int(9, flow);
}
