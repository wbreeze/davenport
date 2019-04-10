#include <cutter.h>
#include <stdio.h>
#include "../src/preflow_push.c"

void test_push_excess(void);
void test_push_excess(void)
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
  cut_assert_equal_int(0, excess[from]);
  cut_assert_equal_int(send, excess[to]);
  cut_assert_equal_int(send, flow[RCI(from,to,node_ct)]);
  cut_assert_equal_int(-send, flow[RCI(to,from,node_ct)]);
}

void test_push_capacity(void);
void test_push_capacity(void)
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
  cut_assert_equal_int(send - cap, excess[from]);
  cut_assert_equal_int(cap, excess[to]);
  cut_assert_equal_int(cap, flow[RCI(from,to,node_ct)]);
  cut_assert_equal_int(-cap, flow[RCI(to,from,node_ct)]);
}

void test_push_residual(void);
void test_push_residual(void)
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
  cut_assert_equal_int(send - residual, excess[from]);
  cut_assert_equal_int(residual, excess[to]);
  printf("FLOW:\n");
  for(int i = 0; i < node_ct; ++i) {
    for (int j = 0; j < node_ct; ++j) {
      printf("%d\t", flow[RCI(i,j,node_ct)]);
    }
    printf("\n");
  }
  cut_assert_equal_int(cap, flow[RCI(from,to,node_ct)]);
  cut_assert_equal_int(-residual, flow[RCI(to,from,node_ct)]);
}
