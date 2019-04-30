/*
 Produce a rank order for the items given:
 - solution_graph, a transitive, directed graph with edge (u,v) indicating that
   u comes before (<) v. Although transitive, the groph is not necessarily
   complete.  The graph may have u < v and u < w but no edge between v and w
   that orders one before the other.  The function treats this array as
   containing at least ECT(node_ct) entries, with non-zero values signifying a
   connection.
 - topological_sort, a list of node indices sorted in topological order.  If u
   is topologically prior to v, the index for u occurs prior in the list.  For
   v and w, which are topologically equivalent, either may occur before the
   other. If any of these values are outside the range 0 <= u < node_ct, the
   function might attempt to read and write outside of allocated storage.
 - node_ct is the number of nodes in the graph, and in the sort
 - Places the result in ranking. The rank number ranking[u] is the number of
   nodes/items that occur prior to item at index u in the topological sort,
   plus one. The root has rank one. Two children of the root v, w at equal
   depth in the tree both have rank two. A child of v or w will have rank four,
   because there are three nodes before it in the topological sort.  There
   should be at least node_ct integers allocated to ranking.
*/
void rank_sorted_items(const unsigned char *solution_graph,
  const int *topological_sort, int node_ct, int *ranking);
