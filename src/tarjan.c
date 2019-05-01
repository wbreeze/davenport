#include <assert.h>
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

#define ONSTACK_SIZE(t) (t->node_ct * sizeof(unsigned char))

void tarjan_init(Tarjan *t)
{
  t->next_index = 1;
  t->next_id = 1;
  t->depth = 0;
  node_array_clear(t->index, t->node_ct);
  node_array_clear(t->lowlink, t->node_ct);
  memset(t->onstack, 0, ONSTACK_SIZE(t));
}

Tarjan *tarjan_create(int node_ct)
{
  Tarjan *t = malloc(sizeof(Tarjan));

  t->node_ct = node_ct;
  t->index = node_array_calloc(node_ct);
  t->lowlink = node_array_calloc(node_ct);
  t->stack = node_array_calloc(node_ct);
  t->onstack = malloc(ONSTACK_SIZE(t));

  tarjan_init(t);
  return t;
}

Tarjan *tarjan_destroy(Tarjan *t)
{
  free(t->onstack);
  free(t->stack);
  free(t->lowlink);
  free(t->index);
  free(t);

  return NULL;
}

void tarjan_push(Tarjan *t, int v)
{
  if (t->depth < t->node_ct && v < t->node_ct) {
    t->stack[t->depth++] = v;
    t->onstack[v] = 1;
  }
}

int tarjan_pop(Tarjan *t)
{
  int v = 0;
  if (0 < t->depth) {
    v = t->stack[--t->depth];
    t->onstack[v] = 0;
  }
  return v;
}

int tarjan_next_index(Tarjan *t)
{
  return t->next_index++;
}

void tarjan_connect(Tarjan *t,
  const int *edges, int node_ct, int *components, int v)
{
  t->index[v] = t->lowlink[v] = tarjan_next_index(t);
  tarjan_push(t, v);

  for (int w = 0; w < node_ct; ++w) {
    if (edges[RCI(v,w,node_ct)] != 0) {
      if (t->index[w] == 0) {
        tarjan_connect(t, edges, node_ct, components, w);
        t->lowlink[v] = MIN(t->lowlink[v], t->lowlink[w]);
      } else if (t->onstack[w]) {
        t->lowlink[v] = MIN(t->lowlink[v], t->index[w]);
      }
    }
  }

  if (t->lowlink[v] == t->index[v]) {
    int w, ct = 0;
    do {
      w = tarjan_pop(t);
      components[w] = t->next_id;
      ++ct;
    } while(w != v);
    t->next_id += ct;
  }
}

void tarjan_identify_components(Tarjan *t, const int *edges, int node_ct,
  int *components)
{
  assert(node_ct <= t->node_ct);
  tarjan_init(t);
  for (int i = 0; i < node_ct; ++i) {
    if (t->index[i] == 0) {
      tarjan_connect(t, edges, node_ct, components, i);
    }
  }
}
