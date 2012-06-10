
AM_CPPFLAGS = -I$(srcdir)/../src
LDADD = $(top_builddir)/src/ctlparse/libctl.la

TESTS= 			\
  simple.test 	 	\
  medium.test 		\
  big.test 		\
  parse-ctl.test

EXTRA_DIST = $(TESTS) \
  cl3serv3.kripke

distclean-local:
	rm -rf $(TESTS:.test=.dir)

