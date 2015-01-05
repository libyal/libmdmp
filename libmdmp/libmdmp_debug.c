/*
 * Debug functions
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
#include <types.h>

#include "libmdmp_debug.h"
#include "libmdmp_definitions.h"
#include "libmdmp_libbfio.h"
#include "libmdmp_libcerror.h"
#include "libmdmp_libcnotify.h"

#if defined( HAVE_DEBUG_OUTPUT )

/* Prints the page flags
 */
void libmdmp_debug_print_file_flags(
      uint32_t file_flags )
{
	if( file_flags == 0x00000000UL )
	{
		libcnotify_printf(
		 "\t(MiniDumpNormal)\n" );
	}
	if( ( file_flags & 0x00000001 ) != 0 )
	{
		libcnotify_printf(
		 "\t(MiniDumpWithDataSegs)\n" );
	}
	if( ( file_flags & 0x00000002 ) != 0 )
	{
		libcnotify_printf(
		 "\t(MiniDumpWithFullMemory)\n" );
	}
	if( ( file_flags & 0x00000004 ) != 0 )
	{
		libcnotify_printf(
		 "\t(MiniDumpWithHandleData)\n" );
	}
	if( ( file_flags & 0x00000008 ) != 0 )
	{
		libcnotify_printf(
		 "\t(MiniDumpFilterMemory)\n" );
	}
	if( ( file_flags & 0x00000010 ) != 0 )
	{
		libcnotify_printf(
		 "\t(MiniDumpScanMemory)\n" );
	}
	if( ( file_flags & 0x00000020 ) != 0 )
	{
		libcnotify_printf(
		 "\t(MiniDumpWithUnloadedModules)\n" );
	}
	if( ( file_flags & 0x00000040 ) != 0 )
	{
		libcnotify_printf(
		 "\t(MiniDumpWithIndirectlyReferencedMemory)\n" );
	}
	if( ( file_flags & 0x00000080 ) != 0 )
	{
		libcnotify_printf(
		 "\t(MiniDumpFilterModulePaths)\n" );
	}
	if( ( file_flags & 0x00000100 ) != 0 )
	{
		libcnotify_printf(
		 "\t(MiniDumpWithProcessThreadData)\n" );
	}
	if( ( file_flags & 0x00000200 ) != 0 )
	{
		libcnotify_printf(
		 "\t(MiniDumpWithPrivateReadWriteMemory)\n" );
	}
	if( ( file_flags & 0x00000400 ) != 0 )
	{
		libcnotify_printf(
		 "\t(MiniDumpWithoutOptionalData)\n" );
	}
	if( ( file_flags & 0x00000800 ) != 0 )
	{
		libcnotify_printf(
		 "\t(MiniDumpWithFullMemoryInfo)\n" );
	}
	if( ( file_flags & 0x00001000 ) != 0 )
	{
		libcnotify_printf(
		 "\t(MiniDumpWithThreadInfo)\n" );
	}
	if( ( file_flags & 0x00002000 ) != 0 )
	{
		libcnotify_printf(
		 "\t(MiniDumpWithCodeSegs)\n" );
	}
	if( ( file_flags & 0x00004000 ) != 0 )
	{
		libcnotify_printf(
		 "\t(MiniDumpWithoutAuxiliaryState)\n" );
	}
	if( ( file_flags & 0x00008000 ) != 0 )
	{
		libcnotify_printf(
		 "\t(MiniDumpWithFullAuxiliaryState)\n" );
	}
	if( ( file_flags & 0x00010000 ) != 0 )
	{
		libcnotify_printf(
		 "\t(MiniDumpWithPrivateWriteCopyMemory)\n" );
	}
	if( ( file_flags & 0x00020000 ) != 0 )
	{
		libcnotify_printf(
		 "\t(MiniDumpIgnoreInaccessibleMemory)\n" );
	}
	if( ( file_flags & 0x00040000 ) != 0 )
	{
		libcnotify_printf(
		 "\t(MiniDumpWithTokenInformation)\n" );
	}
	if( ( file_flags & 0x00080000 ) != 0 )
	{
		libcnotify_printf(
		 "\t(MiniDumpWithModuleHeaders)\n" );
	}
	if( ( file_flags & 0x00100000 ) != 0 )
	{
		libcnotify_printf(
		 "\t(MiniDumpFilterTriage)\n" );
	}
}

/* Returns a string with the stream type description
 */
const char *libmdmp_debug_get_stream_type(
             uint32_t stream_type )
{
	switch( stream_type )
	{
/* TODO add descriptive names */
		case 0:
			return( "UnusedStream" );
		case 1:
			return( "ReservedStream0" );
		case 2:
			return( "ReservedStream1" );
		case 3:
			return( "ThreadListStream" );
		case 4:
			return( "ModuleListStream" );
		case 5:
			return( "MemoryListStream" );
		case 6:
			return( "ExceptionStream" );
		case 7:
			return( "SystemInfoStream" );
		case 8:
			return( "ThreadExListStream" );
		case 9:
			return( "Memory64ListStream" );
		case 10:
			return( "CommentStreamA" );
		case 11:
			return( "CommentStreamW" );
		case 12:
			return( "HandleDataStream" );
		case 13:
			return( "FunctionTableStream" );
		case 14:
			return( "UnloadedModuleListStream" );
		case 15:
			return( "MiscInfoStream" );
		case 16:
			return( "MemoryInfoListStream" );
		case 17:
			return( "ThreadInfoListStream" );
		case 18:
			return( "HandleOperationListStream" );

		default:
			break;
	}
	return( "UNKNOWN" );
}

/* Prints the read offsets
 * Returns 1 if successful or -1 on error
 */
int libmdmp_debug_print_read_offsets(
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	static char *function = "libmdmp_debug_print_read_offsets";
	off64_t offset        = 0;
	size64_t size         = 0;
	int number_of_offsets = 0;
	int offset_iterator   = 0;

	if( file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file io handle.",
		 function );

		return( -1 );
	}
	if( libbfio_handle_get_number_of_offsets_read(
	     file_io_handle,
	     &number_of_offsets,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of offsets read.",
		 function );

		return( -1 );
	}
	libcnotify_printf(
	 "Offsets read:\n" );

	for( offset_iterator = 0;
	     offset_iterator < number_of_offsets;
	     offset_iterator++ )
	{
		if( libbfio_handle_get_offset_read(
		     file_io_handle,
		     offset_iterator,
		     &offset,
		     &size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve offset: %d.",
			 function,
			 ( offset_iterator + 1 ) );

			return( -1 );
		}
		libcnotify_printf(
		 "%08" PRIi64 " ( 0x%08" PRIx64 " ) - %08" PRIi64 " ( 0x%08" PRIx64 " ) size: %" PRIu64 "\n",
		 offset,
		 offset,
		 offset + size,
		 offset + size,
		 size );
	}
	libcnotify_printf(
	 "\n" );

	return( 1 );
}

#endif

