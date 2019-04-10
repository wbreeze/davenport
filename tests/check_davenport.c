#include <cutter.h>
#include <stdlib.h>
#include "../src/davenport.h"

void test_davenport_create(void);
void test_davenport_create(void)
{
  Davenport *d;

  d = davenport_create();
  cut_assert(d != NULL);
  davenport_free(d);
}
