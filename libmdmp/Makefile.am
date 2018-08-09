AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCTHREADS_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBFCACHE_CPPFLAGS@ \
	@LIBFDATA_CPPFLAGS@ \
	@LIBFDATETIME_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBMDMP_DLL_EXPORT@

lib_LTLIBRARIES = libmdmp.la

libmdmp_la_SOURCES = \
	libmdmp.c \
	libmdmp_codepage.h \
	libmdmp_debug.c libmdmp_debug.h \
	libmdmp_definitions.h \
	libmdmp_error.c libmdmp_error.h \
	libmdmp_extern.h \
	libmdmp_file.c libmdmp_file.h \
	libmdmp_io_handle.c libmdmp_io_handle.h \
	libmdmp_libbfio.h \
	libmdmp_libcdata.h \
	libmdmp_libcerror.h \
	libmdmp_libclocale.h \
	libmdmp_libcnotify.h \
	libmdmp_libfdata.h \
	libmdmp_libfdatetime.h \
	libmdmp_libuna.h \
	libmdmp_notify.c libmdmp_notify.h \
	libmdmp_stream.c libmdmp_stream.h \
	libmdmp_stream_descriptor.c libmdmp_stream_descriptor.h \
	libmdmp_stream_io_handle.c libmdmp_stream_io_handle.h \
	libmdmp_support.c libmdmp_support.h \
	libmdmp_types.h \
	libmdmp_unused.h \
	mdmp_file_header.h

libmdmp_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	@LIBCTHREADS_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@LIBFCACHE_LIBADD@ \
	@LIBFDATA_LIBADD@ \
	@LIBFDATETIME_LIBADD@ \
	@PTHREAD_LIBADD@

libmdmp_la_LDFLAGS = -no-undefined -version-info 1:0:0

EXTRA_DIST = \
	libmdmp_definitions.h.in \
	libmdmp.rc \
	libmdmp.rc.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f libmdmp_definitions.h
	/bin/rm -f libmdmp.rc
	/bin/rm -f Makefile

splint:
	@echo "Running splint on libmdmp ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libmdmp_la_SOURCES)

