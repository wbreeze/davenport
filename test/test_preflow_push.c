#include <cutter.h>
#include <limits.h>
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
