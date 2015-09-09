AM_CPPFLAGS = @VMOD_INCLUDES@ -Wall -Werror
AUTOMAKE_OPTIONS = subdir-objects

vmoddir = @VMOD_DIR@
vmod_LTLIBRARIES = libvmod_shards.la

libvmod_shards_la_LDFLAGS = -module -export-dynamic -avoid-version -shared

libvmod_shards_la_SOURCES = \
	vmod_shards.c \
	murmur3/murmur3.c

nodist_libvmod_shards_la_SOURCES = \
	vcc_if.c \
	vcc_if.h

vmod_shards.lo: vcc_if.c vcc_if.h

vcc_if.c: vcc_if.h

vcc_if.h: @VMODTOOL@ $(top_srcdir)/src/vmod_shards.vcc
	@VMODTOOL@ $(top_srcdir)/src/vmod_shards.vcc

VMOD_TESTS = $(top_srcdir)/src/tests/*.vtc
.PHONY: $(VMOD_TESTS)

$(top_srcdir)/src/tests/*.vtc: libvmod_shards.la
	@VARNISHTEST@ -Dvarnishd=@VARNISHD@ -Dvmod_topbuild=$(abs_top_builddir) $@

check: $(VMOD_TESTS)

EXTRA_DIST = \
	vmod_shards.vcc \
	$(VMOD_TESTS)

CLEANFILES = \
	$(builddir)/vcc_if.c \
	$(builddir)/vcc_if.h \
	$(builddir)/vmod_shards.rst \
	$(builddir)/vmod_shards.man.rst
