#ifndef TEST_LOWER_BOUND_H
#define TEST_LOWER_BOUND_H

#include "../src/lower_bound.h"

// declare internal methods from lower_bound, for testing
LBNetwork *lb_network_new(int component_sz);
LBNetwork *lb_network_destroy(LBNetwork *lb_net);
void lb_network_init_capacities(LBNetwork *lb_net, LBNetworkEdgeLookup lookup,
  void *context, int node_ct, const int *component);
void lb_network_init_for_pass(LBNetwork *lb_net, int u);
void lb_network_update_from_pass(LBNetwork *lb_net, int u);
int lower_bound_edge_lookup(void *context, int u, int v, int node_ct);

#endif
