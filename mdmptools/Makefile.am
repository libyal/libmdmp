AM_CPPFLAGS = \
	-I../include -I$(top_srcdir)/include \
	-I../common -I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBFDATETIME_CPPFLAGS@ \
	@LIBMDMP_DLL_IMPORT@

AM_LDFLAGS = @STATIC_LDFLAGS@

bin_PROGRAMS = \
	mdmpinfo

mdmpinfo_SOURCES = \
	info_handle.c info_handle.h \
	mdmpinfo.c \
	mdmpinput.c mdmpinput.h \
	mdmptools_getopt.c mdmptools_getopt.h \
	mdmptools_i18n.h \
	mdmptools_libbfio.h \
	mdmptools_libcerror.h \
	mdmptools_libclocale.h \
	mdmptools_libcnotify.h \
	mdmptools_libmdmp.h \
	mdmptools_libuna.h \
	mdmptools_signal.c mdmptools_signal.h \
	mdmptools_output.c mdmptools_output.h \
	mdmptools_unused.h

mdmpinfo_LDADD = \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	../libmdmp/libmdmp.la \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

DISTCLEANFILES = \
	Makefile \
	Makefile.in

splint-local:
	@echo "Running splint on mdmpinfo ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(mdmpinfo_SOURCES)

