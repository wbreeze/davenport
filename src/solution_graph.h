#ifndef SOLUTION_GRAPH_H
#define SOLUTION_GRAPH_H

typedef struct SolutionGraph {
  int node_ct;
  const int *majority_graph;
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

/*
 Create a graph that tracks the current solution.
 The solution (virtually) modifies the provided majority graph when
   an edge added directly, or indirectly through transitive closure,
   is opposite to an edge in the majority graph. When that happens,
   this adds that edge's weight to the total of disagreements.
*/
SolutionGraph *solution_graph_create(const int *majority_graph, int node_ct);
SolutionGraph *solution_graph_destroy(SolutionGraph *sol);

/*
 Add an edge (u,v) to the solution graph and maintain transitive closure.
 This works provided the solution graph is already transitive.
 By always calling this method to add edges, we ensure that is the case.
 We don't do any work if the edge is already in the graph.
 Returns a set_point that can be used with "solution_graph_rollback()"
   to put the solution graph in the state it had before this call.
 Updates the total weight of disagreements in the solution relative to
   the majority graph.
*/
int solution_graph_add_edge(SolutionGraph *sol, int u, int v);

/*
 Restore the solution graph to the state it was in before a call
   to "solution_graph_add_edge()".
 set_point value returned by a call made to add an edge
*/
void solution_graph_rollback(SolutionGraph *sol, int set_point);

/*
 Returns non-zero if the solution graph has an edge directed from u to v.
 Treat the return as boolean. Zero value denotes no edge.
*/
unsigned char solution_graph_has_edge(SolutionGraph *sol, int u, int v);

/*
 Returns presence of an edge directed from u to v in the modified majority
 graph.  The rule is that, if the edge exists in the solution graph, it exists
 in the modified majority graph. Otherwise, if the edge exists in the majority
 graph and the opposite edge is not in the solution graph, then the edge is in
 the modified majority graph.  Treat the return as boolean. Zero value denotes
 no edge.
*/
unsigned char solution_graph_has_majority_edge(SolutionGraph *sol,
  int r, int c);

/*
 Returns the current disagreement count, which is the total
 weight of edges in the majority graph that are opposite an edge in
 the solution graph.
*/
int solution_graph_disagreements(SolutionGraph *sol);

/*
 Delegates with a call to rank_sorted_items().
 Find the description in ranking.h
*/
void solution_graph_rank_sort_items(SolutionGraph *sol,
  const int *topological_sort, int *ranking);

#endif
