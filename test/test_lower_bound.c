#include <cutter.h>
#include "test_helper.h"
#include "../src/network.h"
#include "test_lower_bound.h"

void populate_connected_component(int *majority, int node_ct, int offset)
{
  majority[RCI(offset + 0, offset + 1, node_ct)] = 3;
  majority[RCI(offset + 0, offset + 2, node_ct)] = 2;
  majority[RCI(offset + 1, offset + 3, node_ct)] = 2;
  majority[RCI(offset + 1, offset + 4, node_ct)] = 3;
  majority[RCI(offset + 2, offset + 4, node_ct)] = 2;
  majority[RCI(offset + 3, offset + 0, node_ct)] = 2;
  majority[RCI(offset + 4, offset + 0, node_ct)] = 3;
}

void draw_majority(int *majority, int node_ct, int from, int weight)
{
  for (int to = from + 1; to < node_ct; ++to) {
    majority[RCI(from, to, node_ct)] = weight;
  }
}

void test_lower_bound_indexing(void)
{
  int ct = 5; // count of components
  int lci = ct - 1; // last component index
  int mdim = ct * 2 + 2; // count of nodes
  LBNetwork *lb_net = lb_network_new(ct);

  cut_assert_equal_int(0, s_index(lb_net));

  cut_assert_equal_int(1, c1_index(lb_net, 0));
  cut_assert_equal_int(ct, c1_index(lb_net, lci));

  cut_assert_equal_int(ct + 1, c2_index(lb_net, 0));
  cut_assert_equal_int(ct * 2, c2_index(lb_net, lci));

  cut_assert_equal_int(ct * 2 + 1, t_index(lb_net));

  cut_assert_equal_int(1, s_edge_index(lb_net, 0));
  cut_assert_equal_int(ct, s_edge_index(lb_net, lci));

  cut_assert_equal_int(mdim + ct + 1, col_edge_index(lb_net, 0, 0));
  cut_assert_equal_int(mdim + ct + 2, col_edge_index(lb_net, 0, 1));
  cut_assert_equal_int(mdim + ct + 1 + lci, col_edge_index(lb_net, 0, lci));

  cut_assert_equal_int(mdim * 2 + 1 + ct, col_edge_index(lb_net, 1, 0));
  cut_assert_equal_int(mdim * 2 + 1 + ct + lci, col_edge_index(lb_net, 1, lci));

  cut_assert_equal_int(mdim * ct + 1 + ct, col_edge_index(lb_net, lci, 0));
  cut_assert_equal_int(mdim * ct + 1 + ct + lci,
    col_edge_index(lb_net, lci, lci));

  cut_assert_equal_int(mdim * (ct + 1 + 1) - 1, t_edge_index(lb_net, 0));
  cut_assert_equal_int(mdim * (ct + 2 + 1) - 1, t_edge_index(lb_net, 1));
  cut_assert_equal_int(mdim * (ct + ct + 1) - 1, t_edge_index(lb_net, lci));

  lb_net = lb_network_destroy(lb_net);
}

void test_lb_network_init_capacities(void)
{
  const int node_ct = 8;
  const int component_ct = 5;
  int offset = 2;
  int *majority = edge_array_calloc(node_ct);
  populate_connected_component(majority, node_ct, offset);
  const int component[component_ct] = {
    offset, offset + 1, offset + 2, offset + 3, offset + 4
  };
  LBNetwork *lb_net = lb_network_new(component_ct);

  lb_network_init_capacities(lb_net, majority, node_ct, component);

  int *flow_caps = lb_net->capacities;
  cut_assert_equal_int(majority[RCI(offset, offset + 1, node_ct)],
    flow_caps[col_edge_index(lb_net, 0, 1)]);
  cut_assert_equal_int(majority[RCI(offset, offset + 2, node_ct)],
    flow_caps[col_edge_index(lb_net, 0, 2)]);
  cut_assert_equal_int(majority[RCI(offset + 1, offset + 3, node_ct)],
    flow_caps[col_edge_index(lb_net, 1, 3)]);
  cut_assert_equal_int(majority[RCI(offset + 1, offset + 4, node_ct)],
    flow_caps[col_edge_index(lb_net, 1, 4)]);
  cut_assert_equal_int(majority[RCI(offset + 2, offset + 4, node_ct)],
    flow_caps[col_edge_index(lb_net, 2, 4)]);
  cut_assert_equal_int(majority[RCI(offset + 3, offset, node_ct)],
    flow_caps[col_edge_index(lb_net, 3, 0)]);
  cut_assert_equal_int(majority[RCI(offset + 4, offset, node_ct)],
    flow_caps[col_edge_index(lb_net, 4, 0)]);
}

