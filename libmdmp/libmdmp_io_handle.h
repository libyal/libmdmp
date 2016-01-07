/*
 * Input/Output (IO) handle functions
 *
 * Copyright (C) 2014-2016, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBMDMP_IO_HANDLE_H )
#define _LIBMDMP_IO_HANDLE_H

#include <common.h>
#include <types.h>

#include "libmdmp_libbfio.h"
#include "libmdmp_libcdata.h"
#include "libmdmp_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

extern const char *mdmp_file_signature;

typedef struct libmdmp_io_handle libmdmp_io_handle_t;

struct libmdmp_io_handle
{
	/* The version
	 */
	uint16_t version;

	/* Value to indicate if abort was signalled
	 */
	int abort;
};

int libmdmp_io_handle_initialize(
     libmdmp_io_handle_t **io_handle,
     libcerror_error_t **error );

int libmdmp_io_handle_free(
     libmdmp_io_handle_t **io_handle,
     libcerror_error_t **error );

int libmdmp_io_handle_clear(
     libmdmp_io_handle_t *io_handle,
     libcerror_error_t **error );

int libmdmp_io_handle_read_file_header(
     libmdmp_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint32_t *streams_directory_offset,
     uint32_t *number_of_streams,
     libcerror_error_t **error );

int libmdmp_io_handle_read_streams_directory(
     libmdmp_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint32_t streams_directory_offset,
     uint32_t number_of_streams,
     libcdata_array_t *streams_array,
     libcerror_error_t **error );

ssize_t libmdmp_io_handle_read_segment_data(
         intptr_t *data_handle,
         libbfio_handle_t *file_io_handle,
         int segment_index,
         int segment_file_index,
         uint8_t *segment_data,
         size_t segment_data_size,
         uint32_t segment_flags,
         uint8_t read_flags,
         libcerror_error_t **error );

off64_t libmdmp_io_handle_seek_segment_offset(
         intptr_t *data_handle,
         libbfio_handle_t *file_io_handle,
         int segment_index,
         int segment_file_index,
         off64_t segment_offset,
         libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

