#include <assert.h>
#include <stdlib.h>
#include "test_helper.h"
#include "../src/network.h"

NetworkScratchSpace *network_scratch_space_new(int node_ct)
{
  NetworkScratchSpace *network = malloc(sizeof(NetworkScratchSpace));
  network->node_ct = node_ct;
  network->excess = node_array_calloc(node_ct);
  network->labels = node_array_calloc(node_ct);
  network->seen = node_array_calloc(node_ct);
  network->node_scratch = node_array_calloc(node_ct);
  network->capacity = edge_array_calloc(node_ct);
  network->flow = edge_array_calloc(node_ct);
  network->edge_scratch = edge_array_calloc(node_ct);
  return network;
}

void network_scratch_space_free(NetworkScratchSpace *network)
{
  free(network->excess);
  free(network->labels);
  free(network->seen);
  free(network->node_scratch);
  free(network->capacity);
  free(network->flow);
  free(network->edge_scratch);
  free(network);
}

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

void set_majority_net_one_cycle_embedded(int *majority, int node_ct)
{
  assert(5 <= node_ct);
  majority[RCI(0,1,node_ct)] = 2;
  majority[RCI(1,2,node_ct)] = 1;
  majority[RCI(2,3,node_ct)] = 2;
  majority[RCI(3,1,node_ct)] = 1;
  majority[RCI(3,4,node_ct)] = 2;
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
