
AM_CPPFLAGS = -I$(srcdir)/../src
LDADD = $(top_builddir)/src/ctlparse/libctl.la

parse_ctl_SOURCES =			\
  parse-ctl.cc

check_PROGRAMS =			\
  parse_ctl

TESTS =					\
  parse-ctl.test

EXTRA_DIST = $(TESTS)

distclean-local:
	rm -rf $(TESTS:.test=.dir)

