/*
 * Section functions
 *
 * Copyright (C) 2014-2024, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBMDMP_INTERNAL_STREAM_H )
#define _LIBMDMP_INTERNAL_STREAM_H

#include <common.h>
#include <types.h>

#include "libmdmp_extern.h"
#include "libmdmp_io_handle.h"
#include "libmdmp_libbfio.h"
#include "libmdmp_libcerror.h"
#include "libmdmp_stream_descriptor.h"
#include "libmdmp_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libmdmp_internal_stream libmdmp_internal_stream_t;

struct libmdmp_internal_stream
{
	/* The IO handle
	 */
	libmdmp_io_handle_t *io_handle;

	/* The file IO handle
	 */
	libbfio_handle_t *file_io_handle;

	/* The stream descriptor
	 */
	libmdmp_stream_descriptor_t *stream_descriptor;
};

int libmdmp_stream_initialize(
     libmdmp_stream_t **stream,
     libmdmp_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libmdmp_stream_descriptor_t *stream_descriptor,
     libcerror_error_t **error );

LIBMDMP_EXTERN \
int libmdmp_stream_free(
     libmdmp_stream_t **stream,
     libcerror_error_t **error );

LIBMDMP_EXTERN \
int libmdmp_stream_get_type(
     libmdmp_stream_t *stream,
     uint32_t *type,
     libcerror_error_t **error );

LIBMDMP_EXTERN \
ssize_t libmdmp_stream_read_buffer(
         libmdmp_stream_t *stream,
         void *buffer,
         size_t buffer_size,
         libcerror_error_t **error );

LIBMDMP_EXTERN \
ssize_t libmdmp_stream_read_buffer_at_offset(
         libmdmp_stream_t *stream,
         void *buffer,
         size_t buffer_size,
         off64_t offset,
         libcerror_error_t **error );

LIBMDMP_EXTERN \
off64_t libmdmp_stream_seek_offset(
         libmdmp_stream_t *stream,
         off64_t offset,
         int whence,
         libcerror_error_t **error );

LIBMDMP_EXTERN \
int libmdmp_stream_get_offset(
     libmdmp_stream_t *stream,
     off64_t *offset,
     libcerror_error_t **error );

LIBMDMP_EXTERN \
int libmdmp_stream_get_size(
     libmdmp_stream_t *stream,
     size64_t *size,
     libcerror_error_t **error );

LIBMDMP_EXTERN \
int libmdmp_stream_get_start_offset(
     libmdmp_stream_t *stream,
     off64_t *start_offset,
     libcerror_error_t **error );

LIBMDMP_EXTERN \
int libmdmp_stream_get_data_file_io_handle(
     libmdmp_stream_t *stream,
     libbfio_handle_t **file_io_handle,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBMDMP_INTERNAL_STREAM_H ) */

