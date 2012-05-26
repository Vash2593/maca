include $(top_srcdir)/build-aux/make/init.mk

AM_CPPFLAGS += -I$(srcdir)
AM_LDFLAGS += -lbdd

SUBDIRS = kripkeparse ctlparse


bin_PROGRAMS += maca

maca_SOURCES = maca.cc verification/verification.cc

LDADD += $(top_builddir)/src/kripkeparse/libkripke.la
