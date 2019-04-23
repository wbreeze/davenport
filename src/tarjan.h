#ifndef TARJAN_H
#define TARJAN_H

/*
 Apply Tarjan's algorithm to identify maximum, strongly connected components
 within the directed graph using integer valued edges and node_ct nodes.
 An non-zero entry in edges at offset, RCI(i,j,node_ct) indicates an edge
 from the node at i to the node at j.

 Overwrites the values of components, which must be an integer array
 of minimum length, node_ct.

 The values in components will be integer component identifiers for the
 node at each corresponding index. These identifiers will be in the range,
 0 < index <= node_ct. As a bonus, listing components by decreasing
 identifier gives a topological sort of the components. Otherwise, the
 exact values are not defined.
*/
void identify_components(const int *edges, int node_ct, int *components);

// defined here for testing

typedef struct {
  int node_ct;
  const int *edges;
  int *lowlink;
  int next_index;
  int *index;
  int depth;
  int *stack;
  unsigned char *onstack;
} Tarjan;

#endif
