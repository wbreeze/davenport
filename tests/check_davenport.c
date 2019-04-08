#include <check.h>
#include "../src/davenport.h"

START_TEST(check_davenport_create)
{
  Davenport *d;

  d = davenport_create();
  ck_assert(d != NULL);
  davenport_free(d);
}
END_TEST

int main(void) {
  return 0;
}
