#include <cutter.h>
#include <limits.h>
#include "test_helper.h"
#include "test_preflow_push.h"
#include "../src/network.h"
#include "../src/preflow_push.h"

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
