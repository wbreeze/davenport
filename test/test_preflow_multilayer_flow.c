#include <assert.h>
#include <cutter.h>
#include "test_helper.h"
#include "test_preflow_push.h"
#include "../src/network.h"
#include "../src/preflow_push.h"

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
