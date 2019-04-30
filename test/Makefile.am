TESTS = run_test.sh
TESTS_ENVIRONMENT = NO_MAKE=yes CUTTER="$(CUTTER)"

noinst_LTLIBRARIES = test_davenport.la

test_davenport_la_CPPFLAGS = $(CUTTER_CFLAGS) -I $(top_srcdir)/src

LIBS = $(CUTTER_LIBS) $(top_builddir)/src/libdavenport.la

AM_LDFLAGS = -module -rpath $(libdir) -avoid-version -no-undefined

test_davenport_la_SOURCES = \
  test_helper.c \
  test_helper_nets.c \
  test_helper_pentagons.c \
  test_davenport.c \
  test_dv_init_elist.c \
  test_dv_init_solution.c \
  test_dv_solution_set.c \
  test_lower_bound.c \
  test_network.c \
  test_preflow_discharge.c \
  test_preflow_list_mgr.c \
  test_preflow_max_flow.c \
  test_preflow_multilayer_flow.c \
  test_preflow_push.c \
  test_preflow_reduced_flow.c \
  test_preflow_relabel.c \
  test_preflow_saturate.c \
  test_ranking.c \
  test_sort_edges.c \
  test_sort_nodes.c \
  test_tarjan.c \
  test_tarjan_impl.c \
  test_transitive_net.c

test_davenport_la_LIBADD = $(top_builddir)/src/libdavenport.la

#config.status: error: in `/Users/dcl/Documents/p.temp/stack':
#config.status: error: Something went wrong bootstrapping makefile fragments
#    for automatic dependency tracking.  Try re-running configure with the
#    '--disable-dependency-tracking' option to at least be able to build
#    the package (albeit without support for automatic dependency tracking).
#See `config.log' for more details
#echo-cutter:
#        @echo $(CUTTER)
