/*
 Variation of the C source given in
 https://en.wikipedia.org/wiki/Push%E2%80%93relabel_maximum_flow_algorithm
 that computes maximum flow using highest label push-relabel algorithm.

 Major differences are
 - the source is always the first node
 - the sink is always the last node
 - the capacity and flow edge matrices are stored as arrays
*/

#include <assert.h>
#include <limits.h>
#include "network.h"

int residual(const int *capacity, const int *flow, int u, int v, int node_ct)
{
  return capacity[RCI(u,v,node_ct)] - flow[RCI(u,v,node_ct)];
}

/*
 Push excess flow from node u to node v.
 The amount of push is the minimum of the excess at u and the residual flow
 from u to v.
 Updates the flow and excess as a side effect.
*/
void push(const int *capacity, int *flow, int *excess, int node_ct,
  int u, int v)
{
  int send = MIN(excess[u], residual(capacity, flow, u, v, node_ct));
  flow[RCI(u,v,node_ct)] += send;
  flow[RCI(v,u,node_ct)] -= send;
  excess[u] -= send;
  excess[v] += send;
}

/*
 Relabel the "from" node.
 The "from" node is the node from which we're currently pushing flow.
 The relabel operation diverts attention to pushing flow from
   other, higher labeled nodes.
 After this operation, the label for the "from" node will be either
   - the INT_MAX label if there is no outgoing flow capacity at the
     "from" node.
   - the minimum of the labels of neighboring nodes to which flow can go,
     plus one
*/
void relabel(const int * capacity, const int * flow, int *label,
  int node_ct, int from)
{
  int v;
  int min_label = INT_MAX - 1;
  for (v = 0; v < node_ct; v++) {
    if (residual(capacity, flow, from, v, node_ct) > 0) {
      min_label = MIN(min_label, label[v]);
    }
  }
  label[from] = min_label + 1;
}
