#include <cutter.h>
#include "test_helper.h"
#include "test_preflow_push.h"
#include "../src/network.h"
#include "../src/preflow_push.h"

void test_preflow_remove_back_flows(void)
{
  int node_ct = 4;
  int existing_flow = 2;
  int *flow = edge_array_calloc(node_ct);
  int *expected = edge_array_calloc(node_ct);
  for(int i = 1; i < node_ct; ++i) {
    flow[RCI(i-1, i, node_ct)] = existing_flow;
    expected[RCI(i-1, i, node_ct)] = existing_flow;
    flow[RCI(i, i-1, node_ct)] = -existing_flow;
  }

  remove_back_flows(flow, node_ct);

  assert_equal_int_array(expected, flow, ECT(node_ct));

  free(flow);
  free(expected);
}

void test_preflow_push_reduced_1(void)
{
  int node_ct = 4;
  int flow;
  NetworkScratchSpace *n = network_scratch_space_new(node_ct);
  n->capacity[RCI(0,1,node_ct)] = 4;
  n->capacity[RCI(1,2,node_ct)] = 3;
  n->capacity[RCI(2,3,node_ct)] = 2;
  for (int i = 1; i < node_ct; ++i)
    n->edge_scratch[RCI(i-1,i,node_ct)] = 2;

  PreflowPush *p = preflow_push_new(n->capacity, node_ct);
  flow = max_flow_reduced_caps(p, n->flow, n->labels, 0, 3);
  cut_assert_equal_int(2, flow);
  assert_equal_int_array(n->edge_scratch, n->flow, node_ct);

  flow = max_flow_reduced_caps(p, n->flow, n->labels, 0, 3);
  cut_assert_equal_int(0, flow);
  assert_equal_int_array(n->edge_scratch, n->flow, node_ct);

  preflow_push_free(p);
  network_scratch_space_free(n);
}

void test_preflow_push_reduced_2(void)
{
  int node_ct = 4;
  int flow;
  NetworkScratchSpace *n = network_scratch_space_new(node_ct);
  n->capacity[RCI(0,1,node_ct)] = 8;
  n->capacity[RCI(1,2,node_ct)] = 6;
  n->capacity[RCI(2,3,node_ct)] = 4;
  for (int i = 1; i < node_ct; ++i)
  {
    n->flow[RCI(i-1,i,node_ct)] = 2;
    n->edge_scratch[RCI(i-1,i,node_ct)] = 4;
  }

  PreflowPush *p = preflow_push_new(n->capacity, node_ct);
  flow = max_flow_reduced_caps(p, n->flow, n->labels, 0, 3);
  cut_assert_equal_int(2, flow);
  assert_equal_int_array(n->edge_scratch, n->flow, node_ct);

  preflow_push_free(p);
  network_scratch_space_free(n);
}

void test_preflow_push_reduced_3(void)
{
  int node_ct = 10;
  NetworkScratchSpace *n = network_scratch_space_new(node_ct);
  for (int i = 0; i < 3; ++i)
  {
    n->capacity[RCI(0,i+1,node_ct)] = 6;
    n->flow[RCI(0,i+1,node_ct)] = 3;
    for (int j = 0; j < 3; ++j)
    {
      n->capacity[RCI(i,i+3,node_ct)] = 2;
      n->flow[RCI(i,i+3,node_ct)] = 1;
    }
  }
  n->capacity[RCI(4,7,node_ct)] = 4;
  n->flow[RCI(4,7,node_ct)] = 4;
  n->capacity[RCI(5,4,node_ct)] = 1;
  n->flow[RCI(5,4,node_ct)] = 1;
  n->capacity[RCI(5,8,node_ct)] = 2;
  n->flow[RCI(5,8,node_ct)] = 1;
  n->capacity[RCI(5,6,node_ct)] = 1;
  n->flow[RCI(5,6,node_ct)] = 1;
  n->capacity[RCI(6,8,node_ct)] = 6;
  n->flow[RCI(6,8,node_ct)] = 4;
  n->capacity[RCI(7,9,node_ct)] = 6;
  n->flow[RCI(7,9,node_ct)] = 4;
  n->capacity[RCI(8,9,node_ct)] = 8;
  n->flow[RCI(8,9,node_ct)] = 5;

  PreflowPush *p = preflow_push_new(n->capacity, node_ct);
  int flow = max_flow_reduced_caps(p, n->flow, n->labels, 0, 3);
  cut_assert_equal_int(3, flow);

  preflow_push_free(p);
  network_scratch_space_free(n);
}
