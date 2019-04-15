#ifndef CHECK_HELPER_H
#define CHECK_HELPER_H

#include <check.h>

#define check_assert_int_array_eq(expected, have, length) \
  ck_assert_mem_eq(expected, have, (length) * sizeof(int))

#define copy_int_array(dest, src, length) \
  memcpy(dest, src, (length) * sizeof(int))
#define clear_int_array(array, length) \
  memset(array, 0, (length) * sizeof(int))
#define set_int_array(array, value, length) \
  for(int i = 0; i < length; ++i) array[i] = value;

#endif
