#include <cutter.h>
#include "../src/network.h"
#include "../src/sorting.h"
#include "test_helper.h"

void test_sort_edges_1(void) {
  const int node_ct = 12;
  int *edges = edge_array_calloc(node_ct);
  int *selection = edge_array_calloc(node_ct);

  int select_ct = 0;
  int next_weight = 1;
  for(int r = 0; r < node_ct; ++r) {
    for(int c = 0; c < node_ct; ++c) {
      if (r != c && (r + c) % 2 == 1) {
        int index = RCI(r,c,node_ct);
        edges[index] = next_weight++;
        selection[select_ct++] = index;
      }
    }
  }
  sort_edge_selection(edges, selection, select_ct);

  for(int i = 1; i < select_ct; ++i) {
    cut_assert_operator_int(edges[selection[i]], <, edges[selection[i-1]]);
  }

  free(selection);
  free(edges);
}

void test_sort_edges_2(void) {
  const int edge_ct = 12;
  const int select_ct = 6;

  int edges[edge_ct] = { 1, 3, 5, 7, 9, 11, 2, 3, 4, 5, 6, 12 };
  int selection[select_ct] = { 0, 2, 4, 6, 8, 10 };
  sort_edge_selection(edges, selection, select_ct);

  int expected[select_ct] = { 4, 10, 2, 8, 6, 0 };
  assert_equal_int_array(expected, selection, select_ct);
}

void test_sort_edges_3(void) {
  const int node_ct = 12;
  int *edges = edge_array_calloc(node_ct);
  int *selection = edge_array_calloc(node_ct);

  int select_ct = 0;
  for(int r = 0; r < node_ct; ++r) {
    for(int c = 0; c < node_ct; ++c) {
      int index = RCI(r,c,node_ct);
      if ((r + c) % 2 == 1) {
        edges[index] = r;
      }
      selection[select_ct++] = index;
    }
  }
  sort_edge_selection(edges, selection, select_ct);

  for(int i = 1; i < select_ct; ++i) {
    cut_assert_operator_int(edges[selection[i]], <=, edges[selection[i-1]]);
  }

  free(selection);
  free(edges);
}
