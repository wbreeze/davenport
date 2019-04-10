if WITH_CUTTER
  TESTS = run-tests.sh
  TESTS_ENVIRONMENT = IS_MAKE_TEST=yes CUTTER="$(CUTTER)"
  noinst_LTLIBRARIES = libtest_davenport.la
  libtest_davenport_la_SOURCES = \
    test_davenport.c \
    test_preflow_push.c
endif

AM_CPPFLAGS = $(CUTTER_CFLAGS) -I$(top_srcdir)/src
AM_LDFLAGS = -module -avoid-version -no-undefined
AM_LIBS = $(CUTTER_LIBS) $(top_builddir)/src/libdavenport.la
