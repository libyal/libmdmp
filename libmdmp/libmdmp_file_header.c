/*
 * File header functions
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
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libmdmp_debug.h"
#include "libmdmp_file_header.h"
#include "libmdmp_io_handle.h"
#include "libmdmp_libcerror.h"
#include "libmdmp_libcnotify.h"
#include "libmdmp_libfdatetime.h"

#include "mdmp_file_header.h"

/* Creates file header
 * Make sure the value file_header is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libmdmp_file_header_initialize(
     libmdmp_file_header_t **file_header,
     libcerror_error_t **error )
{
	static char *function = "libmdmp_file_header_initialize";

	if( file_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file header.",
		 function );

		return( -1 );
	}
	if( *file_header != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file header value already set.",
		 function );

		return( -1 );
	}
	*file_header = memory_allocate_structure(
	                libmdmp_file_header_t );

	if( *file_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create file header.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *file_header,
	     0,
	     sizeof( libmdmp_file_header_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear file header.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *file_header != NULL )
	{
		memory_free(
		 *file_header );

		*file_header = NULL;
	}
	return( -1 );
}

/* Frees file header
 * Returns 1 if successful or -1 on error
 */
int libmdmp_file_header_free(
     libmdmp_file_header_t **file_header,
     libcerror_error_t **error )
{
	static char *function = "libmdmp_file_header_free";

	if( file_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file header.",
		 function );

		return( -1 );
	}
	if( *file_header != NULL )
	{
		memory_free(
		 *file_header );

		*file_header = NULL;
	}
	return( 1 );
}

/* Reads the file header data
 * Returns 1 if successful or -1 on error
 */
int libmdmp_file_header_read_data(
     libmdmp_file_header_t *file_header,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function = "libmdmp_file_header_read_data";

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit  = 0;
	uint16_t value_16bit  = 0;
#endif

	if( file_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file header.",
		 function );

		return( -1 );
	}
	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data.",
		 function );

		return( -1 );
	}
	if( ( data_size < sizeof( mdmp_file_header_t ) )
	 || ( data_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data size value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: file header data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 sizeof( mdmp_file_header_t ),
		 0 );
	}
#endif
	if( memory_compare(
	     ( (mdmp_file_header_t *) data )->signature,
	     mdmp_file_signature,
	     4 ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid signature.",
		 function );

		return( -1 );
	}
	byte_stream_copy_to_uint16_little_endian(
	 ( (mdmp_file_header_t *) data )->version,
	 file_header->version );

	byte_stream_copy_to_uint32_little_endian(
	 ( (mdmp_file_header_t *) data )->number_of_streams,
	 file_header->number_of_streams );

	byte_stream_copy_to_uint32_little_endian(
	 ( (mdmp_file_header_t *) data )->streams_directory_rva,
	 file_header->streams_directory_offset );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: signature\t\t\t\t: %c%c%c%c\n",
		 function,
		 ( (mdmp_file_header_t *) data )->signature[ 0 ],
		 ( (mdmp_file_header_t *) data )->signature[ 1 ],
		 ( (mdmp_file_header_t *) data )->signature[ 2 ],
		 ( (mdmp_file_header_t *) data )->signature[ 3 ] );

		libcnotify_printf(
		 "%s: version\t\t\t\t: 0x%04" PRIx16 "\n",
		 function,
		 file_header->version );

		byte_stream_copy_to_uint16_little_endian(
		 ( (mdmp_file_header_t *) data )->implementation_version,
		 value_16bit );
		libcnotify_printf(
		 "%s: implementation version\t\t: 0x%04" PRIx16 "\n",
		 function,
		 value_16bit );

		libcnotify_printf(
		 "%s: number of streams\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 file_header->number_of_streams );

		libcnotify_printf(
		 "%s: streams directory RVA\t\t: 0x%08" PRIx32 "\n",
		 function,
		 file_header->streams_directory_offset );

		byte_stream_copy_to_uint32_little_endian(
		 ( (mdmp_file_header_t *) data )->checksum,
		 value_32bit );
		libcnotify_printf(
		 "%s: checksum\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

/* TODO print date time value */
		byte_stream_copy_to_uint32_little_endian(
		 ( (mdmp_file_header_t *) data )->timestamp,
		 value_32bit );
		libcnotify_printf(
		 "%s: timestamp\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (mdmp_file_header_t *) data )->file_flags,
		 value_32bit );
		libcnotify_printf(
		 "%s: file flags\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );
		libmdmp_debug_print_file_flags(
		 value_32bit );
		libcnotify_printf(
		 "\n" );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	return( 1 );
}

/* Reads the file header
 * Returns 1 if successful or -1 on error
 */
int libmdmp_file_header_read_file_io_handle(
     libmdmp_file_header_t *file_header,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	uint8_t file_header_data[ sizeof( mdmp_file_header_t ) ];

	static char *function = "libmdmp_file_header_read_file_io_handle";
	ssize_t read_count    = 0;

	if( file_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file header.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading file header at offset: 0 (0x00000000)\n",
		 function );
	}
#endif
	read_count = libbfio_handle_read_buffer_at_offset(
	              file_io_handle,
	              file_header_data,
	              sizeof( mdmp_file_header_t ),
	              0,
	              error );

	if( read_count != (ssize_t) sizeof( mdmp_file_header_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read file header data at offset: 0 (0x00000000).",
		 function );

		return( -1 );
	}
	if( libmdmp_file_header_read_data(
	     file_header,
	     file_header_data,
	     sizeof( mdmp_file_header_t ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read file header.",
		 function );

		return( -1 );
	}
	return( 1 );
}

