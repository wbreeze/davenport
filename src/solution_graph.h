#ifndef SOLUTION_GRAPH_H
#define SOLUTION_GRAPH_H

/*
 Add an edge (u,v) to the solution graph and maintain transitive closure.
 This works provided the solution graph is already transitive.
 By always calling this method to add edges, we ensure that is the case.
 We don't do any work if the edge is already in the graph.
*/
void solution_graph_add_edge(unsigned char *solution, int node_ct,
  int u, int v);

#endif
