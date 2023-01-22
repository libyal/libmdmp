/*
 * Library file type test program
 *
 * Copyright (C) 2014-2023, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <file_stream.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "mdmp_test_functions.h"
#include "mdmp_test_getopt.h"
#include "mdmp_test_libbfio.h"
#include "mdmp_test_libcerror.h"
#include "mdmp_test_libmdmp.h"
#include "mdmp_test_macros.h"
#include "mdmp_test_memory.h"
#include "mdmp_test_unused.h"

#include "../libmdmp/libmdmp_file.h"

#if !defined( LIBMDMP_HAVE_BFIO )

LIBMDMP_EXTERN \
int libmdmp_check_file_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

LIBMDMP_EXTERN \
int libmdmp_file_open_file_io_handle(
     libmdmp_file_t *file,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libmdmp_error_t **error );

#endif /* !defined( LIBMDMP_HAVE_BFIO ) */

#if defined( HAVE_WIDE_SYSTEM_CHARACTER ) && SIZEOF_WCHAR_T != 2 && SIZEOF_WCHAR_T != 4
#error Unsupported size of wchar_t
#endif

/* Define to make mdmp_test_file generate verbose output
#define MDMP_TEST_FILE_VERBOSE
 */

/* Creates and opens a source file
 * Returns 1 if successful or -1 on error
 */
int mdmp_test_file_open_source(
     libmdmp_file_t **file,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	static char *function = "mdmp_test_file_open_source";
	int result            = 0;

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file IO handle.",
		 function );

		return( -1 );
	}
	if( libmdmp_file_initialize(
	     file,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize file.",
		 function );

		goto on_error;
	}
	result = libmdmp_file_open_file_io_handle(
	          *file,
	          file_io_handle,
	          LIBMDMP_OPEN_READ,
	          error );

	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open file.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *file != NULL )
	{
		libmdmp_file_free(
		 file,
		 NULL );
	}
	return( -1 );
}

/* Closes and frees a source file
 * Returns 1 if successful or -1 on error
 */
int mdmp_test_file_close_source(
     libmdmp_file_t **file,
     libcerror_error_t **error )
{
	static char *function = "mdmp_test_file_close_source";
	int result            = 0;

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( libmdmp_file_close(
	     *file,
	     error ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close file.",
		 function );

		result = -1;
	}
	if( libmdmp_file_free(
	     file,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free file.",
		 function );

		result = -1;
	}
	return( result );
}

/* Tests the libmdmp_file_initialize function
 * Returns 1 if successful or 0 if not
 */
int mdmp_test_file_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libmdmp_file_t *file            = NULL;
	int result                      = 0;

#if defined( HAVE_MDMP_TEST_MEMORY )
	int number_of_malloc_fail_tests = 1;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libmdmp_file_initialize(
	          &file,
	          &error );

	MDMP_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MDMP_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	MDMP_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libmdmp_file_free(
	          &file,
	          &error );

	MDMP_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MDMP_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

	MDMP_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libmdmp_file_initialize(
	          NULL,
	          &error );

	MDMP_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MDMP_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	file = (libmdmp_file_t *) 0x12345678UL;

	result = libmdmp_file_initialize(
	          &file,
	          &error );

	MDMP_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MDMP_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	file = NULL;

