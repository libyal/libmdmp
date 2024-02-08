/*
 * Codepage definitions for libmdmp
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

#if !defined( _LIBMDMP_CODEPAGE_H )
#define _LIBMDMP_CODEPAGE_H

#include <libmdmp/types.h>

#if defined( __cplusplus )
extern "C" {
#endif

/* The codepage definitions
 */
enum LIBMDMP_CODEPAGES
{
	LIBMDMP_CODEPAGE_ASCII				= 20127,

	LIBMDMP_CODEPAGE_ISO_8859_1			= 28591,
	LIBMDMP_CODEPAGE_ISO_8859_2			= 28592,
	LIBMDMP_CODEPAGE_ISO_8859_3			= 28593,
	LIBMDMP_CODEPAGE_ISO_8859_4			= 28594,
	LIBMDMP_CODEPAGE_ISO_8859_5			= 28595,
	LIBMDMP_CODEPAGE_ISO_8859_6			= 28596,
	LIBMDMP_CODEPAGE_ISO_8859_7			= 28597,
	LIBMDMP_CODEPAGE_ISO_8859_8			= 28598,
	LIBMDMP_CODEPAGE_ISO_8859_9			= 28599,
	LIBMDMP_CODEPAGE_ISO_8859_10			= 28600,
	LIBMDMP_CODEPAGE_ISO_8859_11			= 28601,
	LIBMDMP_CODEPAGE_ISO_8859_13			= 28603,
	LIBMDMP_CODEPAGE_ISO_8859_14			= 28604,
	LIBMDMP_CODEPAGE_ISO_8859_15			= 28605,
	LIBMDMP_CODEPAGE_ISO_8859_16			= 28606,

	LIBMDMP_CODEPAGE_KOI8_R				= 20866,
	LIBMDMP_CODEPAGE_KOI8_U				= 21866,

	LIBMDMP_CODEPAGE_WINDOWS_874			= 874,
	LIBMDMP_CODEPAGE_WINDOWS_932			= 932,
	LIBMDMP_CODEPAGE_WINDOWS_936			= 936,
	LIBMDMP_CODEPAGE_WINDOWS_949			= 949,
	LIBMDMP_CODEPAGE_WINDOWS_950			= 950,
	LIBMDMP_CODEPAGE_WINDOWS_1250			= 1250,
	LIBMDMP_CODEPAGE_WINDOWS_1251			= 1251,
	LIBMDMP_CODEPAGE_WINDOWS_1252			= 1252,
	LIBMDMP_CODEPAGE_WINDOWS_1253			= 1253,
	LIBMDMP_CODEPAGE_WINDOWS_1254			= 1254,
	LIBMDMP_CODEPAGE_WINDOWS_1255			= 1255,
	LIBMDMP_CODEPAGE_WINDOWS_1256			= 1256,
	LIBMDMP_CODEPAGE_WINDOWS_1257			= 1257,
	LIBMDMP_CODEPAGE_WINDOWS_1258			= 1258
};

#define LIBMDMP_CODEPAGE_US_ASCII			LIBMDMP_CODEPAGE_ASCII

#define LIBMDMP_CODEPAGE_ISO_WESTERN_EUROPEAN		LIBMDMP_CODEPAGE_ISO_8859_1
#define LIBMDMP_CODEPAGE_ISO_CENTRAL_EUROPEAN		LIBMDMP_CODEPAGE_ISO_8859_2
#define LIBMDMP_CODEPAGE_ISO_SOUTH_EUROPEAN		LIBMDMP_CODEPAGE_ISO_8859_3
#define LIBMDMP_CODEPAGE_ISO_NORTH_EUROPEAN		LIBMDMP_CODEPAGE_ISO_8859_4
#define LIBMDMP_CODEPAGE_ISO_CYRILLIC			LIBMDMP_CODEPAGE_ISO_8859_5
#define LIBMDMP_CODEPAGE_ISO_ARABIC			LIBMDMP_CODEPAGE_ISO_8859_6
#define LIBMDMP_CODEPAGE_ISO_GREEK			LIBMDMP_CODEPAGE_ISO_8859_7
#define LIBMDMP_CODEPAGE_ISO_HEBREW			LIBMDMP_CODEPAGE_ISO_8859_8
#define LIBMDMP_CODEPAGE_ISO_TURKISH			LIBMDMP_CODEPAGE_ISO_8859_9
#define LIBMDMP_CODEPAGE_ISO_NORDIC			LIBMDMP_CODEPAGE_ISO_8859_10
#define LIBMDMP_CODEPAGE_ISO_THAI			LIBMDMP_CODEPAGE_ISO_8859_11
#define LIBMDMP_CODEPAGE_ISO_BALTIC			LIBMDMP_CODEPAGE_ISO_8859_13
#define LIBMDMP_CODEPAGE_ISO_CELTIC			LIBMDMP_CODEPAGE_ISO_8859_14

