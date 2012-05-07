
AM_CPPFLAGS = -I$(srcdir)/../src
LDADD = $(top_builddir)/src/ctlparse/libctl.la \
  $(top_builddir)/src/kripkeparse/libkripke.la

parse_ctl_SOURCES =			\
  parse-ctl.cc

parse_kripke_SOURCES =			\
  parse-kripke.cc

check_PROGRAMS =			\
  parse_ctl				\
  parse_kripke

TESTS =					\
  parse-ctl.test			\
  parse-kripke.test

EXTRA_DIST = $(TESTS)

distclean-local:
	rm -rf $(TESTS:.test=.dir)

