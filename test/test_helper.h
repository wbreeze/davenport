#ifndef TEST_HELPER_H
#define TEST_HELPER_H

#include <string.h>
#include "test_helper_nets.h"
#include "test_helper_pentagons.h"

#define assert_equal_int_array(expected, have, length) \
  cut_assert_equal_memory( \
    expected, (length) * sizeof(int), have, (length) * sizeof(int) \
  )

#define copy_int_array(dest, src, count) \
  memcpy(dest, src, (count) * sizeof(int))
#define clear_int_array(array, count) \
  memset(array, 0, (count) * sizeof(int))
#define set_int_array(array, value, count) \
  for(int i = 0; i < count; ++i) array[i] = value;

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

#endif
