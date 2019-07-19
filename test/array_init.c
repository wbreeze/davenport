#include <stdarg.h>
#include "array_init.h"

void int_array_init(int *a, const int ct, ...) {
  va_list args;
  va_start(args, ct);
  for(int i = 0; i < ct; ++i) {
    a[i] = va_arg(args, int);
  }
  va_end(args);
}
