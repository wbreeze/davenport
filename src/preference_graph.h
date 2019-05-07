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

#endif
