/*
 Produce a rank order for the items given:
 - solution_graph, a transitive, directed graph with edge (u,v) indicating that
   u comes before (<) v. Although transitive, the groph is not necessarily
   complete.  The graph may have u < v and u < w but no edge between v and w
   that orders one before the other.
 - topological_sort, a list of node indices sorted in topological order.
   If u is topologically prior to v, u occurs prior in the list.
   For v and w, which are topologically equivalent, either may occur before
   the other.
 - node_ct is the number of nodes in the graph, and in the sort
 - Places the result in ranking. The rank number for the node at index u
   is the number of nodes/items that occur prior to it in the topological
   sort, plus one. The root has rank one. Two children of the root v, w at equal
   depth in the tree both have rank two. A child of v or w will have rank
   four, because there are three nodes before it in the topological sort.
*/
void rank_sorted_items(const unsigned char *solution_graph,
  const int *topological_sort, int node_ct, int *ranking);
