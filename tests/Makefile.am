AUTOMAKE_OPTIONS = subdir-objects

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
	@LIBMDMP_DLL_IMPORT@

TESTS = \
	test_library.sh \
	test_tools.sh \
	test_mdmpinfo.sh

check_SCRIPTS = \
	test_library.sh \
	test_manpage.sh \
	test_mdmpinfo.sh \
	test_runner.sh \
	test_tools.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	mdmp_test_error \
	mdmp_test_file \
	mdmp_test_io_handle \
	mdmp_test_notify \
	mdmp_test_stream \
	mdmp_test_stream_descriptor \
	mdmp_test_stream_io_handle \
	mdmp_test_support \
	mdmp_test_tools_info_handle \
	mdmp_test_tools_output \
	mdmp_test_tools_signal

mdmp_test_error_SOURCES = \
	mdmp_test_error.c \
	mdmp_test_libmdmp.h \
	mdmp_test_macros.h \
	mdmp_test_unused.h

mdmp_test_error_LDADD = \
	../libmdmp/libmdmp.la

mdmp_test_file_SOURCES = \
	mdmp_test_file.c \
	mdmp_test_functions.c mdmp_test_functions.h \
	mdmp_test_getopt.c mdmp_test_getopt.h \
	mdmp_test_libbfio.h \
	mdmp_test_libcerror.h \
	mdmp_test_libclocale.h \
	mdmp_test_libcnotify.h \
	mdmp_test_libmdmp.h \
	mdmp_test_libuna.h \
	mdmp_test_macros.h \
	mdmp_test_memory.c mdmp_test_memory.h \
	mdmp_test_unused.h

mdmp_test_file_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libmdmp/libmdmp.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@PTHREAD_LIBADD@

mdmp_test_io_handle_SOURCES = \
	mdmp_test_io_handle.c \
	mdmp_test_libcerror.h \
	mdmp_test_libmdmp.h \
	mdmp_test_macros.h \
	mdmp_test_memory.c mdmp_test_memory.h \
	mdmp_test_unused.h

mdmp_test_io_handle_LDADD = \
	../libmdmp/libmdmp.la \
	@LIBCERROR_LIBADD@

mdmp_test_notify_SOURCES = \
	mdmp_test_libcerror.h \
	mdmp_test_libmdmp.h \
	mdmp_test_macros.h \
	mdmp_test_notify.c \
	mdmp_test_unused.h

mdmp_test_notify_LDADD = \
	../libmdmp/libmdmp.la \
	@LIBCERROR_LIBADD@

mdmp_test_stream_SOURCES = \
	mdmp_test_libcerror.h \
	mdmp_test_libmdmp.h \
	mdmp_test_macros.h \
	mdmp_test_memory.c mdmp_test_memory.h \
	mdmp_test_stream.c \
	mdmp_test_unused.h

mdmp_test_stream_LDADD = \
	../libmdmp/libmdmp.la \
	@LIBCERROR_LIBADD@

mdmp_test_stream_descriptor_SOURCES = \
	mdmp_test_libcerror.h \
	mdmp_test_libmdmp.h \
	mdmp_test_macros.h \
	mdmp_test_memory.c mdmp_test_memory.h \
	mdmp_test_stream_descriptor.c \
	mdmp_test_unused.h

mdmp_test_stream_descriptor_LDADD = \
	../libmdmp/libmdmp.la \
	@LIBCERROR_LIBADD@

mdmp_test_stream_io_handle_SOURCES = \
	mdmp_test_libcerror.h \
	mdmp_test_libmdmp.h \
	mdmp_test_macros.h \
	mdmp_test_memory.c mdmp_test_memory.h \
	mdmp_test_stream_io_handle.c \
	mdmp_test_unused.h

mdmp_test_stream_io_handle_LDADD = \
	../libmdmp/libmdmp.la \
	@LIBCERROR_LIBADD@

mdmp_test_support_SOURCES = \
	mdmp_test_functions.c mdmp_test_functions.h \
	mdmp_test_getopt.c mdmp_test_getopt.h \
	mdmp_test_libbfio.h \
	mdmp_test_libcerror.h \
	mdmp_test_libclocale.h \
	mdmp_test_libcnotify.h \
	mdmp_test_libmdmp.h \
	mdmp_test_libuna.h \
	mdmp_test_macros.h \
	mdmp_test_memory.c mdmp_test_memory.h \
	mdmp_test_support.c \
	mdmp_test_unused.h

mdmp_test_support_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libmdmp/libmdmp.la \
	@LIBCERROR_LIBADD@

mdmp_test_tools_info_handle_SOURCES = \
	../mdmptools/info_handle.c ../mdmptools/info_handle.h \
	../mdmptools/mdmpinput.c ../mdmptools/mdmpinput.h \
	mdmp_test_libcerror.h \
	mdmp_test_macros.h \
	mdmp_test_memory.c mdmp_test_memory.h \
	mdmp_test_tools_info_handle.c \
	mdmp_test_unused.h

mdmp_test_tools_info_handle_LDADD = \
	@LIBCLOCALE_LIBADD@ \
	../libmdmp/libmdmp.la \
	@LIBCERROR_LIBADD@

mdmp_test_tools_output_SOURCES = \
	../mdmptools/mdmptools_output.c ../mdmptools/mdmptools_output.h \
	mdmp_test_libcerror.h \
	mdmp_test_macros.h \
	mdmp_test_tools_output.c \
	mdmp_test_unused.h

mdmp_test_tools_output_LDADD = \
	../libmdmp/libmdmp.la \
	@LIBCERROR_LIBADD@

mdmp_test_tools_signal_SOURCES = \
	../mdmptools/mdmptools_signal.c ../mdmptools/mdmptools_signal.h \
	mdmp_test_libcerror.h \
	mdmp_test_macros.h \
	mdmp_test_tools_signal.c \
	mdmp_test_unused.h

mdmp_test_tools_signal_LDADD = \
	../libmdmp/libmdmp.la \
	@LIBCERROR_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

