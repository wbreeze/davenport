#ifndef TARJAN_H
#define TARJAN_H

// defined here for testing

typedef struct {
  int node_ct;
  int next_index;
  int next_id;
  int *index;
  int *lowlink;
  int depth;
  int *stack;
  unsigned char *onstack;
  int (*edge_lookup)(void *context, int r, int c, int node_ct);
  void *edge_context;
} Tarjan;

// public interface

/*
 Create Tarjan reusable data structure for node_ct components.
 The edge_lookup function accepts the context and returns true if
 there is a directed edge in the edge_context from r to c.
*/
Tarjan *tarjan_create(
  int (*edge_lookup)(void *context, int r, int c, int node_ct),
  void *edge_context,
  int node_ct);

/*
 Return Tarjan data structure and its resources to the heap.
 Always returns NULL
*/
Tarjan *tarjan_destroy(Tarjan *tarjan);

/*
 An edge lookup that accepts an integer array as context and returns
 the value at context[RCI(r,c,node_ct)]
*/
int tarjan_default_edge_lookup(void *context, int r, int c, int node_ct);

/*
 Apply Tarjan's algorithm to identify maximum, strongly connected components
 within the directed graph.
 
 It usese the edge_lookup function supplied in the constructor, along
 with the context data passed there, to determine the existence of each edge.

 An non-zero return from the edge_lookup function indicates an edge
 from the node at i to the node at j.

 Overwrites the values of components, which must be an integer array
 of minimum length, node_ct.

 The values in components will be integer component identifiers for the
 node at each corresponding offset. These identifiers will be in the range,
 0 < offset <= node_ct. As a bonus, listing components by decreasing
 identifier gives a topological sort of the components. Otherwise, the
 exact values are not defined.
*/
void tarjan_identify_components(Tarjan *t, int *components);

#endif
