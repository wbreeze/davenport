/*
 Variation of the C source given in
 https://en.wikipedia.org/wiki/Push%E2%80%93relabel_maximum_flow_algorithm
 that computes maximum flow using highest label push-relabel algorithm.

 Major differences are
 - the source is always the first node
 - the sink is always the last node
 - the capacity and flow edge matrices are stored as arrays
*/

#include "network.h"

/*
 Push excess flow from node u to node v.
 The amount of push is the minimum of the excess at u and the residual flow
 from u to v.
 Updates the flow and excess as a side effect.
*/
void push(const int * capacity, int * flow, int *excess, int node_ct,
  int u, int v)
{
  int residual = capacity[RCI(u,v,node_ct)] - flow[RCI(u,v,node_ct)];
  int send = MIN(excess[u], residual);
  flow[RCI(u,v,node_ct)] += send;
  flow[RCI(v,u,node_ct)] -= send;
  excess[u] -= send;
  excess[v] += send;
}
