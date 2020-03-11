/*
 * File functions
 *
 * Copyright (C) 2014-2020, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBMDMP_INTERNAL_FILE_H )
#define _LIBMDMP_INTERNAL_FILE_H

#include <common.h>
#include <types.h>

#include "libmdmp_extern.h"
#include "libmdmp_io_handle.h"
#include "libmdmp_libbfio.h"
#include "libmdmp_libcdata.h"
#include "libmdmp_libcerror.h"
#include "libmdmp_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libmdmp_internal_file libmdmp_internal_file_t;

struct libmdmp_internal_file
{
	/* The IO handle
	 */
	libmdmp_io_handle_t *io_handle;

	/* The file IO handle
	 */
	libbfio_handle_t *file_io_handle;

	/* Value to indicate if the file IO handle was created inside the library
	 */
	uint8_t file_io_handle_created_in_library;

	/* Value to indicate if the file IO handle was opened inside the library
	 */
	uint8_t file_io_handle_opened_in_library;

	/* The streams array
	 */
	libcdata_array_t *streams_array;
};

LIBMDMP_EXTERN \
int libmdmp_file_initialize(
     libmdmp_file_t **file,
     libcerror_error_t **error );

LIBMDMP_EXTERN \
int libmdmp_file_free(
     libmdmp_file_t **file,
     libcerror_error_t **error );

LIBMDMP_EXTERN \
int libmdmp_file_signal_abort(
     libmdmp_file_t *file,
     libcerror_error_t **error );

LIBMDMP_EXTERN \
int libmdmp_file_open(
     libmdmp_file_t *file,
     const char *filename,
     int access_flags,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )
LIBMDMP_EXTERN \
int libmdmp_file_open_wide(
     libmdmp_file_t *file,
     const wchar_t *filename,
     int access_flags,
     libcerror_error_t **error );
#endif

LIBMDMP_EXTERN \
int libmdmp_file_open_file_io_handle(
     libmdmp_file_t *file,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libcerror_error_t **error );

LIBMDMP_EXTERN \
int libmdmp_file_close(
     libmdmp_file_t *file,
     libcerror_error_t **error );

int libmdmp_file_open_read(
     libmdmp_internal_file_t *internal_file,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

LIBMDMP_EXTERN \
int libmdmp_file_get_number_of_streams(
     libmdmp_file_t *file,
     int *number_of_streams,
     libcerror_error_t **error );

LIBMDMP_EXTERN \
int libmdmp_file_get_stream(
     libmdmp_file_t *file,
     int stream_index,
     libmdmp_stream_t **stream,
     libcerror_error_t **error );

LIBMDMP_EXTERN \
int libmdmp_file_get_stream_by_type(
     libmdmp_file_t *file,
     uint32_t stream_type,
     libmdmp_stream_t **stream,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBMDMP_INTERNAL_FILE_H ) */

