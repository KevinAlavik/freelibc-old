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

#ifndef __FREELIBC_STDINT_GCC_H
#define __FREELIBC_STDINT_GCC_H

#if defined(__FREELIBC_DEF_STDINT_GCC)

#include <limits.h>

// Fixed-width integer types
typedef signed char int8_t;
typedef short int int16_t;
typedef int int32_t;
typedef long long int int64_t;

typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long int uint64_t;

#if defined(__SIZEOF_INT128__)
typedef __int128 int128_t;
typedef unsigned __int128 uint128_t;
#endif

// Minimum-width integer types
typedef signed char int_least8_t;
typedef short int int_least16_t;
typedef int int_least32_t;
typedef long long int int_least64_t;

typedef unsigned char uint_least8_t;
typedef unsigned short int uint_least16_t;
typedef unsigned int uint_least32_t;
typedef unsigned long long int uint_least64_t;

#if defined(__SIZEOF_INT128__)
typedef __int128 int_least128_t;
typedef unsigned __int128 uint_least128_t;
#endif

// Fastest minimum-width integer types
typedef signed char int_fast8_t;
typedef int int_fast16_t;
typedef int int_fast32_t;
typedef long long int int_fast64_t;

typedef unsigned char uint_fast8_t;
typedef unsigned int uint_fast16_t;
typedef unsigned int uint_fast32_t;
typedef unsigned long long int uint_fast64_t;

#if defined(__SIZEOF_INT128__)
typedef __int128 int_fast128_t;
typedef unsigned __int128 uint_fast128_t;
#endif

// Integer types capable of holding object pointers
#if INTPTR_MAX == INT64_MAX
typedef long long int intptr_t;
typedef unsigned long long int uintptr_t;
#else
typedef int intptr_t;
typedef unsigned int uintptr_t;
#endif

// Greatest-width integer types
typedef long long int intmax_t;
typedef unsigned long long int uintmax_t;

#if defined(__SIZEOF_INT128__)
typedef __int128 intmax128_t;
typedef unsigned __int128 uintmax128_t;
#endif

// Limits of specified-width integer types
#define INT8_MIN (-128)
#define INT8_MAX 127
#define UINT8_MAX 255

#define INT16_MIN (-32768)
#define INT16_MAX 32767
#define UINT16_MAX 65535

#define INT32_MIN (-2147483648)
#define INT32_MAX 2147483647
#define UINT32_MAX 4294967295U

#define INT64_MIN (-9223372036854775807LL - 1)
#define INT64_MAX 9223372036854775807LL
#define UINT64_MAX 18446744073709551615ULL

#if defined(__SIZEOF_INT128__)
#define INT128_MIN (-170141183460469231731687303715884105727LL - 1)
#define INT128_MAX 170141183460469231731687303715884105727LL
#define UINT128_MAX 340282366920938463463374607431768211455ULL
#endif

// Limits of minimum-width integer types
#define INT_LEAST8_MIN INT8_MIN
#define INT_LEAST8_MAX INT8_MAX
#define UINT_LEAST8_MAX UINT8_MAX

#define INT_LEAST16_MIN INT16_MIN
#define INT_LEAST16_MAX INT16_MAX
#define UINT_LEAST16_MAX UINT16_MAX

#define INT_LEAST32_MIN INT32_MIN
#define INT_LEAST32_MAX INT32_MAX
#define UINT_LEAST32_MAX UINT32_MAX

#define INT_LEAST64_MIN INT64_MIN
#define INT_LEAST64_MAX INT64_MAX
#define UINT_LEAST64_MAX UINT64_MAX

#if defined(__SIZEOF_INT128__)
#define INT_LEAST128_MIN INT128_MIN
#define INT_LEAST128_MAX INT128_MAX
#define UINT_LEAST128_MAX UINT128_MAX
#endif

// Limits of fastest minimum-width integer types
#define INT_FAST8_MIN INT8_MIN
#define INT_FAST8_MAX INT8_MAX
#define UINT_FAST8_MAX UINT8_MAX

#define INT_FAST16_MIN INT32_MIN
#define INT_FAST16_MAX INT32_MAX
#define UINT_FAST16_MAX UINT32_MAX

#define INT_FAST32_MIN INT32_MIN
#define INT_FAST32_MAX INT32_MAX
#define UINT_FAST32_MAX UINT32_MAX

#define INT_FAST64_MIN INT64_MIN
#define INT_FAST64_MAX INT64_MAX
#define UINT_FAST64_MAX UINT64_MAX

#if defined(__SIZEOF_INT128__)
#define INT_FAST128_MIN INT128_MIN
#define INT_FAST128_MAX INT128_MAX
#define UINT_FAST128_MAX UINT128_MAX
#endif

// Limits of integer types capable of holding object pointers
#if INTPTR_MAX == INT64_MAX
#define INTPTR_MIN INT64_MIN
#define INTPTR_MAX INT64_MAX
#define UINTPTR_MAX UINT64_MAX
#else
#define INTPTR_MIN INT32_MIN
#define INTPTR_MAX INT32_MAX
#define UINTPTR_MAX UINT32_MAX
#endif

// Limits of greatest-width integer types
#define INTMAX_MIN INT64_MIN
#define INTMAX_MAX INT64_MAX
#define UINTMAX_MAX UINT64_MAX

#if defined(__SIZEOF_INT128__)
#define INTMAX128_MIN INT128_MIN
#define INTMAX128_MAX INT128_MAX
#define UINTMAX128_MAX UINT128_MAX
#endif

// Other integer type limits
#define PTRDIFF_MIN INTPTR_MIN
#define PTRDIFF_MAX INTPTR_MAX

#define SIZE_MAX UINTPTR_MAX

#define WCHAR_MIN 0
#define WCHAR_MAX 65535

#define WINT_MIN 0
#define WINT_MAX 65535

#endif // __FREELIBC_DEF_STDINT_GCC

#endif // __FREELIBC_STDINT_GCC_H
