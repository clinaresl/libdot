dnl Process this file with autoconf to produce a configure script.

AC_INIT(parser.cc)
dnl Every other copy of the package version number gets its value from here
AM_INIT_AUTOMAKE(parser, 0.1.0)

dnl create a config.h file (Automake will add -DHAVE_CONFIG_H)
AM_CONFIG_HEADER(config.h)

AC_SUBST(VERSION)

ISODATE=`date +%Y-%m-%d`
AC_SUBST(ISODATE)

AC_CANONICAL_HOST

dnl Checks for programs.
AC_PROG_INSTALL
AC_PROG_CC
AC_PROG_CXX

# Get the dot parser include location
AC_ARG_WITH([dot-include-path],
  [AS_HELP_STRING([--with-dot-include-path],
    [location of the dot parser headers, defaults to /usr/local/include/libdot-0.0])],
  [DOT_CFLAGS="-I$withval"],
  [DOT_CFLAGS="-I/usr/local/include/libdot-0.0"])
AC_SUBST([DOT_CFLAGS])

# Get the dot parser library location
AC_ARG_WITH([dot-lib-path],
  [AS_HELP_STRING([--with-dot-lib-path], 
    [location of the dot parser library, defaults to /usr/local/lib])],
  [DOT_LIBS="-L$withval -ldot-0.0"],
  [DOT_LIBS='-L/usr/local/lib -ldot-0.0'])
AC_SUBST([DOT_LIBS])

dnl Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS(unistd.h sys/param.h sys/time.h time.h sys/mkdev.h sys/sysmacros.h string.h memory.h fcntl.h dirent.h sys/ndir.h ndir.h alloca.h locale.h )

jm_CHECK_TYPE_STRUCT_UTIMBUF
AC_HEADER_MAJOR
AC_FUNC_ALLOCA
AC_STRUCT_TM
AC_STRUCT_ST_BLOCKS
AC_FUNC_CLOSEDIR_VOID
AC_CHECK_FUNCS(mkfifo)
AC_CHECK_FUNC(mknod)

dnl Checks for typedefs, structures, and compiler characteristics.

dnl Checks for library functions.

AC_OUTPUT(Makefile parser.lsm parser.spec)