#if defined( HAVE_MDMP_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libmdmp_file_initialize with malloc failing
		 */
		mdmp_test_malloc_attempts_before_fail = test_number;

		result = libmdmp_file_initialize(
		          &file,
		          &error );

		if( mdmp_test_malloc_attempts_before_fail != -1 )
		{
			mdmp_test_malloc_attempts_before_fail = -1;

			if( file != NULL )
			{
				libmdmp_file_free(
				 &file,
				 NULL );
			}
		}
		else
		{
			MDMP_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			MDMP_TEST_ASSERT_IS_NULL(
			 "file",
			 file );

			MDMP_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		/* Test libmdmp_file_initialize with memset failing
		 */
		mdmp_test_memset_attempts_before_fail = test_number;

		result = libmdmp_file_initialize(
		          &file,
		          &error );

		if( mdmp_test_memset_attempts_before_fail != -1 )
		{
			mdmp_test_memset_attempts_before_fail = -1;

			if( file != NULL )
			{
				libmdmp_file_free(
				 &file,
				 NULL );
			}
		}
		else
		{
			MDMP_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			MDMP_TEST_ASSERT_IS_NULL(
			 "file",
			 file );

			MDMP_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( HAVE_MDMP_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		libmdmp_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

/* Tests the libmdmp_file_free function
 * Returns 1 if successful or 0 if not
 */
int mdmp_test_file_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libmdmp_file_free(
	          NULL,
	          &error );

	MDMP_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MDMP_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libmdmp_file_open function
 * Returns 1 if successful or 0 if not
 */
int mdmp_test_file_open(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libcerror_error_t *error = NULL;
	libmdmp_file_t *file     = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = mdmp_test_get_narrow_source(
	          source,
	          narrow_source,
	          256,
	          &error );

	MDMP_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MDMP_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libmdmp_file_initialize(
	          &file,
	          &error );

	MDMP_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MDMP_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	MDMP_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libmdmp_file_open(
	          file,
	          narrow_source,
	          LIBMDMP_OPEN_READ,
	          &error );

	MDMP_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MDMP_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libmdmp_file_open(
	          NULL,
	          narrow_source,
	          LIBMDMP_OPEN_READ,
	          &error );

	MDMP_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MDMP_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libmdmp_file_open(
	          file,
	          NULL,
	          LIBMDMP_OPEN_READ,
	          &error );

	MDMP_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MDMP_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libmdmp_file_open(
	          file,
	          narrow_source,
	          -1,
	          &error );

	MDMP_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MDMP_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test open when already opened
	 */
	result = libmdmp_file_open(
	          file,
	          narrow_source,
	          LIBMDMP_OPEN_READ,
	          &error );

	MDMP_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MDMP_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libmdmp_file_free(
	          &file,
	          &error );

	MDMP_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MDMP_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

	MDMP_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		libmdmp_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the libmdmp_file_open_wide function
 * Returns 1 if successful or 0 if not
 */
int mdmp_test_file_open_wide(
     const system_character_t *source )
{
	wchar_t wide_source[ 256 ];

	libcerror_error_t *error = NULL;
	libmdmp_file_t *file     = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = mdmp_test_get_wide_source(
	          source,
	          wide_source,
	          256,
	          &error );

	MDMP_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MDMP_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libmdmp_file_initialize(
	          &file,
	          &error );

	MDMP_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MDMP_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	MDMP_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libmdmp_file_open_wide(
	          file,
	          wide_source,
	          LIBMDMP_OPEN_READ,
	          &error );

	MDMP_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MDMP_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libmdmp_file_open_wide(
	          NULL,
	          wide_source,
	          LIBMDMP_OPEN_READ,
	          &error );

	MDMP_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MDMP_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libmdmp_file_open_wide(
	          file,
	          NULL,
	          LIBMDMP_OPEN_READ,
	          &error );

	MDMP_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MDMP_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libmdmp_file_open_wide(
	          file,
	          wide_source,
	          -1,
	          &error );

	MDMP_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MDMP_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test open when already opened
	 */
	result = libmdmp_file_open_wide(
	          file,
	          wide_source,
	          LIBMDMP_OPEN_READ,
	          &error );

	MDMP_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MDMP_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libmdmp_file_free(
	          &file,
	          &error );

	MDMP_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MDMP_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

	MDMP_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		libmdmp_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Tests the libmdmp_file_open_file_io_handle function
 * Returns 1 if successful or 0 if not
 */
int mdmp_test_file_open_file_io_handle(
     const system_character_t *source )
{
	libbfio_handle_t *file_io_handle = NULL;
	libcerror_error_t *error         = NULL;
	libmdmp_file_t *file             = NULL;
	size_t string_length             = 0;
	int result                       = 0;

	/* Initialize test
	 */
	result = libbfio_file_initialize(
	          &file_io_handle,
	          &error );

	MDMP_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        MDMP_TEST_ASSERT_IS_NOT_NULL(
         "file_io_handle",
         file_io_handle );

        MDMP_TEST_ASSERT_IS_NULL(
         "error",
         error );

	string_length = system_string_length(
	                 source );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libbfio_file_set_name_wide(
	          file_io_handle,
	          source,
	          string_length,
	          &error );
#else
	result = libbfio_file_set_name(
	          file_io_handle,
	          source,
	          string_length,
	          &error );
#endif
	MDMP_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        MDMP_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libmdmp_file_initialize(
	          &file,
	          &error );

	MDMP_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MDMP_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	MDMP_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libmdmp_file_open_file_io_handle(
	          file,
	          file_io_handle,
	          LIBMDMP_OPEN_READ,
	          &error );

	MDMP_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MDMP_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libmdmp_file_open_file_io_handle(
	          NULL,
	          file_io_handle,
	          LIBMDMP_OPEN_READ,
	          &error );

	MDMP_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MDMP_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libmdmp_file_open_file_io_handle(
	          file,
	          NULL,
	          LIBMDMP_OPEN_READ,
	          &error );

	MDMP_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MDMP_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libmdmp_file_open_file_io_handle(
	          file,
	          file_io_handle,
	          -1,
	          &error );

	MDMP_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MDMP_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test open when already opened
	 */
	result = libmdmp_file_open_file_io_handle(
	          file,
	          file_io_handle,
	          LIBMDMP_OPEN_READ,
	          &error );

	MDMP_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MDMP_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libmdmp_file_free(
	          &file,
	          &error );

	MDMP_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MDMP_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

	MDMP_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_handle_free(
	          &file_io_handle,
	          &error );

	MDMP_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MDMP_TEST_ASSERT_IS_NULL(
         "file_io_handle",
         file_io_handle );

        MDMP_TEST_ASSERT_IS_NULL(
         "error",
         error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		libmdmp_file_free(
		 &file,
		 NULL );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libmdmp_file_close function
 * Returns 1 if successful or 0 if not
 */
int mdmp_test_file_close(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libmdmp_file_close(
	          NULL,
	          &error );

	MDMP_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MDMP_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libmdmp_file_open and libmdmp_file_close functions
 * Returns 1 if successful or 0 if not
 */
int mdmp_test_file_open_close(
     const system_character_t *source )
{
	libcerror_error_t *error = NULL;
	libmdmp_file_t *file     = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = libmdmp_file_initialize(
	          &file,
	          &error );

	MDMP_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MDMP_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	MDMP_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open and close
	 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libmdmp_file_open_wide(
	          file,
	          source,
	          LIBMDMP_OPEN_READ,
	          &error );
#else
	result = libmdmp_file_open(
	          file,
	          source,
	          LIBMDMP_OPEN_READ,
	          &error );
#endif

	MDMP_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MDMP_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libmdmp_file_close(
	          file,
	          &error );

	MDMP_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	MDMP_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open and close a second time to validate clean up on close
	 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libmdmp_file_open_wide(
	          file,
	          source,
	          LIBMDMP_OPEN_READ,
	          &error );
#else
	result = libmdmp_file_open(
	          file,
	          source,
	          LIBMDMP_OPEN_READ,
	          &error );
#endif

	MDMP_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MDMP_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libmdmp_file_close(
	          file,
	          &error );

	MDMP_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	MDMP_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Clean up
	 */
	result = libmdmp_file_free(
	          &file,
	          &error );

	MDMP_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MDMP_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

	MDMP_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		libmdmp_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

/* Tests the libmdmp_file_signal_abort function
 * Returns 1 if successful or 0 if not
 */
int mdmp_test_file_signal_abort(
     libmdmp_file_t *file )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libmdmp_file_signal_abort(
	          file,
	          &error );

	MDMP_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MDMP_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libmdmp_file_signal_abort(
	          NULL,
	          &error );

	MDMP_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MDMP_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libmdmp_file_get_number_of_streams function
 * Returns 1 if successful or 0 if not
 */
int mdmp_test_file_get_number_of_streams(
     libmdmp_file_t *file )
{
	libcerror_error_t *error     = NULL;
	int number_of_streams        = 0;
	int number_of_streams_is_set = 0;
	int result                   = 0;

	/* Test regular cases
	 */
	result = libmdmp_file_get_number_of_streams(
	          file,
	          &number_of_streams,
	          &error );

	MDMP_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MDMP_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	number_of_streams_is_set = result;

	/* Test error cases
	 */
	result = libmdmp_file_get_number_of_streams(
	          NULL,
	          &number_of_streams,
	          &error );

	MDMP_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MDMP_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	if( number_of_streams_is_set != 0 )
	{
		result = libmdmp_file_get_number_of_streams(
		          file,
		          NULL,
		          &error );

		MDMP_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		MDMP_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libmdmp_file_get_stream function
 * Returns 1 if successful or 0 if not
 */
int mdmp_test_file_get_stream(
     libmdmp_file_t *file )
{
	libcerror_error_t *error = NULL;
	libmdmp_stream_t *stream = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libmdmp_file_get_stream(
	          file,
	          0,
	          &stream,
	          &error );

	MDMP_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MDMP_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	MDMP_TEST_ASSERT_IS_NOT_NULL(
	 "stream",
	 stream );

	result = libmdmp_stream_free(
	          &stream,
	          &error );

	MDMP_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MDMP_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libmdmp_file_get_stream(
	          NULL,
	          0,
	          &stream,
	          &error );

	MDMP_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MDMP_TEST_ASSERT_IS_NULL(
	 "stream",
	 stream );

	MDMP_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libmdmp_file_get_stream(
	          file,
	          -1,
	          &stream,
	          &error );

	MDMP_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MDMP_TEST_ASSERT_IS_NULL(
	 "stream",
	 stream );

	MDMP_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libmdmp_file_get_stream(
	          file,
	          0,
	          NULL,
	          &error );

	MDMP_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MDMP_TEST_ASSERT_IS_NULL(
	 "stream",
	 stream );

	MDMP_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc,
     wchar_t * const argv[] )
#else
int main(
     int argc,
     char * const argv[] )
#endif
{
	libbfio_handle_t *file_io_handle = NULL;
	libcerror_error_t *error         = NULL;
	libmdmp_file_t *file             = NULL;
	system_character_t *source       = NULL;
	system_integer_t option          = 0;
	size_t string_length             = 0;
	int result                       = 0;

	while( ( option = mdmp_test_getopt(
	                   argc,
	                   argv,
	                   _SYSTEM_STRING( "" ) ) ) != (system_integer_t) -1 )
	{
		switch( option )
		{
			case (system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_SYSTEM ".\n",
				 argv[ optind - 1 ] );

				return( EXIT_FAILURE );
		}
	}
	if( optind < argc )
	{
		source = argv[ optind ];
	}
#if defined( HAVE_DEBUG_OUTPUT ) && defined( MDMP_TEST_FILE_VERBOSE )
	libmdmp_notify_set_verbose(
	 1 );
	libmdmp_notify_set_stream(
	 stderr,
	 NULL );
#endif

	MDMP_TEST_RUN(
	 "libmdmp_file_initialize",
	 mdmp_test_file_initialize );

	MDMP_TEST_RUN(
	 "libmdmp_file_free",
	 mdmp_test_file_free );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )
	if( source != NULL )
	{
		result = libbfio_file_initialize(
		          &file_io_handle,
		          &error );

		MDMP_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

	        MDMP_TEST_ASSERT_IS_NOT_NULL(
	         "file_io_handle",
	         file_io_handle );

	        MDMP_TEST_ASSERT_IS_NULL(
	         "error",
	         error );

		string_length = system_string_length(
		                 source );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libbfio_file_set_name_wide(
		          file_io_handle,
		          source,
		          string_length,
		          &error );
#else
		result = libbfio_file_set_name(
		          file_io_handle,
		          source,
		          string_length,
		          &error );
#endif
		MDMP_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

	        MDMP_TEST_ASSERT_IS_NULL(
	         "error",
	         error );

		result = libmdmp_check_file_signature_file_io_handle(
		          file_io_handle,
		          &error );

		MDMP_TEST_ASSERT_NOT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		MDMP_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	if( result != 0 )
	{
		MDMP_TEST_RUN_WITH_ARGS(
		 "libmdmp_file_open",
		 mdmp_test_file_open,
		 source );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

		MDMP_TEST_RUN_WITH_ARGS(
		 "libmdmp_file_open_wide",
		 mdmp_test_file_open_wide,
		 source );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

		MDMP_TEST_RUN_WITH_ARGS(
		 "libmdmp_file_open_file_io_handle",
		 mdmp_test_file_open_file_io_handle,
		 source );

		MDMP_TEST_RUN(
		 "libmdmp_file_close",
		 mdmp_test_file_close );

		MDMP_TEST_RUN_WITH_ARGS(
		 "libmdmp_file_open_close",
		 mdmp_test_file_open_close,
		 source );

		/* Initialize file for tests
		 */
		result = mdmp_test_file_open_source(
		          &file,
		          file_io_handle,
		          &error );

		MDMP_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		MDMP_TEST_ASSERT_IS_NOT_NULL(
		 "file",
		 file );

		MDMP_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		MDMP_TEST_RUN_WITH_ARGS(
		 "libmdmp_file_signal_abort",
		 mdmp_test_file_signal_abort,
		 file );

#if defined( __GNUC__ ) && !defined( LIBMDMP_DLL_IMPORT )

		/* TODO: add tests for libmdmp_file_open_read */

#endif /* defined( __GNUC__ ) && !defined( LIBMDMP_DLL_IMPORT ) */

		MDMP_TEST_RUN_WITH_ARGS(
		 "libmdmp_file_get_number_of_streams",
		 mdmp_test_file_get_number_of_streams,
		 file );

		MDMP_TEST_RUN_WITH_ARGS(
		 "libmdmp_file_get_stream",
		 mdmp_test_file_get_stream,
		 file );

		/* TODO: add tests for libmdmp_file_get_stream_by_type */

		/* Clean up
		 */
		result = mdmp_test_file_close_source(
		          &file,
		          &error );

		MDMP_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 0 );

		MDMP_TEST_ASSERT_IS_NULL(
		 "file",
		 file );

		MDMP_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	if( file_io_handle != NULL )
	{
		result = libbfio_handle_free(
		          &file_io_handle,
		          &error );

		MDMP_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		MDMP_TEST_ASSERT_IS_NULL(
	         "file_io_handle",
	         file_io_handle );

	        MDMP_TEST_ASSERT_IS_NULL(
	         "error",
	         error );
	}
#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */

	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		libmdmp_file_free(
		 &file,
		 NULL );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( EXIT_FAILURE );
}

