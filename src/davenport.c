#include <stdlib.h>
#include "davenport.h"
#include "network.h"

Davenport *davenport_create(const int *majority_graph, int node_ct)
{
  Davenport *d = malloc(sizeof(struct Davenport));
  d->node_ct = node_ct;
  d->majority_graph = majority_graph;
  d->solution = solution_array_calloc(node_ct);

  return d;
}

Davenport *davenport_destroy(Davenport * d)
{
  free(d->solution);
  free(d);
  return NULL;
}

void dv_initialize_solution(d)
{
}
