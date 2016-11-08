AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
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
	test_api_types.sh \
	test_mdmpinfo.sh

check_SCRIPTS = \
	test_api_functions.sh \
	test_api_types.sh \
	test_mdmpinfo.sh \
	test_runner.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	mdmp_test_error \
	mdmp_test_file \
	mdmp_test_open_close \
	mdmp_test_support

mdmp_test_error_SOURCES = \
	mdmp_test_error.c \
	mdmp_test_libmdmp.h \
	mdmp_test_macros.h \
	mdmp_test_unused.h

mdmp_test_error_LDADD = \
	../libmdmp/libmdmp.la

mdmp_test_file_SOURCES = \
	mdmp_test_file.c \
	mdmp_test_libcerror.h \
	mdmp_test_libclocale.h \
	mdmp_test_libcsystem.h \
	mdmp_test_libmdmp.h \
	mdmp_test_libuna.h \
	mdmp_test_memory.c mdmp_test_memory.h \
	mdmp_test_unused.h

mdmp_test_file_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libmdmp/libmdmp.la \
	@LIBCERROR_LIBADD@

mdmp_test_open_close_SOURCES = \
	mdmp_test_libcerror.h \
	mdmp_test_libmdmp.h \
	mdmp_test_libcsystem.h \
	mdmp_test_open_close.c

mdmp_test_open_close_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	../libmdmp/libmdmp.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@
	@PTHREAD_LIBADD@

mdmp_test_support_SOURCES = \
	mdmp_test_libcerror.h \
	mdmp_test_libclocale.h \
	mdmp_test_libcsystem.h \
	mdmp_test_libmdmp.h \
	mdmp_test_libuna.h \
	mdmp_test_macros.h \
	mdmp_test_support.c \
	mdmp_test_unused.h

mdmp_test_support_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libmdmp/libmdmp.la \
	@LIBCERROR_LIBADD@


MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

