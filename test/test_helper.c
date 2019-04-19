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
