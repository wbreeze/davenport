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

  d = davenport_destroy(d);
  cut_assert_equal_pointer(NULL, d);
  free(majority_graph);
}

void test_initialize_solution_pentagon_2(void)
{
  int node_ct = 5;
  int *majority_graph = edge_array_calloc(node_ct);
  Davenport *d = davenport_create(majority_graph, node_ct);
  set_majority_net_pentagon_2(majority_graph, node_ct);

  dv_initialize_solution(d);

  unsigned char *solution_graph = solution_array_calloc(node_ct);
  assert_equal_int_array(solution_graph, d->solution, node_ct);

  d = davenport_destroy(d);
  free(majority_graph);
}

void test_initialize_solution_pentagon_5(void)
{
  int node_ct = 5;
  int *majority_graph = edge_array_calloc(node_ct);
  Davenport *d = davenport_create(majority_graph, node_ct);
  set_majority_net_pentagon_5(majority_graph, node_ct);

  dv_initialize_solution(d);

  cut_assert_equal_int(0, d->solution[RCI(0,0,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(3,3,node_ct)]);
  cut_assert_equal_int(1, d->solution[RCI(3,4,node_ct)]);
  cut_assert_equal_int(1, d->solution[RCI(3,0,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(0,3,node_ct)]);
  cut_assert_equal_int(1, d->solution[RCI(3,1,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(1,3,node_ct)]);
  cut_assert_equal_int(1, d->solution[RCI(3,2,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(2,3,node_ct)]);
  cut_assert_equal_int(1, d->solution[RCI(4,0,node_ct)]);
  cut_assert_equal_int(1, d->solution[RCI(4,1,node_ct)]);
  cut_assert_equal_int(1, d->solution[RCI(4,2,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(2,4,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(1,2,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(2,1,node_ct)]);

  d = davenport_destroy(d);
  free(majority_graph);
}

void test_initialize_solution_one_cycle_embedded(void)
{
  int node_ct = 5;
  int *majority_graph = edge_array_calloc(node_ct);
  Davenport *d = davenport_create(majority_graph, node_ct);
  set_majority_net_one_cycle_embedded(majority_graph, node_ct);

  dv_initialize_solution(d);

  cut_assert_equal_int(1, d->solution[RCI(0,1,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(0,2,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(0,3,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(0,4,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(1,0,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(1,2,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(1,3,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(1,4,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(2,0,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(2,1,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(2,3,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(2,4,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(3,0,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(3,2,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(3,1,node_ct)]);
  cut_assert_equal_int(1, d->solution[RCI(3,4,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(4,0,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(4,1,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(4,2,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(4,3,node_ct)]);

  d = davenport_destroy(d);
  free(majority_graph);
}

void test_initialize_solution_multi_cycle_embedded(void)
{
  int node_ct = 8;
  int *majority_graph = edge_array_calloc(node_ct);
  Davenport *d = davenport_create(majority_graph, node_ct);
  set_majority_net_multi_cycle_embedded(majority_graph, node_ct);

  dv_initialize_solution(d);

  cut_assert_equal_int(0, d->solution[RCI(0,0,node_ct)]);
  cut_assert_equal_int(1, d->solution[RCI(0,1,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(0,2,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(0,3,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(0,4,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(0,5,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(0,6,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(0,7,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(1,0,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(1,1,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(1,2,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(1,3,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(1,4,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(1,5,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(1,6,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(1,7,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(2,0,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(2,1,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(2,2,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(2,3,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(2,4,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(2,5,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(2,6,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(2,7,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(3,0,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(3,1,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(3,2,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(3,3,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(3,4,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(3,5,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(3,6,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(3,7,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(4,0,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(4,1,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(4,2,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(4,3,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(4,4,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(4,5,node_ct)]);
  cut_assert_equal_int(1, d->solution[RCI(4,6,node_ct)]);
  cut_assert_equal_int(1, d->solution[RCI(4,7,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(5,0,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(5,1,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(5,2,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(5,3,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(5,4,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(5,5,node_ct)]);
  cut_assert_equal_int(1, d->solution[RCI(5,6,node_ct)]);
  cut_assert_equal_int(1, d->solution[RCI(5,7,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(6,0,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(6,1,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(6,2,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(6,3,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(6,4,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(6,5,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(6,6,node_ct)]);
  cut_assert_equal_int(1, d->solution[RCI(6,7,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(7,0,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(7,1,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(7,2,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(7,3,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(7,4,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(7,5,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(7,6,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(7,7,node_ct)]);

  d = davenport_destroy(d);
  free(majority_graph);
}

void test_initialize_solution_two_embedded_cycles(void)
{
  int node_ct = 8;
  int *majority_graph = edge_array_calloc(node_ct);
  Davenport *d = davenport_create(majority_graph, node_ct);
  set_majority_net_two_embedded_cycles(majority_graph, node_ct);

  dv_initialize_solution(d);

  cut_assert_equal_int(0, d->solution[RCI(0,0,node_ct)]);
  cut_assert_equal_int(1, d->solution[RCI(0,1,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(0,2,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(0,3,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(0,4,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(0,5,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(0,6,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(0,7,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(1,0,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(1,1,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(1,2,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(1,3,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(1,4,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(1,5,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(1,6,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(1,7,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(2,0,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(2,1,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(2,2,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(2,3,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(2,4,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(2,5,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(2,6,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(2,7,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(3,0,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(3,1,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(3,2,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(3,3,node_ct)]);
  cut_assert_equal_int(1, d->solution[RCI(3,4,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(3,5,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(3,6,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(3,7,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(4,0,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(4,1,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(4,2,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(4,3,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(4,4,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(4,5,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(4,6,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(4,7,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(5,0,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(5,1,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(5,2,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(5,3,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(5,4,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(5,5,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(5,6,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(5,7,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(6,0,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(6,1,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(6,2,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(6,3,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(6,4,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(6,5,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(6,6,node_ct)]);
  cut_assert_equal_int(1, d->solution[RCI(6,7,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(7,0,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(7,1,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(7,2,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(7,3,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(7,4,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(7,5,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(7,6,node_ct)]);
  cut_assert_equal_int(0, d->solution[RCI(7,7,node_ct)]);

  d = davenport_destroy(d);
  free(majority_graph);
}
