#ifndef NETWORK_H
#define NETWORK_H

#include <stdlib.h>
#include <string.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define RCI(row, col, node_ct) ((row) * (node_ct) + (col))
#define ECT(node_ct) ((node_ct) * (node_ct))

#define edge_array_calloc(node_ct) calloc(ECT(node_ct), sizeof(int))
#define node_array_calloc(node_ct) calloc(node_ct, sizeof(int))
#define node_array_clear(array, node_ct) memset(array, 0, node_ct * sizeof(int))
#define solution_array_calloc(node_ct) \
  calloc(ECT(node_ct), sizeof(unsigned char))

void edge_array_print(const int *edges, int node_ct);
void edge_array_printl(const int *edges, int node_ct, char *label);

void node_array_print(const int *nodes, int node_ct);
void node_array_printl(const int *nodes, int node_ct, char *label);

#endif
