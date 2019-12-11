/*
 * Library stream type test program
 *
 * Copyright (C) 2014-2019, Joachim Metz <joachim.metz@gmail.com>
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
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "mdmp_test_libcerror.h"
#include "mdmp_test_libmdmp.h"
#include "mdmp_test_macros.h"
#include "mdmp_test_memory.h"
#include "mdmp_test_unused.h"

#include "../libmdmp/libmdmp_stream.h"

/* Tests the libmdmp_stream_free function
 * Returns 1 if successful or 0 if not
 */
int mdmp_test_stream_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libmdmp_stream_free(
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

#if defined( __GNUC__ ) && !defined( LIBMDMP_DLL_IMPORT )

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

	/* TODO: add tests for libmdmp_stream_initialize */

#endif /* defined( __GNUC__ ) && !defined( LIBMDMP_DLL_IMPORT ) */

	MDMP_TEST_RUN(
	 "libmdmp_stream_free",
	 mdmp_test_stream_free );

#if defined( __GNUC__ ) && !defined( LIBMDMP_DLL_IMPORT )

	/* TODO: add tests for libmdmp_stream_get_type */

	/* TODO: add tests for libmdmp_stream_read_buffer */

	/* TODO: add tests for libmdmp_stream_read_buffer_at_offset */

	/* TODO: add tests for libmdmp_stream_seek_offset */

	/* TODO: add tests for libmdmp_stream_get_offset */

	/* TODO: add tests for libmdmp_stream_get_size */

	/* TODO: add tests for libmdmp_stream_get_start_offset */

	/* TODO: add tests for libmdmp_stream_get_data_file_io_handle */

#endif /* defined( __GNUC__ ) && !defined( LIBMDMP_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

