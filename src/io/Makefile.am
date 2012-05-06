include $(top_srcdir)/build-aux/make/init.mk

AM_CPPFLAGS += -I$(srcdir)/..

BISONXX = $(top_builddir)/build-aux/bin/bison++
BISONXX_IN = $(top_srcdir)/build-aux/bin/bison++.in
$(BISONXX): $(BISONXX_IN)
	cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) build-aux/bin/bison++

BISONXXFLAGS =					\
  $(if $(V:0=),--verbose)
AM_BISONFLAGS =					\
  -Wall -Werror --report=all

SOURCES_PARSE_KRIPKE =				\
  position.hh					\
  location.hh					\
  kripke.hh					\
  kripke.cc

SOURCES_PARSE_CTL =				\
  ctl.hh					\
  ctl.cc

BUILT_SOURCES += $(SOURCES_PARSE_KRIPKE) 	\
  $(SOURCES_PARSE_CTL)

EXTRA_DIST +=					\
  kripke.yy					\
  kripke.stamp					\
  ctl.yy					\
  ctl.stamp

kripke.stamp: kripke.yy $(BISONXX_IN)
	$(AM_V_GEN)mkdir -p $(@D)
	$(AM_V_at)rm -f $@ $@.tmp
	$(AM_V_at)echo '$@ rebuilt because of: $?' >$@.tmp
	$(AM_V_at)$(MAKE) $(BISONXX)
	$(AM_V_at)$(BISONXX) $(BISONXXFLAGS) --	\
	  $< $(srcdir)/kripke.cc		\
	  $(AM_BISONFLAGS) $(BISONFLAGS)
	$(AM_V_at)mv -f $@.tmp $@
$(addprefix $(srcdir)/, $(SOURCES_PARSE_KRIPKE)): kripke.stamp
	@if test -f $@; then :; else		\
	  rm -f $<;				\
	  $(MAKE) $(AM_MAKEFLAGS) $<;		\
	fi


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




pkglib_LTLIBRARIES = libkripke.la
libkripke_la_SOURCES = 				\
  $(SOURCES_PARSE_KRIPKE)			\
  kripke-lexer.ll


pkglib_LTLIBRARIES = libctl.la
libctl_la_SOURCES = 				\
  $(SOURCES_PARSE_CTL)				\
  ctl-lexer.ll



MAINTAINERCLEANFILES +=				\
  kripke.dir					\
  kripke.stamp					\
  kripke.hh.bak					\
  location.hh.bak				\
  position.hh.bak				\
  stack.hh.bak					\
  position.hh					\
  stack.hh					\
  kripke.output					\
  kripke.xml					\
  kripke.html
