include $(top_srcdir)/build-aux/make/init.mk

AM_CPPFLAGS += -I$(srcdir)
AM_LDFLAGS += -lbdd

SUBDIRS = kripkeparse ctlparse


bin_PROGRAMS += ../gyver

___gyver_SOURCES = main.cc verification/verification.cc parseKripke.cc

LDADD += $(top_builddir)/src/kripkeparse/libkripke.la \
	 $(top_builddir)/src/ctlparse/libctl.la

___gyverdir= $(includedir)/src
___gyver_HEADERS =                                       \
  kripkeparse/driver.hh                                 \
  parseKripke.hh                                        \
  ctlparse/ctl-public.hh                                \
  ctlparse/ctl.hh                                       \
  verification/verification.hh