#define LIBMDMP_CODEPAGE_ISO_LATIN_1			LIBMDMP_CODEPAGE_ISO_8859_1
#define LIBMDMP_CODEPAGE_ISO_LATIN_2			LIBMDMP_CODEPAGE_ISO_8859_2
#define LIBMDMP_CODEPAGE_ISO_LATIN_3			LIBMDMP_CODEPAGE_ISO_8859_3
#define LIBMDMP_CODEPAGE_ISO_LATIN_4			LIBMDMP_CODEPAGE_ISO_8859_4
#define LIBMDMP_CODEPAGE_ISO_LATIN_5			LIBMDMP_CODEPAGE_ISO_8859_9
#define LIBMDMP_CODEPAGE_ISO_LATIN_6			LIBMDMP_CODEPAGE_ISO_8859_10
#define LIBMDMP_CODEPAGE_ISO_LATIN_7			LIBMDMP_CODEPAGE_ISO_8859_13
#define LIBMDMP_CODEPAGE_ISO_LATIN_8			LIBMDMP_CODEPAGE_ISO_8859_14
#define LIBMDMP_CODEPAGE_ISO_LATIN_9			LIBMDMP_CODEPAGE_ISO_8859_15
#define LIBMDMP_CODEPAGE_ISO_LATIN_10			LIBMDMP_CODEPAGE_ISO_8859_16

#define LIBMDMP_CODEPAGE_KOI8_RUSSIAN			LIBMDMP_CODEPAGE_KOI8_R
#define LIBMDMP_CODEPAGE_KOI8_UKRAINIAN			LIBMDMP_CODEPAGE_KOI8_U

#define LIBMDMP_CODEPAGE_WINDOWS_THAI			LIBMDMP_CODEPAGE_WINDOWS_874
#define LIBMDMP_CODEPAGE_WINDOWS_JAPANESE		LIBMDMP_CODEPAGE_WINDOWS_932
#define LIBMDMP_CODEPAGE_WINDOWS_CHINESE_SIMPLIFIED	LIBMDMP_CODEPAGE_WINDOWS_936
#define LIBMDMP_CODEPAGE_WINDOWS_KOREAN			LIBMDMP_CODEPAGE_WINDOWS_949
#define LIBMDMP_CODEPAGE_WINDOWS_CHINESE_TRADITIONAL	LIBMDMP_CODEPAGE_WINDOWS_950
#define LIBMDMP_CODEPAGE_WINDOWS_CENTRAL_EUROPEAN	LIBMDMP_CODEPAGE_WINDOWS_1250
#define LIBMDMP_CODEPAGE_WINDOWS_CYRILLIC		LIBMDMP_CODEPAGE_WINDOWS_1251
#define LIBMDMP_CODEPAGE_WINDOWS_WESTERN_EUROPEAN	LIBMDMP_CODEPAGE_WINDOWS_1252
#define LIBMDMP_CODEPAGE_WINDOWS_GREEK			LIBMDMP_CODEPAGE_WINDOWS_1253
#define LIBMDMP_CODEPAGE_WINDOWS_TURKISH		LIBMDMP_CODEPAGE_WINDOWS_1254
#define LIBMDMP_CODEPAGE_WINDOWS_HEBREW			LIBMDMP_CODEPAGE_WINDOWS_1255
#define LIBMDMP_CODEPAGE_WINDOWS_ARABIC			LIBMDMP_CODEPAGE_WINDOWS_1256
#define LIBMDMP_CODEPAGE_WINDOWS_BALTIC			LIBMDMP_CODEPAGE_WINDOWS_1257
#define LIBMDMP_CODEPAGE_WINDOWS_VIETNAMESE		LIBMDMP_CODEPAGE_WINDOWS_1258

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBMDMP_CODEPAGE_H ) */

