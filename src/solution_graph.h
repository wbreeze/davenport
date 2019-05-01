#ifndef SOLUTION_GRAPH_H
#define SOLUTION_GRAPH_H

typedef struct SolutionGraph {
  int node_ct;
  int disagreement_count;
  unsigned char *solution;
  int set_point;
  int *edge_stack;
} SolutionGraph;

#define solution_array_calloc(node_ct) \
  calloc(ECT(node_ct), sizeof(unsigned char))
#define clear_solution_array(array, node_ct) \
  memset(array, 0, ECT(node_ct) * sizeof(unsigned char))

#define edge_stack_calloc(node_ct) \
  calloc(DG_ECT(node_ct), sizeof(int))
#define clear_edge_stack(stack, node_ct) \
  memset(stack, 0, DG_ECT(node_ct) * sizeof(int))

SolutionGraph *solution_graph_create(int node_ct);
SolutionGraph *solution_graph_destroy(SolutionGraph *sol);

/*
 Add an edge (u,v) to the solution graph and maintain transitive closure.
 This works provided the solution graph is already transitive.
 By always calling this method to add edges, we ensure that is the case.
 We don't do any work if the edge is already in the graph.
*/
void solution_graph_add_edge(SolutionGraph *sol, int u, int v);

/*
 Returns the value of the edge at (u, v).
 Treat it as boolean. Zero value denotes no edge.
*/
unsigned char solution_graph_has_edge(SolutionGraph *sol, int u, int v);

/*
 Delegates with a call to rank_sorted_items().
 Find the description in ranking.h
*/
void solution_graph_rank_sort_items(SolutionGraph *sol,
  const int *topological_sort, int *ranking);

#endif
