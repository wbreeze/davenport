#ifndef SOLUTION_GRAPH_H
#define SOLUTION_GRAPH_H

/*
 Called when an edge is added or removed, either through add_edge, by
 transitive closure, or by rollbock.
 The offsets u and v are from and to; direction is 1 if the edge from
   u to v is added, -1 if the edge from u to v is removed.
 This little coding trick saves making two separate callbacks.
*/
typedef void SolutionGraphEdgeChange(
  void *context, int u, int v, int direction);

typedef struct SolutionGraph {
  int node_ct;
  unsigned char *solution;
  int set_point;
  int *edge_stack;
  SolutionGraphEdgeChange *change;
  void *change_context;
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
 The graph tracks order of edge addition so that it may be rolled back.
*/
SolutionGraph *solution_graph_create(int node_ct);
SolutionGraph *solution_graph_destroy(SolutionGraph *sol);

/*
 Register callback for edge addition and removal
*/
void solution_graph_on_edge_change(SolutionGraph *sol,
  SolutionGraphEdgeChange *change, void *context);

/*
 Add an edge (u,v) to the solution graph and maintain transitive closure.
 This works provided the solution graph is already transitive.
 By always calling this method to add edges, we ensure that is the case.
 We don't do any work if the edge is already in the graph.
 Returns a set_point that can be used with "solution_graph_rollback()"
   to put the solution graph in the state it had before this call.
 Will invoke the edge addition and removal callback.
*/
int solution_graph_add_edge(SolutionGraph *sol, int u, int v);

/*
 Restore the solution graph to the state it was in before a call
   to "solution_graph_add_edge()".
 set_point value returned by a call made to add an edge
 Will invoke the edge addition and removal callback.
*/
void solution_graph_rollback(SolutionGraph *sol, int set_point);

/*
 Returns non-zero if the solution graph has an edge directed from u to v.
 Treat the return as boolean. Zero value denotes no edge.
*/
unsigned char solution_graph_has_edge(SolutionGraph *sol, int u, int v);

/*
 Delegates with a call to rank_sorted_items().
 Find the description in ranking.h
*/
void solution_graph_rank_sort_items(SolutionGraph *sol,
  const int *topological_sort, int *ranking);

/*
 Send a picture of the solution graph to stdout.
*/
void solution_graph_printl(SolutionGraph *sol, char *message);

#endif