void test_lb_network_init_for_pass(void)
{
  const int node_ct = 5;
  const int component_ct = 5;
  int *majority = edge_array_calloc(node_ct);
  populate_connected_component(majority, node_ct, 0);
  const int component[component_ct] = {0, 1, 2, 3, 4};
  LBNetwork *lb_net = lb_network_new(component_ct);
  int u = 0;

  lb_network_init_capacities(lb_net, majority, node_ct, component);
  // initialize a fake flow, including something on u-u that shouldn't be there
  majority[RCI(u, u, node_ct)] = node_ct;
  for (int v = 0; v < component_ct; ++v) {
    lb_net->flows[col_edge_index(lb_net, u, v)] = majority[RCI(u, v, node_ct)];
    lb_net->flows[col_edge_index(lb_net, v, u)] = majority[RCI(v, u, node_ct)];
  }
  // spoil s-u and u-t from "prior" run
  lb_net->capacities[s_edge_index(lb_net, u)] = node_ct;
  lb_net->capacities[t_edge_index(lb_net, u)] = node_ct;

  lb_network_init_for_pass(lb_net, u);

  cut_assert_equal_int(0, lb_net->capacities[s_edge_index(lb_net, u)]);
  cut_assert_equal_int(0, lb_net->capacities[t_edge_index(lb_net, u)]);
  cut_assert_equal_int(0, lb_net->flows[s_edge_index(lb_net, u)]);
  cut_assert_equal_int(0, lb_net->flows[t_edge_index(lb_net, u)]);
  for (int v = 0; v < component_ct; ++v) {
    if (u != v) {
      cut_assert_equal_int(majority[RCI(u, v, node_ct)],
        lb_net->capacities[s_edge_index(lb_net, v)]);
      cut_assert_equal_int(majority[RCI(u, v, node_ct)],
        lb_net->flows[s_edge_index(lb_net, v)]);
      cut_assert_equal_int(majority[RCI(v, u, node_ct)],
        lb_net->capacities[t_edge_index(lb_net, v)]);
      cut_assert_equal_int(majority[RCI(v, u, node_ct)],
        lb_net->flows[t_edge_index(lb_net, v)]);
    }
  }
}

void test_lb_network_update_from_pass(void)
{
  const int component_ct = 5;
  const int component[component_ct] = {0, 1, 2, 3, 4};
  LBNetwork *lb_net = lb_network_new(component_ct);
  int u = 0;

  // initialize a fake flow; anything non-zero will do
  for (int v = 0; v < component_ct; ++v) {
    lb_net->flows[s_edge_index(lb_net, v)] = v + 1;
    lb_net->flows[t_edge_index(lb_net, v)] = 2 * (v + 1);
  }

  lb_network_update_from_pass(lb_net, u);

  for (int v = 0; v < component_ct; ++v) {
    if (u != v) {
      cut_assert_equal_int(lb_net->flows[s_edge_index(lb_net, v)],
        lb_net->flows[col_edge_index(lb_net, u, v)]);
      cut_assert_equal_int(lb_net->flows[t_edge_index(lb_net, v)],
        lb_net->flows[col_edge_index(lb_net, v, u)]);
    } else {
      cut_assert_equal_int(0, lb_net->flows[col_edge_index(lb_net, u, v)]);
    }
  }
}

// test with a connected component
void test_lower_bound_majority_1(void)
{
  const int node_ct = 5;
  const int component_ct = 5;
  int *majority = edge_array_calloc(node_ct);
  populate_connected_component(majority, node_ct, 0);
  const int component[component_ct] = {0, 1, 2, 3, 4};

  int lower_bound = compute_lower_bound(majority, node_ct,
    component, component_ct);

  cut_assert_equal_int(5, lower_bound);
}

// test with a connected component embedded within a larger graph
void test_lower_bound_majority_2(void)
{
  const int node_ct = 8;
  const int component_ct = 5;
  int offset = 2;
  int *majority = edge_array_calloc(node_ct);
  populate_connected_component(majority, node_ct, offset);
  const int component[component_ct] = {
    offset, offset + 1, offset + 2, offset + 3, offset + 4
  };
  draw_majority(majority, node_ct, 0, 1);
  draw_majority(majority, node_ct, 1, 1);
  for (int from = 0; from < (node_ct - 1); ++from) {
    majority[RCI(from, node_ct - 1, node_ct)] = 3;
  }

  int lower_bound = compute_lower_bound(majority, node_ct,
    component, component_ct);

  cut_assert_equal_int(5, lower_bound);
}
