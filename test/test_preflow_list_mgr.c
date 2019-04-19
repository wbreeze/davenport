#include <cutter.h>
#include "test_helper.h"
#include "test_preflow_push.h"
#include "../src/network.h"
#include "../src/preflow_push.h"

void test_initialize_list_ends(void)
{
  int node_ct = 8;
  int source = 0;
  int sink = 7;
  int *list = node_array_calloc(node_ct);
  initialize_list(list, node_ct, source, sink);
  cut_assert_equal_int(1, list[0]);
  cut_assert_equal_int(6, list[5]);
  for (int i = 0; i < node_ct - 2; ++i)
  {
    cut_assert_not_equal_int(source, list[i]);
    cut_assert_not_equal_int(sink, list[i]);
  }
  free(list);
}

void test_initialize_list_middle(void)
{
  int node_ct = 8;
  int source = 3;
  int sink = 4;
  int *list = node_array_calloc(node_ct);
  initialize_list(list, node_ct, source, sink);
  cut_assert_equal_int(0, list[0]);
  cut_assert_equal_int(7, list[5]);
  for (int i = 0; i < node_ct - 2; ++i)
  {
    cut_assert_not_equal_int(source, list[i]);
    cut_assert_not_equal_int(sink, list[i]);
  }
  free(list);
}

void test_move_to_front_noop(void)
{
  int node_ct = 5;
  int list[] = {1,2,3,4,5};
  int expected[] = {1,2,3,4,5};
  moveToFront(list, 0);
  assert_equal_int_array(expected, list, node_ct);
}

void test_move_to_front_middle(void)
{
  int node_ct = 5;
  int list[] = {1,2,3,4,5};
  int expected[] = {3,1,2,4,5};
  moveToFront(list, 2);
  assert_equal_int_array(expected, list, node_ct);
}

void test_move_to_front_last(void)
{
  int node_ct = 5;
  int list[] = {1,2,3,4,5};
  int expected[] = {5,1,2,3,4};
  moveToFront(list, 4);
  assert_equal_int_array(expected, list, node_ct);
}
