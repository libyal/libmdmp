/*
 * Input/Output (IO) handle functions
 *
 * Copyright (C) 2014, Joachim Metz <joachim.metz@gmail.com>
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
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libmdmp_debug.h"
#include "libmdmp_definitions.h"
#include "libmdmp_io_handle.h"
#include "libmdmp_libbfio.h"
#include "libmdmp_libcerror.h"
#include "libmdmp_libcnotify.h"
#include "libmdmp_stream_descriptor.h"
#include "libmdmp_unused.h"

#include "mdmp_file_header.h"

const char *mdmp_file_signature = "MDMP";

const uint8_t empty_streams_directory_entry[ 12 ] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

/* Creates an IO handle
 * Make sure the value io_handle is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libmdmp_io_handle_initialize(
     libmdmp_io_handle_t **io_handle,
     libcerror_error_t **error )
{
	static char *function = "libmdmp_io_handle_initialize";

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( *io_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid IO handle value already set.",
		 function );

		return( -1 );
	}
	*io_handle = memory_allocate_structure(
	              libmdmp_io_handle_t );

	if( *io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create IO handle.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *io_handle,
	     0,
	     sizeof( libmdmp_io_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear file.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *io_handle != NULL )
	{
		memory_free(
		 *io_handle );

		*io_handle = NULL;
	}
	return( -1 );
}

/* Frees a IO handle
 * Returns 1 if successful or -1 on error
 */
int libmdmp_io_handle_free(
     libmdmp_io_handle_t **io_handle,
     libcerror_error_t **error )
{
	static char *function = "libmdmp_io_handle_free";

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( *io_handle != NULL )
	{
		memory_free(
		 *io_handle );

		*io_handle = NULL;
	}
	return( 1 );
}

/* Clears the IO handle
 * Returns 1 if successful or -1 on error
 */
