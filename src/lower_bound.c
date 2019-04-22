#include <stdlib.h>
#include "lower_bound.h"
#include "network.h"
#include "preflow_push.h"

/*
 Initialize for a network that computes max_flow through three-cycles
 from a strongly connected component of component_sz nodes.

 The network has:
 - a source node, index zero
 - a sink node,  index ((2 * component_sz) + 1)
 - a first column, indices 1 to component_sz
 - a second column, indices (component_sz + 1) to (2 * component_sz)

 net_ct: number of nodes in the flow network
 node_ct: number of nodes in the component of the majority graph
 capacities: net_ct * net_ct edge values representing capacity
 flows: net_ct * net_ct edge values representing flow
 labels: net_ct labels for the preflow_push
 pp: PreflowPush data structure for use on the network
*/
LBNetwork *lb_network_new(int component_sz)
{
  int net_ct = (component_sz * 2) + 2;
  LBNetwork *lb_net = malloc(sizeof(LBNetwork));
  lb_net->node_ct = component_sz;
  lb_net->net_ct = net_ct;
  lb_net->capacities = edge_array_calloc(net_ct);
  lb_net->flows = edge_array_calloc(net_ct);
  lb_net->labels = node_array_calloc(net_ct);
  lb_net->pp = preflow_push_new(lb_net->capacities, net_ct);
  return lb_net;
}

LBNetwork *lb_network_destroy(LBNetwork *lb_net)
{
  lb_net->pp = preflow_push_free(lb_net->pp);
  free(lb_net->labels);
  free(lb_net->flows);
  free(lb_net->capacities);
  free(lb_net);
  return NULL;
}

/*
 Initialize the capacities of the internal edges of the network
*/
void lb_network_init_capacities(LBNetwork *lb_net,
  const int *majority, int node_ct, const int *component)
{
  for (int u = 0; u < lb_net->node_ct; ++u) {
    int u_ref = component[u];
    for (int v = 0; v < lb_net->node_ct; ++v) {
      int v_ref = component[v];
       lb_net->capacities[col_edge_index(lb_net, u, v)] =
         majority[RCI(u_ref, v_ref, node_ct)];
    }
  }
}

/*
 Initialize source and sink edges for flow computation
 of any three-cycles originating at node "u"
*/
void lb_network_init_for_pass(LBNetwork *lb_net, int u)
{
  lb_net->capacities[s_edge_index(lb_net, u)] = 0;
  lb_net->capacities[t_edge_index(lb_net, u)] = 0;
  for(int v = 0; v < lb_net->node_ct; ++v) {
    if (v != u) {
      lb_net->capacities[s_edge_index(lb_net, v)] =
        lb_net->capacities[col_edge_index(lb_net, u, v)];
      lb_net->flows[s_edge_index(lb_net, v)] =
        lb_net->flows[col_edge_index(lb_net, u, v)];
      lb_net->capacities[t_edge_index(lb_net, v)] =
        lb_net->capacities[col_edge_index(lb_net, v, u)];
      lb_net->flows[t_edge_index(lb_net, v)] =
        lb_net->flows[col_edge_index(lb_net, v, u)];
    }
  }
}

/*
 Update "internal" edge flows from source and sink edges
   from flow computation for any three-cycles
   originating at node "u"
*/
void lb_network_update_from_pass(LBNetwork *lb_net, int u)
{
  for (int v = 0; v < lb_net->node_ct; ++v) {
    if (v != u) {
      lb_net->flows[col_edge_index(lb_net, u, v)] =
        lb_net->flows[s_edge_index(lb_net, v)];
      lb_net->flows[col_edge_index(lb_net, v, u)] =
        lb_net->flows[t_edge_index(lb_net, v)];
    }
  }
}

int compute_lower_bound(const int *majority, int node_ct,
  const int *component, int component_sz)
{
  LBNetwork *lb_net = lb_network_new(component_sz);
  lb_network_init_capacities(lb_net, majority, node_ct, component);

  int lower_bound = 0;

  for (int u = 0; u < component_sz; ++u)
  {
    lb_network_init_for_pass(lb_net, u);
    lower_bound += max_flow_reduced_caps(lb_net->pp,
       lb_net->flows, lb_net->labels,
       s_index(lb_net), t_index(lb_net));
    lb_network_update_from_pass(lb_net, u);
  }

  lb_net = lb_network_destroy(lb_net);
  return lower_bound;
}
