/*
 * Library stream_descriptor type test program
 *
 * Copyright (C) 2014-2018, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <file_stream.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "mdmp_test_libcerror.h"
#include "mdmp_test_libmdmp.h"
#include "mdmp_test_macros.h"
#include "mdmp_test_memory.h"
#include "mdmp_test_unused.h"

#include "../libmdmp/libmdmp_stream_descriptor.h"

#if defined( __GNUC__ ) && !defined( LIBMDMP_DLL_IMPORT )

/* Tests the libmdmp_stream_descriptor_initialize function
 * Returns 1 if successful or 0 if not
 */
int mdmp_test_stream_descriptor_initialize(
     void )
{
	libcerror_error_t *error                       = NULL;
	libmdmp_stream_descriptor_t *stream_descriptor = NULL;
	int result                                     = 0;

#if defined( HAVE_MDMP_TEST_MEMORY )
	int number_of_malloc_fail_tests                = 1;
	int number_of_memset_fail_tests                = 1;
	int test_number                                = 0;
#endif

	/* Test regular cases
	 */
	result = libmdmp_stream_descriptor_initialize(
	          &stream_descriptor,
	          &error );

	MDMP_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MDMP_TEST_ASSERT_IS_NOT_NULL(
	 "stream_descriptor",
	 stream_descriptor );

	MDMP_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libmdmp_stream_descriptor_free(
	          &stream_descriptor,
	          &error );

	MDMP_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MDMP_TEST_ASSERT_IS_NULL(
	 "stream_descriptor",
	 stream_descriptor );

	MDMP_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libmdmp_stream_descriptor_initialize(
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

	stream_descriptor = (libmdmp_stream_descriptor_t *) 0x12345678UL;

	result = libmdmp_stream_descriptor_initialize(
	          &stream_descriptor,
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

	stream_descriptor = NULL;

#if defined( HAVE_MDMP_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libmdmp_stream_descriptor_initialize with malloc failing
		 */
		mdmp_test_malloc_attempts_before_fail = test_number;

		result = libmdmp_stream_descriptor_initialize(
		          &stream_descriptor,
		          &error );

		if( mdmp_test_malloc_attempts_before_fail != -1 )
		{
			mdmp_test_malloc_attempts_before_fail = -1;

			if( stream_descriptor != NULL )
			{
				libmdmp_stream_descriptor_free(
				 &stream_descriptor,
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
			 "stream_descriptor",
			 stream_descriptor );

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
		/* Test libmdmp_stream_descriptor_initialize with memset failing
		 */
		mdmp_test_memset_attempts_before_fail = test_number;

		result = libmdmp_stream_descriptor_initialize(
		          &stream_descriptor,
		          &error );

		if( mdmp_test_memset_attempts_before_fail != -1 )
		{
			mdmp_test_memset_attempts_before_fail = -1;

			if( stream_descriptor != NULL )
			{
				libmdmp_stream_descriptor_free(
				 &stream_descriptor,
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
			 "stream_descriptor",
			 stream_descriptor );

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
	if( stream_descriptor != NULL )
	{
		libmdmp_stream_descriptor_free(
		 &stream_descriptor,
		 NULL );
	}
	return( 0 );
}

/* Tests the libmdmp_stream_descriptor_free function
 * Returns 1 if successful or 0 if not
 */
int mdmp_test_stream_descriptor_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libmdmp_stream_descriptor_free(
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

#endif /* defined( __GNUC__ ) && !defined( LIBMDMP_DLL_IMPORT ) */

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc MDMP_TEST_ATTRIBUTE_UNUSED,
     wchar_t * const argv[] MDMP_TEST_ATTRIBUTE_UNUSED )
#else
int main(
     int argc MDMP_TEST_ATTRIBUTE_UNUSED,
     char * const argv[] MDMP_TEST_ATTRIBUTE_UNUSED )
#endif
{
	MDMP_TEST_UNREFERENCED_PARAMETER( argc )
	MDMP_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBMDMP_DLL_IMPORT )

	MDMP_TEST_RUN(
	 "libmdmp_stream_descriptor_initialize",
	 mdmp_test_stream_descriptor_initialize );

	MDMP_TEST_RUN(
	 "libmdmp_stream_descriptor_free",
	 mdmp_test_stream_descriptor_free );

	/* TODO: add tests for libmdmp_stream_descriptor_set_data_range */

#endif /* defined( __GNUC__ ) && !defined( LIBMDMP_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

