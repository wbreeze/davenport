#include <assert.h>
#include "../src/network.h"

void set_majority_net_no_cycles(int *majority, int node_ct)
{
  assert(4 <= node_ct);
  majority[RCI(0,1,node_ct)] = 2;
  majority[RCI(0,2,node_ct)] = 3;
  majority[RCI(0,3,node_ct)] = 3;
  majority[RCI(1,2,node_ct)] = 2;
  majority[RCI(1,3,node_ct)] = 1;
  majority[RCI(2,3,node_ct)] = 3;
}

void set_majority_net_partial_no_cycles(int *majority, int node_ct)
{
  assert(4 <= node_ct);
  majority[RCI(0,1,node_ct)] = 2;
  majority[RCI(0,2,node_ct)] = 3;
  majority[RCI(0,3,node_ct)] = 3;
  majority[RCI(1,3,node_ct)] = 1;
  majority[RCI(2,3,node_ct)] = 3;
}

void set_majority_net_one_cycle_embedded(int *majority, int node_ct)
{
  assert(5 <= node_ct);
  majority[RCI(0,1,node_ct)] = 2;
  majority[RCI(1,2,node_ct)] = 1;
  majority[RCI(2,3,node_ct)] = 2;
  majority[RCI(3,1,node_ct)] = 1;
  majority[RCI(3,4,node_ct)] = 2;

  majority[RCI(0,4,node_ct)] = 2;
  majority[RCI(0,2,node_ct)] = 2;
  majority[RCI(0,3,node_ct)] = 2;
  majority[RCI(1,4,node_ct)] = 2;
  majority[RCI(2,4,node_ct)] = 2;
}

void set_majority_net_multi_cycle_embedded(int *majority, int node_ct)
{
  assert(8 <= node_ct);
  majority[RCI(0,1,node_ct)] = 6;
  majority[RCI(1,2,node_ct)] = 4;
  majority[RCI(2,4,node_ct)] = 2;
  majority[RCI(3,1,node_ct)] = 2;
  majority[RCI(3,2,node_ct)] = 3;
  majority[RCI(4,3,node_ct)] = 1;
  majority[RCI(4,5,node_ct)] = 2;
  majority[RCI(4,6,node_ct)] = 1;
  majority[RCI(5,3,node_ct)] = 3;
  majority[RCI(5,6,node_ct)] = 4;
  majority[RCI(6,7,node_ct)] = 4;


  majority[RCI(0,2,node_ct)] = 6;
  majority[RCI(0,3,node_ct)] = 6;
  majority[RCI(0,4,node_ct)] = 6;
  majority[RCI(0,5,node_ct)] = 6;
  majority[RCI(0,6,node_ct)] = 6;
  majority[RCI(0,7,node_ct)] = 6;
  majority[RCI(1,4,node_ct)] = 6;
  majority[RCI(1,5,node_ct)] = 6;
  majority[RCI(1,6,node_ct)] = 6;
  majority[RCI(1,7,node_ct)] = 6;
  majority[RCI(2,5,node_ct)] = 6;
  majority[RCI(2,6,node_ct)] = 6;
  majority[RCI(2,7,node_ct)] = 6;
  majority[RCI(3,6,node_ct)] = 6;
  majority[RCI(3,7,node_ct)] = 6;
  majority[RCI(4,7,node_ct)] = 6;
  majority[RCI(5,7,node_ct)] = 6;
}

void set_majority_net_two_embedded_cycles(int *majority, int node_ct)
{
  assert(8 <= node_ct);
  majority[RCI(0,1,node_ct)] = 2;
  majority[RCI(1,2,node_ct)] = 1;
  majority[RCI(2,3,node_ct)] = 2;
  majority[RCI(3,1,node_ct)] = 1;
  majority[RCI(3,4,node_ct)] = 2;
  majority[RCI(4,5,node_ct)] = 1;
  majority[RCI(5,6,node_ct)] = 1;
  majority[RCI(6,4,node_ct)] = 2;
  majority[RCI(6,7,node_ct)] = 2;
}

void set_majority_tarjan_example(int *majority, int node_ct)
{
  assert(8 <= node_ct);
  majority[RCI(0,1,node_ct)] = 1;
  majority[RCI(1,2,node_ct)] = 1;
  majority[RCI(2,0,node_ct)] = 1;
  majority[RCI(3,1,node_ct)] = 1;
  majority[RCI(3,2,node_ct)] = 1;
  majority[RCI(3,5,node_ct)] = 1;
  majority[RCI(4,2,node_ct)] = 1;
  majority[RCI(4,6,node_ct)] = 1;
  majority[RCI(5,3,node_ct)] = 1;
  majority[RCI(5,4,node_ct)] = 1;
  majority[RCI(6,4,node_ct)] = 1;
  majority[RCI(7,5,node_ct)] = 1;
  majority[RCI(7,6,node_ct)] = 1;
  majority[RCI(7,7,node_ct)] = 1;
}
