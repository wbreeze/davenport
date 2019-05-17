#ifndef PREFERENCE_GRAPH_H
#define PREFERENCE_GRAPH_H

/*
 Add rankings to preference graph
 Where rankings[u] < rankings[v] we increment preference_graph[u,v] by one.
   Ranks are numbered in order of preference. A lower number rank is preferred
   to higher number rank. They are as in "First, second, third, ...".
 node_ct: is the number of nodes represented by the preference graph
 preference_graph: modified by the call, edge array allocated to minimum
   ECT(node_ct) integers, size ESZ(node_ct)
 rankings: read by the call, node array allocated to minimum node_ct integers,
   size NSZ(node_ct)
*/
void preference_graph_add_preference(int *preference_graph,
  const int *rankings, int node_ct);

/*
 Initialize a majority graph from a preference graph
 Writes majority_graph[u,v] = preference_graph[u,v] - preference_graph[v,u]
   when preference_graph[u,v] > preference_graph[v,u], otherwise writes
   majority_graph[u,v] to zero.
 node_ct: is the number of nodes represented by the preference graph
 preference_graph: read by the call, edge array allocated to minimum
   ECT(node_ct) integers, size ESZ(node_ct)
 majority_graph: modified by the call, edge array allocated to minimum
   ECT(node_ct) integers, size ESZ(node_ct)
*/
void preference_graph_to_majority_graph(const int *preference_graph,
  int *majority_graph, int node_ct);

#endif
