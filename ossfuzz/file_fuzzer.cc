/*
 * OSS-Fuzz target for libmdmp file type
 *
 * Copyright (C) 2014-2026, Joachim Metz <joachim.metz@gmail.com>
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

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

/* Note that some of the OSS-Fuzz engines use C++
 */
extern "C" {

#include "ossfuzz_libbfio.h"
#include "ossfuzz_libmdmp.h"

#if !defined( LIBMDMP_HAVE_BFIO )

/* Determines if a file contains a MDMP file signature using a Basic File IO (bfio) handle
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBMDMP_EXTERN \
int libmdmp_check_file_signature_file_io_handle(
      libbfio_handle_t *file_io_handle,
      libmdmp_error_t **error );

/* Opens a file using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
LIBMDMP_EXTERN \
int libmdmp_file_open_file_io_handle(
      libmdmp_file_t *file,
      libbfio_handle_t *file_io_handle,
      int access_flags,
      libmdmp_error_t **error );

/* Retrieves the stream data file io handle
 * Returns 1 if successful -1 on error
 */
LIBMDMP_EXTERN \
int libmdmp_stream_get_data_file_io_handle(
      libmdmp_stream_t *stream,
      libbfio_handle_t **file_io_handle,
      libmdmp_error_t **error );

#endif /* !defined( LIBMDMP_HAVE_BFIO ) */

/* The maximum number of streams to exercise per input,
 * to bound the execution time
 */
#define MAXIMUM_NUMBER_OF_STREAMS	10

/* The size of the read buffer used to exercise the streams
 */
#define READ_BUFFER_SIZE		4096

/* Exercises the stream functions
 */
static void fuzz_stream(
          libmdmp_stream_t *stream,
          size_t size )
{
	uint8_t read_buffer[ READ_BUFFER_SIZE ];

	libbfio_handle_t *stream_file_io_handle = NULL;
	size64_t stream_file_io_handle_size     = 0;
	size64_t stream_size                    = 0;
	uint32_t stream_type                    = 0;
	off64_t stream_offset                   = 0;
	int result                              = 0;

	libmdmp_stream_get_type(
	 stream,
	 &stream_type,
	 NULL );

	libmdmp_stream_get_size(
	 stream,
	 &stream_size,
	 NULL );

	libmdmp_stream_get_offset(
	 stream,
	 &stream_offset,
	 NULL );

	libmdmp_stream_get_start_offset(
	 stream,
	 &stream_offset,
	 NULL );

	libmdmp_stream_read_buffer(
	 stream,
	 read_buffer,
	 READ_BUFFER_SIZE,
	 NULL );

	libmdmp_stream_get_offset(
	 stream,
	 &stream_offset,
	 NULL );

	libmdmp_stream_seek_offset(
	 stream,
	 0,
	 SEEK_SET,
	 NULL );

	libmdmp_stream_seek_offset(
	 stream,
	 1,
	 SEEK_CUR,
	 NULL );

	libmdmp_stream_seek_offset(
	 stream,
	 0,
	 SEEK_END,
	 NULL );

	libmdmp_stream_read_buffer_at_offset(
	 stream,
	 read_buffer,
	 READ_BUFFER_SIZE,
	 ( off64_t ) ( size + 1 ),
	 NULL );

	result = libmdmp_stream_get_data_file_io_handle(
	         stream,
	         &stream_file_io_handle,
	         NULL );

	if( ( result == 1 )
	 && ( stream_file_io_handle != NULL ) )
	{
		libbfio_handle_exists(
		 stream_file_io_handle,
		 NULL );

		libbfio_handle_get_size(
		 stream_file_io_handle,
		 &stream_file_io_handle_size,
		 NULL );

		libbfio_handle_seek_offset(
		 stream_file_io_handle,
		 0,
		 SEEK_SET,
		 NULL );

		libbfio_handle_seek_offset(
		 stream_file_io_handle,
		 1,
		 SEEK_CUR,
		 NULL );

		libbfio_handle_seek_offset(
		 stream_file_io_handle,
		 0,
		 SEEK_END,
		 NULL );

		libbfio_handle_read_buffer(
		 stream_file_io_handle,
		 read_buffer,
		 READ_BUFFER_SIZE,
		 NULL );

		libbfio_handle_read_buffer_at_offset(
		 stream_file_io_handle,
		 read_buffer,
		 READ_BUFFER_SIZE,
		 ( off64_t ) ( size + 1 ),
		 NULL );

		libbfio_handle_write_buffer_at_offset(
		 stream_file_io_handle,
		 read_buffer,
		 READ_BUFFER_SIZE,
		 0,
		 NULL );

		libbfio_handle_free(
		 &stream_file_io_handle,
		 NULL );
	}
}

/* Exercises the file functions
 */
void fuzz_file(
      libmdmp_file_t *file,
      size_t size )
{
	uint8_t read_buffer[ 128 ];

	static const uint32_t requested_stream_types[ 8 ] = {
		0x00000003,  /* Thread list stream */
		0x00000004,  /* Exception stream */
		0x00000006,  /* System process info stream */
		0x00000007,  /* Thread contexts stream */
		0x00010000,  /* Module list stream */
		0x00100002,  /* Memory 64 list stream */
		0x00100003,  /* Memory ranges list stream */
		0xffffffff
	};
	libmdmp_stream_t *stream        = NULL;
	ssize_t read_count              = 0;
	int number_of_streams           = 0;
	int maximum_number_of_streams   = MAXIMUM_NUMBER_OF_STREAMS;
	int requested_stream_type_index = 0;
	int stream_index                = 0;

	libmdmp_file_get_number_of_streams(
	 file,
	 &number_of_streams,
	 NULL );

	if( number_of_streams > maximum_number_of_streams )
	{
		number_of_streams = maximum_number_of_streams;
	}
	for( stream_index = 0;
	     stream_index < number_of_streams;
	     stream_index++ )
	{
		stream = NULL;

		if( libmdmp_file_get_stream(
		     file,
		     stream_index,
		     &stream,
		     NULL ) != 1 )
		{
			break;
		}
		fuzz_stream(
		 stream,
		 size );

		if( stream != NULL )
		{
			libmdmp_stream_free(
			 &stream,
			 NULL );
		}
	}
	libmdmp_file_signal_abort(
	 file,
	 NULL );

	for( requested_stream_type_index = 0;
	     requested_stream_type_index < (int) ( sizeof( requested_stream_types ) / sizeof( uint32_t ) );
	     requested_stream_type_index++ )
	{
		stream = NULL;
		read_count = 0;

		/* The return value can be 1 if a stream was found,
		 * 0 if no such stream or -1 on error
		 */
		if( libmdmp_file_get_stream_by_type(
		     file,
		     requested_stream_types[ requested_stream_type_index ],
		     &stream,
		     NULL ) != 1 )
		{
			continue;
		}
		if( stream != NULL )
		{
			read_count = libmdmp_stream_read_buffer(
			              stream,
			              read_buffer,
			              sizeof( read_buffer ),
			              NULL );

			if( read_count > 0 )
			{
				/* Prevent the buffer from being flagged as unused
				 */
				( void ) read_buffer[ 0 ];
			}
			libmdmp_stream_free(
			 &stream,
			 NULL );
		}
	}
}

int LLVMFuzzerTestOneInput(
      const uint8_t *data,
      size_t size )
{
	libbfio_handle_t *file_io_handle = NULL;
	libmdmp_file_t *file             = NULL;
	libmdmp_error_t *error           = NULL;
	char error_string[ 257 ];
	int codepage                     = 0;

	libmdmp_notify_set_verbose(
	 0 );

	libmdmp_get_version();

	libmdmp_get_access_flags_read();

	libmdmp_set_codepage(
	 1252,
	 NULL );

	libmdmp_get_codepage(
	 &codepage,
	 NULL );

	libmdmp_set_codepage(
	 0,
	 NULL );

	if( libbfio_memory_range_initialize(
	     &file_io_handle,
	     NULL ) != 1 )
	{
		return( 0 );
	}
	if( libbfio_memory_range_set(
	     file_io_handle,
	     (uint8_t *) data,
	     size,
	     NULL ) != 1 )
	{
		goto on_error_libbfio;
	}
	libmdmp_check_file_signature_file_io_handle(
	 file_io_handle,
	 NULL );

	if( libmdmp_file_initialize(
	     &file,
	     NULL ) != 1 )
	{
		goto on_error_libbfio;
	}
	if( libmdmp_file_open_file_io_handle(
	     file,
	     file_io_handle,
	     LIBMDMP_OPEN_READ,
	     &error ) != 1 )
	{
		libmdmp_error_sprint(
		 error,
		 error_string,
		 sizeof( error_string ) );

		libmdmp_error_backtrace_sprint(
		 error,
		 error_string,
		 sizeof( error_string ) );

		libmdmp_error_fprint(
		 error,
		 NULL );

		libmdmp_error_backtrace_fprint(
		 error,
		 NULL );

		libmdmp_error_free(
		 &error );

		goto on_error_libmdmp;
	}
	fuzz_file(
	 file,
	 size );

	libmdmp_file_close(
	 file,
	 NULL );

on_error_libmdmp:
	libmdmp_file_free(
	 &file,
	 NULL );

on_error_libbfio:
	libbfio_handle_free(
	 &file_io_handle,
	 NULL );

	return( 0 );
}

} /* extern "C" */
