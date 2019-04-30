#ifndef SORTING_H
#define SORTING_H

/*
 sort selection according to decreasing weight of edges
 selection contains indexes into edges
 select_ct is the number of edge indexes in the selection
*/
void sort_edge_selection(const int *edges, int *selection, int select_ct);

/*
 Given topological position of each node by index, where greater position
   numbers come before lesser ones (result of Tarjan component computation),
 Return in topo_sort the node indexes in preference order such that
   topo_positions[topo_sort[i]] >= topo_positions[topo_sort[i+1]]
 Both topo_positions and topo_sort are integer arrays of size no less than
   node_ct. Only the first node_ct items are sorted.
*/
void sort_nodes_topo(const int *topo_positions, int *topo_sort, int node_ct);

#endif
