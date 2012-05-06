# -*- mode: autoconf -*-
AC_PREREQ([2.61])

AC_INIT([Fixme], [0.1], [moreira@lrde.epita.fr]) # FIXME: Define it when create the project
AC_CONFIG_AUX_DIR([build-aux]) # FIXME: add build-aux
AC_CONFIG_MACRO_DIR([build-aux/m4]) # FIXME: add build-aux

AM_INIT_AUTOMAKE([1.11 tar-ustar no-define foreign dist-xz
                  color-tests
                  parallel-tests nostdinc])

AM_SILENT_RULES([yes])

LT_PREREQ([2.2.6])
LT_INIT([pic-only shared disable-static])
AC_SUBST([LIBTOOL_DEPS])

## -------- ##
## C++ CODE ##
## -------- ##
AC_PROG_CXX

if test x$GXX = xyes; then
   case x`$CXX -dumpversion`x in
   xx|x2*|x3*|x4.[[0123456]]*)
     AC_MSG_ERROR([GNU g++ version 4.7 or later is required]);;
   *);;
   esac
fi

AC_LANG(C++)

AX_CHECK_COMPILE_FLAG([-std=c++11],
                      [stdfailed=false  CXXFLAGS="$CXXFLAGS -std=c++11"])
if "${stdfailed-true}"; then
  AX_CHECK_COMPILE_FLAG([-std=c++0x],
                        [stdfailed=false  CXXFLAGS="$CXXFLAGS -std=c++0x"])
fi
if "${stdfailed-true}"; then
  AC_ERROR([Unable to turn on C++11 mode with this compiler.])
fi

CF_GXX_WARNINGS

## -------------------- ##
## Auxiliary programs.  ##
## -------------------- ##

TC_PROG([flex], [>= 2.5.4], [FLEX], [Flex scanner generator])
AM_PROG_LEX
TC_PROG([bison], [>= 2.4], [BISON], [Bison parser generator])
AC_CONFIG_FILES([build-aux/bin/bison++], [chmod +x build-aux/bin/bison++])
AC_CONFIG_HEADERS([src/config.h:src/config.in.h])

## ------------------ ##
## Generated Makefile ##
## ------------------ ##
AC_CONFIG_FILES([
  Makefile
  src/Makefile
  src/kripkeparse/Makefile
  src/ctlparse/Makefile
  tests/Makefile
])

AC_OUTPUT
