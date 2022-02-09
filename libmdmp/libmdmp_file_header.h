/*
 * File header functions
 *
 * Copyright (C) 2014-2022, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBMDMP_FILE_HEADER_H )
#define _LIBMDMP_FILE_HEADER_H

#include <common.h>
#include <types.h>

#include "libmdmp_libbfio.h"
#include "libmdmp_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libmdmp_file_header libmdmp_file_header_t;

struct libmdmp_file_header
{
	/* The version
	 */
	uint16_t version;

	/* The number of streams
	 */
	uint32_t number_of_streams;

	/* The streams directory offset
	 */
	uint32_t streams_directory_offset;
};

int libmdmp_file_header_initialize(
     libmdmp_file_header_t **file_header,
     libcerror_error_t **error );

int libmdmp_file_header_free(
     libmdmp_file_header_t **file_header,
     libcerror_error_t **error );

int libmdmp_file_header_read_data(
     libmdmp_file_header_t *file_header,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libmdmp_file_header_read_file_io_handle(
     libmdmp_file_header_t *file_header,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBMDMP_FILE_HEADER_H ) */

