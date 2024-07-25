/*
Freelibc
Copyright (C) 2024 Kevin Alavik and contributors

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __FREELIBC_POSIX_LIMITS_H
#define __FREELIBC_POSIX_LIMITS_H

#ifdef __FREELIBC_POSIX_DEF_LIMITS

#define __FREELIBC_POSIX_DEF_STDDEF
#include <posix/stddef.h>

// Size of basic data types
#define CHAR_BIT 8 // Number of bits in a char

// Limits for integer types
#define CHAR_MIN (-128)
#define CHAR_MAX 127
#define UCHAR_MAX 255

#define SHRT_MIN (-32768)
#define SHRT_MAX 32767
#define USHRT_MAX 65535

#define INT_MIN (-2147483648)
#define INT_MAX 2147483647
#define UINT_MAX 4294967295U

#define LONG_MIN (-9223372036854775808LL)
#define LONG_MAX 9223372036854775807LL
#define ULONG_MAX 18446744073709551615ULL

// Limits for pointer types
#define PTRDIFF_MIN (-LONG_MAX)
#define PTRDIFF_MAX LONG_MAX

#define SIZE_MAX UINT_MAX

#define SSIZE_MIN (-LONG_MAX)
#define SSIZE_MAX LONG_MAX

// Limits for `intmax_t` and `uintmax_t`
#define INTMAX_MIN LONG_MIN
#define INTMAX_MAX LONG_MAX
#define UINTMAX_MAX ULONG_MAX

// Limits for `int128_t` and `uint128_t` (if supported)
#if defined(__SIZEOF_INT128__)
#define INT128_MIN (-__INT128_MAX__ - 1)
#define INT128_MAX __INT128_MAX__
#define UINT128_MAX (__UINT128_MAX__)
#else
// For platforms without native 128-bit support
typedef struct
{
    unsigned long long __low, __high;
} uint128_t;
typedef struct
{
    long long __low, __high;
} int128_t;
#define INT128_MIN (-9223372036854775808LL - 9223372036854775808LL)
#define INT128_MAX (9223372036854775807LL + 9223372036854775807LL)
#define UINT128_MAX 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFULL
#endif

#endif // __FREELIBC_POSIX_DEF_LIMITS

#endif // __FREELIBC_POSIX_LIMITS_H
