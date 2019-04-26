#ifndef EDGE_SELECTION_H
#define EDGE_SELECTION_H

/*
 sort selection according to decreasing weight of edges
 selection contains indexes into edges
 select_ct is the number of edge indexes in the selection
*/
void sort_edge_selection(const int *edges, int *selection, int select_ct);

#endif
