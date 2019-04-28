#include <assert.h>
#include "../src/network.h"

void set_majority_net_pentagon_2(int *majority, int node_ct)
{
  assert(5 <= node_ct);
  majority[RCI(0,1,node_ct)] = 3;
  majority[RCI(0,2,node_ct)] = 2;
  majority[RCI(1,3,node_ct)] = 2;
  majority[RCI(1,4,node_ct)] = 3;
  majority[RCI(2,4,node_ct)] = 2;
  majority[RCI(3,0,node_ct)] = 2;
  majority[RCI(4,0,node_ct)] = 3;
}

void set_majority_net_pentagon_3(int *majority, int node_ct)
{
  assert(5 <= node_ct);
  majority[RCI(0,2,node_ct)] = 2;
  majority[RCI(1,3,node_ct)] = 2;
  majority[RCI(2,3,node_ct)] = 3;
  majority[RCI(3,0,node_ct)] = 2;
  majority[RCI(3,4,node_ct)] = 3;
  majority[RCI(4,1,node_ct)] = 2;
}

void set_majority_net_pentagon_4(int *majority, int node_ct)
{
  assert(5 <= node_ct);
  majority[RCI(0,1,node_ct)] = 3;
  majority[RCI(1,2,node_ct)] = 3;
  majority[RCI(1,3,node_ct)] = 2;
  majority[RCI(2,4,node_ct)] = 2;
  majority[RCI(4,1,node_ct)] = 2;
}

void set_majority_net_pentagon_5(int *majority, int node_ct)
{
  assert(5 <= node_ct);
  majority[RCI(0,2,node_ct)] = 2;
  majority[RCI(3,4,node_ct)] = 3;
  majority[RCI(4,0,node_ct)] = 3;
  majority[RCI(4,1,node_ct)] = 2;
}

void set_majority_net_pentagon_6(int *majority, int node_ct)
{
  assert(5 <= node_ct);
  majority[RCI(0,1,node_ct)] = 2;
  majority[RCI(0,2,node_ct)] = 3;
  majority[RCI(0,3,node_ct)] = 3;
  majority[RCI(0,4,node_ct)] = 2;
  majority[RCI(1,2,node_ct)] = 3;
  majority[RCI(1,3,node_ct)] = 2;
  majority[RCI(1,4,node_ct)] = 3;
  majority[RCI(2,3,node_ct)] = 3;
  majority[RCI(2,4,node_ct)] = 1;
  majority[RCI(3,4,node_ct)] = 2;
}
