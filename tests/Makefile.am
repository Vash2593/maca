
AM_CPPFLAGS = -I$(srcdir)/../src
LDADD = $(top_builddir)/src/ctlparse/libctl.la

TESTS= \
  simple.test \
  medium.test \
  parse-ctl.test

EXTRA_DIST = $(TESTS)

distclean-local:
	rm -rf $(TESTS:.test=.dir)

