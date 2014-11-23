AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
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
	@LIBCSYSTEM_CPPFLAGS@ \
	@LIBMDMP_DLL_IMPORT@

AM_LDFLAGS = @STATIC_LDFLAGS@

bin_PROGRAMS = \
	mdmpinfo

mdmpinfo_SOURCES = \
	info_handle.c info_handle.h \
	mdmpinfo.c \
	mdmpinput.c mdmpinput.h \
	mdmpoutput.c mdmpoutput.h \
	mdmptools_libbfio.h \
	mdmptools_libcerror.h \
	mdmptools_libclocale.h \
	mdmptools_libcnotify.h \
	mdmptools_libcstring.h \
	mdmptools_libcsystem.h \
	mdmptools_libfdatetime.h \
	mdmptools_libmdmp.h \
	mdmptools_libuna.h

mdmpinfo_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	../libmdmp/libmdmp.la \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@ \
	@LIBINTL@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on mdmpinfo ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(mdmpinfo_SOURCES)

