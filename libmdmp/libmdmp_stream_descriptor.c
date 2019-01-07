/*
 * Section decriptor functions
 *
 * Copyright (C) 2014-2019, Joachim Metz <joachim.metz@gmail.com>
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
#include <memory.h>
#include <types.h>

#include "libmdmp_io_handle.h"
#include "libmdmp_libcerror.h"
#include "libmdmp_libfdata.h"
#include "libmdmp_stream_descriptor.h"

/* Creates a stream descriptor
 * Make sure the value stream_descriptor is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libmdmp_stream_descriptor_initialize(
     libmdmp_stream_descriptor_t **stream_descriptor,
     libcerror_error_t **error )
{
	static char *function = "libmdmp_stream_descriptor_initialize";

	if( stream_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream descriptor.",
		 function );

		return( -1 );
	}
	if( *stream_descriptor != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid stream descriptor value already set.",
		 function );

		return( -1 );
	}
	*stream_descriptor = memory_allocate_structure(
	                      libmdmp_stream_descriptor_t );

	if( *stream_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create stream descriptor.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *stream_descriptor,
	     0,
	     sizeof( libmdmp_stream_descriptor_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear stream descriptor.",
		 function );

		memory_free(
		 *stream_descriptor );

		*stream_descriptor = NULL;

		return( -1 );
	}
	if( libfdata_stream_initialize(
	     &( ( *stream_descriptor )->data_stream ),
	     NULL,
	     NULL,
	     NULL,
	     NULL,
	     (ssize_t (*)(intptr_t *, intptr_t *, int, int, uint8_t *, size_t, uint32_t, uint8_t, libcerror_error_t **)) &libmdmp_io_handle_read_segment_data,
	     NULL,
	     (off64_t (*)(intptr_t *, intptr_t *, int, int, off64_t, libcerror_error_t **)) &libmdmp_io_handle_seek_segment_offset,
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create data stream.",
		 function );

		goto on_error;
	}
	if( libfdata_stream_resize(
	     ( *stream_descriptor )->data_stream,
	     1,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_RESIZE_FAILED,
		 "%s: unable to resize data stream.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *stream_descriptor != NULL )
	{
		if( ( *stream_descriptor )->data_stream != NULL )
		{
			libfdata_stream_free(
			 &( ( *stream_descriptor )->data_stream ),
			 NULL );
		}
		memory_free(
		 *stream_descriptor );

		*stream_descriptor = NULL;
	}
	return( -1 );
}

/* Frees a stream descriptor
 * Returns 1 if successful or -1 on error
 */
int libmdmp_stream_descriptor_free(
     libmdmp_stream_descriptor_t **stream_descriptor,
     libcerror_error_t **error )
{
	static char *function = "libmdmp_stream_descriptor_free";
	int result            = 1;

	if( stream_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream descriptor.",
		 function );

		return( -1 );
	}
	if( *stream_descriptor != NULL )
	{
		if( libfdata_stream_free(
		     &( ( *stream_descriptor )->data_stream ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free data stream.",
			 function );

			result = -1;
		}
		memory_free(
		 *stream_descriptor );

		*stream_descriptor = NULL;
	}
	return( result );
}

/* Sets the data range
 * Returns 1 if successful or -1 on error
 */
int libmdmp_stream_descriptor_set_data_range(
     libmdmp_stream_descriptor_t *stream_descriptor,
     off64_t data_offset,
     size64_t data_size,
     libcerror_error_t **error )
{
	static char *function = "libmdmp_stream_descriptor_set_data_range";

	if( stream_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream descriptor.",
		 function );

		return( -1 );
	}
	if( libfdata_stream_set_segment_by_index(
	     stream_descriptor->data_stream,
	     0,
	     0,
	     data_offset,
	     data_size,
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set segment in data stream.",
		 function );

		return( -1 );
	}
	return( 1 );
}

