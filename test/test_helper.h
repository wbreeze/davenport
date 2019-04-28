#ifndef TEST_HELPER_H
#define TEST_HELPER_H

#include <string.h>
#include "test_helper_pentagons.h"

#define assert_equal_int_array(expected, have, length) \
  cut_assert_equal_memory( \
    expected, (length) * sizeof(int), have, (length) * sizeof(int) \
  )

#define copy_int_array(dest, src, length) \
  memcpy(dest, src, (length) * sizeof(int))
#define clear_int_array(array, length) \
  memset(array, 0, (length) * sizeof(int))
#define set_int_array(array, value, length) \
  for(int i = 0; i < length; ++i) array[i] = value;

typedef struct {
  int node_ct;
  int *excess;
  int *labels;
  int *seen;
  int *node_scratch;
  int *flow;
  int *capacity;
  int *edge_scratch;
} NetworkScratchSpace;

NetworkScratchSpace *network_scratch_space_new(int node_ct);
void network_scratch_space_free(NetworkScratchSpace *network);

void set_majority_net_one_cycle_embedded(int *majority, int node_ct);
void set_majority_net_multi_cycle_embedded(int *majority, int node_ct);
void set_majority_net_two_embedded_cycles(int *majority, int node_ct);

#endif
