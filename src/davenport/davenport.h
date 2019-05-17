#ifndef DAVENPORT_H
#define DAVENPORT_H

/*
 Callback function invoked when the algorithm finds a solution.
 The context is that supplied by the receiver when the callback was set.
 The ranking is node_ct integers with an index 0 < index <= node_ct for the
 node at the corresponding row or column of the majority graph.
 The disagreement_count is the total of weights from the majority graph
 broken by opposite edges in the solution from which the ranking is derived.

 The data within ranking belongs to the caller and will change after
 the callback returns.
*/
typedef void (*DavenportSolutionCallback)(
  void *context, int *ranking, int node_ct, int disagreement_count
);

typedef struct Davenport Davenport;

/*
 Create data structure for Kemeny order computation.
 Accepts an existing majority graph and count of nodes (alternatives)
 The majority_graph contains integer weights, where the weight at
 RCI(u,v,node_ct) is zero, or represents a majority weight of preference
 for alternative index u over v.
 The caller represents the following:
 - majority_graph has memory allocated to ECT(node_ct) * sizeof(int)
 - that memory is not freed before calling davenport_destroy with the
   returned pointer to the Davenport data structure.
 - if majority_graph[RCI(u,v,node_ct)] is non-zero, then
   majority_graph[RCI(v,u,node_ct)] is zero. (There are no reverse edges,
   nor edges to self.)
*/
Davenport *davenport_create(const int *majority_graph, int node_ct);

/*
 Free the storage allocated for Kemeny order computation and the
 data structure used to track it.
 Always returns NULL.
*/
Davenport *davenport_destroy(Davenport *d);

/*
 Set a callback that will be invoked with each viable ordering found by the
 algorithm. The value of disagreements will decrease. That is, the callback
 will not be invoked with orderings that have  more disagreements than in prior
 invocations of the callback. However, the algorithm may invoke the callback
 with "best found so far" orderings. It is up to the provider of the callback
 what to do with solutions from any prior invocations that had a greater number
 of disagreements.

 The algorithm passes the context pointer in the callback and otherwise
 leaves it entirely under control of the receiver.

 This is to keep the algorithm out of the solution management business,
 leaving solution management uncoupled from the core search.
*/
void davenport_set_solution_callback(Davenport *d,
  DavenportSolutionCallback callback, void *context);

/*
 Compute Kemeny-Young partial orders for the current majority graph.
 Returns the count of solutions, also available as d->solution_ct.
*/
int davenport_compute(Davenport *d);

/*
 Return the last computed solution
*/
int *davenport_last_solution(Davenport *d);

#endif
