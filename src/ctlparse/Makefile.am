include $(top_srcdir)/build-aux/make/init.mk

AM_CPPFLAGS += -I$(srcdir)/..
AM_LDFLAGS += -lbdd

BISONXX = $(top_builddir)/build-aux/bin/bison++
BISONXX_IN = $(top_srcdir)/build-aux/bin/bison++.in
$(BISONXX): $(BISONXX_IN)
	cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) build-aux/bin/bison++

BISONXXFLAGS =					\
  $(if $(V:0=),--verbose)
AM_BISONFLAGS =					\
  -Wall -Werror --report=all

SOURCES_PARSE_CTL =				\
  position.hh					\
  location.hh					\
  stack.hh					\
  ctl.hh					\
  ctl.cc

BUILT_SOURCES +=				\
  $(SOURCES_PARSE_CTL)

EXTRA_DIST +=					\
  ctl.yy					\
  ctl-public.hh					\
  ctl.stamp

ctl.stamp: ctl.yy $(BISONXX_IN)
	$(AM_V_GEN)mkdir -p $(@D)
	$(AM_V_at)rm -f $@ $@.tmp
	$(AM_V_at)echo '$@ rebuilt because of: $?' >$@.tmp
	$(AM_V_at)$(MAKE) $(BISONXX)
	$(AM_V_at)$(BISONXX) $(BISONXXFLAGS) --	\
	  $< $(srcdir)/ctl.cc		\
	  $(AM_BISONFLAGS) $(BISONFLAGS)
	$(AM_V_at)mv -f $@.tmp $@
$(addprefix $(srcdir)/, $(SOURCES_PARSE_CTL)): ctl.stamp
	@if test -f $@; then :; else		\
	  rm -f $<;				\
	  $(MAKE) $(AM_MAKEFLAGS) $<;		\
	fi




pkglib_LTLIBRARIES = libctl.la
libctl_la_SOURCES = 				\
  $(SOURCES_PARSE_CTL)			\
  ctl-lexer.ll


MAINTAINERCLEANFILES +=				\
  ctl.dir					\
  ctl.stamp					\
  ctl.hh.bak					\
  location.hh.bak				\
  position.hh.bak				\
  stack.hh.bak					\
  position.hh					\
  stack.hh					\
  ctl.output					\
  ctl.xml					\
  ctl.html
CLEANFILES =					\
  ctl.dir
