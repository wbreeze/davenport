#ifndef LOWER_BOUND_H
#define LOWER_BOUND_H

#include "network.h"
#include "preflow_push.h"

// defined here for testing; internal use only
typedef struct {
  int node_ct;
  int net_ct;
  int *capacities;
  int *flows;
  int *labels;
  PreflowPush *pp;
} LBNetwork;

#define s_index(lb_net) (0)
#define t_index(lb_net) (lb_net->net_ct - 1)
#define c1_index(lb_net, u) ((u) + 1)
#define c2_index(lb_net, v) (lb_net->node_ct + (v) + 1)

#define s_edge_index(lb_net, u) \
  (RCI(s_index(lb_net), c1_index(lb_net, u), lb_net->net_ct))
#define col_edge_index(lb_net, u, v) \
  (RCI(c1_index(lb_net, u), c2_index(lb_net, v), lb_net->net_ct))
#define t_edge_index(lb_net, v) \
  (RCI(c2_index(lb_net, v), t_index(lb_net), lb_net->net_ct))

/*
 This is the public interface.

 Given the pair-wise majority graph as "majority" with node_ct nodes
 and a list of indexes within that graph, "component" with component_sz
 indexes (0 <= index < node_ct),
 compute the lower bound on the number of pair-wise rankings
 that must be broken in order to create a non-cyclic majority graph
*/
int compute_lower_bound(const int *majority, int node_ct,
  const int *component, int component_sz);

#endif
