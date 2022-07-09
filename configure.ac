#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([Davenport],[0.1.1],[https://github.com/wbreeze/davenport/issues])
AC_CONFIG_SRCDIR([src, cmdline, test])
AC_CONFIG_MACRO_DIRS([m4])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AM_PROG_AR
LT_INIT

# Checks for programs.
AC_REQUIRE(AC_PROG_CC)
LT_INIT

# Checks for libraries
AC_CHECK_CUTTER

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_MALLOC

# Output files
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
  Makefile
  src/Makefile
  src/cmdline/Makefile
  test/Makefile
])
AC_OUTPUT
