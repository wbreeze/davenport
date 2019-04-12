#include <stdlib.h>
#include "check_davenport.h"
#include "../src/davenport.h"

START_TEST(check_davenport_create)
{
  Davenport *d;

  d = davenport_create();
  ck_assert(d != NULL);
  davenport_free(d);
}
END_TEST

Suite *make_davenport_suite(void)
{
  Suite *s;
  TCase *tc;

  s = suite_create("Davenport");
  tc = tcase_create("Core");

  suite_add_tcase (s, tc);
  tcase_add_test(tc, check_davenport_create);
  return s;
}

int main(void) {
  int number_failed;
  SRunner *sr;

  sr = srunner_create(make_davenport_suite());
  srunner_add_suite(sr, make_preflow_push_suite());
  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
