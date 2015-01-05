/*
 * Section functions
 *
 * Copyright (C) 2014-2015, Joachim Metz <joachim.metz@gmail.com>
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

#include "libmdmp_definitions.h"
#include "libmdmp_io_handle.h"
#include "libmdmp_libbfio.h"
#include "libmdmp_libcerror.h"
#include "libmdmp_libfdata.h"
#include "libmdmp_libuna.h"
#include "libmdmp_stream.h"
#include "libmdmp_stream_io_handle.h"

/* Creates a stream
 * Make sure the value stream is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libmdmp_stream_initialize(
     libmdmp_stream_t **stream,
     libmdmp_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libmdmp_stream_descriptor_t *stream_descriptor,
     libcerror_error_t **error )
{
	libmdmp_internal_stream_t *internal_stream = NULL;
	static char *function                      = "libmdmp_stream_initialize";

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	if( *stream != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid stream value already set.",
		 function );

		return( -1 );
	}
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
	internal_stream = memory_allocate_structure(
	                   libmdmp_internal_stream_t );

	if( internal_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create internal stream.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_stream,
	     0,
	     sizeof( libmdmp_internal_stream_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear internal stream.",
		 function );

		memory_free(
		 internal_stream );

		return( -1 );
	}
	internal_stream->file_io_handle    = file_io_handle;
	internal_stream->io_handle         = io_handle;
	internal_stream->stream_descriptor = stream_descriptor;

	*stream = (libmdmp_stream_t *) internal_stream;

	return( 1 );

on_error:
	if( internal_stream != NULL )
	{
		memory_free(
		 internal_stream );
	}
	return( -1 );
}

/* Frees a stream
 * Returns 1 if successful or -1 on error
 */
int libmdmp_stream_free(
     libmdmp_stream_t **stream,
     libcerror_error_t **error )
{
	libmdmp_internal_stream_t *internal_stream = NULL;
	static char *function                      = "libmdmp_stream_free";

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	if( *stream != NULL )
	{
		internal_stream = (libmdmp_internal_stream_t *) *stream;
		*stream         = NULL;

		/* The file_io_handle, io_handle and stream_descriptor references are freed elsewhere
		 */
		memory_free(
		 internal_stream );
	}
	return( 1 );
}

/* Retrieves the type
 * Returns 1 if successful or -1 on error
 */
int libmdmp_stream_get_type(
     libmdmp_stream_t *stream,
     uint32_t *type,
     libcerror_error_t **error )
{
	libmdmp_internal_stream_t *internal_stream = NULL;
	static char *function                      = "libmdmp_stream_get_type";

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	internal_stream = (libmdmp_internal_stream_t *) stream;

	if( internal_stream->stream_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid internal stream - missing stream descriptor.",
		 function );

		return( -1 );
	}
	if( type == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid type.",
		 function );

		return( -1 );
	}
	*type = internal_stream->stream_descriptor->type;

	return( 1 );
}

/* Reads data at the current offset into a buffer
 * Returns the number of bytes read or -1 on error
 */
ssize_t libmdmp_stream_read_buffer(
         libmdmp_stream_t *stream,
         void *buffer,
         size_t buffer_size,
         libcerror_error_t **error )
{
	libmdmp_internal_stream_t *internal_stream = NULL;
	static char *function                      = "libmdmp_stream_read_buffer";
	ssize_t read_count                         = 0;

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	internal_stream = (libmdmp_internal_stream_t *) stream;

	if( internal_stream->stream_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid stream - missing stream descriptor.",
		 function );

		return( -1 );
	}
	read_count = libfdata_stream_read_buffer(
	              internal_stream->stream_descriptor->data_stream,
	              (intptr_t *) internal_stream->file_io_handle,
	              buffer,
	              buffer_size,
	              0,
	              error );

	if( read_count == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read buffer from stream data stream.",
		 function );

		return( -1 );
	}
	return( read_count );
}

/* Reads data at a specific offset into a buffer
 * Returns the number of bytes read or -1 on error
 */
ssize_t libmdmp_stream_read_buffer_at_offset(
         libmdmp_stream_t *stream,
         void *buffer,
         size_t buffer_size,
         off64_t offset,
         libcerror_error_t **error )
{
	static char *function = "libmdmp_stream_read_buffer_at_offset";
	ssize_t read_count    = 0;

	if( libmdmp_stream_seek_offset(
	     stream,
	     offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek offset.",
		 function );

		return( -1 );
	}
	read_count = libmdmp_stream_read_buffer(
	              stream,
	              buffer,
	              buffer_size,
	              error );

	if( read_count < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read buffer.",
		 function );

		return( -1 );
	}
	return( read_count );
}

/* Seeks a certain offset of the data
 * Returns the offset if seek is successful or -1 on error
 */
