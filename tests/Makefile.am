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
	@LIBCSYSTEM_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBMDMP_DLL_IMPORT@

TESTS = \
	test_api_functions.sh \
	test_mdmpinfo.sh

check_SCRIPTS = \
	test_api_functions.sh \
	test_mdmpinfo.sh \
	test_runner.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	mdmp_test_get_version \
	mdmp_test_open_close

mdmp_test_get_version_SOURCES = \
	mdmp_test_get_version.c \
	mdmp_test_libcstring.h \
	mdmp_test_libmdmp.h \
	mdmp_test_unused.h

mdmp_test_get_version_LDADD = \
	../libmdmp/libmdmp.la \
	@LIBCSTRING_LIBADD@

mdmp_test_open_close_SOURCES = \
	mdmp_test_libcerror.h \
	mdmp_test_libmdmp.h \
	mdmp_test_libcstring.h \
	mdmp_test_libcsystem.h \
	mdmp_test_open_close.c

mdmp_test_open_close_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	../libmdmp/libmdmp.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@ \
	@PTHREAD_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

