/*
 * Section descriptor functions
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

#if !defined( _LIBMDMP_STREAM_DESCRIPTOR_H )
#define _LIBMDMP_STREAM_DESCRIPTOR_H

#include <common.h>
#include <types.h>

#include "libmdmp_libcerror.h"
#include "libmdmp_libfdata.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libmdmp_stream_descriptor libmdmp_stream_descriptor_t;

struct libmdmp_stream_descriptor
{
	/* The type
	 */
	uint32_t type;

	/* The data stream
	 */
	libfdata_stream_t *data_stream;
};

int libmdmp_stream_descriptor_initialize(
     libmdmp_stream_descriptor_t **stream_descriptor,
     libcerror_error_t **error );

int libmdmp_stream_descriptor_free(
     libmdmp_stream_descriptor_t **stream_descriptor,
     libcerror_error_t **error );

int libmdmp_stream_descriptor_set_data_range(
     libmdmp_stream_descriptor_t *stream_descriptor,
     off64_t data_offset,
     size64_t data_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBMDMP_STREAM_DESCRIPTOR_H ) */

