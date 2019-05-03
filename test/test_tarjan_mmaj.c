#include <cutter.h>
#include "test_helper.h"
#include "../src/network.h"
#include "../src/tarjan.h"

struct EdgeLookup {
  unsigned char was_called;
  const int *edges;
};

int edge_lookup(void *context, int r, int c, int node_ct)
{
  struct EdgeLookup *el = (struct EdgeLookup *)context;
  el->was_called = 1;
  return el->edges[RCI(r,c,node_ct)];
}

void test_tarjan_edge_lookup(void)
{
  int node_ct = 8;
  int *edges = edge_array_calloc(node_ct);
  int *components = node_array_calloc(node_ct);
  struct EdgeLookup *el = malloc(sizeof(struct EdgeLookup));
  el->was_called = 0;
  el->edges = edges;

  set_majority_tarjan_example(edges, node_ct);

  Tarjan *t = tarjan_create(edge_lookup, el, node_ct);
  tarjan_identify_components(t, components);
  t = tarjan_destroy(t);

  cut_assert_true(el->was_called);

  free(el);
  free(components);
  free(edges);
}
