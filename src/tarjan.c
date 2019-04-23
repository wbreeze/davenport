#include <stdlib.h>
#include "network.h"
#include "tarjan.h"

/*
 Implements Tarjan's algorithm for identifying connected components in
 a directed graph. Find the algorithm is described at
 https://en.wikipedia.org/wiki/Tarjan%27s_strongly_connected_components_algorithm
 which references an original paper at
 https://epubs.siam.org/doi/10.1137/0201010
 Tarjan, Robert. Depth-First Search and Linear Graph Algorithms.
 SIAM Journal on Computing, 1(2), 146-160. 1972
*/

Tarjan *tarjan_new(const int *edges, int node_ct, int *components)
{
  Tarjan *tarjan = malloc(sizeof(Tarjan));

  tarjan->node_ct = node_ct;
  tarjan->edges = edges;
  tarjan->lowlink = components;
  tarjan->next_index = 1;
  tarjan->index = node_array_calloc(node_ct);
  tarjan->depth = 0;
  tarjan->stack = node_array_calloc(node_ct);
  tarjan->onstack = calloc(node_ct, sizeof(unsigned char));

  return tarjan;
}

Tarjan *tarjan_destroy(Tarjan *tarjan)
{
  free(tarjan->onstack);
  free(tarjan->stack);
  free(tarjan->index);
  free(tarjan);

  return NULL;
}

void tarjan_push(Tarjan *tarjan, int v)
{
  if (tarjan->depth < tarjan->node_ct && v < tarjan->node_ct) {
    tarjan->stack[tarjan->depth++] = v;
    tarjan->onstack[v] = 1;
  }
}

int tarjan_pop(Tarjan *tarjan)
{
  int v = 0;
  if (0 < tarjan->depth) {
    v = tarjan->stack[--tarjan->depth];
    tarjan->onstack[v] = 0;
  }
  return v;
}

int tarjan_next_index(Tarjan *tarjan)
{
  return tarjan->next_index++;
}

void tarjan_connect(Tarjan *tarjan, int v)
{
  tarjan->index[v] = tarjan->lowlink[v] = tarjan_next_index(tarjan);
  tarjan_push(tarjan, v);

  for (int w = 0; w < tarjan->node_ct; ++w) {
    if (tarjan->edges[RCI(v,w,tarjan->node_ct)] != 0) {
      if (tarjan->index[w] == 0) {
        tarjan_connect(tarjan, w);
        tarjan->lowlink[v] = MIN(tarjan->lowlink[v], tarjan->lowlink[w]);
      } else if (tarjan->onstack[w]) {
        tarjan->lowlink[v] = MIN(tarjan->lowlink[v], tarjan->lowlink[w]);
      }
    }
  }

  if (tarjan->lowlink[v] == tarjan->index[v]) {
    int w;
    do {
      w = tarjan_pop(tarjan);
    } while(w != v);
  }
}

void identify_components(const int *edges, int node_ct, int *components)
{
  Tarjan *tarjan = tarjan_new(edges, node_ct, components);
  for (int i = 0; i < node_ct; ++i) {
    if (tarjan->index[i] == 0) {
      tarjan_connect(tarjan, i);
    }
  }
  tarjan = tarjan_destroy(tarjan);
}
