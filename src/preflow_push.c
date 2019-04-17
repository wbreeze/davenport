/*
 Variation of the C source given in
 https://en.wikipedia.org/wiki/Push%E2%80%93relabel_maximum_flow_algorithm
 that computes maximum flow using highest label push-relabel algorithm.

 Major differences are
 - the capacity and flow edge matrices are stored as arrays
 - the algorithm will function on a subset of the network.
*/

#include <assert.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include "network.h"
#include "preflow_push.h"

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

/*
 Push initial flow from the source into the network, at maximum capacity.
*/
void saturate_from_source(const int *capacity, int *flow, int *excess,
  int node_ct, int source)
{
  excess[source] = INT_MAX;
  for(int v = 0; v < node_ct; ++v)
    push(capacity, flow, excess, node_ct, source, v);
  excess[source] = 0;
}

/*
 Initialize list of node_ct - 2 nodes that includes all nodes
 except the source and sink nodes
*/
void initialize_list(int *list, int node_ct, int source, int sink)
{
  int offset = 0;
  for(int i = 0; i < node_ct; ++i) {
    if (i != source && i != sink) {
      list[offset++] = i;
    }
  }
}

struct PreflowPush {
  int used;
  int node_ct;
  const int *capacity;
  int *excess;
  int *seen;
  int *sequence;
};

/*
 The PreflowPush structure contains the capacity network, node count,
   and buffers for internal computations.
 Use this to allocate one.
 You promise not to free the storage given by capacity before freeing the
   returned structure using preflow_push_free().
 You promise that the size of storage allocated for capacity is at minimim,
   node_ct * node_ct * sizeof(int)
 You set capacity for an edge from u to v using index, RCI(u,v,node_ct) defined
   in network.h. For example, "capacity[RCI(0,3,4)] = 6" sets capacity
   on the edge from node 0 to node 3 to value, 6 in a network of four nodes.
*/
PreflowPush *preflow_push_new(const int *capacity, int node_ct)
{
  PreflowPush *p = malloc(sizeof(PreflowPush));
  p->node_ct = node_ct;
  p->capacity = capacity;
  p->seen = node_array_calloc(node_ct);
  p->excess = node_array_calloc(node_ct);
  p->sequence = node_array_calloc(node_ct);
  p->used = 0;
  return p;
}

/*
 Free-up memory used by PreflowPush.
 After this, the address referenced by "p" is no longer valid for reference.
 For convenience, this returns NULL; so, "p = preflow_push_free(p);" will
 clear p to help prevent accidents.
*/
void *preflow_push_free(PreflowPush *p)
{
  free(p->seen);
  free(p->excess);
  free(p->sequence);
  free(p);
  return NULL;
}

/*
 Reset the scratch buffers used by the preflow push
*/
void reset(PreflowPush *p)
{
  // this is just a little optimization to prevent resetting on first use.
  if (p->used) {
    memset(p->seen, 0, p->node_ct * sizeof(int));
    memset(p->excess, 0, p->node_ct * sizeof(int));
  }
  p->used = 1;
}

/*
 Compute maximum flow over a subset of the network, given by list,
   with existing flow to simulate reduced capacities. Provide labels
   initialized with distance to the sink.
 The source and sink values are node indexes.

 TODO: future
 The list is of node indexes that comprise a subset of the network.
   No flow will be pushed through nodes not in the list.
   The list must *not* include the source and sink nodes.
 The list_ct value is the number of nodes in the list.
*/
int max_flow_reduced_caps(PreflowPush *p, int *flow, int *labels,
  int source, int sink) //, int *list, int list_ct)
{
  assert(source < p->node_ct);
  assert(sink < p->node_ct);
  reset(p);
  saturate_from_source(p->capacity, flow, p->excess, p->node_ct, source);

  return 0;
}