int libmdmp_io_handle_clear(
     libmdmp_io_handle_t *io_handle,
     libcerror_error_t **error )
{
	static char *function = "libmdmp_io_handle_clear";

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( memory_set(
	     io_handle,
	     0,
	     sizeof( libmdmp_io_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear IO handle.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Reads the file header
 * Returns 1 if successful or -1 on error
 */
int libmdmp_io_handle_read_file_header(
     libmdmp_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint32_t *streams_directory_offset,
     uint32_t *number_of_streams,
     libcerror_error_t **error )
{
	mdmp_file_header_t file_header;

	static char *function = "libmdmp_io_handle_read_file_header";
	ssize_t read_count    = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit  = 0;
	uint16_t value_16bit  = 0;
#endif

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( streams_directory_offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid streams directory offset.",
		 function );

		return( -1 );
	}
	if( number_of_streams == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid number of streams.",
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
	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     0,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek file header offset: 0.",
		 function );

		return( -1 );
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              (uint8_t *) &file_header,
	              sizeof( mdmp_file_header_t ),
	              error );

	if( read_count != (ssize_t) sizeof( mdmp_file_header_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read file header data.",
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
		 (uint8_t *) &file_header,
		 sizeof( mdmp_file_header_t ),
		 0 );
	}
#endif
	if( memory_compare(
	     file_header.signature,
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
	 file_header.version,
	 io_handle->version );

	byte_stream_copy_to_uint32_little_endian(
	 file_header.number_of_streams,
	 *number_of_streams );

	byte_stream_copy_to_uint32_little_endian(
	 file_header.streams_directory_rva,
	 *streams_directory_offset );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: signature\t\t\t\t: %c%c%c%c\n",
		 function,
		 file_header.signature[ 0 ],
		 file_header.signature[ 1 ],
		 file_header.signature[ 2 ],
		 file_header.signature[ 3 ] );

		libcnotify_printf(
		 "%s: version\t\t\t\t: 0x%04" PRIx16 "\n",
		 function,
		 io_handle->version );

		byte_stream_copy_to_uint16_little_endian(
		 file_header.implementation_version,
		 value_16bit );
		libcnotify_printf(
		 "%s: implementation version\t\t: 0x%04" PRIx16 "\n",
		 function,
		 value_16bit );

		libcnotify_printf(
		 "%s: number of streams\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 *number_of_streams );

		libcnotify_printf(
		 "%s: streams directory RVA\t\t: 0x%08" PRIx32 "\n",
		 function,
		 *streams_directory_offset );

		byte_stream_copy_to_uint32_little_endian(
		 file_header.checksum,
		 value_32bit );
		libcnotify_printf(
		 "%s: checksum\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

/* TODO print date time value */
		byte_stream_copy_to_uint32_little_endian(
		 file_header.timestamp,
		 value_32bit );
		libcnotify_printf(
		 "%s: timestamp\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 file_header.file_flags,
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
#endif
	return( 1 );
}

/* Reads the streams directory
 * Returns 1 if successful or -1 on error
 */
int libmdmp_io_handle_read_streams_directory(
     libmdmp_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint32_t streams_directory_offset,
     uint32_t number_of_streams,
     libcdata_array_t *streams_array,
     libcerror_error_t **error )
{
	libmdmp_stream_descriptor_t *stream_descriptor = NULL;
	uint8_t *streams_directory_data                = NULL;
	uint8_t *streams_directory_entry_data          = NULL;
	static char *function                          = "libmdmp_io_handle_read_streams_directory";
	size_t streams_directory_data_size             = 0;
	ssize_t read_count                             = 0;
	uint32_t stream_data_offset                    = 0;
	uint32_t stream_data_size                      = 0;
	uint32_t stream_index                          = 0;
	int entry_index                                = 0;
	int result                                     = 0;

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading streams directory at offset: %" PRIu32 " (0x%08" PRIx32 ")\n",
		 function,
		 streams_directory_offset,
		 streams_directory_offset );
	}
#endif
	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     streams_directory_offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek streams directory offset: %" PRIu32 " (0x%08" PRIx32 ").",
		 function );

		goto on_error;
	}
	streams_directory_data_size = sizeof( mdmp_streams_directory_entry_t )
	                            * number_of_streams;

	if( streams_directory_data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid streams directory data size value out of bounds.",
		 function );

		goto on_error;
	}
	streams_directory_data = (uint8_t *) memory_allocate(
	                                      sizeof( uint8_t ) * streams_directory_data_size );

	if( streams_directory_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create streams directory data.",
		 function );

		goto on_error;
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              streams_directory_data,
	              streams_directory_data_size,
	              error );

	if( read_count != (ssize_t) streams_directory_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read streams directory data.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: streams directory data:\n",
		 function );
		libcnotify_print_data(
		 streams_directory_data,
		 streams_directory_data_size,
		 0 );
	}
#endif
	streams_directory_entry_data = streams_directory_data;

	for( stream_index = 0;
	     stream_index < number_of_streams;
	     stream_index++ )
	{
		if( stream_descriptor == NULL )
		{
			if( libmdmp_stream_descriptor_initialize(
			     &stream_descriptor,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
				 "%s: unable to create stream descriptor.",
				 function );

				goto on_error;
			}
		}
		byte_stream_copy_to_uint32_little_endian(
		 ( (mdmp_streams_directory_entry_t *) streams_directory_entry_data )->stream_type,
		 stream_descriptor->type );

		byte_stream_copy_to_uint32_little_endian(
		 ( (mdmp_streams_directory_entry_t *) streams_directory_entry_data )->stream_data_size,
		 stream_data_size );

		byte_stream_copy_to_uint32_little_endian(
		 ( (mdmp_streams_directory_entry_t *) streams_directory_entry_data )->stream_data_rva,
		 stream_data_offset );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: stream: %02" PRIu32 " type\t\t: %" PRIu32 " (%s)\n",
			 function,
			 stream_index,
			 stream_descriptor->type,
			 libmdmp_debug_get_stream_type(
			  stream_descriptor->type ) );

			libcnotify_printf(
			 "%s: stream: %02" PRIu32 " data size\t\t: %" PRIu32 "\n",
			 function,
			 stream_index,
			 stream_data_size );

			libcnotify_printf(
			 "%s: stream: %02" PRIu32 " RVA\t\t: 0x%08" PRIx32 "\n",
			 function,
			 stream_index,
			 stream_data_offset );
		}
