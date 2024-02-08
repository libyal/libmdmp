/*
 * The file header definition of a Windows Minidump (MDMP) file
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

#if !defined( _MDMP_FILE_HEADER_H )
#define _MDMP_FILE_HEADER_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct mdmp_file_header mdmp_file_header_t;

struct mdmp_file_header
{
	/* Signature
	 * Consists of 4 bytes
	 * "MDMP"
	 */
	uint8_t signature[ 4 ];

	/* The version
	 * Consists of 2 bytes
	 */
	uint8_t version[ 2 ];

	/* The implementation version
	 * Consists of 2 bytes
	 */
	uint8_t implementation_version[ 2 ];

	/* The number of streams
	 * Consists of 4 bytes
	 */
	uint8_t number_of_streams[ 4 ];

	/* The streams directory RVA
	 * Consists of 4 bytes
	 */
	uint8_t streams_directory_rva[ 4 ];

	/* The checksum
	 * Consists of 4 bytes
	 */
	uint8_t checksum[ 4 ];

	/* The timestamp
	 * Consists of 4 bytes
	 */
	uint8_t timestamp[ 4 ];

	/* The file flags
	 * Consists of 4 bytes
	 */
	uint8_t file_flags[ 4 ];
};

typedef struct mdmp_streams_directory_entry mdmp_streams_directory_entry_t;

struct mdmp_streams_directory_entry
{
	/* The stream type
	 * Consists of 4 bytes
	 */
	uint8_t stream_type[ 4 ];

	/* The stream data size
	 * Consists of 4 bytes
	 */
	uint8_t stream_data_size[ 4 ];

	/* The stream data RVA
	 * Consists of 4 bytes
	 */
	uint8_t stream_data_rva[ 4 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _MDMP_FILE_HEADER_H ) */

