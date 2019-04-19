#include <cutter.h>
#include "test_helper.h"
#include "test_preflow_push.h"
#include "../src/network.h"
#include "../src/preflow_push.h"

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