#endif
		result = memory_compare(
		          streams_directory_entry_data,
		          empty_streams_directory_entry,
		          sizeof( mdmp_streams_directory_entry_t ) );

		streams_directory_entry_data += sizeof( mdmp_streams_directory_entry_t );

		if( result != 0 )
		{
			if( libmdmp_stream_descriptor_set_data_range(
			     stream_descriptor,
			     (off64_t) stream_data_offset,
			     (size64_t) stream_data_size,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
				 "%s: unable to set data range in stream descriptor.",
				 function );

				goto on_error;
			}
			if( libcdata_array_append_entry(
			     streams_array,
			     &entry_index,
			     (intptr_t *) stream_descriptor,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
				 "%s: unable to append stream descriptor to sections array.",
				 function );

				goto on_error;
			}
			stream_descriptor = NULL;
		}
	}
	if( stream_descriptor != NULL )
	{
		if( libmdmp_stream_descriptor_free(
		     &stream_descriptor,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free stream descriptor.",
			 function );

			goto on_error;
		}
	}
	memory_free(
	 streams_directory_data );

	return( 1 );

on_error:
	if( stream_descriptor != NULL )
	{
		libmdmp_stream_descriptor_free(
		 &stream_descriptor,
		 NULL );
	}
	if( streams_directory_data != NULL )
	{
		memory_free(
		 streams_directory_data );
	}
	return( -1 );
}

/* Reads the segment data into the buffer
 * Callback function for the section stream
 * Returns the number of bytes read or -1 on error
 */
ssize_t libmdmp_io_handle_read_segment_data(
         intptr_t *data_handle LIBMDMP_ATTRIBUTE_UNUSED,
         libbfio_handle_t *file_io_handle,
         int segment_index LIBMDMP_ATTRIBUTE_UNUSED,
         int segment_file_index LIBMDMP_ATTRIBUTE_UNUSED,
         uint8_t *segment_data,
         size_t segment_data_size,
         uint32_t segment_flags LIBMDMP_ATTRIBUTE_UNUSED,
         uint8_t read_flags LIBMDMP_ATTRIBUTE_UNUSED,
         libcerror_error_t **error )
{
	static char *function = "libmdmp_io_handle_read_segment_data";
	ssize_t read_count    = 0;

	LIBMDMP_UNREFERENCED_PARAMETER( data_handle )
	LIBMDMP_UNREFERENCED_PARAMETER( segment_index )
	LIBMDMP_UNREFERENCED_PARAMETER( segment_file_index )
	LIBMDMP_UNREFERENCED_PARAMETER( segment_flags )
	LIBMDMP_UNREFERENCED_PARAMETER( read_flags )

	read_count = libbfio_handle_read_buffer(
		      file_io_handle,
		      segment_data,
		      segment_data_size,
		      error );

	if( read_count != (ssize_t) segment_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read segment data.",
		 function );

		return( -1 );
	}
	return( read_count );
}

/* Seeks a certain segment offset
 * Callback function for the section stream
 * Returns the offset or -1 on error
 */
off64_t libmdmp_io_handle_seek_segment_offset(
         intptr_t *data_handle LIBMDMP_ATTRIBUTE_UNUSED,
         libbfio_handle_t *file_io_handle,
         int segment_index LIBMDMP_ATTRIBUTE_UNUSED,
         int segment_file_index LIBMDMP_ATTRIBUTE_UNUSED,
         off64_t segment_offset,
         libcerror_error_t **error )
{
	static char *function = "libmdmp_io_handle_seek_segment_offset";

	LIBMDMP_UNREFERENCED_PARAMETER( data_handle )
	LIBMDMP_UNREFERENCED_PARAMETER( segment_index )
	LIBMDMP_UNREFERENCED_PARAMETER( segment_file_index )

	segment_offset = libbfio_handle_seek_offset(
	                  file_io_handle,
	                  segment_offset,
	                  SEEK_SET,
	                  error );

	if( segment_offset == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to seek segment offset.",
		 function );

		return( -1 );
	}
	return( segment_offset );
}

