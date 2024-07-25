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

#ifndef __FREELIBC_POSIX_STDINT_H
#define __FREELIBC_POSIX_STDINT_H

#ifdef __FREELIBC_POSIX_DEF_STDINT

// Define fixed-width integer types
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;

typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef signed long int64_t;

// Define pointer-sized integer types
#if defined(__LP64__) || defined(_WIN64) || defined(__X86_64__) // 64-bit platform
typedef unsigned long uintptr_t;
typedef signed long intptr_t;
#else // Assume 32-bit platform
typedef unsigned int uintptr_t;
typedef signed int intptr_t;
#endif

// Define integer types capable of holding any object pointer
typedef intptr_t intptr_t;
typedef uintptr_t uintptr_t;

// Define minimum-width integer types
typedef int8_t int_least8_t;
typedef int16_t int_least16_t;
typedef int32_t int_least32_t;
typedef int64_t int_least64_t;
typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;
typedef uint32_t uint_least32_t;
typedef uint64_t uint_least64_t;

// Define fastest minimum-width integer types
typedef int32_t int_fast8_t;
typedef int32_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef int64_t int_fast64_t;
typedef uint32_t uint_fast8_t;
typedef uint32_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
typedef uint64_t uint_fast64_t;

// Define greatest-width integer types
typedef int64_t intmax_t;
typedef uint64_t uintmax_t;

// Define limits for integer types
#define INT8_MIN (-128)
#define INT8_MAX 127
#define UINT8_MAX 255
#define INT16_MIN (-32768)
#define INT16_MAX 32767
#define UINT16_MAX 65535
#define INT32_MIN (-2147483648)
#define INT32_MAX 2147483647
#define UINT32_MAX 4294967295U
#define INT64_MIN (-9223372036854775808LL)
#define INT64_MAX 9223372036854775807LL
#define UINT64_MAX 18446744073709551615ULL

#define INTMAX_MIN INT64_MIN
#define INTMAX_MAX INT64_MAX
#define UINTMAX_MAX UINT64_MAX

// Define 128-bit integer types
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

#endif // __FREELIBC_POSIX_DEF_STDINT

#endif // __FREELIBC_POSIX_STDINT_H
