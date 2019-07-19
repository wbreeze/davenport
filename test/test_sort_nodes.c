#include <cutter.h>
#include "../src/network.h"
#include "../src/sorting.h"
#include "array_init.h"
#include "test_helper.h"

void test_sort_nodes_1(void) {
  const int node_ct = 12;
  int *topo_positions = node_array_calloc(node_ct);
  int *topo_sort = node_array_calloc(node_ct);

  for(int r = 0; r < node_ct; ++r) {
    topo_positions[r] = r + 1;
  }
  sort_nodes_topo(topo_positions, topo_sort, node_ct);

  for(int i = 1; i < node_ct; ++i) {
    cut_assert_operator_int(topo_positions[topo_sort[i]], <,
      topo_positions[topo_sort[i-1]]);
  }

  free(topo_positions);
  free(topo_sort);
}

void test_sort_nodes_2(void) {
  const int node_ct = 12;
  int *topo_sort = node_array_calloc(node_ct);
  int topo_positions[node_ct];
  int_array_init(topo_positions, node_ct,
    1, 3, 5, 7, 9, 11, 2, 4, 6, 8, 10, 12);

  sort_nodes_topo(topo_positions, topo_sort, node_ct);

  int expected[node_ct];
  int_array_init(expected, node_ct, 11, 5, 10, 4, 9, 3, 8, 2, 7, 1, 6, 0);
  assert_equal_int_array(expected, topo_sort, node_ct);

  free(topo_sort);
}
