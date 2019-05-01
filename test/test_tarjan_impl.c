#include <cutter.h>
#include <string.h>
#include "test_helper.h"
#include "test_tarjan.h"
#include "../src/network.h"
#include "../src/tarjan.h"

void test_tarjan_create(void)
{
  int node_ct = 6;
  Tarjan *tarjan = tarjan_create(node_ct);

  cut_assert_equal_int(node_ct, tarjan->node_ct);
  clear_int_array(tarjan->index, node_ct);
  clear_int_array(tarjan->lowlink, node_ct);
  cut_assert_equal_int(1, tarjan->next_index);
  cut_assert_equal_int(1, tarjan->next_id);
  cut_assert_equal_int(0, tarjan->depth);
  clear_int_array(tarjan->stack, node_ct);
  cut_assert_equal_int(0, tarjan->onstack[0]);

  tarjan = tarjan_destroy(tarjan);
}

void test_tarjan_push(void)
{
  int node_ct = 6;
  Tarjan *tarjan = tarjan_create(node_ct);

  tarjan_push(tarjan, node_ct + 1);
  cut_assert_equal_int(0, tarjan->depth);

  for (int i = 0; i < node_ct; ++i) {
    tarjan_push(tarjan, i);
    cut_assert_equal_int(i, tarjan->stack[i]);
    cut_assert_true(tarjan->onstack[i]);
  }
  cut_assert_equal_int(node_ct, tarjan->depth);

  tarjan_push(tarjan, 1);
  cut_assert_equal_int(node_ct, tarjan->depth);

  tarjan = tarjan_destroy(tarjan);
}

void test_tarjan_pop(void)
{
  int node_ct = 6;
  Tarjan *tarjan = tarjan_create(node_ct);

  int v = tarjan_pop(tarjan);
  cut_assert_equal_int(0, v);
  cut_assert_equal_int(0, tarjan->depth);

  int i = node_ct - 2;
  tarjan_push(tarjan, i);
  cut_assert_equal_int(i, tarjan->stack[0]);
  cut_assert_true(tarjan->onstack[i]);
  cut_assert_equal_int(1, tarjan->depth);

  v = tarjan_pop(tarjan);
  cut_assert_equal_int(i, v);
  cut_assert_false(tarjan->onstack[v]);
  cut_assert_equal_int(0, tarjan->depth);

  tarjan = tarjan_destroy(tarjan);
}

void test_tarjan_next_index(void)
{
  int node_ct = 6;
  Tarjan *tarjan = tarjan_create(node_ct);

  cut_assert_equal_int(1, tarjan->next_index);
  cut_assert_equal_int(1, tarjan_next_index(tarjan));
  cut_assert_equal_int(2, tarjan->next_index);
  cut_assert_equal_int(2, tarjan_next_index(tarjan));
  cut_assert_equal_int(3, tarjan->next_index);

  tarjan = tarjan_destroy(tarjan);
}
