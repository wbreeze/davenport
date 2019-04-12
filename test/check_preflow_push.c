#include <check.h>
#include <stdio.h>
#include "check_preflow_push.h"
#include "../src/preflow_push.h"

START_TEST(check_push_excess)
{
  int node_ct = 2;
  int excess[2];
  int flow[4];
  int capacity[4];
  int send = 4;
  int from = 0;
  int to = 1;

  excess[from] = send;
  capacity[RCI(from,to,node_ct)] = send + 1;
  flow[RCI(from,to,node_ct)] = 0;
  push(capacity, flow, excess, node_ct, from, to);
  ck_assert_int_eq(0, excess[from]);
  ck_assert_int_eq(send, excess[to]);
  ck_assert_int_eq(send, flow[RCI(from,to,node_ct)]);
  ck_assert_int_eq(-send, flow[RCI(to,from,node_ct)]);
}
END_TEST

START_TEST(check_push_capacity)
{
  int node_ct = 2;
  int excess[2];
  int flow[4];
  int capacity[4];
  int send = 4;
  int cap = 2;
  int from = 0;
  int to = 1;

  excess[from] = send;
  capacity[RCI(from,to,node_ct)] = cap;
  flow[RCI(from,to,node_ct)] = 0;
  push(capacity, flow, excess, node_ct, from, to);
  ck_assert_int_eq(send - cap, excess[from]);
  ck_assert_int_eq(cap, excess[to]);
  ck_assert_int_eq(cap, flow[RCI(from,to,node_ct)]);
  ck_assert_int_eq(-cap, flow[RCI(to,from,node_ct)]);
}
END_TEST

START_TEST(check_push_residual)
{
  int node_ct = 2;
  int excess[2];
  int flow[4];
  int capacity[4];
  int send = 4;
  int cap = 4;
  int existing = 2;
  int residual = cap - existing;
  int from = 0;
  int to = 1;

  excess[from] = send;
  capacity[RCI(from,to,node_ct)] = cap;
  flow[RCI(from,to,node_ct)] = existing;
  push(capacity, flow, excess, node_ct, from, to);
  ck_assert_int_eq(send - residual, excess[from]);
  ck_assert_int_eq(residual, excess[to]);
  printf("FLOW:\n");
  for(int i = 0; i < node_ct; ++i) {
    for (int j = 0; j < node_ct; ++j) {
      printf("%d\t", flow[RCI(i,j,node_ct)]);
    }
    printf("\n");
  }
  ck_assert_int_eq(cap, flow[RCI(from,to,node_ct)]);
  ck_assert_int_eq(-residual, flow[RCI(to,from,node_ct)]);
}
END_TEST

Suite *make_preflow_push_suite(void)
{
  Suite *s;
  TCase *tc;

  s = suite_create("Preflow Push");
  tc = tcase_create("Core");

  suite_add_tcase (s, tc);
  tcase_add_test(tc, check_push_excess);
  tcase_add_test(tc, check_push_capacity);
  tcase_add_test(tc, check_push_residual);
  return s;
}
