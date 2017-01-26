/*
 * Library stream_io_handle type test program
 *
 * Copyright (C) 2014-2017, Joachim Metz <joachim.metz@gmail.com>
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

#include "../libmdmp/libmdmp_stream_io_handle.h"

#if defined( __GNUC__ )

/* Tests the libmdmp_stream_io_handle_free function
 * Returns 1 if successful or 0 if not
 */
int mdmp_test_stream_io_handle_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libmdmp_stream_io_handle_free(
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

#endif /* defined( __GNUC__ ) */

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

#if defined( __GNUC__ )

	/* TODO: add tests for libmdmp_stream_io_handle_initialize */

	MDMP_TEST_RUN(
	 "libmdmp_stream_io_handle_free",
	 mdmp_test_stream_io_handle_free );

	/* TODO: add tests for libmdmp_stream_io_handle_clone */

	/* TODO: add tests for libmdmp_stream_io_handle_read */

	/* TODO: add tests for libmdmp_stream_io_handle_write */

	/* TODO: add tests for libmdmp_stream_io_handle_seek_offset */

	/* TODO: add tests for libmdmp_stream_io_handle_exists */

	/* TODO: add tests for libmdmp_stream_io_handle_is_open */

	/* TODO: add tests for libmdmp_stream_io_handle_get_size */

#endif /* defined( __GNUC__ ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

