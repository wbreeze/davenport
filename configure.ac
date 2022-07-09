#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([Davenport],[0.1.1],[https://github.com/wbreeze/davenport/issues])
AC_CONFIG_MACRO_DIRS([m4])
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_MAKE_SET

# Checks for libraries.
LT_INIT

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memset strcspn strdup strpbrk strspn])

AM_INIT_AUTOMAKE

AC_CONFIG_FILES([Makefile
                 cmdline/Makefile
                 src/Makefile
                 test/Makefile])

AC_OUTPUT
