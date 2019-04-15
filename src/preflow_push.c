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

/*
 Compute residual flow on an edge. The residual is the capacity minus
   the existing flow.
 If the existing flow is negative, this still returns positive, because
   the flow of any edge never exceeds the capacity.
*/
int residual(const int *capacity, const int *flow, int node_ct,
  int u, int v)
{
  int index = RCI(u,v,node_ct);
  return capacity[index] - flow[index];
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
  int send = MIN(excess[u], residual(capacity, flow, node_ct, u, v));
  flow[RCI(u,v,node_ct)] += send;
  flow[RCI(v,u,node_ct)] -= send;
  excess[u] -= send;
  excess[v] += send;
}

/*
 Relabel the "from" node, u.
 The "from" node is the node from which we're currently pushing flow.
 The relabel operation enables excess at the "from" node to flow across
   an edge that has residual capacity to another, currently higher labeled node.
 After this operation, the label for the "from" node will be either
   - unchanged if there is no outgoing flow capacity at the "from" node.
   - the minimum of the labels of neighboring nodes to which flow can go,
     plus one
 Note: relabel is not called if there is no excess at the "from" node.
*/
void relabel(const int * capacity, const int * flow, int *labels,
  int node_ct, int u)
{
  int v;
  int min_label = INT_MAX - 1;
  for (v = 0; v < node_ct; v++) {
    if (0 < residual(capacity, flow, node_ct, u, v)) {
      min_label = MIN(min_label, labels[v]);
      labels[u] = min_label + 1;
    }
  }
}

/*
 Discharge excess capacity at the "from" node, u
 Pushes flow where there is residual and lower labeled nodes
 Relabels to push any remaining excess "back" if needed.
*/
void discharge(const int * capacity, int * flow, int *excess,
  int *labels, int *seen, int node_ct, int u)
{
  while(0 < excess[u]) {
    if (seen[u] < node_ct) {
      int v = seen[u];
      if (labels[u] > labels[v] &&
          0 < residual(capacity, flow, node_ct, u, v))
      {
        push(capacity, flow, excess, node_ct, u, v);
      } else {
        seen[u] += 1;
      }
    } else {
      relabel(capacity, flow, labels, node_ct, u);
      seen[u] = 0;
    }
  }
}
