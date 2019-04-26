#include <cutter.h>
#include <stdlib.h>
#include "../src/davenport.h"
#include "../src/network.h"
#include "test_helper.h"
#include "test_davenport.h"

void test_davenport_create(void)
{
  int node_ct = 4;
  int *majority_graph = edge_array_calloc(node_ct);

  Davenport *d = davenport_create(majority_graph, node_ct);

  cut_assert(d != NULL);
  cut_assert_equal_pointer(majority_graph, d->majority_graph);
  cut_assert_equal_int(node_ct, d->node_ct);
  memset(d->solution, 0, node_ct * sizeof(unsigned char));
  memset(d->components, 0, node_ct);
  memset(d->edge_list, 0, DV_EDGE_CT(node_ct));

  d = davenport_destroy(d);
  cut_assert_equal_pointer(NULL, d);
  free(majority_graph);
}
