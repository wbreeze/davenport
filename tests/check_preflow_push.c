#include "check_davenport.h"
#include "../src/preflow_push.c"

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

Suite *make_preflow_push_suite(void)
{
  Suite *s;
  TCase *tc;

  s = suite_create("Preflow Push");
  tc = tcase_create("Core");

  suite_add_tcase (s, tc);
  tcase_add_test(tc, check_push_excess);
  return s;
}
