#ifndef TEST_HELPER_H
#define TEST_HELPER_H

#include <string.h>

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

#endif
