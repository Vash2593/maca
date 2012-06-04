include $(top_srcdir)/build-aux/make/init.mk

AM_CPPFLAGS += -I$(srcdir)
AM_LDFLAGS += -lbdd

SUBDIRS = kripkeparse ctlparse


bin_PROGRAMS += maca

maca_SOURCES = main.cc verification/verification.cc parseKripke.cc

LDADD += $(top_builddir)/src/kripkeparse/libkripke.la \
	 $(top_builddir)/src/ctlparse/libctl.la

macadir= $(includedir)/src
maca_HEADERS =                                          \
  kripkeparse/kripke.hh                                 \
  kripkeparse/driver.hh                                 \
  parseKripke.hh                                        \
  ctlparse/ctl-public.hh                                \
  ctlparse/ctl.hh                                       \
  verification/verification.hh
