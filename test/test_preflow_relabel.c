#include <cutter.h>
#include "test_helper.h"
#include "test_preflow_push.h"
#include "../src/network.h"
#include "../src/preflow_push.h"

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
