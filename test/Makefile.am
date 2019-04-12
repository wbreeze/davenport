if WITH_CUTTER
  TESTS = run-tests.sh
  TESTS_ENVIRONMENT = IS_MAKE_TEST=yes CUTTER="$(CUTTER)"
  noinst_LTLIBRARIES = test_davenport.la
  test_davenport_la_SOURCES = \
    test_davenport.c \
    test_preflow_push.c test_preflow_push.h
  test_davenport_la_LIBADD = $(top_builddir)/src/libdavenport.la
  AM_LIBS = $(CUTTER_LIBS) $(top_builddir)/src/libdavenport.la
  AM_CFLAGS = $(CUTTER_CFLAGS) -I$(top_srcdir)/src
  AM_LDFLAGS = -module -avoid-version -no-undefined
endif
