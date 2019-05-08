#ifndef TARJAN_H
#define TARJAN_H

typedef int (*TarjanEdgeLookup)(
  void *context, int r, int c, int node_ct);
typedef void (*TarjanComponentCallback)(
  void *context, int *component, int member_ct);

typedef struct {
  int node_ct;
  int next_index;
  int next_id;
  int *index;
  int *lowlink;
  int depth;
  int *stack;
  unsigned char *onstack;
  TarjanEdgeLookup edge_lookup;
  void *edge_context;
  TarjanComponentCallback component_callback;
  void *component_callback_context;
} Tarjan;

/*
 Create Tarjan reusable data structure for node_ct components.
 The edge_lookup function accepts the context and returns true if
 there is a directed edge in the edge_context from r to c.
*/
Tarjan *tarjan_create(
  TarjanEdgeLookup edge_lookup,
  void *edge_context,
  int node_ct);

/*
 Return Tarjan data structure and its resources to the heap.
 Always returns NULL
*/
Tarjan *tarjan_destroy(Tarjan *tarjan);

/*
 Record a callback that the algorithm calls on each component when identified.
 The callback receives the context, an array of integer offsets that identify
 graph vertices that belong to the component, and the count of vertices in the
 component.
*/
void tarjan_set_component_callback(Tarjan *tarjan,
  TarjanComponentCallback component_callback, void *context);

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
