#include <cutter.h>
#include "test_helper.h"
#include "test_preflow_push.h"
#include "../src/network.h"
#include "../src/preflow_push.h"

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

  preflow_push_free(p);
  network_scratch_space_free(n);
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

  preflow_push_free(p);
  network_scratch_space_free(n);
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

  preflow_push_free(p);
  network_scratch_space_free(n);
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

  preflow_push_free(p);
  network_scratch_space_free(n);
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

  preflow_push_free(p);
  network_scratch_space_free(n);
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

  preflow_push_free(p);
  network_scratch_space_free(n);
}
