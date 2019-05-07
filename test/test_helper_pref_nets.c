#include <assert.h>
#include "../src/network.h"

void set_preference_net_1(int *preference_graph, int node_ct)
{
  assert(5 <= node_ct);
  preference_graph[RCI(0,1,node_ct)] = 5;
  preference_graph[RCI(0,2,node_ct)] = 3;
  preference_graph[RCI(0,3,node_ct)] = 5;
  preference_graph[RCI(0,4,node_ct)] = 5;
  preference_graph[RCI(1,0,node_ct)] = 2;
  preference_graph[RCI(1,2,node_ct)] = 4;
  preference_graph[RCI(1,3,node_ct)] = 3;
  preference_graph[RCI(1,4,node_ct)] = 5;
  preference_graph[RCI(2,0,node_ct)] = 4;
  preference_graph[RCI(2,1,node_ct)] = 3;
  preference_graph[RCI(2,3,node_ct)] = 5;
  preference_graph[RCI(2,4,node_ct)] = 3;
  preference_graph[RCI(3,0,node_ct)] = 2;
  preference_graph[RCI(3,1,node_ct)] = 4;
  preference_graph[RCI(3,2,node_ct)] = 2;
  preference_graph[RCI(3,4,node_ct)] = 2;
  preference_graph[RCI(4,0,node_ct)] = 2;
  preference_graph[RCI(4,1,node_ct)] = 2;
  preference_graph[RCI(4,2,node_ct)] = 4;
  preference_graph[RCI(4,3,node_ct)] = 5;
}