off64_t libmdmp_stream_seek_offset(
         libmdmp_stream_t *stream,
         off64_t offset,
         int whence,
         libcerror_error_t **error )
{
	libmdmp_internal_stream_t *internal_stream = NULL;
	static char *function                      = "libmdmp_stream_seek_offset";

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	internal_stream = (libmdmp_internal_stream_t *) stream;

	if( internal_stream->stream_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid stream - missing stream descriptor.",
		 function );

		return( -1 );
	}
	offset = libfdata_stream_seek_offset(
	          internal_stream->stream_descriptor->data_stream,
	          offset,
	          whence,
	          error );

	if( offset == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek in stream data stream.",
		 function );

		return( -1 );
	}
	return( offset );
}

/* Retrieves the (current) offset
 * Returns 1 if successful or -1 on error
 */
int libmdmp_stream_get_offset(
     libmdmp_stream_t *stream,
     off64_t *offset,
     libcerror_error_t **error )
{
	libmdmp_internal_stream_t *internal_stream = NULL;
	static char *function                      = "libmdmp_stream_get_offset";

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	internal_stream = (libmdmp_internal_stream_t *) stream;

	if( internal_stream->stream_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid stream - missing stream descriptor.",
		 function );

		return( -1 );
	}
	if( libfdata_stream_get_offset(
	     internal_stream->stream_descriptor->data_stream,
	     offset,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve stream data stream offset.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size
 * Returns 1 if successful or -1 on error
 */
int libmdmp_stream_get_size(
     libmdmp_stream_t *stream,
     size64_t *size,
     libcerror_error_t **error )
{
	libmdmp_internal_stream_t *internal_stream = NULL;
	static char *function                      = "libmdmp_stream_get_size";

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	internal_stream = (libmdmp_internal_stream_t *) stream;

	if( internal_stream->stream_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid stream - missing stream descriptor.",
		 function );

		return( -1 );
	}
	if( libfdata_stream_get_size(
	     internal_stream->stream_descriptor->data_stream,
	     size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve stream data stream size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the start offset
 * Returns 1 if successful or -1 on error
 */
int libmdmp_stream_get_start_offset(
     libmdmp_stream_t *stream,
     off64_t *start_offset,
     libcerror_error_t **error )
{
	libmdmp_internal_stream_t *internal_stream = NULL;
	static char *function                      = "libmdmp_stream_get_start_offset";
	size64_t segment_size                      = 0;
	uint32_t segment_flags                     = 0;
	int segment_file_index                     = 0;

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	internal_stream = (libmdmp_internal_stream_t *) stream;

	if( internal_stream->stream_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid internal stream - missing stream descriptor.",
		 function );

		return( -1 );
	}
	if( libfdata_stream_get_segment_by_index(
	     internal_stream->stream_descriptor->data_stream,
	     0,
	     &segment_file_index,
	     start_offset,
	     &segment_size,
	     &segment_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve stream data stream segment: 0.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the stream data file IO handle
 * Returns 1 if successful -1 on error
 */
int libmdmp_stream_get_data_file_io_handle(
     libmdmp_stream_t *stream,
     libbfio_handle_t **file_io_handle,
     libcerror_error_t **error )
{
	libmdmp_stream_io_handle_t *io_handle = NULL;
	static char *function                 = "libmdmp_stream_get_data_file_io_handle";

	if( libmdmp_stream_io_handle_initialize(
	     &io_handle,
	     stream,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create stream file IO handle.",
		 function );

		goto on_error;
	}
	if( libbfio_handle_initialize(
	     file_io_handle,
	     (intptr_t *) io_handle,
	     (int (*)(intptr_t **, libcerror_error_t **)) libmdmp_stream_io_handle_free,
	     (int (*)(intptr_t **, intptr_t *, libcerror_error_t **)) libmdmp_stream_io_handle_clone,
	     (int (*)(intptr_t *, int flags, libcerror_error_t **)) libmdmp_stream_io_handle_open,
	     (int (*)(intptr_t *, libcerror_error_t **)) libmdmp_stream_io_handle_close,
	     (ssize_t (*)(intptr_t *, uint8_t *, size_t, libcerror_error_t **)) libmdmp_stream_io_handle_read,
	     (ssize_t (*)(intptr_t *, const uint8_t *, size_t, libcerror_error_t **)) libmdmp_stream_io_handle_write,
	     (off64_t (*)(intptr_t *, off64_t, int, libcerror_error_t **)) libmdmp_stream_io_handle_seek_offset,
	     (int (*)(intptr_t *, libcerror_error_t **)) libmdmp_stream_io_handle_exists,
	     (int (*)(intptr_t *, libcerror_error_t **)) libmdmp_stream_io_handle_is_open,
	     (int (*)(intptr_t *, size64_t *, libcerror_error_t **)) libmdmp_stream_io_handle_get_size,
	     LIBBFIO_FLAG_IO_HANDLE_MANAGED | LIBBFIO_FLAG_IO_HANDLE_CLONE_BY_FUNCTION,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create file IO handle.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( io_handle != NULL )
	{
		libmdmp_stream_io_handle_free(
		 &io_handle,
		 NULL );
	}
	return( -1 );
}

